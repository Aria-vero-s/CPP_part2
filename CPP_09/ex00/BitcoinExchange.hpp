#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>

class BitcoinExchange {
public:
	BitcoinExchange();
	~BitcoinExchange();

	bool loadDatabase(const std::string &dbFilename);
	void processInput(const std::string &inputFilename) const;

private:
	std::map<std::string, double> _rates;

	void handleLine(const std::string &line) const;
	static std::string trim(const std::string &s);
	static bool validDate(const std::string &date);
	static bool isLeap(int year);
};

#endif