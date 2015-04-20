#pragma once
#include "AbstractProcessingPipeline.h"
#include "DepthThreshold.h"
#include "GreedyProjectionMeshProcessor.h"
#include <boost/signals2.hpp>
#include "PointCloudSampler.h"
#include "StaticBackgroundRemover.h"

namespace recon
{
	class Pipeline02 :
		public AbstractProcessingPipeline
	{
	public:
		EIGEN_MAKE_ALIGNED_OPERATOR_NEW;
		Pipeline02(int inputCloudCount,
			boost::signals2::signal<void (float)> * minDepUpdate, 
			boost::signals2::signal<void (float)> * maxDepUpdate, 
			boost::signals2::signal<void (float)> * triangleSizeUpdate,
			boost::signals2::signal<void (int)> * normalKNeighbourUpdate,
			boost::signals2::signal<void (float)> * muUpdate,
			boost::signals2::signal<void (int)> * maxNearestNeighboursUpdate,
			boost::signals2::signal<void (float)> * updateSampleResolution);
		~Pipeline02(void);

		void processData() override;

	private:
		DepthThreshold d_;
		StaticBackgroundRemover bgr_;
		PointCloudSampler s_;
		GreedyProjectionMeshProcessor g_;
	}; 
}

