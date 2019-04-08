#include <boost/network/protocol/http/server.hpp>
#include <string>
#include <iostream>

namespace http = boost::network::http;

struct hello_world; //fwd declaration to deal with the circular dependency -- typdev vs struct
typedef http::server<hello_world> server;

struct hello_world {
    void operator() (server::request const &request,
                     server::response &response) {
        std::string ip = source(request);
        response = server::response::stock_reply(
            server::response::ok, std::string("Hello, ") + ip + "!");
    }
};
int main(int argc, char * argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " address port" << std::endl;        return 1;
    }
    try {
        hello_world handler;
        server(argv[1], argv[2], handler).run();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;        return 1;
    }
}/*based on https://cpp-netlib.org/0.9.1/hello_world_server.html
*/
