#pragma once

#include <string>
#include <optional>

class Response {
private:
    int code;
    std::optional<std::string> body;

public:
    explicit Response(int code);
    Response(int code, std::string body);

public:
    [[nodiscard]] int getCode() const { return code; }
    [[nodiscard]] std::optional<std::string> getBody() const { return body; }

public:
    bool operator == (const Response& other);
    bool operator != (const Response& other);

public:
    static Response NotFoundResponse;
    static Response InternalServerErrorResponse;
};

