#pragma once

#include "typedefs.h"

namespace recon
{
	class AbstractPointProcessor
	{
	public:
		AbstractPointProcessor(void);
		virtual ~AbstractPointProcessor(void);

		void setInputCloud(CloudConstPtr);
		virtual void processData() = 0;
		CloudPtr getOutputCloud();

	protected:
		CloudConstPtr inputCloud_;
		CloudPtr outputCloud_;
	};
}

