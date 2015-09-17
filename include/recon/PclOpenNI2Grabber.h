#pragma once

#include "typedefs.h"
#include "AbstractPointCloudGenerator.h"
#include <pcl/io/openni2_grabber.h>
#include <recon/CameraIntrinsics.h>
namespace recon
{
	class PclOpenNI2Grabber :
		public AbstractPointCloudGenerator
	{
	public:
		EIGEN_MAKE_ALIGNED_OPERATOR_NEW;
		PclOpenNI2Grabber(void);
		PclOpenNI2Grabber(std::string uri);
		~PclOpenNI2Grabber(void);

		void aquireFrame() override;
		void cloud_callback (const pcl::PointCloud<pcl::PointXYZRGBA>::ConstPtr& cloud);
		void image_callback(const boost::shared_ptr<pcl::io::Image>& image);


		void start() override;
		void stop() override;
		bool isRunning();

		CameraIntrinsics::Ptr getDepthIntrinsics();

	private:
		pcl::io::OpenNI2Grabber * grabber_;
		boost::signals2::connection cloud_connection_;
		boost::signals2::connection image_connection_;

		bool fully_started;
	}; 
}

