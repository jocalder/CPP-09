/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocalder <jocalder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 11:30:31 by jocalder          #+#    #+#             */
/*   Updated: 2026/04/09 11:56:37 by jocalder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
    BitcoinExchange     btc;
    if (argc != 2)
    {
        std::cerr << "Usage: ./btc <input file>." << std::endl;
        return 1;
    }
    try
    {
        btc.loadDataBase("data.csv");
        btc.processInput(argv[1]);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
    
}