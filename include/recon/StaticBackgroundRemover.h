#include "AbstractPointProcessor.h"
#include <pcl/segmentation/segment_differences.h>

namespace recon
{
	class StaticBackgroundRemover 
		: public AbstractPointProcessor 
	{
	public:
		EIGEN_MAKE_ALIGNED_OPERATOR_NEW;
		StaticBackgroundRemover();
		~StaticBackgroundRemover() override;

		void processData() override;
		void setBackGroundCloud(CloudConstPtr backGroundCloud);
	private:
		CloudConstPtr backGroundCloud_;
		pcl::SegmentDifferences<PointType> sd_;

	}; 
}
