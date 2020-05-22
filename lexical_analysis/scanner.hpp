//
// Created by FancyKing on 2020/3/30.
//

#ifndef COMPILEREXPERIMENT_SCANNER_H
#define COMPILEREXPERIMENT_SCANNER_H

#endif //COMPILEREXPERIMENT_SCANNER_H

#pragma once

#include <bits/stdc++.h>

using namespace std;
/*
 * against refactor
const int IDENTIFIER = 0;
const int COMMENT    = 1;
const int DIGIT      = 2;
const int STRING     = 3;
const int BOOLEAN    = 4;
const int LITERAL    = 5;
const int KEYWORD    = 6;
const int STATEMENT  = 7;
const int OPERATOR   = 8;
const int SEPARATOR  = 9;
const int NOT_LEGAL  = 10;
 */

const int IDENTIFIER = 0;
const int COMMENT    = 1;
const int DIGIT      = 2;
const int STRING     = 3;
const int BOOLEAN    = 4;
const int LITERAL    = 5;
const int KEYWORD    = 6;
const int STATEMENT  = 7;
const int OPERATOR   = 8;
const int SEPARATOR  = 9;
const int NOT_LEGAL  = 10;
const int HEADER     = 11;

const static map<string, int> mapper{
        {"IDENTIFIER", 0},
        {"COMMENT",    1},
        {"DIGIT",      2},
        {"STRING",     3},
        {"BOOLEAN",    4},
        {"LITERAL",    5},
        {"KEYWORD",    6},
        {"STATEMENT",  7},
        {"OPERATOR",   8},
        {"SEPARATOR",  9},
        {"NOT_LEGAL",  10},
        {"HEADER",     11}
};

bool isInDictionary(const vector<string> &dict, const string& key);

bool isIdentifier(const string &str);

bool isComment(const string &str);

bool isDigit(const string &str);

bool isString(const string &str);

bool isBool(const string &str);

bool isLiteral(const string &str);

bool isKeyword(const string &str);

bool isStatement(const string &str);

bool isOperator(const string &str);

bool isSeparator(const string &str);

bool isNotLegal(const string &str);

void printRoleOfToken(const string &tokens);

void lexicalAnalyze(const string &nameOfFile);