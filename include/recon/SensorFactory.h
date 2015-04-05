#pragma once
#include "recon/AbstractPointCloudGenerator.h"


namespace recon
{
	class SensorFactory
	{
	public:
		SensorFactory();
		~SensorFactory();
		//static AbstractPointCloudGenerator::Ptr createFilePointCloudGenerator();
		//static AbstractPointCloudGenerator::Ptr createPclOpenNI2Grabber();
	};

}
