#include "AbstractPointProcessor.h"

namespace recon
{
	class PointCloudSmoother : AbstractPointProcessor {


	public:
		EIGEN_MAKE_ALIGNED_OPERATOR_NEW;
		void processData() override;
	};

}