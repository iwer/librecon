#include "recon/Frame.h"


namespace recon
{
	int Frame::count = 0;
	int Frame::instances = 0;

	Frame::Frame(void)
	{
		new Frame(1);
	}

	Frame::Frame(int sensorCount)
		: sensorCount_(sensorCount)
		, inputClouds_(std::vector<CloudConstPtr>(sensorCount_))
		, inputImages_(std::vector<ImagePtr>(sensorCount_))
		, inputExtrinsics_(std::vector<CameraExtrinsics::Ptr>(sensorCount_))
		, inputIntrinsics_(std::vector<CameraIntrinsics::Ptr>(sensorCount_))
		, outputClouds_(std::vector<CloudPtr>(sensorCount_))
		, outputTriangles_(std::vector<TrianglesPtr>(sensorCount_))
	{
		frameNumber = count;
		count++;
		instances++;
		//std::cout << "New Frame (" << frameNumber << ") instances: " << instances << std::endl;
	}


	Frame::~Frame(void)
	{
		instances--;
	}

	void Frame::setInputCloud(CloudConstPtr c, int index)
	{
		if(index >= 0 && index < sensorCount_)
		{
			inputClouds_[index] = c;
		} 
		else
		{
			std::cerr << "[Frame   ]: Set cloud: " << index << " is out of bounds" << std::endl;
		}
	}

	void Frame::setInputImage(ImagePtr i, int index)
	{
		if(index >= 0 && index < sensorCount_)
		{
			inputImages_[index] = i;
		}
		else
		{
			std::cerr << "[Frame   ]: Set image: " << index << " is out of bounds" << std::endl;
		}
	}

	void Frame::setInputExtrinsics(CameraExtrinsics::Ptr e, int index)
	{
		if(index >= 0 && index < sensorCount_)
		{
			inputExtrinsics_[index] = e;
		}
	}

	void Frame::setInputIntrinsics(CameraIntrinsics::Ptr i, int index)
	{
		if(index >= 0 && index < sensorCount_)
		{
			inputIntrinsics_[index] = i;
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

	CloudConstPtr Frame::getInputCloud(int index)
	{
		return inputClouds_[index];
	}

	ImagePtr Frame::getInputImage(int index)
	{
		return inputImages_[index];
	}

	CameraExtrinsics::Ptr Frame::getInputExtrinsics(int index)
	{
		return inputExtrinsics_[index];
	}

	CameraIntrinsics::Ptr Frame::getInputIntrinsics(int index)
	{
		return inputIntrinsics_[index];
	}

	CloudPtr Frame::getOutputCloud(int index)
	{
		return outputClouds_[index];
	}

	TrianglesPtr Frame::getOutputTriangles(int index)
	{
		return outputTriangles_[index];
	}

	int Frame::sensorCount() const
	{
		return sensorCount_;
	}

	int Frame::getFrameNumber() const
	{
		return frameNumber;
	}
}