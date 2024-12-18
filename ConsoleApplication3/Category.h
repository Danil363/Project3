#ifndef CATEGORY_H
#define CATEGORY_H

#include <string>

class Category {
private:
    std::string name;

public:
    Category(const std::string& name);
    std::string getName() const;
};

#endif // CATEGORY_H
