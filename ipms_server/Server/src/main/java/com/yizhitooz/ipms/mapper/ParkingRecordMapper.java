package com.yizhitooz.ipms.mapper;

import com.yizhitooz.ipms.entity.ParkingRecord;
import org.apache.ibatis.annotations.Insert;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Update;

@Mapper
public interface ParkingRecordMapper {
    @Insert("INSERT INTO parkingrecord (plate, enterDateTime, ExitDateTime, fee, carType, CarColor, parkinglotId) " +
            "VALUES (#{plate}, #{enterDateTime}, #{ExitDateTime}, #{fee}, #{carType}, #{CarColor}, #{parkinglotId})")
    int insert(ParkingRecord parkingRecord);

    @Update("UPDATE parkingrecord " +
            "SET ExitDateTime = #{exitDateTime}, fee = #{fee} " +
            "WHERE plate = #{plate} AND ExitDateTime IS NULL")
    int updateExitDateTimeAndFee(String plate, String exitDateTime, double fee);
}
