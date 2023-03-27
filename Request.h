#pragma once

#include <string>
#include <optional>

class Request {
private:
    std::string method;
    std::string url;
    std::optional<std::string> getParameters;
    std::optional<std::string> body;

public:
    Request(std::string method, std::string url);
    Request(std::string method, std::string url, std::string getParameters);
    Request(std::string method, std::string url, std::string getParameters, std::string body);

public:
    std::string getMethod() const { return method; }
    std::string getUrl() const { return url; }
    std::optional<std::string> getGetParameters() const { return getParameters; }
    std::optional<std::string> getBody() const { return body; }

public:
    bool operator == (const Request& other);
    bool operator != (const Request& other);
};
