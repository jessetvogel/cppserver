#include "response.hpp"
#include <unistd.h>
#include <fstream>

Response::Response(int socket) {
    this->socket = socket;
}

bool Response::writeStatus() {
    return write("HTTP/1.1 ") && writeLine(status);
}

bool Response::writeHeaders() {
    return headers.write(this);
}

bool Response::write(std::string string) {
    size_t length = string.length();
    return ::write(socket, string.c_str(), length) == length;
}

bool Response::writeLine() {
    return write("\n");
}

bool Response::writeLine(std::string string) {
    return write(string) && writeLine();
}

#define BUFFER_SIZE (512)
bool Response::writeFile(std::string path) {
    std::ifstream file;
    file.open(path);
    
    char buffer[BUFFER_SIZE];
    std::streamsize bytes;
    do {
        file.read(buffer, BUFFER_SIZE);
        bytes = file.gcount();
        ::write(socket, buffer, bytes);
    } while(bytes > 0);
    
    file.close();
    return true;
}
