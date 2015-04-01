#include "recon/GreedyProjectionMeshProcessor.h"


GreedyProjectionMeshProcessor::GreedyProjectionMeshProcessor(void)
	: tree (new pcl::search::KdTree<PointType>)
	, normals (new pcl::PointCloud<pcl::Normal>)
	, normalKNeighbours_(20)
	, maxEdgeLength_(0.025)
	, mu_(2.5)
	, maxNearestNeighbours_(150)
{
}


GreedyProjectionMeshProcessor::~GreedyProjectionMeshProcessor(void)
{
}

void GreedyProjectionMeshProcessor::setMaxNearestNeighbours(int n)
{
	//maxNearestNeighbours_ = n;
}

void GreedyProjectionMeshProcessor::setMu(float mu)
{
	//mu_ = mu;
}

void GreedyProjectionMeshProcessor::setMaxEdgeLength(float edgeLength)
{
	//maxEdgeLength_ = edgeLength;
}

void GreedyProjectionMeshProcessor::setNormalKNeighbours(int k)
{
	//normalKNeighbours_ = k;
}

void GreedyProjectionMeshProcessor::processData() 
{
	// Normal estimation*
	tree->setInputCloud (inputCloud_);
	n.setInputCloud (inputCloud_);
	n.setSearchMethod (tree);
	n.setKSearch (normalKNeighbours_);
	n.compute (*normals);

	//* normals should not contain the point normals + surface curvatures

	// Concatenate the XYZ and normal fields*
	pcl::PointCloud<PointNormalType>::Ptr cloud_with_normals (new pcl::PointCloud<PointNormalType>);
	pcl::concatenateFields (*inputCloud_.get(), *normals.get(), *cloud_with_normals.get());
	//* cloud_with_normals = cloud + normals

	// Create search tree*
	pcl::search::KdTree<PointNormalType>::Ptr tree2 (new pcl::search::KdTree<PointNormalType>);
	tree2->setInputCloud (cloud_with_normals);

	// Set the maximum distance between connected points (maximum edge length)

	gp3.setSearchRadius (maxEdgeLength_);

	// Set typical values for the parameters
	gp3.setMu (mu_);
	gp3.setMaximumNearestNeighbors (maxNearestNeighbours_);
	gp3.setMaximumSurfaceAngle(M_PI/2); // 45 degrees
	gp3.setMinimumAngle(M_PI/18); // 10 degrees
	gp3.setMaximumAngle(2*M_PI/3); // 120 degrees
	gp3.setNormalConsistency(false);

	// Get result
	gp3.setInputCloud (cloud_with_normals);
	gp3.setSearchMethod (tree2);
	gp3.reconstruct (*triangles_);

	// Additional vertex information
	auto parts = gp3.getPartIDs();
	auto states = gp3.getPointStates();
}
