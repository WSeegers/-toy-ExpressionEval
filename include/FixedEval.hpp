#ifndef FIXEDEVAL_HPP
#define FIXEDEVAL_HPP

#include <sstream>

#include "./Fixed.hpp"

class FixedEval
{
private:
	FixedEval();

	static Fixed EvalFactor(std::stringstream &input);
	static Fixed EvalProduct(std::stringstream &input);
	static Fixed EvalSum(std::stringstream &input);
	static void clenseString(const std::string &input, std::stringstream &output);

	static bool _hasError;
	static std::string _errorMsg;

	static void setError(const std::string &msg);

public:
	static Fixed Eval(const std::string &input);
	static bool hasError();
	static std::string getError();

	static void test(void);
};

#endif
