#include <thevoid/server.hpp>
#include <thevoid/stream.hpp>

#include "handlers/service_handler.hpp"
#include "handlers/user_handler.hpp"


using namespace ioremap;

class http_server : public thevoid::server<http_server>
{
public:
    virtual bool initialize(const rapidjson::Value &/* config */) {
        //forum
        /*
		on<on_ping>(
            options::exact_match("/forum/create"),
            options::methods("POST"),
            options::header("Content-Type", "application/json")
		);
        on<on_ping>(
            options::regex_match("^\/forum\/(\d|\w|-|_)*(\w|-|_)(\d|\w|-|_)*\/create"),
            options::methods("POST"),
            options::header("Content-Type", "application/json")
        );
        on<on_ping>(
            options::regex_match("^\/forum\/(\d|\w|-|_)*(\w|-|_)(\d|\w|-|_)*\/details"),
            options::methods("GET")
        );
        on<on_ping>(
            options::regex_match("^\/forum\/(\d|\w|-|_)*(\w|-|_)(\d|\w|-|_)*\/threads"),
            options::methods("GET")
        );
        on<on_ping>(
            options::regex_match("^\/forum\/(\d|\w|-|_)*(\w|-|_)(\d|\w|-|_)*\/users"),
            options::methods("GET")
        );

        //post
        on<on_ping>(
            options::regex_match("^\/post\/[0-9]+\/details"),
            options::methods("GET")
        );
        on<on_ping>(
            options::regex_match("^\/post\/[0-9]+\/details"),
            options::methods("POST"),
            options::header("Content-Type", "application/json")
        );
        */
        //service
        on<service_clear<http_server>>(
            options::exact_match("/service/clear"),
            options::methods("POST")
        );
        on<service_status<http_server>>(
            options::exact_match("/service/status"),
            options::methods("GET")
        );
        /*
        //thread
        on<on_ping>(
            options::exact_match("/thread/create"),
            options::methods("GET"),
            options::header("Content-Type", "application/json")
        );
        on<on_ping>(
            options::exact_match("/forum/create"),
            options::methods("GET"),
            options::header("Content-Type", "application/json")
        );
        on<on_ping>(
            options::exact_match("/forum/create"),
            options::methods("GET"),
            options::header("Content-Type", "application/json")
        );
        on<on_ping>(
            options::exact_match("/forum/create"),
            options::methods("GET"),
            options::header("Content-Type", "application/json")
        );
        on<on_ping>(
            options::exact_match("/forum/create"),
            options::methods("GET"),
            options::header("Content-Type", "application/json")
        );
        */
        //user
        on<user_create<http_server>>(
            options::regex_match("^\/user\/[[:word:]]+\/create"),
            options::methods("POST"),
            options::header("Content-Type", "application/json")
        );
        /*
        on<my_func>(
            options::regex_match("^\/user\/[[:word:]]+\/profile"),
            options::methods("GET")
        );
        on<my_func>(
            options::regex_match("^\/user\/[[:word:]]+\/profile"),
            options::methods("POST"),
            options::header("Content-Type", "application/json")
        );
        */
        on<my_func>(
                    options::regex_match("^\/my\/[[:word:]]+\/func"),
                    options::methods("GET")
                    //options::header("Content-Type", "application/json")

        );
	
		return true;
	}

    struct my_func : public thevoid::simple_request_stream<http_server> {
        virtual void on_request(const thevoid::http_request &req, const boost::asio::const_buffer &buffer) {
            (void) buffer;



            std::string data = "my func : " +  req.url().path_components()[1];

            int timeout_ms = 10 + (rand() % 10);
            usleep(timeout_ms * 1000);

            thevoid::http_response reply;
            reply.set_code(thevoid::http_response::ok);
            reply.headers().set_content_length(data.size());

            this->send_reply(std::move(reply), std::move(data));
        }
    };

	struct on_ping : public thevoid::simple_request_stream<http_server> {
		virtual void on_request(const thevoid::http_request &req, const boost::asio::const_buffer &buffer) {
			(void) buffer;
			(void) req;

			this->send_reply(thevoid::http_response::ok);
		}
	};


};

int main(int argc, char **argv)
{
	return ioremap::thevoid::run_server<http_server>(argc, argv);
}
