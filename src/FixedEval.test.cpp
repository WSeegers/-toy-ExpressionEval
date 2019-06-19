#include <iomanip>

#include "FixedEval.hpp"

static void doTest(std::string input, float actual)
{
	Fixed result = FixedEval::Eval(input);

	std::cout << std::left << std::setw(10) << "Test: " << input << std::endl;

	if (!FixedEval::hasError())
	{
		std::cout << std::left << std::setw(10) << "Result: " << result << std::endl;
		std::cout << std::left << std::setw(10) << "Actual: " << actual << std::endl;
	}
	else
	{
		std::cout << std::left << std::setw(10) << "Error: " << FixedEval::getError() << std::endl;
	}
	std::cout << std::endl;
}

void FixedEval::test(void)
{
	doTest("500", 500);
	doTest("(((500)))", 500);
	doTest("2 + 5", 2 + 5);
	doTest("-2 + -5", -2 + (-5));
	doTest("10*2+5", 10 * 2 + 5);
	doTest("10*2+5*-5", 10 * 2 + 5 * -5);
	doTest("2*(99+1)", 2 * (99 + 1));
	doTest("2.5 / 2 + 100", 2.5f / 2 + 100);
	doTest("2.5abc", 2.5);
	doTest("2--2", 2 - -2);

	// Error Tests
	doTest("2*(99+1", 2 * (99 + 1));
	doTest("2/0", 2);
	doTest("2-/2", 2);
	doTest("--5", -5);
}
