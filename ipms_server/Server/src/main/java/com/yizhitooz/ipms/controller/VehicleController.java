package com.yizhitooz.ipms.controller;

import com.yizhitooz.ipms.common.Result;
import com.yizhitooz.ipms.entity.Vehicle;
import com.yizhitooz.ipms.service.VehicleService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.time.temporal.ChronoUnit;


@RestController
@RequestMapping("/vehicle")
public class VehicleController {
    @Autowired
    VehicleService vehicleService;

    /**
     * 更新车辆车位租赁到期日
     *
     * @param vehicle
     * @return
     */
    @PostMapping("/charge")
    public Result selectVehicleCharge(@RequestBody Vehicle vehicle) {
        DateTimeFormatter dtf = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");
        String plate = vehicle.getPlate();
        Vehicle vehicleOnServer = vehicleService.search(plate);
        if (vehicleOnServer != null) {
            if (vehicleOnServer.getDueDate() == null) {
                vehicleOnServer.setDueDate(dtf.format(LocalDateTime.now()));
            }
            LocalDateTime dueDateOnServer = LocalDateTime.parse(vehicleOnServer.getDueDate(), dtf); // 服务器上的到期日期
            LocalDateTime dueDate = LocalDateTime.parse(vehicle.getDueDate(), dtf);// 客户端传入的到期日期
            LocalDateTime currentDate = LocalDateTime.now();
            // 到期日期与当前日期的关系
            if (dueDateOnServer.isBefore(currentDate)) {
                // 到期日期（server）比当前日期早, 使用客户端传入的到期日期
                vehicleOnServer.setDueDate(vehicle.getDueDate());
                vehicleService.update(vehicleOnServer);
            } else {
                // 到期日期（server）比当前日期晚, 计算日期差
                long daysDifference = ChronoUnit.DAYS.between(dueDateOnServer, dueDate);
                // 传入日期加上日期差
                LocalDateTime newDueDateTime = dueDate.plusDays(daysDifference);
                vehicle.setDueDate(newDueDateTime.format(dtf));
                vehicleService.update(vehicle);
            }
        } else {
            vehicleService.insert(vehicle);
        }
        return Result.success(vehicle);
    }

    @PostMapping("/search")
    public Result selectVehicle(@RequestBody Vehicle vehicle) {
        Vehicle vehicleOnServer = vehicleService.search(vehicle.getPlate());
        return Result.success(vehicleOnServer);
    }
}
