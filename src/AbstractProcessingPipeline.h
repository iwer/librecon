#pragma once

#include "AbstractMeshProcessor.h"
#include "AbstractPointProcessor.h"
#include "typedefs.h"

class AbstractProcessingPipeline
{
public:
	AbstractProcessingPipeline(void);
	~AbstractProcessingPipeline(void);

	void setInputCloud(CloudConstPtr cloud);
	virtual void processData() = 0;

	CloudConstPtr getInputCloud();
	TrianglesPtr getTriangles();


protected:
	CloudConstPtr cloud_;
	CloudConstPtr meshCloud_;
	TrianglesPtr triangles_;

	AbstractPointProcessor * pp_;
	AbstractMeshProcessor * mp_;
};

