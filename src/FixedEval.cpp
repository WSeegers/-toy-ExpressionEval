
#include <limits>

#include "FixedEval.hpp"

bool FixedEval::_hasError = false;
std::string FixedEval::_errorMsg;

void FixedEval::setError(const std::string &msg)
{
	if (FixedEval::_hasError)
		return;
	FixedEval::_hasError = true;
	FixedEval::_errorMsg = msg;
}

void FixedEval::clenseString(const std::string &input, std::stringstream &output)
{
	for (unsigned int i = 0; i < input.size(); i++)
	{
		if (!std::isspace(input[i]) && !std::isalpha(input[i]))
			output << input[i];
	}
}

Fixed FixedEval::Eval(const std::string &input)
{
	FixedEval::_hasError = false;
	std::stringstream ss;
	FixedEval::clenseString(input, ss);

	Fixed f1 = FixedEval::EvalSum(ss);
	return f1;
}

Fixed FixedEval::EvalFactor(std::stringstream &input)
{
	if (input.peek() == '(')
	{
		input.get();
		Fixed f1(FixedEval::EvalSum(input));
		if (input.get() != ')')
			FixedEval::setError("No closing bracket");
		return f1;
	}
	else
	{
		char neg = 1;
		if (input.peek() == '-')
		{
			input.get();
			neg = -1;
		}
		if (!(std::isdigit(input.peek())))
		{
			std::string error("Invalid character found: ");
			error += (char)input.get();
			FixedEval::setError(error);
		};

		float ft1;
		input >> ft1;
		return Fixed(ft1 * neg);
	}
}

Fixed FixedEval::EvalProduct(std::stringstream &input)
{
	Fixed f1 = FixedEval::EvalFactor(input);

	while (input.peek() == '*' || input.peek() == '/')
	{
		char op = input.get();
		if (op == '*')
			f1 *= FixedEval::EvalFactor(input);
		else
		{
			Fixed f2 = FixedEval::EvalFactor(input);
			if (f2.toFloat() == 0)
				FixedEval::setError("Divide by Zero");
			else
				f1 /= f2;
		}
	}
	return f1;
}

Fixed FixedEval::EvalSum(std::stringstream &input)
{
	Fixed f1 = FixedEval::EvalProduct(input);

	while (input.peek() == '+' || input.peek() == '-')
	{
		char op = input.get();
		if (op == '+')
			f1 += FixedEval::EvalProduct(input);
		else
			f1 -= FixedEval::EvalProduct(input);
	}
	return f1;
}

bool FixedEval::hasError() { return FixedEval::_hasError; }
std::string FixedEval::getError() { return FixedEval::_errorMsg; }
