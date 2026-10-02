#ifndef      DEFINE_H
#define      DEFINE_H
/*    Type value definition
        User don't touch !
*/
/*           Codec Type        */
#define     ES8311         0
/*           Flash Type        
   Minimum capacity requirement
             4MB(32Mbit)
          Maximum capacity
             16MB(128bit)
*/
#define     FLASH_128      0
#define     FLASH_64       1
#define     FLASH_32       2
/*           LIE Type          */
#define     DX_CT511       0
#define     EC_FAMILY      1
#define     SIMCOM         2
#define     AIR_FAMILY     3
/*           GNSS Type         */
#define     DX_FAMILY      0
#define     BE_FAMILY
/*      Screen Drive Type      */
#define     LT7680         0
#define     ST7735         1
#define     ST7789         2
#define     ILI9341        3
/*         Device Switch  
           1 true
           0 false     
*/
#define     CODEC_SWITCH   1
#define     FLASH_SWITCH   1
#define     SCREEN_SWITCH  1
#define     LTE_SWITCH     1
#define     GNSS_SWITCH    1
#define     UVC_SWITCH     1
#define     SD_SWITCH      1
#define     USBHOST_SWITCH 1
#define     RGB_SWITCH     1



/*     Pin and Type Define     */
#if RGB_SWITCH == 1
#define     RGB_PIN        48
#endif

#if CODEC_SWITCH == 1
#define     I2S_DIN        17
#define     I2S_DOUT       15
#define     I2S_MCLK       6
#define     I2S_LRCK       16
#define     I2S_SCLK       7
#define     CODEC_SDA      4
#define     CODEC_SCL      5
#define     CODEC_TYPE     ES8311
#endif

#if SCREEN_SWITCH == 1
#define     SCREEN_INT     42
#define     SCREEN_SDA     14
#define     SCREEN_SCL     13
#define     CS_SCREEN      9
#define     SCREEN_TYPE    LT7680
//#define     SCREEN_TYPE    ST7735
//#define     SCREEN_TYPE    ST7789
//#define     SCREEN_TYPE    ILI9341
#define     SCREEN_WIDTH   480
#define     SCREEN_LENGTH  800
#endif

#if FLASH_SWITCH == 1
#define     CS_FLASH       8
#define     FLASH_TYPE     FLASH_128
//#define     FLASH_TYPE     FLASH_64
//#define     FLASH_TYPE     FLASH_32
#endif

#if LTE_SWITCH == 1
#define     LTE_RX       1
#define     LTE_TX       2
#define     LTE_TYPE    DX_CT511
//#define     LTE_TYPE    EC_FAMILY
//#define     LTE_TYPE    SIMCOM
//#define     LTE_TYPE    AIR_FAMILY
#endif

#if GNSS_SWITCH == 1
#define     GNSS_RX       1
#define     GNSS_TX       2
#define     GNSS_TYPE    DX_FAMILY
//#define     GNSS_TYPE    BE_FAMILY
#endif

#if USBHOST_SWITCH == 1
#define     USB_DP         20
#define     USB_DM         19
#endif

#if SD_SWITCH == 1
#define     CS_TF          18
#endif


#define     SPI_MOSI       10
#define     SPI_MISO       12
#define     SPI_SCLK       11
#define     BUTTON_POWER   GPIO_NUM_21
#define     BUTTON_V_UP    41
#define     BUTTON_V_DOWN  40



#endif