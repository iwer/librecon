#pragma once

#include "typedefs.h"
#include "CameraIntrinsics.h"
#include "CameraExtrinsics.h"

namespace recon
{
	class Frame
	{
	public:
		typedef boost::shared_ptr<Frame> Ptr;

		Frame(void);
		explicit Frame(int sensorCount);
		~Frame(void);

		void setInputCloud(CloudConstPtr c, int index);
		void setInputImage(ImagePtr i, int index);

		void setInputExtrinsics(CameraExtrinsics::Ptr e, int index);

		void setInputIntrinsics(CameraIntrinsics::Ptr i, int index);
		void setOutputCloud(CloudPtr c, int index);
		void setOutputTriangles(TrianglesPtr t, int index);

		CloudConstPtr getInputCloud(int index);
		ImagePtr getInputImage(int index);
		CameraExtrinsics::Ptr getInputExtrinsics(int index);
		CameraIntrinsics::Ptr getInputIntrinsics(int index);
		CloudPtr getOutputCloud(int index);
		TrianglesPtr getOutputTriangles(int index);

		int sensorCount() const;
		int getFrameNumber() const;

	private:
		int sensorCount_;

		static int count;
		static int instances;
		int frameNumber;

		std::vector<CloudConstPtr> inputClouds_;
		std::vector<ImagePtr> inputImages_;
		std::vector<CameraExtrinsics::Ptr> inputExtrinsics_;
		std::vector<CameraIntrinsics::Ptr> inputIntrinsics_;

		std::vector<CloudPtr> outputClouds_;
		std::vector<TrianglesPtr> outputTriangles_;
	}; 
}

