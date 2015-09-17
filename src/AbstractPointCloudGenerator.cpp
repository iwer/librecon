#include "recon/AbstractPointCloudGenerator.h"


namespace recon
{
	AbstractPointCloudGenerator::AbstractPointCloudGenerator(void) :
		cloud_(new Cloud)
	{
	}


	AbstractPointCloudGenerator::~AbstractPointCloudGenerator(void)
	{
	}

	CloudConstPtr AbstractPointCloudGenerator::getOutputCloud()
	{
		CloudConstPtr temp_cloud_;

		if(cloud_mutex_.try_lock()) {
			//temp_cloud_.swap(cloud_);
			temp_cloud_ = cloud_;
			cloud_mutex_.unlock();
			//std::cout << "Got cloud, has points: " << temp_cloud_->size() << std::endl;
		}

		return temp_cloud_;
	}

	ImagePtr AbstractPointCloudGenerator::getOutputImage()
	{
		ImagePtr tmp_image;
		if(image_mutex_.try_lock())
		{
			tmp_image = image_;
			cloud_mutex_.unlock();
		}
		return tmp_image;
	}
}


