#include "Repository.h"
#include "../domain/Activity.h"

void Repository::add(const Activity& activity) {
    if (exists(activity.getName()))
        throw std::runtime_error("Activity already exists.");
    activities.push_back(activity);
}

void Repository::remove(const std::string& name) {
    for (auto it = activities.begin(); it != activities.end(); ++it) {
        if (it->getName() == name) {
            activities.erase(it);
            return;
        }
    }
    throw std::runtime_error("Activity not found.");
}

void Repository::update(const Activity& updatedActivity) {
    for (auto& act : activities) {
        if (act.getName() == updatedActivity.getName()) {
            act.setType(updatedActivity.getType());
            act.setDuration(updatedActivity.getDuration());
            act.setDate(updatedActivity.getDate());
            act.setEffort(updatedActivity.getEffort());
            return;
        }
    }
    throw std::runtime_error("Activity not found.");
}


const std::vector<Activity>& Repository::getAll() const {
    return activities;
}

const Activity& Repository::findByName(const std::string& name) const {
    for (const auto& act : activities) {
        if (act.getName() == name)
            return act;
    }
    throw std::runtime_error("Activity not found.");
}

bool Repository::exists(const std::string& name) const {
    for (const auto& act : activities) {
        if (act.getName() == name)
            return true;
    }
    return false;
}

