#pragma once

#include "AbstractMeshProcessor.h"
#include "AbstractPointProcessor.h"
#include "typedefs.h"
#include "AbstractSensor.h"

namespace recon
{
	class AbstractProcessingPipeline
	{
	public:
		EIGEN_MAKE_ALIGNED_OPERATOR_NEW;
		AbstractProcessingPipeline(int cloudCount);
		virtual ~AbstractProcessingPipeline(void);

		void setInputCloud(CloudConstPtr cloud, int cloudIndex);
		void setSensor(AbstractSensor::Ptr sensor, int index);
		virtual void processData() = 0;

		CloudConstPtr getOutputCloud();
		CloudConstPtr getInputCloud(int index);
		TrianglesPtr getTriangles();


	protected:
		int cloudCount_;
		//std::vector<CloudConstPtr> clouds_;
		std::vector<AbstractSensor::Ptr> sensors_;
		CloudConstPtr meshCloud_;
		TrianglesPtr triangles_;

		AbstractPointProcessor * pp_;
		AbstractMeshProcessor * mp_;
	};
}

