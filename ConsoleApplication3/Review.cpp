#include "Review.h"

Review::Review(const std::string& username, const std::string& reviewText, int rating)
    : username(username), reviewText(reviewText), rating(rating) {}

std::string Review::getUsername() const {
    return username;
}

std::string Review::getReviewText() const {
    return reviewText;
}

int Review::getRating() const {
    return rating;
}
