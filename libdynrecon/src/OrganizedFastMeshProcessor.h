#pragma once
#include "AbstractMeshProcessor.h"
#include "Controls.h"
#include <pcl/surface/organized_fast_mesh.h>

#include "typedefs.h"

/**
  * Very fast Triangulator. Relies on organized Point Clouds because it exploits the known neighbourhood relations.
  */
class OrganizedFastMeshProcessor :
	public AbstractMeshProcessor
{
public:
	OrganizedFastMeshProcessor(void);
	~OrganizedFastMeshProcessor(void);

	void processData();
	void guiEvent(ofxUIEventArgs &e);
private:
	pcl::OrganizedFastMesh<PointType> ofm;
	boost::shared_ptr<std::vector<pcl::Vertices> > vertices_;

	int ofmPixelSize;


};

