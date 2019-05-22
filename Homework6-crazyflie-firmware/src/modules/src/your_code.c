#include "your_code.h"

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

static void test_task1(void);
static void test_task2(void);

uint32_t tick;


void yourCodeInit(void)
{

  tick = 1;

  xTaskCreate(test_task1, "STABILIZER_TASK_NAME1",
              (3 * configMINIMAL_STACK_SIZE), NULL, 1, NULL);
  xTaskCreate(test_task2, "STABILIZER_TASK_NAME2",
              (3 * configMINIMAL_STACK_SIZE), NULL, 2, NULL);
   xTaskCreate(test_task2, "STABILIZER_TASK_NAME2",
              (3 * configMINIMAL_STACK_SIZE), NULL, 3, NULL);


  //xTaskCreate(comp_filter, "comp_filter", configMINIMAL_STACK_SIZE, NULL, 1, NULL);  
	//xTaskCreate(setpointgen, "setpointgen", configMINIMAL_STACK_SIZE, NULL, 3, NULL);  
	//xTaskCreate(LQcontrol, "LQcontrol", configMINIMAL_STACK_SIZE, NULL, 2, NULL);  

 }

static void test_task1(void)
{
  uint16_t value_1;
  uint32_t lastWakeTime;
  sensorData_t sensorData;

  lastWakeTime = xTaskGetTickCount();
  while(!sensorsAreCalibrated()) {
    vTaskDelayUntil(&lastWakeTime, F2T(RATE_MAIN_LOOP));
  }
  
  
  while(1)
  { 
    sensorsAcquire(&sensorData, tick);
    value_1 = 5000 * sensorData.gyro.x;

    motorsSetRatio(MOTOR_M1, value_1);
    vTaskDelayUntil(&lastWakeTime, F2T(RATE_MAIN_LOOP));
    tick++;
  }
}

static void test_task2(void)
{
  uint16_t value_2;
  uint32_t lastWakeTime;
  sensorData_t sensorData;

  lastWakeTime = xTaskGetTickCount();
  while(!sensorsAreCalibrated()) {
    vTaskDelayUntil(&lastWakeTime, F2T(RATE_MAIN_LOOP));
  }
  
  
  while(1)
  { 
    sensorsAcquire(&sensorData, tick);
    value_2 = 5000 * sensorData.gyro.x;

    motorsSetRatio(MOTOR_M2, value_2);
    vTaskDelayUntil(&lastWakeTime, F2T(RATE_MAIN_LOOP));
    tick++;
  }
}




void comp_filter(void)
{
    int gamma = 0.95;
    int     h = 0.01;
    float fx, fy, fz, ax, ay, az, theta, phi;
    
    lastWakeTime = xTaskGetTickCount();
    while(!sensorsAreCalibrated()) {
    vTaskDelayUntil(&lastWakeTime, F2T(RATE_MAIN_LOOP));
   }

    sensorData_t sensorData;
    
    
    while(1){
    sensorsAcquire(&sensorData, tick); // Read sensors at full rate (1000Hz)

    ax = sensorData.acc.ax;
    ay = sensorData.acc.ay;
    az = sensorData.acc.az;

    if(!((ax == 0.0f) && (ay == 0.0f) && (az == 0.0f)))
    {
        fx = ax*invSqrt(ax * ax + ay * ay + az * az);
        fy = ax*invSqrt(ax * ax + ay * ay + az * az);
        fz = az*invSqrt(ax * ax + ay * ay + az * az);

        theta = (180/pi)*atan2(-fx,sqrt(fy*fy + fz*fz));
        phi = (180/pi)*atan2(fy,fz);

        // How do we do with the states? 

        // Should we maybe just create new variables for the states?

        // Then we would have to initilize these somehow, maybe with zero since we
        // most likely will start with zero pitch and roll?

        // If we continue like before with the state pointer, we need to find the command 
        // that gets us state data, i.e the state version of sensorsAcquire       
        (*state).attitude.roll = (1-gamma)*theta + gamma*((*state).attitude.roll + h*sensorData.gyro.y);
        (*state).attitude.pitch = (1-gamma)*phi + gamma*((*state).attitude.pitch + h*sensorData.gyro.x);
    }
    
    tick++;
  }
}







/*void comp_filter(state_t *state, sensorData_t *sensorData, const uint32_t tick)
{
    int gamma = 0.95;
    int     h = 0.01;
    float fx, fy, fz, ax, ay, az, theta, phi;

    xSemaphoreTake(semMutex,1000);
    sensorsAcquire(sensorData, tick); // Read sensors at full rate (1000Hz)

    ax = (*sensorData).acc.ax;
    ay = (*sensorData).acc.ay;
    az = (*sensorData).acc.az;

    if(!((ax == 0.0f) && (ay == 0.0f) && (az == 0.0f)))
    {
        fx = ax*invSqrt(ax * ax + ay * ay + az * az);
        fy = ax*invSqrt(ax * ax + ay * ay + az * az);
        fz = az*invSqrt(ax * ax + ay * ay + az * az);

        theta = (180/pi)*atan2(-fx,sqrt(fy*fy + fz*fz));
        phi = (180/pi)*atan2(fy,fz);
        (*state).attitude.roll = (1-gamma)*theta + gamma*((*state).attitude.roll + h*(*sensorData).gyro.y);
        (*state).attitude.pitch = (1-gamma)*phi + gamma*((*state).attitude.pitch + h*(*sensorData).gyro.x);
    }
    xSemaphoreGive(semMutex);
}*/

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
