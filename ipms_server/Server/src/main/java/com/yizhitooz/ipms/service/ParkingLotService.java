package com.yizhitooz.ipms.service;

import com.yizhitooz.ipms.entity.ParkingLot;
import com.yizhitooz.ipms.mapper.CarParkMapper;
import com.yizhitooz.ipms.mapper.ParkingLotMapper;
import com.yizhitooz.ipms.mapper.ParkingRecordMapper;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

@Service
public class ParkingLotService {
    @Autowired
    ParkingLotMapper parkingLotMapper;
    @Autowired
    CarParkMapper carParkMapper;

    public ParkingLot getParkingLot(int id) {
        return parkingLotMapper.selectById(id);
    }

    public List<ParkingLot> getAllParkingLot() {
        return parkingLotMapper.selectAll();
    }

    public void updateParkingLotCarPark(ParkingLot parkingLot) {
       Integer current = carParkMapper.countNotNullPlates(parkingLot.getId());
       parkingLotMapper.updateCarPark(parkingLot.getId(), current);
    }
}
