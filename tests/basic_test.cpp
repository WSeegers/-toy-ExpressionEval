#define CATCH_CONFIG_MAIN
#include "./catch.hpp"
#include "../include/expEval.hpp"

// #define EXPTEST

TEST_CASE("Basic Tests", "[BASIC]")
{
    SECTION("Addition")
    {
        REQUIRE(expEval<int>("1 + 1") == 1 + 1);
        REQUIRE(expEval<int>("1 + 11") == 1 + 11);
        REQUIRE(expEval<int>("9999 + -9999") == 9999 + -9999);
    };

    SECTION("Subtraction")
    {
        REQUIRE(expEval<int>("10 - 1") == 10 - 1);
        REQUIRE(expEval<int>("1 - 10") == 1 - 10);
        REQUIRE(expEval<int>("9999 - -9999") == 9999 - -9999);
    };
};