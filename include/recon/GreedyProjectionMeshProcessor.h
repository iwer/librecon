#pragma once
#include "typedefs.h"
#include "AbstractMeshProcessor.h"
#include <pcl/surface/gp3.h>
#include <pcl/features/normal_3d.h>
#include <pcl/kdtree/kdtree_flann.h>

class GreedyProjectionMeshProcessor :
	public AbstractMeshProcessor
{
public:
	GreedyProjectionMeshProcessor(void);
	~GreedyProjectionMeshProcessor(void);

	void processData() override;

	void setNormalKNeighbours(int k);
	void setMaxEdgeLength(float edgeLength);
	void setMu(float mu);
	void setMaxNearestNeighbours(int n);

private:
	pcl::NormalEstimation<PointType, pcl::Normal> n;
	pcl::search::KdTree<PointType>::Ptr tree;
	pcl::GreedyProjectionTriangulation<PointNormalType> gp3;

	pcl::PointCloud<pcl::Normal>::Ptr normals;

	int normalKNeighbours_;
	double maxEdgeLength_;
	double mu_;
	int maxNearestNeighbours_;

};

