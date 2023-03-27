#include <iostream>
using std::cout;

#include <string>
using std::string;
using std::endl;

#include <sstream>
using std::stringstream;

#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include <boost/filesystem.hpp>
#include <boost/filesystem/string_file.hpp>
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
            Request{"GET", "/api/employee", "?id=123", "{\n\t\"id\":123\n}"},
            Response{200, "{\n\t\"id\":123,\n\t\"name\":\"user\"\n}"}};

    string jsonStr = Serialize(rrf);

    cout << jsonStr << endl;

    auto rrfParsed = Parse(jsonStr);

    if(rrf == rrfParsed){
        cout << "Original and Parsed match" << endl;
    } else {
        cout << "Original and Parsed do not match" << endl;
    }

    fs::ifstream file(path / "/../testData/GETemployeeId123.json", std::ios::in | std::ios::binary);

    stringstream ss;
    while (!file.eof()){
        string s;
        file >> s;
        ss << s;
    }

    string jsonStrFromFile{ss.str()};

    cout << jsonStrFromFile << endl;

    auto rrfParsedFromFile = Parse(jsonStrFromFile);

    if(rrf == rrfParsedFromFile){
        cout << "Original and Parsed from File match" << endl;
    } else {
        cout << "Original and Parsed from File do not match" << endl;
    }

    return 0;
}
