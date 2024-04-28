#ifndef USER_H
#define USER_H

#include <QString>

/**
 * @brief 权限枚举
 */
enum class PermissionLevel {
    Guest = 0,
    User = 3,
    Moderator = 2,
    Admin = 1
};


class User
{
public:
    User();

    // 设置和获取用户名
    QString getUsername() const;
    void setUsername(const QString &username);

    // 设置和获取密码
    QString getPassword() const;
    void setPassword(const QString &password);

    // 设置和获取权限级别
    PermissionLevel getPermissionLevel() const;
    void setPermissionLevel(PermissionLevel level);

private:
    QString m_username;
    QString m_password;
    PermissionLevel m_level; // 权限级别

};

#endif // USER_H
