#include "recon/Pipeline01.h"


Pipeline01::Pipeline01(boost::signals2::signal<void (float)> * minDepUpdate, 
					   boost::signals2::signal<void (float)> * maxDepUpdate, 
					   boost::signals2::signal<void (float)> * triangleSizeUpdate)
					   : AbstractProcessingPipeline(1)
{


	pp_ = &d;
	mp_ = &m;

	minDepUpdate->connect(boost::bind(&DepthThreshold::setDepthThresholdMin, &d, _1));
	maxDepUpdate->connect(boost::bind(&DepthThreshold::setDepthThresholdMax, &d, _1));
	triangleSizeUpdate->connect(boost::bind(&Pipeline01::updateTriangleSize, this, _1));
}


Pipeline01::~Pipeline01(void)
{
}

void Pipeline01::updateTriangleSize(float size)
{
	m.setEdgeLength(int(size));
}

void Pipeline01::processData()
{
	pp_->setInputCloud(clouds_[0]);
	pp_->processData();
	mp_->setInputCloud(pp_->getOutputCloud());
	mp_->processData();
	meshCloud_ = mp_->getInputCloud();
	triangles_ = mp_->getTriangles();
}