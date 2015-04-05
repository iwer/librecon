#pragma once
#include <Eigen/StdVector>
#include <Eigen/Geometry>

namespace recon
{
	class CameraExtrinsics
	{
	public:
		CameraExtrinsics(void);
		~CameraExtrinsics(void);

		Eigen::Vector3f getTranslation();
		Eigen::Quaternionf getRotation();
		Eigen::Affine3f getTransformation();

	private:
		Eigen::Vector3f translation_;
		Eigen::Quaternionf rotation_;
	}; 
}

