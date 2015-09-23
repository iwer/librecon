#include "recon/CameraExtrinsics.h"


namespace recon
{
	CameraExtrinsics::CameraExtrinsics(void)
		: translation_(Eigen::Vector4f(0,0,0,1))
		, rotation_(Eigen::Quaternionf::Identity())
	{
	}

	CameraExtrinsics::CameraExtrinsics(Eigen::Vector4f &translation, Eigen::Quaternionf &rotation)
		: translation_(translation)
		, rotation_(rotation)
	{
	}

	CameraExtrinsics::~CameraExtrinsics(void)
	{
	}

	Eigen::Vector4f * CameraExtrinsics::getTranslation()
	{
		return &translation_;
	}

	Eigen::Quaternionf * CameraExtrinsics::getRotation()
	{
		return &rotation_;
	}

		Eigen::Affine3f CameraExtrinsics::getTransformation()
	{
		auto transform = Eigen::Affine3f::Identity();
		transform.translation() << translation_.x(), translation_.y(), translation_.z();
		transform.rotate(rotation_);
		return transform;
	}

	std::ostream& operator<<(std::ostream& os, const CameraExtrinsics& obj)
	{
		return os
			<< "translation_: " << std::endl << obj.translation_ << std::endl
			<< " rotation_: " << std::endl << obj.rotation_.matrix();
	}
}
