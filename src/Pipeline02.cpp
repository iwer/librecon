#include "recon/Pipeline02.h"
#include <pcl/common/transforms.h>
#include <pcl/common/time.h>

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
		pcl::ScopeTime t1("Processing");

		auto combinedCloud = Cloud();

		// Single input cloud processing
		for (auto &s : sensors_)
		{
			auto tmpCloud = s->getCloudSource()->getOutputCloud();
			if(tmpCloud && tmpCloud->size() > 0){

				// Depth threshold
				//d_.setInputCloud(tmpCloud);
				//d_.processData();
				//auto s1 = d_.getOutputCloud();

				// Remove Background
				//bgr_.setInputCloud(tmpCloud);
				//bgr_.setBackGroundCloud(s->getBackground());
				//bgr_.processData();
				//auto s2 = bgr_.getOutputCloud();
				
				// Normal calculation?

				// Transform using extrinsics
				CloudPtr cloudTransformed(new Cloud);
				auto transformation = Eigen::Affine3f::Identity();
				auto translation = s->getDepthExtrinsics()->getTranslation();
				transformation.translation() << translation->x() , translation->y(), translation->z();
				auto rotation = s->getDepthExtrinsics()->getRotation();
				// Flip to match global coordinate frame
				Eigen::AngleAxisf aa(*rotation);
				auto vec = aa.axis();
				aa.angle();
				vec.x() = -vec.x();
				vec.y() = vec.y();
				vec.z() = -vec.z();
				aa.axis() = vec;
				transformation.rotate(aa);
				pcl::transformPointCloud(*tmpCloud, *cloudTransformed, transformation);


				// Merge into combined cloud
				combinedCloud += *cloudTransformed;
			}
		}

		// Combined cloud processing
		if (combinedCloud.size() > 0)	{
			// Downsample
			//s_.setInputCloud(boost::make_shared<Cloud>(combinedCloud));
			//s_.processData();

			auto c1 = s_.getOutputCloud();

			// MLS Smoothing
			// Greedy Projection
			if(c1->size() > 0) {
				//mp_->setInputCloud(s_.getOutputCloud());
				//mp_->processData();
			}
			meshCloud_ = boost::make_shared<Cloud>(combinedCloud);
			triangles_ = mp_->getTriangles();
		}  else
		{
			std::cerr << "Combined Cloud contains no points..." << std::endl;
		}

	}

	void Pipeline02::processData(Frame::Ptr frame)
	{
	}
}