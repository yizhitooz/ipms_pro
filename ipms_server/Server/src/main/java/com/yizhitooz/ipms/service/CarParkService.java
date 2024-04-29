package com.yizhitooz.ipms.service;

import com.yizhitooz.ipms.mapper.CarParkMapper;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
public class CarParkService {
    @Autowired
    private CarParkMapper carParkMapper;
}
