#include "headers/Scene.hpp"
#include "headers/BombGem.hpp"
#include "headers/CrossGem.hpp"
#include <SFML/Audio.hpp>
#include <cstddef>
#include <utility>
#include <cstdlib>
#include <cmath>
#include <iostream>

// Стоят ли рядом два таких же по цвету
bool isThird(GemTable const& gems, size_t i, size_t j, SpriteEnum color) {
    bool cond1 = (i >= 2) && (gems.at(i - 1).at(j)->getSprite() == color) && (gems.at(i - 2).at(j)->getSprite() == color);
    bool cond2 = (j >= 2) && (gems.at(i).at(j - 1)->getSprite() == color) && (gems.at(i).at(j - 2)->getSprite() == color);
    return cond1 || cond2;
}

// Экранная координата гема в (i,j) 
sf::Vector2f Scene::calculPosition(size_t i, size_t j) {
    return sf::Vector2f(x0 + Gem::GEM_SIZE / 2.0f + j * Gem::GEM_SIZE,
        y0 + Gem::GEM_SIZE / 2.0f + i * Gem::GEM_SIZE);
}

// Конструктор сцены
Scene::Scene(size_t x0, size_t y0, size_t width, size_t height)
    : x0(x0), y0(y0), width(width), height(height)
{
    this->mainBoard.resize(height);
    for (size_t i = 0; i < height; i++) {
        this->mainBoard.at(i).resize(width);
        for (size_t j = 0; j < width; j++) {
            sf::Vector2f pos(calculPosition(i, j));
            SpriteEnum color = SpriteEnum(rand() % 4);

            while (isThird(mainBoard, i, j, color))
                color = SpriteEnum(rand() % 4);

            this->mainBoard.at(i).at(j) = new Gem(pos.x, pos.y, color);
        }
    }
}

// Деструктор сцены
Scene::~Scene() {
    for (auto& line : this->mainBoard)
        for (auto& gem : line)
            delete gem;
}

// Рисует всю сцену в окне
void Scene::draw(sf::RenderWindow* window) {
    for (auto const& line : this->mainBoard)
        for (auto const& gem : line)
            gem->draw(window);
}

// Обработчик движений мыши
void Scene::onHover(sf::Event event, size_t ti, size_t tj, size_t& hi, size_t& hj, bool isTaken) {
    size_t i = (event.mouseMove.y - y0) / Gem::GEM_SIZE;
    size_t j = (event.mouseMove.x - x0) / Gem::GEM_SIZE;

    if (i < height && j < width) {
        if (!isTaken || ti != hi || tj != hj)
            mainBoard.at(hi).at(hj)->hover(false);

        mainBoard.at(i).at(j)->hover(true);
        hi = i;
        hj = j;
    }
}

// Проверка гемов на соседство
bool isNeighbor(size_t ti, size_t tj, size_t hi, size_t hj) {
    return (
        std::abs(int(ti - hi)) == 1 &&
        std::abs(int(tj - hj)) == 0) ||
        (std::abs(int(ti - hi)) == 0 &&
        std::abs(int(tj - hj)) == 1);
}

// Свап гемов и их спрайтов
void swapGems(GemTable& gems, size_t i1, size_t j1, size_t i2, size_t j2) {
    sf::Vector2f pos = gems.at(i1).at(j1)->getPosition();
    gems.at(i1).at(j1)->setPosition(gems.at(i2).at(j2)->getPosition());
    gems.at(i2).at(j2)->setPosition(pos);
    std::swap(gems.at(i1).at(j1), gems.at(i2).at(j2));
}

// Обработчик нажатия
bool Scene::pressedEvent(bool& isTaken, size_t& ti, size_t& tj, size_t hi, size_t hj) {
    bool isSwapped = false;

    if (!isTaken) {
        ti = hi;
        tj = hj;
    }
    else if (isNeighbor(ti, tj, hi, hj)) {
        swapGems(mainBoard, ti, tj, hi, hj);
        isSwapped = true;
        
        sf::Music music;
        music.openFromFile("assets/thud.wav");
        music.play();
    }

    isTaken = !isTaken;
    mainBoard.at(ti).at(tj)->hover(isTaken);
    mainBoard.at(hi).at(hj)->hover(isTaken);
    return isSwapped;
}

// Обработчик срабатываний событий после свопа, возвращает заработанные в процессе очки 
int Scene::collisionGems(int gi, int gj) {
    SpriteEnum color = mainBoard.at(gi).at(gj)->getSprite();
    int gemsCount = 0,
        lineCount = 0,
        score = 0,
        left = gj - 1,
        right = gj + 1,
        up = gi - 1,
        down = gi + 1;

    while (left >= 0 && (mainBoard.at(gi).at(left)->getSprite() == color))
        --left;

    while (right < int(width) && (mainBoard.at(gi).at(right)->getSprite() == color))
        ++right;

    while (up >= 0 && (mainBoard.at(up).at(gj)->getSprite() == color))
        --up;

    while (down < int(height) && (mainBoard.at(down).at(gj)->getSprite() == color))
        ++down;

    if (right - left > 3) {
        lineCount++;
        gemsCount += right - left - 1;
        for (int j = left + 1; j < right; j++)
            score += mainBoard.at(gi).at(j)->activate(mainBoard, gi, j, width, height);
    }

    if (down - up > 3) {
        lineCount++;
        gemsCount += down - up - 1;
        for (int i = up + 1; i < down; i++)
            score += mainBoard.at(i).at(gj)->activate(mainBoard, i, gj, width, height);
    }

    if (lineCount == 2) {
        sf::Vector2f pos(calculPosition(gi, gj));
        delete mainBoard.at(gi).at(gj);
        mainBoard.at(gi).at(gj) = new BombGem(pos.x, pos.y, color);
    }
    else if (gemsCount >= 4) {
        sf::Vector2f pos(calculPosition(gi, gj));
        delete mainBoard.at(gi).at(gj);
        mainBoard.at(gi).at(gj) = new CrossGem(pos.x, pos.y, SpriteEnum(rand() % 4), color);
    }

    return score;
}

// Обновляет все гемы после схлопывания, двигает дырки наверх, заполняет новыми гемами
void updateGems(GemTable& gems, size_t width, size_t height) {
    int find;
    for (int i =height-1; i >= 0; i--) {
        for (size_t j = 0; j < width; j++) {
            if (gems.at(i).at(j)->getSprite() == SpriteEnum::SpriteEmpty) {
                find = i - 1;

                while (find >= 0 && gems.at(find).at(j)->getSprite() == SpriteEnum::SpriteEmpty)
                    --find;

                if (find >= 0){
                    swapGems(gems, i, j, find, j);
                }
                else
                    gems.at(i).at(j)->setSprite(SpriteEnum(rand() % 4));
            }
        }
    }
}

// Обновляет сцену, счётчики после событий IO
void Scene::update(sf::Event event, int& score) {
    static bool isUpdated = true;
    static bool isTaken = false;
    static bool isSwapped = false;
    static size_t hover_i = 0, hover_j = 0;
    static size_t taken_i = 0, taken_j = 0;
    int dscore = 0;

    switch (event.type){
    case sf::Event::MouseMoved:
        onHover(event, taken_i, taken_j, hover_i, hover_j, isTaken);
        break;

    case sf::Event::MouseButtonPressed:
        isSwapped = pressedEvent(isTaken, taken_i, taken_j, hover_i, hover_j);
        break;

    default:
        break;
    }

    if (isSwapped) {
        dscore += collisionGems(int(hover_i), int(hover_j));
        dscore += collisionGems(int(taken_i), int(taken_j));

        if (dscore == 0)
            swapGems(mainBoard, taken_i, taken_j, hover_i, hover_j);
        else
            isUpdated = false;

        score += dscore;
        isSwapped = false;
    }

    if (!isUpdated) {
        updateGems(mainBoard, width, height);
        isUpdated = true;

        for (size_t i = 0; i < height; i++) {
            for (size_t j = 0; j < width; j++) {
                SpriteEnum color = mainBoard.at(i).at(j)->getSprite();
                if (color != SpriteEnum::SpriteEmpty && isThird(mainBoard, i, j, color)) {
                    score += collisionGems(i, j);
                    isUpdated = false;
                }
            }
        }
        sf::sleep(sf::seconds(0.05));
    }
}
