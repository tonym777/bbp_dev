
#include "BashBraceParser.hpp"

using namespace std;

string BashBraceParse(string expression) {

	BashBraceParser parser;

	try {
		list<string> l = parser.Parse(expression);
		string result;
		for (auto s : l)  {
			if (result.length() == 0)
				result = s;
			else
				result = result + " " + s;
		}
		return result;
	}
	catch (BashBraceParserException e)  {
		return e.what();
	}

}

list<string> BashBraceParser::Parse(string expression) {
    _expression = expression;
    _nextCharIndex = 0;

    return ParseExpression();
}

list<string> BashBraceParser::ParseExpression() {

	list<string> result;

	if (_expression.find("{") == string::npos && _expression.find("}") == string::npos  &&
		_expression.find(",") == string::npos) {
		result.emplace_back(_expression);
		return result;
	}

    while (!isEof())
    {
        // Parsing a component will produce a list of strings,
        // they are added to the final string list

    	list<string> items = ParseComponent();

    	for (auto item : items)
    		result.emplace_back(item);

        // If next char is ',' simply skip it and parse next component
    	char nextChar = Peek();
        if (nextChar == ',')
        {
            // Skip comma
            ReadNextChar();
        }
        else if (nextChar == '\0' || nextChar == '}')
        {
            break;
        }
        else  {
        	BashBraceParserException e("Invalid Format");
        	throw e;
        }
    }
    if (result.size() == 0)  {
    	BashBraceParserException e("Invalid Format");
    	throw e;
    }
    return result;
}

list<string> BashBraceParser::ParseComponent() {

    list<string> leftItems;

    while (!isEof())
    {
    	list<string> rightItems = ParseComponentPart();
        if (rightItems.empty() == true)
        {
            break;
        }

        if (leftItems.empty() == true)
        {
            leftItems = rightItems;
        }
        else
        {
            leftItems = Combine(leftItems, rightItems);
        }
    }

    return leftItems;
}

list<string> BashBraceParser::ParseComponentPart() {

	list<string> items;
	char nextChar = Peek();

	if (nextChar == '{')
	{
	    // Skip '{'
	    ReadNextChar();

	    // Recursively parse the inner expression
	    items = ParseExpression();

	    // Skip '}'
	    if (ReadNextChar() != '}')  {
        	BashBraceParserException e("Invalid Format");
        	throw e;
	    }

	    return items;
	}
	else if (isalpha(nextChar) &&  _nextCharIndex != 0)
	{
	    string letters = ReadLetters();

	    items.emplace_back(letters);
	}

	return items;
}

list<string> BashBraceParser::Combine(list<string> left, list<string> right) {

	list<string>  result;

	for (auto leftItem : left)
	{
		for (auto rightItem : right)
	    {
			result.emplace_back(leftItem + rightItem);
	    }
	}

	return result;
}

char BashBraceParser::Peek() {

    if (isEof())
    {
        return '\0';
    }

    return _expression[_nextCharIndex];
}

char BashBraceParser::ReadNextChar(){
	return _expression[_nextCharIndex++];
}

void BashBraceParser::UnreadChar() {
	_nextCharIndex--;
}

bool BashBraceParser::isEof()  {
	if (_nextCharIndex == _expression.length())
		return true;
	else
		return false;
}

string BashBraceParser::ReadLetters() {

    string str;

    if (!isalpha(Peek()))
     {
         return str;
     }

     while (!isEof())
     {
         char ch = ReadNextChar();
         if (isalpha(ch))
         {
             str += ch;
         }
         else
         {
             UnreadChar();
             break;
         }
     }

     return str;
}

