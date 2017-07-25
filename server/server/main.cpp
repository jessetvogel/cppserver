#include <iostream>
#include <string>

#include "server.hpp"

bool callback(Request* request, Response* response) {
    // Show some request information
    std::cout << "Method: " << request->getMethod() << std::endl;
    std::cout << "Request URI: " << request->getRequestURI() << std::endl;
    std::cout << "HTTP version: " << request->getHTTPVersion() << std::endl;
    
    std::cout << "Host: " << request->getHeaders()->get("Host") << std::endl << std::endl;
    
    // Write response
    response->setHeader("Content-Type", "text/html");
    response->writeStatus();
    response->writeHeaders();
    
    // We can write files
    response->writeFile("/Users/jessetvogel/Desktop/test.html");
    
    // Or we can write lines
    response->writeLine("123");
    
    return 1;
}

int main(int argc, const char * argv[]) {
    // Create and start server
    Server server(8080, &callback, 10);
    if(!server.start()) return 1;

        std::cout << "started on port " << server.getPort() << std::endl;
    
    // Wait for input
    std::string line;
    while(std::getline(std::cin, line)) {
        // Check for exit command
        if(line.compare("exit") == 0) break;
    }
    
    // Stop server
    server.stop();
    
    return 0;
}
