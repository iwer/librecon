#include "recon/Pipeline02.h"


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


	pp_ = &d;
	mp_ = &g;

	minDepUpdate->connect(boost::bind(&DepthThreshold::setDepthThresholdMin, &d, _1));
	maxDepUpdate->connect(boost::bind(&DepthThreshold::setDepthThresholdMax, &d, _1));
	triangleSizeUpdate->connect(boost::bind(&GreedyProjectionMeshProcessor::setMaxEdgeLength, &g, _1));
	normalKNeighbourUpdate->connect(boost::bind(&GreedyProjectionMeshProcessor::setNormalKNeighbours, &g, _1));
	muUpdate->connect(boost::bind(&GreedyProjectionMeshProcessor::setMu, &g, _1));
	maxNearestNeighboursUpdate->connect(boost::bind(&GreedyProjectionMeshProcessor::setMaxNearestNeighbours, &g, _1));
	updateSampleResolution->connect(boost::bind(&PointCloudSampler::setResolution, &s, _1));
}


Pipeline02::~Pipeline02(void)
{
}

void Pipeline02::processData()
{

	Cloud combinedCloud;

	for (auto &c : clouds_)
	{
		s.setInputCloud(c);
		s.processData();
		combinedCloud += *s.getOutputCloud();
		//combinedCloud += *c;
		std::cout << "Combined cloud size: " << combinedCloud.size() << std::endl;
	}



	mp_->setInputCloud(boost::make_shared<Cloud>(combinedCloud));
	mp_->processData();
	meshCloud_ = mp_->getInputCloud();
	triangles_ = mp_->getTriangles();
	//meshCloud_ =  boost::make_shared<Cloud>(combinedCloud);
}