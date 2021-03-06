#ifndef _gps_H_
#define _gps_H_

#include "sensor.h"
#include "system/nmea_parser.h"

/**
 * @brief Support for a GPS module communicating with NMEA-0183
 * messages over a serial interface.
 * 
 * @param rx_stream Pointer to the Stream of incoming GPS data over
 * a serial connection. 
 **/ 

class GPSInput : public Sensor {
 public:
  GPSInput(Stream* rx_stream);
  virtual void enable() override final;
  NMEAData nmea_data_;
 private:
  Stream* rx_stream_;
  NMEAParser nmea_parser_;
};

// must parse the following sentences:
// - GPGGA - Global Positioning System Fix Data
// - GPGLL - Latitude/Longitude
// - GPRMC - The Recommended Minimum
// - GPVTG - Course Over Ground and Ground Speed
// - GPGSA - GNSS DOP and Active Satellites
// - GLGSA - GNSS DOP and Active Satellites
// - GPGSV - GNSS Satellites in View
// - GLGSV - GNSS Satellites in View
// - PSTI,030 - Recommended Minimum 3D GNSS Data
// - PSTI,032 - RTK Baseline Data

#endif
