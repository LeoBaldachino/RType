#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <iostream>

class Entity {
    private:
        size_t id;

    public:
        Entity(size_t id) : id(id) {}
        size_t getId() const { return id; }
};
