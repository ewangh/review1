#pragma once
#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <cmath>
#include <vector>

bool isOperator(const char);

bool isOperator(const std::string &);

int getPriority(const char);

bool checkParentheses(const std::string&);

std::vector<std::string> infixToPostfix(const std::string &);