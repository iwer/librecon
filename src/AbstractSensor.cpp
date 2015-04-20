#include "recon/AbstractSensor.h"


namespace recon
{
	AbstractSensor::AbstractSensor(void)
		: depthIntrinsics_()
		, depthExtrinsics_()
		, rgbIntrinsics_()
		, rgbExtrinsics_()
	{
	}


	AbstractSensor::~AbstractSensor(void)
	{
	}

	CloudConstPtr AbstractSensor::getBackground() const
	{
		return background_;
	}

	void AbstractSensor::setBackground()
	{
		setBackGroundImpl();
	}

	CameraIntrinsics::Ptr AbstractSensor::getDepthIntrinsics() const
	{
		return depthIntrinsics_;
	}

	void AbstractSensor::setDepthIntrinsics(const CameraIntrinsics::Ptr& depthIntrinsics)
	{
		depthIntrinsics_ = depthIntrinsics;
	}

	CameraExtrinsics::Ptr AbstractSensor::getDepthExtrinsics() const
	{
		return depthExtrinsics_;
	}

	void AbstractSensor::setDepthExtrinsics(const CameraExtrinsics::Ptr& depthExtrinsics)
	{
		depthExtrinsics_ = depthExtrinsics;
	}

	CameraIntrinsics::Ptr AbstractSensor::getRgbIntrinsics() const
	{
		return rgbIntrinsics_;
	}

	void AbstractSensor::setRgbIntrinsics(const CameraIntrinsics::Ptr& rgbIntrinsics)
	{
		rgbIntrinsics_ = rgbIntrinsics;
	}

	CameraExtrinsics::Ptr AbstractSensor::getRgbExtrinsics() const
	{
		return rgbExtrinsics_;
	}

	void AbstractSensor::setRgbExtrinsics(const CameraExtrinsics::Ptr& rgbExtrinsics)
	{
		rgbExtrinsics_ = rgbExtrinsics;
	}

	AbstractPointCloudGenerator* AbstractSensor::getCloudSource() const
	{
		return cloudSource_;
	}
}
