#pragma once
#include <vector>
#include <iostream>
#include <memory>
#include <sstream>
class FormatterItem {
public:
	typedef std::shared_ptr<FormatterItem> ptr;
	
	FormatterItem(std::string pattern = "") : m_pattern(pattern) {	}
	virtual ~FormatterItem() {	}
	
	virtual std::string format() = 0;

protected:
	std::string m_pattern;
};


class Formatter {
public:
	typedef std::shared_ptr<Formatter> ptr;

	Formatter(const std::string& formate) : m_formate(formate) { }
	
	virtual ~Formatter() { }

	std::string format();
proteted:
	virtual initItems() = 0;
protected:
	std::string   m_formate;
	std::vector<FormatterItem::ptr> m_items;
};


std::string Formatter::format()  {
	initItems();
	stringstream ss;
	for(auto i : m_items) {
		ss << i->format();
	}
	return ss.str();
}
