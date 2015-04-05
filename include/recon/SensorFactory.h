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
		SensorFactory();
		~SensorFactory();
		AbstractSensor::Ptr createFilePointCloudGenerator();
		AbstractSensor::Ptr createPclOpenNI2Grabber();
		void checkConnectedDevices();
	private:
		std::vector<pcl::io::openni2::OpenNI2DeviceInfo> deviceIds_;
		int nextSensorIndex_;
	};

}
