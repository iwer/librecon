#include "recon/StaticBackgroundRemover.h"
#include <pcl/common/time.h>

namespace recon
{
	StaticBackgroundRemover::StaticBackgroundRemover()
		: AbstractPointProcessor()
		, tree_(new pcl::search::KdTree<PointType>)
	{
	}

	StaticBackgroundRemover::~StaticBackgroundRemover()
	{
	}

	void StaticBackgroundRemover::processData() {
		pcl::ScopeTime t1("Background removal");
		if(inputCloud_->size() > 0) {
			sd_.setInputCloud(inputCloud_);
			sd_.setDistanceThreshold(.002);
			sd_.setSearchMethod(tree_);
			sd_.setTargetCloud(backGroundCloud_);
			sd_.segment(outputCloud_);
		}
	}

	void StaticBackgroundRemover::setBackGroundCloud(CloudConstPtr &backGroundCloud) {
		backGroundCloud_.swap(backGroundCloud);
	}

}