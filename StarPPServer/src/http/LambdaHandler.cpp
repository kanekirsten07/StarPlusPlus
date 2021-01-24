#include <iostream>
#include <folly/Memory.h>
#include <folly/io/async/EventBaseManager.h>

#include <folly/portability/Unistd.h>
#include <proxygen/httpserver/HTTPServer.h>
#include <proxygen/httpserver/ResponseBuilder.h>

#include "http/LambdaHander.h"

namespace
{
    using namespace http;
};

void LambdaHandler::onRequest(std::unique_ptr<proxygen::HTTPMessage> req) noexcept {
    proxygen::ResponseBuilder builder(getDownstream());
    

    auto& url = req->getURL();

    auto iter = m_handlers.find(url);

    //If not found
    if (iter == m_handlers.end())
    {
        builder.status(404, "Not Found");

        builder.send();

        return;
    }

    builder.status(200, "OK");

    iter->second(req, builder);

    
    builder.send();
    proxygen::ResponseBuilder(downstream_).sendWithEOM();
}

void LambdaHandler::onBody(std::unique_ptr<folly::IOBuf> body) noexcept {
    //proxygen::ResponseBuilder(downstream_).body(std::move(body)).send(); Will need for POST/PUT
}

void LambdaHandler::onEOM() noexcept {
    //proxygen::ResponseBuilder(downstream_).sendWithEOM();
}

void LambdaHandler::onUpgrade(proxygen::UpgradeProtocol /*protocol*/) noexcept {
    // handler doesn't support upgrades
}

//TODO: Return to a pool
void LambdaHandler::requestComplete() noexcept {
    delete this;
}

//TODO: Return to a pool
void LambdaHandler::onError(proxygen::ProxygenError /*err*/) noexcept {
    delete this;
}
