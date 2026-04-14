/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jocalder <jocalder@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/13 11:39:31 by jocalder          #+#    #+#             */
/*   Updated: 2026/04/14 08:14:43 by jocalder         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN() {}
RPN::RPN(const RPN& other) {*this = other;}
RPN&	RPN::operator=(const RPN& other)
{
	if (this != &other)
		_stack = other._stack;
	return *this;
}
RPN::~RPN() {}

bool	RPN::isOperator(const std::string& token) const
{
	return (token == "+" || token == "-" || token == "*" || token == "/");
}

void	RPN::applyOperation(const std::string& op)
{
	if (_stack.size() < 2)
		throw std::runtime_error("Error: insuficient operands.");

	int		b = _stack.top(); _stack.pop();
	int		a = _stack.top(); _stack.pop();
	int		result;

	if (op == "+")
		result = a + b;
	else if (op == "-")
		result = a - b;
	else if (op == "*")
		result = a * b;
	else if (op == "/")
	{
		if (b == 0)
			throw std::runtime_error("Error: not divisible by 0.");
		result = a / b;
	}
	else	
		throw std::runtime_error("Error: bad operand.");
	_stack.push(result);
}

void	RPN::evaluate(const std::string& expression)
{
	std::stringstream		ss(expression);
	std::string				token;

	while (ss >> token)
	{
		if (isOperator(token))
			applyOperation(token);
		else
		{
			if (token.length() != 1 || !isdigit(token[0]))
				throw std::runtime_error("Error");
			int		value = token[0] - '0';
			_stack.push(value);
		}
	}
	if (_stack.size() != 1)
		throw std::runtime_error("Error");
	std::cout << _stack.top() << std::endl;
}