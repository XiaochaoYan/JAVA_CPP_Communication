#include <iostream>
#include <fstream>
#include <string>
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/reader.h"

class CppObjectData {
public:
    int value;
    std::string message;
};

int main() {
    std::ifstream file("data.json");
    if (!file) {
        std::cerr << "Failed to open file." << std::endl;
        return 1;
    }

    // Read the file into a string
    std::string jsonString((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    rapidjson::Document document;
    document.Parse(jsonString.c_str());

    if (document.HasParseError()) {
        std::cerr << "Failed to parse JSON data." << std::endl;
        return 1;
    }

    CppObjectData obj;
    obj.value = document["value"].GetInt();
    obj.message = document["message"].GetString();

    // Print the deserialized data
    std::cout << "Deserialized Data:" << std::endl;
    std::cout << "Value: " << obj.value << std::endl;
    std::cout << "Message: " << obj.message << std::endl;

    return 0;
}
