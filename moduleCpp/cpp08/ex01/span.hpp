#ifndef SPAN_HPP
# define SPAN_HPP

#include <string>
#include <iostream>
#include <iterator>
#include <vector>
#include <climits>

class Span
{
private:
	Span();
	unsigned int		_size;
	std::vector<int>	_nums;
	
public:
	Span(unsigned int size);
	~Span();
	Span(const Span &ref);
	Span& operator=(const Span &ref);
	std::vector<int>	getNums(void) const;
	unsigned int		getSize(void) const;
	void				addNumber(int num);
	void				addNumber(std::vector<int>::iterator begin, std::vector<int>::iterator end);
	unsigned int		shortestSpan(void);
	unsigned int		longestSpan(void);
	
	class NoSpaceException : public std::exception
	{
	public:
		virtual const char* what() const throw();
	};

	class NumberIsLessThanTwoException : public std::exception
	{
	public:
		virtual const char* what() const throw();
	};
};

#endif
