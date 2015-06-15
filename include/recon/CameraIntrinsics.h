#pragma once
#include <vector>
#include <boost/smart_ptr/shared_ptr.hpp>

namespace recon
{
	class CameraIntrinsics
	{
	public:
		typedef boost::shared_ptr<CameraIntrinsics> Ptr;

//		EIGEN_MAKE_ALIGNED_OPERATOR_NEW;
		CameraIntrinsics();
		CameraIntrinsics(float focalLength, int sensorWidth, int sensorHeight);
		CameraIntrinsics(float focalLengthX, float focalLengthY, float principalPointX, float principalPointY, int sensorWidth, int sensorHeight);

		float getFocalLengthX() const;
		float getFocalLengthY() const;
		int getSensorWidth() const;
		int getSensorHeight() const;
		float getPrincipalPointX() const;
		float getPrincipalPointY() const;
		float getHFov() const;
		float getVFov() const;

	private:
		float focalLengthX_;
		float focalLengthY_;

		int sensorWidth_;
		int sensorHeight_;

		float principalPointX_;
		float principalPointY_;

		float hFov_;
		float vFov_;
	};

}
