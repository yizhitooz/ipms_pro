package com.yizhitooz.ipms.entity;

import lombok.AllArgsConstructor;
import lombok.Builder;
import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@Builder
public class carPark {
    private String plate;
    private int id;
    private String location;
    private int parkingLotId;
}
