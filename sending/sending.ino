#include "AudioTools.h"

// Настройки аудио: 16 кГц, моно, 16 бит (хорошо для голоса)
AudioInfo info(16000, 1, 16); 
I2SStream i2s_in;
I2SConfig i2s_config;

void setup() {
  Serial.begin(115200);
  AudioLogger::instance().begin(Serial, AudioLogger::Warning);

  // Настраиваем I2S как Slave RX (прием данных от микрофона)
  i2s_config = i2s_in.defaultConfig(RX_MODE);
  i2s_config.copyFrom(info);
  i2s_config.pin_bck = 14;
  i2s_config.pin_ws = 15;
  i2s_config.pin_data = 32; // Пин, с которого данные пойдут на приемник
  i2s_config.is_master = false; // Передатчик — Slave
  
  i2s_in.begin(i2s_config);
  Serial.println("Передатчик готов. Ожидание тактового сигнала...");
}

void loop() {
  int16_t buffer[256];
  // Читаем данные с микрофона (блокирующий вызов, ждет тактов от Мастера)
  size_t bytes_read = i2s_in.readBytes((uint8_t*)buffer, sizeof(buffer));
  
  // Данные автоматически уходят по проводу I2S на приемник
  // (В этом режиме Slave данные передаются сразу при поступлении тактов)
}
