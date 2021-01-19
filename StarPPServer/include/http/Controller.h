#pragma once

#include <functional>
#include <string>
#include <map>

#include <folly/io/async/EventBaseManager.h>
#include <proxygen/httpserver/RequestHandlerFactory.h>

#include "Handler.h"

namespace http
{
    // Implementation of the controller pattern
    // Similar to Spring's Controller. See https://spring.io/guides/gs/serving-web-content/
    class Controller : public proxygen::RequestHandlerFactory
    {
    public:
        void onServerStart(folly::EventBase* /*evb*/) noexcept override {}

        void onServerStop() noexcept override {}

        proxygen::RequestHandler* onRequest(proxygen::RequestHandler*, proxygen::HTTPMessage*) noexcept override;

        // Map a request to GET
        Controller& get(std::string uri, Handler handler) {
            m_handlers[uri] = handler;
        }
    private:
        // Mapped URI's
        std::map<std::string, Handler> m_handlers;
    };
}
