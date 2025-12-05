#include "BitcoinExchange.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <cctype>

BitcoinExchange::BitcoinExchange() {}
BitcoinExchange::~BitcoinExchange() {}

std::string BitcoinExchange::trim(const std::string &s) {
	std::string::size_type start = 0;
	while (start < s.size() && std::isspace(static_cast<unsigned char>(s[start])))
		++start;
	std::string::size_type end = s.size();
	while (end > start && std::isspace(static_cast<unsigned char>(s[end - 1])))
		--end;
	return s.substr(start, end - start);
}

bool BitcoinExchange::isLeap(int year) {
	if (year % 400 == 0)
		return true;
	if (year % 100 == 0)
		return false;
	return (year % 4 == 0);
}

bool BitcoinExchange::validDate(const std::string &date) {
	if (date.size() != 10)
		return false;
	if (date[4] != '-' || date[7] != '-')
		return false;
	size_t i = 0;
	while (i < date.size()) {
		if (i == 4 || i == 7) {
			++i;
			continue;
		}
		if (!std::isdigit(static_cast<unsigned char>(date[i])))
			return false;
		++i;
	}
	int year = std::atoi(date.substr(0, 4).c_str());
	int month = std::atoi(date.substr(5, 2).c_str());
	int day = std::atoi(date.substr(8, 2).c_str());
	if (month < 1 || month > 12)
		return false;
	if (day < 1)
		return false;
	int mdays = 31;
	switch (month) {
		case 1: case 3: case 5: case 7: case 8: case 10: case 12:
			mdays = 31; break;
		case 4: case 6: case 9: case 11:
			mdays = 30; break;
		case 2:
			if (isLeap(year))
				mdays = 29;
			else
				mdays = 28;
			break;
	}
	if (day > mdays)
		return false;
	return true;
}

bool BitcoinExchange::loadDatabase(const std::string &dbFilename) {
	std::ifstream f(dbFilename.c_str());
	if (!f)
		return false;
	std::string line;
	while (std::getline(f, line)) {
		if (line.empty())
			continue;
		std::string::size_type comma = line.find(',');
		if (comma == std::string::npos)
			continue;
		std::string date = trim(line.substr(0, comma));
		std::string rateStr = trim(line.substr(comma + 1));
		if (!validDate(date))
			continue;
		double rate = 0.0;
		std::istringstream ss(rateStr);
		if (!(ss >> rate))
			continue;
		char c;
		if (ss >> c)
			continue;
		_rates[date] = rate;
	}
	return !_rates.empty();
}

void BitcoinExchange::processInput(const std::string &inputFilename) const {
	std::ifstream f(inputFilename.c_str());
	if (!f) {
		std::cerr << "Error: could not open file." << std::endl;
		return;
	}
	std::string line;
	std::streampos pos = f.tellg();
	if (std::getline(f, line)) {
		std::string::size_type pipe = line.find('|');
		if (pipe != std::string::npos) {
			std::string left = trim(line.substr(0, pipe));
			std::string right = trim(line.substr(pipe + 1));
			if (left == "date" && (right == "value")) {
				;
			}
			else {
				f.clear();
				f.seekg(pos);
			}
		}
		else {
			f.clear();
			f.seekg(pos);
		}
	}
	while (std::getline(f, line)) {
		if (line.empty())
			continue;
		std::string::size_type pipe = line.find('|');
		if (pipe == std::string::npos) {
			std::cout << "Error: bad input : " << line << std::endl;
			continue;
		}
		std::string date = trim(line.substr(0, pipe));
		std::string valueStr = trim(line.substr(pipe + 1));
		if (!validDate(date)) {
			std::cout << "Error: date invalid : " << date << std::endl;
			continue;
		}
		double value = 0.0;
		{
			std::istringstream vs(valueStr);
			if (!(vs >> value)) {
				std::cout << "Error: value invalid : " << valueStr << std::endl;
				continue;
			}
			char c;
			if (vs >> c) {
				std::cout << "Error: value invalid : " << valueStr << std::endl;
				continue;
			}
		}
		if (value < 0) {
			std::cout << "Error: not a positive number." << std::endl;
			continue;
		}
		if (value > 1000) {
			std::cout << "Error: too large a number." << std::endl;
			continue;
		}
		if (_rates.empty()) {
			std::cout << "Error." << std::endl;
			continue;
		}
		std::map<std::string, double>::const_iterator it = _rates.lower_bound(date);
		if (it == _rates.end()) {
			std::map<std::string, double>::const_iterator it2 = _rates.end();
			--it2;
			it = it2;
		}
		else if (it->first == date) {
			;
		}
		else {
			if (it == _rates.begin()) {
				std::cout << "Error: date too early : " << date << std::endl;
				continue;
			}
			--it;
		}
		double rate = it->second;
		double result = value * rate;
		std::cout << date << " => " << value << " = ";
		std::ostringstream out;
		out << std::fixed << std::setprecision(6) << result;
		std::string r = out.str();
		while (!r.empty() && r.find('.') != std::string::npos && (r[r.size() - 1] == '0'))
			r.erase(r.size() - 1);
		if (!r.empty() && (r[r.size() - 1] == '.'))
			r.erase(r.size() - 1);
		std::cout << r << std::endl;
	}
}
