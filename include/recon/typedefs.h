#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/Vertices.h>


namespace recon
{
	typedef pcl::PointXYZRGB PointType;
	typedef pcl::PointXYZRGBNormal PointNormalType;
	typedef pcl::PointCloud<PointType> Cloud;
	typedef Cloud::ConstPtr CloudConstPtr;
	typedef Cloud::Ptr CloudPtr;

	typedef boost::shared_ptr<std::vector<pcl::Vertices> > TrianglesPtr;

}