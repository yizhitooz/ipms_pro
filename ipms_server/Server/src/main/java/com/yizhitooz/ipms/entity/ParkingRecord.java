package com.yizhitooz.ipms.entity;

import lombok.Builder;
import lombok.Data;

@Data
@Builder
public class ParkingRecord {
    private Integer id;
    private String plate;
    private String enterDateTime;
    private String exitDateTime;
    private Double fee;
    private String carType;
    private String carColor;
    private Integer parkingLotId;
}
