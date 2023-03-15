#include <iostream>

#include <server.hpp>

int main() {
    Server server(POOL_SIZE, PORT);
    if (!server.Init()) {
        return 1;
    }

    std::cout << "The server is ON" << std::endl;

    server.Run();

    return EXIT_SUCCESS;
}
