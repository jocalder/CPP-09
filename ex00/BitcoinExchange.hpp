/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocalder <jocalder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 11:30:26 by jocalder          #+#    #+#             */
/*   Updated: 2026/04/13 11:03:10 by jocalder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <map>
#include <string>
#include <iomanip>
#include <limits>
#include <stdexcept>

class BitcoinExchange
{
	private:
		std::map<std::string, double>	_db;
		std::string	trim(const std::string& str) const;
		bool	isValidDate(const std::string& date) const;
		bool	isValidValue(const std::string& str, double& value) const;
		bool	isLeapYear(int year) const;
	public:
		BitcoinExchange();
		BitcoinExchange(const BitcoinExchange& other);
		BitcoinExchange&	operator=(const BitcoinExchange& other);
		~BitcoinExchange();

		void	loadDataBase(const std::string& filename);
		void	processInput(const std::string& filename);
};

#endif