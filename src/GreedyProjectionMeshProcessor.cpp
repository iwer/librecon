#include "recon/GreedyProjectionMeshProcessor.h"


namespace recon
{
	GreedyProjectionMeshProcessor::GreedyProjectionMeshProcessor(void)
		: tree_(new pcl::search::KdTree<PointType>)
		, normals_(new pcl::PointCloud<pcl::Normal>)
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
		maxNearestNeighbours_ = n;
	}

	void GreedyProjectionMeshProcessor::setMu(float mu)
	{
		mu_ = mu;
	}

	void GreedyProjectionMeshProcessor::setMaxEdgeLength(float edgeLength)
	{
		maxEdgeLength_ = edgeLength;
	}

	void GreedyProjectionMeshProcessor::setNormalKNeighbours(int k)
	{
		normalKNeighbours_ = k;
	}

	void GreedyProjectionMeshProcessor::processData() 
	{
		// Normal estimation*
		tree_->setInputCloud (inputCloud_);
		n_.setInputCloud (inputCloud_);
		n_.setSearchMethod (tree_);
		n_.setKSearch (normalKNeighbours_);
		n_.compute (*normals_);

		//* normals should not contain the point normals + surface curvatures

		// Concatenate the XYZ and normal fields*
		pcl::PointCloud<PointNormalType>::Ptr cloud_with_normals (new pcl::PointCloud<PointNormalType>);
		pcl::concatenateFields (*inputCloud_.get(), *normals_.get(), *cloud_with_normals.get());
		//* cloud_with_normals = cloud + normals

		// Create search tree*
		pcl::search::KdTree<PointNormalType>::Ptr tree2 (new pcl::search::KdTree<PointNormalType>);
		tree2->setInputCloud (cloud_with_normals);

		// Set the maximum distance between connected points (maximum edge length)

		gp3_.setSearchRadius (maxEdgeLength_);

		// Set typical values for the parameters
		gp3_.setMu (mu_);
		gp3_.setMaximumNearestNeighbors (maxNearestNeighbours_);
		gp3_.setMaximumSurfaceAngle(M_PI/2); // 45 degrees
		gp3_.setMinimumAngle(M_PI/18); // 10 degrees
		gp3_.setMaximumAngle(2*M_PI/3); // 120 degrees
		gp3_.setNormalConsistency(false);

		// Get result
		gp3_.setInputCloud (cloud_with_normals);
		gp3_.setSearchMethod (tree2);
		gp3_.reconstruct (*triangles_);

		// Additional vertex information
		auto parts = gp3_.getPartIDs();
		auto states = gp3_.getPointStates();
	}

}