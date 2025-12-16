#pragma once
#include "Repository.h"
#include <string>

class CSVRepository : public Repository {
protected:
    std::string filename;
    void loadFromFile();
    void saveToFile() const;
public:
    explicit CSVRepository(const std::string& file);
    void add(const Activity& activity) override;
    void remove(const std::string& name) override;
    void update(const Activity& activity) override;
    const std::vector<Activity>& getAll() const override;
    const Activity& findByName(const std::string& name) const override;
    bool exists(const std::string& name) const override;
};