package com.yizhitooz.ipms.entity;

import lombok.Builder;
import lombok.Data;

@Data
@Builder
public class ParkingLot {
    private Integer id;
    private String name;
    private Integer maxCarPark;
    private Integer currentCarPark;
    private String location;
}
