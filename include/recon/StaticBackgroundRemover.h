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
		virtual ~StaticBackgroundRemover();

		void processData() override;
		void setBackGroundCloud(CloudConstPtr &backGroundCloud);
	private:
		CloudConstPtr backGroundCloud_;
		pcl::SegmentDifferences<PointType> sd_;
		pcl::search::KdTree<PointType>::Ptr tree_;

	}; 
}
