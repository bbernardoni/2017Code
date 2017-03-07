#include "Comm.h"
#include <util/crc16.h>

void Comm::begin(long baud_rate) {
  Serial2.begin(baud_rate);
  failures = 0;
}

bool Comm::read(){
  int bytes_avail = Serial2.available();
  //Serial2.print("bytes_avail = ");
  //Serial2.println(bytes_avail);
  Serial.print("bytes_avail = ");
  Serial.println(bytes_avail);
  if(bytes_avail < 30){
    failures++;
    return false;
  }
  Serial2.readBytes(read_buf, bytes_avail);
  for (int i = bytes_avail - 1; i >= 14; i --) {   // search for last complete packet
    if (read_buf[i] == 0xdd && read_buf[i - 14] == 0xff) {   // a complete packet
      uint8_t crc = _crc8(&read_buf[i - 13], 12);
      if (crc != read_buf[i - 1]) {
        i -= 15;
        continue;
      }
      Serial.print("It works to here");
      Serial.println(_out_struct->driveFL);
      //Serial2.println("Read successful");
      _out_struct->driveFL = read_buf[i - 13];     //TODO: potential race condition. No synchronization primitives
      _out_struct->driveBL = read_buf[i - 12];
      _out_struct->driveFR = read_buf[i - 11];
      _out_struct->driveBR = read_buf[i - 10];
      _out_struct->omni    = read_buf[i - 9];
      _out_struct->shoulder= read_buf[i - 8];
      _out_struct->wrist   = read_buf[i - 7];
      _out_struct->keyGrabber= read_buf[i - 6];
      _out_struct->intake  = read_buf[i - 5];
      _out_struct->score   = read_buf[i - 4];
      _out_struct->doorOut = read_buf[i - 3];
      _out_struct->doorUp  = read_buf[i - 2];
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
  Serial2.write(outBuf, 27);
  Serial2.write(outBuf, 27);
}

int Comm::write(unsigned char * msg, int len) {
  return Serial2.write(msg, len);
}

int Comm::read(unsigned char * buf, int bufsize) {
  int bytes_avail = Serial2.available();
  if(bytes_avail < 4){
    failures++;
    return false;
  }
  Serial2.readBytes(read_buf, bytes_avail);
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
  *(tmp+1) = _in_struct->sonicDistanceF;
  *(tmp+2) = _in_struct->sonicDistanceL;
  *(tmp+3) = _in_struct->sonicDistanceR;
  *(tmp+4) = _in_struct->sonicDistanceB;
  uint16_t *tmp2 = (uint16_t *)(outBuf + 21);
  *tmp2 = _in_struct->shoulder;
  *(tmp2+1) = _in_struct->wrist;
  outBuf[25] = _crc8(&outBuf[1], 24);
  outBuf[26] = 0xdd;
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

