#pragma once

#include <functional>
#include <memory>

#include <proxygen/httpserver/RequestHandler.h>
#include <proxygen/httpserver/ResponseBuilder.h>

namespace http
{
    using Handler = std::function<void(std::unique_ptr<proxygen::HTTPMessage>&, proxygen::ResponseBuilder&)>;
};
