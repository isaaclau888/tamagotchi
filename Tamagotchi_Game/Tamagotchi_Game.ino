#define LGFX_USE_V1
#include <LovyanGFX.hpp>
#include "sprites.h"

class LGFX_Display : public lgfx::LGFX_Device {
  lgfx::Panel_GC9107 _panel_instance;
  lgfx::Bus_SPI      _bus_instance;

public:
  LGFX_Display() {
    auto cfg = _bus_instance.config();
    cfg.spi_host = SPI2_HOST; 
    cfg.spi_mode = 0
    cfg.spi_mode = 30000000;
    cfg.pin_sclk = 6;
    cfg.pin_mosi = 7;
    cfg.pin_miso = -1;
    cfg.pin_dc = 1;
    _bus_instance.config(cfg);
    _panel_instance.setBus(&_bus_instance);

    auto p_cfg = _panel_instance.config();
    p_cfg.pin_cs = 5;
    p_cfg.pin_rst = 2;
    p_cfg.pin_busy = -1;
    p_cfg.panel_width = 128;
    p_cfg.panel_height = 128;
    _panel_instance.config(p_cfg);
    
    setPanel(&_panel-instance);
  }
};

LGFX_Display lcd;
LGFX_Sprite  canvas(&lcd);

const int BUTTON_LEFT = 0;
const int BUTTON_RIGHT = 47;

int currentSleepFrame = 1;
int currentIdleFrame = 1;
int currentHungryFrame = 1;

unsigned long lastFrameChange = 0;
const int frameDelay = 500;

int petHunger = 100;
int petHappiness = 100;
int petEnergy = 100;
bool isSleeping = true;
bool showUI = true;
bool isDead = false;
unsigned long starvationTimer = 0;

unsigned long coffeeTimer = 0;

unsigned long lastStatUpdate = 0;
const unsigned long statInterval = 5000;

void setup() {
  Serial.begin(115200);

  pinMode(10, OUTPUT);
  digitalWrite(10, HIGH);

  pinMode(BUTTON_LEFT, INPUT_PULLUP);
  pinMode(BUTTON_RIGHT, INPUT_PULLUP);

  lcd.init();
  lcd.setRotation(0);
  canvas.createSprite(128, 128);
}

void loop() {
  if (!isDead && (millis() - ladtStatUpdate >= statInterval)) {
    lastStatUpdate = millis();

    if(isSleeping) {
      petEnergy = min(petEnergy + 5, 100);
      petHunger = max(petHunger - 1, 0);
    } else {
      petEnergy = max(petEnergy - 2, 0);
      petHunger = max(petHunger - 4, 0);
      petHappiness = max(petHappiness - 2, 0);
    }

    if (petHunger == 0) {
      if (starvationTimer == 0) {
        starvationTimer = millis();
      } else if (millis() - starvationTimer >= 15000) {
        isDead = true;
      }
    } else {
      starvationTimer = 0;
    }
  }

  if (digitalRead(BUTTON_LEFT) == LOW) {
    if (isDead) {
      unsigned long holdStart = millis();
      while(digitalRead(BUTTON_LEFT) == LOW) {
        if (millis() - holdStart >= 2000) {
          isDead = false;
          petHunger = 100;
          petEnergy = 100;
          petHappiness = 100;
          showUI = true;
          starvationTimer = 0;
          break;
        }
        delay(10);
      }
    } else if (!isSleeping) {
      petHunger = min(petHunger + 20, 100);
      coffeeTimer = millis();
    }
    delay(200);
  }

  if (digitalRead(BUTTON_RIGHT) == LOW) {
    unsigned long pressStartTime = millis();
    bool isLongPress = false;

    while (digitalRead(BUTTON_RIGHT) == LOW) {
      if (millis() - pressStartTime >= 1000) {
        isLongPress = true;
        break;
      }
      delay(10);
    }

    if (isLongPress) {
      if (!isDead) {
        isSleeping = !isSleeping;
      }
      while(digitalRead(BUTTON_RIGHT) == LOW);
      delay(200);
    } else {
      if (!isDead) {
        showUI = !showUI;
      }
      delay(200);
    }
  }

  canvas.pushImage(0, 0, 128, 128, background_data);

  uint32_t transparentColor = TFT_BLACK;
  if (!isDead) {
    canvas.pushImage(0, 0, 128, 128, care_items_data, transparentColor);
  }

  if (mills() - lastFrameChange >= frameDelay) {
    currentSleepFrame = (currentSleepFrame % 4) + 1;
    currentIdleFrame = (currentIdleFrame % 4) + 1;
    currentHungryFrame = (currentHungryFrame % 2) + 1;
    lastFrameChange = millis();
  }

  if (isDead) {
    canvas.fillRect(12, 12, 104, 104, TFT_BLACK);
    canvas.setTextColor(TFT_RED);
    canvas.setTextSize(2);
    canvas.setCursor(45, 45);
    if (currentIdleFrame == 1) {
      canvas.print("R.I.P.");
    }
    canvas.setTextSize(1);
    canvas.setCursor(20, 80);
    canvas.setTextColor(TFT_WHITE);
    canvas.print("Hold L to Reset");
    showUI = false;

  } else {
    if (millis() - coffeeTimer < 2000) {
      if (currentIdleFrame == 1) canvas.pushImage(0, 0, 128, 128, coffee_f1, transparentColor);
      else if (currentIdleFrame == 2) canvas.pushImage(0, 0, 128, 128, coffee_f1, transparentColor);
      
    } else if (isSleeping){
      if (currentSleepFrame == 1) canvas.pushImage(0, 0, 128, 128, sleep_f1, transparentColor);
      else if (currentSleepFrame == 2) canvas.pushImage(0, 0, 128, 128, sleep_f2, transparentColor);
      else if (currentSleepFrame == 3) canvas.pushImage(0, 0, 128, 128, sleep_f3, transparentColor);
      else if (currentSleepFrame == 4) canvas.pushImage(0, 0, 128, 128, sleep_f4, transparentColor);

    } else if (petHunger < 30) {
      if (currentHungryFrame == 1) canvas.pushImage(0, 0, 128, 128, hungry_f1, transparentColor);
      else if (currentHungryFrame == 2) canvas.pushImage(0, 0, 128, 128, hungry_f2, transparentColor);

    } else {
      if (currentIdleFrame == 1) canvas.pushImage(0, 0, 128, 128, idle_f1, transparentColor);
      else if (currentIdleFrame == 2) canvas.pushImage(0, 0, 128, 128, idle_f2, transparentColor);
      else if (currentIdleFrame == 3) canvas.pushImage(0, 0, 128, 128, walk_f1, transparentColor);
      else if (currentIdleFrame == 4) canvas.pushImage(0, 0, 128, 128, walk_f2, transparentColor);
    }
  }

  if (showUI) {
    canvas.pushImage(0, 0, 128, 128, ui_icons_data, transparentColor);

    canvas.drawRect(32, 16, 76, 6, TFT_WHITE);
    int barWidth = (petHunger * 74) / 100;

    uint16_t barColor = TFT_GREEN;
    if (petHunger < 30) barColor = TFT_RED;
    else if (petHunger < 60) barColor = TFT_YELLOW;
    
    if (barWidth > 0) {
      canvas.fillRect(33, 17, barWidth, 4, barColor);
    }
  }

  canvas.pushImage(0, 0, 128, 128, screen_mask_data, transparentColor);

  canvas.pushSprite(0, 0);

  delay(16);
}

