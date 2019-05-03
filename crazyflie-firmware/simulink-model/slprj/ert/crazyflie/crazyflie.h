/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: crazyflie.h
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

#ifndef RTW_HEADER_crazyflie_h_
#define RTW_HEADER_crazyflie_h_
#include <math.h>
#ifndef crazyflie_COMMON_INCLUDES_
# define crazyflie_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* crazyflie_COMMON_INCLUDES_ */

/* Block signals and states (default storage) for model 'crazyflie' */
typedef struct {
  real_T DiscreteTimeIntegrator_DSTATE;/* '<Root>/Discrete-Time Integrator' */
  real_T DiscreteTimeIntegrator1_DSTATE;/* '<Root>/Discrete-Time Integrator1' */
  real_T DiscreteTimeIntegrator_DSTATE_m;/* '<S1>/Discrete-Time Integrator' */
  real_T DiscreteTimeIntegrator1_DSTAT_b;/* '<S1>/Discrete-Time Integrator1' */
  real_T DiscreteTimeIntegrator2_DSTATE;/* '<S1>/Discrete-Time Integrator2' */
  real_T Memory_PreviousInput;         /* '<Root>/Memory' */
  real_T Memory1_PreviousInput;        /* '<Root>/Memory1' */
} crazyflie_DW_f;

typedef struct {
  crazyflie_DW_f rtdw;
} crazyflie_MdlrefDW;

extern void crazyflie(const real_T *rtu_Base_Thrust, const real_T *rtu_Ref_Roll,
                      const real_T *rtu_Ref_Pitch, const real_T *rtu_Ref_YawRate,
                      const real_T *rtu_Acc_x, const real_T *rtu_Acc_y, const
                      real_T *rtu_Acc_z, const real_T *rtu_Gyro_x, const real_T *
                      rtu_Gyro_y, const real_T *rtu_Gyro_z, uint16_T
                      *rty_Motor_1, uint16_T *rty_Motor_2, uint16_T *rty_Motor_3,
                      uint16_T *rty_Motor_4, real_T *rty_Log1, real_T *rty_Log2,
                      real_T *rty_Log3, real_T *rty_Log4, real_T *rty_Log5,
                      real_T *rty_Log6, crazyflie_DW_f *localDW);

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S3>/Gain' : Unused code path elimination
 * Block '<S3>/Gain1' : Unused code path elimination
 * Block '<S3>/Sum' : Unused code path elimination
 * Block '<S3>/Sum1' : Unused code path elimination
 * Block '<S3>/Sum2' : Unused code path elimination
 * Block '<S3>/Sum3' : Unused code path elimination
 * Block '<S3>/Unary Minus' : Unused code path elimination
 * Block '<S3>/Unary Minus1' : Unused code path elimination
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'crazyflie'
 * '<S1>'   : 'crazyflie/LQR Control'
 * '<S2>'   : 'crazyflie/MATLAB Function'
 * '<S3>'   : 'crazyflie/Subsystem1'
 */
#endif                                 /* RTW_HEADER_crazyflie_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
