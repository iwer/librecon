#include "AbstractPointProcessor.h"
#include <pcl/segmentation/segment_differences.h>

namespace recon
{
	class StaticBackgroundRemover : AbstractPointProcessor {

	public:
		void processData() override;

		void getBackGroundCloud();

		void setBackGroundCloud(CloudConstPtr backGroundCloud);
	private:
		CloudConstPtr backGroundCloud_;
		pcl::SegmentDifferences<PointType> sd_;

	}; 
}
