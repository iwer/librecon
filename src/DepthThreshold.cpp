#include "recon/DepthThreshold.h"

namespace recon
{
	DepthThreshold::DepthThreshold(void):
		AbstractPointProcessor()
	{
		depthThreshMax_ = 5;
		depthThreshMin_ = .1;
		pass_.setFilterFieldName ("z");
		pass_.setKeepOrganized(false);
	}

	DepthThreshold::~DepthThreshold(void)
	{
	}

	void DepthThreshold::processData()
	{
		if(inputCloud_->size() > 0) {
			pass_.setFilterLimits (depthThreshMin_, depthThreshMax_);
			pass_.setInputCloud(inputCloud_);
			pass_.filter(outputCloud_);
			//std::cout << "DepthThresh in: "<< inputCloud_->size() << " out: " << outputCloud_.size() << std::endl;
		}
	}

	float DepthThreshold::getDepthThresholdMax()
	{
		return depthThreshMax_;
	}

	void DepthThreshold::setDepthThresholdMax(float value)
	{
		depthThreshMax_ = value;
		std::cout << "Updated Depth Threshold Max to " << value << std::endl;
	}

	float DepthThreshold::getDepthThresholdMin()
	{
		return depthThreshMin_;
	}

	void DepthThreshold::setDepthThresholdMin(float value)
	{
		depthThreshMin_ = value;
		std::cout << "Updated Depth Threshold Min to " << value << std::endl;
	}

}