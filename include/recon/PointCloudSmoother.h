#include "AbstractPointProcessor.h"

namespace recon
{
	class PointCloudSmoother : AbstractPointProcessor {


	public:
		void processData() override;
	};

}