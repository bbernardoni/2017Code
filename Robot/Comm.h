
#ifndef COMM_H
#define COMM_H

#define USE_TIMER   1

#include <stdint.h>
#include <Arduino.h>
#include "RobotIO.h"

/**
 * The packet format:
 * -- To PC:              Data
 *          |0xff|    |    |    |    |CRC |0xee|0xdd|
 * -- From PC:
 *          |0xff| FL | BL | FR | BR |omni|CRC |0xdd|
 */
class Comm {
private:
  int _baud_rate;
  int _timer_rate;
  RobotIn *_in_struct;
  RobotOut *_out_struct;
  unsigned char read_buf[64];
  
public:
  Comm(int timer_rate, int baud_rate, RobotIn *in_struct, RobotOut *out_struct) : _timer_rate(timer_rate), 
                                                                                  _baud_rate(baud_rate), 
                                                                                  _in_struct(in_struct), 
                                                                                  _out_struct(out_struct){}
  void begin();
  
  /**
   * Basically, read from serial, update the internal servo values,
   * and write out to PC through serial.
   */
  void update();

  bool is_still_on();
  ~Comm();

private:
  void _set_timer(uint32_t rate);
  void _rm_timer();
  uint8_t _crc8(uint8_t *data, int len);
};

#endif /* COMM_H */
