#include <iostream>
#include <fstream>
#include <regex>
#include "dictionary.hpp"
#include "radomStr.h"
#include "bean.hpp"
#include "evaluate.h"
// #include "http_request.h"

// class AAA
// {
// public:
//     AAA(int d) : a(d), b(d), c(d), f(d), g(d){};
//     AAA(int d1, int d2) : a(d1), b(d2), c(d2), f(d2), g(d2){};
//     AAA &getSize() { return *this; }
//     int a, b, c, f, g, h;
// };

#define D_ZT "zt"
#define D_LBRACKET "===============["
#define D_RBRACKET "]==============="
#define D_PATH "../file/"
#define D_REGEX R"(\d{6})" //"\\d{6}"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__) || _WIN64
#define D_TXT_EXTENSION ".txt"
#else
#define D_TXT_EXTENSION
#endif

std::vector<std::string> getQueue(const std::string &file, Dictionary<std::string, std::string> &myDict)
{
    std::vector<std::string> tempq;

    if (myDict.containsKey(file))
    {
        tempq = myDict.findValues(file);
    }
    else
    {
        std::string fileName = file;

        if (file.size() <= 4 || file.substr(file.length() - 4) != D_TXT_EXTENSION)
        {
            fileName += D_TXT_EXTENSION;
        }

        tempq = getMatchingElements<std::string>(D_PATH + fileName, D_REGEX);

        if (fileName.size() > 2 && fileName.substr(0, 2) == D_ZT)
        {
            auto subKey = file.substr(2);

            if (myDict.containsSubKey(subKey))
            {
                myDict.updateSubKey(subKey, tempq);
            }
            else
            {
                myDict.addSubKey(subKey, tempq);
            }
        }
    }

    return tempq;
}

int main(int argc, char *argv[])
{
    Dictionary<std::string, std::string> myDict;
    std::string input;
    Bean<std::string> *bean;

    while (1)
    {
        std::cout << "Keys :";
        std::getline(std::cin, input);

        input.erase(std::remove_if(input.begin(), input.end(), ::isspace), input.end());

        if (input.empty())
        {
            continue;
        }

        if (myDict.containsKey(input))
        {
            std::cout << D_LBRACKET << input << D_RBRACKET << std::endl;
            myDict.printKey(input);
            std::cout << D_LBRACKET << input << D_RBRACKET << std::endl;

            continue;
        }

        std::vector<std::string> postfix;

        try
        {
            postfix = infixToPostfix(input);

#ifdef DEBUG
            for (auto item : postfix)
            {
                std::cout << item << " | ";
            }
            std::cout << std::endl;
#endif
        }
        catch (const char *errorMessage)
        {
            std::cerr << errorMessage << std::endl;
            continue;
        }

        if (postfix.empty())
        {
            throw "error 0: There must be something wrong in this!!!";
        }
        std::vector<std::string> queue;

        if (postfix.size() == 1 && !isOperator(postfix.front()))
        {
            std::string fileName = postfix.front();
            queue = getQueue(fileName, myDict);
        }
        else
        {
            std::stack<std::string> splitted;

            for (const auto &item : postfix)
            {
                if (item.size() == 1 && isOperator(item[0]))
                {
                    switch (item[0])
                    {
                    case '+':
                        bean = new MergeBean<std::string>;
                        break;
                    case '-':
                        bean = new DifferenceBean<std::string>;
                        break;
                    case '&':
                        bean = new CommonBean<std::string>;
                        break;
                    default:
                        throw "Operators are not defined!!!";
                    }

                    std::string top0 = splitted.top();
                    splitted.pop();

                    std::string top1 = splitted.top();
                    splitted.pop();

                    auto queue0 = getQueue(top0, myDict);
                    auto queue1 = getQueue(top1, myDict);

                    if (bean == nullptr)
                    {
                        throw "Bean no has statue!!!";
                    }

                    if (myDict.containsKey(top0))
                    {
                        myDict.removeKey(top0);
                    }

                    auto tempQueue = bean->getElements(queue1, queue0);

                    if(bean)
                    {
                        delete bean;
                    }
                    
                    auto key = newSubStr();
                    myDict.addKey(key, tempQueue);
                    splitted.push(key);
                }
                else
                {
                    splitted.push(item);
                    continue;
                }
            }

            if (splitted.size() != 1)
            {
                throw "error 1: There must be something wrong in this!!!";
            }

            std::string lastTop = splitted.top();

            if (!myDict.containsKey(lastTop))
            {
                throw "error 2: There must be something wrong in this!!!";
            }

            queue = myDict.findValues(lastTop);
        }

        if (!queue.empty())
        {
            auto key = newStr();
            myDict.addKey(key, queue);
            // queue.clear();

            std::cout << D_LBRACKET << key << D_RBRACKET << std::endl;
            myDict.printKey(key);
            std::cout << D_LBRACKET << key << D_RBRACKET << std::endl;
        }
        else
        {
            std::cout << "EMPTY QUEUE!!!" << std::endl;
        }
    }

    return 0;
}