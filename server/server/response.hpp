#ifndef response_hpp
#define response_hpp

#include <string>

#include "headers.hpp"

class Response {

    int socket;
    
    std::string status;
    Headers headers;
    
public:
    
    Response(int);
    
    inline void setStatus(std::string status) { this->status = status; }
    inline void setHeader(std::string field, std::string value) { headers.set(field, value); }
    
    bool writeStatus();
    bool writeHeaders();
    
    bool write(std::string);
    bool writeLine();
    bool writeLine(std::string);
    
    bool writeFile(std::string);

};

#endif
