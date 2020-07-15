#ifndef DECK_H
#define DECK_H

#include <optional>
#include <random>
#include <unordered_map>
#include <vector>

//TEMPORARY, debugging only
#include <iostream>

namespace cov {
    template <class T>
    class deck {
        public:
            deck(std::vector<T> vec = {}): size(vec.size()), ind(-1), arr(vec) {}
            std::optional<T> draw() {
                if(size == 0) {
                    return std::nullopt;
                }
                ++ind;
                if(ind >= size) {
                    shuffle();
                    ind = 0;
                }
                return arr[ind];
            }
            /**
             * Called after draw to simulate a player getting to keep the card
             */
            void remove() {
                if(ind < 0 || size == 0) {
                    return;
                }
                indices.insert({arr[ind], size-1});
                std::swap(arr[ind--], arr[--size]);
            }
            void reinsert(T add) {
                if(indices.count(add) == 0)
                    return;
                auto it = indices.find(add);
                auto range = indices.equal_range(arr[size]);
                while(range.first->second != size) {
                    range.first++;
                }
                std::swap(arr[it->second], arr[size]);
                range.first->second = it->second;
                indices.erase(it);
                size++;
            }
            void print() {
                for(int i = 0; i<ind; ++i) {
                    std::cout << arr[i] << ", ";
                }
                std::cout << '[' << arr[ind] << "], ";
                for(int i = ind+1; i<size; ++i) {
                    std::cout << arr[i] << ", ";
                }
                std::cout << "| ";
                for(int i = size; i<arr.size(); ++i) {
                    std::cout << arr[i] << ", ";
                }
                std::cout << " ||ind: " << ind << ", size: " << size << " ";
                for(auto p : indices) {
                    std::cout << "(" << p.first << ", " << p.second << "), ";
                }
            }
        private:
            std::size_t size;
            int ind; //-1 at the start due to implementation
            std::unordered_multimap<T, std::size_t> indices;
            std::vector<T> arr;

            void shuffle() {
                for(int i = 0; i<size; ++i) {
                    std::swap(arr[i], arr[i+rand()%(size-i)]);
                }
            }
    };
}

#endif