/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: crazyflie.c
 *
 * Code generated for Simulink model 'crazyflie'.
 *
 * Model version                  : 1.173
 * Simulink Coder version         : 9.0 (R2018b) 24-May-2018
 * C/C++ source code generated on : Fri Apr  5 15:19:05 2019
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
  real_T rtb_Gain1;
  real_T tmp;

  /* MATLAB Function: '<Root>/MATLAB Function' incorporates:
   *  Inport: '<Root>/Acc_x'
   *  Inport: '<Root>/Acc_y'
   *  Inport: '<Root>/Acc_z'
   *  Inport: '<Root>/Gyro_x'
   *  Inport: '<Root>/Gyro_y'
   *  Memory: '<Root>/Memory'
   *  Memory: '<Root>/Memory1'
   */
  /* MATLAB Function 'MATLAB Function': '<S1>:1' */
  /* '<S1>:1:2' gamma = 0.1; */
  /* '<S1>:1:3' h = 0.01; */
  /* '<S1>:1:5' fx = Acc_x/sqrt(Acc_x^2 + Acc_y^2 + Acc_z^2); */
  /* '<S1>:1:6' fy = Acc_y/sqrt(Acc_x^2 + Acc_y^2 + Acc_z^2); */
  rtb_theta = sqrt((rtU.Acc_x * rtU.Acc_x + rtU.Acc_y * rtU.Acc_y) + rtU.Acc_z *
                   rtU.Acc_z);
  fy = rtU.Acc_y / rtb_theta;

  /* '<S1>:1:7' fz = Acc_z/sqrt(Acc_x^2 + Acc_y^2 + Acc_z^2); */
  fz = rtU.Acc_z / rtb_theta;

  /* '<S1>:1:9' theta_a = atan2(-fx,sqrt(fy^2 + fz^2)); */
  /* '<S1>:1:10' phi_a = atan2(fy,fz); */
  /* '<S1>:1:13' theta = (1-gamma)*theta_a + gamma*(theta + h*gyro_y); */
  /* '<S1>:1:16' phi = (1-gamma)*phi_a + gamma*(phi + h*gyro_x); */
  rtb_theta = atan2(-(rtU.Acc_x / rtb_theta), sqrt(fy * fy + fz * fz)) * 0.9 +
    (0.01 * rtU.Gyro_y + rtDW.Memory_PreviousInput) * 0.1;
  fy = (0.01 * rtU.Gyro_x + rtDW.Memory1_PreviousInput) * 0.1 + 0.9 * atan2(fy,
    fz);

  /* Gain: '<S2>/Gain' */
  fz = 4000.0 * fy;

  /* Gain: '<S2>/Gain1' */
  rtb_Gain1 = 4000.0 * rtb_theta;

  /* DataTypeConversion: '<Root>/ToUint16' incorporates:
   *  Sum: '<S2>/Sum'
   */
  tmp = fz + rtb_Gain1;
  if (tmp < 65536.0) {
    if (tmp >= 0.0) {
      /* Outport: '<Root>/Motor_1' */
      rtY.Motor_1 = (uint16_T)tmp;
    } else {
      /* Outport: '<Root>/Motor_1' */
      rtY.Motor_1 = 0U;
    }
  } else {
    /* Outport: '<Root>/Motor_1' */
    rtY.Motor_1 = MAX_uint16_T;
  }

  /* End of DataTypeConversion: '<Root>/ToUint16' */

  /* DataTypeConversion: '<Root>/ToUint16_1' incorporates:
   *  Sum: '<S2>/Sum1'
   *  UnaryMinus: '<S2>/Unary Minus1'
   */
  tmp = fz + -rtb_Gain1;
  if (tmp < 65536.0) {
    if (tmp >= 0.0) {
      /* Outport: '<Root>/Motor_2' */
      rtY.Motor_2 = (uint16_T)tmp;
    } else {
      /* Outport: '<Root>/Motor_2' */
      rtY.Motor_2 = 0U;
    }
  } else {
    /* Outport: '<Root>/Motor_2' */
    rtY.Motor_2 = MAX_uint16_T;
  }

  /* End of DataTypeConversion: '<Root>/ToUint16_1' */

  /* UnaryMinus: '<S2>/Unary Minus' */
  fz = -fz;

  /* DataTypeConversion: '<Root>/ToUint16_2' incorporates:
   *  Sum: '<S2>/Sum2'
   *  UnaryMinus: '<S2>/Unary Minus1'
   */
  tmp = fz + -rtb_Gain1;
  if (tmp < 65536.0) {
    if (tmp >= 0.0) {
      /* Outport: '<Root>/Motor_3' */
      rtY.Motor_3 = (uint16_T)tmp;
    } else {
      /* Outport: '<Root>/Motor_3' */
      rtY.Motor_3 = 0U;
    }
  } else {
    /* Outport: '<Root>/Motor_3' */
    rtY.Motor_3 = MAX_uint16_T;
  }

  /* End of DataTypeConversion: '<Root>/ToUint16_2' */

  /* Sum: '<S2>/Sum3' */
  fz += rtb_Gain1;

  /* DataTypeConversion: '<Root>/ToUint16_3' */
  if (fz < 65536.0) {
    if (fz >= 0.0) {
      /* Outport: '<Root>/Motor_4' */
      rtY.Motor_4 = (uint16_T)fz;
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
