#include "parser.h"
#include <gtest.h>

TEST(TParser, throw_when_invalid_symbol)
{
	std::string s="2*3!=";
	Parser p(s);
	ASSERT_ANY_THROW(p.compute());
}

TEST(TParser, throw_if_impossible_to_convert_to_number)
{
	std::string s="1.04.6=";
	Parser p(s);
	ASSERT_ANY_THROW(p.compute());
}

TEST(TParser, throw_if_impossible_to_convert_to_number_2)
{
	std::string s=".046=";
	Parser p(s);
	ASSERT_ANY_THROW(p.compute());
}

TEST(TParser, throw_if_too_many_close_brackets)
{
	std::string s="(2+3))=";
	Parser p(s);
	ASSERT_ANY_THROW(p.compute());
}

TEST(TParser, throw_if_too_many_open_brackets)
{
	std::string s="((2+3)=";
	Parser p(s);
	ASSERT_ANY_THROW(p.compute());
}

TEST(TParser, throw_if_after_open_bracket_an_operator)
{
	std::string s="(/8)=";
	Parser p(s);
	ASSERT_ANY_THROW(p.compute());
}

TEST(TParser, throw_if_after_open_bracket_a_close_bracket)
{
	std::string s="()=";
	Parser p(s);
	ASSERT_ANY_THROW(p.compute());
}

TEST(TParser, throw_if_after_close_bracket_an_open_bracket)
{
	std::string s="(2+1)(3*3)=";
	Parser p(s);
	ASSERT_ANY_THROW(p.compute());
}

TEST(TParser, throw_if_after_close_bracket_a_number)
{
	std::string s="(8-5)7=";
	Parser p(s);
	ASSERT_ANY_THROW(p.compute());
}

TEST(TParser, throw_if_after_number_an_open_bracket)
{
	std::string s="8(1+1)=";
	Parser p(s);
	ASSERT_ANY_THROW(p.compute());
}

TEST(TParser, throw_if_after_operator_a_close_bracket)
{
	std::string s="(8+)=";
	Parser p(s);
	ASSERT_ANY_THROW(p.compute());
}

TEST(TParser, throw_if_after_operator_an_operator)
{
	std::string s="++=";
	Parser p(s);
	ASSERT_ANY_THROW(p.compute());
}

TEST(TParser, throw_if_divided_by_zero)
{
	std::string s="2/0=";
	Parser p(s);
	ASSERT_ANY_THROW(p.compute());
}

TEST(TParser, can_add)
{
	std::string s="2+4=";
	Parser p(s);
	EXPECT_EQ(6, p.compute());
}

TEST(TParser, can_subtract)
{
	std::string s="2-4=";
	Parser p(s);
	EXPECT_EQ(-2, p.compute());
}

TEST(TParser, can_multiply)
{
	std::string s="2*4=";
	Parser p(s);
	EXPECT_EQ(8, p.compute());
}

TEST(TParser, can_divide)
{
	std::string s="2/4=";
	Parser p(s);
	EXPECT_EQ(0.5, p.compute());
}

TEST(TParser, calculate_with_brackets_correctly)
{
	std::string s="4*(5-3)=";
	Parser p(s);
	EXPECT_EQ(8, p.compute());
}

TEST(TParser, calculate_correctly_if_priority_is_different)
{
	std::string s="9-7/2=";
	Parser p(s);
	EXPECT_EQ(5.5, p.compute());
}

TEST(TParser, main_test)
{
	std::string s="(2.5+4*5)/12-4*2+3=";
	Parser p(s);
	EXPECT_EQ(-3.125, p.compute());
}
