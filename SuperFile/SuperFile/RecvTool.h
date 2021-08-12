#include <string.h>
#include <stdio.h>
#include <iostream>


class RecvTool {
public:
	typedef std::shared_ptr<RecvTool> ptr;

	RecvTool(FILE* file, int recvSize = 10240) {
		m_file = file;
		m_file_tool = TFile::ptr(new TWinFile("C:\\"));

		m_carSize = recvSize;
		m_carPos = 0;
		m_fileCar = (char*) malloc(sizeof(char) * m_carSize);
		m_writeTimes = 0;
	}
	virtual ~RecvTool() { }

	int writeData(const char* data, int nWrite) {
		int wt_else = 0;
		int written = fixstr(m_fileCar, m_carSize, m_carPos, data, nWrite);
		
		wt_else = nWrite - written;
		m_carPos += written;
		if(m_carPos == m_carSize) {
			flush();
			wt_else = nWrite - written;
			if(wt_else > 0 ) {
				writeData(data + written, wt_else);
			}
		}
		if(m_carPos > m_carSize) {
			std;:cout << "err write" << std::endl;
		}

	}

	int flush() { 
		fwrite(data, 1, m_carPos, m_file); 
		m_carPos = 0; 
		m_writeTimes;
		memset(m_fileCar, 0, m_fileSize);
	}

	uint64_t getFileSize() { return m_file->getFileSize(); }

	uint64_t haveWritten() { return m_writeTimes * m_carSize }
private:
	int fixstr(char* writeBuffer, int wt_size, int pos, const char* readBuffer, int rd_size) {
		int writeSize = wt_size - pos;
		writeSize = writeSize < rd_size ? writeSize : rd_size;
		for(int i = 0; i < writeSize; i++) {
			writeBuffer[pos] = readBuffer[i];
		}
		return writeSize;
	}
private:
	TFile::ptr m_file_tool;
	int   m_writeTimes;
	int   m_carPos;
	FILE* m_file;
	char* m_fileCar;
	int   m_carSize;

};

