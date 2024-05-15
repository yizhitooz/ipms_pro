package com.yizhitooz.ipms.mapper;

import com.yizhitooz.ipms.entity.ParkingLot;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Select;
import org.apache.ibatis.annotations.Update;

import java.util.List;

@Mapper
public interface ParkingLotMapper {
    @Select("SELECT * FROM parkinglot")
    List<ParkingLot> selectAll();

    @Select("SELECT * FROM parkinglot WHERE id=#{id}")
    ParkingLot selectById(int id);

    @Update("UPDATE parkinglot SET currentCarPark = #{currentCarPark} WHERE id = #{parkingLotId}")
    void updateCarPark(Integer parkingLotId, Integer currentCarPark);
}
