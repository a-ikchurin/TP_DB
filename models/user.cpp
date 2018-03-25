#include "user.hpp"

#include <postgresql/libpq-fe.h>
#include <sstream>

namespace models {

std::tuple<int, User> create_user(const User &user) {

    std::ostringstream conn_string("");
    conn_string << "host=" << "0.0.0.0"
        << " port=" << "5432"
        << " user=" << "docker"
        << " password=" << "docker"
        << " dbname=" << "docker";

    PGresult   *res;
    int         nFields;
    int         i,
                j;

    PGconn *conn = PQconnectdb(conn_string.str().c_str());
    if (PQstatus(conn) != CONNECTION_OK){
        PQfinish(conn);
        return std::make_tuple(1, User());
    }

    std::ostringstream request_str("");
    request_str << "BEGIN;"
                << "UPDATE users "
                << "SET "
                << "email = '" << user.email << "', "
                << "fullname = '" << user.fullname << "', "
                << "about = '" << user.about << "' "
                << "WHERE username = '" << user.username << "' "
                << "RETURNING *;"
                << "COMMIT;";

    res = PQexec(conn, request_str.str().c_str());

    if (PQresultStatus(res) != PGRES_TUPLES_OK)
    {
        PQclear(res);
        PQfinish(conn);
        return std::make_tuple(1, User());
    }

    //Наверное можно не возращать этого пользователя
    User result_user;
    result_user.email = PQgetvalue(res, 0, 1);
    result_user.fullname = PQgetvalue(res, 0, 2);
    result_user.about = PQgetvalue(res, 0, 3);

    PQclear(res);
    PQfinish(conn);

    return std::make_tuple(0, std::move(result_user));
}

std::tuple<int, User> get_user(User user) {
    return std::make_tuple(1, user);
}

std::tuple<int, User> update_user(User user) {
    return std::make_tuple(1, user);
}

}
