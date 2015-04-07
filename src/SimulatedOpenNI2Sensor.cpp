#include "recon/SimulatedOpenNI2Sensor.h"


namespace recon
{

	SimulatedOpenNI2Sensor::SimulatedOpenNI2Sensor(std::string fileName, std::string backgroundFileName)
		: AbstractSensor()
		, grabber_(new FilePointCloudGenerator(fileName))
		, fileName_(fileName)
		, backgroundFileName_(backgroundFileName)
	{
		cloudSource_ = grabber_;
		grabber_->start();
		depthExtrinsics_ = grabber_->getExtrinsics();
		std::cout << "Created new Simulated OpenNI2 Sensor" << std::endl;
		std::cout << "Extrinsic translation: " << std::endl << depthExtrinsics_->getTranslation() << std::endl;
		std::cout << "Extrinsic rotation   : "<< std::endl <<  depthExtrinsics_->getRotation().toRotationMatrix() << std::endl;
	}


	SimulatedOpenNI2Sensor::~SimulatedOpenNI2Sensor(void)
	{
	}

	void SimulatedOpenNI2Sensor::setBackGroundImpl()
	{
		pcl::PCDReader reader;
		Cloud cloud;
		auto err = reader.read(backgroundFileName_, cloud);
		if(!err){
			background_= boost::make_shared<Cloud>(cloud);
		} else
		{
			background_ = CloudConstPtr(new Cloud);
		}
	}
}