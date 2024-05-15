package com.yizhitooz.ipms.service;

import com.yizhitooz.ipms.entity.CarPark;
import com.yizhitooz.ipms.mapper.CarParkMapper;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class CarParkService {
    @Autowired
    private CarParkMapper carParkMapper;

    public void updateCarParkPlateById(int id, String plate) {
        carParkMapper.updateCarParkPlateById(id, plate);
    }

    public List<CarPark> getCarParkByPlate(String plate) {
        return carParkMapper.getCarParkByPlate(plate);
    }
}
