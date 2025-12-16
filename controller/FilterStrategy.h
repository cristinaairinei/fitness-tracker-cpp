#pragma once
#include "../domain/Activity.h"
#include <memory>
#include <functional>

class FilterStrategy {
public:
    virtual bool matches(const Activity& a) const = 0;
    virtual ~FilterStrategy() = default;
};


class TypeFilter : public FilterStrategy {
protected:
    std::string type;
public:
    TypeFilter(const std::string& t);
    bool matches(const Activity& a) const override;
};


class DurationFilter : public FilterStrategy {
protected:
    int minDuration;
public:
    DurationFilter(int minD);
    bool matches(const Activity& a) const override;
};


class EffortFilter : public FilterStrategy {
protected:
    std::string effort;
public:
    EffortFilter(const std::string& e);
    bool matches(const Activity& a) const override;
};


class AndFilter : public FilterStrategy {
protected:
    std::shared_ptr<FilterStrategy> left, right;
public:
    AndFilter(std::shared_ptr<FilterStrategy> l, std::shared_ptr<FilterStrategy> r);
    bool matches(const Activity& a) const override;
};

class OrFilter : public FilterStrategy {
protected:
    std::shared_ptr<FilterStrategy> left, right;
public:
    OrFilter(std::shared_ptr<FilterStrategy> l, std::shared_ptr<FilterStrategy> r);
    bool matches(const Activity& a) const override;
};
