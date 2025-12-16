#include "Command.h"

AddCommand::AddCommand(Repository& r, const Activity& a) : repo(r), activity(a) {}
void AddCommand::undo() { repo.remove(activity.getName()); }
void AddCommand::redo() { repo.add(activity); }

RemoveCommand::RemoveCommand(Repository& r, const Activity& a) : repo(r), removed(a) {}
void RemoveCommand::undo() { repo.add(removed); }
void RemoveCommand::redo() { repo.remove(removed.getName()); }

UpdateCommand::UpdateCommand(Repository& r, const Activity& oldAct, const Activity& newAct)
    : repo(r), before(oldAct), after(newAct) {}
void UpdateCommand::undo() { repo.update(before); }
void UpdateCommand::redo() { repo.update(after); }
