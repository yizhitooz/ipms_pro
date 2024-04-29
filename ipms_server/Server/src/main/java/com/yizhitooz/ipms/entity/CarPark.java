package com.yizhitooz.ipms.entity;

import lombok.Builder;
import lombok.Data;

@Data
@Builder
public class CarPark {
    private String plate;
    private int id;
    private String location;
    private int parkingLotId;
}
