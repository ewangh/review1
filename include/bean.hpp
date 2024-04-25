#pragma once
#include "utils.hpp"
#include <vector>

template <typename T>
class Bean
{
public:
    virtual std::vector<T> getElements(const std::vector<T> &, const std::vector<T> &) const = 0;

    Bean(){};
    virtual ~Bean(){};
};

// 并集
template <typename T>
class MergeBean : public Bean<T>
{
public:
    virtual std::vector<T> getElements(const std::vector<T> &vec1, const std::vector<T> &vec2) const override
    {
        return getMergeElements<T>(vec1, vec2);
    }
};

// 交集
template <typename T>
class CommonBean : public Bean<T>
{
public:
    virtual std::vector<T> getElements(const std::vector<T> &vec1, const std::vector<T> &vec2) const override
    {
        return getCommonElements<T>(vec1, vec2);
    }
};

// 差集
template <typename T>
class DifferenceBean : public Bean<T>
{
public:
    virtual std::vector<T> getElements(const std::vector<T> &vec1, const std::vector<T> &vec2) const override
    {
        return getDifferenceElements<T>(vec1, vec2);
    }
};
