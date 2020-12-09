#pragma once
#include "stack.h"
#include <vector>
#include <string>

enum operation { PLUS, MINUS, MULT, DIV };
enum type_lexem {NUMBER, OPERATOR, BRACKET};
enum bracket { OPEN_BRACKET, CLOSE_BRACKET };

class Term {
protected:
	int type;
	double value;
public:
	int GetType() { return type; };
	double GetValue() { return value; };
	virtual void print()=0;
};
class Number: public Term {
public:
	Number(double s) { type=type_lexem::NUMBER; value=s; };
	void print() { std::cout<<value<<" "; };
};
class Operator: public Term {
public:
	Operator(double s) {  type=type_lexem::OPERATOR; value=s; };
	int GetPriority() 
	{ if ((GetValue()==operation::MULT)||(GetValue()==operation::DIV))
		return 1;
	  else return 0;
	}
	void print() 
	{ 
		if (value==operation::PLUS) std::cout<<"+ ";
		if (value==operation::MINUS) std::cout<<"- ";
		if (value==operation::MULT) std::cout<<"* ";
		if (value==operation::DIV) std::cout<<"/ ";
	}
};
class Bracket: public Term {
public:
	Bracket(double s) { type=type_lexem::BRACKET; value=s; };
	void print()
	{
		if (value==bracket::OPEN_BRACKET) std::cout<<"( ";
		if (value==bracket::CLOSE_BRACKET) std::cout<<") ";
	}
};
class Parser {
protected:
	std::string str;
	std::vector <Term*> lexems;
	std::vector <Term*> polish_notation;
	double result;
	bool lexical_analysis();
	bool are_brackets_good();
	bool syntax_analysis();
	void convert_to_polish();
	bool calculation();
public:
	Parser(std::string s) { str=s; };
	double compute()
	{
		if (!lexical_analysis())
			throw std::logic_error("Impossible to convert expression to lexems");
		if (!syntax_analysis())
			throw std::logic_error("Invalid lexems placement");
		convert_to_polish();
		if (!calculation())
			throw std::logic_error("Calculation error");
		return result;
	}
};