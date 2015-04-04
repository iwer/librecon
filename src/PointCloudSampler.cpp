#include "recon/PointCloudSampler.h"
namespace recon
{

	PointCloudSampler::PointCloudSampler() 
		: AbstractPointProcessor()
	{
		resolution_ = .1; // 10 cm
	}

	PointCloudSampler::~PointCloudSampler()
	{
	}

	void PointCloudSampler::processData() {
		if(inputCloud_->size() > 0)
		{
			vg_.setDownsampleAllData(true);
			vg_.setLeafSize(resolution_, resolution_, resolution_);
			vg_.setInputCloud(inputCloud_);
			vg_.filter(*outputCloud_);
		}
		//std::cout << "Sampler: " << inputCloud_->size() << " : " << outputCloud_->size() << std::endl;
	}

	float PointCloudSampler::getResolution() const
	{
		return resolution_;
	}

	void PointCloudSampler::setResolution(float resolution)
	{
		resolution_ = resolution;
		std::cout << "Resolution updated to: " << resolution << std::endl;
	} 
}