#include "Request.h"

#include <utility>

Request::Request(std::string method, std::string url) :
        method(std::move(method)),
        url(std::move(url))
{
}

Request::Request(std::string method, std::string url, std::string getParameters) :
        method(std::move(method)),
        url(std::move(url)),
        getParameters(getParameters)
{
}

Request::Request(std::string method, std::string url, std::string getParameters, std::string body) :
        method(std::move(method)),
        url(std::move(url)),
        getParameters(getParameters),
        body(body)
{
}

bool Request::operator==(const Request &other) {
    return method == other.method
           && url == other.url
           && getParameters.value_or("") == other.getParameters.value_or("")
           && body.value_or("") == other.body.value_or("");
}

bool Request::operator!=(const Request &other) {
    return !(*this == other);
}
