#include "Utils.h"

bool Utils::validateExtension(std::string p_path) 
{
	size_t pos = p_path.find_last_of(".");
	if (pos == std::string::npos) 
	{
		return false;
	}
	else 
	{
		if ((p_path.substr(pos + 1) == std::string("txt")) || 
			(p_path.substr(pos + 1) == std::string("log")) ||
			(p_path.substr(pos + 1) == std::string("xml")))
		{
			return true;
		}
	}
	return false;
}