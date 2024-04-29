package com.yizhitooz.ipms.controller;

import com.yizhitooz.ipms.service.ParkingRecordService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.RestController;

@RestController("parking/record")
public class ParkingRecordController {
    @Autowired
    ParkingRecordService parkingRecordService;

}
