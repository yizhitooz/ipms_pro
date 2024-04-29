package com.yizhitooz.ipms.service;

import com.yizhitooz.ipms.mapper.VehicleMapper;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
public class ParkingRecordService {
    @Autowired
    private VehicleMapper vehicleMapper;
}
