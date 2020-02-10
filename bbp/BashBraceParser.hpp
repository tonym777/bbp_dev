#ifndef BASHBRACEPARSER_H_
#define BASHBRACEPARSER_H_

#include <bits/stdc++.h>

using namespace std;

string BashBraceParse(string expression);

class BashBraceParserException : public exception {
public:
	string _s;
	BashBraceParserException(string desc) :_s(desc) {}
	~BashBraceParserException() throw() {}
	virtual const char * what () const throw () { return _s.c_str(); }
};

class BashBraceParser
{
private:
	string 	_expression;
    size_t 	_nextCharIndex;

public:
    list<string>  Parse(string expression);
    list<string>  ParseExpression();

private:
    list<string>  ParseComponent();
    list<string>  ParseComponentPart();
    list<string>  Combine(list<string> left, list<string> right);

    char Peek();
    char ReadNextChar();
    void UnreadChar();
    bool isEof();
    string ReadLetters();

};

#endif  // BASHBRACEPARSER_H_
