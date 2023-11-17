#pragma once
#include <iostream>
#include <vector>
#include <unordered_set>
#include <cstring>

#pragma region 获取集合
template <typename T>
std::vector<T> getMatchingElements(const std::string &filePath, const std::string &regexPattern)
{
    std::vector<T> result;

    std::ifstream file(filePath);
    if (!file)
    {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        return result;
    }

    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>()); // 读取文件内容到字符串
    std::regex pattern(regexPattern);
    std::smatch matches;

    while (std::regex_search(content, matches, pattern))
    {
        for (auto match : matches)
        {
            T element;
            std::istringstream(match) >> element;
            result.push_back(element);
        }
        content = matches.suffix().str(); // 继续匹配剩余的内容
    }

    file.close();
    return result;
}
#pragma endregion

#pragma region 切割字符串
std::vector<std::string> splitString(const std::string& str, char delimiter) {
    std::vector<std::string> result;
    char* token = strtok(const_cast<char*>(str.c_str()), &delimiter);

    while (token != nullptr) {
        result.push_back(token);
        token = strtok(nullptr, &delimiter);
    }

    return result;
}
#pragma endregion

#pragma region 合并
template <typename T>
std::vector<T> getMergeElements(const std::vector<T> &vec1, const std::vector<T> &vec2)
{
    if (vec1.empty())
    {
        return vec2;
    }
    if (vec2.empty())
    {
        return vec1;
    }

    std::vector<T> commonElements;

    // 将vector1和vector2的元素插入到vector3中
    commonElements.insert(commonElements.end(), vec1.begin(), vec1.end());
    commonElements.insert(commonElements.end(), vec2.begin(), vec2.end());

    // 对vector3进行去重
    std::unordered_set<T> uniqueElements(commonElements.begin(), commonElements.end());
    commonElements.assign(uniqueElements.begin(), uniqueElements.end());

    return commonElements;
}

template <typename T, typename... Args>
std::vector<T> getMergeElements(const std::vector<T> &vec1, const std::vector<T> &vec2, const Args &...args)
{
    std::vector<T> commonElements = getMergeElements(vec1, vec2);
    return getMergeElements(commonElements, args...);
}

template <typename T>
std::vector<T> getMergeElements(const std::vector<T> &vec)
{
    return vec;
}
#pragma endregion

#pragma region 交集
template <typename T>
std::vector<T> getCommonElements(const std::vector<T> &vec1, const std::vector<T> &vec2)
{
    if (vec1.empty())
    {
        return vec1;
    }
    if (vec2.empty())
    {
        return vec2;
    }
    
    std::unordered_set<T> set1(vec1.begin(), vec1.end());
    std::vector<T> commonElements;

    for (const auto &element : vec2)
    {
        if (set1.count(element) > 0)
        {
            commonElements.push_back(element);
        }
    }

    return commonElements;
}

template <typename T, typename... Args>
std::vector<T> getCommonElements(const std::vector<T> &vec1, const std::vector<T> &vec2, const Args &...args)
{
    std::vector<T> commonElements = getCommonElements(vec1, vec2);
    return getCommonElements(commonElements, args...);
}

template <typename T>
std::vector<T> getCommonElements(const std::vector<T> &vec)
{
    return vec;
}
#pragma endregion

#pragma region 差集
template <typename T>
std::vector<T> getDifferenceElements(const std::vector<T> &vec1, const std::vector<T> &vec2)
{
    if (vec2.empty())
    {
        return vec1;
    }

    std::unordered_set<T> set1(vec1.begin(), vec1.end());
    std::vector<T> commonElements;

    // 将vector1中不在vector2中的元素插入到vector4中
    for (const auto &element : set1)
    {
        if (std::find(vec2.begin(), vec2.end(), element) == vec2.end())
        {
            commonElements.push_back(element);
        }
    }

    return commonElements;
}

template <typename T, typename... Args>
std::vector<T> getDifferenceElements(const std::vector<T> &vec1, const std::vector<T> &vec2, const Args &...args)
{
    std::vector<T> commonElements = getDifferenceElements(vec1, vec2);
    return getDifferenceElements(commonElements, args...);
}

template <typename T>
std::vector<T> getDifferenceElements(const std::vector<T> &vec)
{
    return vec;
}
#pragma endregion