package com.yizhitooz.ipms.entity;

import lombok.*;

/**
 * 用户类
 */
@Data
@Builder
public class User {
    private Integer userID; // 🔑
    private String account;
    private String userName;
    private String password;
    private String phoneNumber;
    private Integer level; // 权限级别
}
