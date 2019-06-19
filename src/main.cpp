#include <string>
#include <iomanip>

#include "FixedEval.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
	{
		return 0;
	}

	if (!std::string(av[1]).compare("test"))
		FixedEval::test();
	else
	{
		Fixed result(FixedEval::Eval(av[1]));
		if (!FixedEval::hasError())
			std::cout << result << std::endl;
		else
		{
			std::cout << std::left << std::setw(10)
								<< "Error: " << FixedEval::getError() << std::endl;
			return -1;
		}
	}
	return 0;
}
