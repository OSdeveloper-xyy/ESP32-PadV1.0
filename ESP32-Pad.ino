#include <Arduino.h>
#include "BasicServer.h"
uint8_t r = 255 , g = 0 , b = 0;
ServerLTE         LTE0;
ServerCodec       CODEC0;
void IRAM_ATTR PowerButtonISR(){
    return;
}
void IRAM_ATTR VoiceUpButtonISR(){
    return;
}
void IRAM_ATTR VoiceDownButtonISR(){
    return;
}void WakeUp(){
    esp_sleep_wakeup_cause_t WakeUpCause = esp_sleep_get_wakeup_cause();
    unsigned long StartupTime = millis();
    rtc_gpio_deinit(BUTTON_POWER);
    pinMode(BUTTON_POWER,INPUT_PULLUP);
    delay(10);
    Serial.begin(115200);
    Serial.println("ESP32 Wake Up!");
    if(WakeUpCause == ESP_SLEEP_WAKEUP_UNDEFINED){
        Serial.println("WakeCause:Just Power On!");
        Serial.println("Jump To Deep Sleep......");
        esp_sleep_enable_ext0_wakeup(BUTTON_POWER,0);
        rtc_gpio_pullup_en(BUTTON_POWER);
        rtc_gpio_pulldown_dis(BUTTON_POWER);
        esp_deep_sleep_start();
    }else if(WakeUpCause == ESP_SLEEP_WAKEUP_EXT0){
        Serial.println("WakeCause:Power Button Press!");
        while((millis() - StartupTime) < 3000){
            if(digitalRead(BUTTON_POWER) == HIGH){
                Serial.println("Power Button Press Less 3s,Get Into Deep Sleep...");
                esp_sleep_enable_ext0_wakeup(BUTTON_POWER,0);
                rtc_gpio_pullup_en(BUTTON_POWER);
                rtc_gpio_pulldown_dis(BUTTON_POWER);
                esp_deep_sleep_start();
            }
        }
    }else{
        Serial.println("WakeCause:Unkown,Get Into Deep Sleep...");
        esp_sleep_enable_ext0_wakeup(BUTTON_POWER,0);
        rtc_gpio_pullup_en(BUTTON_POWER);
        rtc_gpio_pulldown_dis(BUTTON_POWER);
        esp_deep_sleep_start();
    }
    return;
}void BootInit(){
    Serial.println("SPI Initialize......");
    SPI.begin(SPI_SCLK,SPI_MISO,SPI_MOSI,-1);
    Serial.println("SPI Initialization successful!");
    Serial.println("Mount ESP32 FAT FS......");
    FFat.begin(true);
    Serial.println("Mount ESP32 FAT FS Successfully!");

    Serial.println("USB Host Initialize......");
    if(USBINIT() == false)Serial.println("USB Initialization failed");
    else Serial.println("USB Initialization successful!");

    Serial.println("Codec Initialize......");
    if(CODEC0.INIT() == false)Serial.println("Codec Initialization failed");
    else Serial.println("USB Initialization successful!");

    Serial.println("LTE Initialize......");
    if(LTE0.INIT() == false)Serial.println("LTE Initialization failed");
    else Serial.println("LTE Initialization successful!");

    Serial.println("Button Pin Initialize......");
    SetInt(BUTTON_POWER,PowerButtonISR);
    SetInt(BUTTON_V_UP,VoiceUpButtonISR);
    SetInt(BUTTON_V_DOWN,VoiceDownButtonISR);
    Serial.println("Button Pin Initialization successful!");
    return;
}void rgb_light(){
    rgb.setPixelColor(0, rgb.Color(r, g, b));
    if(r == 255 && g < 255 && b == 0){
        g++;
    }
    else if(g == 255 && r > 0){
        r--;
    }
    else if(g == 255 && b < 255 && r == 0){
        b++;
    }
    else if(b == 255 && g > 0){
        g--;
    }
    else if(b == 255 && r < 255 && g == 0){
        r++;
    }
    else if(r == 255 && b > 0){
        b--;
    }
    return;
}void setup(){
    WakeUp();
    BootInit();
}void loop(){
    rgb_light();
    rgb.show();
    delay(5);
}

