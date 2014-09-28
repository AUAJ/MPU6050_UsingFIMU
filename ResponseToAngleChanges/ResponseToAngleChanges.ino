#include <PID_v1.h>

double kp = 1; 
double ki = 1; 
double kd = 1;
double iTerm;
double prevAng = 0;
double output_cust;
double newSpeed;
double K = 1;

#define PID_LIB 1

#if PID_LIB
  double setpoint = 0;
  PID pid(&currAng, &newSpeed, &setpoint, 0, 0, 0, DIRECT);
#endif

void setup(){
  Serial.begin(9600);
}
//oldSpeed = newSpeed;
/* Compute all working error variables */
void loop(){
  for(int currAng = -25; currAng < 25; currAng++){
    
    #if PID_LIB
      pid.SetTunings(kp, ki, kd);
      pid.Compute();
      Processing();
    #else
      double error = 0 - currAng;
      iTerm += ki * error;
      //iTerm = constrain(iTerm, -200, 200);
      double dInput = currAng - prevAng;
    	
      /* Compute PID output */
      output_cust = kp*error + iTerm - kd*dInput;
      // output_cust = constrain(output, min?, max?);
      newSpeed = constrain((float) (K*output_cust), -255, 255);  		
      prevAng = currAng; 
      Processing();
    #endif
    
    Serial.print(kp*error);
    Serial.print(",");
    Serial.print(iTerm);
    Serial.print(",");
    Serial.print(kd*dInput);
    Serial.print(",");
    Serial.print(currAng);
    Serial.print(",");
    Serial.println(newSpeed);
  }
}

Processing(){
  #if PID_LIB
    Serial.print(pid.getKp);
    Serial.print(",");
    Serial.print(pid.getKi);
    Serial.print(",");
    Serial.print(pid.getKd);
    Serial.print(",");
    Serial.print(currAng);
    Serial.print(",");
    Serial.println(newSpeed);
  #else
    Serial.print(kp*error);
    Serial.print(",");
    Serial.print(iTerm);
    Serial.print(",");
    Serial.print(kd*dInput);;
    Serial.print(",");
    Serial.print(currAng);
    Serial.print(",");
    Serial.println(newSpeed);
  #endif
}
