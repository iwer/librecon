#include "AbstractPointProcessor.h"
#include <pcl/segmentation/segment_differences.h>

namespace recon
{
	class StaticBackgroundRemover 
		: public AbstractPointProcessor 
	{
	public:
		StaticBackgroundRemover();
		~StaticBackgroundRemover() override;

		void processData() override;
		void setBackGroundCloud(CloudConstPtr backGroundCloud);
	private:
		CloudConstPtr backGroundCloud_;
		pcl::SegmentDifferences<PointType> sd_;

	}; 
}
