#ifndef USERS_H
#define USERS_H

#include <string>
#include <vector>
#include <unordered_map>

class Users {
public:
    Users() = default;

    // Добавление пользователя
    void addUser(const std::string& name, const std::string& password, int age = 0);

    // Проверка существования пользователя
    bool userExists(const std::string& name) const;

    // Проверка пароля
    bool checkPassword(const std::string& name, const std::string& password) const;

    // Получение ID пользователя
    int getUserId(const std::string& name) const;

    // Получение имени по ID
    std::string getUserName(int id) const;

    // Получение всех пользователей
    const std::vector<std::string>& getAllUsers() const;

    // Количество пользователей
    size_t getUserCount() const;

private:
    struct UserInfo {
        std::string name;
        std::string password;
        int age;
    };

    std::vector<UserInfo> users_;
    std::unordered_map<std::string, int> nameToId_; // имя -> индекс в векторе
};

#endif


