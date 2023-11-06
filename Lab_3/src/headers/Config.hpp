#ifndef GAMECONF_HPP
#define GAMECONF_HPP

struct Config{
    // Gems
    char SPRITE_FILE[128] = "assets/gems.png";
    float ONE_SPRITE_WIDTH = 48.f;
    size_t GEM_SIZE = 50;

    // Scene
    size_t X0 = 20;
    size_t Y0 = 100;
    size_t GEMS_WIDTH_COUNT = 16;
    size_t GEMS_HEIGHT_COUNT = 9;

    // Window
    size_t WINDOW_WIDTH = 840;
    size_t WINDOW_HEIGHT = 570;
    size_t CLEAR_COLOR_RGB = 0x00bfbfbf;

    // Score badge
    char FONT_FILE[128] = "assets/JetBrainsMono-Medium.ttf";
    size_t CHARTER_SIZE = 35;
    float M_POSITION_X = 50;
    float M_POSITION_Y = 10;
    size_t M_COLOR_RGB = 0x00000000;

    // Global
    int SCORE_GOAL = 500;
};

#endif