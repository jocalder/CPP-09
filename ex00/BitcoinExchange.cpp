/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocalder <jocalder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 11:30:29 by jocalder          #+#    #+#             */
/*   Updated: 2026/04/09 12:15:18 by jocalder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() {}
BitcoinExchange::BitcoinExchange(const BitcoinExchange& other)
{_db = other._db;}
BitcoinExchange& BitcoinExchange::operator=(const BitcoinExchange& other)
{
	if (this != &other)
		_db = other._db;
	return *this;
}
BitcoinExchange::~BitcoinExchange() {}

std::string		BitcoinExchange::trim(const std::string& str) const
{
	size_t	start = 0, end = str.length();

	while (start < str.length() || str[start] == ' ' || str[start] == '\t')
		start++;
	while (end > start && (str[end - 1] == ' ' || str[end - 1] == '\t'))
		end--;
	return (str.substr(start, end - start));
}

bool	BitcoinExchange::isLeapYear(int year) const
{
	if (year % 400 == 0)
		return true;
	if (year % 100 == 0)
		return false;
	return (year % 4 == 0);
}

bool	BitcoinExchange::isValidDate(const std::string& date) const
{
	if (date.size() != 10 || date[4] != '-' || date[7] != '-')
		return false;
	for (size_t i = 0; i < date.size(); ++i)
	{
		if (i == 4 || i == 7)
		continue ;
		if (!isdigit(date[i]))
		return false;
	}
	int		year = std::atoi(date.substr(0, 4).c_str());
	int		month = std::atoi(date.substr(5, 2).c_str());
	int		day = std::atoi(date.substr(8, 2).c_str());

	if (month < 1 || month > 12)
		return false;
	if (day < 1 || day > 31)
		return false;
	
	int		daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if (month == 2 && isLeapYear(year))
		daysInMonth[1] = 29;
	if (day < daysInMonth[month - 1])
		return false;
	return true;
}

bool	BitcoinExchange::isValidValue(const std::string& valueStr, double& value) const
{
	char	*endPtr;

	value = std::strtod(valueStr.c_str(), &endPtr);
	if (*endPtr != '\0')
		return false;
	if (value < 0)
		throw std::runtime_error("Error: Not a positive number.");
	if (value > 1000)
		throw std::runtime_error("Error: too large a number.");
	return true;
}


void	BitcoinExchange::loadDataBase(const std::string& filename)
{
	std::ifstream	file(filename.c_str());
	std::string		line;
	
	if (!file.is_open())
		throw std::runtime_error("Error: could not open database.");
	if (!std::getline(file, line))
		throw std::runtime_error("Error: empty database.");
	while (std::getline(file, line))
	{
		std::stringstream	ss(line);
		std::string			date, priceStr;
		double				price;
		if (!std::getline(ss, date, ',') || !std::getline(ss, priceStr))
			continue ;
		date = trim(date);
		priceStr = trim(priceStr);
		if (!isValidDate(date))
			continue ;
		price = std::stod(priceStr.c_str(), NULL);
		_db[date] = price;
	}
	file.close();
}

void	BitcoinExchange::processInput(const std::string& filename)
{
	std::ifstream	file(filename.c_str());
	std::string		line;
	
	if (!file.is_open())
		throw std::runtime_error("Error: could not open file.");
	if (!std::getline(file, line))
		throw std::runtime_error("Errot: empty file.");
	while (std::getline(file, line))
	{
		std::stringstream	ss(line);
		std::string			date, valueStr;
		double				value;
		if (!std::getline(ss, date, '|') || !std::getline(ss, valueStr))
		{
			std::cerr << "Error: bad input => " << line << std::endl;
			continue ;
		}
		date = trim(date);
		valueStr = trim(valueStr);
		if (!isValidDate(date))
		{
			std::cerr << "Error: bad input => " << date << std::endl;
		}
		try
		{
			if (!isValidValue(valueStr, value))
			{	
				std::cerr << "Error: bad input => " << line << std::endl;
				continue ;
			}
		}
		catch(const std::exception& e)
		{
			std::cerr << e.what() << std::endl;
			continue ;
		}
		std::map<std::string, double>::iterator	it = _db.upper_bound(date);
		if (it == _db.begin())
		{
			std::cerr << "Error: no rate available for this date." << std::endl;
			continue ;
		}
		if (it == _db.end() || it->first != date)
			--it;
		std::cout << date << " => " << value << " = " << value * it->second << std::endl;
	}
	file.close();
}