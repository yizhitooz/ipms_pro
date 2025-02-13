package com.yizhitooz.ipms.controller;

import com.yizhitooz.ipms.common.Result;
import com.yizhitooz.ipms.entity.User;
import com.yizhitooz.ipms.service.UserService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.sql.SQLException;
import java.util.List;

@RestController
@RequestMapping("/user")
public class UserController {
    @Autowired
    UserService userService;

    @PostMapping("/add")
    public Result add(@RequestBody User user) {
        try {
            userService.insertUser(user);
            return Result.success();
        } catch (SQLException e) {
            return Result.error("数据库错误: " + e.getMessage());
        } catch (Exception e) {
            return Result.error("其他错误: " + e.getMessage());
        }
    }

    @PostMapping("/change")
    public Result changePasswordPhoneLevel(@RequestBody User user) {
        try {
            User userOnServer = userService.select(user.getAccount());
            // 判断密码需不需要更改
            if(user.getPassword()!=null&&!user.getPassword().equals(userOnServer.getPassword())){
                userOnServer.setPassword(user.getPassword());
            }
            // 判断电话需不要更改
            if(user.getPhoneNumber()!=null&&!user.getPhoneNumber().equals(userOnServer.getPassword())){
                userOnServer.setPhoneNumber(user.getPhoneNumber());
            }
            // 判断权限等级是否需要更改
            if(user.getLevel()!=null&&!user.getLevel().equals(userOnServer.getLevel())){
                userOnServer.setLevel(user.getLevel());
            }
            userService.updatePasswordPhoneLevel(userOnServer);
            return Result.success(userOnServer);
        } catch (SQLException e) {
            return Result.error("数据库错误: " + e.getMessage());
        } catch (Exception e) {
            return Result.error("其他错误: " + e.getMessage());
        }
    }

    @PostMapping("/delete/{id}")
    Result delete(@PathVariable Integer id) {
        try {
            userService.delete(id);
            return Result.success();
        } catch (SQLException e) {
            return Result.error("数据库错误: " + e.getMessage());
        } catch (Exception e) {
            return Result.error("其他错误: " + e.getMessage());
        }
    }

    @PostMapping("/delete/batch")
    public Result delete(@RequestBody List<Integer> ids) {
        try {
            userService.delete(ids);
            return Result.success();
        } catch (SQLException e) {
            return Result.error("数据库错误: " + e.getMessage());
        } catch (Exception e) {
            return Result.error("其他错误: " + e.getMessage());
        }
    }

    @GetMapping("/search/all")
    public Result selectAll() {
        try {
            List<User> users = userService.select();
            User user = users.get(0);
            System.out.println("name:" + user.getUserName());
            return Result.success(users);
        } catch (SQLException e) {
            return Result.error("数据库错误: " + e.getMessage());
        } catch (Exception e) {
            return Result.error("其他错误: " + e.getMessage());
        }
    }

    @GetMapping("/search/manager")
    public Result selectManager() {
        try {
            List<User> users = userService.selectManager();
            return Result.success(users);
        } catch (SQLException e) {
            return Result.error("数据库错误: " + e.getMessage());
        } catch (Exception e) {
            return Result.error("其他错误: " + e.getMessage());
        }
    }

    @GetMapping("/search/id/{id}")
    public Result selectByID(@PathVariable Integer id) {
        try {
            User user = userService.select(id);
            return Result.success(user);
        } catch (SQLException e) {
            return Result.error("数据库错误: " + e.getMessage());
        } catch (Exception e) {
            return Result.error("其他错误: " + e.getMessage());
        }
    }

    @GetMapping("/search/account/{account}")
    public Result selectByID(@PathVariable String account) {
        try {
            User user = userService.select(account);
            return Result.success(user);
        } catch (SQLException e) {
            return Result.error("数据库错误: " + e.getMessage());
        } catch (Exception e) {
            return Result.error("其他错误: " + e.getMessage());
        }
    }

    @PostMapping("/login/")
    public Result login(@RequestBody User user) throws SQLException {
        User userOnServer = userService.select(user.getAccount());
        if (userOnServer.getPassword().equals(user.getPassword())) {
            user.setLevel(userOnServer.getLevel());
            return Result.success(user);
        } else
            return Result.error();
    }
}
