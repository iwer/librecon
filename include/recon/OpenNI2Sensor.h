#pragma once
#include "recon/AbstractSensor.h"
#include "recon/PclOpenNI2Grabber.h"
#include <pcl/io/openni2/openni2_device_info.h>

namespace recon
{

	class OpenNI2Sensor :
		public AbstractSensor
	{
	public:
		EIGEN_MAKE_ALIGNED_OPERATOR_NEW;
		explicit OpenNI2Sensor(pcl::io::openni2::OpenNI2DeviceInfo deviceInfo, int deviceId);
		~OpenNI2Sensor(void);
		void setBackGroundImpl() override;
	private:
		PclOpenNI2Grabber * grabber_;
	};

}
