#ifndef REVIEW_H
#define REVIEW_H

#include <string>

class Review {
private:
    std::string username;
    std::string reviewText;
    int rating;

public:
    Review(const std::string& username, const std::string& reviewText, int rating);
    std::string getUsername() const;
    std::string getReviewText() const;
    int getRating() const;
};

#endif // REVIEW_H
