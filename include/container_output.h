#ifndef _CONTAINER_OUTPUT_H_
#define _CONTAINER_OUTPUT_H_

#include <iostream>
#include <map>
#include <set>
#include <vector>

template<class T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
    os << "[ ";
    for (const T& value : v) {
        os << value << " ";
    }
    os << "]";
    return os;
}

template<class T>
std::ostream& operator<<(std::ostream& os, const std::set<T>& v) {
    os << "( ";
    for (const T& value : v) {
        os << value << " ";
    }
    os << ")";
    return os;
}

template<typename K, typename V> 
std::ostream& operator<<(std::ostream& os, const std::map<K, V>& v) {
    os << "{ ";
    for (const auto& value : v) {
        os << value.first << ": " << value.second << " ";
    }
    os << "}";
    return os;
}

#endif