#include <iostream>
#include <string>
#include <winsock2.h> //замена библиотек Ubuntu 
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

#define MESSAGE_LENGTH 1024
#define PORT 7777

// Функция сервера
void runServer() {
    WSADATA wsaData;
    SOCKET serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    int clientAddrLen = sizeof(clientAddr);
    char message[MESSAGE_LENGTH];

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cout << "Инициализация не удалась!" << endl;
        return;
    }

    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET) {
        cout << "Сокет не создался" << endl;
        WSACleanup();
        return;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        cout << "Не забиндилось" << endl;
        closesocket(serverSocket);
        WSACleanup();
        return;
    }

    if (listen(serverSocket, SOMAXCONN) == SOCKET_ERROR) {
        cout << "Прослушка не удалась!" << endl;
        closesocket(serverSocket);
        WSACleanup();
        return;
    }

    cout << "Сервер подключился к порту " << PORT << "..." << endl;

    clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);
    if (clientSocket == INVALID_SOCKET) {
        cout << "Соединение не удалось!" << endl;
        closesocket(serverSocket);
        WSACleanup();
        return;
    }

    cout << "Клиент подключился!" << endl;

    while (true) {
        memset(message, 0, MESSAGE_LENGTH);
        int bytesReceived = recv(clientSocket, message, MESSAGE_LENGTH, 0);

        if (bytesReceived > 0) {
            if (strncmp("end", message, 3) == 0) {
                cout << "Клиент отключился" << endl;
                break;
            }
            cout << "Сообщение: " << message << endl;

            cout << "Ответ: ";
            cin.getline(message, MESSAGE_LENGTH);
            send(clientSocket, message, static_cast<int>(strlen(message)), 0);
        }
        else {
            break;
        }
    }

    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();
}

// Функция клиента
void runClient() {
    WSADATA wsaData;
    SOCKET clientSocket;
    struct sockaddr_in serverAddr;
    char message[MESSAGE_LENGTH];

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cout << "Инициализация не удалась" << endl;
        return;
    }

    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET) {
        cout << "Сокет не создался" << endl;
        WSACleanup();
        return;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);

    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        cout << "Connection failed!" << endl;
        closesocket(clientSocket);
        WSACleanup();
        return;
    }

    cout << "Соединение с сервером успешно!" << endl;

    while (true) {
        cout << "Ваше сообщение ( 'end' чтобвы выйти): ";
        cin.getline(message, MESSAGE_LENGTH);

        if (strncmp(message, "end", 3) == 0) {
            send(clientSocket, message, static_cast<int>(strlen(message)), 0);
            break;
        }

        send(clientSocket, message, static_cast<int>(strlen(message)), 0);

        memset(message, 0, MESSAGE_LENGTH);
        recv(clientSocket, message, MESSAGE_LENGTH, 0);
        cout << "Сервер: " << message << endl;
    }

    closesocket(clientSocket);
    WSACleanup();
}

int main() {
    setlocale(LC_ALL, ""); // смена кодировки
    int choice;

    cout << "TCP Server/Client" << endl;
    cout << "1. Server запущен" << endl;
    cout << "2. Client запущен" << endl;
    cout << "Выберите 1 или 2: ";
    cin >> choice;
    cin.ignore(); // Очистка буфера

    if (choice == 1) {
        runServer();
    }
    else if (choice == 2) {
        runClient();
    }
    else {
        cout << "Неправильный выбор" << endl;
    }

    return 0;
}