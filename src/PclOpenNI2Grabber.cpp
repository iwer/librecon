#include "recon/PclOpenNI2Grabber.h"
#include <pcl/common/io.h>

namespace recon
{

	PclOpenNI2Grabber::PclOpenNI2Grabber(void)
	{
		grabber_ =  new pcl::io::OpenNI2Grabber("", pcl::io::OpenNI2Grabber::OpenNI_Default_Mode, pcl::io::OpenNI2Grabber::OpenNI_Default_Mode);
		double depth_focal_length_x, depth_focal_length_y, depth_principal_point_x, depth_principal_point_y;
		grabber_->getDepthCameraIntrinsics(depth_focal_length_x, depth_focal_length_y, depth_principal_point_x, depth_principal_point_y);
	}

	PclOpenNI2Grabber::PclOpenNI2Grabber(std::string uri)
	{
		grabber_ =  new pcl::io::OpenNI2Grabber(uri, pcl::io::OpenNI2Grabber::OpenNI_Default_Mode, pcl::io::OpenNI2Grabber::OpenNI_Default_Mode);
		double depth_focal_length_x, depth_focal_length_y, depth_principal_point_x, depth_principal_point_y;
		grabber_->getDepthCameraIntrinsics(depth_focal_length_x, depth_focal_length_y, depth_principal_point_x, depth_principal_point_y);
	}

	PclOpenNI2Grabber::~PclOpenNI2Grabber(void)
	{
		delete(grabber_);
	}

	void PclOpenNI2Grabber::aquireFrame()
	{
		// for synchronizing frame aquisition of multiple cameras
	}

	void PclOpenNI2Grabber::start()
	{
		grabber_->start();
		// connect cloud callback to openni grabber
		boost::function<void (const pcl::PointCloud<pcl::PointXYZRGBA>::ConstPtr&) > cloud_cb = boost::bind (&PclOpenNI2Grabber::cloud_callback, this, _1);
		cloud_connection_ = grabber_->registerCallback (cloud_cb);
	}

	CameraIntrinsics::Ptr PclOpenNI2Grabber::getDepthIntrinsics()
	{
		double depth_focal_length_x, depth_focal_length_y, depth_principal_point_x, depth_principal_point_y;
		grabber_->getDepthCameraIntrinsics(depth_focal_length_x, depth_focal_length_y, depth_principal_point_x, depth_principal_point_y);
		auto x_res = grabber_->getDevice()->getDepthVideoMode().x_resolution_;
		auto y_res = grabber_->getDevice()->getDepthVideoMode().y_resolution_;
		CameraIntrinsics intrinsics(depth_focal_length_x, depth_focal_length_y, depth_principal_point_x, depth_principal_point_y, x_res, y_res);
		return boost::make_shared<CameraIntrinsics>(intrinsics);
	}

	void PclOpenNI2Grabber::stop()
	{
		grabber_->stop();
		cloud_connection_.disconnect();
	}

	void PclOpenNI2Grabber::cloud_callback (const pcl::PointCloud<pcl::PointXYZRGBA>::ConstPtr& cloud)
	{
		boost::mutex::scoped_lock lock (cloud_mutex_);
		Cloud alphaRemovedCloud;
		pcl::copyPointCloud<pcl::PointXYZRGBA, PointType>(*cloud, alphaRemovedCloud);
		cloud_ = boost::make_shared<Cloud>(alphaRemovedCloud);
		//std::cout << "Grabbed clouds size: " << cloud_->size() << std::endl;
	}



}