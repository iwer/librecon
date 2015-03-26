#include "AbstractPointCloudGenerator.h"

class FilePointCloudGenerator : public AbstractPointCloudGenerator
{
public:
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

