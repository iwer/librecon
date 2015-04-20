#include "..\include\recon\DummySensor.h"

namespace recon {
	DummySensor::DummySensor(void)
	{
	}


	DummySensor::~DummySensor(void)
	{
	}

	void DummySensor::setBackGroundImpl()
	{
		std::cerr << "WARNING: This is only a dummy sensor. It does virtually nothing!" << std::endl;
	}
}

