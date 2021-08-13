#include "FileBuffer.h"


FileBuffer::FileBuffer(FILE* file, int buffer_size) {
	m_file = file;
	m_carPos = 0;
	resetSize(buffer_size);
}

FileBuffer::~FileBuffer() {
	if(m_car != nullptr) {
		free(m_car);
	}
}

FileBuffer::resetSize(int size) {
	if(m_car != nullptr) {
		flush();
		free(m_car);
		m_car = nullptr;
	} 
	m_carSize = size;
	m_car = (char*)malloc(sizeof(char) * m_carSize);
	m_carPos = 0;

}
int FileBuffer::writeData(char* buffer, int nWrite) {
	char* buffer_head = buffer;
	while(nWrite) {
		int realWrite = fixcar(buffer_head, nWrite); 
		nWrite -= realWrite;
		buffer_head += realWrite;
	}
	return nWrite;
}

int FileBuffer::flush() {
	int nWrite = fwrite(m_car, 1, m_carPos, m_file);
	if(nWrite != m_carPos) {
		std::cout << "fwrite_nWrite != carPos: " 
				<< " " <<  __FILE__ << ": " << __LINE__
				<< "\nnWrite = " << nWrite << "m_carPos = " << m_carPos
				<< "\nperror_";
		perror("fwrite");
	}
	if(m_carPos < m_carSize) {
		std::cout << "FileBuffer::flush->carPos = " << m_carPos << std::endl;
	}
	m_carPos = 0;
	memset(m_car, 0, m_carSize);
	return nWrite;
}

int FileBuffer::fixcar(char* buffer, int size) {
	int realWrite = m_carSize - m_carPos;
	if(realWrite > size) {
		realWrite = size;
		for(int i = 0; i < realWrite; i++) {
			m_car[m_carPos++] = buffer[i];
		}
	} else {
		for(int i = 0; i < realWrite; i++) {
			m_car[m_carPos++] = buffer[i];
		}
		flush();
	}

	std::cout << "reaWrite = " << realWrite << " size = " << size << std::endl;
	return realWrite;
	
}
int main() {
	std::cout << "Hello, FileBuffer!" << std::endl;

	return 0;
}
