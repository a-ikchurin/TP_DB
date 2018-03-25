#ifndef SERVICE_HANDLER_HPP
#define SERVICE_HANDLER_HPP

#include <thevoid/stream.hpp>

using namespace ioremap;

template <class T>
struct service_clear : public thevoid::simple_request_stream<T> {
    virtual void on_request(const thevoid::http_request &req, const boost::asio::const_buffer &buffer) {
        (void) buffer;
        (void) req;


        std::string data = "clear\r\n";

        thevoid::http_response reply;
        reply.set_code(thevoid::http_response::ok);
        reply.headers().set_content_length(data.size());

        usleep(1000);

        this->send_reply(std::move(reply), std::move(data));
    }
};

template <class T>
struct service_status : public thevoid::simple_request_stream<T> {
    virtual void on_request(const thevoid::http_request &req, const boost::asio::const_buffer &buffer) {
        (void) buffer;
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
