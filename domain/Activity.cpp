#include "Activity.h"

Activity::Activity(const std::string& name, const std::string& type, int duration,
                   const std::string& date, const std::string& effort)
    : name(name), type(type), duration(duration), date(date), effort(effort) {}

std::string Activity::getName() const { return name; }
std::string Activity::getType() const { return type; }
int Activity::getDuration() const { return duration; }
std::string Activity::getDate() const { return date; }
std::string Activity::getEffort() const { return effort; }

void Activity::setType(const std::string& newType) { type = newType; }
void Activity::setDuration(int newDuration) { duration = newDuration; }
void Activity::setDate(const std::string& newDate) { date = newDate; }
void Activity::setEffort(const std::string& newEffort) { effort = newEffort; }

std::string Activity::toString() const {
    return name + " | " + type + " | " + std::to_string(duration) + " min | " + date + " | " + effort;
}
