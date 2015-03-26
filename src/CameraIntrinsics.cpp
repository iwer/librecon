#include <recon/CameraIntrinsics.h>
#include <valarray>

CameraIntrinsics::CameraIntrinsics(float focalLength, int sensorWidth, float sensorHeight)
	: focalLength_(focalLength)
	, sensorWidth_(sensorWidth)
	,sensorHeight_(sensorHeight)
{
	hFov_ = std::atan(sensorWidth_ / 2 / focalLength_);
	vFov_ = std::atan(sensorHeight_ / 2 / focalLength_);
}