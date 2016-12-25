# cppserver

    int callback(int socket_client) {
        // Do stuff.
        close(socket_client);
        return 1;
    }
    
    int main() {
        Server server(1234);
        server.handle = &callback;
        server.max_queue = 10;
        
        return 0;
    }
    
