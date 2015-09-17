#pragma once
#include "recon/AbstractSensor.h"
#include <pcl/io/openni2/openni2_device_info.h>
#include <vector>
#include <string>

namespace recon
{
	class SensorFactory
	{
	public:
		EIGEN_MAKE_ALIGNED_OPERATOR_NEW;
		SensorFactory();
		~SensorFactory();
		AbstractSensor::Ptr createFilePointCloudGenerator(std::string fileName, std::string backgroundFileName);
		AbstractSensor::Ptr createPclOpenNI2Grabber();
		int checkConnectedDevices(bool output);
	private:
		std::vector<pcl::io::openni2::OpenNI2DeviceInfo> openNIDeviceIds_;
		int nextOpenNISensorIndex_;
		int nextFileSensorIndex_;
	};

}
