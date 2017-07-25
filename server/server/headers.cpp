#include "headers.hpp"
#include "response.hpp"

Headers::Headers() {
    // Set defaults
    set("Content-Type", "text/html");
    set("Date", "now");
}

void Headers::set(std::string field, std::string value) {
    headers[field] = value;
}

bool Headers::write(Response* response) {
    for(auto it = headers.begin();it != headers.end(); ++it) {
        response->write(it->first);
        response->write(": ");
        response->writeLine(it->second);
    }
    response->writeLine();
    return true;
}
