/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocalder <jocalder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 10:27:39 by jocalder          #+#    #+#             */
/*   Updated: 2026/04/15 10:28:44 by jocalder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <deque>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <algorithm>

class PmergeMe
{
	private:
		PmergeMe();
		PmergeMe(const PmergeMe& other);
		PmergeMe&	operator=(const PmergeMe& other);
	public:
		~PmergeMe();
		
		static void		process(char **argv);
		static void		sortVector(std::vector<int>& vec);
		static void		sortDeque(std::deque<int>& deq);
		static std::vector<int>		parseInput(char **argv);
		static void		print(const std::vector<int>& seq, const std::string& msg);
};

#endif