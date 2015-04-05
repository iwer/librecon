#include "recon/CameraExtrinsics.h"


namespace recon
{
	CameraExtrinsics::CameraExtrinsics(void)
		: translation_(Eigen::Vector3f())
		, rotation_(Eigen::Quaternionf::Identity())
	{
	}


	CameraExtrinsics::~CameraExtrinsics(void)
	{
	}

	Eigen::Vector3f CameraExtrinsics::getTranslation()
	{
		return translation_;
	}

	Eigen::Quaternionf CameraExtrinsics::getRotation()
	{
		return rotation_;
	}

	Eigen::Affine3f CameraExtrinsics::getTransformation()
	{
		Eigen::Affine3f transform = Eigen::Affine3f::Identity();
		transform.translation() << translation_.x(), translation_.y(), translation_.z();
		transform.rotate(rotation_);
		return transform;
	}
}
