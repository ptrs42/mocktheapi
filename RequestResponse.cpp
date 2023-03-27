#include "RequestResponse.h"

RequestResponse::RequestResponse(Request request) :
        request(request)
{
}

RequestResponse::RequestResponse(Request request, Response response) :
        request(request),
        response(response)
{
}

bool RequestResponse::operator==(const RequestResponse &other) {
    return request == other.request && response.value_or(Response::NotFoundResponse) == other.response.value_or(Response::NotFoundResponse);
}

bool RequestResponse::operator!=(const RequestResponse &other) {
    return false;
}
