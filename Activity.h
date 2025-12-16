#pragma once
#include <string>

class Activity {
protected:
    std::string name;
    std::string type;
    int duration; // in minutes
    std::string date; // format: YYYY-MM-DD
    std::string effort; // easy, medium, hard

public:
    Activity(const std::string& name, const std::string& type, int duration,
             const std::string& date, const std::string& effort);

    std::string getName() const;
    std::string getType() const;
    int getDuration() const;
    std::string getDate() const;
    std::string getEffort() const;

    void setType(const std::string& newType);
    void setDuration(int newDuration);
    void setDate(const std::string& newDate);
    void setEffort(const std::string& newEffort);

    std::string toString() const;
};
