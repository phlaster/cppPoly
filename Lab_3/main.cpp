#include <SFML/Graphics.hpp>

class Window {
public:
    Window(int width, int height, const std::string& title) {
        window.create(sf::VideoMode(width, height), title);
    }

    void clear() {
        window.clear();
    }

    void display() {
        window.display();
    }

    bool isOpen() {
        return window.isOpen();
    }

    sf::RenderWindow& getWindow() {
        return window;
    }

private:
    sf::RenderWindow window;
};

class Game {
private:
    Window window;
public:
    Game(int width, int height, const std::string& title) 
        : window(width, height, title) 
    {
        // Initialize game objects and other setup here
    }

    void run() {
        while (window.isOpen()) {
            handleEvents();
            update();
            render();
        }
    }

    void handleEvents() {
        sf::Event event;
        while (window.isOpen() && window.getWindow().pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.getWindow().close();
            // Handle other events here
        }
    }

    void update() {
        // Handle game logic and state updates here
    }

    void render() {
        window.clear();
        // Draw game objects and UI elements here
        window.display();
    }

};

class GameObject {
public:
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void update(float deltaTime) = 0;
};

class Diamond : public GameObject {
public:
    void draw(sf::RenderWindow& window) override {
        // Draw the diamond specific drawing logic here
    }

    void update(float deltaTime) override {
        // Update the diamond specific update logic here
    }
};

int main(){
    Game threeinrow(800,600, "3 in row");
    threeinrow.run();
    return 0;
}