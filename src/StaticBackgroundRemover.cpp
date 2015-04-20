#include "recon/StaticBackgroundRemover.h"
namespace recon
{
	StaticBackgroundRemover::StaticBackgroundRemover()
		: AbstractPointProcessor()
	{
	}

	StaticBackgroundRemover::~StaticBackgroundRemover()
	{
	}

	void StaticBackgroundRemover::processData() {
		if(inputCloud_->size() > 0) {
			sd_.setInputCloud(inputCloud_);
			sd_.setDistanceThreshold(1);
			sd_.setTargetCloud(backGroundCloud_);
			sd_.segment(*outputCloud_);
		}
	}

	void StaticBackgroundRemover::setBackGroundCloud(CloudConstPtr backGroundCloud) {
		backGroundCloud_.swap(backGroundCloud);
	}

}