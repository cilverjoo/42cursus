#include "span.hpp"

int main()
{
	Span	sp(5);
	
	try
	{
		sp.addNumber(3);
		std::cout << sp.shortestSpan() << '\n';
	}
	catch(const std::exception &e)
	{
		std::cout << e.what() << '\n';
	}

	sp.addNumber(10);
	sp.addNumber(6);
	sp.addNumber(16);
	sp.addNumber(1);

	try
	{
		sp.addNumber(21);
	}
	catch(const std::exception &e)
	{
		std::cout<<e.what()<<'\n';
	}
    std::cout << sp.shortestSpan() << '\n';
    std::cout << sp.longestSpan() << '\n';
	
	std::cout << "====================\n";
	
	std::vector<int>	temp;
	Span sp2(100);

	for(int i = 1; i < 100; i++)
		temp.push_back(rand() % 1000);
	sp2.addNumber(temp.begin(), temp.end());

	std::sort(temp.begin(), temp.end());
	std::vector<int>::iterator iter;	
	std::cout << "random vector : [";	
	for (iter = temp.begin(); iter != temp.end(); iter++)
	{
		std::cout << *iter << " ";
	}
	std::cout << "]" << std::endl;
	
    std::cout << sp2.shortestSpan() << '\n';
    std::cout << sp2.longestSpan() << '\n'; 
	return (0);
}
