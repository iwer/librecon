#pragma once
#include "recon/typedefs.h"
#include "recon/CameraIntrinsics.h"
#include "recon/CameraExtrinsics.h"
#include "recon/AbstractPointCloudGenerator.h"

namespace recon
{
	class AbstractSensor
	{
	public:
		typedef boost::shared_ptr<AbstractSensor> Ptr;

		AbstractSensor(void);
		~AbstractSensor(void);

	protected:
		CloudConstPtr background_;
		CameraIntrinsics::Ptr intrinsics_;
		CameraExtrinsics::Ptr extrinsics_;
		//CameraIntrinsics::Ptr rgbIntrinsics_;
		//CameraExtrinsics::Ptr rgbExtrinsics_;

		AbstractPointCloudGenerator * cloudSource_;
	};

}
