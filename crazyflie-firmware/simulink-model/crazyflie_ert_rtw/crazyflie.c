/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: crazyflie.c
 *
 * Code generated for Simulink model 'crazyflie'.
 *
 * Model version                  : 1.199
 * Simulink Coder version         : 9.0 (R2018b) 24-May-2018
 * C/C++ source code generated on : Sun May 26 14:46:11 2019
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "crazyflie.h"

/* Block signals and states (default storage) */
DW rtDW;

/* External inputs (root inport signals with default storage) */
ExtU rtU;

/* External outputs (root outports fed by signals with default storage) */
ExtY rtY;

/* Model step function */
void crazyflie_step(void)
{
  real_T fy;
  real_T fz;
  real_T rtb_theta;
  real_T rtb_Add[4];
  real_T fy_0[5];
  int32_T i;
  int32_T i_0;

  /* MATLAB Function: '<Root>/MATLAB Function' incorporates:
   *  Inport: '<Root>/Acc_x'
   *  Inport: '<Root>/Acc_y'
   *  Inport: '<Root>/Acc_z'
   *  Inport: '<Root>/Gyro_x'
   *  Inport: '<Root>/Gyro_y'
   *  Memory: '<Root>/Memory'
   *  Memory: '<Root>/Memory1'
   */
  /* MATLAB Function 'MATLAB Function': '<S2>:1' */
  /* '<S2>:1:2' gamma = 0.95; */
  /* '<S2>:1:3' h = 0.01; */
  /* '<S2>:1:5' fx = Acc_x/sqrt(Acc_x^2 + Acc_y^2 + Acc_z^2); */
  /* '<S2>:1:6' fy = Acc_y/sqrt(Acc_x^2 + Acc_y^2 + Acc_z^2); */
  rtb_theta = sqrt((rtU.Acc_x * rtU.Acc_x + rtU.Acc_y * rtU.Acc_y) + rtU.Acc_z *
                   rtU.Acc_z);
  fy = rtU.Acc_y / rtb_theta;

  /* '<S2>:1:7' fz = Acc_z/sqrt(Acc_x^2 + Acc_y^2 + Acc_z^2); */
  fz = rtU.Acc_z / rtb_theta;

  /* '<S2>:1:9' theta_a = (180/pi)*atan2(-fx,sqrt(fy^2 + fz^2)); */
  /* '<S2>:1:10' phi_a = (180/pi)*atan2(fy,fz); */
  /* '<S2>:1:13' theta = (1-gamma)*theta_a + gamma*(theta + h*gyro_y); */
  /* '<S2>:1:16' phi = (1-gamma)*phi_a + gamma*(phi + h*gyro_x); */
  rtb_theta = atan2(-(rtU.Acc_x / rtb_theta), sqrt(fy * fy + fz * fz)) *
    57.295779513082323 * 0.050000000000000044 + (0.01 * rtU.Gyro_y +
    rtDW.Memory_PreviousInput) * 0.95;
  fy = (0.01 * rtU.Gyro_x + rtDW.Memory1_PreviousInput) * 0.95 +
    57.295779513082323 * atan2(fy, fz) * 0.050000000000000044;

  /* SignalConversion: '<S1>/TmpSignal ConversionAtLQRInport1' incorporates:
   *  Gain: '<S1>/Gain1'
   *  Inport: '<Root>/Gyro_x'
   *  Inport: '<Root>/Gyro_y'
   *  Inport: '<Root>/Gyro_z'
   *  Inport: '<Root>/Ref_Pitch'
   *  Inport: '<Root>/Ref_Roll'
   *  Inport: '<Root>/Ref_YawRate'
   *  Sum: '<S1>/Add1'
   *  Sum: '<S1>/Add2'
   *  Sum: '<S1>/Add3'
   */
  fy_0[0] = fy - (-rtU.Ref_Roll);
  fy_0[1] = rtb_theta - rtU.Ref_Pitch;
  fy_0[2] = rtU.Gyro_x;
  fy_0[3] = rtU.Gyro_y;
  fy_0[4] = rtU.Gyro_z - rtU.Ref_YawRate;

  /* Sum: '<S1>/Add' incorporates:
   *  Gain: '<S1>/LQR'
   *  Inport: '<Root>/Base_Thrust'
   */
  for (i = 0; i < 4; i++) {
    fz = 0.0;
    for (i_0 = 0; i_0 < 5; i_0++) {
      fz += rtConstP.LQR_Gain[(i_0 << 2) + i] * fy_0[i_0];
    }

    rtb_Add[i] = rtU.Base_Thrust + fz;
  }

  /* End of Sum: '<S1>/Add' */

  /* DataTypeConversion: '<Root>/ToUint16' */
  if (rtb_Add[0] < 65536.0) {
    if (rtb_Add[0] >= 0.0) {
      /* Outport: '<Root>/Motor_1' */
      rtY.Motor_1 = (uint16_T)rtb_Add[0];
    } else {
      /* Outport: '<Root>/Motor_1' */
      rtY.Motor_1 = 0U;
    }
  } else {
    /* Outport: '<Root>/Motor_1' */
    rtY.Motor_1 = MAX_uint16_T;
  }

  /* End of DataTypeConversion: '<Root>/ToUint16' */

  /* DataTypeConversion: '<Root>/ToUint16_1' */
  if (rtb_Add[1] < 65536.0) {
    if (rtb_Add[1] >= 0.0) {
      /* Outport: '<Root>/Motor_2' */
      rtY.Motor_2 = (uint16_T)rtb_Add[1];
    } else {
      /* Outport: '<Root>/Motor_2' */
      rtY.Motor_2 = 0U;
    }
  } else {
    /* Outport: '<Root>/Motor_2' */
    rtY.Motor_2 = MAX_uint16_T;
  }

  /* End of DataTypeConversion: '<Root>/ToUint16_1' */

  /* DataTypeConversion: '<Root>/ToUint16_2' */
  if (rtb_Add[2] < 65536.0) {
    if (rtb_Add[2] >= 0.0) {
      /* Outport: '<Root>/Motor_3' */
      rtY.Motor_3 = (uint16_T)rtb_Add[2];
    } else {
      /* Outport: '<Root>/Motor_3' */
      rtY.Motor_3 = 0U;
    }
  } else {
    /* Outport: '<Root>/Motor_3' */
    rtY.Motor_3 = MAX_uint16_T;
  }

  /* End of DataTypeConversion: '<Root>/ToUint16_2' */

  /* DataTypeConversion: '<Root>/ToUint16_3' */
  if (rtb_Add[3] < 65536.0) {
    if (rtb_Add[3] >= 0.0) {
      /* Outport: '<Root>/Motor_4' */
      rtY.Motor_4 = (uint16_T)rtb_Add[3];
    } else {
      /* Outport: '<Root>/Motor_4' */
      rtY.Motor_4 = 0U;
    }
  } else {
    /* Outport: '<Root>/Motor_4' */
    rtY.Motor_4 = MAX_uint16_T;
  }

  /* End of DataTypeConversion: '<Root>/ToUint16_3' */

  /* Outport: '<Root>/Log1' */
  rtY.Log1 = rtb_theta;

  /* Outport: '<Root>/Log2' */
  rtY.Log2 = fy;

  /* Outport: '<Root>/Log3' incorporates:
   *  Inport: '<Root>/Acc_x'
   */
  rtY.Log3 = rtU.Acc_x;

  /* Outport: '<Root>/Log4' incorporates:
   *  Inport: '<Root>/Acc_y'
   */
  rtY.Log4 = rtU.Acc_y;

  /* Outport: '<Root>/Log5' incorporates:
   *  DiscreteIntegrator: '<Root>/Discrete-Time Integrator'
   */
  rtY.Log5 = rtDW.DiscreteTimeIntegrator_DSTATE;

  /* Outport: '<Root>/Log6' incorporates:
   *  DiscreteIntegrator: '<Root>/Discrete-Time Integrator1'
   */
  rtY.Log6 = rtDW.DiscreteTimeIntegrator1_DSTATE;

  /* Update for Memory: '<Root>/Memory' */
  rtDW.Memory_PreviousInput = rtb_theta;

  /* Update for Memory: '<Root>/Memory1' */
  rtDW.Memory1_PreviousInput = fy;

  /* Update for DiscreteIntegrator: '<Root>/Discrete-Time Integrator' incorporates:
   *  Inport: '<Root>/Gyro_y'
   */
  rtDW.DiscreteTimeIntegrator_DSTATE += 0.01 * rtU.Gyro_y;

  /* Update for DiscreteIntegrator: '<Root>/Discrete-Time Integrator1' incorporates:
   *  Inport: '<Root>/Gyro_x'
   */
  rtDW.DiscreteTimeIntegrator1_DSTATE += 0.01 * rtU.Gyro_x;
}

/* Model initialize function */
void crazyflie_initialize(void)
{
  /* (no initialization code required) */
}

/* Model terminate function */
void crazyflie_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
