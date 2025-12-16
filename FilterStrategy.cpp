#include "FilterStrategy.h"


TypeFilter::TypeFilter(const std::string& t) : type(t) {}
bool TypeFilter::matches(const Activity& a) const {
    return a.getType() == type;
}


DurationFilter::DurationFilter(int minD) : minDuration(minD) {}
bool DurationFilter::matches(const Activity& a) const {
    return a.getDuration() >= minDuration;
}


EffortFilter::EffortFilter(const std::string& e) : effort(e) {}
bool EffortFilter::matches(const Activity& a) const {
    return a.getEffort() == effort;
}


AndFilter::AndFilter(std::shared_ptr<FilterStrategy> l, std::shared_ptr<FilterStrategy> r)
    : left(l), right(r) {}
bool AndFilter::matches(const Activity& a) const {
    return left->matches(a) && right->matches(a);
}


OrFilter::OrFilter(std::shared_ptr<FilterStrategy> l, std::shared_ptr<FilterStrategy> r)
    : left(l), right(r) {}
bool OrFilter::matches(const Activity& a) const {
    return left->matches(a) || right->matches(a);
}
