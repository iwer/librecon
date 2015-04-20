#pragma once
#include "AbstractSensor.h"

namespace recon {
	class DummySensor :
		public AbstractSensor
	{

	public:
		DummySensor(void);
		~DummySensor(void);
	protected:
		void setBackGroundImpl() override;
	};

}


