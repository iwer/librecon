#include "recon/OrganizedFastMeshProcessor.h"

namespace recon
{

	OrganizedFastMeshProcessor::OrganizedFastMeshProcessor(void) :
		AbstractMeshProcessor(){
			ofm_.setTriangulationType (pcl::OrganizedFastMesh<PointType>::TRIANGLE_LEFT_CUT);
			edgeLength_ = 5;
	}


	OrganizedFastMeshProcessor::~OrganizedFastMeshProcessor(void)
	{
	}

	void OrganizedFastMeshProcessor::processData()
	{
		if(inputCloud_->size() > 0) {
			// fast organized mesh triangulation
			ofm_.setTrianglePixelSize (edgeLength_);
			ofm_.setInputCloud(inputCloud_);
			ofm_.reconstruct (*triangles_);
			//std::cout << "Reconstructed triangles: " << triangles_->size() << " from " << inputCloud_->size() << " points" << std::endl;

		}
	}

	int OrganizedFastMeshProcessor::getEdgeLength()
	{
		return edgeLength_;
	}

	void OrganizedFastMeshProcessor::setEdgeLength(int value)
	{
		edgeLength_ = value;
	}


}