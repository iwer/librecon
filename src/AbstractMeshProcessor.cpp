#include "recon/AbstractMeshProcessor.h"


namespace recon
{
	AbstractMeshProcessor::AbstractMeshProcessor(void) :
		inputCloud_(new Cloud),
		triangles_(new std::vector<pcl::Vertices>)
	{
	}


	AbstractMeshProcessor::~AbstractMeshProcessor(void)
	{
	}

	CloudConstPtr AbstractMeshProcessor::getInputCloud()
	{
		//boost::mutex::scoped_lock(cloud_mutex_);
		return inputCloud_;
	}

	TrianglesPtr AbstractMeshProcessor::getTriangles()
	{
		//boost::mutex::scoped_lock(triangle_mutex_);
		return triangles_;
	}

	void AbstractMeshProcessor::setInputCloud(CloudConstPtr cloud)
	{
		inputCloud_ .swap(cloud);
		//triangles_.reset(new std::vector<pcl::Vertices>);
	}


}