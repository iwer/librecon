#pragma once

#include "typedefs.h"

namespace recon
{
	class AbstractPointProcessor
	{
	public:
		EIGEN_MAKE_ALIGNED_OPERATOR_NEW;
		AbstractPointProcessor(void);
		virtual ~AbstractPointProcessor(void);

		void setInputCloud(CloudConstPtr);
		virtual void processData() = 0;
		CloudPtr getOutputCloud();

	protected:
		CloudConstPtr inputCloud_;
		Cloud outputCloud_;
	};
}

