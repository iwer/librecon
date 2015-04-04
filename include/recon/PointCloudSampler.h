#include "AbstractPointProcessor.h"
#include <pcl/filters/voxel_grid.h>

namespace recon
{
	class PointCloudSampler 
		: public AbstractPointProcessor 
	{
	public:
		PointCloudSampler();
		~PointCloudSampler();

		void processData() override;
		float getResolution() const;

		void setResolution(float resolution);

	private:
		pcl::VoxelGrid<PointType> vg_;
		float resolution_;
	}; 
}
