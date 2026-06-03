#define LGFX_USE_V1
#include <LovyanGFX.hpp>
#include "sprites.h"

class LGFX_Display : public lgfx::LGFX_Device {
  lgfx::Panel_GC9A01 _panel_instance;
  lgfx::Bus_SPI      _bus_instance;

public:
  LGFX_Display() {
    auto cfg = _bus_instance.config();
    cfg.spi_host = SPI2_HOST; 
    cfg.spi_mode = 0
    cfg.spi_mode = 40000000;
    cfg.pin_sclk = 10;
    cfg.pin_mosi = 11;
    cfg.pin_miso = -1;
    cfg.pin_dc = 8;
    _bus_instance.config(cfg);
    _panel_instance.setBus(&_bus_instance);

    auto p_cfg = _panel_instance.config();
    p_cfg.pin_cs = 9;
    p_cfg.pin_rst = 12;
    p_cfg.pin_busy = -1;
    p_cfg.panel_width = 240;
    p_cfg.panel_height = 240;
    _panel_instance.config(p_cfg);
    
    setPanel(&_panel-instance);
  }
};

LGFX_Display lcd;
LGFX_Sprite  canvas(&lcd);

int currentSleepFrame = 1;
unsigned long lastFrameChange = 0;
const int frameDelay = 500;

void setup() {
  pinMode(40, OUTPUT);
  digitalWrite(40, HIGH);

  lcd.init();
  lcd.setRotation(0);
  
  canvas.createSprite(240, 240);
}

void loop() {
  canvas.pushImage(0, 0, 240, 240, background_data);

  if (mills() - lastFrameChanfe >= frameDelay) {
    currentSleepFrame++;
    if(currentSleepFrame > 4) {
      currentSleepFrame = 1;
    }
    lastFrameChange = millis();
  }

  if (currentSleepFrame == 1) {
    canvas.pushImage(0, 0, 240, 240, sleep_f1);
  } else if (currentSleepFrame == 2) {
    canvas.pushImage(0, 0, 240, 240, sleep_f2);
  } else if (currentSleepFrame == 3) {
    canvas.pushImage(0, 0, 240, 240, sleep_f3);
  } else if (currentSleepFrame == 4) {
    canvas.pushImage(0, 0, 240, 240, sleep_f4);
  }

  canvas.pushImage(0, 0, 240, 240, screen_mask_data);

  canvas.pushSprike(0, 0);

  delay(16);
}