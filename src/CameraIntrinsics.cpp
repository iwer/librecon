#include <recon/CameraIntrinsics.h>
#include <iostream>

#define M_PI 3.14159265359

recon::CameraIntrinsics::CameraIntrinsics()
{
}

void recon::CameraIntrinsics::updateFov()
{
	hFov_ = 180 / M_PI * 2 * std::atan(static_cast<float>(sensorWidth_) * .5 / focalLengthX_);
	vFov_ = 180 / M_PI * 2 * std::atan(static_cast<float>(sensorHeight_) * .5 / focalLengthY_);
}

recon::CameraIntrinsics::CameraIntrinsics(float focalLength, int sensorWidth, int sensorHeight)
	: focalLengthX_(focalLength)
	, focalLengthY_(focalLength)
	, sensorWidth_(sensorWidth)
	, sensorHeight_(sensorHeight)
	, principalPointX_(.5f*sensorWidth)
	, principalPointY_(.5f*sensorHeight)
{
	updateFov();
}

recon::CameraIntrinsics::CameraIntrinsics(float focalLengthX, float focalLengthY, float principalPointX, float principalPointY, int sensorWidth, int sensorHeight)
	: focalLengthX_(focalLengthX)
	, focalLengthY_(focalLengthY)
	, sensorWidth_(sensorWidth)
	, sensorHeight_(sensorHeight)
	, principalPointX_(principalPointX)
	, principalPointY_(principalPointY)
{
	updateFov();
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

double recon::CameraIntrinsics::getAspectRatio()
{
	return static_cast<double>(sensorWidth_) / static_cast<double>(sensorHeight_);
}

void recon::CameraIntrinsics::setFocalLength(float f)
{
	focalLengthX_ = f;
	focalLengthY_ = f;
	updateFov();
}

std::ostream& recon::operator<<(std::ostream& os, const CameraIntrinsics& obj)
{
	return os
		<< "focalLengthX_: " << obj.focalLengthX_
		<< " focalLengthY_: " << obj.focalLengthY_
		<< " sensorWidth_: " << obj.sensorWidth_
		<< " sensorHeight_: " << obj.sensorHeight_
		<< " principalPointX_: " << obj.principalPointX_
		<< " principalPointY_: " << obj.principalPointY_
		<< " hFov_: " << obj.hFov_
		<< " vFov_: " << obj.vFov_
		<< " getAspectRatio(): " << static_cast<double>(obj.sensorWidth_) / static_cast<double>(obj.sensorHeight_);
}
