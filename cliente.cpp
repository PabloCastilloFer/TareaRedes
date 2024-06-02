#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

#define PORT 7777

int main(int argc, char const *argv[]) {
    if (argc != 3) {
        std::cerr << "Uso: " << argv[0] << " <dirección IP> <puerto>\n";
        return -1;
    }

    int sock = 0;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        std::cerr << "Error al crear el socket\n";
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[2]));

    if (inet_pton(AF_INET, argv[1], &serv_addr.sin_addr) <= 0) {
        std::cerr << "Dirección inválida/ No soportada\n";
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "Conexión fallida\n";
        return -1;
    }

    // Leer el estado inicial del tablero desde el servidor
    memset(buffer, 0, sizeof(buffer));
    int valread = read(sock, buffer, 1024);
    if (valread > 0) {
        std::cout << buffer;
    }

    while (true) {
        std::string input;
        std::cout << "Ingresa la columna (1-7): ";
        std::cin >> input;

        send(sock, input.c_str(), input.size(), 0);

        memset(buffer, 0, sizeof(buffer));
        valread = read(sock, buffer, 1024);
        std::cout << buffer;

        if (valread <= 0 || strstr(buffer, "Gana") != nullptr) break;
    }

    close(sock);
    return 0;
}

