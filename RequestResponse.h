#pragma once

#include <optional>

#include "Request.h"
#include "Response.h"

class RequestResponse {
private:
    Request request;
    std::optional<Response> response;

public:
    explicit RequestResponse(Request request);
    RequestResponse(Request request, Response response);

public:
    Request getRequest() const { return request; };
    std::optional<Response> getResponse() const { return response; };

public:
    bool operator == (const RequestResponse& other);
    bool operator != (const RequestResponse& other);
};
