//**************************************
// parse.cpp
//
// Starting point for top-down recursive-descent parser
// Used in CST 320 Lab2
//
// Author: Phil Howard 
// phil.howard@oit.edu
//
// Date: Nov. 23, 2015
//

#include <iostream>
#include "lex.h"
#include "parse.h"
#include "utils.h"
#include "tokens.h"

//*******************************************
// Find a PROG non-terminal
bool FindPROG()
{
    FindSTMTS();

    if (PeekToken() != END) return false;
    AdvanceToken();

    return true;
}

bool FindSTMTS()
{
    while (FindSTMT())
    {
        std::cout << "Found a statement" << std::endl;
    }

    // λ
    return true;
}

bool FindSTMT()
{
    if (!FindEXPR()) return false;

    if (PeekToken() != ';') return false;
    AdvanceToken();

    return true;
}

bool FindEXPR()
{
    // (EXPR) EXPR'
    if (PeekToken() == '(')
    {
        AdvanceToken();

        if (!FindEXPR()) return false;

        if (PeekToken() != ')') return false;
        AdvanceToken();

        if (!FindEXPR_P()) return false;
    }
    // TERM
    else
    {
        if (!FindTERM()) return false;
    }

    return true;
}

bool FindEXPR_P()
{
    // PLUSOP (EXPR) EXPR’
    if (FindPLUSOP())
    {
        if (PeekToken() != '(') return false;
        AdvanceToken();

        if (!FindEXPR()) return false;

        if (PeekToken() != ')') return false;
        AdvanceToken();

        if (!FindEXPR_P()) return false;
    }

    // λ
    return true;
}

bool FindPLUSOP()
{
    int token = PeekToken();
    if (!(token == '+' || token == '-')) return false;
    AdvanceToken();

    return true;
}

bool FindTERM()
{
    // [EXPR] TERM’
    if (PeekToken() == '[')
    {
        AdvanceToken();

        if (!FindEXPR()) return false;

        if (PeekToken() != ']') return false;
        AdvanceToken();

        if (!FindTERM_P()) return false;
    }
    // num
    else
    {
        if (PeekToken() != NUM) return false;
        AdvanceToken();
    }

    return true;
}

bool FindTERM_P()
{
    // TIMESOP [EXPR] TERM’
    if (FindTIMESOP())
    {
        if (PeekToken() != '[') return false;
        AdvanceToken();

        if (!FindEXPR()) return false;

        if (PeekToken() != ']') return false;
        AdvanceToken();

        if (!FindTERM_P()) return false;
    }
    // λ
    else
    {
        if (PeekToken() != ';') return false;
    }

    return true;
}

bool FindTIMESOP()
{
    int token = PeekToken();
    if (!(token == '*' || token == '/')) return false;
    AdvanceToken();

    return true;
}

