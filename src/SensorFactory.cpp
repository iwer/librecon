#include "recon/SensorFactory.h"
#include <pcl/io/openni2/openni2_device_manager.h>
#include "recon/PclOpenNI2Grabber.h"
#include "recon/OpenNI2Sensor.h"

namespace recon
{
	SensorFactory::SensorFactory(void)
		: deviceIds_()
		, nextSensorIndex_(0)
	{

	}


	SensorFactory::~SensorFactory(void)
	{
	}

	AbstractSensor::Ptr SensorFactory::createFilePointCloudGenerator()
	{
		//AbstractSensor::Ptr sensor()
		return nullptr;
	}

	AbstractSensor::Ptr SensorFactory::createPclOpenNI2Grabber()
	{
		std::cout << "Creating sensor #" << nextSensorIndex_ << std::endl;
		auto nDevices = pcl::io::openni2::OpenNI2DeviceManager::getInstance()->getNumOfConnectedDevices();
		if (nextSensorIndex_ < nDevices)
		{
			auto info(deviceIds_.at(nextSensorIndex_));
			AbstractSensor::Ptr sensor(new OpenNI2Sensor(info, nextSensorIndex_));
			nextSensorIndex_++;
			return sensor;
		}
		else
		{
			return nullptr;
		}
	}

	void SensorFactory::checkConnectedDevices()
	{
		auto man = pcl::io::openni2::OpenNI2DeviceManager::getInstance();
		auto deviceInfo = man->getConnectedDeviceInfos();
		for (auto &d : *deviceInfo)
		{
			std::cout << "Device: " << std::endl;
			std::cout << " * Vendor:	" << d.vendor_ << std::endl;
			std::cout << " * Name:	" << d.name_ << std::endl;
			std::cout << " * ProductId:	" << d.product_id_ << std::endl;
			std::cout << " * URI:		" << d.uri_ << std::endl;
			deviceIds_.push_back(d);
		}
	}

}