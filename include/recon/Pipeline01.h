#pragma once
#include "AbstractProcessingPipeline.h"
#include "DepthThreshold.h"
#include "OrganizedFastMeshProcessor.h"
#include <boost/signals2.hpp>

namespace recon
{
	class Pipeline01 :
		public AbstractProcessingPipeline
	{
	public:
		Pipeline01(boost::signals2::signal<void (float)> * minDepUpdate, 
			boost::signals2::signal<void (float)> * maxDepUpdate, 
			boost::signals2::signal<void (float)> * triangleSizeUpdate);
		~Pipeline01(void);

		void processData() override;
		void updateTriangleSize(float size);
		DepthThreshold d_;
		OrganizedFastMeshProcessor m_;
	}; 
}

