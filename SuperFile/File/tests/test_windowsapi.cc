#include <iostream>
#include <windows.h>
#include <direct.h>
#include <io.h>
#include <time.h>
#include <map>
#include <string>
#include <vector>

//#define MK_FUN CreateDirectory
#define MK_FUN mkdir

void showFindData(const struct _finddata_t& data) {
	static std::map<unsigned, std::string> arti_map = {
		{
			_A_ARCH
			, "cun dang"
		},
		{
			_A_NORMAL
			, "zheng chang"
		},
		{
			_A_HIDDEN
			, "yin cang"
		},
		{
			_A_RDONLY
			, "only read"
		},
		{
			_A_SUBDIR
			, "is dir"
		},
		{
			_A_SYSTEM
			, "system"
		}
	};
	char createTime[128] = {
		0
	};
	char accessTime[128] = {
		0
	};
	char writeTime[128] = {
		0
	};
#define xx(saveStr, timep) \
	strftime((char*)saveStr, 128, "%c", gmtime((time_t*)timep)
	xx(createTime, data.create_time, )
	std::cout << "find_data: "
		<< "\n\tattrib = " << data.attrib << " desc: " << arti_map[data.attrib]
		<< "\n\tcreate_time: " << createTime
		<< "\n\taccess_time: " << accessTime
		<< "\n\twrite_time: " << writeTime
		<< "\n\tsize = " << data.size
		<< "\n\tname = " << data.name
		<< std::endl;
}

int test_findFirst() {
	struct _finddata_t file_data = {
		0
	};
	
	std::string testPath = "C:\\SoftWare\\Project\\cpp\\*.*"; 
	int k;
	long f_handle;
	k = f_handle = _findfirst(testPath.c_str(), &file_data);
	showFindData(file_data);
}


int test_mkdir() {
//err = -1
	int md1 = _mkdir("./mkdir_0");
	int md2 = _mkdir("./mkdir_1/mkdir_2");

	std::cout << "test_mkdir: "
		<< "md1 = " << md1
		<< "md2 = " << md2
		<< std::endl;
	return 0;
}
int test_CreateDirectory() {
//err = 0 
	int cd1 = CreateDirectory("./test_dir", nullptr);
	int cd2 = CreateDirectory("./test_dir1/test_dir2", nullptr);
	std::cout << "hello windows file api" 
			<< "\ncd1 = " << cd1
			<< "\ncd2 = " << cd2
			<< std::endl;
	return 0;
}
int main() {

	//test_mkdir();
	//test_CreateDirectory();
	test_findFirst();
	return 0;
}
