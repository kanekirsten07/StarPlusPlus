
#include "http/Controller.h"
#include "http/LambdaHander.h"

namespace
{
    using namespace http;
}

//TODO: This should use a pool
proxygen::RequestHandler* http::Controller::onRequest(proxygen::RequestHandler*, proxygen::HTTPMessage*) noexcept {
    return new LambdaHandler(m_handlers);
}