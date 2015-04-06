#include <recon/FilePointCloudGenerator.h>
#include <pcl/io/pcd_io.h>
#include <pcl/common/transforms.h>
#include <boost/make_shared.hpp>

namespace recon
{
	FilePointCloudGenerator::FilePointCloudGenerator(std::string filename)
		: AbstractPointCloudGenerator()
		, filename_(filename)
		, extrinsics_(new CameraExtrinsics)
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

	CameraExtrinsics::Ptr FilePointCloudGenerator::getExtrinsics() const
	{
		return extrinsics_;
	}

	void FilePointCloudGenerator::reloadFile()
	{
		pcl::PCDReader reader;
		Cloud cloud;
		CloudPtr cloudT(new Cloud);
		auto err = reader.read(filename_, cloud);
		if(!err){
			//auto transform = Eigen::Affine3f::Identity();
			////transform.rotate (Eigen::AngleAxisf (M_PI, Eigen::Vector3f::UnitZ()));
			//transform.translation() << cloud.sensor_origin_.x(),cloud.sensor_origin_.y(),cloud.sensor_origin_.z();
			//transform.rotate(cloud.sensor_orientation_.toRotationMatrix());
			//pcl::transformPointCloud(cloud, *cloudT, transform);

			extrinsics_ = boost::make_shared<CameraExtrinsics>(CameraExtrinsics(cloud.sensor_origin_, cloud.sensor_orientation_));



			{
				boost::mutex::scoped_lock(cloud_mutex_);
				cloud_ = cloudT;		
			}
			std::cout << "Loaded " << cloud_->size() << " points from '" << filename_ << "'" << std::endl;
		}
	}
}