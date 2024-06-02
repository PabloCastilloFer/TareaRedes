#include <iostream>
#include <thread>
#include <vector>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <mutex>
#include <cstdlib>
#include <ctime>
#include <arpa/inet.h> // Asegúrate de tener esta cabecera para inet_ntop

#define PORT 7777
#define ROWS 6
#define COLS 7

std::mutex mtx;

class Connect4Game {
public:
    Connect4Game() : board(ROWS, std::vector<char>(COLS, ' ')), moveCount(0) {
        srand(time(0));
    }

    bool makeMove(int col, char player) {
        if (col < 0 || col >= COLS || board[0][col] != ' ') {
            return false;
        }
        for (int i = ROWS - 1; i >= 0; --i) {
            if (board[i][col] == ' ') {
                board[i][col] = player;
                lastMoveRow = i;
                lastMoveCol = col;
                lastPlayer = player;
                moveCount++;
                return true;
            }
        }
        return false;
    }

    bool makeRandomMove(char player) {
        std::vector<int> availableCols;
        for (int i = 0; i < COLS; ++i) {
            if (board[0][i] == ' ') {
                availableCols.push_back(i);
            }
        }
        if (availableCols.empty()) return false;

        int randomCol = availableCols[rand() % availableCols.size()];
        return makeMove(randomCol, player);
    }

    bool checkWin() {
        return checkDirection(1, 0) || // vertical
               checkDirection(0, 1) || // horizontal
               checkDirection(1, 1) || // diagonal
               checkDirection(1, -1);  // diagonal /
    }

    std::string getBoardString() {
        std::string boardStr;
        boardStr += " 1 2 3 4 5 6 7\n";
        boardStr += "+-+-+-+-+-+-+-+\n";
        for (const auto& row : board) {
            for (const auto& cell : row) {
                boardStr += "|";
                boardStr += cell;
            }
            boardStr += "|\n";
            boardStr += "+-+-+-+-+-+-+-+\n";
        }
        return boardStr;
    }

    int getLastMoveCol() const {
        return lastMoveCol;
    }

    int getMoveCount() const {
        return moveCount;
    }

private:
    std::vector<std::vector<char>> board;
    int lastMoveRow = -1;
    int lastMoveCol = -1;
    char lastPlayer = ' ';
    int moveCount;

    bool checkDirection(int rowDir, int colDir) {
        int count = 0;
        for (int i = -3; i <= 3; ++i) {
            int row = lastMoveRow + i * rowDir;
            int col = lastMoveCol + i * colDir;
            if (row >= 0 && row < ROWS && col >= 0 && col < COLS && board[row][col] == lastPlayer) {
                count++;
                if (count == 4) return true;
            } else {
                count = 0;
            }
        }
        return false;
    }
};

void handleClient(int newSocket, std::string clientIp, int clientPort) {
    Connect4Game game;
    char buffer[1024] = {0};

    std::cout << "Juego nuevo[" << clientIp << ":" << clientPort << "]\n";

    // Decidir de manera aleatoria quién pone la primera ficha
    bool clientTurn = rand() % 2 == 0;
    std::string response;
    if (clientTurn) {
        std::cout << "Juego [" << clientIp << ":" << clientPort << "]: inicia juego el cliente.\n";
        response = game.getBoardString();
        send(newSocket, response.c_str(), response.size(), 0);
    } else {
        std::cout << "Juego [" << clientIp << ":" << clientPort << "]: inicia juego el servidor.\n";
        game.makeRandomMove('S');
        std::cout << "Juego [" << clientIp << ":" << clientPort << "]: servidor juega columna " << (game.getLastMoveCol() + 1) << ".\n";
        response = game.getBoardString();
        send(newSocket, response.c_str(), response.size(), 0);
    }

    while (true) {
        memset(buffer, 0, sizeof(buffer));
        int valread = read(newSocket, buffer, 1024);
        if (valread <= 0) break;

        int col = atoi(buffer);
        std::cout << "Juego [" << clientIp << ":" << clientPort << "]: cliente juega columna " << col << ".\n";

        bool validMove = game.makeMove(col - 1, 'C');
        response.clear();
        if (validMove) {
            if (game.checkWin()) {
                response = game.getBoardString() + "Gana el Cliente!\n";
                send(newSocket, response.c_str(), response.size(), 0);
                std::cout << "Juego [" << clientIp << ":" << clientPort << "]: gana el cliente.\n";
                break;
            }
            if (game.getMoveCount() >= 21) {
                response = game.getBoardString() + "¡Empate!\n";
                send(newSocket, response.c_str(), response.size(), 0);
                std::cout << "Juego [" << clientIp << ":" << clientPort << "]: empate.\n";
                break;
            }
            game.makeRandomMove('S');
            std::cout << "Juego [" << clientIp << ":" << clientPort << "]: servidor juega columna " << (game.getLastMoveCol() + 1) << ".\n";
            if (game.checkWin()) {
                response = game.getBoardString() + "Gana el Servidor!\n";
                send(newSocket, response.c_str(), response.size(), 0);
                std::cout << "Juego [" << clientIp << ":" << clientPort << "]: gana el servidor.\n";
                break;
            }
            if (game.getMoveCount() >= 21) {
                response = game.getBoardString() + "¡Empate!\n";
                send(newSocket, response.c_str(), response.size(), 0);
                std::cout << "Juego [" << clientIp << ":" << clientPort << "]: empate.\n";
                break;
            }
            response = game.getBoardString();
        } else {
            response = "Movimiento inválido, intenta de nuevo.\n";
        }

        send(newSocket, response.c_str(), response.size(), 0);
    }
    close(newSocket);
}

int main(int argc, char const *argv[]) {
    int serverFd, newSocket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    if ((serverFd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Error al crear el socket");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("Error al adjuntar el socket al puerto");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(serverFd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Error en bind");
        exit(EXIT_FAILURE);
    }
    if (listen(serverFd, 3) < 0) {
        perror("Error en listen");
        exit(EXIT_FAILURE);
    }

    std::cout << "Servidor iniciado y esperando conexiones en el puerto " << PORT << "...\n";

    while (true) {
        if ((newSocket = accept(serverFd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
            perror("Error en accept");
            exit(EXIT_FAILURE);
        }

        struct sockaddr_in clientAddress;
        socklen_t clientAddressLen = sizeof(clientAddress);
        getpeername(newSocket, (struct sockaddr*)&clientAddress, &clientAddressLen);
        char clientIp[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &clientAddress.sin_addr, clientIp, INET_ADDRSTRLEN);
        int clientPort = ntohs(clientAddress.sin_port);

        std::thread clientThread(handleClient, newSocket, std::string(clientIp), clientPort);
        clientThread.detach();
    }

    return 0;
}
