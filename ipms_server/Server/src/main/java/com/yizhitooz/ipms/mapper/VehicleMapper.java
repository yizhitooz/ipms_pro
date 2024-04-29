package com.yizhitooz.ipms.mapper;

import com.yizhitooz.ipms.entity.Vehicle;
import org.apache.ibatis.annotations.Insert;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Select;
import org.apache.ibatis.annotations.Update;

@Mapper
public interface VehicleMapper {
    @Select("SELECT * FROM vehicle WHERE plate = #{plate}")
    Vehicle selectByPlate(String plate);

    /**
     * 更新车辆车位租赁到期日
     */
    @Update("UPDATE vehicle SET dueDate = #{dueDate} WHERE plate = #{plate}")
    int update(Vehicle vehicle);

    @Insert("INSERT INTO vehicle (plate, ownerId, dueDate) VALUES (#{plate}, #{ownerId}, #{dueDate}")
    void insert(Vehicle vehicle);

    /**
     *
     */
    @Update()
}
