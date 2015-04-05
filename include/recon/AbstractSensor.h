#pragma once
#include "recon/typedefs.h"
#include "recon/CameraIntrinsics.h"
#include "recon/CameraExtrinsics.h"

namespace recon
{
	class AbstractSensor
	{
	public:
		AbstractSensor(void);
		~AbstractSensor(void);
	private:
		CloudConstPtr background_;
		CameraIntrinsics intrinsics_;
		CameraExtrinsics extrinsics_;
	};

}
