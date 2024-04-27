#ifndef USER_H
#define USER_H

#include <QString>

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

    // 其他可能的用户信息和操作

private:
    QString m_username;
    QString m_password;
    // 其他可能的用户属性
};

#endif // USER_H
