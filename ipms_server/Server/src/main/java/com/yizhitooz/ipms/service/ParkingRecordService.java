package com.yizhitooz.ipms.service;

import com.yizhitooz.ipms.entity.ParkingRecord;
import com.yizhitooz.ipms.mapper.ParkingRecordMapper;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
public class ParkingRecordService {
    @Autowired
    private ParkingRecordMapper parkingRecordMapper;

    public ParkingRecord selectById(Integer id) {
        return parkingRecordMapper.selectById(id);
    }

    public int updateWhenExit(ParkingRecord parkingRecord) {
        return parkingRecordMapper.
                updateExitDateTimeAndFee(parkingRecord.getPlate(),
                                         parkingRecord.getExitDateTime(),
                                         parkingRecord.getFee());
    }
}
