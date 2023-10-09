/*
** EPITECH PROJECT, 2023
** B-CPP-500-MLH-5-1-rtype-robin.denni
** File description:
** DrawSystem.hpp
*/

#include <memory>
#include "../../Components/Drawable.hpp"
#include "../../Components/Position.hpp"
 
class DrawSystem {
    public:
        DrawSystem() {};
        DrawSystem(const Drawable &drawable, const Position &position);
        ~DrawSystem() {};
        void setDrawable(const Drawable &drawable);
        void setPosition(const Position &position);
        void draw(std::unique_ptr<sf::RenderWindow> &window);
    private:
        Drawable _drawable;
        Position _position;
};
