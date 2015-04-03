#include "AbstractPointCloudGenerator.h"

class FilePointCloudGenerator : public AbstractPointCloudGenerator
{
public:
	EIGEN_MAKE_ALIGNED_OPERATOR_NEW;
	void aquireFrame() override;
	void start() override;
	void stop() override;
public:
	FilePointCloudGenerator(std::string filename);
	~FilePointCloudGenerator();

private:
	void reloadFile();

	std::string filename_;

};

