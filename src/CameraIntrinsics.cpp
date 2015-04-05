#include <recon/CameraIntrinsics.h>
#include <iostream>

recon::CameraIntrinsics::CameraIntrinsics()
{
}

recon::CameraIntrinsics::CameraIntrinsics(float focalLength, int sensorWidth, int sensorHeight)
	: focalLengthX_(focalLength)
	, focalLengthY_(focalLength)
	, sensorWidth_(sensorWidth)
	, sensorHeight_(sensorHeight)
	, principalPointX_(.5)
	, principalPointY_(.5)
{
	hFov_ = std::atan(sensorWidth_ / 2 / focalLengthX_);
	vFov_ = std::atan(sensorHeight_ / 2 / focalLengthY_);
}

recon::CameraIntrinsics::CameraIntrinsics(float focalLengthX, float focalLengthY, float principalPointX, float principalPointY, int sensorWidth, int sensorHeight)
	: focalLengthX_(focalLengthX)
	, focalLengthY_(focalLengthY)
	, sensorWidth_(sensorWidth)
	, sensorHeight_(sensorHeight)
	, principalPointX_(principalPointX)
	, principalPointY_(principalPointY)
{
	std::cout << "New Intrinsics: " << focalLengthX << " " << focalLengthY << " " << principalPointX << " " << principalPointY << " " << sensorWidth << " " << sensorHeight << " " << std::endl;
	hFov_ = std::atan(sensorWidth_ / 2 / focalLengthX_);
	vFov_ = std::atan(sensorHeight_ / 2 / focalLengthY_);
}

float recon::CameraIntrinsics::getFocalLengthX() const
{
	return focalLengthX_;
}

float recon::CameraIntrinsics::getFocalLengthY() const
{
	return focalLengthY_;
}

int recon::CameraIntrinsics::getSensorWidth() const
{
	return sensorWidth_;
}

int recon::CameraIntrinsics::getSensorHeight() const
{
	return sensorHeight_;
}

float recon::CameraIntrinsics::getPrincipalPointX() const
{
	return principalPointX_;
}

float recon::CameraIntrinsics::getPrincipalPointY() const
{
	return principalPointY_;
}

float recon::CameraIntrinsics::getHFov() const
{
	return hFov_;
}

float recon::CameraIntrinsics::getVFov() const
{
	return vFov_;
}