
#include <vector>

#include <folly/portability/GFlags.h>
#include <glog/logging.h>
#include <proxygen/httpserver/HTTPServer.h>

#include "http/Controller.h"

//Commandline arguments
DEFINE_int32(http_port, 8080, "Port to listen on with HTTP protocol");
DEFINE_string(ip, "localhost", "IP/Hostname to bind to");
DEFINE_int32(threads,
    0,
    "Number of threads to listen on. Numbers <= 0 "
    "will use the number of cores on this machine."
);

// Example of how to create a controller
std::unique_ptr<http::Controller> CreateController()
{
    auto controller = std::make_unique<http::Controller>();

    //Simple get request
    //Example: http://localhost:8080/helloWorld
    controller->get("/helloWorld", [](std::unique_ptr<proxygen::HTTPMessage>& req, proxygen::ResponseBuilder& responseBuilder) {
        responseBuilder.body("Hello World");
    });

    return controller;
}

int main(int argc, char* argv[])
{
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    google::InitGoogleLogging(argv[0]);
    google::InstallFailureSignalHandler();

    std::vector<proxygen::HTTPServer::IPConfig> IPs = {
      {folly::SocketAddress(FLAGS_ip, FLAGS_http_port, true), proxygen::HTTPServer::Protocol::HTTP},
    };

    if (FLAGS_threads <= 0) {
        FLAGS_threads = sysconf(_SC_NPROCESSORS_ONLN);
        CHECK(FLAGS_threads > 0);
    }

    proxygen::HTTPServerOptions options;
    options.threads = static_cast<size_t>(FLAGS_threads);
    options.idleTimeout = std::chrono::milliseconds(60000);
    options.shutdownOn = { SIGINT, SIGTERM };
    options.enableContentCompression = false;
    options.handlerFactories = proxygen::RequestHandlerChain().addThen(CreateController()).build();
    // Increase the default flow control to 1MB/10MB
    options.initialReceiveWindow = uint32_t(1 << 20);
    options.receiveStreamWindowSize = uint32_t(1 << 20);
    options.receiveSessionWindowSize = 10 * (1 << 20);
    options.h2cEnabled = true;

    LOG(INFO) << "Starting up";
    LOG(INFO) << "Listening on: " << FLAGS_http_port;

    proxygen::HTTPServer server(std::move(options));
    server.bind(IPs);

    // Start HTTPServer mainloop in a separate thread
    std::thread t([&server]() { server.start(); });

    t.join();

    LOG(INFO) << "Shutdown";

	return 0;
}