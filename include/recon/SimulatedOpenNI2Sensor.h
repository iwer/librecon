#pragma once
#include "recon/AbstractSensor.h"
#include "recon/FilePointCloudGenerator.h"
#include <string>

namespace recon
{
	class SimulatedOpenNI2Sensor :
		public AbstractSensor
	{
	public:
		EIGEN_MAKE_ALIGNED_OPERATOR_NEW;
		SimulatedOpenNI2Sensor(std::string fileName, std::string backgroundFilename);
		~SimulatedOpenNI2Sensor(void);

		void setBackGroundImpl() override;
	private:
		FilePointCloudGenerator * grabber_;
		std::string fileName_;
		std::string backgroundFileName_;
	}; 
}

