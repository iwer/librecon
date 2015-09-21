#pragma once

#include "typedefs.h"
namespace recon
{
	class Frame
	{
	public:
		typedef boost::shared_ptr<Frame> Ptr;

		Frame(void);
		explicit Frame(int sensorCount);
		~Frame(void);

		void setInputCloud(CloudPtr c, int index);
		void setInputImage(ImagePtr i, int index);
		void setOutputCloud(CloudPtr c, int index);
		void setOutputTriangles(TrianglesPtr t, int index);

		CloudPtr getInputCloud(int index);
		ImagePtr getInputImage(int index);
		CloudPtr getOutputCloud(int index);
		TrianglesPtr getOutputTriangles(int index);

	private:
		int sensorCount_;
		std::vector<CloudPtr> inputClouds_;
		std::vector<ImagePtr> inputImages_;
		std::vector<CloudPtr> outputClouds_;
		std::vector<TrianglesPtr> outputTriangles_;
	}; 
}

