#include "RequestResponseJsonSerializer.h"

#include <string>
using std::string;

#include <boost/json.hpp>
namespace json = boost::json;

std::string Serialize(const RequestResponse &file) {
    return json::serialize(json::value_from(file));
}

RequestResponse Parse(string const & s) {
    return RequestResponse(json::value_to<RequestResponse>(json::parse(s)));
}

[[maybe_unused]] void tag_invoke( json::value_from_tag, json::value& jv, Request const& r )
{
    if(r.getGetParameters() && r.getBody()) {
        jv = {
                { "method" , r.getMethod() },
                { "url", r.getUrl() },
                { "getParameters", r.getGetParameters().value() },
                { "body", r.getBody().value() }
        };
    } else if(r.getGetParameters() && !r.getBody()){
        jv = {
                { "method" , r.getMethod() },
                { "url", r.getUrl() },
                { "getParameters", r.getGetParameters().value() }
        };
    } else if(!r.getGetParameters() && r.getBody()){
        jv = {
                { "method" , r.getMethod() },
                { "url", r.getUrl() },
                { "body", r.getBody().value() }
        };
    } else {
        jv = {
                { "method" , r.getMethod() },
                { "url", r.getUrl() }
        };
    }
}

[[maybe_unused]] void tag_invoke( json::value_from_tag, json::value& jv, Response const& r )
{
    if(r.getBody()) {
        jv = {
                { "code" , r.getCode() },
                { "body", r.getBody().value() }
        };
    } else {
        jv = {
                { "code" , r.getCode() }
        };
    }
}

[[maybe_unused]] void tag_invoke( json::value_from_tag, json::value& jv, RequestResponse const& file )
{
    jv = {
            { "request" , json::value_from(file.getRequest()) },
            { "response", json::value_from(file.getResponse()) }
    };
}

[[maybe_unused]] RequestResponse tag_invoke(json::value_to_tag<RequestResponse>, json::value const& jv)
{
    json::object const& obj = jv.as_object();

    if(!obj.at("response").is_null()){
        return RequestResponse {
                json::value_to<Request>( obj.at( "request" ) ),
                json::value_to<Response>( obj.at( "response" ) )
        };
    } else {
        return RequestResponse {
                json::value_to<Request>( obj.at( "request" ) )
        };
    }
}

[[maybe_unused]] Request tag_invoke(json::value_to_tag<Request>, json::value const& jv)
{
    json::object const& obj = jv.as_object();

    if(!obj.at("getParameters").is_null() && !obj.at("body").is_null()){
        return Request{ json::value_to<string>(obj.at("method")),
                        json::value_to<string>(obj.at("url")),
                        json::value_to<string>(obj.at("getParameters")),
                        json::value_to<string>(obj.at("body"))};
    } else if(!obj.at("getParameters").is_null() && obj.at("body").is_null()) {
        return Request{ json::value_to<string>(obj.at("method")),
                        json::value_to<string>(obj.at("url")),
                        json::value_to<string>(obj.at("getParameters"))};
    } else if (obj.at("getParameters").is_null() && obj.at("body").is_null()) {
        return Request{ json::value_to<string>(obj.at("method")),
                        json::value_to<string>(obj.at("url")),
                        json::value_to<string>(obj.at("body"))};
    } else {
        return Request{ json::value_to<string>(obj.at("method")),
                        json::value_to<string>(obj.at("url"))};
    }
}

[[maybe_unused]] Response tag_invoke(json::value_to_tag<Response>, json::value const& jv)
{
    json::object const& obj = jv.as_object();

    if(!obj.at("body").is_null()){
        return Response { json::value_to<int>(obj.at("code")), json::value_to<string>(obj.at("body")) };
    } else {
        return Response { json::value_to<int>(obj.at("code")) };
    }
}
