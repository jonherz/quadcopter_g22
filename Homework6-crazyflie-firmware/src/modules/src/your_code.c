#include "your_code.h"
#include "semphr.h"

#define MAX_uint16_t ((uint16_t)(65535U))
/***
 *
 * This file is where you should add you tasks. You already know the structure
 * Required to do so from the work with the simulator.
 *
 * The function yourCodeInit() is set to automatically execute when the
 * quadrotor is started. This is where you need to create your tasks. The
 * scheduler that runs the tasks is already up and running so you should
 * NOT make a call to vTaskStartScheduler();.
 *
 * Below that you can find a few examples of useful function calls and code snippets.
 *
 * For further reference on how this is done. Look into the file stabilizer.c
 * which is usually handles the control of the crazyflie.
 *
 ***/

volatile struct {
  // angles - degree
  float roll;
  float pitch;
  // angular velocity - degree / sec
  float rateRoll;
  float ratePitch;
  float rateYaw;
} state;

uint32_t tick;
setpoint_t setpoint;

SemaphoreHandle_t filtsema;
SemaphoreHandle_t setsema;



static void comp_filter(void);
static void setPointtrack(void);
static void controller(void);



void yourCodeInit(void)
{
  tick = 1;
  state.roll = 0.0f;
  state.pitch = 0.0f;
  
  filtsema = xSemaphoreCreateMutex();
	setsema = xSemaphoreCreateMutex();

  xTaskCreate(comp_filter, "FILTER",
              (3 * configMINIMAL_STACK_SIZE), NULL, 3, NULL);
  xTaskCreate(setPointtrack, "SETPOINT",
              (3 * configMINIMAL_STACK_SIZE), NULL, 1, NULL);
  xTaskCreate(controller, "CONTROL",
              (3 * configMINIMAL_STACK_SIZE), NULL, 2, NULL);
 }





static void comp_filter(void)
{
  float gamma = 0.98;
  float     h = 0.001;
  uint32_t lastWakeTime; 
  float fx, fy, fz, ax, ay, az, thetaNoobacc, phiNoobacc;
  sensorData_t sensorData;

  lastWakeTime = xTaskGetTickCount();
  while(!sensorsAreCalibrated()) {
    vTaskDelayUntil(&lastWakeTime, F2T(RATE_MAIN_LOOP));
  }
  
  
  while(1)
  { 
      vTaskDelayUntil(&lastWakeTime, F2T(1000));
      sensorsAcquire(&sensorData, tick); // Read sensors at full rate (1000Hz)

      ax = sensorData.acc.x;
      ay = sensorData.acc.y;
      az = sensorData.acc.z;

      if(!((ax == 0.0f) && (ay == 0.0f) && (az == 0.0f)))
      {
        fx = ax/sqrt(ax * ax + ay * ay + az * az);
        fy = ay/sqrt(ax * ax + ay * ay + az * az);
        fz = az/sqrt(ax * ax + ay * ay + az * az);

        thetaNoobacc = (180/M_PI)*atan2(-fx,sqrt(fy*fy + fz*fz));
        phiNoobacc = (180/M_PI)*atan2(fy,fz);
            
      xSemaphoreTake(filtsema,portMAX_DELAY);          
        state.pitch= (1-gamma)*thetaNoobacc + gamma*(state.pitch + h*sensorData.gyro.y);
        state.roll= (1-gamma)*phiNoobacc + gamma*(state.roll  + h*sensorData.gyro.x);
        state.rateRoll= sensorData.gyro.x;
        state.ratePitch= sensorData.gyro.y;
        state.rateYaw= sensorData.gyro.z;
        tick++;
      xSemaphoreGive(filtsema);
    }
  }
}


static void setPointtrack(void)
{
  uint32_t lastWakeTime;

  lastWakeTime = xTaskGetTickCount();
  while(!sensorsAreCalibrated()) {
    vTaskDelayUntil(&lastWakeTime, F2T(RATE_MAIN_LOOP));
  }
  
  
  while(1)
  { 
    vTaskDelayUntil(&lastWakeTime, F2T(100));
    xSemaphoreTake(setsema,portMAX_DELAY);          
    commanderGetSetpoint(&setpoint, tick);
    tick++;
    xSemaphoreGive(setsema);
    
  }
}

static void controller(void)
{
  uint32_t lastWakeTime;
  float setTrackRoll, setTrackPitch, setTrackRollRate, setTrackPitchRate, setTrackYawRate;
  uint16_t motor_1, motor_2, motor_3, motor_4;
  float value_1,value_2,value_3,value_4;

  lastWakeTime = xTaskGetTickCount();
  while(!sensorsAreCalibrated()) {
    vTaskDelayUntil(&lastWakeTime, F2T(RATE_MAIN_LOOP));
  }
  
  float LQRGain[4][5] = {
            {-135.2796, -135.3304,  -58.4204,  -59.2390,  -50.6338},
            {-135.2796,  135.3304,  -58.4204,   59.2390,   50.6338},
            {135.2796,  135.3304,   58.4204,   59.2390,  -50.6338},
            {135.2796, -135.3304,   58.4204,  -59.2390,   50.6338},
            };
  
  while(1)
  { 
    vTaskDelayUntil(&lastWakeTime, F2T(1000));

    xSemaphoreTake(setsema,portMAX_DELAY); 
    xSemaphoreTake(filtsema,portMAX_DELAY);                   
    setTrackRoll = (-1)*(state.roll - (-1)*setpoint.attitude.roll);
    setTrackPitch = (-1)*(state.pitch - setpoint.attitude.pitch);
    setTrackRollRate = (-1)*state.rateRoll;
    setTrackPitchRate = (-1)*state.ratePitch;
    setTrackYawRate = (-1)*(state.rateYaw - setpoint.attitudeRate.yaw);
    xSemaphoreGive(filtsema);


    value_1 = 1*(setTrackRoll*LQRGain[0][0] + setTrackPitch*LQRGain[0][1] + setTrackRollRate*LQRGain[0][2] + setTrackPitchRate*LQRGain[0][3] + setTrackYawRate*LQRGain[0][4]);
    value_2 = 1*(setTrackRoll*LQRGain[1][0] + setTrackPitch*LQRGain[1][1] + setTrackRollRate*LQRGain[1][2] + setTrackPitchRate*LQRGain[1][3] + setTrackYawRate*LQRGain[1][4]);
    value_3 = 1*(setTrackRoll*LQRGain[2][0] + setTrackPitch*LQRGain[2][1] + setTrackRollRate*LQRGain[2][2] + setTrackPitchRate*LQRGain[2][3] + setTrackYawRate*LQRGain[2][4]);
    value_4 = 1*(setTrackRoll*LQRGain[3][0] + setTrackPitch*LQRGain[3][1] + setTrackRollRate*LQRGain[3][2] + setTrackPitchRate*LQRGain[3][3] + setTrackYawRate*LQRGain[3][4]);

    value_1 += setpoint.thrust;
    value_2 += setpoint.thrust;
    value_3 += setpoint.thrust;
    value_4 += setpoint.thrust;
    xSemaphoreGive(setsema);

    if(value_1 < 65536.0){
      if(value_1 >= 0.0){
        motor_1 = (uint16_t)value_1;
      } else{
        motor_1 = 0U;
      }
    } else{
      motor_1 = MAX_uint16_t;
    }
    if(value_2 < 65536.0){
      if(value_2 >= 0.0){
        motor_2 = (uint16_t)value_2;
      } else{
        motor_2 = 0U;
      }
    } else{
      motor_2 = MAX_uint16_t;
    }
    if(value_3 < 65536.0){
      if(value_3 >= 0.0){
        motor_3 = (uint16_t)value_3;
      } else{
        motor_3 = 0U;
      }
    } else{
      motor_3 = MAX_uint16_t;
    }
    if(value_4 < 65536.0){
      if(value_4 >= 0.0){
        motor_4 = (uint16_t)value_4;
      } else{
        motor_4 = 0U;
      }
    } else{
      motor_4 = MAX_uint16_t;
    }



    motorsSetRatio(MOTOR_M1, motor_1);
    motorsSetRatio(MOTOR_M2, motor_2);
    motorsSetRatio(MOTOR_M3, motor_3);
    motorsSetRatio(MOTOR_M4, motor_4);
    tick++;
  }
}



/*************************************************
 * WAIT FOR SENSORS TO BE CALIBRATED
 ************************************************/
// lastWakeTime = xTaskGetTickCount ();
// while(!sensorsAreCalibrated()) {
//     vTaskDelayUntil(&lastWakeTime, F2T(RATE_MAIN_LOOP));
// }



/*************************************************
 * RETRIEVE THE MOST RECENT SENSOR DATA
 *
 * The code creates a variable called sensorData and then calls a function
 * that fills this variable with the latest data from the sensors.
 *
 * sensorData_t sensorData = struct {
 *     Axis3f acc;
 *     Axis3f gyro;
 *     Axis3f mag;
 *     baro_t baro;
 *     zDistance_t zrange;
 *     point_t position;
 * }
 *
 ************************************************/
// sensorData_t sensorData;
// sensorsAcquire(&sensorData);
// sensorData.acc.x 



/*************************************************
 * RETRIEVE THE SET POINT FROM ANY EXTERNAL COMMAND INTERFACE
 *
 * The code creates a variable called setpoint and then calls a function
 * that fills this variable with the latest command input.
 *
 * setpoint_t setpoint = struct {
 *     uint32_t timestamp;
 *
 *     attitude_t attitude;      // deg
 *     attitude_t attitudeRate;  // deg/s
 *     quaternion_t attitudeQuaternion;
 *     float thrust;
 *     point_t position;         // m
 *     velocity_t velocity;      // m/s
 *     acc_t acceleration;       // m/s^2
 *     bool velocity_body;       // true if velocity is given in body frame; false if velocity is given in world frame
 *
 *     struct {
 *         stab_mode_t x;
 *         stab_mode_t y;
 *         stab_mode_t z;
 *         stab_mode_t roll;
 *         stab_mode_t pitch;
 *         stab_mode_t yaw;
 *         stab_mode_t quat;
 *     } mode;
 * }
 *
 ************************************************/
// setpoint_t setpoint;
// commanderGetSetpoint(&setpoint);



/*************************************************
 * SENDING OUTPUT TO THE MOTORS
 *
 * The code sends an output to each motor. The output should have the be
 * of the typ unsigned 16-bit integer, i.e. use variables such as:
 * uint16_t value_i
 *
 ************************************************/
// motorsSetRatio(MOTOR_M1, value_1);
// motorsSetRatio(MOTOR_M2, value_2);
// motorsSetRatio(MOTOR_M3, value_3);
// motorsSetRatio(MOTOR_M4, value_4);


/*************************************************
 * LOGGING VALUES THAT CAN BE PLOTTEN IN PYTHON CLIENT
 *
 * We have already set up three log blocks to for the accelerometer data, the
 * gyro data and the setpoints, just uncomment the block to start logging. Use
 * them as reference if you want to add custom blocks.
 *
 ************************************************/

LOG_GROUP_START(filter)
LOG_ADD(LOG_FLOAT, roll, &state.roll)
LOG_ADD(LOG_FLOAT, pitch, &state.pitch)
LOG_GROUP_STOP(filter)

/*
LOG_GROUP_START(acc)
LOG_ADD(LOG_FLOAT, x, &sensorData.acc.x)
LOG_ADD(LOG_FLOAT, y, &sensorData.acc.y)
LOG_ADD(LOG_FLOAT, z, &sensorData.acc.z)
LOG_GROUP_STOP(acc)
*/

/*
LOG_GROUP_START(gyro)
LOG_ADD(LOG_FLOAT, x, &sensorData.gyro.x)
LOG_ADD(LOG_FLOAT, y, &sensorData.gyro.y)
LOG_ADD(LOG_FLOAT, z, &sensorData.gyro.z)
LOG_GROUP_STOP(gyro)
*/

/*
LOG_GROUP_START(ctrltarget)
LOG_ADD(LOG_FLOAT, roll, &setpoint.attitude.roll)
LOG_ADD(LOG_FLOAT, pitch, &setpoint.attitude.pitch)
LOG_ADD(LOG_FLOAT, yaw, &setpoint.attitudeRate.yaw)
LOG_GROUP_STOP(ctrltarget)
*/
