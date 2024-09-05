#include "utils.h"

// Function to read shader code from a file
std::string Utils::read_file_source(const char* filePath) {
    std::string code;
    std::ifstream shaderFile(filePath, std::ios::in);
    if (shaderFile.is_open()) {
        std::stringstream buffer;
        buffer << shaderFile.rdbuf();  // Read file into stream
        code = buffer.str();           // Convert stream into string
        shaderFile.close();
    } else {
        SDL_Log("ERROR::UTILS::FILE_NOT_SUCCESFULLY_READ: %s", filePath);
        return "";
    }
    return code;
}