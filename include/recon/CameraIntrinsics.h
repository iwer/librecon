#include <vector>
//#include <Eigen/src/Core/Matrix.h>

namespace recon
{
	class CameraIntrinsics
	{
	public:
		CameraIntrinsics();
		CameraIntrinsics(float focalLength, int sensorWidth, float sensorHeight);

	private:
		float focalLength_;

		int sensorWidth_;
		int sensorHeight_;

		std::vector<int> principalPoint_;

		int imageWidth_;
		int imageHeight_;

		//Eigen::Matrix4f intrinsicMatrix_;

		float hFov_;
		float vFov_;
	};

}
