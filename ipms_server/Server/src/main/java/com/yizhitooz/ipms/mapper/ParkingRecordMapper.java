package com.yizhitooz.ipms.mapper;

import com.yizhitooz.ipms.entity.ParkingRecord;
import org.apache.ibatis.annotations.Insert;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Select;
import org.apache.ibatis.annotations.Update;

import java.util.List;

@Mapper
public interface ParkingRecordMapper {
    @Insert("INSERT INTO parkingrecord (plate, enterDateTime, ExitDateTime, fee, carType, CarColor, parkinglotId) " +
            "VALUES (#{plate}, #{enterDateTime}, #{exitDateTime}, #{fee}, #{carType}, #{carColor}, #{parkingLotId})")
    int insert(ParkingRecord parkingRecord);

    @Update("UPDATE parkingrecord " +
            "SET ExitDateTime = #{exitDateTime}, fee = #{fee} " +
            "WHERE plate = #{plate} AND ExitDateTime IS NULL")
    int updateExitDateTimeAndFee(String plate, String exitDateTime, double fee);

    @Select("SELECT * FROM parkingrecord WHERE id = #{id}")
    ParkingRecord selectById(Integer id);

    @Select("SELECT * FROM  parkingrecord WHERE plate= #{plate} AND exitDateTime IS NULL")
    List<ParkingRecord> selectByPlate(String plate);

    @Select("SELECT * FROM  parkingrecord WHERE plate= #{plate}")
    List<ParkingRecord> selectByPlateAll(String plate);
}
