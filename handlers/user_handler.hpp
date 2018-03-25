#ifndef USER_HANDLER_HPP
#define USER_HANDLER_HPP

#include <thevoid/stream.hpp>
#include <thevoid/rapidjson/document.h>

#include <string>
#include <tuple>

#include "../models/user.hpp"

using namespace ioremap;

template <class T>
struct user_create : public thevoid::simple_request_stream<T> {
    virtual void on_request(const thevoid::http_request &req, const boost::asio::const_buffer &buffer) {

        //get username from path
        std::string username = req.url().path_components()[1];

        BH_LOG(this->logger(), SWARM_LOG_INFO, "test_mark %s\n",
               std::string((char*)boost::asio::detail::buffer_cast_helper(buffer),
                           boost::asio::detail::buffer_size_helper(buffer)).c_str());

        rapidjson::Document doc;
        doc.Parse(buffer);

        User user;
        user.username = username;
        user.about = doc["about"].getString();
        user.email = doc["email"].getString();
        user.fullname = doc["fullname"].getString();
        
        User res;
        int err_code = 0;
        std::tie<err_code, res> = models::create_user(user);

        thevoid::http_response reply;

        if ()
        reply.set_code(thevoid::http_response::ok);
        reply.headers().set_content_length(data.size());
        reply.headers().set_content_type("application/json");

        this->send_reply(std::move(reply), buffer);
    }
};

template <class T>
struct user_get : public thevoid::simple_request_stream<T> {
    virtual void on_request(const thevoid::http_request &req, const boost::asio::const_buffer &/*buffer*/) {
        (void) req;


        std::string data = "status\r\n";

        thevoid::http_response reply;
        reply.set_code(thevoid::http_response::ok);
        reply.headers().set_content_length(data.size());

        usleep(1000);

        this->send_reply(std::move(reply), std::move(data));
    }
};

template <class T>
struct user_update : public thevoid::simple_request_stream<T> {
    virtual void on_request(const thevoid::http_request &req, const boost::asio::const_buffer &/*buffer*/) {
        (void) req;


        std::string data = "status\r\n";

        thevoid::http_response reply;
        reply.set_code(thevoid::http_response::ok);
        reply.headers().set_content_length(data.size());

        usleep(1000);

        this->send_reply(std::move(reply), std::move(data));
    }
};

#endif
