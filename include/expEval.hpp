#include <string>
#include <sstream>
#include <exception>

//TODO: Add namespace

template <typename T>
static T evalSum(std::stringstream &input);

static void clenseString(const std::string &input, std::stringstream &output)
{
    for (unsigned int i = 0; i < input.size(); i++)
    {
        // if (!std::isspace(input[i]) && !std::isalpha(input[i]))
        if (!std::isspace(input[i]))
            output << input[i];
    }
}

template <typename T>
T evalFactor(std::stringstream &input)
{
    if (input.peek() == '(')
    {
        input.get();
        T f1(evalSum<T>(input));
        if (input.get() != ')')
            throw std::exception();
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
            throw std::exception();

        T ft1;
        input >> ft1;
        return ft1 * neg;
    }
}

template <typename T>
static T evalProduct(std::stringstream &input)
{
    T f1 = evalFactor<T>(input);

    while (input.peek() == '*' || input.peek() == '/')
    {
        T f2 = evalFactor<T>(input);
        char op = input.get();

        if (op == '*')
            f1 *= f2; // TODO: check for overflow
        else
        {
            T f2 = evalFactor<T>(input);
            if (f2 == 0)
                throw std::exception(); // TODO: Namespaced errors
            else
                f1 /= f2;
        }
    }
    return f1;
}

template <typename T>
static T evalSum(std::stringstream &input)
{
    T f1 = evalProduct<T>(input);

    while (input.peek() == '+' || input.peek() == '-')
    {
        char op = input.get();
        T f2 = evalProduct<T>(input);
        if (op == '+')
            f1 += f2; // TODO: check for overflow
        else
            f1 -= f2; // TODO: check for overflow
    }
    return f1;
}

template <typename T>
T expEval(const std::string &input)
{
    std::stringstream ss;
    clenseString(input, ss);

    T f1 = evalSum<T>(ss);
    return f1;
}
