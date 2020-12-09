#include "parser.h"

bool Parser::calculation() 
	{
		Stack<double> stack; double a,b; double c=0.0;
		bool res=true;
		for (size_t i=0; i<polish_notation.size(); i++)
		{
		switch (polish_notation[i]->GetType())
		{
		case type_lexem::NUMBER:
			stack.push(polish_notation[i]->GetValue());
		    break;
		case type_lexem::OPERATOR:
			a=stack.top();
			stack.pop();
			b=stack.top();
			stack.pop();
			switch (static_cast<int>(polish_notation[i]->GetValue()))
			{
			case operation::PLUS:
				c=b+a;
				stack.push(c);
				break;
			case operation::MINUS:
				c=b-a;
				stack.push(c);
				break;
			case operation::MULT:
				c=b*a;
				stack.push(c);
				break;
			case operation::DIV:
				if (a==0)
					res=false;
				else
					{ 
						c=b/a;
						stack.push(c);
				}
				break;
			}
			break;
		}
	}
		result=c;
		return res;
	};

bool Parser::lexical_analysis()
{
	bool f=false; bool analysis_result=true;
	std::string new_number;
	size_t idx;
	double num;
	for (size_t i=0; i<str.length(); i++)
	{
		idx=0;
	    switch (f)
	    {
	        case false:
		    switch (str[i])
		    {
		       case '+':
			        lexems.push_back(new Operator(operation::PLUS));
			        break;
		       case '-':
			        lexems.push_back(new Operator(operation::MINUS));
		            break;
		       case '*':
			        lexems.push_back(new Operator(operation::MULT));
			        break;
		       case '/':
			        lexems.push_back(new Operator(operation::DIV));
			        break;
		       case '(':
			        lexems.push_back(new Bracket(bracket::OPEN_BRACKET));
			        break;
		       case ')':
			        lexems.push_back(new Bracket(bracket::CLOSE_BRACKET));
			        break;
			   case '0':
			   case '1':
			   case '2':
			   case '3':
			   case '4':
			   case '5':
			   case '6':
			   case '7':
			   case '8':
			   case '9':
				    new_number.clear();
					new_number+=str[i];
					f=true;
					break;
			   case '=':
				   break;
			   default:
					analysis_result=false;
					break;
			}
			break;
			case true:
				switch (str[i])
				{
					case '+':
					     num=std::stod(new_number, &idx);
					     if (idx!=new_number.length()) analysis_result=false;
					     else {
							 lexems.push_back(new Number(num));	
					         lexems.push_back(new Operator(operation::PLUS));
					         f=false;
						 }
			             break;
		            case '-':
				          num=std::stod(new_number, &idx);
					      if (idx!=new_number.length()) analysis_result=false;
						  else {
					            lexems.push_back(new Number(num));	
			                    lexems.push_back(new Operator(operation::MINUS));
					            f=false;
						  }
		                  break;
		            case '*':
			 	         num=std::stod(new_number, &idx);
					     if (idx!=new_number.length()) analysis_result=false;
						 else {
					          lexems.push_back(new Number(num));	
			                  lexems.push_back(new Operator(operation::MULT));
					          f=false;
						 }
			             break;
		            case '/':
				         num=std::stod(new_number, &idx);
					     if (idx!=new_number.length()) analysis_result=false;
						 else {
					          lexems.push_back(new Number(num));	
			                  lexems.push_back(new Operator(operation::DIV));
					          f=false;
						 }
			             break;
		            case '(':
				         num=std::stod(new_number, &idx);
					     if (idx!=new_number.length()) analysis_result=false;
						 else {
					          lexems.push_back(new Number(num));	
			                  lexems.push_back(new Bracket(bracket::OPEN_BRACKET));
					          f=false;
						 }
			             break;
		            case ')':
				         num=std::stod(new_number, &idx);
					    if (idx!=new_number.length()) analysis_result=false;
						 else {
					          lexems.push_back(new Number(num));	
			                  lexems.push_back(new Bracket(bracket::CLOSE_BRACKET));
					          f=false;
						 }
			             break;
					case '0':
					case '1':
					case '2':
					case '3':
					case '4':
					case '5':
					case '6':
					case '7':
					case '8':
					case '9':
					case '.':
					     new_number+=str[i];
					     break;
					case '=':
						 num=std::stod(new_number, &idx);
					     if (idx!=new_number.length()) analysis_result=false;
						 else {
					          lexems.push_back(new Number(num));
					          f=false;
						 }
			             break;
				    default:
				         analysis_result=false;
				}
				break;
	}
 }
  return analysis_result;
}

bool Parser::are_brackets_good()
{
	bool syntax_result=true;
	Stack<Term*> stack;
	for (size_t i=0; i<lexems.size(); i++)
	{
		if ((lexems[i]->GetType()==type_lexem::BRACKET)&&(lexems[i]->GetValue()==bracket::OPEN_BRACKET))
			stack.push(lexems[i]);
		else
			if ((lexems[i]->GetType()==type_lexem::BRACKET)&&(lexems[i]->GetValue()==bracket::CLOSE_BRACKET))
			{
				if (!stack.empty())
					stack.pop();
				else 
			    {
						syntax_result=false;
						break;
				}
			}
	}
	if (!stack.empty()) 
		syntax_result=false;
	return syntax_result;
}

bool Parser::syntax_analysis()
{
	bool syntax_result=true;
	if (!are_brackets_good())
		syntax_result=false;
	else {
	    for (size_t i=0; i<lexems.size()-1; i++)
		{
			switch (lexems[i]->GetType())
			{
			case type_lexem::NUMBER:
				if (!(((lexems[i+1]->GetType()==type_lexem::BRACKET)&&\
					(lexems[i+1]->GetValue()==bracket::CLOSE_BRACKET))\
					||(lexems[i+1]->GetType()==type_lexem::OPERATOR)))
				syntax_result=false;
				break;
			case type_lexem::OPERATOR:
				if (!(((lexems[i+1]->GetType()==type_lexem::BRACKET)&&\
					(lexems[i+1]->GetValue()==bracket::OPEN_BRACKET))\
					||(lexems[i+1]->GetType()==type_lexem::NUMBER)))
				syntax_result=false;
				break;
			case type_lexem::BRACKET:
				if (lexems[i]->GetValue()==bracket::OPEN_BRACKET)
					{ if (!(((lexems[i+1]->GetType()==type_lexem::BRACKET)&&\
						(lexems[i+1]->GetValue()==bracket::OPEN_BRACKET))\
				    ||(lexems[i+1]->GetType()==type_lexem::NUMBER)))
					syntax_result=false;
				}
				else
					if (!(((lexems[i+1]->GetType()==BRACKET)&&\
						(lexems[i+1]->GetValue()==bracket::CLOSE_BRACKET))\
					||(lexems[i+1]->GetType()==type_lexem::OPERATOR)))
				     syntax_result=false;
				break;
			}
			if (!syntax_result) break;
		}
	}
	return syntax_result;
}

void Parser::convert_to_polish()
{
	Stack<Term*> stack;
	for (size_t i=0; i<lexems.size(); i++)
	{
		switch (lexems[i]->GetType())
		{
		case type_lexem::NUMBER:
			polish_notation.push_back(lexems[i]);
			break;
		case type_lexem::BRACKET:
			if (lexems[i]->GetValue()==bracket::OPEN_BRACKET)
				stack.push(lexems[i]);
			else {
				while (!((stack.top()->GetType()==type_lexem::BRACKET)&&\
					(stack.top()->GetValue()==bracket::OPEN_BRACKET)))
				{
			       polish_notation.push_back(stack.top());
				   stack.pop();
				}
				stack.pop();
			}
			break;
		case type_lexem::OPERATOR:
			if (stack.empty()) stack.push(lexems[i]);
			else {
				if (stack.top()->GetType()!=type_lexem::OPERATOR)
					stack.push(lexems[i]);
				else {
						while ((!stack.empty())&&(stack.top()->GetType()==type_lexem::OPERATOR)&&\
							(((Operator*)(stack.top()))->GetPriority()>=((Operator*)(lexems[i]))->GetPriority()))
						 {
							 polish_notation.push_back(stack.top());
							 stack.pop();
						 }
						 stack.push(lexems[i]);
					 }
			}
			break;
	}
	}
	while (!stack.empty())
	{
		polish_notation.push_back(stack.top());
		stack.pop();
	}
}

