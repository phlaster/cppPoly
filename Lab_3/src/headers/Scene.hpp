#ifndef BOARD_HPP
#define BOARD_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include "Gem.hpp"

class Scene
{
public:
    explicit Scene(size_t x, size_t y, size_t width, size_t height);
    ~Scene();
    
    void draw(sf::RenderWindow* window);
    void update(sf::Event event, int& score);
private:
    size_t x0, y0;
    size_t width, height;

    int collisionGems(int gi, int gj);
    sf::Vector2f calculPosition(size_t i, size_t j);
    void onHover(sf::Event event, size_t ti, size_t tj, size_t& hi, size_t& hj, bool isTaken);
    bool pressedEvent(bool& isTaken, size_t& ti, size_t& tj, size_t hi, size_t hj);
    GemTable mainBoard;
};

#endif