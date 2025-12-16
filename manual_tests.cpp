#include "controller/Service.h"
#include "repository/Repository.h"
#include "controller/FilterStrategy.h"
#include <iostream>

class TestRepo : public Repository {
protected:
    std::vector<Activity> data;

public:
    void add(const Activity& activity) override {
        data.push_back(activity);
    }

    void remove(const std::string& name) override {
        for (auto it = data.begin(); it != data.end(); ++it) {
            if (it->getName() == name) {
                data.erase(it);
                return;
            }
        }
        throw std::runtime_error("Not found");
    }

    void update(const Activity& activity) override {
        for (auto& a : data) {
            if (a.getName() == activity.getName()) {
                a = activity;
                return;
            }
        }
        throw std::runtime_error("Not found");
    }

    const std::vector<Activity>& getAll() const override {
        return data;
    }

    const Activity& findByName(const std::string& name) const override {
        for (const auto& a : data)
            if (a.getName() == name)
                return a;
        throw std::runtime_error("Not found");
    }

    bool exists(const std::string& name) const override {
        for (const auto& a : data)
            if (a.getName() == name)
                return true;
        return false;
    }

    ~TestRepo() override = default;
};

void runTests() {
    TestRepo repo;
    Service service(repo);

    std::cout << "TEST: Add...\n";
    service.addActivity(Activity("A1", "cardio", 30, "2025-06-01", "medium"));
    service.addActivity(Activity("A2", "strength", 45, "2025-06-02", "hard"));
    std::cout << "Activities: " << service.getAllActivities().size() << "\n";  // 2

    std::cout << "TEST: Update...\n";
    service.updateActivity(Activity("A1", "updated", 50, "2025-06-03", "easy"));
    std::cout << "A1 new type: " << service.getAllActivities()[0].getType() << "\n";

    std::cout << "TEST: Remove...\n";
    service.removeActivity("A2");
    std::cout << "Activities after remove: " << service.getAllActivities().size() << "\n";

    std::cout << "TEST: Undo...\n";
    service.undo();
    std::cout << "After undo, activities: " << service.getAllActivities().size() << "\n";

    std::cout << "TEST: Redo...\n";
    service.redo();
    std::cout << "After redo, activities: " << service.getAllActivities().size() << "\n";

    std::cout << "TEST: Filter by type = updated\n";
    auto filtered1 = service.filter(std::make_shared<TypeFilter>("updated"));
    std::cout << "Filtered count: " << filtered1.size() << "\n";

    std::cout << "TEST: Filter by effort = easy\n";
    auto filtered2 = service.filter(std::make_shared<EffortFilter>("easy"));
    std::cout << "Filtered count: " << filtered2.size() << "\n";

    std::cout << "TEST: Filter by effort = hard\n";
    auto filtered3 = service.filter(std::make_shared<EffortFilter>("hard"));
    std::cout << "Filtered count: " << filtered3.size() << "\n";

    std::cout << "TEST: Combined filter: type = updated AND effort = easy\n";
    auto combined = service.filter(std::make_shared<AndFilter>(
        std::make_shared<TypeFilter>("updated"),
        std::make_shared<EffortFilter>("easy")
    ));
    std::cout << "Combined filter count: " << combined.size() << "\n";

    std::cout << "All tests passed.\n";
}
