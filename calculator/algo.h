#pragma once
#include <cstddef>
#include <deque>

template<class T, class Comp>
std::deque<T> Merge(const std::deque<T>& half1,
                    const std::deque<T>& half2,
                    const Comp& comparator) {
    std::deque<T> result;
    auto first = half1.begin();
    auto second = half2.begin();
    while (first != half1.end() && second != half2.end()) {
        if (comparator(*second, *first)) {
            result.push_back(*second++);
        } else {
            result.push_back(*first++);
        }
    }
    result.insert(result.end(), first, half1.end());
    result.insert(result.end(), second, half2.end());
    return result;
}

template<class T, class Comp>
std::deque<T> MergeSort(const std::deque<T>& src, const Comp& comparator) {
    if (src.size() <= 1) {
        return src;
    }
    const size_t middle = src.size() / 2;
    const std::deque<T> left(src.begin(), src.begin() + middle);
    const std::deque<T> right(src.begin() + middle, src.end());
    return Merge(MergeSort(left, comparator), MergeSort(right, comparator), comparator);
}
