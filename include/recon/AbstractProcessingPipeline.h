#pragma once

#include "AbstractMeshProcessor.h"
#include "AbstractPointProcessor.h"
#include "typedefs.h"
#include "AbstractSensor.h"
#include "Frame.h"

namespace recon
{
	class AbstractProcessingPipeline
	{
	public:
		EIGEN_MAKE_ALIGNED_OPERATOR_NEW;
		explicit AbstractProcessingPipeline(int cloudCount);
		virtual ~AbstractProcessingPipeline(void);

		void setSensor(AbstractSensor::Ptr sensor, int index);
		virtual void processData() = 0;
		virtual void processData(Frame::Ptr frame) = 0;

		CloudConstPtr getOutputCloud();
		TrianglesPtr getTriangles();


	protected:
		int cloudCount_;
		std::vector<AbstractSensor::Ptr> sensors_;
		CloudConstPtr meshCloud_;
		TrianglesPtr triangles_;

		AbstractPointProcessor * pp_;
		AbstractMeshProcessor * mp_;
	};
}

