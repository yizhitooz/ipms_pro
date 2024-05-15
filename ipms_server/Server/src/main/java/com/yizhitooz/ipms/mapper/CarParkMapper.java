package com.yizhitooz.ipms.mapper;

import com.yizhitooz.ipms.entity.CarPark;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Select;
import org.apache.ibatis.annotations.Update;

import java.util.List;

@Mapper
public interface CarParkMapper {
    @Update("UPDATE carpark SET plate = #{plate} WHERE id = #{id}")
    void updateCarParkPlateById(int id, String plate);

    @Select("SELECT id, plate, ST_AsText(location) as location, parkinglotId FROM carpark WHERE plate = #{plate}")
    List<CarPark> getCarParkByPlate(String plate);

    @Select("SELECT COUNT(*) FROM carpark WHERE plate IS NOT NULL AND parkinglotId = #{parkingLotId}")
    int countNotNullPlates(Integer parkingLotId);
}
