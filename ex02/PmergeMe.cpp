/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocalder <jocalder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 10:28:03 by jocalder          #+#    #+#             */
/*   Updated: 2026/04/15 10:39:04 by jocalder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::~PmergeMe() {}

std::vector<int>	PmergeMe::parseInput(char **argv)
{
	std::vector<int>	result;
	for (int i = 1; argv[i]; i++)
	{
		std::string		s(argv[i]);
		for (size_t j = 0; j < s.size(); j++)
		{
			if (!isdigit(s[j]))
				throw std::runtime_error("Error: is not a digit or positive number.");
		}
		int	n = atoi(argv[i]);
		if (n < 0)
			throw std::runtime_error("Error: is not a positive number.");
		result.push_back(n);
	}
	return result;
}

void	PmergeMe::print(const std::vector<int>& seq, const std::string& msg)
{
	std::cout << msg;
	for (size_t i = 0; i < seq.size(); i++)
		std::cout << seq[i] << " ";
	std::cout << std::endl;
}

template<typename T>
void	binaryInsert(T &container, int value)
{
	typename T::iterator	pos =
			std::lower_bound(container.begin(), container.end(), value);
	container.insert(pos, value);
}

void	PmergeMe::sortVector(std::vector<int>& vec)
{
	if (vec.size() <= 1)
		return;
	std::vector<int>	mainChain;
	std::vector<int>	pending;

	for (size_t i = 0; i + 1 < vec.size(); i += 2)
	{
		if (vec[i] > vec[i + 1])
			std::swap(vec[i], vec[i + 1]);
		mainChain.push_back(vec[i + 1]);
		pending.push_back(vec[i]);
	}
	if (vec.size() % 2 != 0)
		pending.push_back(vec.back());
	sortVector(mainChain);
	
	for (size_t i = 0; i < pending.size(); i++)
		binaryInsert(mainChain, pending[i]);
	vec = mainChain;
}

void	PmergeMe::sortDeque(std::deque<int>& deq)
{
	if (deq.size() <= 1)
		return ;
	std::deque<int>		mainChain;
	std::deque<int>		pending;

	for (size_t i = 0; i + 1 < deq.size(); i += 2)
	{
		if (deq[i] > deq[i + 1])
			std::swap(deq[i], deq[i + 1]);
		mainChain.push_back(deq[i + 1]);
		pending.push_back(deq[i]);
	}
	if (deq.size() % 2 != 0)
		pending.push_back(deq.back());
	sortDeque(mainChain);
	
	for (size_t i = 0; i < pending.size(); i++)
		binaryInsert(mainChain, pending[i]);
	deq = mainChain;
}

void	PmergeMe::process(char **argv)
{
	std::vector<int>	input = parseInput(argv);

	print(input, "Before: ");

	std::vector<int>	vec = input;
	clock_t	startVec = clock();
	sortVector(vec);
	clock_t	endVec = clock();
	
	print(vec, "After: ");

	double timeVec =
		(double)(endVec - startVec) / CLOCKS_PER_SEC * 1000000;
	std::cout << "Time to process a range of " << vec.size()
	        << " elements with std::vector : "
	    	<< timeVec << " us" << std::endl;

	std::deque<int> deq(input.begin(), input.end());

	clock_t startDeq = clock();
	sortDeque(deq);
	clock_t endDeq = clock();

	double timeDeq =
		(double)(endDeq - startDeq) / CLOCKS_PER_SEC * 1000000;
	std::cout << "Time to process a range of " << deq.size()
	    	<< " elements with std::deque : "
	        << timeDeq << " us" << std::endl;
}