#include "recon/AbstractProcessingPipeline.h"
#include "recon/DummySensor.h"


namespace recon
{
	AbstractProcessingPipeline::AbstractProcessingPipeline(int cloudCount) 
		: cloudCount_(cloudCount)
		, meshCloud_(new Cloud)
		, triangles_(new std::vector<pcl::Vertices>)
	{
		for(auto i = 0; i < cloudCount_; i++) 
		{
			sensors_.push_back(boost::make_shared<DummySensor>(DummySensor()));
		}
	}


	AbstractProcessingPipeline::~AbstractProcessingPipeline(void)
	{
	}

	void AbstractProcessingPipeline::setSensor(AbstractSensor::Ptr sensor, int index)
	{
		if(index < cloudCount_){
			sensors_[index] = sensor;
		}
	}

	CloudConstPtr AbstractProcessingPipeline::getOutputCloud()
	{
		return meshCloud_;
	}

	TrianglesPtr AbstractProcessingPipeline::getTriangles()
	{
		return triangles_;
	}

}