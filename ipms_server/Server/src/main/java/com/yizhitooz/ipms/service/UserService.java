package com.yizhitooz.ipms.service;

import com.yizhitooz.ipms.entity.User;
import com.yizhitooz.ipms.mapper.UserMapper;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.sql.SQLException;
import java.util.List;

@Service
public class UserService {

    @Autowired
    private UserMapper userMapper;

    public void insertUser(User user) throws SQLException {
        userMapper.insert(user);
    }

    public void updatePasswordPhoneLevel(User user) throws SQLException {
        userMapper.updatePasswordPhoneLevel(user);
    }

    public void delete(Integer id) throws SQLException {
        userMapper.deleteByID(id);
    }

    public void delete(List<Integer> ids) throws SQLException {
        for (Integer id : ids) {
            userMapper.deleteByID(id);
        }
    }

    public List<User> select() throws SQLException {
        return userMapper.selectAll();
    }

    public User select(Integer id) throws SQLException {
        return userMapper.selectById(id);
    }

    public User select(String account) throws SQLException {
        return userMapper.selectByAccount(account);
    }

    public List<User> selectManager() throws SQLException {
        return userMapper.selectManager();
    }
}
