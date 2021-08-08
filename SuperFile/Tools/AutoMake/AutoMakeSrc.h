#pragma once
#include <iostream>
#include <memory>

static const char* HeadContent = "
#include \"????.h\" \r\n

????::????() {\r\n

}

????::~????() {

}

int main() {
	std::cout << "Hello, ????!" << std::endl;

	return 0;
}
";

class AutoMakeSrc {
public:
	typedef std::shared_ptr<AutoMaakeSrc> ptr;
	AutoMakeSrc();
	~AutoMakeSrc();

	static std::string* run(const std::string& projectName);


protected:

private:

};
