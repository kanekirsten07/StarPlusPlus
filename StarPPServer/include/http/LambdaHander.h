#pragma once

#include <functional>

#include <memory>
#include <folly/Memory.h>
#include <folly/portability/Unistd.h>

#include "Handler.h"

namespace http
{
    // Implementation of a request handler
    // Currently only supports get
    class LambdaHandler : public proxygen::RequestHandler
    {
    public:
        LambdaHandler(std::map<std::string, http::Handler>& handlers)
            : m_handlers(handlers)
        {}

        void onRequest(std::unique_ptr<proxygen::HTTPMessage> headers) noexcept override;

        // On request body (Needed for POST/PUT)
        void onBody(std::unique_ptr<folly::IOBuf> body) noexcept override;

        // Once we're done
        void onEOM() noexcept override;

        // TODO
        void onUpgrade(proxygen::UpgradeProtocol proto) noexcept override;


        void requestComplete() noexcept override;


        void onError(proxygen::ProxygenError err) noexcept override;
    private:
        std::map<std::string, http::Handler>& m_handlers;

        std::unique_ptr<folly::IOBuf> body_;
    };
}
