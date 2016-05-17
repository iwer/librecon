#include "recon/PclOpenNI2Grabber.h"
#include <pcl/common/io.h>

namespace recon
{

	PclOpenNI2Grabber::PclOpenNI2Grabber(void)
		: AbstractPointCloudGenerator()
		, fully_started(false)
	{
		grabber_ =  new pcl::io::OpenNI2Grabber("", pcl::io::OpenNI2Grabber::OpenNI_Default_Mode, pcl::io::OpenNI2Grabber::OpenNI_VGA_30Hz);
	}

	PclOpenNI2Grabber::PclOpenNI2Grabber(std::string uri)
		: AbstractPointCloudGenerator()
		, fully_started(false)
	{
		grabber_ =  new pcl::io::OpenNI2Grabber(uri, pcl::io::OpenNI2Grabber::OpenNI_Default_Mode, pcl::io::OpenNI2Grabber::OpenNI_VGA_30Hz);
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
		
		boost::function<void (const boost::shared_ptr<pcl::io::Image>&)> image_cb = boost::bind (&PclOpenNI2Grabber::image_callback, this, _1);
		image_connection_ = grabber_->registerCallback(image_cb);

		std::cout << "Grabber " << this << " started. " << std::endl;
	}

	CameraIntrinsics::Ptr PclOpenNI2Grabber::getDepthIntrinsics()
	{
		double depth_focal_length_x, depth_focal_length_y, depth_principal_point_x, depth_principal_point_y;
		// this does not return anything!!!
		//grabber_->getDepthCameraIntrinsics(depth_focal_length_x, depth_focal_length_y, depth_principal_point_x, depth_principal_point_y);
		
		auto x_res = grabber_->getDevice()->getDepthVideoMode().x_resolution_;
		auto y_res = grabber_->getDevice()->getDepthVideoMode().y_resolution_;
		// default values
		depth_principal_point_x =  x_res / 2 - 0.5;
		depth_principal_point_y =  y_res / 2 - 0.5;

		depth_focal_length_x = 531.15;
		depth_focal_length_y = 531.15;

		CameraIntrinsics intrinsics(depth_focal_length_x, depth_focal_length_y, depth_principal_point_x, depth_principal_point_y, x_res, y_res);
		return boost::make_shared<CameraIntrinsics>(intrinsics);
	}

	void PclOpenNI2Grabber::stop()
	{
		grabber_->stop();
		cloud_connection_.disconnect();
		image_connection_.disconnect();
		std::cout << "Grabber " << this << " stopped" << std::endl;
	}

	bool PclOpenNI2Grabber::isRunning()
	{
		return grabber_->isRunning() && cloud_connection_.connected() && fully_started;
	}

	void PclOpenNI2Grabber::cloud_callback (const pcl::PointCloud<pcl::PointXYZRGBA>::ConstPtr& cloud)
	{
		boost::mutex::scoped_lock lock (cloud_mutex_);
		fully_started = true;
		Cloud alphaRemovedCloud;
		pcl::copyPointCloud<pcl::PointXYZRGBA, PointType>(*cloud, alphaRemovedCloud);
		cloud_ = alphaRemovedCloud.makeShared();
	}

	void PclOpenNI2Grabber::image_callback(const boost::shared_ptr<pcl::io::Image>& newImage)
	{
		boost::mutex::scoped_lock lock(image_mutex_);
		//std::cout << "Got " << newImage->getDataSize() << " bytes of image data" << std::endl;
		image_ = newImage;
	}
	void PclOpenNI2Grabber::setMirror(bool mirrorEnabled)
	{
		grabber_->getDevice()->setMirror(mirrorEnabled);
	}
}