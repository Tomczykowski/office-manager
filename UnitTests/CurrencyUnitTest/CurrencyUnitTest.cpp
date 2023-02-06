#include <gtest/gtest.h>
#include "Currency.h"
#include <sstream>


TEST(CurrencyUnitTest, emptyConstructor){
    Currency a;
    ASSERT_EQ(a.gr, 0);
    ASSERT_EQ(a.zl, 0);
}

TEST(CurrencyUnitTest, plusEqualOperator){
    Currency a, b;
    a.gr = 4;
    a.zl = 10;
    b.gr = 97;
    b.zl = 4;
    a += b;
    ASSERT_EQ(a.zl, 15);
    ASSERT_EQ(a.gr, 1);
}

TEST(CurrencyUnitTest, plusEqualOperator2){
    Currency a, b;
    a.gr = 4;
    a.zl = 10;
    a += b;
    ASSERT_EQ(a.zl, 10);
    ASSERT_EQ(a.gr, 4);
}

TEST(CurrencyUnitTest, minusEqualOperator){
    Currency a, b;
    a.gr = 4;
    a.zl = 10;
    b.gr = 97;
    b.zl = 4;
    a -= b;
    ASSERT_EQ(a.zl, 5);
    ASSERT_EQ(a.gr, 7);
}

TEST(CurrencyUnitTest, minusEqualOperatorEmpty){
    Currency a, b;
    a.gr = 4;
    a.zl = 10;
    a -= b;
    ASSERT_EQ(a.zl, 10);
    ASSERT_EQ(a.gr, 4);
}

TEST(CurrencyUnitTest, minusEqualOperatorThrow){
    Currency a, b;
    a.gr = 4;
    a.zl = 10;
    b.zl = 10;
    b.gr = 5;
    ASSERT_THROW( a -= b, std::invalid_argument);
}

TEST(CurrencyUnitTest, lessOperator){
    Currency a, b;
    a.gr = 4;
    a.zl = 10;
    b.zl = 10;
    b.gr = 5;
    ASSERT_TRUE(a < b);
}

TEST(CurrencyUnitTest, graterOperator){
    Currency a, b;
    a.gr = 4;
    a.zl = 11;
    b.zl = 10;
    b.gr = 5;
    ASSERT_TRUE(a > b);
}

TEST(CurrencyUnitTest, equalOperator){
    Currency a, b;
    a.gr = 5;
    a.zl = 10;
    b.zl = 10;
    b.gr = 5;
    ASSERT_TRUE(a == b);
}

TEST(CurrencyUnitTest, notEqualOperator){
    Currency a, b;
    a.gr = 5;
    a.zl = 10;
    b.zl = 10;
    b.gr = 3;
    ASSERT_TRUE(a != b);
}

TEST(CurrencyUnitTest, multiplyOperator){
    Currency a;
    a.gr = 5;
    a.zl = 10;
    Currency b = a * 2;
    ASSERT_EQ(b.zl, 20);
    ASSERT_EQ(b.gr, 10);
}

TEST(CurrencyUnitTest, ostreamOperator){
    Currency a;
    a.gr = 5;
    a.zl = 10;
    stringstream str;
    str << a;
    ASSERT_EQ(str.str(), "10 zl 5 gr");
}

TEST(CurrencyUnitTest, ostreamOperator2){
    Currency a;
    stringstream str;
    str << a;
    ASSERT_EQ(str.str(), "0 zl 0 gr");
}