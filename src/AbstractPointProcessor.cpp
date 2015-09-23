#include "recon/AbstractPointProcessor.h"
#include <boost/smart_ptr/make_shared.hpp>


namespace recon
{
	AbstractPointProcessor::AbstractPointProcessor(void) :
		inputCloud_(new Cloud),
		outputCloud_()
	{
	}


	AbstractPointProcessor::~AbstractPointProcessor(void)
	{
	}

	void AbstractPointProcessor::setInputCloud(CloudConstPtr cloud)
	{
		inputCloud_.swap(cloud);
	}

	CloudPtr AbstractPointProcessor::getOutputCloud()
	{
		return outputCloud_.makeShared();//boost::make_shared<Cloud>(outputCloud_);
	} 
}
