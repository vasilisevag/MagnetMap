#include <iostream>
#include <map>
#include <initializer_list>
#include <utility>
#include <vector>
#include <cmath>
#include <ctime>
#include <chrono>
#include <thread>
#include <unistd.h>
using namespace std;

template <typename K, typename V>
class MagnetMap {
    public:
    MagnetMap();
    MagnetMap(const initializer_list<pair<const K, V>>& pairValues);
    void insert(const pair<K, V>& p);
    V& operator[](const K& key);
    private:
    map<K, V> m_map;
};

template <typename K, typename V>
MagnetMap<K, V>::MagnetMap() : MagnetMap({}) {}

template <typename K, typename V>
MagnetMap<K, V>::MagnetMap(const initializer_list<pair<const K, V>>& pairValues) : m_map(pairValues) {}

// O(log(N)) time | O(1) space
template <typename K, typename V>
void MagnetMap<K, V>::insert(const pair<K, V>& p) {
    m_map.insert(p);
}

// O(log(N)) time | O(1) space
template <typename K, typename V>
V& MagnetMap<K, V>::operator[](const K& key) {
    auto upperBoundIterator = m_map.upper_bound(key);
    if(upperBoundIterator == m_map.begin()) 
        return upperBoundIterator->second;

    auto lowerOrEqualBoundIterator = upperBoundIterator; --lowerOrEqualBoundIterator;
    if(upperBoundIterator == m_map.end()) 
        return lowerOrEqualBoundIterator->second;

    if(upperBoundIterator->first - key < key - lowerOrEqualBoundIterator->first) 
        return upperBoundIterator->second;
    else 
        return lowerOrEqualBoundIterator->second;
}

int main(){
    MagnetMap<int, char> mm{{-10, 'a'}, {10, 'b'}};
    //mm.insert({-10, 'a'});
    //mm.insert({10, 'b'});
    cout << mm[2];
}