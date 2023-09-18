#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>

template <typename Component>
class SparseArray {
    public:
        using value_type = Component;
        using reference = value_type&;
        using const_reference = const value_type&;
        using size_type = size_t;
        using iterator = typename std::vector<value_type>::iterator;
        using const_iterator = typename std::vector<value_type>::const_iterator;
    public:
        SparseArray() = default;
        SparseArray(const SparseArray&) = default;
        SparseArray(SparseArray&&) = default;
        SparseArray& operator=(const SparseArray&) = default;
        SparseArray& operator=(SparseArray&&) = default;
        ~SparseArray() = default;

        void add(const value_type& value) {
            if (value.getId() >= data.size()) {
                data.resize(value.getId() + 1);
            }
            data[value.getId()] = value;
        }

        void remove(const value_type& value) {
            data[value.getId()] = value_type();
        }

        void remove(size_type id) {
            data[id] = value_type();
        }

        reference operator[](size_type id) {
            return data[id];
        }

        const_reference operator[](size_type id) const {
            return data[id];
        }

        iterator begin() {
            return data.begin();
        }

        const_iterator begin() const {
            return data.begin();
        }

        iterator end() {
            return data.end();
        }

        const_iterator end() const {
            return data.end();
        }

        size_type size() const {
            return data.size();
        }

        bool empty() const {
            return data.empty();
        }

        void clear() {
            data.clear();
        }
    
    private:
        std::vector<value_type> data;
        
};