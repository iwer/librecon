#include "recon/DepthThreshold.h"

DepthThreshold::DepthThreshold(void):
	AbstractPointProcessor()
{
	depthThreshMax = 1.5;
	depthThreshMin = 0;
	pass_.setFilterFieldName ("z");
	pass_.setKeepOrganized(true);
}

DepthThreshold::~DepthThreshold(void)
{
}

void DepthThreshold::processData()
{
	if(inputCloud_->size() > 0) {
		pass_.setFilterLimits (depthThreshMin, depthThreshMax);
		pass_.setInputCloud(inputCloud_);
		pass_.filter(*outputCloud_);
	}
}

float DepthThreshold::getDepthThresholdMax()
{
	return depthThreshMax;
}

void DepthThreshold::setDepthThresholdMax(float value)
{
	depthThreshMax = value;
	std::cout << "Updated Depth Threshold Max to " << value << std::endl;
}

float DepthThreshold::getDepthThresholdMin()
{
	return depthThreshMin;
}

void DepthThreshold::setDepthThresholdMin(float value)
{
	depthThreshMin = value;
	std::cout << "Updated Depth Threshold Min to " << value << std::endl;
}
