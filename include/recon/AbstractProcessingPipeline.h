#pragma once

#include "AbstractMeshProcessor.h"
#include "AbstractPointProcessor.h"
#include "typedefs.h"

class AbstractProcessingPipeline
{
public:
	EIGEN_MAKE_ALIGNED_OPERATOR_NEW;
	AbstractProcessingPipeline(int cloudCount);
	~AbstractProcessingPipeline(void);

	void setInputCloud(CloudConstPtr cloud, int cloudIndex);
	virtual void processData() = 0;

	CloudConstPtr getOutputCloud();
	TrianglesPtr getTriangles();


protected:
	int cloudCount_;
	std::vector<CloudConstPtr> clouds_;
	CloudConstPtr meshCloud_;
	TrianglesPtr triangles_;

	AbstractPointProcessor * pp_;
	AbstractMeshProcessor * mp_;
};

