#pragma once
#include "../controller/Service.h"

class Console {
protected:
    Service& service;

    void addUI();
    void removeUI();
    void updateUI();
    void listUI();
    void undoUI();
    void redoUI();
    void filterUI();

public:
    Console(Service& s);
    void run();
};

