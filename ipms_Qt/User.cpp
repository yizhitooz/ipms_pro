#include "User.h"

User::User()
{
    // 可以在这里进行初始化
}

QString User::getUsername() const
{
    return m_username;
}

void User::setUsername(const QString &username)
{
    m_username = username;
}

QString User::getPassword() const
{
    return m_password;
}

void User::setPassword(const QString &password)
{
    m_password = password;
}

// 实现其他可能的用户信息和操作的函数
