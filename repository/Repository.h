#pragma once
#include <vector>
#include "../domain/Activity.h"

class Repository {
protected:
    std::vector<Activity> activities;
public:
    virtual void add(const Activity& activity);
    virtual void remove(const std::string& name);
    virtual void update(const Activity& updatedActivity);
    virtual const std::vector<Activity>& getAll() const;
    virtual const Activity& findByName(const std::string& name) const;
    virtual bool exists(const std::string& name) const;
    virtual ~Repository() = default;
};