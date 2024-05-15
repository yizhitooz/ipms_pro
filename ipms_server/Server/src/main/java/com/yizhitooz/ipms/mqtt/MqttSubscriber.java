package com.yizhitooz.ipms.mqtt;

import com.fasterxml.jackson.databind.ObjectMapper;
import com.yizhitooz.ipms.entity.CarPark;
import com.yizhitooz.ipms.service.CarParkService;
import org.eclipse.paho.client.mqttv3.*;
import org.eclipse.paho.client.mqttv3.persist.MemoryPersistence;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Component;

@Component
public class MqttSubscriber {

    @Autowired
    CarParkService carParkService;
    @Value("${spring.mqtt.broker}")
    private String broker;
    @Value("${spring.mqtt.clientId}")
    private String clientId;
    @Value("${spring.mqtt.topic}")
    private String topic;

    public void subscribe() {
        try {
            IMqttClient mqttClient = new MqttClient(broker, clientId, new MemoryPersistence());
            mqttClient.setCallback(new MqttCallback() {
                @Override
                public void connectionLost(Throwable cause) {
                    System.out.println("Connection lost: " + cause.getMessage());
                }

                @Override
                public void messageArrived(String topic, MqttMessage message) throws Exception {
                    System.out.println("Message received on topic " + topic + ": " + new String(message.getPayload()));
                    try {
                        ObjectMapper objectMapper = new ObjectMapper();
                        CarPark carPark = objectMapper.readValue(message.getPayload(), CarPark.class);
                        int carParkId = carPark.getId();
                        String plate = carPark.getPlate();
                        if (carParkId != 0) {
                            carParkService.updateCarParkPlateById(carParkId, plate);
                        }
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                }

                @Override
                public void deliveryComplete(IMqttDeliveryToken token) {
                    // 消息传递完成
                }
            });

            MqttConnectOptions connOpts = new MqttConnectOptions();
            connOpts.setCleanSession(true);
            System.out.println("Connecting to broker: " + broker);
            mqttClient.connect(connOpts);
            System.out.println("Connected");

            mqttClient.subscribe(topic);
            System.out.println("Subscribed to topic: " + topic);
        } catch (MqttException e) {
            System.out.println("Error subscribing to MQTT topic: " + e.getMessage());
        }
    }
}
