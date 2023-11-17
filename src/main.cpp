#include <iostream>
#include <fstream>
#include <regex>
#include "dictionary.hpp"
#include "radomStr.h"
#include "bean.hpp"
// #include "http_request.h"

class AAA
{
public:
    AAA(int d) : a(d), b(d), c(d), f(d), g(d){};
    AAA(int d1, int d2) : a(d1), b(d2), c(d2), f(d2), g(d2){};
    AAA &getSize() { return *this; }
    int a, b, c, f, g, h;
};

#define ZT "zt"

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

        std::vector<std::string> splitted;

        if (input.find('&') != std::string::npos && input.find('+') != std::string::npos || input.find('&') != std::string::npos && input.find('-') != std::string::npos || input.find('+') != std::string::npos && input.find('-') != std::string::npos)
        {
            std::cout << "Sorry, the keys you entered is not valid. Please check and try again!!!" << std::endl;
            continue;
        }

        if (myDict.containsKey(input))
        {
            std::cout << "[" << input << "]" << std::endl;
            myDict.printKey(input);

            continue;
        }
        else if (input.find('&') != std::string::npos)
        {
            splitted = splitString(input, '&');
            bean = new CommonBean<std::string>;
        }
        else if (input.find('+') != std::string::npos)
        {
            splitted = splitString(input, '+');
            bean = new MergeBean<std::string>;
        }
        else if (input.find('-') != std::string::npos)
        {
            splitted = splitString(input, '-');
            bean = new DifferenceBean<std::string>;
        }
        else
        {
            std::string fileName = input;

            if (input.size() >= 4 && input.substr(input.length() - 4) != ".txt" && input.substr(input.length() - 4) != ".TXT")
            {
                fileName += ".txt";
            }

            std::vector<std::string> vector_f = getMatchingElements<std::string>("../file/" + fileName, R"(\d{6})");

            if (vector_f.empty())
            {
                std::cout << input << " IS EMPTY QUEUE!!!" << std::endl;
            }
            else
            {
                myDict.addKey(input, vector_f);
                std::cout << "[" << input << "]" << std::endl;
                myDict.printKey(input);
            }

            continue;
        }

        std::vector<std::string> queue;

        for (const std::string &str : splitted)
        {
            std::vector<std::string> tempq;

            if (myDict.containsKey(str))
            {
                tempq = myDict.findValues(str);
            }
            else
            {
                tempq = getMatchingElements<std::string>("../file/" + str + ".txt", "\\d{6}");

                if (str.size() < 3 || str.substr(0, 2) != ZT)
                {
                }
                else
                {
                    auto subKey = str.substr(2);

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

            if (queue.empty())
            {
                queue = tempq;
                continue;
            }

            queue = bean->getElements(queue, tempq);
        }

        if (!queue.empty())
        {
            auto key = newStr();
            myDict.addKey(key, queue);
            queue.clear();

            std::cout << "[" << key << "]" << std::endl;
            myDict.printKey(key);
        }
        else
        {
            std::cout << "EMPTY QUEUE!!!" << std::endl;
        }

        splitted.clear();

        if (bean != nullptr)
        {
            delete bean;
            bean = nullptr;
        }
    }

    return 0;
}
