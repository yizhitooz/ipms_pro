package com.yizhitooz.ipms.entity;

import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@NoArgsConstructor
public class CarPark {
    private String plate;
    private int id;
    private String location;
    private int parkingLotId;
}
