#include <iostream>
#include <memory>
#include <string>
#include <vector>

class Command {
public:
	Command();
	~Command();
	
	std::string getCommand(const char* cmdStr);
	std::string getCommand(const std::string& cmdStr);
	int makeCommand(proto::head ph, std::vector<std::string>& strs, std::string& cmdStr);


private:
	Proto::ptr proto;     //use protocol<tools>

};
