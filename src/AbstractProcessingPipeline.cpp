#include "recon/AbstractProcessingPipeline.h"


namespace recon
{
	AbstractProcessingPipeline::AbstractProcessingPipeline(int cloudCount) 
		: cloudCount_(cloudCount)
		, meshCloud_(new Cloud)
		, triangles_(new std::vector<pcl::Vertices>)
	{
		for(auto i = 0; i < cloudCount_; i++) 
		{
			clouds_.push_back(CloudConstPtr(new Cloud));
		}
	}


	AbstractProcessingPipeline::~AbstractProcessingPipeline(void)
	{
	}

	void AbstractProcessingPipeline::setInputCloud(CloudConstPtr cloud, int cloudIndex)
	{
		if(cloudIndex<cloudCount_){
			clouds_[cloudIndex].swap(cloud);
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