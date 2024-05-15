package com.yizhitooz.ipms.controller;

import com.yizhitooz.ipms.common.Result;
import com.yizhitooz.ipms.entity.CarPark;
import com.yizhitooz.ipms.service.CarParkService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import java.util.List;

@RestController
@RequestMapping("/carpark")
public class CarParkController {
    @Autowired
    CarParkService carParkService;

    @GetMapping("/plate/{plate}")
    public Result getCarParkByPlate(@PathVariable String plate) {
        List<CarPark> carParks = carParkService.getCarParkByPlate(plate);
        if (carParks.isEmpty()) {
            return Result.error("没有记录");
        } else if (carParks.size() > 1) {
            return Result.error("有多个记录");
        }else{
            return Result.success(carParks.getFirst());
        }
    }
}
