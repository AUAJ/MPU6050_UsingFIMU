// I2C device class (I2Cdev) demonstration Arduino sketch for MPU6050 class
// 10/7/2011 by Jeff Rowberg <jeff@rowberg.net>
// Updates should (hopefully) always be available at https://github.com/jrowberg/i2cdevlib
//
// Changelog:
//      2013-05-08 - added multiple output formats
//                 - added seamless Fastwire support
//      2011-10-07 - initial release

/* ============================================
I2Cdev device library code is placed under the MIT license
Copyright (c) 2011 Jeff Rowberg

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
===============================================
*/
//Testing of branch
// attempt to merge
#include "I2Cdev.h"
#include "MPU6050.h"
#include "Wire.h"

MPU6050 accelgyro;

int16_t ax, ay, az;
int16_t gx, gy, gz;

int ax_tot = 0, ay_tot = 0, az_tot = 0;
int gx_tot = 0, gy_tot = 0, gz_tot = 0;

int ax_avg, ay_avg, az_avg;
int gx_avg, gy_avg, gz_avg;

int ax_loop = 0; int ay_loop = 0; int az_loop = 0;

int tot_to_avg = 100;

void setup() {
    Wire.begin();
    Serial.begin(38400);

    // initialize device
    Serial.println("Initializing I2C devices...");
    accelgyro.initialize();

    // verify connection
    Serial.println("Testing device connections...");
    Serial.println(accelgyro.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

    // use the code below to change accel/gyro offset values
    
    Serial.println("Updating internal sensor offsets...");
    // -76	-2359	1688	0	0	0
    Serial.print(accelgyro.getXGyroOffset()); Serial.print("\t"); // 0
    Serial.print(accelgyro.getYGyroOffset()); Serial.print("\t"); // 0
    Serial.print(accelgyro.getZGyroOffset()); Serial.print("\t"); // 0
    Serial.print(accelgyro.getXAccelOffset()); Serial.print("\t"); // -76
    Serial.print(accelgyro.getYAccelOffset()); Serial.print("\t"); // -2359
    Serial.print(accelgyro.getZAccelOffset()); Serial.print("\t"); // 1688
    Serial.print("\n");
    Serial.println("-----------------------");
    
    accelgyro.setXGyroOffset(80.04); // (0 offset avg)/4
    accelgyro.setYGyroOffset(-8);  // (0 offset avg)/4ish
    accelgyro.setZGyroOffset(15.4);  // (0 offset avg)/4
    accelgyro.setXAccelOffset(-2861.927); // (0 offset avg)/9.125
    accelgyro.setYAccelOffset(-970.4342); // (0 offset avg)/9.12
    accelgyro.setZAccelOffset(843.7773); // (0 offset avg) /9.7
    delay(1000);  
    Serial.print(accelgyro.getXGyroOffset()); Serial.print("\t"); // 0
    Serial.print(accelgyro.getYGyroOffset()); Serial.print("\t"); // 0
    Serial.print(accelgyro.getZGyroOffset()); Serial.print("\t"); // 0
    Serial.print(accelgyro.getXAccelOffset()); Serial.print("\t"); // -76
    Serial.print(accelgyro.getYAccelOffset()); Serial.print("\t"); // -2359
    Serial.print(accelgyro.getZAccelOffset()); Serial.print("\t"); // 1688
    Serial.print("\n");
    Serial.println("----------------");
    
    for(int i = 0 ; i < tot_to_avg; i++){
      accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

      // these methods (and a few others) are also available
      //accelgyro.getAcceleration(&ax, &ay, &az);
      //accelgyro.getRotation(&gx, &gy, &gz);
    
      // display tab-separated accel/gyro x/y/z values
      Serial.print("g/z:\t");
      Serial.print(gx); Serial.print("\t");
      Serial.print(gy); Serial.print("\t");
      Serial.print(gz); Serial.print("\t");
      Serial.print(ax); Serial.print("\t");
      Serial.print(ay); Serial.print("\t");
      Serial.print(az); Serial.println("\t");
    }
      //Serial.println(i);

      /*ax_tot += ax; 
      ay_tot += ay; 
      az_tot += az; 
      gx_tot += gx; 
      gy_tot += gy; 
      gz_tot += gz;
      */
    //}
    /*
    ax_avg = ax_tot/tot_to_avg; 
    ay_avg = ay_tot/tot_to_avg; 
    az_avg = az_tot/tot_to_avg;
    gx_avg = gx_tot/tot_to_avg; 
    gy_avg = gy_tot/tot_to_avg; 
    gz_avg = gz_tot/tot_to_avg;
    
    Serial.print("\n");
    Serial.print("Avg : "); Serial.print("\t");
    Serial.print(ax_tot); Serial.print("\t");
    Serial.print(ay_tot); Serial.print("\t");
    Serial.print(az_tot); Serial.print("\t");
    Serial.print(gx_tot); Serial.print("\t");
    Serial.print(gy_tot); Serial.print("\t");
    Serial.println(gz_tot);
    Serial.print(ax_loop); Serial.print("\t");
    Serial.print(ay_loop); Serial.print("\t");
    Serial.print(az_loop); Serial.println("\t");
    Serial.println("DONE");
    
    */
}

void loop() {
    // read raw accel/gyro measurements from device
    /*for(int i = 0 ; i < 100; i++){
    accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    // these methods (and a few others) are also available
    //accelgyro.getAcceleration(&ax, &ay, &az);
    //accelgyro.getRotation(&gx, &gy, &gz);
    
        // display tab-separated accel/gyro x/y/z values
        Serial.print("a/g:\t");
        Serial.print(ax); Serial.print("\t");
        Serial.print(ay); Serial.print("\t");
        Serial.print(az); Serial.print("\t");
        Serial.print(gx); Serial.print("\t");
        Serial.print(gy); Serial.print("\t");
        Serial.print(gz); Serial.print("\t");
        Serial.println(i);
    
      ax_tot += ax; ay_tot += ay; az_tot += az;
      gx_tot += gx; gy_tot += gy; gz_tot += gz;
    }
    
    ax_avg = ax_tot/10000; ay_avg = ay_tot/10000; az_avg = az_tot/10000;
    gx_avg = gx_tot/10000; gy_avg = gy_tot/10000; gz_avg = gz_tot/10000;
    Serial.print("\n");
    Serial.print("Avg of 10,000");
    Serial.print(ax_avg); Serial.print("\t");
    Serial.print(ay_avg); Serial.print("\t");
    Serial.print(az_avg); Serial.print("\t");
    Serial.print(gx_avg); Serial.print("\t");
    Serial.print(gy_avg); Serial.print("\t");
    Serial.println(gz);
    */
}
