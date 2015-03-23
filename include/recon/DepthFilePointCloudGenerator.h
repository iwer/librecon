#include "AbstractPointCloudGenerator.h"
#include <pcl/io/image.h>
#include <pcl/io/image_depth.h>
#include <pcl/io/vtk_lib_io.h>
#include <OniCAPI.h>
#include <stdint.h>

class DepthFilePointCloudGenerator : AbstractPointCloudGenerator {

	/** \brief Basic camera parameters placeholder. */
	struct CameraParameters
	{
		/** fx */
		double focal_length_x;
		/** fy */
		double focal_length_y;
		/** cx */
		double principal_point_x;
		/** cy */
		double principal_point_y;

		CameraParameters (double initValue)
			: focal_length_x (initValue), focal_length_y (initValue),
			principal_point_x (initValue),  principal_point_y (initValue)
		{}

		CameraParameters (double fx, double fy, double cx, double cy)
			: focal_length_x (fx), focal_length_y (fy), principal_point_x (cx), principal_point_y (cy)
		{ }
	};

public:
	DepthFilePointCloudGenerator();
	DepthFilePointCloudGenerator(float focalLength);
	~DepthFilePointCloudGenerator();

	void aquireFrame() override;

	void start() override;

	void stop() override;


	void loadDepthImageFromFile(std::string rgbFileName, std::string depthFileName);
private:
	std::string rgb_frame_id_;
	std::string depth_frame_id_;
	unsigned image_width_;
	unsigned image_height_;
	unsigned depth_width_;
	unsigned depth_height_;

	float rgb_focal_length_;
	float depth_focal_length_;

	CameraParameters rgb_parameters_;
	CameraParameters depth_parameters_;

	std::vector<uint8_t> color_resize_buffer_;
	std::vector<uint16_t> depth_resize_buffer_;
};
