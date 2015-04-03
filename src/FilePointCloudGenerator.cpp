#include <recon/FilePointCloudGenerator.h>
#include <pcl/io/pcd_io.h>
#include <pcl/common/transforms.h>

FilePointCloudGenerator::FilePointCloudGenerator(std::string filename)
	: AbstractPointCloudGenerator()
	, filename_(filename)
{
}

FilePointCloudGenerator::~FilePointCloudGenerator()
{
}

void FilePointCloudGenerator::aquireFrame()
{
}

void FilePointCloudGenerator::start()
{
	reloadFile();
}

void FilePointCloudGenerator::stop()
{
}

void FilePointCloudGenerator::reloadFile()
{
	pcl::PCDReader reader;
	Cloud cloud;
	CloudPtr cloudT(new Cloud);
	reader.read(filename_, cloud);
	
	Eigen::Affine3f transform = Eigen::Affine3f::Identity();
	//transform.rotate (Eigen::AngleAxisf (M_PI, Eigen::Vector3f::UnitZ()));
	transform.translation() << cloud.sensor_origin_.x(),cloud.sensor_origin_.y(),cloud.sensor_origin_.z();
	transform.rotate(cloud.sensor_orientation_.toRotationMatrix());
	pcl::transformPointCloud(cloud, *cloudT, transform);
		
	
	{
		boost::mutex::scoped_lock(cloud_mutex_);
		cloud_ = cloudT;		
	}
	std::cout << "Loaded " << cloud_->size() << " points from '" << filename_ << "'" << std::endl;
	std::cout << "Sensor origin: " << cloud_->sensor_origin_ << std::endl;
}