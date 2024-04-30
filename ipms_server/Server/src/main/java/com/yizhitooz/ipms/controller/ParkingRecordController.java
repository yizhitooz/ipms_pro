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

    @PostMapping("/search")
    public Result searchParkingRecord(@RequestBody ParkingRecord parkingRecord) {
        ParkingRecord parkingRecordOnServer = parkingRecordService.selectById(parkingRecord.getId());
        if (parkingRecordOnServer == null) {
            return Result.error();
        } else if (parkingRecord.getPlate().equals(parkingRecordOnServer.getPlate())) {
            return Result.success(parkingRecordOnServer);
        } else {
            return Result.error();
        }
    }

    @PostMapping("/exit")
    public Result exitParkingRecord(@RequestBody ParkingRecord parkingRecord) {
        ParkingRecord parkingRecordOnServer = parkingRecordService.selectById(parkingRecord.getId());
        if (parkingRecordOnServer == null) {
            return Result.error();
        }
        parkingRecordOnServer.setExitDateTime(LocalDateTime.now().format(dtf));
        Vehicle vehicle = vehicleService.search(parkingRecordOnServer.getPlate());
        LocalDateTime dueDateTime = LocalDateTime.parse(vehicle.getDueDate(), dtf);
        LocalDateTime currentDateTime = LocalDateTime.now();
        String enterDateTimeString = parkingRecordOnServer.getEnterDateTime();
        LocalDateTime enterDateTime = LocalDateTime.parse(enterDateTimeString, dtf);
        Duration duration = Duration.between(enterDateTime, currentDateTime);
        Double parkingHours = (double) (duration.toMinutes() / 60);

        Double parkingFee = (parkingHours / 24) * 60 + (parkingHours % 24) * 2;
        parkingRecordOnServer.setFee(parkingFee);

        if (dueDateTime.isAfter(currentDateTime)) {
            parkingRecordOnServer.setFee(0.00);
        }

        parkingRecordService.updateWhenExit(parkingRecordOnServer);
        return Result.success(parkingRecordOnServer);
    }

    @PostMapping("/enter")
    public Result enterParkingRecord(@RequestBody ParkingRecord parkingRecord) {
        if (parkingRecord.getPlate() == null) {
            return Result.error();
        } else {
            Vehicle vehicleOnServer = vehicleService.search(parkingRecord.getPlate());
            if (vehicleOnServer == null) {
                vehicleOnServer = Vehicle.builder().plate(parkingRecord.getPlate()).build();
                vehicleService.insert(vehicleOnServer);
            }
        }
        List<ParkingRecord> parkingRecordsOnServer =parkingRecordService.getByPlate(parkingRecord.getPlate());
        if(!parkingRecordsOnServer.isEmpty()){
            return Result.error("车辆已经入库");
        }
        parkingRecord.setEnterDateTime(LocalDateTime.now().format(dtf));
        parkingRecordService.addParkingRecord(parkingRecord);
        return Result.success(parkingRecord);
    }
}
