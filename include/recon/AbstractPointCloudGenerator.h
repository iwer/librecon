#pragma once

#include "typedefs.h"
#include <boost/thread.hpp>

namespace recon
{
	class AbstractPointCloudGenerator {
	public:
		typedef boost::shared_ptr<AbstractPointCloudGenerator> Ptr; 

		EIGEN_MAKE_ALIGNED_OPERATOR_NEW;
		AbstractPointCloudGenerator(void);
		virtual ~AbstractPointCloudGenerator(void);


		virtual void aquireFrame() = 0;
		CloudConstPtr getOutputCloud();
		ImagePtr getOutputImage();
		virtual void start() = 0;
		virtual void stop() = 0;


	protected:
		boost::mutex cloud_mutex_;
		boost::mutex image_mutex_;
		/**
		* Cloud for the generator to write into. Access has to be secured via cloud_mutex_.
		*/
		CloudConstPtr cloud_;
		ImagePtr image_;

	};
}

