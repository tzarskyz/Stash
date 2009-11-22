#include <string>
#include <iostream>
#include <fstream>
#include <cstring>

inline void StoreString(const std::string& string, std::fstream& stream)
{
	int size = string.size();
	
	if (size <= 512)
	{
		const unsigned char csize = (unsigned char)size;
		
		stream.write((char *) &csize, sizeof(unsigned char));
		stream.write(string.c_str(), csize);
	}
	else // cap the string at 512
	{
		std::string strLimitedString = string.substr(0, 512);
		
		const unsigned char csize = (unsigned char)512;
		
		stream.write((char *) &csize, sizeof(unsigned char));
		stream.write(strLimitedString.c_str(), csize);
	}
}

inline void LoadString(std::string& string, std::fstream& stream)
{
	char* buf = 0;
	
	unsigned char size = 0;
	stream.read((char *) &size, sizeof(unsigned char));
	
	buf = new char[size + 1];
	stream.read(buf, size);
	buf[size] = 0;
	
	string.assign(buf);
	
	delete [] buf;
}