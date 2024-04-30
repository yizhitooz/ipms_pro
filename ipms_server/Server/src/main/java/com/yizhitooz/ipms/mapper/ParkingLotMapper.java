package com.yizhitooz.ipms.mapper;

import com.yizhitooz.ipms.entity.ParkingLot;
import com.yizhitooz.ipms.service.ParkingLotService;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Select;
import org.springframework.beans.factory.annotation.Autowired;

import java.util.List;

@Mapper
public interface ParkingLotMapper {
    @Select("SELECT * FROM parkinglot")
    List<ParkingLot> selectAll();

    @Select("SELECT * FROM parkinglot WHERE id=#{id}")
    ParkingLot selectById(int id);
}
