
#ifndef USER_H
#define USER_H

#include <string>
#include <vector>

class User {
protected:
    int user_id;
    std::string username;
    std::string password;

public:
    User(int user_id, std::string username, std::string password);

    std::string getUsername() const;
    virtual void login();
    static bool registerUser(std::vector<User*>& users, std::string username, std::string password);
    static User* loginUser(const std::vector<User*>& users, std::string username, std::string password);

};

#endif
