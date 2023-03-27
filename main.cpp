#include <iostream>
using std::cout;

#include <string>
using std::string;
using std::endl;

#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include <boost/filesystem.hpp>
namespace fs = boost::filesystem;

#include "RequestResponse.h"
#include "RequestResponseJsonSerializer.h"

int main(int argc, char *argv[]) {
    int port;

    po::options_description opDesc;
    opDesc.add_options()
            ("help", "prints out this help text")
            ("port,p", po::value<int>(&port)->default_value(9000), "port to listen on, default: 9000")
            ("path,P", po::value<string>(), "path with mock files, default: current directory");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, opDesc), vm);
    po::notify(vm);

    if(vm.count("help"))
    {
        cout << opDesc << endl;
        return 1;
    }

    fs::path path = vm.count("path") ? vm["path"].as<string>() : fs::current_path();

    cout << "Using path: " << path << endl;
    cout << "Listening on port :" << port << endl;

    // Test code
    RequestResponse rrf{
            Request{"GET", "/api/employee", "?id=123", R"({ "id": 123 })"},
            Response{200, "{\n\t\"id\": 123,\n\t\"name\": \"user\"\n}"}};

    string jsonStr = Serialize(rrf);

    cout << jsonStr << endl;

    auto rrfParsed = Parse(jsonStr);

    if(rrf == rrfParsed){
        cout << "Original and Parsed match" << endl;
    } else {
        cout << "Original and Parsed match" << endl;
    }

    return 0;
}
