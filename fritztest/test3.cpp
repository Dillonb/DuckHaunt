#include <stdio.h>      /* printf */
#include <stdlib.h>     /* system, NULL, EXIT_FAILURE */
#include <wiringPi.h>
#include <wiringPiI2C.h>

// ------- HEADER -------
// Sg Acceleration g for 0.1 ms 10,000 g
#define L3GD20_ADDRESS                      (0x6B)   // 1101011
#define L3GD20_REGISTER_CTRL_REG1           (0x20)   // 00000111   rw
#define REG_INIT                            (0x0F)   // 00001111
#define L3GD20_REGISTER_OUT_X_L             (0x28)   //            r
#define L3GD20_REGISTER_OUT_X_H             (0x29)   //            r
#define L3GD20_REGISTER_OUT_Y_L             (0x2A)   //            r
#define L3GD20_REGISTER_OUT_Y_H             (0x2B)   //            r
#define L3GD20_REGISTER_OUT_Z_L             (0x2C)   //            r
#define L3GD20_REGISTER_OUT_Z_H             (0x2D)   //            r
#define L3GD20_BYPASS_MODE                  (0x00)   // 00000000   w  // blank out FIFO
#define L3GD20_FIFO_MODE                    (0x40)   // 00100000   w  // store 32 values into queue
#define L3GD20_STREAM_MODE                  (0x80)   // 01000000   w 
#define L3GD20_DPS_TO_RADS          (0.017453293F)   // degress/s to rad/s multiplier
#define L3GD20_REGISTER_WHO_AM_I            (0x0F)   // 11010100   r
#define L3GD20_REGISTER_CTRL_REG2           (0x21)   // 00000000   rw
#define L3GD20_REGISTER_CTRL_REG3           (0x22)   // 00000000   rw
#define L3GD20_REGISTER_CTRL_REG4           (0x23)   // 00000000   rw
#define L3GD20_REGISTER_CTRL_REG5           (0x24)   // 00000000   rw
#define L3GD20_REGISTER_REFERENCE           (0x25)   // 00000000   rw
#define L3GD20_REGISTER_OUT_TEMP            (0x26)   //            r
#define L3GD20_REGISTER_STATUS_REG          (0x27)   //            r
#define L3GD20_REGISTER_FIFO_CTRL_REG       (0x2E)   // 00000000   rw
#define L3GD20_REGISTER_FIFO_SRC_REG        (0x2F)   //            r
#define L3GD20_REGISTER_INT1_CFG            (0x30)   // 00000000   rw
#define L3GD20_REGISTER_INT1_SRC            (0x31)   //            r
#define L3GD20_REGISTER_TSH_XH              (0x32)   // 00000000   rw
#define L3GD20_REGISTER_TSH_XL              (0x33)   // 00000000   rw
#define L3GD20_REGISTER_TSH_YH              (0x34)   // 00000000   rw
#define L3GD20_REGISTER_TSH_YL              (0x35)   // 00000000   rw
#define L3GD20_REGISTER_TSH_ZH              (0x36)   // 00000000   rw
#define L3GD20_REGISTER_TSH_ZL              (0x37)   // 00000000   rw
#define L3GD20_REGISTER_INT1_DURATION       (0x38)   // 00000000   rw

// gpio load i2c //load i2c drivers into kernal
// g++ -Wall -o test test3.cpp -lwiringPi && sudo ./test

// ------- STEPS -------
// The gyro is in power down mode by default. You have to turn it on by writing the appropriate value to the CTRL_REG1 register.
// write L3GD20_REGISTER_CTRL_REG1 0x0F (0x0F = 0b00001111 - Normal power mode, all axes enabled)
// then start reading?

// ------- DOCS ------
// ST (START) transition = HIGH to LOW transition on the data line while the SCL line is held HIGH  
// SP (STOP) transition A LOW to HIGH transition on the SDA line while the SCL line is HIGH.
  //    Each data transfer must be terminated by the generation of a STOP (SP) condition.
// WAIT? If a receiver can’t receive another complete byte of data until it has performed some other function, 
  // it can hold the clock line, SCL LOW to force the transmitter into a wait state. 
  // Data transfer only continues when the receiver is ready for another byte and releases the data line.
// DATA Data are transmitted in byte format .
  // If the bit was ‘1’ (Read), a repeated START (SR) condition will have to be issued after the two sub-address bytes; 
  // if the bit is ‘0’ (Write) the Master will transmit to the slave with direction unchanged.
// SAK / MAK  The transmitter must release the SDA line during the acknowledge pulse. 
  // The receiver must then pull the data line LOW so that it remains stable low during the HIGH period of the acknowledge clock pulse. 
  // A receiver which has been addressed is obliged to generate an acknowledge after each byte of data received.
// SAD+R (SA0=GND, so 2nd from right is 0; else 1)  11010101 (D5h)
// SAD+W                                            11010100 (D4h)
// Transfer when Master is writing multiple bytes to slave
  // ST->;   SAD+W->;  SAK<-;  SUB->;  DATA->; 
  // SAK<-;  DATA->;   SAK<-;  SP->;
// Transfer when Master is receiving (reading) one byte of data from slave
  // ST->;   SAD+W->;  SAK<-;  SUB->;  SAK<-; 
  // SR->;   SAD+R->;  SAK<-;  DATA<-;   NMAK->;   SP->;
// Transfer when Master is receiving (reading) multiple bytes of data from slave
  // ST->;   SAD+W->;  SAK<-;  SUB->;  SAK<-;  SR->;   SAD+R->;  SAK<-;  DATA<-; MAK->;  DATA<-; MAK->;
  // DATA<-; NMAK->; SP->;


int main (void){
  wiringPiSetup ();
  pinMode (0, INPUT);
  pinMode (1, OUTPUT);
  int gyro = wiringPiI2CSetup( L3GD20_ADDRESS ); // this is the i2c address for the gyro
  printf("gyro - %i\n", gyro);
  
  int test = wiringPiI2CWriteReg8 (gyro, L3GD20_REGISTER_CTRL_REG1, REG_INIT); // init the sensor with defaults 
  printf("initiated %i\n", test); // 0 so far, seems right

  int test2 = wiringPiI2CWriteReg8 (gyro, L3GD20_REGISTER_FIFO_CTRL_REG, L3GD20_STREAM_MODE);
  printf("switched to stream mode %i\n", test2); // 0 so far, seems right
  delay(2000);

  for(int i=0; i < 100; ++i){
    // 91    168   250 straight i2c read
    // int wiringPiI2CReadReg8 (int fd, int reg) ;
    int txl = 0, txh = 0, tyl = 0, tyh = 0, tzl = 0, tzh = 0;
    for(int j=0; i<32; j++){
      int8_t xl = wiringPiI2CReadReg8(gyro, L3GD20_REGISTER_OUT_X_L);
      int8_t xh = wiringPiI2CReadReg8(gyro, L3GD20_REGISTER_OUT_X_H);
      int8_t yl = wiringPiI2CReadReg8(gyro, L3GD20_REGISTER_OUT_Y_L);
      int8_t yh = wiringPiI2CReadReg8(gyro, L3GD20_REGISTER_OUT_Y_H);
      int8_t zl = wiringPiI2CReadReg8(gyro, L3GD20_REGISTER_OUT_Z_L);
      int8_t zh = wiringPiI2CReadReg8(gyro, L3GD20_REGISTER_OUT_Z_H);
      // printf("GX - %i / %i \n", xl, xh );
      // printf("GY - %i / %i \n", yl, yh );
      // printf("GZ - %i / %i \n", zl, zh );
      txl += xl; txh += xh; tyl += yl; tyh += yh; tzl += zl; tzh += zh;
      printf("\n");
    }
    txl/=32; txh/=32; tyl/=32; tyh/=32; tzl/=32; tzh/=32;
    printf("GX - %i / %i \n", txl, txh );
    printf("GY - %i / %i \n", tyl, tyh );
    printf("GZ - %i / %i \n", tzl, tzh );


    // digitalRead(0);
    // digitalWrite (1, HIGH);
    delay(100);
    // digitalWrite (1, LOW);
  }
  return 0 ;
}