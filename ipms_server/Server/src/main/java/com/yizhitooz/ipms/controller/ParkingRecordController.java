package com.yizhitooz.ipms.controller;

import com.yizhitooz.ipms.common.Result;
import com.yizhitooz.ipms.entity.ParkingRecord;
import com.yizhitooz.ipms.entity.Vehicle;
import com.yizhitooz.ipms.service.ParkingRecordService;
import com.yizhitooz.ipms.service.VehicleService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import java.time.Duration;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.List;

@RestController
@RequestMapping(("/parking/record"))
public class ParkingRecordController {
    DateTimeFormatter dtf = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");
    @Autowired
    ParkingRecordService parkingRecordService;
    @Autowired
    VehicleService vehicleService;

    @PostMapping("/search/id")
    public Result searchParkingRecordById(@RequestBody ParkingRecord parkingRecord) {
        ParkingRecord parkingRecordOnServer = parkingRecordService.getById(parkingRecord.getId());
        if (parkingRecordOnServer == null) {
            return Result.error();
        } else if (parkingRecord.getPlate().equals(parkingRecordOnServer.getPlate())) {
            return Result.success(parkingRecordOnServer);
        } else {
            return Result.error();
        }
    }

    @PostMapping("/search/all")
    public Result searchParkingRecordByPlateAll(@RequestBody ParkingRecord parkingRecord) {
        List<ParkingRecord> parkingRecordsOnServer = parkingRecordService.getByPlateAll(parkingRecord.getPlate());
        if (parkingRecordsOnServer.isEmpty()) {
           return Result.error("找不到记录");
        } else{
            return Result.success(parkingRecordsOnServer);
        }
    }


    @PostMapping("/exit")
    public Result userExitParkingRecord(@RequestBody ParkingRecord parkingRecord) {
        List<ParkingRecord> parkingRecordsOnServer = parkingRecordService.getByPlate(parkingRecord.getPlate());
        if (parkingRecordsOnServer.isEmpty()) {
            return Result.error("没有相关的登记信息");
        } else if (parkingRecordsOnServer.size() > 1) {
            return Result.error("有多个登记信息");
        }
        if (parkingRecord.getParkingLotId()==null) {
            parkingRecord.setParkingLotId(parkingRecordsOnServer.get(0).getId());
        }
        ParkingRecord parkingRecordOnServer = parkingRecordsOnServer.get(0);
        parkingRecordOnServer.setExitDateTime(LocalDateTime.now().format(dtf));
        Vehicle vehicle = vehicleService.search(parkingRecordOnServer.getPlate());
        String enterDateTimeString = parkingRecordOnServer.getEnterDateTime();
        LocalDateTime enterDateTime = LocalDateTime.parse(enterDateTimeString, dtf);
        LocalDateTime currentDateTime = LocalDateTime.now();
        Duration duration = Duration.between(enterDateTime, currentDateTime);
        Double parkingHours = (double) (duration.toMinutes() / 60);
        Double parkingFee = (parkingHours / 24) * 60 + (parkingHours % 24) * 2;

        parkingRecordOnServer.setFee(parkingFee);
        if (vehicle.getDueDate() != null) {
            LocalDateTime dueDateTime = LocalDateTime.parse(vehicle.getDueDate(), dtf);
            if (dueDateTime.isAfter(currentDateTime)) {
                parkingRecordOnServer.setFee(0.00);
            }
        }

        parkingRecordService.updateWhenExit(parkingRecordOnServer);
        return Result.success(parkingRecordOnServer);
    }

    @PostMapping("/enter")
    public Result enterParkingRecord(@RequestBody ParkingRecord parkingRecord) {
        if (parkingRecord.getPlate() == null) {
            return Result.error("传入的车牌号为空");
        } else {
            Vehicle vehicleOnServer = vehicleService.search(parkingRecord.getPlate());
            if (vehicleOnServer == null) {
                vehicleOnServer = Vehicle.builder().plate(parkingRecord.getPlate()).build();
                vehicleService.insert(vehicleOnServer);
            }
        }
        List<ParkingRecord> parkingRecordsOnServer = parkingRecordService.getByPlate(parkingRecord.getPlate());
        if (!parkingRecordsOnServer.isEmpty()) {
            return Result.error("车辆已经入库");
        }
        parkingRecord.setEnterDateTime(LocalDateTime.now().format(dtf));
        parkingRecordService.addParkingRecord(parkingRecord);
        return Result.success(parkingRecord);
    }
}
