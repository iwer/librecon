#include <pcl/point_cloud.h>
#include <pcl/point_types.h>
#include <pcl/Vertices.h>
#include <pcl/io/image.h>


namespace recon
{
	typedef pcl::PointXYZRGB PointType;
	typedef pcl::PointXYZRGBNormal PointNormalType;
	typedef pcl::PointCloud<PointType> Cloud;
	typedef Cloud::ConstPtr CloudConstPtr;
	typedef Cloud::Ptr CloudPtr;

	typedef boost::shared_ptr<std::vector<pcl::Vertices> > TrianglesPtr;
	typedef boost::shared_ptr<pcl::io::Image> ImagePtr;

}