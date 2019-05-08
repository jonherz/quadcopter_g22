/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: crazyflie.c
 *
 * Code generated for Simulink model 'crazyflie'.
 *
 * Model version                  : 1.193
 * Simulink Coder version         : 9.0 (R2018b) 24-May-2018
 * C/C++ source code generated on : Fri May  3 12:32:55 2019
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives:
 *    1. Execution efficiency
 *    2. RAM efficiency
 * Validation result: Not run
 */

#include "crazyflie.h"

extern const real_T rtCP_pooled_VoPnT3ZVOFV2[32];

#define rtCP_LQR_Gain                  rtCP_pooled_VoPnT3ZVOFV2  /* Expression: -KLQR
                                                                  * Referenced by: '<S1>/LQR'
                                                                  */

/* Output and update for referenced model: 'crazyflie' */
void crazyflie(const real_T *rtu_Base_Thrust, const real_T *rtu_Ref_Roll, const
               real_T *rtu_Ref_Pitch, const real_T *rtu_Ref_YawRate, const
               real_T *rtu_Acc_x, const real_T *rtu_Acc_y, const real_T
               *rtu_Acc_z, const real_T *rtu_Gyro_x, const real_T *rtu_Gyro_y,
               const real_T *rtu_Gyro_z, uint16_T *rty_Motor_1, uint16_T
               *rty_Motor_2, uint16_T *rty_Motor_3, uint16_T *rty_Motor_4,
               real_T *rty_Log1, real_T *rty_Log2, real_T *rty_Log3, real_T
               *rty_Log4, real_T *rty_Log5, real_T *rty_Log6, crazyflie_DW_f
               *localDW)
{
  real_T fy;
  real_T fz;
  real_T rtb_Gain3;
  real_T rtb_Gain4;
  real_T rtb_Gain5;
  real_T rtb_theta;
  real_T rtb_Saturation[4];
  real_T fy_0[8];
  int32_T i;
  int32_T i_0;

  /* Gain: '<Root>/Gain3' */
  rtb_Gain3 = 0.017453292519943295 * *rtu_Gyro_x;

  /* Gain: '<Root>/Gain4' */
  rtb_Gain4 = 0.017453292519943295 * *rtu_Gyro_y;

  /* Gain: '<Root>/Gain5' */
  rtb_Gain5 = 0.017453292519943295 * *rtu_Gyro_z;

  /* MATLAB Function: '<Root>/MATLAB Function' incorporates:
   *  Memory: '<Root>/Memory'
   *  Memory: '<Root>/Memory1'
   */
  /* MATLAB Function 'MATLAB Function': '<S2>:1' */
  /* '<S2>:1:2' gamma = 0.95; */
  /* '<S2>:1:3' h = 0.01; */
  /* '<S2>:1:5' fx = Acc_x/sqrt(Acc_x^2 + Acc_y^2 + Acc_z^2); */
  /* '<S2>:1:6' fy = Acc_y/sqrt(Acc_x^2 + Acc_y^2 + Acc_z^2); */
  rtb_theta = sqrt((*rtu_Acc_x * *rtu_Acc_x + *rtu_Acc_y * *rtu_Acc_y) +
                   *rtu_Acc_z * *rtu_Acc_z);
  fy = *rtu_Acc_y / rtb_theta;

  /* '<S2>:1:7' fz = Acc_z/sqrt(Acc_x^2 + Acc_y^2 + Acc_z^2); */
  fz = *rtu_Acc_z / rtb_theta;

  /* '<S2>:1:9' theta_a = atan2(-fx,sqrt(fy^2 + fz^2)); */
  /* '<S2>:1:10' phi_a = atan2(fy,fz); */
  /* '<S2>:1:13' theta = (1-gamma)*theta_a + gamma*(theta + h*gyro_y); */
  /* '<S2>:1:16' phi = (1-gamma)*phi_a + gamma*(phi + h*gyro_x); */
  rtb_theta = atan2(-(*rtu_Acc_x / rtb_theta), sqrt(fy * fy + fz * fz)) *
    0.050000000000000044 + (0.01 * rtb_Gain4 + localDW->Memory_PreviousInput) *
    0.95;
  fy = (0.01 * rtb_Gain3 + localDW->Memory1_PreviousInput) * 0.95 +
    0.050000000000000044 * atan2(fy, fz);

  /* SignalConversion: '<S1>/TmpSignal ConversionAtLQRInport1' incorporates:
   *  DiscreteIntegrator: '<S1>/Discrete-Time Integrator'
   *  DiscreteIntegrator: '<S1>/Discrete-Time Integrator1'
   *  DiscreteIntegrator: '<S1>/Discrete-Time Integrator2'
   */
  fy_0[0] = fy;
  fy_0[1] = rtb_theta;
  fy_0[2] = rtb_Gain3;
  fy_0[3] = rtb_Gain4;
  fy_0[4] = rtb_Gain5;
  fy_0[5] = localDW->DiscreteTimeIntegrator_DSTATE_m;
  fy_0[6] = localDW->DiscreteTimeIntegrator1_DSTAT_b;
  fy_0[7] = localDW->DiscreteTimeIntegrator2_DSTATE;
  for (i = 0; i < 4; i++) {
    /* Sum: '<S1>/Add' incorporates:
     *  Gain: '<S1>/LQR'
     */
    fz = 0.0;
    for (i_0 = 0; i_0 < 8; i_0++) {
      fz += rtCP_LQR_Gain[(i_0 << 2) + i] * fy_0[i_0];
    }

    fz += *rtu_Base_Thrust;

    /* End of Sum: '<S1>/Add' */

    /* Saturate: '<S1>/Saturation' */
    if (fz > 65536.0) {
      rtb_Saturation[i] = 65536.0;
    } else if (fz < 0.0) {
      rtb_Saturation[i] = 0.0;
    } else {
      rtb_Saturation[i] = fz;
    }

    /* End of Saturate: '<S1>/Saturation' */
  }

  /* DataTypeConversion: '<Root>/ToDouble' */
  *rty_Log1 = rtb_theta;

  /* DataTypeConversion: '<Root>/ToDouble1' */
  *rty_Log2 = fy;

  /* DataTypeConversion: '<Root>/ToDouble2' */
  *rty_Log3 = *rtu_Acc_x;

  /* DataTypeConversion: '<Root>/ToDouble3' */
  *rty_Log4 = *rtu_Acc_y;

  /* DataTypeConversion: '<Root>/ToDouble4' incorporates:
   *  DiscreteIntegrator: '<Root>/Discrete-Time Integrator'
   */
  *rty_Log5 = localDW->DiscreteTimeIntegrator_DSTATE;

  /* DataTypeConversion: '<Root>/ToDouble5' incorporates:
   *  DiscreteIntegrator: '<Root>/Discrete-Time Integrator1'
   */
  *rty_Log6 = localDW->DiscreteTimeIntegrator1_DSTATE;

  /* DataTypeConversion: '<Root>/ToUint16' */
  if (rtb_Saturation[0] < 65536.0) {
    *rty_Motor_1 = (uint16_T)rtb_Saturation[0];
  } else {
    *rty_Motor_1 = MAX_uint16_T;
  }

  /* End of DataTypeConversion: '<Root>/ToUint16' */

  /* DataTypeConversion: '<Root>/ToUint16_1' */
  if (rtb_Saturation[1] < 65536.0) {
    *rty_Motor_2 = (uint16_T)rtb_Saturation[1];
  } else {
    *rty_Motor_2 = MAX_uint16_T;
  }

  /* End of DataTypeConversion: '<Root>/ToUint16_1' */

  /* DataTypeConversion: '<Root>/ToUint16_2' */
  if (rtb_Saturation[2] < 65536.0) {
    *rty_Motor_3 = (uint16_T)rtb_Saturation[2];
  } else {
    *rty_Motor_3 = MAX_uint16_T;
  }

  /* End of DataTypeConversion: '<Root>/ToUint16_2' */

  /* DataTypeConversion: '<Root>/ToUint16_3' */
  if (rtb_Saturation[3] < 65536.0) {
    *rty_Motor_4 = (uint16_T)rtb_Saturation[3];
  } else {
    *rty_Motor_4 = MAX_uint16_T;
  }

  /* End of DataTypeConversion: '<Root>/ToUint16_3' */

  /* Update for DiscreteIntegrator: '<Root>/Discrete-Time Integrator' */
  localDW->DiscreteTimeIntegrator_DSTATE += 0.01 * rtb_Gain4;

  /* Update for DiscreteIntegrator: '<Root>/Discrete-Time Integrator1' */
  localDW->DiscreteTimeIntegrator1_DSTATE += 0.01 * rtb_Gain3;

  /* Update for Memory: '<Root>/Memory' */
  localDW->Memory_PreviousInput = rtb_theta;

  /* Update for Memory: '<Root>/Memory1' */
  localDW->Memory1_PreviousInput = fy;

  /* Update for DiscreteIntegrator: '<S1>/Discrete-Time Integrator' incorporates:
   *  Gain: '<Root>/Gain'
   *  Sum: '<S1>/Sum3'
   */
  localDW->DiscreteTimeIntegrator_DSTATE_m += (0.017453292519943295 *
    *rtu_Ref_Roll - fy) * 0.01;

  /* Update for DiscreteIntegrator: '<S1>/Discrete-Time Integrator1' incorporates:
   *  Gain: '<Root>/Gain1'
   *  Sum: '<S1>/Sum1'
   */
  localDW->DiscreteTimeIntegrator1_DSTAT_b += (0.017453292519943295 *
    *rtu_Ref_Pitch - rtb_theta) * 0.01;

  /* Update for DiscreteIntegrator: '<S1>/Discrete-Time Integrator2' incorporates:
   *  Gain: '<Root>/Gain2'
   *  Sum: '<S1>/Sum2'
   */
  localDW->DiscreteTimeIntegrator2_DSTATE += (0.017453292519943295 *
    *rtu_Ref_YawRate - rtb_Gain5) * 0.01;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
