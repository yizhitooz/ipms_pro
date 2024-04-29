package com.yizhitooz.ipms.controller;

import com.yizhitooz.ipms.service.CarParkService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class CarParkController {
    @Autowired
    CarParkService carParkService;

}
