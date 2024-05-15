package com.yizhitooz.ipms.controller;

import com.yizhitooz.ipms.common.Result;
import com.yizhitooz.ipms.entity.ParkingLot;
import com.yizhitooz.ipms.service.ParkingLotService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import java.util.List;

@RestController
@RequestMapping("/parking/lot")
public class ParkingLotController {
    @Autowired
    ParkingLotService parkingLotService;

    @GetMapping("search/all")
    public Result searchAll() {
        List<ParkingLot> parkingLots = parkingLotService.getAllParkingLot();
        if (!parkingLots.isEmpty()) {
            return Result.success(parkingLots);
        } else {
            return Result.error();
        }
    }

    @GetMapping("search/id/{id}")
    public Result searchById(@PathVariable Integer id) {
        ParkingLot parkingLot = parkingLotService.getParkingLot(id);
        if (parkingLot != null) {
            return Result.success(parkingLot);
        } else {
            return Result.error();
        }
    }

    @GetMapping("/update/{parkingLotId}")
    public Result updateParkingLot(@PathVariable Integer parkingLotId) {
        ParkingLot parkingLot = parkingLotService.getParkingLot(parkingLotId);
        if (parkingLot != null) {
            parkingLotService.updateParkingLotCarPark(parkingLot);
            parkingLot = parkingLotService.getParkingLot(parkingLotId);
            return Result.success(parkingLot);
        } else {
            return Result.error();
        }
    }
}
