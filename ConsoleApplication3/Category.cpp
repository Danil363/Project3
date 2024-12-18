#include "Category.h"

Category::Category(const std::string& name) : name(name) {}

std::string Category::getName() const {
    return name;
}
