#include <iostream>

#include <memory>

class Buffer {
public:
	typedef std::shared_ptr<Buffer> ptr;
	typedef int data_s;
	typedef char* data_p;
	Buffer() {}
	~Buffer() {}
	Buffer(data_s data_size) {
		m_data_size = data_size;
		int ret = init();

		std::cout << "init_ret = " << ret << std::endl;
	}

	void showData() {
		std::cout << "data_addr = " << (int)m_data_addr
			<< std::endl
			<< "data_size = " << m_data_size
			<< std::endl;
	}

	int reSet(data_s data_size) {
		int ans = 0;
		m_data_size = data_size;
		if(m_data_addr != nullptr) {
			free(m_data_addr);
		}
		m_data_addr = nullptr;
		m_data_addr = (data_p)malloc(m_data_size);
		if(m_data_addr == nullptr) {
			ans = -1;
		} else {
			ans = m_data_size;
		}
		return ans;
	}
	

	int init() {
		int ans = 0;
		m_data_addr = (data_p)malloc(m_data_size);
		if(m_data_addr == nullptr) {
			ans = -1;
		} else {
			ans = m_data_size;
		}
		return ans;
	}

	data_p getDataAddr() { return m_data_addr; } 
	data_s getDataSize() { return m_data_size; }
private:
	data_p m_data_addr;
	data_s m_data_size;

};

int main() {
	Buffer bf(1024);

	bf.showData();
	return 0;

}
