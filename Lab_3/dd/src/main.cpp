#include "headers/Game.hpp"
#include <iostream>

int main() {
    Game gems;

    if (!gems.init(Config())){
        std::cerr << "Unable to run the game" << std::endl;
        exit(1);
    }
    gems.loop();
    return 0;
}
