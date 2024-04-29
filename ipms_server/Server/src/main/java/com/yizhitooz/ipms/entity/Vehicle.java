package com.yizhitooz.ipms.entity;

import lombok.Builder;
import lombok.Data;

@Data
@Builder
public class Vehicle {
    private String plate;
    private Integer ownerId;
    private String dueDate;
}
