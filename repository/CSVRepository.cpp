#include "CSVRepository.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

CSVRepository::CSVRepository(const std::string& file) : filename(file) {
    loadFromFile();
}

void CSVRepository::loadFromFile() {
    activities.clear();
    std::ifstream fin(filename);
    std::string line;
    while (std::getline(fin, line)) {
        std::stringstream ss(line);
        std::string name, type, durationStr, date, effort;
        std::getline(ss, name, ',');
        std::getline(ss, type, ',');
        std::getline(ss, durationStr, ',');
        std::getline(ss, date, ',');
        std::getline(ss, effort, ',');
        int duration = std::stoi(durationStr);
        activities.emplace_back(name, type, duration, date, effort);
    }
}


void CSVRepository::saveToFile() const {
    std::ofstream fout(filename);
    for (const auto& act : activities) {
        fout << act.getName() << "," << act.getType() << ","
             << act.getDuration() << "," << act.getDate() << ","
             << act.getEffort() << "\n";
    }
}


void CSVRepository::add(const Activity& activity) {
    if (exists(activity.getName()))
        throw std::runtime_error("Activity already exists.");
    activities.push_back(activity);
    saveToFile();
}

void CSVRepository::remove(const std::string& name) {
    for (auto it = activities.begin(); it != activities.end(); ++it) {
        if (it->getName() == name) {
            activities.erase(it);
            saveToFile();
            return;
        }
    }
    throw std::runtime_error("Activity not found.");
}

void CSVRepository::update(const Activity& activity) {
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

const std::vector<Activity>& CSVRepository::getAll() const {
    return activities;
}

const Activity& CSVRepository::findByName(const std::string& name) const {
    for (const auto& a : activities) {
        if (a.getName() == name)
            return a;
    }
    throw std::runtime_error("Activity not found.");
}

bool CSVRepository::exists(const std::string& name) const {
    for (const auto& a : activities) {
        if (a.getName() == name)
            return true;
    }
    return false;
}
