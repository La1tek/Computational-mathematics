#include <gtest/gtest.h>
#include <cmath>
#include <sstream>
#include "../src/DualNumbers.h"
#include "../src/DualNumbersMath.h"

using namespace dual;

constexpr float PI = 3.14159265358979323846f;

TEST(DualNumbersTest, ConstructorAndGetters) {
    DualNumbers a(3.0f, 2.0f);
    EXPECT_FLOAT_EQ(a.real(), 3.0f);
    EXPECT_FLOAT_EQ(a.dual(), 2.0f);

    DualNumbers b(5.0f);
    EXPECT_FLOAT_EQ(b.real(), 5.0f);
    EXPECT_FLOAT_EQ(b.dual(), 0.0f);
}

TEST(DualNumbersTest, Setters) {
    DualNumbers a(0.0f, 0.0f);
    a.real(7.0f);
    a.dual(4.0f);
    EXPECT_FLOAT_EQ(a.real(), 7.0f);
    EXPECT_FLOAT_EQ(a.dual(), 4.0f);
}

TEST(DualNumbersTest, Addition) {
    DualNumbers a(3.0f, 2.0f);
    DualNumbers b(1.0f, 5.0f);
    DualNumbers c = a + b;
    EXPECT_FLOAT_EQ(c.real(), 4.0f);
    EXPECT_FLOAT_EQ(c.dual(), 7.0f);
}

TEST(DualNumbersTest, Subtraction) {
    DualNumbers a(3.0f, 2.0f);
    DualNumbers b(1.0f, 5.0f);
    DualNumbers c = a - b;
    EXPECT_FLOAT_EQ(c.real(), 2.0f);
    EXPECT_FLOAT_EQ(c.dual(), -3.0f);
}

TEST(DualNumbersTest, Multiplication) {
    DualNumbers a(3.0f, 2.0f);
    DualNumbers b(4.0f, 5.0f);
    DualNumbers c = a * b;
    // (3 + 2e)(4 + 5e) = 12 + (3*5 + 2*4)e = 12 + 23e
    EXPECT_FLOAT_EQ(c.real(), 12.0f);
    EXPECT_FLOAT_EQ(c.dual(), 23.0f);
}

TEST(DualNumbersTest, Division) {
    DualNumbers a(6.0f, 4.0f);
    DualNumbers b(2.0f, 1.0f);
    DualNumbers c = a / b;
    // (6 + 4e) / (2 + 1e) = 3 + (4*2 - 6*1)/(2*2) e = 3 + (8 - 6)/4 e = 3 + 0.5e
    EXPECT_FLOAT_EQ(c.real(), 3.0f);
    EXPECT_FLOAT_EQ(c.dual(), 0.5f);
}

TEST(DualNumbersTest, EqualityOperators) {
    DualNumbers a(3.0f, 2.0f);
    DualNumbers b(3.0f, 2.0f);
    DualNumbers c(3.0f, 5.0f);
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
    EXPECT_TRUE(a != c);
}

TEST(DualNumbersTest, StreamOutput) {
    DualNumbers a(3.0f, 2.0f);
    std::ostringstream oss;
    a.operator<<(oss);
    EXPECT_EQ(oss.str(), "3 + 2e");
}

TEST(DualNumbersTest, StreamInput) {
    DualNumbers a(0.0f, 0.0f);
    std::istringstream iss("7 4");
    a.operator>>(iss);
    EXPECT_FLOAT_EQ(a.real(), 7.0f);
    EXPECT_FLOAT_EQ(a.dual(), 4.0f);
}

class DualMathTest : public ::testing::Test {
protected:
    void SetUp() override {
        x = DualNumbers(2.0f, 3.0f);
        y = DualNumbers(4.0f, 1.0f);
    }
    
    DualNumbers x, y;
};

TEST_F(DualMathTest, Exp) {
    DualNumbers result = exp(x);
    EXPECT_FLOAT_EQ(result.real(), std::exp(2.0f));
    EXPECT_FLOAT_EQ(result.dual(), std::exp(2.0f) * 3.0f);
    
    DualNumbers zero = DualNumbers(0.0f, 1.0f);
    DualNumbers result_zero = exp(zero);
    EXPECT_FLOAT_EQ(result_zero.real(), 1.0f);
    EXPECT_FLOAT_EQ(result_zero.dual(), 1.0f);
}

TEST_F(DualMathTest, Log) {
    DualNumbers result = log(x);
    EXPECT_FLOAT_EQ(result.real(), std::log(2.0f));
    EXPECT_FLOAT_EQ(result.dual(), 3.0f / 2.0f);
    
    DualNumbers one = DualNumbers(1.0f, 2.0f);
    DualNumbers result_one = log(one);
    EXPECT_FLOAT_EQ(result_one.real(), 0.0f);
    EXPECT_FLOAT_EQ(result_one.dual(), 2.0f);
}

TEST_F(DualMathTest, Sin) {
    DualNumbers result = sin(x);
    EXPECT_FLOAT_EQ(result.real(), std::sin(2.0f));
    EXPECT_FLOAT_EQ(result.dual(), std::cos(2.0f) * 3.0f);
    
    float pi_2 = PI / 2.0f;
    DualNumbers pi_2_dual = DualNumbers(pi_2, 1.0f);
    DualNumbers result_pi_2 = sin(pi_2_dual);
    EXPECT_NEAR(result_pi_2.real(), 1.0f, 1e-6f);
    EXPECT_NEAR(result_pi_2.dual(), 0.0f, 1e-6f);
}

TEST_F(DualMathTest, Cos) {
    DualNumbers result = cos(x);
    EXPECT_FLOAT_EQ(result.real(), std::cos(2.0f));
    EXPECT_FLOAT_EQ(result.dual(), -std::sin(2.0f) * 3.0f);
    
    float pi = PI;
    DualNumbers pi_dual = DualNumbers(pi, 1.0f);
    DualNumbers result_pi = cos(pi_dual);
    EXPECT_NEAR(result_pi.real(), -1.0f, 1e-6f);
    EXPECT_NEAR(result_pi.dual(), 0.0f, 1e-6f);
}

TEST_F(DualMathTest, Sqrt) {
    DualNumbers result = sqrt(y); // y = (4, 1)
    EXPECT_FLOAT_EQ(result.real(), 2.0f);
    EXPECT_FLOAT_EQ(result.dual(), 1.0f / (2.0f * 2.0f));
    
    DualNumbers one = DualNumbers(1.0f, 2.0f);
    DualNumbers result_one = sqrt(one);
    EXPECT_FLOAT_EQ(result_one.real(), 1.0f);
    EXPECT_FLOAT_EQ(result_one.dual(), 2.0f / (2.0f * 1.0f));
}

TEST_F(DualMathTest, FunctionComposition) {
    DualNumbers sin_x = sin(x);
    DualNumbers exp_sin_x = exp(sin_x);
    
    float real_expected = std::exp(std::sin(2.0f));
    float dual_expected = real_expected * std::cos(2.0f) * 3.0f;
    
    EXPECT_FLOAT_EQ(exp_sin_x.real(), real_expected);
    EXPECT_FLOAT_EQ(exp_sin_x.dual(), dual_expected);
}