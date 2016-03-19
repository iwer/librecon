#include "recon/SensorFactory.h"
#include <pcl/io/openni2/openni2_device_manager.h>
#include "recon/PclOpenNI2Grabber.h"
#include "recon/OpenNI2Sensor.h"
#include "recon/SimulatedOpenNI2Sensor.h"

namespace recon
{
	SensorFactory::SensorFactory(void)
		: openNIDeviceIds_()
		, nextOpenNISensorIndex_(0)
		, nextFileSensorIndex_(0)
	{

	}


	SensorFactory::~SensorFactory(void)
	{
	}

	AbstractSensor::Ptr SensorFactory::createFilePointCloudGenerator(std::string fileName, std::string backgroundFileName)
	{
		std::cout << "Creating simulated sensor #" << nextFileSensorIndex_ << std::endl;
		AbstractSensor::Ptr sensor(new SimulatedOpenNI2Sensor(fileName, backgroundFileName));
		nextFileSensorIndex_++;
		return sensor;
	}

	AbstractSensor::Ptr SensorFactory::createPclOpenNI2Grabber()
	{
		std::cout << "Creating OpenNI sensor #" << nextOpenNISensorIndex_ << std::endl;
		auto nDevices = pcl::io::openni2::OpenNI2DeviceManager::getInstance()->getNumOfConnectedDevices();
		if (nextOpenNISensorIndex_ < nDevices)
		{
			auto info(openNIDeviceIds_.at(nextOpenNISensorIndex_));
			std::cout << "OpenNI Sensor: " << info.name_ << std::endl;
			AbstractSensor::Ptr sensor(new OpenNI2Sensor(info, nextOpenNISensorIndex_));
			std::cout << sensor->getId() << std::endl;
			nextOpenNISensorIndex_++;
			return sensor;
		}
		else
		{
			return nullptr;
		}
	}

	int SensorFactory::checkConnectedDevices(bool output)
	{
		auto man = pcl::io::openni2::OpenNI2DeviceManager::getInstance();
		auto deviceInfo = man->getConnectedDeviceInfos();
		if (deviceInfo->size() > 0) {
			for (auto &d : *deviceInfo)
			{
				if(output)
				{
					std::cout << "Device: " << std::endl;
					std::cout << " * Vendor:	" << d.vendor_ << std::endl;
					std::cout << " * Name:	" << d.name_ << std::endl;
					std::cout << " * ProductId:	" << d.product_id_ << std::endl;
					std::cout << " * URI:		" << d.uri_ << std::endl;
				}
				openNIDeviceIds_.push_back(d);
			}
		} else
		{
			std::cout << "No OpenNI2 compatible devices connected." << std::endl;
		}
		return deviceInfo->size();
	}

}