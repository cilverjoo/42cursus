#include "span.hpp"

Span::Span(unsigned int size) : _size(size)
{
}

Span::~Span()
{
}

Span::Span(const Span &ref) : _size(ref._size), _nums(ref._nums)
{
}

Span&					Span::operator=(const Span &ref)
{
	*this = Span(ref);
	return (*this);
}

std::vector<int>		Span::getNums()
{
	return (this->_nums);
}

const char*				Span::NoSpaceException::what() const throw()
{
	return ("There is no space :(");
}

const char*				Span::NumberIsLessThanTwoException::what() const throw()
{
	return ("Not enough number(s) exist(s) :(");
}

void					Span::addNumber(int num)
{
	if (this->_nums.size() == this->_size)
		throw(Span::NoSpaceException());
	this->_nums.push_back(num);
}

void					Span::addNumber(std::vector<int>::iterator begin, std::vector<int>::iterator end)
{
	if (this->_nums.size() + std::distance(begin, end) > this->_size)
		throw(Span::NoSpaceException());
	this->_nums.insert(_nums.end(), begin, end);
}

unsigned int			Span::shortestSpan(void)
{
	std::vector<int>::iterator iter1;
	std::vector<int>::iterator iter2;
	unsigned int min;
	
	min = std::numeric_limits<unsigned int>::max();
	if (this->_nums.size() <= 1)
		throw (NumberIsLessThanTwoException());
	for (iter1 = _nums.begin(); iter1 != _nums.end(); iter1++)
	{
		for (iter2 = _nums.end(); iter2 != _nums.begin(); iter2--)
		{
			if (min > (std::max(*iter1, *iter2) - (std::min(*iter1, *iter2))))
				min = (std::max(*iter1, *iter2) - (std::min(*iter1, *iter2)));
		}
	}
	return (min);
}

unsigned int			Span::longestSpan(void)
{
	std::vector<int>::iterator iter1;
	std::vector<int>::iterator iter2;
	std::vector<int> copy;
	
	if (this->_nums.size() <= 1)
		throw(NumberIsLessThanTwoException());
	copy = this->_nums;
	std::sort(copy.begin(), copy.end());
	return (std::abs(copy.at(0) - copy.at(copy.size() - 1)));
}
