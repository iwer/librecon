#pragma once
#include "recon/typedefs.h"
#include "recon/CameraIntrinsics.h"
#include "recon/CameraExtrinsics.h"
#include "recon/AbstractPointCloudGenerator.h"
#include <pcl/io/pcd_io.h>
#include <boost/make_shared.hpp>

namespace recon
{
	class AbstractSensor
	{
	public:
		typedef boost::shared_ptr<AbstractSensor> Ptr;

		EIGEN_MAKE_ALIGNED_OPERATOR_NEW;
		AbstractSensor(void);
		AbstractSensor(int id);
		virtual ~AbstractSensor(void);

		CloudConstPtr getBackground() const;
		void setBackground(void);
		CameraIntrinsics::Ptr getDepthIntrinsics() const;
		void setDepthIntrinsics(const CameraIntrinsics::Ptr depthIntrinsics);
		CameraExtrinsics::Ptr getDepthExtrinsics() const;
		void setDepthExtrinsics(const CameraExtrinsics::Ptr depthExtrinsics);
		CameraIntrinsics::Ptr getRgbIntrinsics() const;
		void setRgbIntrinsics(const CameraIntrinsics::Ptr rgbIntrinsics);
		CameraExtrinsics::Ptr getRgbExtrinsics() const;
		void setRgbExtrinsics(const CameraExtrinsics::Ptr rgbExtrinsics);

		int getId() const;
		AbstractPointCloudGenerator* getCloudSource() const;

	protected:
		virtual void setBackGroundImpl(void) = 0;


		int sensorId_;
		CloudConstPtr background_;
		CameraIntrinsics::Ptr depthIntrinsics_;
		CameraExtrinsics::Ptr depthExtrinsics_;
		CameraIntrinsics::Ptr rgbIntrinsics_;
		CameraExtrinsics::Ptr rgbExtrinsics_;

		AbstractPointCloudGenerator* cloudSource_;
	};

}
