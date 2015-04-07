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
		PclOpenNI2Grabber(void);
		PclOpenNI2Grabber(std::string uri);
		~PclOpenNI2Grabber(void);

		void aquireFrame() override;
		void cloud_callback (const pcl::PointCloud<pcl::PointXYZRGBA>::ConstPtr& cloud);

		void start() override;
		void stop() override;

		CameraIntrinsics::Ptr getDepthIntrinsics();

	private:
		pcl::io::OpenNI2Grabber * grabber_;
		boost::signals2::connection cloud_connection_;


	}; 
}

