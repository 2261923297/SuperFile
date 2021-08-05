#include <iostream>
#include <memory>


class AutoMakeSrc {
public:
	typedef std::shared_ptr<AutoMakeSrc> ptr;
	AutoMakeSrc(const std::string& configFilePath) : m_configFilePath(configFilePath) { }
	virtual ~AutoMakeSrc() { }

	int readConfigFile();

	int 
private:
	std::string m_configFilePath;
};


int main(int argc, char** argv) {
	if(argc	 < 2) {
		std::cout << "error call for atmksrc, right format: atmksrc [config file]" << std::endl;
		return -1;
	}

}
