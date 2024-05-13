package com.yizhitooz.ipms.mqtt;

import org.springframework.integration.annotation.MessageEndpoint;
import org.springframework.integration.annotation.ServiceActivator;
import org.springframework.messaging.Message;

@MessageEndpoint
public class MqttSubscriber {

    @ServiceActivator(inputChannel = "mqttInputChannel")
    public void messageReceiver(Message<String> message) {
        System.out.println("Received MQTT message: " + message.getPayload());
        // 在这里处理你的消息逻辑
    }
}
