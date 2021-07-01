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
	if (this == &ref)
		return (*this);
	this->_nums = ref.getNums();
	this->_size = ref.getSize();
	return (*this);
}

std::vector<int>		Span::getNums() const
{
	return (this->_nums);
}

unsigned int			Span::getSize() const
{
	return (this->_size);
}

const char*				Span::NoSpaceException::what() const throw()
{
	return ("There is no space :(");
}

const char*				Span::NumberIsLessThanTwoException::what() const throw()
{
	return ("There are less than 2 elements : Cannot compare :(");
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
	std::vector<int>::iterator iter;
	std::vector<int>::iterator iter2;
	std::vector<int> copy;
	int min;
	
	min = std::numeric_limits<int>::max();
	if (this->_nums.size() <= 1)
		throw (NumberIsLessThanTwoException());
	copy = this->_nums;
	std::sort(copy.begin(), copy.end());
	for (iter = copy.begin(); iter != copy.end(); iter++)
	{
		if (min > (std::max(*iter, *(iter + 1)) - (std::min(*iter, *(iter + 1)))))
			min = (std::max(*iter, *(iter + 1)) - (std::min(*iter, *(iter + 1))));
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
	return ((unsigned int)(std::abs(copy.at(0) - copy.at(copy.size() - 1))));
}
