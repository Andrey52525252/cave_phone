#include "AudioTools.h"

AudioInfo info(16000, 1, 16);
I2SStream i2s_out;
I2SConfig i2s_config;

void setup() {
  Serial.begin(115200);
  AudioLogger::instance().begin(Serial, AudioLogger::Warning);

  // Настраиваем I2S как Master TX (выдача данных на динамик)
  i2s_config = i2s_out.defaultConfig(TX_MODE);
  i2s_config.copyFrom(info);
  i2s_config.pin_bck = 14;
  i2s_config.pin_ws = 15;
  i2s_config.pin_data = 22; // Пин, на который приходят данные от передатчика
  i2s_config.is_master = true; // Приемник — Master (генерирует такты)
  
  i2s_out.begin(i2s_config);
  Serial.println("Приемник готов. Генерация тактов...");
}

void loop() {
  // В режиме Master TX данные автоматически читаются с пина DATA
  // и отправляются в I2S-ЦАП (динамик)
  // Этот цикл может быть пустым, вся работа в фоне
  delay(1000); 
}
