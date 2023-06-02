#include <iostream>

#ifndef ACTION_HPP
#define ACTION_HPP
enum Action
{
    EXIT,
    GENERATE_TASKS,
    SOLVE_TASKS,
    CHECK_ANSWERS,
    ROOT_ERROR
};
#endif


int main() {
    Action choice;
    do {
        std::cout << "Myprogram";
        std::cout << "Enter:";
        std::cout << "1 to generate tasks";
        std::cout << "2 to solve tasks";
        std::cout << "3 to check solved tasks";
        std::cout << "0 to exit";

        std::cin >> choice;

        switch (choice) {
            case 1:
                // generate tasks logic
                break;
            case 2:
                // solve tasks logic
                break;
            case 3:
                // check solved tasks logic
                break;
            case EXIT:
                std::cout << "Exiting program...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    } while (choice != EXIT);

    return 0;
}
