#include <iostream>
#include <memory>
#include <stdio.h>
#include <string.h>

class FileBuffer {
public:
	FileBuffer(FILE* file, int buffer_size = 10240);
	~FileBuffer();

	int getPos()  { return m_carPos; }
	int getSize() { return m_carSize; }
	const FILE* getFile() { return m_file; }
	const char* getCar()  { return m_car; }

	int resetSize(int size);

	int writeData(char* buffer, int nWrite);

	int flush();
private:

	int fixcar(char* buffer, int size);

	

private:
	FILE* m_file;

	char* m_car;
	int m_carSize;
	int m_carPos;

};

