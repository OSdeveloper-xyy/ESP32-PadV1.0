#ifndef      OSSERVE_H
#define      OSSERVE_H
/*     Include Head files      */
#include <stdint.h>
#include "driver/i2s.h"
#include "driver/rtc_io.h"
#include "usb/usb_host.h"
#include "esp_log.h"
#include <SPI.h>
#include <FFat.h>
#include <FS.h>
#include <Wire.h>
#include <HardwareSerial.h>
#include <Adafruit_NeoPixel.h>
#include "define.h" 
/*        Inf Define           */
#if RGB_SWITCH == 1
#define     NUMPIXELS      1
Adafruit_NeoPixel rgb(NUMPIXELS, RGB_PIN, NEO_GRB + NEO_KHZ800);
#endif

#if CODEC_SWITCH == 1
#define I2S_NUM         I2S_NUM_0
#define SAMPLE_RATE     16000
i2s_config_t i2s_config = {
  .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_TX | I2S_MODE_RX),
  .sample_rate = 44100,
  .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,
  .channel_format = I2S_CHANNEL_FMT_RIGHT_LEFT,
  .communication_format = I2S_COMM_FORMAT_STAND_I2S,
  .intr_alloc_flags = ESP_INTR_FLAG_IRAM,
  .dma_buf_count = 8,
  .dma_buf_len = 64,
  .use_apll = true,
  .mclk_multiple = I2S_MCLK_MULTIPLE_256,
};
i2s_pin_config_t pin_config = {
  .mck_io_num   = I2S_MCLK,
  .bck_io_num   = I2S_SCLK,
  .ws_io_num    = I2S_LRCK,
  .data_out_num = I2S_DOUT,
  .data_in_num  = I2S_DIN
};
TwoWire AudioI2C(0);
#endif

#if LTE_SWITCH == 1
HardwareSerial AT_4G(1);
#endif

#if USBHOST_SWITCH == 1
usb_host_config_t host_config = {
    .skip_phy_setup = false,
    .intr_flags = ESP_INTR_FLAG_LEVEL1,
};
#endif

#if SCREEN_SWITCH == 1
TwoWire ScreenI2C(1);
#endif

#if GNSS_SWITCH == 1
#define GNSS_TYPE          DXCT511N
#endif
const char* wifiname  =    "FerainESP32" ;
const char* blename   =    "FerainESPBLE";

int USBEnu(){
    #if USBHOST_SWITCH == 1
    return true;
    #endif
    return false;
}int USBINIT(){
    #if USBHOST_SWITCH == 1
    usb_host_install(&host_config);
    return true;
    #endif
    return false;
}void SetInt(uint8_t IntNum,void(*func)(void)){
  detachInterrupt(digitalPinToInterrupt(IntNum));
  pinMode(IntNum,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(IntNum),func,FALLING);
  return;
}
struct TouchStruct{
 uint8_t BusyFlag;
 uint32_t x;
 uint32_t y;
 uint32_t width;
 uint32_t length;
 TouchStruct():BusyFlag(false){}
};
typedef struct TouchStruct TouchStruct;
struct FileOperate{
  uint16_t FileSegment;
  uint32_t FileOffset;
  uint32_t Line;
  File INIT(String Path){
    if(Path.substring(0,4) == "Chip"){
    }
  }String Read(uint32_t ByteNum){
  }String ReadUntil(char UntilByte){
  }int Write(String Data){
  }int WriteLine(uint32_t line,String Data){
  }
};
typedef struct FileOperate ServerFile;
struct LTEOperate{
  String TempPath;
  int INIT(){
    #if LTE_SWITCH == 1
    AT_4G.begin(115200,SERIAL_8N1,LTE_RX,LTE_TX);
    #if LTE_TYPE == DX_CT511
    AT_4G.setTimeout(5000);
    AT_4G.println("ATE0");
    delay(200);
    while (AT_4G.available()){
      AT_4G.read(); 
    }
    AT_4G.println("AT");
    AT_4G.readStringUntil('\n');
    if(AT_4G.readStringUntil('\n') != "OK"){
      Serial.println("AT false");
      return false;
    }
    #elif LTE_TYPE == EC_FAMILY
    #elif LTE_TYPE == SIMCOM
    #elif LTE_TYPE == AIR_FAMILY
    #endif

    return true;
    #endif
    return false;
  }int NetSwitch(uint8_t Switch){
    #if LTE_SWITCH == 1
    while (AT_4G.available()){
        AT_4G.read(); 
    }
    #if LTE_TYPE == DX_CT511
    if(Switch == true){
      AT_4G.println("AT+NETOPEN");
      AT_4G.readStringUntil('\n');
      if(AT_4G.readStringUntil('\n') != "OK"){
        Serial.println("OK false");
        return false;
      }
      AT_4G.readStringUntil('\n');
      if(AT_4G.readStringUntil('\n') != "+NETOPEN:SUCCESS"){
        Serial.println("NETOPEN false");
        return false;
      }
    }else if(Switch == false){
      AT_4G.println("AT+NETCLOSE");
      AT_4G.readStringUntil('\n');
      if(AT_4G.readStringUntil('\n') != "OK"){
        Serial.println("OK false");
        return false;
      }
      AT_4G.readStringUntil('\n');
      if(AT_4G.readStringUntil('\n') != "+NETCLOSE:SUCCESS"){
        Serial.println("NETCLOSE false");
        return false;
      }
    }
    #elif LTE_TYPE == EC_FAMILY
    #elif LTE_TYPE == SIMCOM
    #elif LTE_TYPE == AIR_FAMILY
    #endif

    return true;
    #endif
    return false;
  }int GetTime(){
    #if LTE_SWITCH == 1
    while (AT_4G.available()){
      AT_4G.read(); 
    }
    #if LTE_TYPE == DX_CT511
    AT_4G.println("AT+CCLK?");
    AT_4G.readStringUntil('\n');
    String InData = AT_4G.readStringUntil('\n');
    //......
    AT_4G.readStringUntil('\n');
    if(AT_4G.readStringUntil('\n') != "OK"){
      Serial.println("OK false");
      return false;
    }
    #elif LTE_TYPE == EC_FAMILY
    #elif LTE_TYPE == SIMCOM
    #elif LTE_TYPE == AIR_FAMILY
    #endif

    return true;
    #endif
    return false;
  }int GetStrength(){
    #if LTE_SWITCH == 1
    while (AT_4G.available()){
      AT_4G.read(); 
    }
    #if LTE_TYPE == DX_CT511
    AT_4G.println("AT+CSQ");
    AT_4G.readStringUntil('\n');
    String InData = AT_4G.readStringUntil('\n');
    //......
    AT_4G.readStringUntil('\n');
    if(AT_4G.readStringUntil('\n') != "OK"){
      Serial.println("OK false");
      return false;
    }
    #elif LTE_TYPE == EC_FAMILY
    #elif LTE_TYPE == SIMCOM
    #elif LTE_TYPE == AIR_FAMILY
    #endif

    return true;
    #endif
    return false;
  }int SetAPN(uint8_t Cid,uint8_t ContextType,String APNname,String UserName,String PassWord){
    #if LTE_SWITCH == 1
    while (AT_4G.available()){
      AT_4G.read(); 
    }
    #if LTE_TYPE == DX_CT511
    String OutData = "AT+QICSGP=";
    OutData += String(Cid);
    OutData += ",";
    OutData += String(ContextType);
    OutData += ",\"";
    OutData += APNname;
    OutData += "\",\"";
    OutData += UserName ;
    OutData += "\",\"";
    OutData += PassWord;
    OutData += "\"";
    AT_4G.println(OutData);
    AT_4G.readStringUntil('\n');
    if(AT_4G.readStringUntil('\n') != "OK"){
      Serial.println("OK false");
      return false;
    }
    #elif LTE_TYPE == EC_FAMILY
    #elif LTE_TYPE == SIMCOM
    #elif LTE_TYPE == AIR_FAMILY
    #endif

    return true;
    #endif
    return false;
  }String GetUrlIP(String URL){
    #if LTE_SWITCH == 1
    while (AT_4G.available()){
      AT_4G.read(); 
    }
    #if LTE_TYPE == DX_CT511
    String OutData = "AT+MDNSGIP=";
    OutData += URL;
    AT_4G.println(OutData);
    AT_4G.readStringUntil('\n');
    String InData = AT_4G.readStringUntil('\n');
    if(InData.substring(0,9) != "+MDNSGIP:"){
      Serial.println("No real IP or true url!");
      return "FALSE";
    }
    InData = InData.substring(URL.length() + 10);
    AT_4G.readStringUntil('\n');
    if(AT_4G.readStringUntil('\n') != "OK"){
      Serial.println("OK false");
      return "FALSE";
    }
    return InData;
    #elif LTE_TYPE == EC_FAMILY
    #elif LTE_TYPE == SIMCOM
    #elif LTE_TYPE == AIR_FAMILY
    #endif

    #endif
    return "FALSE";
  }int PING(String Addr,uint8_t AddrType,uint8_t PingNum = 4,uint16_t PacketSize = 32,uint8_t WaitTime = 3){
    #if LTE_SWITCH == 1
    while (AT_4G.available()){
      AT_4G.read(); 
    }
    #if LTE_TYPE == DX_CT511
    String OutData = "AT+MPING=";
    OutData += Addr;
    OutData += ",";
    OutData += String(AddrType);
    OutData += ",";
    OutData += String(PingNum);
    OutData += ",";
    OutData += String(PacketSize);
    OutData += ",";
    OutData += String(WaitTime);
    AT_4G.println(OutData);
    AT_4G.readStringUntil('\n');
    //......
    #elif LTE_TYPE == EC_FAMILY
    #elif LTE_TYPE == SIMCOM
    #elif LTE_TYPE == AIR_FAMILY
    #endif

    return true;
    #endif
    return false;
  }int HTTP(String WebLink){
    #if LTE_SWITCH == 1

    #if LTE_TYPE == DX_CT511
    #elif LTE_TYPE == EC_FAMILY
    #elif LTE_TYPE == SIMCOM
    #elif LTE_TYPE == AIR_FAMILY
    #endif

    return true;
    #endif
    return false;
  }int HTTPS(String WebLink){
    #if LTE_SWITCH == 1

    #if LTE_TYPE == DX_CT511
    #elif LTE_TYPE == EC_FAMILY
    #elif LTE_TYPE == SIMCOM
    #elif LTE_TYPE == AIR_FAMILY
    #endif

    return true;
    #endif
    return false;
  }String GetIccid(){
    #if LTE_SWITCH == 1
    while (AT_4G.available()){
      AT_4G.read(); 
    }
    #if LTE_TYPE == DX_CT511
    AT_4G.println("AT+ICCID");
    AT_4G.readStringUntil('\n');
    String InData = AT_4G.readStringUntil('\n');
    if(InData.substring(0,7) != "+ICCID:"){
      Serial.println("Na a true iccid!");
      return "FALSE";
    }
    InData = InData.substring(7);
    AT_4G.readStringUntil('\n');
    if(AT_4G.readStringUntil('\n') != "OK"){
      Serial.println("OK false");
      return "FALSE";
    }
    return InData;
    #elif LTE_TYPE == EC_FAMILY
    #elif LTE_TYPE == SIMCOM
    #elif LTE_TYPE == AIR_FAMILY
    #endif

    #endif
    return "FALSE";
  }String GetImei(){
    #if LTE_SWITCH == 1
    while (AT_4G.available()){
      AT_4G.read(); 
    }
    #if LTE_TYPE == DX_CT511
    AT_4G.println("ATI");
    AT_4G.readStringUntil('\n');
    AT_4G.readStringUntil('\n');
    AT_4G.readStringUntil('\n');
    AT_4G.readStringUntil('\n');
    String InData = AT_4G.readStringUntil('\n');
    if(InData.substring(0,6) != "IMEI: "){
      Serial.println("Na a true imei!");
      return "FALSE";
    }
    InData = InData.substring(6);
    AT_4G.readStringUntil('\n');
    if(AT_4G.readStringUntil('\n') != "OK"){
      Serial.println("OK false");
      return "FALSE";
    }
    return InData;
    #elif LTE_TYPE == EC_FAMILY
    #elif LTE_TYPE == SIMCOM
    #elif LTE_TYPE == AIR_FAMILY
    #endif

    #endif
    return "FALSE";
  }
};
typedef struct LTEOperate ServerLTE;
struct GNSSOperate{
  String TempPath;
  int INIT(){
    #if GNSS_SWITCH == 1

    #if GNSS_TYPE == DX_FAMILY
    #elif GNSS_TYPE == BE_FAMILY
    #endif
    return true;

    #endif
    return false;
  }int GetGNSS(){
    #if GNSS_SWITCH == 1

    #if GNSS_TYPE == DX_FAMILY
    #elif GNSS_TYPE == BE_FAMILY
    #endif
    return true;

    #endif
    return false;
  }int SetBootMode(uint8_t Mode){
    #if GNSS_SWITCH == 1

    #if GNSS_TYPE == DX_FAMILY
    #elif GNSS_TYPE == BE_FAMILY
    #endif
    return true;

    #endif
    return false;
  }
};
typedef struct GNSSOperate ServerGNSS;
struct ScreenOperate{
  uint32_t CursorX;
  uint32_t CursorY;
  TouchStruct TouchPoint[128];
  int INIT(){
    #if SCREEN_SWITCH == 1

    #if SCREEN_TYPE == LT7680
    #elif SCREEN_TYPE == ST7735
    #elif SCREEN_TYPE == ST7789
    #elif SCREEN_TYPE == ILI9341
    #endif

    return true;
    #endif
    return false;
  }int Rect(uint32_t x,uint32_t y,uint32_t width,uint32_t length,uint16_t cursor){
    #if SCREEN_SWITCH == 1

    #if SCREEN_TYPE == LT7680
    #elif SCREEN_TYPE == ST7735
    #elif SCREEN_TYPE == ST7789
    #elif SCREEN_TYPE == ILI9341
    #endif

    return true;
    #endif
    return false;
  }int Line(uint32_t startx,uint32_t starty,uint32_t endx,uint32_t endy,uint16_t color){
    #if SCREEN_SWITCH == 1

    #if SCREEN_TYPE == LT7680
    #elif SCREEN_TYPE == ST7735
    #elif SCREEN_TYPE == ST7789
    #elif SCREEN_TYPE == ILI9341
    #endif

    return true;
    #endif
    return false;
  }int DrawFile(uint32_t x,uint32_t y,String Path){
    #if SCREEN_SWITCH == 1

    #if SCREEN_TYPE == LT7680
    #elif SCREEN_TYPE == ST7735
    #elif SCREEN_TYPE == ST7789
    #elif SCREEN_TYPE == ILI9341
    #endif

    return true;
    #endif
    return false;
  }int Print(String str){
    #if SCREEN_SWITCH == 1

    #if SCREEN_TYPE == LT7680
    #elif SCREEN_TYPE == ST7735
    #elif SCREEN_TYPE == ST7789
    #elif SCREEN_TYPE == ILI9341
    #endif

    return true;
    #endif
    return false;
  }int Println(String str){
    #if SCREEN_SWITCH == 1

    #if SCREEN_TYPE == LT7680
    #elif SCREEN_TYPE == ST7735
    #elif SCREEN_TYPE == ST7789
    #elif SCREEN_TYPE == ILI9341
    #endif

    return true;
    #endif
    return false;
  }int TextSize(uint8_t size){
    #if SCREEN_SWITCH == 1

    #if SCREEN_TYPE == LT7680
    #elif SCREEN_TYPE == ST7735
    #elif SCREEN_TYPE == ST7789
    #elif SCREEN_TYPE == ILI9341
    #endif

    return true;
    #endif
    return false;
  }int TextColor(uint16_t color){
    #if SCREEN_SWITCH == 1

    #if SCREEN_TYPE == LT7680
    #elif SCREEN_TYPE == ST7735
    #elif SCREEN_TYPE == ST7789
    #elif SCREEN_TYPE == ILI9341
    #endif

    return true;
    #endif
    return false;
  }int GetTouch(){
    #if SCREEN_SWITCH == 1

    #if SCREEN_TYPE == LT7680
    #elif SCREEN_TYPE == ST7735
    #elif SCREEN_TYPE == ST7789
    #elif SCREEN_TYPE == ILI9341
    #endif

    return true;
    #endif
    return false;
  }
};
typedef struct ScreenOperate ServerScreen;
struct CodecOperate{
  String TempPath;
  int INIT(){
    #if CODEC_SWITCH == 1
    AudioI2C.begin(CODEC_SDA,CODEC_SCL,400000);
    ScreenI2C.begin(SCREEN_SDA,SCREEN_SCL,400000);
    i2s_driver_install(I2S_NUM, &i2s_config,0,NULL);
    i2s_set_pin(I2S_NUM, &pin_config);
    i2s_set_sample_rates(I2S_NUM,SAMPLE_RATE);
    #if CODEC_TYPE == ES8311
    #endif

    return true;
    #endif
    return false;
  }int SetVoice(uint8_t voicenum){
    #if CODEC_SWITCH == 1

    #if CODEC_TYPE == ES8311
    #endif

    return true;
    #endif
    return false;
  }int Instart(){
    #if CODEC_SWITCH == 1

    #if CODEC_TYPE == ES8311
    #endif

    return true;
    #endif
    return false;
  }int InEnd(){
    #if CODEC_SWITCH == 1

    #if CODEC_TYPE == ES8311
    #endif

    return true;
    #endif
    return false;
  }String InStr(){
    #if CODEC_SWITCH == 1

    #if CODEC_TYPE == ES8311
    #endif

    #endif
    return "NOMOUDLESOFALSE";
  }int OutData(uint8_t Data[]){
    #if CODEC_SWITCH == 1

    #if CODEC_TYPE == ES8311
    #endif

    return true;
    #endif
    return false;
  }int SetOutFile(String Path){
    #if CODEC_SWITCH == 1

    #if CODEC_TYPE == ES8311
    #endif

    return true;
    #endif
    return false;
  }int OutStart(){
    #if CODEC_SWITCH == 1

    #if CODEC_TYPE == ES8311
    #endif

    return true;
    #endif
    return false;
  }int OutEnd(){
    #if CODEC_SWITCH == 1

    #if CODEC_TYPE == ES8311
    #endif

    return true;
    #endif
    return false;
  }
};
typedef struct CodecOperate ServerCodec;

#endif
