#include "Response.h"

Response::Response(int code) :
        code(code)
{
}

Response::Response(int code, std::string body) :
        code(code),
        body(body)
{
}

Response Response::NotFoundResponse = Response(404);
Response Response::InternalServerErrorResponse = Response(500);

bool Response::operator==(const Response &other) {
    return code == other.getCode() && body.value_or("") == other.getBody().value_or("");
}

bool Response::operator!=(const Response &other) {
    return !(*this == other);
}
