#pragma once
#include "AbstractSensor.h"

namespace recon {
	class DummySensor :
		public AbstractSensor
	{

	public:
		EIGEN_MAKE_ALIGNED_OPERATOR_NEW;
		DummySensor(void);
		DummySensor(int id);
		~DummySensor(void);
	protected:
		void setBackGroundImpl() override;
	};

}


