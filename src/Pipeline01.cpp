#include "recon/Pipeline01.h"
#include <pcl/common/transforms.h>
#include <recon/Frame.h>

namespace recon
{


	Pipeline01::Pipeline01(boost::signals2::signal<void (float)> * minDepUpdate, 
		boost::signals2::signal<void (float)> * maxDepUpdate, 
		boost::signals2::signal<void (float)> * triangleSizeUpdate)
		: AbstractProcessingPipeline(1)
	{


		pp_ = &d_;
		mp_ = &m_;

		minDepUpdate->connect(boost::bind(&DepthThreshold::setDepthThresholdMin, &d_, _1));
		maxDepUpdate->connect(boost::bind(&DepthThreshold::setDepthThresholdMax, &d_, _1));
		triangleSizeUpdate->connect(boost::bind(&Pipeline01::updateTriangleSize, this, _1));
	}


	Pipeline01::~Pipeline01(void)
	{
	}

	void Pipeline01::updateTriangleSize(float size)
	{
		m_.setEdgeLength(int(size));
	}

	void Pipeline01::processData()
	{
		for(auto &s : sensors_) 
		{
			auto tmpCloud = s->getCloudSource()->getOutputCloud();
			if(tmpCloud && tmpCloud->size() > 0){
				pp_->setInputCloud(tmpCloud);
				pp_->processData();

				mp_->setInputCloud(pp_->getOutputCloud());
				mp_->processData();


				// Transform using extrinsics
				CloudPtr cloudTransformed(new Cloud);
				auto transformation = Eigen::Affine3f::Identity();
				auto translation = s->getDepthExtrinsics()->getTranslation();
				transformation.translation() << -translation->x() , translation->y(), -translation->z();

				auto rotation = s->getDepthExtrinsics()->getRotation();

				// Flip to match global coordinate frame
				Eigen::AngleAxisf aa(*rotation);
				auto axis = aa.axis();
				aa.angle();
				axis.x() = -axis.x();
				axis.y() = axis.y();
				axis.z() = -axis.z();
				aa.axis() = axis;

				transformation.rotate(aa);
				pcl::transformPointCloud(*mp_->getInputCloud(), *cloudTransformed, transformation);

				meshCloud_ = cloudTransformed;
				triangles_ = mp_->getTriangles();
			}		
		}
	}

	void Pipeline01::processData(Frame::Ptr frame)
	{
		for(int i = 0; i < frame->sensorCount(); i++)
		{
			auto tmpCloud = frame->getInputCloud(i);
			if(tmpCloud && tmpCloud->size() > 0){
				pp_->setInputCloud(tmpCloud);
				pp_->processData();

				mp_->setInputCloud(pp_->getOutputCloud());
				mp_->processData();


				// Transform using extrinsics
				CloudPtr cloudTransformed(new Cloud);
				auto transformation = Eigen::Affine3f::Identity();
				auto translation = frame->getInputExtrinsics(i)->getTranslation();
				transformation.translation() << -translation->x() , translation->y(), -translation->z();

				auto rotation = frame->getInputExtrinsics(i)->getRotation();

				// Flip to match global coordinate frame
				Eigen::AngleAxisf aa(*rotation);
				auto axis = aa.axis();
				aa.angle();
				axis.x() = -axis.x();
				axis.y() = axis.y();
				axis.z() = -axis.z();
				aa.axis() = axis;

				transformation.rotate(aa);
				pcl::transformPointCloud(*mp_->getInputCloud(), *cloudTransformed, transformation);

				meshCloud_ = cloudTransformed;
				triangles_ = mp_->getTriangles();

				frame->setOutputCloud(cloudTransformed, i);
				frame->setOutputTriangles(triangles_, i);
			}
		}
	}
}
