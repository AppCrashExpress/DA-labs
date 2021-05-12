#include <sstream>
#include "bigint.h"

#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_FAST_COMPILE
#include "catch2.hpp"

enum TCmp {
    EQUAL, LESS, MORE
};

std::string TestOutput(std::string strVal) {
    TBigInt bigint(strVal);
    std::ostringstream oss;

    oss << bigint;
    return oss.str();
}

std::string TestSum(std::string strFirst, std::string strSecond) {
    TBigInt a(strFirst), b(strSecond);
    std::ostringstream oss;

    oss << a + b;
    return oss.str();
}

std::string TestSub(std::string strFirst, std::string strSecond) {
    TBigInt a(strFirst), b(strSecond);
    std::ostringstream oss;

    oss << a - b;
    return oss.str();
}

std::string TestMult(std::string strFirst, std::string strSecond) {
    TBigInt a(strFirst), b(strSecond);
    std::ostringstream oss;

    oss << a * b;
    return oss.str();
}

std::string TestDiv(std::string strFirst, std::string strSecond) {
    TBigInt a(strFirst), b(strSecond);
    std::ostringstream oss;

    oss << a / b;
    return oss.str();
}

std::string TestPower(std::string strFirst, std::string strSecond) {
    TBigInt a(strFirst);
    TBigInt::TPrimitive b = stoll(strSecond);
    std::ostringstream oss;

    oss << (a ^ b);
    return oss.str();
}

bool TestCmp(std::string strFirst, std::string strSecond, TCmp cmpType) {
    TBigInt a(strFirst), b(strSecond);

    bool res;
    switch (cmpType) {
        case EQUAL:
            res = a == b;
            break;
        case LESS:
            res = a < b;
            break;
        case MORE:
            res = a > b;
            break;
    }

    return res;
}

TEST_CASE("input-output", "[input][output]") {

    SECTION("No input") {
        REQUIRE(TestOutput("") == "0");
    }

    SECTION("Zero digit") {
        REQUIRE(TestOutput("0") == "0");
    }

    SECTION("Many zero digits") {
        REQUIRE(TestOutput("00000000000") == "0");
    }

    SECTION("One digit") {
        REQUIRE(TestOutput("9") == "9");
    }

    SECTION("Two digit") {
        REQUIRE(TestOutput("80") == "80");
    }

    SECTION("Size of base") {
        REQUIRE(TestOutput("1234567891") == "1234567891");
    }

    SECTION("One digit, rest zeros") {
        REQUIRE(TestOutput("2000000000") == "2000000000");
    }

    SECTION("Leading zeros") {
        REQUIRE(TestOutput("000000000000200") == "200");
    }

    SECTION("Twice the base") {
        REQUIRE(TestOutput("12345678912345678912") == "12345678912345678912");
    }
}

TEST_CASE("sum", "[sum][input][output]") {
    SECTION("Sum of zeros") {
        REQUIRE(TestSum("0", "0") == "0");
    }

    SECTION("Sum of zero and one") {
        REQUIRE(TestSum("0", "1") == "1");
    }

    SECTION("Sum of single digits") {
        REQUIRE(TestSum("3", "4") == "7");
    }

    SECTION("Sum of single digits with carry") {
        REQUIRE(TestSum("999999990", "10") == "1000000000");
    }

    SECTION("Sum of value bigger than base and zero") {
        REQUIRE(TestSum("12345678912", "0") == "12345678912");
    }

    SECTION("Sum of double digits") {
        REQUIRE(TestSum("12345678912345", "123456789123456") == "135802468035801");
    }

    SECTION("Sum of double digits with carry") {
        REQUIRE(TestSum("123456789123456789", "876543210876543211") == "1000000000000000000");
    }
}

TEST_CASE("equal", "[compare][equal][input]") {
    SECTION("Equal zeros") {
        REQUIRE(TestCmp("0", "0", EQUAL) == true);
    }

    SECTION("One and zero equal") {
        REQUIRE(TestCmp("0", "1", EQUAL) == false);
    }

    SECTION("Single digit, true") {
        REQUIRE(TestCmp("123456789", "123456789", EQUAL) == true);
    }

    SECTION("Single digit, false") {
        REQUIRE(TestCmp("123456789", "123456787", EQUAL) == false);
    }

    SECTION("Double digits, true") {
        REQUIRE(TestCmp("123456789123456789", "123456789123456789", EQUAL) == true);
    }

    SECTION("Double digit, false") {
        REQUIRE(TestCmp("123456789123456789", "123456787123456789", EQUAL) == false);
    }

    SECTION("Different sizes, false") {
        REQUIRE(TestCmp("123456789", "1234", EQUAL) == false);
    }
}

TEST_CASE("less", "[compare][less][input]") {
    SECTION("Zeros less") {
        REQUIRE(TestCmp("0", "0", LESS) == false);
    }

    SECTION("One and zero less") {
        REQUIRE(TestCmp("0", "1", LESS) == true);
    }

    SECTION("One digit, true") {
        REQUIRE(TestCmp("3", "4", LESS) == true);
    }

    SECTION("One digit, false") {
        REQUIRE(TestCmp("7", "4", LESS) == false);
    }

    SECTION("Two digits, true") {
        REQUIRE(TestCmp("123456789123456787", "123456789123456789", LESS) == true);
    }

    SECTION("Two digits, false") {
        REQUIRE(TestCmp("123456789123456787", "123456789123456781", LESS) == false);
    }

    SECTION("Different sizes, true") {
        REQUIRE(TestCmp("123456789", "123456789123456781", LESS) == true);
    }

    SECTION("Different sizes, false") {
        REQUIRE(TestCmp("123456789123456781", "123456789", LESS) == false);
    }

}

TEST_CASE("more", "[compare][more][input]") {
    SECTION("Zeros more") {
        REQUIRE(TestCmp("0", "0", MORE) == false);
    }

    SECTION("One and zero more") {
        REQUIRE(TestCmp("0", "1", MORE) == false);
    }

    SECTION("One digit, true") {
        REQUIRE(TestCmp("4", "1", MORE) == true);
    }

    SECTION("One digit, false") {
        REQUIRE(TestCmp("4", "5", MORE) == false);
    }

    SECTION("Two digits, true") {
        REQUIRE(TestCmp("123456789123456789", "123456787123456787", MORE) == true);
    }

    SECTION("Two digits, false") {
        REQUIRE(TestCmp("123456689123456789", "123456787123456787", MORE) == false);
    }

    SECTION("Different sizes, true") {
        REQUIRE(TestCmp("123456789123456781", "123456789", MORE) == true);
    }

    SECTION("Different sizes, false") {
        REQUIRE(TestCmp("123456789", "123456789123456781", MORE) == false);
    }

}

TEST_CASE("sub", "[sub]") {
    SECTION("Two zeros") {
        REQUIRE(TestSub("0", "0") == "0");
    }

    SECTION("One and zero") {
        REQUIRE(TestSub("1", "0") == "1");
    }

    SECTION("Zero and one") {
        REQUIRE(TestSub("0", "1") == "Error");
    }

    SECTION("Attempt to get negative value") {
        REQUIRE(TestSub("3", "5") == "Error");
    }

    SECTION("Leading zeroes") {
        REQUIRE(TestSub("123456789", "123456780") == "9");
    }

    SECTION("Two equal values") {
        REQUIRE(TestSub("123456789", "123456789") == "0");
    }

    SECTION("Single digits") {
        REQUIRE(TestSub("123456", "156") == "123300");
    }

    SECTION("Double digits") {
        REQUIRE(TestSub("123456789123456789", "113355779022446688") == "10101010101010101");
    }

    SECTION("Double and single digits") {
        REQUIRE(TestSub("123456789123456789", "123456789") == "123456789000000000");
    }

    SECTION("Leading zeros from double") {
        REQUIRE(TestSub("123456789123456789", "123456789123456780") == "9");
    }

}

TEST_CASE("Mult", "[mult]") {
    SECTION("Two zeros") {
        REQUIRE(TestMult("0", "0") == "0");
    }

    SECTION("One and zero") {
        REQUIRE(TestMult("1", "0") == "0");
    }

    SECTION("Very long and zero") {
        REQUIRE(TestMult("1234567891", "0") == "0");
    }

    SECTION("Very long and one") {
        REQUIRE(TestMult("1234567891", "1") == "1234567891");
    }

    SECTION("Zero and one") {
        REQUIRE(TestMult("0", "1") == "0");
    }

    SECTION("Zero and very long") {
        REQUIRE(TestMult("0", "1234567891") == "0");
    }

    SECTION("One and very long") {
        REQUIRE(TestMult("1", "1234567891") == "1234567891");
    }

    SECTION("Two single digits") {
        REQUIRE(TestMult("5", "7") == "35");
    }

    SECTION("Double digit and single digit") {
        REQUIRE(TestMult("123456789123456789", "7") == "864197523864197523");
    }

    SECTION("Double digit and double digit") {
        REQUIRE(TestMult("1234567891", "2345678912") == "2895899867351014592");
    }

}

TEST_CASE("Div", "[div]") {
    SECTION("Two zeros") {
        REQUIRE(TestDiv("0", "0") == "Error");
    }

    SECTION("One by zero") {
        REQUIRE(TestDiv("1", "0") == "Error");
    }

    SECTION("Zero by one") {
        REQUIRE(TestDiv("0", "1") == "0");
    }

    SECTION("Zero by long") {
        REQUIRE(TestDiv("0", "1234567891") == "0");
    }

    SECTION("Long by one") {
        REQUIRE(TestDiv("1234567891", "1") == "1234567891");
    }

    SECTION("Digit by digit") {
        REQUIRE(TestDiv("6", "3") == "2");
    }

    SECTION("Two digits by two digits") {
        REQUIRE(TestDiv("28958998625361999", "123456789") == "234567891");
    }

    SECTION("Three digits by two digits") {
        REQUIRE(TestDiv("1524157876543126160205", "12345678912345") == "123456789");
    }

}

TEST_CASE("power", "[power]") {
    SECTION("Zero to zero") {
        REQUIRE(TestPower("0", "0") == "Error");
    }

    SECTION("Zero to five") {
        REQUIRE(TestPower("0", "5") == "0");
    }

    SECTION("Five to zero") {
        REQUIRE(TestPower("5", "0") == "1");
    }

    SECTION("Five to one") {
        REQUIRE(TestPower("5", "1") == "5");
    }

    SECTION("Single digit to second") {
        REQUIRE(TestPower("5", "2") == "25");
    }

    SECTION("Single digit to third") {
        REQUIRE(TestPower("5", "3") == "125");
    }

    SECTION("Double digit to second") {
        REQUIRE(TestPower("1234567891", "2") == "1524157877488187881");
    }

    SECTION("Double digit to third") {
        REQUIRE(TestPower("1234567891", "3") == "1881676376361628489657928971");
    }

    SECTION("Single digit to eighth") {
        REQUIRE(TestPower("3", "8") == "6561");
    }

    SECTION("Single digit to ninth") {
        REQUIRE(TestPower("3", "9") == "19683");
    }

}
