#include "recon/OrganizedFastMeshProcessor.h"

namespace recon
{

	OrganizedFastMeshProcessor::OrganizedFastMeshProcessor(void) :
		AbstractMeshProcessor(){
			ofm_.setTriangulationType (pcl::OrganizedFastMesh<PointType>::TRIANGLE_LEFT_CUT);
			ofmPixelSize_ = 5;
	}


	OrganizedFastMeshProcessor::~OrganizedFastMeshProcessor(void)
	{
	}

	void OrganizedFastMeshProcessor::processData()
	{
		if(inputCloud_->size() > 0) {
			// fast organized mesh triangulation
			std::cout << "Cloud Size before Meshing: " << inputCloud_->points.size() << std::endl;

			ofm_.setTrianglePixelSize (ofmPixelSize_);
			ofm_.setInputCloud(inputCloud_);
			{
				//boost::mutex::scoped_lock(triangle_mutex_);
				ofm_.reconstruct (*triangles_);
			}
			ofm_.getIndices();
			//std::cout << "Reconstructed triangles: " << triangles_->size() << std::endl;

		}
	}

	int OrganizedFastMeshProcessor::getEdgeLength()
	{
		return ofmPixelSize_;
	}

	void OrganizedFastMeshProcessor::setEdgeLength(int value)
	{
		ofmPixelSize_ = value;
	}


}