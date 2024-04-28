package com.yizhitooz.ipms.entity;

import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

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
