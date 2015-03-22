#pragma once

#include "typedefs.h"
#include <boost/thread.hpp>

class AbstractPointCloudGenerator {
public:
	AbstractPointCloudGenerator(void);
	~AbstractPointCloudGenerator(void);

	virtual void aquireFrame() = 0;
	CloudConstPtr getOutputCloud();

	virtual void start() = 0;
	virtual void stop() = 0;


protected:
	boost::mutex cloud_mutex_;
	/**
	 * Cloud for the generator to write into. Access has to be secured via cloud_mutex_.
	 */
	CloudConstPtr cloud_;
private:

};

