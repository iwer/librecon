#include "recon/DummySensor.h"

namespace recon {
	DummySensor::DummySensor(void)
	{
		cloudSource_ = nullptr;
	}

	DummySensor::DummySensor(int id)
		: AbstractSensor(id)
	{
		cloudSource_ = nullptr;
	}

	DummySensor::~DummySensor(void)
	{
	}

	void DummySensor::setBackGroundImpl()
	{
		std::cerr << "WARNING: This is only a dummy sensor. It does virtually nothing!" << std::endl;
	}
}

