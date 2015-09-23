#pragma once
#include "AbstractMeshProcessor.h"
#include <pcl/surface/organized_fast_mesh.h>

#include "typedefs.h"

/**
  * Very fast Triangulator. Relies on organized Point Clouds because it exploits the known neighbourhood relations.
  */
namespace recon
{
	class OrganizedFastMeshProcessor :
		public AbstractMeshProcessor
	{
	public:
		EIGEN_MAKE_ALIGNED_OPERATOR_NEW;
		OrganizedFastMeshProcessor(void);
		~OrganizedFastMeshProcessor(void);

		void processData() override;

		int getEdgeLength();
		void setEdgeLength(int value); 
	private:
		pcl::OrganizedFastMesh<PointType> ofm_;

		int edgeLength_;


	}; 
}

