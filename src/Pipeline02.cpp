#include "recon/Pipeline02.h"
#include <pcl/common/transforms.h>

namespace recon
{

	Pipeline02::Pipeline02(int inputCloudCount,
		boost::signals2::signal<void (float)> * minDepUpdate, 
		boost::signals2::signal<void (float)> * maxDepUpdate, 
		boost::signals2::signal<void (float)> * triangleSizeUpdate,
		boost::signals2::signal<void (int)> * normalKNeighbourUpdate,
		boost::signals2::signal<void (float)> * muUpdate,
		boost::signals2::signal<void (int)> * maxNearestNeighboursUpdate,
		boost::signals2::signal<void (float)> * updateSampleResolution)
		: AbstractProcessingPipeline(inputCloudCount)
	{


		pp_ = &d_;
		mp_ = &g_;

		minDepUpdate->connect(boost::bind(&DepthThreshold::setDepthThresholdMin, &d_, _1));
		maxDepUpdate->connect(boost::bind(&DepthThreshold::setDepthThresholdMax, &d_, _1));
		triangleSizeUpdate->connect(boost::bind(&GreedyProjectionMeshProcessor::setMaxEdgeLength, &g_, _1));
		normalKNeighbourUpdate->connect(boost::bind(&GreedyProjectionMeshProcessor::setNormalKNeighbours, &g_, _1));
		muUpdate->connect(boost::bind(&GreedyProjectionMeshProcessor::setMu, &g_, _1));
		maxNearestNeighboursUpdate->connect(boost::bind(&GreedyProjectionMeshProcessor::setMaxNearestNeighbours, &g_, _1));
		updateSampleResolution->connect(boost::bind(&PointCloudSampler::setResolution, &s_, _1));
	}


	Pipeline02::~Pipeline02(void)
	{

	}

	void Pipeline02::processData()
	{

		Cloud combinedCloud;

		// Single input cloud processing
		for (auto &s : sensors_)
		{
			auto tmpCloud = s->getCloudSource()->getOutputCloud();
			if(tmpCloud && tmpCloud->size() > 0){
				// Depth threshold
				d_.setInputCloud(tmpCloud);
				d_.processData();

				// Remove Background
				//bgr_.setInputCloud(tmpCloud);
				//bgr_.setBackGroundCloud(s->getBackground());
				//bgr_.processData();

				auto t = d_.getOutputCloud();
				combinedCloud += *t;

				/*// Transform using extrinsics
				CloudPtr cloudT(new Cloud);
				Eigen::Affine3f transformation = Eigen::Affine3f::Identity();
				Eigen::Vector4f transl = s->getDepthExtrinsics()->getTranslation();
				transformation.translation() << transl.x() , transl.y(), transl.z();
				transformation.rotate(s->getDepthExtrinsics()->getRotation());
				pcl::transformPointCloud(*d_.getOutputCloud(), *cloudT, transformation);


				// Merge into combined cloud
				combinedCloud += *cloudT;
				*/
			}
		}

		// Combined cloud processing
		if (combinedCloud.size() > 0)	{
			// Downsample
			s_.setInputCloud(boost::make_shared<Cloud>(combinedCloud));
			s_.processData();

			mp_->setInputCloud(s_.getOutputCloud());
			//mp_->processData();
			meshCloud_ = mp_->getInputCloud();
			triangles_ = mp_->getTriangles();
		} 

	}
}