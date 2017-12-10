#include <iostream>
#include <string>

#include "server.hpp"
#include "client.hpp"

void clientDemo() {
    // Setup connection
    Client client("www.google.com", 80);
    Request* request = client.createRequest();
    if(request == NULL) return;
    
    // Make request
    request->setMethod("GET");
    request->setRequestURI("/");
    
    request->sendRequestLine();
    request->sendHeaders();
    request->sendLine();
    request->sendLine();
    
    // Get response
    Response* response = client.getResponse();
    std::cout << "Status: " << response->getStatus() << std::endl;
    std::cout << "Content-Type: " << response->getHeaders()->get("Content-Type") << std::endl;
    
    char buffer[4096];
    memset(buffer, 0, 4096);
    std::cout << "data (size " << response->getData(buffer, 4096) << "):" << std::endl;
    std::cout << buffer << std::endl;
}

bool callback(Request& request, Response& response) {
    // Show some request information
    std::cout << "Method: " << request.getMethod() << std::endl;
    std::cout << "Request URI: " << request.getRequestURI() << std::endl;
    std::cout << "HTTP version: " << request.getHTTPVersion() << std::endl;
    
    std::cout << "Host: " << request.getHeaders()->get("Host") << std::endl << std::endl;
    
    // Write response
    response.setHeader("Content-Type", "text/html");
    response.sendStatus();
    response.sendHeaders();
    
    // We can write files
    response.sendFile("/Users/jessetvogel/Desktop/test.html");
    
    // Or send lines
    response.sendLine("123");
    
    return 1;
}

int main(int argc, const char * argv[]) {
    // Make request
    clientDemo();
    
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
