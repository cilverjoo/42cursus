#ifndef SPAN_HPP
# define SPAN_HPP

#include <string>
#include <iostream>

class Span
{

private:
	int	_num;
	Span();

public:

	~Span();
	Span(const Span &ref);
	Span& operator=(const Span &ref);
	void addNumber();
	unsigned int shorestSpan();
	unsigned int longestSpan();

	class AlreadyNumberFilledException : std::exception
	{
	public:
		virtual const char* what() const throw();
	};

};

#endif
