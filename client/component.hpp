#ifndef COMPONENT_HPP
#define COMPONENT_HPP

#include <unordered_map>
#include <typeindex>
#include <SFML/Graphics.hpp>

class Component {
    public:
        Component() = default;
        virtual ~Component() = default;
};

#endif // COMPONENT_HPP
