package com.yizhitooz.ipms.entity;

import lombok.Builder;
import lombok.Data;

@Data
@Builder
public class ParkingLot {
    private int parkingLotId;
    private int maxCarPark;
    private int currentCarPark;
    private String location;
}
