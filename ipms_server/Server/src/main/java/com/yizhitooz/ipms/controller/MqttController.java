package com.yizhitooz.ipms.controller;

import com.yizhitooz.ipms.mqtt.MqttGateway;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class MqttController {

    @Autowired
    private MqttGateway mqttGateway;

    @GetMapping("/send-message")
    public String sendMessage(@RequestParam String message) {
        mqttGateway.sendToMqtt(message);
        return "Message sent to MQTT: " + message;
    }
}
