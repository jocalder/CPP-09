/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocalder <jocalder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 11:39:22 by jocalder          #+#    #+#             */
/*   Updated: 2026/04/13 11:45:42 by jocalder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <cstdlib>

class RPN
{
	private:
		std::stack<int>		_stack;
		bool	isOperator(const std::string& token) const;
		void	applyOperation(const std::string& op);
	public:
		RPN();
		RPN(const RPN& other);
		RPN&	operator=(const RPN& other);
		~RPN();

		void	evaluate(const std::string& expression);
};


#endif