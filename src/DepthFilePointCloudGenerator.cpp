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

DepthFilePointCloudGenerator::DepthFilePointCloudGenerator() 
	: rgb_parameters_(std::numeric_limits<double>::quiet_NaN () )
	, depth_parameters_(std::numeric_limits<double>::quiet_NaN () )
{
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
	int components = color_image_data->GetNumberOfScalarComponents ();
	int dimensions[3];
	color_image_data->GetDimensions (dimensions);

	// Load the depth input file
	vtkSmartPointer<vtkImageData> depth_image_data;
	vtkSmartPointer<vtkPNGReader> depth_reader;
	bool enable_depth = false;
	float v_viewing_angle = 43.0f;
	float h_viewing_angle = 57.0f;
	float depth_unit_magic = 1000.0f;
	depth_reader = vtkSmartPointer<vtkPNGReader>::New ();
	depth_reader->SetFileName (depthFileName.c_str());
	depth_reader->Update ();
	depth_image_data = depth_reader->GetOutput ();
	int depth_components = depth_image_data->GetNumberOfScalarComponents ();
	int depth_dimensions[3];
	depth_image_data->GetDimensions(depth_dimensions);
	
	std::cout << "Components: " << components << " Dimensions: " << dimensions[0] << ", " << dimensions[1] << ", " << dimensions[2] << std::endl;
	std::cout << "DepthComponents: " << depth_components << " DepthDimensions: " << depth_dimensions[0] << ", " << depth_dimensions[1] << ", " << depth_dimensions[2] << std::endl;


}

// from pcl/io/openni2_grabber
CloudPtr DepthFilePointCloudGenerator::convertToXYZRGBPointCloud (const pcl::io::Image::Ptr &image, const pcl::io::DepthImage::Ptr &depth_image)
{
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

	auto depth_map = static_cast<const uint16_t*>(depth_image->getData ());
	if (depth_image->getWidth () != depth_width_ || depth_image->getHeight () != depth_height_)
	{
		// Resize the image if nessacery
		depth_resize_buffer_.resize(depth_width_ * depth_height_);
		depth_map = depth_resize_buffer_.data();
		depth_image->fillDepthImageRaw (depth_width_, depth_height_, const_cast<unsigned short*>(depth_map) );
	}

	auto rgb_buffer = static_cast<const uint8_t*>(image->getData ());
	if (image->getWidth () != image_width_ || image->getHeight () != image_height_)
	{
		// Resize the image if nessacery
		color_resize_buffer_.resize(image_width_ * image_height_ * 3);
		rgb_buffer = color_resize_buffer_.data();
		image->fillRGB (image_width_, image_height_, const_cast<unsigned char*>(rgb_buffer), image_width_ * 3);
	}


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

			auto pixel = depth_map[value_idx];
			if (pixel != 0 &&
				pixel != depth_image->getNoSampleValue () &&
				pixel != depth_image->getShadowValue () )
			{
				pt.z = depth_map[value_idx] * 0.001f;  // millimeters to meters
				pt.x = (static_cast<float> (u) - cx) * pt.z * fx_inv;
				pt.y = (static_cast<float> (v) - cy) * pt.z * fy_inv;
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

			color.Red   = rgb_buffer[value_idx];
			color.Green = rgb_buffer[value_idx + 1];
			color.Blue  = rgb_buffer[value_idx + 2];

			pt.rgba = color.long_value;
		}
	}
	cloud->sensor_origin_.setZero ();
	cloud->sensor_orientation_.setIdentity ();
	return (cloud);
}