#pragma once
#include <Eigen/StdVector>
#include <Eigen/Geometry>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <ostream>

namespace recon
{
	class CameraExtrinsics
	{
	public:
		typedef boost::shared_ptr<CameraExtrinsics> Ptr;
		
		EIGEN_MAKE_ALIGNED_OPERATOR_NEW;
		CameraExtrinsics(void);
		CameraExtrinsics(Eigen::Vector4f &translation, Eigen::Quaternionf &rotation);
		~CameraExtrinsics(void);

		Eigen::Vector4f * getTranslation();
		Eigen::Quaternionf * getRotation();
		Eigen::Affine3f  getTransformation();


		friend std::ostream& operator<<(std::ostream& os, const CameraExtrinsics& obj);

	private:
		Eigen::Vector4f translation_;
		Eigen::Quaternionf rotation_;
	}; 
}

