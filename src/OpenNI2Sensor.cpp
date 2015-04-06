#include "recon/OpenNI2Sensor.h"


namespace recon
{
	OpenNI2Sensor::OpenNI2Sensor(pcl::io::openni2::OpenNI2DeviceInfo deviceInfo, int deviceId)
		: AbstractSensor()
		, grabber_(new PclOpenNI2Grabber("#" + std::to_string(deviceId + 1)))
	{
		cloudSource_ = grabber_;
		grabber_->start();
		depthIntrinsics_ = grabber_->getDepthIntrinsics();
		std::cout << "Created new OpenNI2 Sensor: " << deviceInfo.vendor_ << " " << deviceInfo.name_ << std::endl;
		std::cout << "Initial Intrinsics:" << std::endl; 
		std::cout << "Resolution    : " << depthIntrinsics_->getSensorWidth() << "x" << depthIntrinsics_->getSensorHeight() << std::endl ;
		std::cout << "Principalpoint: " << std::to_string(depthIntrinsics_->getPrincipalPointX()) << ":" << std::to_string(depthIntrinsics_->getPrincipalPointX()) << std::endl;
		std::cout << "Focallength   : " << std::to_string(depthIntrinsics_->getFocalLengthX()) << ":" << std::to_string(depthIntrinsics_->getFocalLengthX()) << std::endl;
		std::cout << "Fiel of View  : " << std::to_string(depthIntrinsics_->getHFov()) << ":" << std::to_string(depthIntrinsics_->getHFov()) << std::endl;
	}


	OpenNI2Sensor::~OpenNI2Sensor(void)
	{
		grabber_->stop();
	}

	void OpenNI2Sensor::setBackGroundImpl()
	{ 
		background_ = grabber_->getOutputCloud();
	}
}
