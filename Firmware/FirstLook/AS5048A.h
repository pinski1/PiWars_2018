/** AS5048A magnetic quadrature encoder library 
 * 
 */
#include <SPI.h>

/** Register addresses */
#define REG_NOP     0x0000
#define REG_ERROR   0x0001
#define REG_PROG    0x0003
#define REG_ZERO_HI   0x0016
#define REG_ZERO_LO   0x0017
#define REG_DIAG    0x3FFD
#define REG_MAG     0x3FFE
#define REG_ANGLE   0x3FFF

/** Error Flag Masks */
#define FLAG_ERR_FRM  0x0001
#define FLAG_ERR_CMD  0x0002
#define FLAG_ERR_PAR  0x0004

/** Programming Flag Masks */
#define FLAG_PROG_ENB 0x0001
#define FLAG_PROG_SET 0x0008
#define FLAG_PROG_VER 0x0040

/** Diagnostics Flag Masks */
#define FLAG_DIAG_AGC 0x00FF
#define FLAG_DIAG_OCF 0x0100
#define FLAG_DIAG_COF 0x0200
#define FLAG_DIAG_CHI 0x0400
#define FLAG_DIAG_CLO 0x0800

class AS5048A {
  private:
  SPISettings settingsAS5048A;
  int _pinCS;
  int _zeroAngle;
  int getParity(int);

  public:
  AS5048A(int pinCS);
  int getCounts(void);
  int getAngle(void);
  int getErrors(void);
  
  void setAngle(int zeroAngle);
};


AS5048A::AS5048A(int pinCS) {
  
  _pinCS = pinCS;
  _zeroAngle = 0;
  
  pinMode(_pinCS, OUTPUT);
  digitalWrite(_pinCS, HIGH);
  
  settingsAS5048A = SPISettings(10000000UL, MSBFIRST, SPI_MODE1); // 10Mhz, MSB first, change data on rising edge, sample on falling edge.
  
  return;
}

int AS5048A::getAngle(void) {
  
  unsigned int temp;
  
  SPI.beginTransaction(settingsAS5048A);
  digitalWrite(_pinCS, LOW);
  
  // transfer data
  SPI.transfer16(REG_ANGLE); // request angle
  temp = SPI.transfer16(0x0000); // read angle

  temp &= 0x1FFF; // clear out diagnostic bits
  
  digitalWrite(_pinCS, HIGH);
  SPI.endTransaction();

  // adjust 'temp' based on '_zeroAngle'
  
  return temp;
}

int AS5048A::getCounts(void) {
  
  unsigned int temp;
  
  SPI.beginTransaction(settingsAS5048A);
  digitalWrite(_pinCS, LOW);
  
  // transfer data
  SPI.transfer16(REG_MAG); // request counts
  temp = SPI.transfer16(0x0000); // read counts
  
  digitalWrite(_pinCS, HIGH);
  SPI.endTransaction();
  
  return temp;
}

int AS5048A::getErrors(void) {
  
  unsigned int temp;
  
  SPI.beginTransaction(settingsAS5048A);
  digitalWrite(_pinCS, LOW);
  
  // transfer data
  SPI.transfer16(REG_DIAG); // request diagnostics
  temp = SPI.transfer16(0x0000); // read diagnostics
  
  digitalWrite(_pinCS, HIGH);
  SPI.endTransaction();
  
  return temp;
}

void AS5048A::setAngle(int zeroAngle) {
  
  _zeroAngle = zeroAngle;
  // set in software, zero angle on chip is only one time programmable.
  
  return;
}



