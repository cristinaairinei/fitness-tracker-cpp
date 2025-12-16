//
// Created by maria-cristina on 03.06.2025.
//
#include "Console.h"
#include <iostream>

Console::Console(Service& s) : service(s) {}

void Console::addUI() {
    std::string name, type, date, effort;
    int duration;

    std::cin.ignore(); // curăță newline rămas

    std::cout << "Name: ";
    std::getline(std::cin, name);

    std::cout << "Type: ";
    std::getline(std::cin, type);

    std::cout << "Duration (min): ";
    std::cin >> duration;
    std::cin.ignore();

    std::cout << "Date (YYYY-MM-DD): ";
    std::getline(std::cin, date);

    std::cout << "Effort (easy/medium/hard): ";
    std::getline(std::cin, effort);

    try {
        service.addActivity(Activity(name, type, duration, date, effort));
    } catch (const std::exception& e) {
        std::cout << e.what() << "\n";
    }
}

void Console::removeUI() {
    std::string name;

    std::cin.ignore();
    std::cout << "Name to remove: ";
    std::getline(std::cin, name);

    try {
        service.removeActivity(name);
    } catch (const std::exception& e) {
        std::cout << e.what() << "\n";
    }
}

void Console::updateUI() {
    std::string name, type, date, effort;
    int duration;

    std::cin.ignore();

    std::cout << "Name: ";
    std::getline(std::cin, name);

    std::cout << "New Type: ";
    std::getline(std::cin, type);

    std::cout << "New Duration (min): ";
    std::cin >> duration;
    std::cin.ignore();

    std::cout << "New Date: ";
    std::getline(std::cin, date);

    std::cout << "New Effort: ";
    std::getline(std::cin, effort);

    try {
        service.updateActivity(Activity(name, type, duration, date, effort));
    } catch (const std::exception& e) {
        std::cout << e.what() << "\n";
    }
}

void Console::listUI() {
    for (const auto& act : service.getAllActivities())
        std::cout << act.toString() << "\n";
}

void Console::undoUI() {
    try {
        service.undo();
    } catch (const std::exception& e) {
        std::cout << e.what() << "\n";
    }
}

void Console::redoUI() {
    try {
        service.redo();
    } catch (const std::exception& e) {
        std::cout << e.what() << "\n";
    }
}

void Console::filterUI() {
    std::string type, logic, effort;
    int minDuration;

    std::cin.ignore();

    std::cout << "Type to filter (or leave empty to skip): ";
    std::getline(std::cin, type);

    std::cout << "Min duration (0 to skip): ";
    std::cin >> minDuration;
    std::cin.ignore();

    std::cout << "Effort to filter (easy/medium/hard or leave empty to skip): ";
    std::getline(std::cin, effort);

    std::cout << "Logic (AND / OR): ";
    std::getline(std::cin, logic);

    // Listează toate filtrele selectate de utilizator
    std::vector<std::shared_ptr<FilterStrategy>> filters;

    if (!type.empty()) {
        filters.push_back(std::make_shared<TypeFilter>(type));
    }

    if (minDuration > 0) {
        filters.push_back(std::make_shared<DurationFilter>(minDuration));
    }

    if (!effort.empty()) {
        filters.push_back(std::make_shared<EffortFilter>(effort));
    }

    if (filters.empty()) {
        std::cout << "No filters specified.\n";
        return;
    }

    // Creează combinația logică (AND/OR)
    std::shared_ptr<FilterStrategy> strategy = filters[0];
    for (size_t i = 1; i < filters.size(); ++i) {
        if (logic == "AND" || logic == "and") {
            strategy = std::make_shared<AndFilter>(strategy, filters[i]);
        } else if (logic == "OR" || logic == "or") {
            strategy = std::make_shared<OrFilter>(strategy, filters[i]);
        } else {
            std::cout << "Invalid logic type. Please use 'AND' or 'OR'.\n";
            return;
        }
    }

    // Afișează rezultatul
    auto result = service.filter(strategy);
    if (result.empty()) {
        std::cout << "No matching activities found.\n";
    } else {
        std::cout << "Filtered activities:\n";
        for (const auto& a : result)
            std::cout << a.toString() << "\n";
    }
}

void Console::run() {
    while (true) {
        std::cout << "\n1. Add\n2. Remove\n3. Update\n4. List\n5. Undo\n6. Redo\n7. Filter\n0. Exit\n> ";
        int cmd;
        std::cin >> cmd;

        switch (cmd) {
            case 1: addUI(); break;
            case 2: removeUI(); break;
            case 3: updateUI(); break;
            case 4: listUI(); break;
            case 5: undoUI(); break;
            case 6: redoUI(); break;
            case 7: filterUI(); break;
            case 0: return;
            default: std::cout << "Invalid!\n";
        }
    }
}
