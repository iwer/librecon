#include "recon/DepthFilePointCloudGenerator.h"


// Treat color as chars, float32, or uint32
typedef union
{
	struct
	{
		unsigned char Blue;
		unsigned char Green;
		unsigned char Red;
		unsigned char Alpha;
	};
	float float_value;
	uint32_t long_value;
} RGBValue;

inline float raw_depth_to_meters(int depth_value){
	float depth_value_f = (float) depth_value; 
	if (depth_value < 2047){ 
		float depth = 1.0 / (depth_value_f  * -0.0030711016 + 3.3309495161);
		return depth; 
	}

	return 0.0f; 
} 

inline void	depth2xyz (float v_viewing_angle, float h_viewing_angle,
					   int image_width, int image_height, int image_x, int image_y,
					   float depth, float &x, float &y, float &z)
{
	float width, height;
	static const float PI = 3.1415927;
	if (depth <= 0.0f)
	{
		x = y = z = std::numeric_limits<float>::quiet_NaN ();
	}
	else
	{
		width = depth * std::tan (h_viewing_angle * PI / 180 / 2) * 2;
		height = depth * std::tan (v_viewing_angle * PI / 180 / 2) * 2;
		x = (image_x - image_width / 2.0) / image_width * width;
		y = (image_height / 2.0 - image_y) / image_height * height;
		z = depth;
	}
}


DepthFilePointCloudGenerator::DepthFilePointCloudGenerator() 
	: rgb_parameters_(std::numeric_limits<double>::quiet_NaN () )
	, depth_parameters_(std::numeric_limits<double>::quiet_NaN () )
{
}

DepthFilePointCloudGenerator::DepthFilePointCloudGenerator(float focalLength)
	: rgb_parameters_(std::numeric_limits<double>::quiet_NaN () )
	, depth_parameters_(std::numeric_limits<double>::quiet_NaN () )
{
	rgb_focal_length_ = focalLength;
	depth_focal_length_ = focalLength;
}

DepthFilePointCloudGenerator::~DepthFilePointCloudGenerator()
{

}


void DepthFilePointCloudGenerator::aquireFrame() {
	// TODO - implement DepthFilePointCloudGenerator::aquireFrame
	throw "Not yet implemented";
}

void DepthFilePointCloudGenerator::start() {
	// TODO - implement DepthFilePointCloudGenerator::start
	throw "Not yet implemented";
}

void DepthFilePointCloudGenerator::stop() {
	// TODO - implement DepthFilePointCloudGenerator::stop
	throw "Not yet implemented";
}

// from here: https://github.com/PointCloudLibrary/pcl/blob/647de7bed7df7cd383e5948ff42b116e5aae0e79/tools/png2pcd.cpp
void DepthFilePointCloudGenerator::loadDepthImageFromFile(std::string rgbFileName, std::string depthFileName) {
	// Load the color input file
	vtkSmartPointer<vtkImageData> color_image_data;
	vtkSmartPointer<vtkPNGReader> color_reader = vtkSmartPointer<vtkPNGReader>::New ();
	color_reader->SetFileName (rgbFileName.c_str());
	color_reader->Update ();
	color_image_data = color_reader->GetOutput ();
	auto components = color_image_data->GetNumberOfScalarComponents ();
	int dimensions[3];
	color_image_data->GetDimensions (dimensions);
	image_width_ = dimensions[0];
	image_height_ = dimensions[1];


	// Load the depth input file
	vtkSmartPointer<vtkImageData> depth_image_data;
	vtkSmartPointer<vtkPNGReader> depth_reader;
	auto enable_depth = false;
	auto v_viewing_angle = 43.0f;
	auto h_viewing_angle = 57.0f;
	auto depth_unit_magic = 1000.0f;
	depth_reader = vtkSmartPointer<vtkPNGReader>::New ();
	depth_reader->SetFileName (depthFileName.c_str());
	depth_reader->Update ();
	depth_image_data = depth_reader->GetOutput ();
	auto depth_components = depth_image_data->GetNumberOfScalarComponents ();
	int depth_dimensions[3];
	depth_image_data->GetDimensions(depth_dimensions);
	depth_width_ = depth_dimensions[0];
	depth_height_ = depth_dimensions[1];

	std::cout << "Components: " << components << " Dimensions: " 
		<< dimensions[0] << ", " << dimensions[1] << ", " << dimensions[2] 
		<< " Scalarsize: " << color_image_data->GetScalarSize() << std::endl;
	std::cout << "DepthComponents: " << depth_components << " DepthDimensions: " 
		<< depth_dimensions[0] << ", " << depth_dimensions[1] << ", " << depth_dimensions[2] 
		<< " Scalarsize: " << depth_image_data->GetScalarSize() << std::endl;

	// #  create pointcloud  ################################ 

	boost::shared_ptr<pcl::PointCloud<PointType> > cloud (new pcl::PointCloud<PointType>);

	cloud->header.frame_id = rgb_frame_id_;
	cloud->height = std::max (image_height_, depth_height_);
	cloud->width = std::max (image_width_, depth_width_);
	cloud->is_dense = false;

	cloud->points.resize (cloud->height * cloud->width);

	// Generate default camera parameters
	auto fx = depth_focal_length_; // Horizontal focal length
	auto fy = depth_focal_length_; // Vertcal focal length
	auto cx = (static_cast<float>(depth_width_) - 1.f) / 2.f;  // Center x
	auto cy = (static_cast<float>(depth_height_)- 1.f) / 2.f; // Center y

	// Load pre-calibrated camera parameters if they exist
	if (pcl_isfinite (depth_parameters_.focal_length_x))
		fx =  1.0f / static_cast<float> (depth_parameters_.focal_length_x);

	if (pcl_isfinite (depth_parameters_.focal_length_y))
		fy =  1.0f / static_cast<float> (depth_parameters_.focal_length_y);

	if (pcl_isfinite (depth_parameters_.principal_point_x))
		cx =  static_cast<float> (depth_parameters_.principal_point_x);

	if (pcl_isfinite (depth_parameters_.principal_point_y))
		cy =  static_cast<float> (depth_parameters_.principal_point_y);

	// Get inverse focal length for calculations below
	auto fx_inv = 1.0f / fx;
	auto fy_inv = 1.0f / fy;

	// no resizing

	float bad_point = std::numeric_limits<float>::quiet_NaN ();

	// set xyz to Nan and rgb to 0 (black)  
	if (image_width_ != depth_width_)
	{
		PointType pt;
		pt.x = pt.y = pt.z = bad_point;
		pt.b = pt.g = pt.r = 0;
		pt.a = 255; // point has no color info -> alpha = max => transparent 
		cloud->points.assign (cloud->points.size (), pt);
	}

	// fill in XYZ values
	auto step = cloud->width / depth_width_;
	auto skip = cloud->width * step - cloud->width;

	auto value_idx = 0;
	auto point_idx = 0;

	for (auto v = 0; v < depth_height_; ++v, point_idx += skip)
	{
		for (auto u = 0; u < depth_width_; ++u, ++value_idx, point_idx += step)
		{
			PointType& pt = cloud->points[point_idx];
			/// @todo Different values for these cases
			// Check for invalid measurements

			//auto pixel = depth_map[value_idx];
			auto pixel = 255 - depth_image_data->GetScalarComponentAsFloat (u, v, 0, 0);// / depth_unit_magic;
			//std::cout << "Depthvalue: " << pixel << std::endl;
			if (pixel != 0 /*&&
						   pixel != depth_image->getNoSampleValue () &&
						   pixel != depth_image->getShadowValue () */)
			{
				depth2xyz((0.5 * depth_height_ / depth_focal_length_), (0.5 * depth_width_ / depth_focal_length_),
					depth_width_, depth_height_, u, v,
					pixel, pt.x, pt.y, pt.z);
				//pt.z = pixel;  // millimeters to meters
				//pt.x = (static_cast<float> (u) - cx) * pt.z * fx_inv;
				//pt.y = (static_cast<float> (v) - cy) * pt.z * fy_inv;
			}
			else
			{
				pt.x = pt.y = pt.z = bad_point;
			}
		}
	}

	// fill in the RGB values
	step = cloud->width / image_width_;
	skip = cloud->width * step - cloud->width;

	value_idx = 0;
	point_idx = 0;
	RGBValue color;
	color.Alpha = 0;

	for (unsigned yIdx = 0; yIdx < image_height_; ++yIdx, point_idx += skip)
	{
		for (unsigned xIdx = 0; xIdx < image_width_; ++xIdx, point_idx += step, value_idx += 3)
		{
			PointType& pt = cloud->points[point_idx];

			//color.Red   = rgb_buffer[value_idx];
			//color.Green = rgb_buffer[value_idx + 1];
			//color.Blue  = rgb_buffer[value_idx + 2];
			color.Red	= color_image_data->GetScalarComponentAsDouble (xIdx, yIdx, 0, 0);
			color.Green	= color_image_data->GetScalarComponentAsDouble (xIdx, yIdx, 0, 1);
			color.Blue	= color_image_data->GetScalarComponentAsDouble (xIdx, yIdx, 0, 2);
			color.Alpha = color_image_data->GetScalarComponentAsDouble (xIdx, yIdx, 0, 3);

			pt.rgba = color.long_value;
		}
	}
	cloud->sensor_origin_.setZero ();
	cloud->sensor_orientation_.setIdentity();
	//return (cloud);
	{
		boost::mutex::scoped_lock(cloud_mutex_);
		cloud_ = cloud;
	}
}

