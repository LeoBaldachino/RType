// #include <SFML/Graphics.hpp>

// class Hitbox : public Component {
// public:
//     sf::RectangleShape &body;

//     Hitbox(Entity* owner, sf::RectangleShape &body)
//         : Component(owner), body(body) {}

//     void update(float deltaTime) override {
//         body.setPosition(owner->getComponent<Position>().position);
//     }

//     bool checkCollision(Hitbox &other) {
//         return body.getGlobalBounds().intersects(other.body.getGlobalBounds());
//     }
// };
