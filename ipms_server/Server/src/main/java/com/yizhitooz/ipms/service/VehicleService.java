package com.yizhitooz.ipms.service;

import com.yizhitooz.ipms.entity.Vehicle;
import com.yizhitooz.ipms.mapper.VehicleMapper;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
public class VehicleService {
    @Autowired
    private VehicleMapper vehicleMapper;

    public Vehicle search(String plate) {
        return vehicleMapper.selectByPlate(plate);
    }

    public void insert(Vehicle vehicle) {
        vehicleMapper.insert(vehicle);
    }

    public void update(Vehicle vehicle) {
        vehicleMapper.update(vehicle);
    }
}
