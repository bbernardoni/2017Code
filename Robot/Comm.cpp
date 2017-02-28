#include "Comm.h"
#include <util/crc16.h>

void Comm::begin(long baud_rate) {
  Serial.begin(baud_rate);
  failures = 0;
}

bool Comm::read(){
  int bytes_avail = Serial.available();
  //Serial.print("bytes_avail = ");
  //Serial.println(bytes_avail);
  if(bytes_avail < 16){
    failures++;
    return false;
  }
  
  Serial.readBytes(read_buf, bytes_avail);
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
//    Serial.print(buf[i], HEX);
//  Serial.println(_in_struct->gyroAngle);
  failures = 0;
  return true;
}

void Comm::write(){
  setOutBuf();
  if(failures == 0){
    while(Serial.available() > 0) {
      char t = Serial.read();
    }
  }
  Serial.write(outBuf, 8);
  Serial.write(outBuf, 8);
}

bool Comm::write(unsigned char * msg, int len) {
  Serial.write(msg, len);
}

int Comm::read(unsigned char * buf, int bufsize) {
  int bytes_avail = Serial.available();
  if(bytes_avail < 4){
    failures++;
    return false;
  }
  Serial.readBytes(read_buf, bytes_avail);
  for (int i = bytes_avail - 1; i >= 3; i --) {
    if (buf[i] == 0xdd) {
      unsigned char len = read_buf[i - 1];
      if ((len + 3) <= i && read_buf[i - len - 3] == 0xff && read_buf[ - 2] == _crc8(&read_buf[i - len - 2], len)) {
        memcpy(buf, read_buf, bufsize > 128 ? 128 : bufsize);
        return bufsize > 128 ? 128 : bufsize;
      }
    }
  }
  return -1;
}

void Comm::setOutBuf(){
  outBuf[0] = 0xff;
  float *tmp = (float *)(outBuf + 1);
  *tmp = _in_struct->gyroAngle;
  outBuf[5] = _crc8(&outBuf[1], 4);
  outBuf[6] = 0xee;
  outBuf[7] = 0xdd;
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

