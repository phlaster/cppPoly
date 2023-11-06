#ifndef GAME_HPP
#define GAME_HPP

#include "Gem.hpp"
#include "Scene.hpp"
#include "Config.hpp"

#include <SFML/Graphics.hpp>

class Game
{
public:
    Game();
    ~Game();
    bool init(Config const& cfg);
    void loop();
private:
    bool setConfiguration(Config const& cfg);

    sf::RenderWindow* m_window;
    sf::Text m_message;
    Scene* mainBoard;
    int m_score;
};

#endif