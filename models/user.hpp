#ifndef MODELS_HPP
#define MODELS_HPP

#include <string>
#include <tuple>

namespace models {

struct User
{
    std::string username;
    std::string email;
    std::string fullname;
    std::string about;
};

std::tuple<int, User> create_user(const User &user);
std::tuple<int, User> get_user(User user);
std::tuple<int, User> update_user(User user);

}

#endif
