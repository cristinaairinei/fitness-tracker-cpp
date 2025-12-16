#pragma once
#include "../domain/Activity.h"
#include "../repository/Repository.h"
#include <memory>

class Command {
public:
    virtual void undo() = 0;
    virtual void redo() = 0;
    virtual ~Command() = default;
};

class AddCommand : public Command {
protected:
    Repository& repo;
    Activity activity;

public:
    AddCommand(Repository& r, const Activity& a);
    void undo() override;
    void redo() override;
};

class RemoveCommand : public Command {
protected:
    Repository& repo;
    Activity removed;

public:
    RemoveCommand(Repository& r, const Activity& a);
    void undo() override;
    void redo() override;
};

class UpdateCommand : public Command {
protected:
    Repository& repo;
    Activity before;
    Activity after;

public:
    UpdateCommand(Repository& r, const Activity& oldAct, const Activity& newAct);
    void undo() override;
    void redo() override;
};
