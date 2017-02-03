#include "Comm.h"
#include <util/crc16.h>

void Comm::begin() {
  Serial.begin(_baud_rate);
}

void Comm::update() {
  // write out to PC
  uint8_t buf[8] = {0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0xee, 0xdd};
  float *tmp = (float *)(buf + 1);
  *tmp = _in_struct->gyroAngle;
  buf[5] = _crc8(&buf[1], 4);
  Serial.write(buf, 8);
  Serial.write(buf, 8);
  
  int bytes_avail = Serial.available();
  if (bytes_avail > 0) {     // has data to read
    Serial.readBytes(read_buf, bytes_avail);
    for (int i = bytes_avail - 1; i >= 7; i --) {   // search for last complete packet
      if (read_buf[i] == 0xdd && read_buf[i - 7] == 0xff) {   // a complete packet
        uint8_t crc = _crc8(&read_buf[i - 6], 5);
        if (crc != read_buf[i - 1]) {
          i -= 8;
          continue;
        }
        _out_struct->driveFL = read_buf[i - 6];     //TODO: potential race condition. No synchronization primitives
        _out_struct->driveBL = read_buf[i - 5];
        _out_struct->driveFR = read_buf[i - 4];
        _out_struct->driveBR = read_buf[i - 3];
        _out_struct->omni    = read_buf[i - 2];
        break;
      }
    }
  }
//  for (int i = 0; i < 8; i++)
//    Serial.print(buf[i], HEX);
//  Serial.println(_in_struct->gyroAngle);
}

bool Comm::is_still_on() {
  // TODO: add implementation
  return true;
}

Comm::~Comm() {
}

uint8_t Comm::_crc8(uint8_t *data, int len) {
  uint8_t crc = 0x00;
  for (int i = 0; i < len; i++) {
    crc = _crc8_ccitt_update(crc, data[i]);
  }
  return crc;
}

