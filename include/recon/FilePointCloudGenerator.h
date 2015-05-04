#include "recon/AbstractPointCloudGenerator.h"
#include "recon/CameraExtrinsics.h"

namespace recon
{
	class FilePointCloudGenerator : public AbstractPointCloudGenerator
	{
	public:
		//EIGEN_MAKE_ALIGNED_OPERATOR_NEW;
		FilePointCloudGenerator(std::string filename);
		~FilePointCloudGenerator();
		
		void aquireFrame() override;
		void start() override;
		void stop() override;

		CameraExtrinsics::Ptr getExtrinsics() const;
	private:
		void reloadFile();

		std::string filename_;
		CameraExtrinsics::Ptr extrinsics_;

	};
}

