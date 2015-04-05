#pragma once
#include <Eigen/StdVector>
#include <Eigen/Geometry>
#include <boost/smart_ptr/shared_ptr.hpp>

namespace recon
{
	class CameraExtrinsics
	{
	public:
		typedef boost::shared_ptr<CameraExtrinsics> Ptr;
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

