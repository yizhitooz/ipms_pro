package com.yizhitooz.ipms.mapper;

import com.yizhitooz.ipms.entity.User;
import org.apache.ibatis.annotations.*;

import java.util.List;

@Mapper
public interface UserMapper {
    @Insert("INSERT INTO user (userID, account, userName, password, phoneNumber, level) " +
            "VALUES (#{userID}, #{account}, #{userName}, #{password}, #{phoneNumber}, #{level})")
    void insert(User user);

    @Update("UPDATE user " +
            "SET password = #{password}, phoneNumber = #{phoneNumber}, level = #{level} " +
            "WHERE userID = #{userID}")
    void updatePasswordPhoneLevel(User user);

    @Delete("DELETE FROM user WHERE userID = #{userID}")
    void delete(User user);

    @Delete("DELETE FROM user WHERE userID = #{userID}")
    void deleteByID(Integer userID);

    @Select("SELECT * FROM `user`")
    List<User> selectAll();

    @Select("SELECT * FROM `user` where level > 0")
    List<User> selectManager();

    @Select("SELECT * FROM user WHERE userID = #{id}")
    User selectById(Integer id);

    @Select("SELECT * FROM user WHERE account = #{account}")
    User selectByAccount(String account);
}
