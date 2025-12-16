#pragma once
#include "../repository/Repository.h"
#include "Command.h"
#include "FilterStrategy.h"
#include <memory>
#include <stack>

class Service {
protected:
    Repository& repo;
    std::stack<std::unique_ptr<Command>> undoStack;
    std::stack<std::unique_ptr<Command>> redoStack;

public:
    Service(Repository& r);

    void addActivity(const Activity& activity);
    void removeActivity(const std::string& name);
    void updateActivity(const Activity& activity);

    void undo();
    void redo();

    std::vector<Activity> filter(std::shared_ptr<FilterStrategy> strategy) const;
    const std::vector<Activity>& getAllActivities() const;
};
