#include <map>
#include <string>
#include <iostream>
#include <fstream>


#ifndef FORMINFO_H
#define FORMINFO_H

struct attribute {
	std::string A;
	std::string B;
	std::string C;
};

class formInfo {
	public:
		formInfo(std::string path);
		renew();
		struct attribute getAttribute(int i);
	protected:
		std::map<int, struct attribute> attributes;
		std::string jsonFilePath;
};

#endif
