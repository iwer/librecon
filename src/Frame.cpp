#include "recon/Frame.h"


namespace recon
{
	Frame::Frame(void)
	{
		new Frame(1);
	}

	Frame::Frame(int sensorCount)
		: sensorCount_(sensorCount)
		, inputClouds_(std::vector<CloudPtr>(sensorCount_))
		, inputImages_(std::vector<ImagePtr>(sensorCount_))
		, outputClouds_(std::vector<CloudPtr>(sensorCount_))
		, outputTriangles_(std::vector<TrianglesPtr>(sensorCount_))
	{
	}


	Frame::~Frame(void)
	{
	}

	void Frame::setInputCloud(CloudPtr c, int index)
	{
		if(index >= 0 && index < sensorCount_)
		{
			inputClouds_[index] = c;
		}
	}

	void Frame::setInputImage(ImagePtr i, int index)
	{
		if(index >= 0 && index < sensorCount_)
		{
			inputImages_[index] = i;
		}
	}

	void Frame::setOutputCloud(CloudPtr c, int index)
	{
		if(index >= 0 && index < sensorCount_)
		{
			outputClouds_[index] = c;
		}
	}

	void Frame::setOutputTriangles(TrianglesPtr t, int index)
	{
		if(index >= 0 && index < sensorCount_)
		{
			outputTriangles_[index] = t;
		}
	}

	CloudPtr Frame::getInputCloud(int index)
	{
		return inputClouds_[index];
	}

	ImagePtr Frame::getInputImage(int index)
	{
		return inputImages_[index];
	}

	CloudPtr Frame::getOutputCloud(int index)
	{
		return outputClouds_[index];
	}

	TrianglesPtr Frame::getOutputTriangles(int index)
	{
		return outputTriangles_[index];
	}
}