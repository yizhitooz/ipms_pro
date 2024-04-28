package com.yizhitooz.ipms.entity;

import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@Builder
public class ParkingLot {
    private int parkingLotId;
    private int maxCarPark;
    private int currentCarPark;
    private String location;
}
