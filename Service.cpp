#include "Service.h"

Service::Service(Repository& r) : repo(r) {}

void Service::addActivity(const Activity& activity) {
    repo.add(activity);
    undoStack.push(std::make_unique<AddCommand>(repo, activity));
    while (!redoStack.empty()) redoStack.pop();
}

void Service::removeActivity(const std::string& name) {
    Activity removed = repo.findByName(name);
    repo.remove(name);
    undoStack.push(std::make_unique<RemoveCommand>(repo, removed));
    while (!redoStack.empty()) redoStack.pop();
}

void Service::updateActivity(const Activity& activity) {
    Activity old = repo.findByName(activity.getName());
    repo.update(activity);
    undoStack.push(std::make_unique<UpdateCommand>(repo, old, activity));
    while (!redoStack.empty()) redoStack.pop();
}

void Service::undo() {
    if (undoStack.empty())
        throw std::runtime_error("Nothing to undo.");
    auto cmd = std::move(undoStack.top());
    undoStack.pop();
    cmd->undo();
    redoStack.push(std::move(cmd));
}

void Service::redo() {
    if (redoStack.empty())
        throw std::runtime_error("Nothing to redo.");
    auto cmd = std::move(redoStack.top());
    redoStack.pop();
    cmd->redo();
    undoStack.push(std::move(cmd));
}

std::vector<Activity> Service::filter(std::shared_ptr<FilterStrategy> strategy) const {
    std::vector<Activity> result;
    for (const auto& a : repo.getAll()) {
        if (strategy->matches(a)) {
            result.push_back(a);
        }
    }
    return result;
}

const std::vector<Activity>& Service::getAllActivities() const {
    return repo.getAll();
}
