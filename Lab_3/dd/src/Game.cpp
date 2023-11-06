#include "headers/Game.hpp"
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <string>
#include <iostream>

static size_t BOARD_X0;
static size_t BOARD_Y0;
static size_t GEMS_WIDTH_COUNT;
static size_t GEMS_HEIGHT_COUNT;

static size_t WINDOW_WIDTH;
static size_t WINDOW_HEIGHT;
static sf::Color CLEAR_COLOR;

static sf::Font FONT;
static size_t CHARTER_SIZE;
static float M_POSITION_X ;
static float M_POSITION_Y;
static sf::Color M_COLOR;

static int SCORE_GOAL;

Game::Game()
    :m_window(nullptr), mainBoard(nullptr), m_score(0)
{}

Game::~Game() {
    delete mainBoard;
    delete m_window;
}

bool Game::setConfiguration(Config const& cfg) {
    sf::Uint8 r, g, b;
    
    if (!Gem::SPRITE.loadFromFile(cfg.SPRITE_FILE))
        return false;

    if (!FONT.loadFromFile(cfg.FONT_FILE))
        return false;

    srand(uint(time(NULL)));
    
    Gem::ONE_SPRITE_WIDTH = cfg.ONE_SPRITE_WIDTH;
    Gem::GEM_SIZE = cfg.GEM_SIZE;

    BOARD_X0 = cfg.X0;
    BOARD_Y0 = cfg.Y0;
    GEMS_WIDTH_COUNT = cfg.GEMS_WIDTH_COUNT;
    GEMS_HEIGHT_COUNT = cfg.GEMS_HEIGHT_COUNT;

    WINDOW_WIDTH = cfg.WINDOW_WIDTH;
    WINDOW_HEIGHT = cfg.WINDOW_HEIGHT;

    r = sf::Uint8((cfg.CLEAR_COLOR_RGB & 0x00ff0000) >> 16);
    g = sf::Uint8((cfg.CLEAR_COLOR_RGB & 0x0000ff00) >> 8);
    b = sf::Uint8(cfg.CLEAR_COLOR_RGB & 0x000000ff);
    CLEAR_COLOR = sf::Color(r, g, b);

    CHARTER_SIZE = cfg.CHARTER_SIZE;
    M_POSITION_X = cfg.M_POSITION_X;
    M_POSITION_Y = cfg.M_POSITION_Y;

    r = sf::Uint8((cfg.M_COLOR_RGB & 0x00ff0000) >> 16);
    g = sf::Uint8((cfg.M_COLOR_RGB & 0x0000ff00) >> 8);
    b = sf::Uint8(cfg.M_COLOR_RGB & 0x000000ff);
    M_COLOR = sf::Color(r, g, b);

    SCORE_GOAL = cfg.SCORE_GOAL;

    return true;
}

void setMessage(sf::Text& message, int score) {
    std::string msg("Points: ");
    msg += std::to_string(score);
    msg += "\nGoal: ";
    msg += std::to_string(SCORE_GOAL);
    message.setString(msg);
}

bool Game::init(Config const& cfg) {
    if (!setConfiguration(cfg))
        return false;
    
    m_score = 0;

    m_window = new sf::RenderWindow(
        sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32U),
        "Gems", sf::Style::Titlebar | sf::Style::Close
    );

    m_window->setVerticalSyncEnabled(true);

    m_message.setFont(FONT);
    m_message.setCharacterSize(CHARTER_SIZE);
    m_message.setPosition(M_POSITION_X, M_POSITION_Y);
    m_message.setFillColor(M_COLOR);
    setMessage(m_message, m_score);

    mainBoard = new Scene(BOARD_X0, BOARD_Y0, GEMS_WIDTH_COUNT, GEMS_HEIGHT_COUNT);

    return true;
}

bool isCloseEvent(sf::Event event) {
    return ((event.type == sf::Event::Closed) ||
        ((event.type == sf::Event::KeyPressed) &&
            (event.key.code == sf::Keyboard::Escape)));
}

void Game::loop() {

    bool isOver = false;
    while (m_window->isOpen()) {
        sf::Event event;

        while (m_window->pollEvent(event)) {
            if (isCloseEvent(event)) {
                m_window->close();
                break;
            }

            if (isOver && (event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::Space) )
            {
                m_score = 0;
                delete mainBoard;
                mainBoard = new Scene(BOARD_X0, BOARD_Y0, GEMS_WIDTH_COUNT, GEMS_HEIGHT_COUNT);
                setMessage(m_message, m_score);
                isOver = false;

                sf::Music music;
                if (!music.openFromFile("assets/blem.wav")){
                    std::cerr << "Couldn't find the sound file!" << std::endl;
                }
                else{
                    music.play();
                }
            }

            if (!isOver)
                mainBoard->update(event, m_score);
        }

        if (!isOver) {
            mainBoard->update(sf::Event(), m_score);
            setMessage(m_message, m_score);
            m_window->clear(CLEAR_COLOR);

            if (m_score > SCORE_GOAL) {
                isOver = true;
                m_message.setString("GAME OVER! Press SPACE to play again.");
            }

            m_window->draw(m_message);
            mainBoard->draw(m_window);
            m_window->display();
        }
    }
}
