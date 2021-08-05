#pragma once
#include <iostream>
#include <string>
#include "Formatter.h"


class LogFormater public Formatter{
public:
	LogFormater();
	~LogFormater();

	std::string format(const std::string& pattern) override;

privata:
	std::map<std::string, FormatterItem>
};
