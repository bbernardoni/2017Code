#include "Comm.h"
#include <util/crc16.h>

void Comm::begin(long baud_rate) {
  Serial2.begin(baud_rate);
  failures = 0;
}

bool Comm::read(){
  int bytes_avail = Serial2.available();
  //Serial.print("bytes_avail = ");
  //Serial.println(bytes_avail);
  if(bytes_avail < 16){
    failures++;
    return false;
  }
  
  Serial2.readBytes(read_buf, bytes_avail);
  for (int i = bytes_avail - 1; i >= 7; i --) {   // search for last complete packet
    if (read_buf[i] == 0xdd && read_buf[i - 7] == 0xff) {   // a complete packet
      uint8_t crc = _crc8(&read_buf[i - 6], 5);
      if (crc != read_buf[i - 1]) {
        i -= 8;
        continue;
      }
      //Serial.println("Read successful");
      _out_struct->driveFL = read_buf[i - 6];     //TODO: potential race condition. No synchronization primitives
      _out_struct->driveBL = read_buf[i - 5];
      _out_struct->driveFR = read_buf[i - 4];
      _out_struct->driveBR = read_buf[i - 3];
      _out_struct->omni    = read_buf[i - 2];
      break;
    }
  }
  
//  for (int i = 0; i < 8; i++)
//    Serial2.print(buf[i], HEX);
//  Serial2.println(_in_struct->gyroAngle);
  failures = 0;
  return true;
}

void Comm::write(){
  setOutBuf();
  if(failures == 0){
    while(Serial2.available() > 0) {
      char t = Serial2.read();
    }
  }
  Serial2.write(outBuf, 8);
  Serial2.write(outBuf, 8);
}

void Comm::setOutBuf(){
  outBuf[0] = 0xff;
  float *tmp = (float *)(outBuf + 1);
  *tmp = _in_struct->gyroAngle;
  outBuf[5] = _crc8(&outBuf[1], 4);
  outBuf[6] = 0xee;
  outBuf[7] = 0xdd;
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

