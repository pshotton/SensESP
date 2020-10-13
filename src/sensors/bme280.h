#ifndef _bme280_H_
#define _bme280_H_

#include <Adafruit_BME280.h>
#include <Wire.h>

#include "sensor.h"

// The BME280 classes are based on the ADAfruit_BME280 library.

// BME280 represents an ADAfruit (or compatible) BME280 temperature / pressure /
// humidity sensor. The constructore creates a pointer to the instance, and
// starts up the sensor. The pointer is passed to BME280value, which retrieves
// the specified value. If you want to change any of the values with the
// Adafruit_BME280::setSampling() method, it's public, so you can call that
// after you instantiate the BME280 and before you start using it, with:
// sensor_object->adafruit_bme280->setSampling(); See the Adafruit
// library for details.
// https://github.com/adafruit/Adafruit_BME280_Library/blob/master/Adafruit_BME280.h
class BME280 : public Sensor {
 public:
  BME280(uint8_t addr = 0x77, String config_path = "");
  Adafruit_BME280* adafruit_bme280;

 private:
  uint8_t addr;
  void check_status();
};

// Pass one of these in the constructor to BME280value() to tell which type of
// value you want to output
enum BME280ValType { temperature, pressure, humidity };

// BME280Value reads and outputs the specified value of a BME280 sensor.
class BME280Value : public NumericSensor {
 public:
  BME280Value(BME280* bme280, BME280ValType val_type, uint read_delay = 500,
              String config_path = "");
  void enable() override final;
  BME280* bme280;

 private:
  BME280ValType val_type;
  uint read_delay;
  virtual void get_configuration(JsonObject& doc) override;
  virtual bool set_configuration(const JsonObject& config) override;
  virtual String get_config_schema() override;
};

// FIXME: Uncomment the following once the PIO Xtensa toolchain is updated
// [[deprecated("Use BME280Value instead.")]]
typedef BME280Value BME280value;

#endif
