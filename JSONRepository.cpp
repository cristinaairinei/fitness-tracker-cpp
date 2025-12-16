#include "JSONRepository.h"
#include "../domain/Activity.h"
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;

JSONRepository::JSONRepository(const std::string& file) : filename(file) {
    loadFromFile();
}

void JSONRepository::loadFromFile() {
    activities.clear();
    std::ifstream fin(filename);
    if (!fin.is_open()) return;

    json j;
    fin >> j;

    for (const auto& item : j) {
        std::string name = item.at("name");
        std::string type = item.at("type");
        int duration = item.at("duration");
        std::string date = item.at("date");
        std::string effort = item.at("effort");
        activities.emplace_back(name, type, duration, date, effort);
    }
}

void JSONRepository::saveToFile() const {
    json j = json::array();
    for (const auto& act : activities) {
        j.push_back({
            {"name", act.getName()},
            {"type", act.getType()},
            {"duration", act.getDuration()},
            {"date", act.getDate()},
            {"effort", act.getEffort()}
        });
    }
    std::ofstream fout(filename);
    fout << std::setw(4) << j;
}

void JSONRepository::add(const Activity& activity) {
    if (exists(activity.getName()))
        throw std::runtime_error("Activity already exists.");
    activities.push_back(activity);
    saveToFile();
}

void JSONRepository::remove(const std::string& name) {
    for (auto it = activities.begin(); it != activities.end(); ++it) {
        if (it->getName() == name) {
            activities.erase(it);
            saveToFile();
            return;
        }
    }
    throw std::runtime_error("Activity not found.");
}

void JSONRepository::update(const Activity& activity) {
    for (auto& a : activities) {
        if (a.getName() == activity.getName()) {
            a.setType(activity.getType());
            a.setDuration(activity.getDuration());
            a.setDate(activity.getDate());
            a.setEffort(activity.getEffort());
            saveToFile();
            return;
        }
    }
    throw std::runtime_error("Activity not found.");
}

const std::vector<Activity>& JSONRepository::getAll() const {
    return activities;
}

const Activity& JSONRepository::findByName(const std::string& name) const {
    for (const auto& a : activities)
        if (a.getName() == name)
            return a;
    throw std::runtime_error("Activity not found.");
}

bool JSONRepository::exists(const std::string& name) const {
    for (const auto& a : activities)
        if (a.getName() == name)
            return true;
    return false;
}
