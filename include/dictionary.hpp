#pragma once
#include <iostream>
#include <unordered_map>
#include <vector>
#include <type_traits>

template <typename KeyType, typename ValueType>
class Dictionary
{
public:
    // 增加键值对
    void addKey(const KeyType &key, const std::vector<ValueType> &value)
    {
        // m_dict[key].push_back(value);
        m_dict[key] = value;
    }

    void addSubKey(const KeyType &key, const std::vector<ValueType> &value)
    {
        m_subDict[key] = value;
    }

    // 删除键值对
    void removeKey(const KeyType &key)
    {
        m_dict.erase(key);
    }

    void removeSubKey(const KeyType &key)
    {
        m_subDict.erase(key);
    }

    // 修改键值对
    void updateKey(const KeyType &key, const std::vector<ValueType> &newValue)
    {
        m_dict[key] = newValue;
    }

    void updateSubKey(const KeyType &key, const std::vector<ValueType> &newValue)
    {
        m_subDict[key] = newValue;
    }

    // 查找键值对
    std::vector<ValueType> findValues(const KeyType &key)
    {
        if (m_dict.find(key) != m_dict.end())
        {
            return m_dict[key];
        }
        else
        {
            return {};
        }
    }

    std::vector<KeyType> findKeys(const ValueType &value)
    {
        std::vector<KeyType> result;

        if (!std::is_convertible<KeyType, std::string>::value)
        {
            return result;
        }

        for (const auto &entry : m_subDict)
        {
            for (const auto &values : entry.second)
            {
                if (values.find(value) != std::string::npos)
                {
                    result.push_back(entry.first);
                    break;
                }
            }
        }

        return result;
    }

    // 判断键是否存在
    bool containsKey(const KeyType &key)
    {
        return m_dict.find(key) != m_dict.end();
    }

    bool containsSubKey(const KeyType &key)
    {
        return m_subDict.find(key) != m_subDict.end();
    }

    void printKey(const KeyType &key)
    {
        int num = 0;

        for (const auto &element : m_dict[key])
        {
            auto keys = findKeys(element);
            std::sort(keys.rbegin(), keys.rend());
            std::string strKeys;

            for (size_t i = 0; i < keys.size(); i++)
            {
                strKeys += keys[i];

                if (i < keys.size() - 1)
                {
                    strKeys += ", ";
                }
            }

            std::cout << num++ << "\t"
                      << (std::is_convertible<ValueType, std::string>::value ? element : "???") << "\t"
                      << strKeys
                      << std::endl;
        }
    }

private:
    std::unordered_map<KeyType, std::vector<ValueType>> m_dict;
    std::unordered_map<KeyType, std::vector<ValueType>> m_subDict;
};