/** PCA9546A I2C 4 channel multiplexer library
 * 
 */
#include <Wire.h>

/** Masks */
#define CHAN_1 0x01
#define CHAN_2 0x02
#define CHAN_3 0x04
#define CHAN_4 0x08

class PCA9546 {
  unsigned char _adr;

  public:
    PCA9546(void);
    void setAddress(unsigned char newAdr);
    void selChannel(unsigned char channel);
};

PCA9546::PCA9546(void) {
  _adr = 0b11100000;
}

void PCA9546::setAddress(unsigned char newAdr) {
  _adr = newAdr;
  return;
}


void PCA9546::selChannel(unsigned char channel) {

  channel = constrain(channel, 0x00, 0x0F); // clamp errors

  Wire.beginTransmission(_adr);
  Wire.write(channel);
  Wire.endTransmission();

  return;
}

