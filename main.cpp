#include "controller/LogicController.h"

int main(int argc, char** argv) {
    if (argc == 0 || argc > 2) {
        throw std::runtime_error("Invalid number of arguments! Run using 'help' to see the commands");
    }

    if (strcmp(argv[0], "run") == 0) LogicController::run();
    else if (strcmp(argv[0], "help") == 0) LogicController::help();
    else if (strcmp(argv[0], "ontology") == 0) LogicController::init("ontology");
    else if (strcmp(argv[0], "instance") == 0) LogicController::init("instance");
    else if (strcmp(argv[0], "rule") == 0) LogicController::init("rule");
    else if (strcmp(argv[0], "file") == 0) LogicController::init("file", argv[1]);
}
