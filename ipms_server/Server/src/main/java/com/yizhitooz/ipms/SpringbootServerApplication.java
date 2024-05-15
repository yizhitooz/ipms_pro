package com.yizhitooz.ipms;

import com.yizhitooz.ipms.mqtt.MqttSubscriber;
import jakarta.annotation.PostConstruct;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

@SpringBootApplication
public class SpringbootServerApplication {

    @Autowired
    private MqttSubscriber mqttSubscriber;

    public static void main(String[] args) {
        SpringApplication.run(SpringbootServerApplication.class, args);
    }

    @PostConstruct
    public void init() {
        mqttSubscriber.subscribe();
    }
}
