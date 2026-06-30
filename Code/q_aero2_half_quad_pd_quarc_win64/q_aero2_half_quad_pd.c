/*
 * q_aero2_half_quad_pd.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "q_aero2_half_quad_pd".
 *
 * Model version              : 19.6
 * Simulink Coder version : 24.2 (R2024b) 21-Jun-2024
 * C source code generated on : Tue Jun 30 16:56:29 2026
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "q_aero2_half_quad_pd.h"
#include "rtwtypes.h"
#include "q_aero2_half_quad_pd_private.h"
#include <string.h>
#include "rt_nonfinite.h"
#include "q_aero2_half_quad_pd_dt.h"

/* Block signals (default storage) */
B_q_aero2_half_quad_pd_T q_aero2_half_quad_pd_B;

/* Continuous states */
X_q_aero2_half_quad_pd_T q_aero2_half_quad_pd_X;

/* Disabled State Vector */
XDis_q_aero2_half_quad_pd_T q_aero2_half_quad_pd_XDis;

/* Block states (default storage) */
DW_q_aero2_half_quad_pd_T q_aero2_half_quad_pd_DW;

/* Real-time model */
static RT_MODEL_q_aero2_half_quad_pd_T q_aero2_half_quad_pd_M_;
RT_MODEL_q_aero2_half_quad_pd_T *const q_aero2_half_quad_pd_M =
  &q_aero2_half_quad_pd_M_;

/*
 * This function updates continuous states using the ODE1 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE1_IntgData *id = (ODE1_IntgData *)rtsiGetSolverData(si);
  real_T *f0 = id->f[0];
  int_T i;
  int_T nXc = 5;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);
  rtsiSetdX(si, f0);
  q_aero2_half_quad_pd_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; ++i) {
    x[i] += h * f0[i];
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model output function */
void q_aero2_half_quad_pd_output(void)
{
  real_T lastTime;
  real_T rtb_HILReadEncoderTimebase;
  real_T rtb_SmoothSignalGenerator1;
  real_T *lastU;
  boolean_T tmp;
  if (rtmIsMajorTimeStep(q_aero2_half_quad_pd_M)) {
    /* set solver stop time */
    if (!(q_aero2_half_quad_pd_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&q_aero2_half_quad_pd_M->solverInfo,
                            ((q_aero2_half_quad_pd_M->Timing.clockTickH0 + 1) *
        q_aero2_half_quad_pd_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&q_aero2_half_quad_pd_M->solverInfo,
                            ((q_aero2_half_quad_pd_M->Timing.clockTick0 + 1) *
        q_aero2_half_quad_pd_M->Timing.stepSize0 +
        q_aero2_half_quad_pd_M->Timing.clockTickH0 *
        q_aero2_half_quad_pd_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(q_aero2_half_quad_pd_M)) {
    q_aero2_half_quad_pd_M->Timing.t[0] = rtsiGetT
      (&q_aero2_half_quad_pd_M->solverInfo);
  }

  tmp = rtmIsMajorTimeStep(q_aero2_half_quad_pd_M);
  if (tmp) {
    /* S-Function (hil_read_encoder_timebase_block): '<Root>/HIL Read Encoder Timebase' */

    /* S-Function Block: q_aero2_half_quad_pd/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
    {
      t_error result;
      result = hil_task_read_encoder
        (q_aero2_half_quad_pd_DW.HILReadEncoderTimebase_Task, 1,
         &q_aero2_half_quad_pd_DW.HILReadEncoderTimebase_Buffer);
      if (result < 0) {
        rtb_HILReadEncoderTimebase = 0;
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_aero2_half_quad_pd_M, _rt_error_message);
      } else {
        rtb_HILReadEncoderTimebase =
          q_aero2_half_quad_pd_DW.HILReadEncoderTimebase_Buffer;
      }
    }

    /* ManualSwitch: '<Root>/Disturbance Switch' */
    if (q_aero2_half_quad_pd_P.DisturbanceSwitch_CurrentSettin == 1) {
      /* ManualSwitch: '<Root>/Disturbance Switch' incorporates:
       *  Constant: '<Root>/ON'
       */
      q_aero2_half_quad_pd_B.DisturbanceSwitch = q_aero2_half_quad_pd_P.ON_Value;
    } else {
      /* ManualSwitch: '<Root>/Disturbance Switch' incorporates:
       *  Constant: '<Root>/OFF'
       */
      q_aero2_half_quad_pd_B.DisturbanceSwitch =
        q_aero2_half_quad_pd_P.OFF_Value;
    }

    /* End of ManualSwitch: '<Root>/Disturbance Switch' */

    /* S-Function (smooth_signal_generator_block): '<Root>/Smooth Signal Generator1' */
    /* S-Function Block: q_aero2_half_quad_pd/Smooth Signal Generator1 (smooth_signal_generator_block) */
    {
      real_T w = TWO_PI * q_aero2_half_quad_pd_P.SmoothSignalGenerator1_Frequenc;
      boolean_T params_changed =
        (q_aero2_half_quad_pd_P.SmoothSignalGenerator1_Amplitud !=
         q_aero2_half_quad_pd_DW.SmoothSignalGenerator1_RWORK.Amp || w !=
         q_aero2_half_quad_pd_DW.SmoothSignalGenerator1_RWORK.W);
      real_T T = TWO_PI / q_aero2_half_quad_pd_DW.SmoothSignalGenerator1_RWORK.W;
      if (q_aero2_half_quad_pd_DW.SmoothSignalGenerator1_RWORK.T < 0.5 * T) {
        rtb_SmoothSignalGenerator1 =
          q_aero2_half_quad_pd_DW.SmoothSignalGenerator1_RWORK.Amp;
      } else {
        rtb_SmoothSignalGenerator1 =
          -q_aero2_half_quad_pd_DW.SmoothSignalGenerator1_RWORK.Amp;
      }

      /*
         If the amplitude or frequency parameter changes, then adjust the
         square wave parameters such that the square wave output is continuous.
       */
      if (params_changed) {
        /*
           Change the amplitude or frequency when the sign of the output
           changes. This technique ensures that we don't get intermediate
           jumps in amplitude and we don't get higher frequencies than
           expected due to a pulse being prematurely truncated.
         */
        if (q_aero2_half_quad_pd_P.SmoothSignalGenerator1_Amplitud == 0 ||
            rtb_SmoothSignalGenerator1 == 0 ||
            q_aero2_half_quad_pd_DW.SmoothSignalGenerator1_RWORK.Y == 0 ||
            (rtb_SmoothSignalGenerator1 < 0) !=
            (q_aero2_half_quad_pd_DW.SmoothSignalGenerator1_RWORK.Y < 0)) {
          q_aero2_half_quad_pd_DW.SmoothSignalGenerator1_RWORK.Amp =
            q_aero2_half_quad_pd_P.SmoothSignalGenerator1_Amplitud;
          q_aero2_half_quad_pd_DW.SmoothSignalGenerator1_RWORK.W = w;
          T = TWO_PI / w;
          if (rtb_SmoothSignalGenerator1 >= 0) {
            q_aero2_half_quad_pd_DW.SmoothSignalGenerator1_RWORK.T = 0;
            rtb_SmoothSignalGenerator1 =
              q_aero2_half_quad_pd_P.SmoothSignalGenerator1_Amplitud;
          } else {
            q_aero2_half_quad_pd_DW.SmoothSignalGenerator1_RWORK.T = T / 2;
            rtb_SmoothSignalGenerator1 =
              -q_aero2_half_quad_pd_P.SmoothSignalGenerator1_Amplitud;
          }
        }
      }

      q_aero2_half_quad_pd_DW.SmoothSignalGenerator1_RWORK.T += 0.002;
      if (q_aero2_half_quad_pd_DW.SmoothSignalGenerator1_RWORK.T >= T) {
        q_aero2_half_quad_pd_DW.SmoothSignalGenerator1_RWORK.T = 0;
      }

      q_aero2_half_quad_pd_DW.SmoothSignalGenerator1_RWORK.Y =
        rtb_SmoothSignalGenerator1;
    }

    /* Gain: '<Root>/Amp_y (deg)' */
    q_aero2_half_quad_pd_B.Amp_ydeg = q_aero2_half_quad_pd_P.Amp_ydeg_Gain *
      rtb_SmoothSignalGenerator1;

    /* Gain: '<S2>/Gain1' */
    q_aero2_half_quad_pd_B.Gain1 = q_aero2_half_quad_pd_P.Gain1_Gain *
      q_aero2_half_quad_pd_B.Amp_ydeg;
  }

  /* Derivative: '<S1>/Derivative' incorporates:
   *  Derivative: '<S1>/Derivative1'
   */
  rtb_SmoothSignalGenerator1 = q_aero2_half_quad_pd_M->Timing.t[0];
  if ((q_aero2_half_quad_pd_DW.TimeStampA >= rtb_SmoothSignalGenerator1) &&
      (q_aero2_half_quad_pd_DW.TimeStampB >= rtb_SmoothSignalGenerator1)) {
    /* Derivative: '<S1>/Derivative' */
    q_aero2_half_quad_pd_B.Derivative = 0.0;
  } else {
    lastTime = q_aero2_half_quad_pd_DW.TimeStampA;
    lastU = &q_aero2_half_quad_pd_DW.LastUAtTimeA;
    if (q_aero2_half_quad_pd_DW.TimeStampA < q_aero2_half_quad_pd_DW.TimeStampB)
    {
      if (q_aero2_half_quad_pd_DW.TimeStampB < rtb_SmoothSignalGenerator1) {
        lastTime = q_aero2_half_quad_pd_DW.TimeStampB;
        lastU = &q_aero2_half_quad_pd_DW.LastUAtTimeB;
      }
    } else if (q_aero2_half_quad_pd_DW.TimeStampA >= rtb_SmoothSignalGenerator1)
    {
      lastTime = q_aero2_half_quad_pd_DW.TimeStampB;
      lastU = &q_aero2_half_quad_pd_DW.LastUAtTimeB;
    }

    /* Derivative: '<S1>/Derivative' */
    q_aero2_half_quad_pd_B.Derivative = (q_aero2_half_quad_pd_B.Gain1 - *lastU) /
      (rtb_SmoothSignalGenerator1 - lastTime);
  }

  /* End of Derivative: '<S1>/Derivative' */

  /* Derivative: '<S1>/Derivative1' */
  if ((q_aero2_half_quad_pd_DW.TimeStampA_a >= rtb_SmoothSignalGenerator1) &&
      (q_aero2_half_quad_pd_DW.TimeStampB_m >= rtb_SmoothSignalGenerator1)) {
    rtb_SmoothSignalGenerator1 = 0.0;
  } else {
    lastTime = q_aero2_half_quad_pd_DW.TimeStampA_a;
    lastU = &q_aero2_half_quad_pd_DW.LastUAtTimeA_k;
    if (q_aero2_half_quad_pd_DW.TimeStampA_a <
        q_aero2_half_quad_pd_DW.TimeStampB_m) {
      if (q_aero2_half_quad_pd_DW.TimeStampB_m < rtb_SmoothSignalGenerator1) {
        lastTime = q_aero2_half_quad_pd_DW.TimeStampB_m;
        lastU = &q_aero2_half_quad_pd_DW.LastUAtTimeB_g;
      }
    } else if (q_aero2_half_quad_pd_DW.TimeStampA_a >=
               rtb_SmoothSignalGenerator1) {
      lastTime = q_aero2_half_quad_pd_DW.TimeStampB_m;
      lastU = &q_aero2_half_quad_pd_DW.LastUAtTimeB_g;
    }

    rtb_SmoothSignalGenerator1 = (q_aero2_half_quad_pd_B.Derivative - *lastU) /
      (rtb_SmoothSignalGenerator1 - lastTime);
  }

  if (tmp) {
    /* Gain: '<Root>/yaw: counts to rad' */
    q_aero2_half_quad_pd_B.yaw = q_aero2_half_quad_pd_P.yawcountstorad_Gain *
      rtb_HILReadEncoderTimebase;

    /* Sum: '<S1>/Sum' */
    q_aero2_half_quad_pd_B.e = q_aero2_half_quad_pd_B.Gain1 -
      q_aero2_half_quad_pd_B.yaw;

    /* Product: '<S1>/Product1' incorporates:
     *  Constant: '<S1>/Kp'
     */
    q_aero2_half_quad_pd_B.Product1 = q_aero2_half_quad_pd_B.e *
      q_aero2_half_quad_pd_P.Controller_Kp;
  }

  /* Product: '<S4>/Product1' incorporates:
   *  Constant: '<S1>/Wn'
   *  Integrator: '<S4>/Integrator2'
   */
  q_aero2_half_quad_pd_B.Product1_i = q_aero2_half_quad_pd_P.Controller_Wn *
    q_aero2_half_quad_pd_X.Integrator2_CSTATE;

  /* Product: '<S5>/Product1' incorporates:
   *  Constant: '<S1>/Wn'
   *  Integrator: '<S5>/Integrator2'
   */
  q_aero2_half_quad_pd_B.Product1_m = q_aero2_half_quad_pd_P.Controller_Wn *
    q_aero2_half_quad_pd_X.Integrator2_CSTATE_h;

  /* Sum: '<Root>/Sum' incorporates:
   *  Constant: '<S1>/Ka'
   *  Constant: '<S1>/Kd'
   *  Constant: '<S1>/Ki'
   *  Constant: '<S1>/Kv'
   *  Integrator: '<S1>/Integrator'
   *  Product: '<S1>/Product'
   *  Product: '<S1>/Product2'
   *  Product: '<S1>/Product3'
   *  Product: '<S1>/Product4'
   *  Sum: '<S1>/Sum1'
   */
  rtb_HILReadEncoderTimebase = ((((q_aero2_half_quad_pd_P.Ka_Value *
    rtb_SmoothSignalGenerator1 + q_aero2_half_quad_pd_B.Product1) +
    q_aero2_half_quad_pd_B.Product1_i * q_aero2_half_quad_pd_P.Kd_Value) +
    q_aero2_half_quad_pd_X.Integrator_CSTATE *
    q_aero2_half_quad_pd_P.Controller_Ki) - q_aero2_half_quad_pd_B.Product1_m *
    q_aero2_half_quad_pd_P.Controller_Kv) +
    q_aero2_half_quad_pd_B.DisturbanceSwitch;

  /* Saturate: '<Root>/+//- 24V' */
  if (rtb_HILReadEncoderTimebase > q_aero2_half_quad_pd_P.u4V_UpperSat) {
    /* Saturate: '<Root>/+//- 24V' */
    q_aero2_half_quad_pd_B.u4V = q_aero2_half_quad_pd_P.u4V_UpperSat;
  } else if (rtb_HILReadEncoderTimebase < q_aero2_half_quad_pd_P.u4V_LowerSat) {
    /* Saturate: '<Root>/+//- 24V' */
    q_aero2_half_quad_pd_B.u4V = q_aero2_half_quad_pd_P.u4V_LowerSat;
  } else {
    /* Saturate: '<Root>/+//- 24V' */
    q_aero2_half_quad_pd_B.u4V = rtb_HILReadEncoderTimebase;
  }

  /* End of Saturate: '<Root>/+//- 24V' */

  /* Gain: '<Root>/For +ve  response' */
  q_aero2_half_quad_pd_B.Forveresponse =
    q_aero2_half_quad_pd_P.Forveresponse_Gain * q_aero2_half_quad_pd_B.u4V;
  if (tmp) {
    /* S-Function (hil_write_analog_block): '<Root>/HIL Write Analog' */

    /* S-Function Block: q_aero2_half_quad_pd/HIL Write Analog (hil_write_analog_block) */
    {
      t_error result;
      q_aero2_half_quad_pd_DW.HILWriteAnalog_Buffer[0] =
        q_aero2_half_quad_pd_B.Forveresponse;
      q_aero2_half_quad_pd_DW.HILWriteAnalog_Buffer[1] =
        q_aero2_half_quad_pd_B.u4V;
      result = hil_write_analog(q_aero2_half_quad_pd_DW.HILInitialize_Card,
        q_aero2_half_quad_pd_P.HILWriteAnalog_channels, 2,
        &q_aero2_half_quad_pd_DW.HILWriteAnalog_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_aero2_half_quad_pd_M, _rt_error_message);
      }
    }

    /* Gain: '<S3>/Gain' */
    q_aero2_half_quad_pd_B.Gain = q_aero2_half_quad_pd_P.Gain_Gain *
      q_aero2_half_quad_pd_B.yaw;
  }

  /* Integrator: '<S4>/Integrator1' */
  if (q_aero2_half_quad_pd_DW.Integrator1_DWORK1) {
    q_aero2_half_quad_pd_X.Integrator1_CSTATE = q_aero2_half_quad_pd_B.e;
  }

  /* Product: '<S4>/Product' incorporates:
   *  Constant: '<S1>/Damping'
   *  Constant: '<S1>/Wn'
   *  Constant: '<S4>/Constant'
   *  Integrator: '<S4>/Integrator1'
   *  Integrator: '<S4>/Integrator2'
   *  Product: '<S4>/Product2'
   *  Sum: '<S4>/Sum'
   *  Sum: '<S4>/Sum1'
   */
  q_aero2_half_quad_pd_B.Product = ((q_aero2_half_quad_pd_B.e -
    q_aero2_half_quad_pd_X.Integrator1_CSTATE) -
    q_aero2_half_quad_pd_X.Integrator2_CSTATE *
    q_aero2_half_quad_pd_P.Constant_Value * q_aero2_half_quad_pd_P.Damping_Value)
    * q_aero2_half_quad_pd_P.Controller_Wn;

  /* Integrator: '<S5>/Integrator1' */
  if (q_aero2_half_quad_pd_DW.Integrator1_DWORK1_h) {
    q_aero2_half_quad_pd_X.Integrator1_CSTATE_a = q_aero2_half_quad_pd_B.yaw;
  }

  /* Product: '<S5>/Product' incorporates:
   *  Constant: '<S1>/Damping'
   *  Constant: '<S1>/Wn'
   *  Constant: '<S5>/Constant'
   *  Integrator: '<S5>/Integrator1'
   *  Integrator: '<S5>/Integrator2'
   *  Product: '<S5>/Product2'
   *  Sum: '<S5>/Sum'
   *  Sum: '<S5>/Sum1'
   */
  q_aero2_half_quad_pd_B.Product_b = ((q_aero2_half_quad_pd_B.yaw -
    q_aero2_half_quad_pd_X.Integrator1_CSTATE_a) -
    q_aero2_half_quad_pd_X.Integrator2_CSTATE_h *
    q_aero2_half_quad_pd_P.Constant_Value_g *
    q_aero2_half_quad_pd_P.Damping_Value) * q_aero2_half_quad_pd_P.Controller_Wn;
}

/* Model update function */
void q_aero2_half_quad_pd_update(void)
{
  real_T *lastU;

  /* Update for Derivative: '<S1>/Derivative' */
  if (q_aero2_half_quad_pd_DW.TimeStampA == (rtInf)) {
    q_aero2_half_quad_pd_DW.TimeStampA = q_aero2_half_quad_pd_M->Timing.t[0];
    lastU = &q_aero2_half_quad_pd_DW.LastUAtTimeA;
  } else if (q_aero2_half_quad_pd_DW.TimeStampB == (rtInf)) {
    q_aero2_half_quad_pd_DW.TimeStampB = q_aero2_half_quad_pd_M->Timing.t[0];
    lastU = &q_aero2_half_quad_pd_DW.LastUAtTimeB;
  } else if (q_aero2_half_quad_pd_DW.TimeStampA <
             q_aero2_half_quad_pd_DW.TimeStampB) {
    q_aero2_half_quad_pd_DW.TimeStampA = q_aero2_half_quad_pd_M->Timing.t[0];
    lastU = &q_aero2_half_quad_pd_DW.LastUAtTimeA;
  } else {
    q_aero2_half_quad_pd_DW.TimeStampB = q_aero2_half_quad_pd_M->Timing.t[0];
    lastU = &q_aero2_half_quad_pd_DW.LastUAtTimeB;
  }

  *lastU = q_aero2_half_quad_pd_B.Gain1;

  /* End of Update for Derivative: '<S1>/Derivative' */

  /* Update for Derivative: '<S1>/Derivative1' */
  if (q_aero2_half_quad_pd_DW.TimeStampA_a == (rtInf)) {
    q_aero2_half_quad_pd_DW.TimeStampA_a = q_aero2_half_quad_pd_M->Timing.t[0];
    lastU = &q_aero2_half_quad_pd_DW.LastUAtTimeA_k;
  } else if (q_aero2_half_quad_pd_DW.TimeStampB_m == (rtInf)) {
    q_aero2_half_quad_pd_DW.TimeStampB_m = q_aero2_half_quad_pd_M->Timing.t[0];
    lastU = &q_aero2_half_quad_pd_DW.LastUAtTimeB_g;
  } else if (q_aero2_half_quad_pd_DW.TimeStampA_a <
             q_aero2_half_quad_pd_DW.TimeStampB_m) {
    q_aero2_half_quad_pd_DW.TimeStampA_a = q_aero2_half_quad_pd_M->Timing.t[0];
    lastU = &q_aero2_half_quad_pd_DW.LastUAtTimeA_k;
  } else {
    q_aero2_half_quad_pd_DW.TimeStampB_m = q_aero2_half_quad_pd_M->Timing.t[0];
    lastU = &q_aero2_half_quad_pd_DW.LastUAtTimeB_g;
  }

  *lastU = q_aero2_half_quad_pd_B.Derivative;

  /* End of Update for Derivative: '<S1>/Derivative1' */

  /* Update for Integrator: '<S4>/Integrator1' */
  q_aero2_half_quad_pd_DW.Integrator1_DWORK1 = false;

  /* Update for Integrator: '<S5>/Integrator1' */
  q_aero2_half_quad_pd_DW.Integrator1_DWORK1_h = false;
  if (rtmIsMajorTimeStep(q_aero2_half_quad_pd_M)) {
    rt_ertODEUpdateContinuousStates(&q_aero2_half_quad_pd_M->solverInfo);
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++q_aero2_half_quad_pd_M->Timing.clockTick0)) {
    ++q_aero2_half_quad_pd_M->Timing.clockTickH0;
  }

  q_aero2_half_quad_pd_M->Timing.t[0] = rtsiGetSolverStopTime
    (&q_aero2_half_quad_pd_M->solverInfo);

  {
    /* Update absolute timer for sample time: [0.002s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick1"
     * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++q_aero2_half_quad_pd_M->Timing.clockTick1)) {
      ++q_aero2_half_quad_pd_M->Timing.clockTickH1;
    }

    q_aero2_half_quad_pd_M->Timing.t[1] =
      q_aero2_half_quad_pd_M->Timing.clockTick1 *
      q_aero2_half_quad_pd_M->Timing.stepSize1 +
      q_aero2_half_quad_pd_M->Timing.clockTickH1 *
      q_aero2_half_quad_pd_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Derivatives for root system: '<Root>' */
void q_aero2_half_quad_pd_derivatives(void)
{
  XDot_q_aero2_half_quad_pd_T *_rtXdot;
  _rtXdot = ((XDot_q_aero2_half_quad_pd_T *) q_aero2_half_quad_pd_M->derivs);

  /* Derivatives for Integrator: '<S4>/Integrator2' */
  _rtXdot->Integrator2_CSTATE = q_aero2_half_quad_pd_B.Product;

  /* Derivatives for Integrator: '<S1>/Integrator' */
  _rtXdot->Integrator_CSTATE = q_aero2_half_quad_pd_B.e;

  /* Derivatives for Integrator: '<S5>/Integrator2' */
  _rtXdot->Integrator2_CSTATE_h = q_aero2_half_quad_pd_B.Product_b;

  /* Derivatives for Integrator: '<S4>/Integrator1' */
  _rtXdot->Integrator1_CSTATE = q_aero2_half_quad_pd_B.Product1_i;

  /* Derivatives for Integrator: '<S5>/Integrator1' */
  _rtXdot->Integrator1_CSTATE_a = q_aero2_half_quad_pd_B.Product1_m;
}

/* Model initialize function */
void q_aero2_half_quad_pd_initialize(void)
{
  /* Start for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: q_aero2_half_quad_pd/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("quanser_aero2_usb", "0@tcpip://localhost:18950",
                      &q_aero2_half_quad_pd_DW.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(q_aero2_half_quad_pd_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_watchdog_clear(q_aero2_half_quad_pd_DW.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(q_aero2_half_quad_pd_M, _rt_error_message);
      return;
    }

    if ((q_aero2_half_quad_pd_P.HILInitialize_AIPStart && !is_switching) ||
        (q_aero2_half_quad_pd_P.HILInitialize_AIPEnter && is_switching)) {
      q_aero2_half_quad_pd_DW.HILInitialize_AIMinimums[0] =
        (q_aero2_half_quad_pd_P.HILInitialize_AILow);
      q_aero2_half_quad_pd_DW.HILInitialize_AIMinimums[1] =
        (q_aero2_half_quad_pd_P.HILInitialize_AILow);
      q_aero2_half_quad_pd_DW.HILInitialize_AIMaximums[0] =
        q_aero2_half_quad_pd_P.HILInitialize_AIHigh;
      q_aero2_half_quad_pd_DW.HILInitialize_AIMaximums[1] =
        q_aero2_half_quad_pd_P.HILInitialize_AIHigh;
      result = hil_set_analog_input_ranges
        (q_aero2_half_quad_pd_DW.HILInitialize_Card,
         q_aero2_half_quad_pd_P.HILInitialize_AIChannels, 2U,
         &q_aero2_half_quad_pd_DW.HILInitialize_AIMinimums[0],
         &q_aero2_half_quad_pd_DW.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_aero2_half_quad_pd_M, _rt_error_message);
        return;
      }
    }

    if ((q_aero2_half_quad_pd_P.HILInitialize_AOPStart && !is_switching) ||
        (q_aero2_half_quad_pd_P.HILInitialize_AOPEnter && is_switching)) {
      q_aero2_half_quad_pd_DW.HILInitialize_AOMinimums[0] =
        (q_aero2_half_quad_pd_P.HILInitialize_AOLow);
      q_aero2_half_quad_pd_DW.HILInitialize_AOMinimums[1] =
        (q_aero2_half_quad_pd_P.HILInitialize_AOLow);
      q_aero2_half_quad_pd_DW.HILInitialize_AOMaximums[0] =
        q_aero2_half_quad_pd_P.HILInitialize_AOHigh;
      q_aero2_half_quad_pd_DW.HILInitialize_AOMaximums[1] =
        q_aero2_half_quad_pd_P.HILInitialize_AOHigh;
      result = hil_set_analog_output_ranges
        (q_aero2_half_quad_pd_DW.HILInitialize_Card,
         q_aero2_half_quad_pd_P.HILInitialize_AOChannels, 2U,
         &q_aero2_half_quad_pd_DW.HILInitialize_AOMinimums[0],
         &q_aero2_half_quad_pd_DW.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_aero2_half_quad_pd_M, _rt_error_message);
        return;
      }
    }

    if ((q_aero2_half_quad_pd_P.HILInitialize_AOStart && !is_switching) ||
        (q_aero2_half_quad_pd_P.HILInitialize_AOEnter && is_switching)) {
      q_aero2_half_quad_pd_DW.HILInitialize_AOVoltages[0] =
        q_aero2_half_quad_pd_P.HILInitialize_AOInitial;
      q_aero2_half_quad_pd_DW.HILInitialize_AOVoltages[1] =
        q_aero2_half_quad_pd_P.HILInitialize_AOInitial;
      result = hil_write_analog(q_aero2_half_quad_pd_DW.HILInitialize_Card,
        q_aero2_half_quad_pd_P.HILInitialize_AOChannels, 2U,
        &q_aero2_half_quad_pd_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_aero2_half_quad_pd_M, _rt_error_message);
        return;
      }
    }

    if (q_aero2_half_quad_pd_P.HILInitialize_AOReset) {
      q_aero2_half_quad_pd_DW.HILInitialize_AOVoltages[0] =
        q_aero2_half_quad_pd_P.HILInitialize_AOWatchdog;
      q_aero2_half_quad_pd_DW.HILInitialize_AOVoltages[1] =
        q_aero2_half_quad_pd_P.HILInitialize_AOWatchdog;
      result = hil_watchdog_set_analog_expiration_state
        (q_aero2_half_quad_pd_DW.HILInitialize_Card,
         q_aero2_half_quad_pd_P.HILInitialize_AOChannels, 2U,
         &q_aero2_half_quad_pd_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_aero2_half_quad_pd_M, _rt_error_message);
        return;
      }
    }

    result = hil_set_digital_directions
      (q_aero2_half_quad_pd_DW.HILInitialize_Card, NULL, 0U,
       q_aero2_half_quad_pd_P.HILInitialize_DOChannels, 2U);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(q_aero2_half_quad_pd_M, _rt_error_message);
      return;
    }

    if ((q_aero2_half_quad_pd_P.HILInitialize_DOStart && !is_switching) ||
        (q_aero2_half_quad_pd_P.HILInitialize_DOEnter && is_switching)) {
      q_aero2_half_quad_pd_DW.HILInitialize_DOBits[0] =
        q_aero2_half_quad_pd_P.HILInitialize_DOInitial;
      q_aero2_half_quad_pd_DW.HILInitialize_DOBits[1] =
        q_aero2_half_quad_pd_P.HILInitialize_DOInitial;
      result = hil_write_digital(q_aero2_half_quad_pd_DW.HILInitialize_Card,
        q_aero2_half_quad_pd_P.HILInitialize_DOChannels, 2U, (t_boolean *)
        &q_aero2_half_quad_pd_DW.HILInitialize_DOBits[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_aero2_half_quad_pd_M, _rt_error_message);
        return;
      }
    }

    if (q_aero2_half_quad_pd_P.HILInitialize_DOReset) {
      q_aero2_half_quad_pd_DW.HILInitialize_DOStates[0] =
        q_aero2_half_quad_pd_P.HILInitialize_DOWatchdog;
      q_aero2_half_quad_pd_DW.HILInitialize_DOStates[1] =
        q_aero2_half_quad_pd_P.HILInitialize_DOWatchdog;
      result = hil_watchdog_set_digital_expiration_state
        (q_aero2_half_quad_pd_DW.HILInitialize_Card,
         q_aero2_half_quad_pd_P.HILInitialize_DOChannels, 2U, (const
          t_digital_state *) &q_aero2_half_quad_pd_DW.HILInitialize_DOStates[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_aero2_half_quad_pd_M, _rt_error_message);
        return;
      }
    }

    if ((q_aero2_half_quad_pd_P.HILInitialize_EIPStart && !is_switching) ||
        (q_aero2_half_quad_pd_P.HILInitialize_EIPEnter && is_switching)) {
      q_aero2_half_quad_pd_DW.HILInitialize_QuadratureModes[0] =
        q_aero2_half_quad_pd_P.HILInitialize_EIQuadrature;
      q_aero2_half_quad_pd_DW.HILInitialize_QuadratureModes[1] =
        q_aero2_half_quad_pd_P.HILInitialize_EIQuadrature;
      q_aero2_half_quad_pd_DW.HILInitialize_QuadratureModes[2] =
        q_aero2_half_quad_pd_P.HILInitialize_EIQuadrature;
      q_aero2_half_quad_pd_DW.HILInitialize_QuadratureModes[3] =
        q_aero2_half_quad_pd_P.HILInitialize_EIQuadrature;
      result = hil_set_encoder_quadrature_mode
        (q_aero2_half_quad_pd_DW.HILInitialize_Card,
         q_aero2_half_quad_pd_P.HILInitialize_EIChannels, 4U,
         (t_encoder_quadrature_mode *)
         &q_aero2_half_quad_pd_DW.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_aero2_half_quad_pd_M, _rt_error_message);
        return;
      }
    }

    if ((q_aero2_half_quad_pd_P.HILInitialize_EIStart && !is_switching) ||
        (q_aero2_half_quad_pd_P.HILInitialize_EIEnter && is_switching)) {
      q_aero2_half_quad_pd_DW.HILInitialize_InitialEICounts[0] =
        q_aero2_half_quad_pd_P.HILInitialize_EIInitial;
      q_aero2_half_quad_pd_DW.HILInitialize_InitialEICounts[1] =
        q_aero2_half_quad_pd_P.HILInitialize_EIInitial;
      q_aero2_half_quad_pd_DW.HILInitialize_InitialEICounts[2] =
        q_aero2_half_quad_pd_P.HILInitialize_EIInitial;
      q_aero2_half_quad_pd_DW.HILInitialize_InitialEICounts[3] =
        q_aero2_half_quad_pd_P.HILInitialize_EIInitial;
      result = hil_set_encoder_counts(q_aero2_half_quad_pd_DW.HILInitialize_Card,
        q_aero2_half_quad_pd_P.HILInitialize_EIChannels, 4U,
        &q_aero2_half_quad_pd_DW.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_aero2_half_quad_pd_M, _rt_error_message);
        return;
      }
    }

    if ((q_aero2_half_quad_pd_P.HILInitialize_OOStart && !is_switching) ||
        (q_aero2_half_quad_pd_P.HILInitialize_OOEnter && is_switching)) {
      result = hil_write_other(q_aero2_half_quad_pd_DW.HILInitialize_Card,
        q_aero2_half_quad_pd_P.HILInitialize_OOChannels, 3U,
        q_aero2_half_quad_pd_P.HILInitialize_OOInitial);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_aero2_half_quad_pd_M, _rt_error_message);
        return;
      }
    }

    if (q_aero2_half_quad_pd_P.HILInitialize_OOReset) {
      result = hil_watchdog_set_other_expiration_state
        (q_aero2_half_quad_pd_DW.HILInitialize_Card,
         q_aero2_half_quad_pd_P.HILInitialize_OOChannels, 3U,
         q_aero2_half_quad_pd_P.HILInitialize_OOWatchdog);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_aero2_half_quad_pd_M, _rt_error_message);
        return;
      }
    }
  }

  /* Start for S-Function (hil_read_encoder_timebase_block): '<Root>/HIL Read Encoder Timebase' */

  /* S-Function Block: q_aero2_half_quad_pd/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
  {
    t_error result;
    result = hil_task_create_encoder_reader
      (q_aero2_half_quad_pd_DW.HILInitialize_Card,
       q_aero2_half_quad_pd_P.HILReadEncoderTimebase_SamplesI,
       &q_aero2_half_quad_pd_P.HILReadEncoderTimebase_Channels, 1,
       &q_aero2_half_quad_pd_DW.HILReadEncoderTimebase_Task);
    if (result >= 0) {
      result = hil_task_set_buffer_overflow_mode
        (q_aero2_half_quad_pd_DW.HILReadEncoderTimebase_Task,
         (t_buffer_overflow_mode)
         (q_aero2_half_quad_pd_P.HILReadEncoderTimebase_Overflow - 1));
    }

    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(q_aero2_half_quad_pd_M, _rt_error_message);
    }
  }

  /* Start for S-Function (smooth_signal_generator_block): '<Root>/Smooth Signal Generator1' */

  /* S-Function Block: q_aero2_half_quad_pd/Smooth Signal Generator1 (smooth_signal_generator_block) */
  {
    real_T T = 1.0 / q_aero2_half_quad_pd_P.SmoothSignalGenerator1_Frequenc;
    q_aero2_half_quad_pd_DW.SmoothSignalGenerator1_RWORK.Amp =
      q_aero2_half_quad_pd_P.SmoothSignalGenerator1_Amplitud;
    q_aero2_half_quad_pd_DW.SmoothSignalGenerator1_RWORK.W = TWO_PI *
      q_aero2_half_quad_pd_P.SmoothSignalGenerator1_Frequenc;
    q_aero2_half_quad_pd_DW.SmoothSignalGenerator1_RWORK.T = fmod
      (q_aero2_half_quad_pd_P.SmoothSignalGenerator1_InitialP, TWO_PI) * T /
      TWO_PI;
    if (q_aero2_half_quad_pd_DW.SmoothSignalGenerator1_RWORK.T < 0) {
      q_aero2_half_quad_pd_DW.SmoothSignalGenerator1_RWORK.T += T;
    }

    if (q_aero2_half_quad_pd_DW.SmoothSignalGenerator1_RWORK.T < 0.5 * T) {
      q_aero2_half_quad_pd_DW.SmoothSignalGenerator1_RWORK.Y =
        q_aero2_half_quad_pd_P.SmoothSignalGenerator1_Amplitud;
    } else {
      q_aero2_half_quad_pd_DW.SmoothSignalGenerator1_RWORK.Y =
        -q_aero2_half_quad_pd_P.SmoothSignalGenerator1_Amplitud;
    }
  }

  /* InitializeConditions for Derivative: '<S1>/Derivative' */
  q_aero2_half_quad_pd_DW.TimeStampA = (rtInf);
  q_aero2_half_quad_pd_DW.TimeStampB = (rtInf);

  /* InitializeConditions for Derivative: '<S1>/Derivative1' */
  q_aero2_half_quad_pd_DW.TimeStampA_a = (rtInf);
  q_aero2_half_quad_pd_DW.TimeStampB_m = (rtInf);

  /* InitializeConditions for Integrator: '<S4>/Integrator2' */
  q_aero2_half_quad_pd_X.Integrator2_CSTATE =
    q_aero2_half_quad_pd_P.Integrator2_IC;

  /* InitializeConditions for Integrator: '<S1>/Integrator' */
  q_aero2_half_quad_pd_X.Integrator_CSTATE =
    q_aero2_half_quad_pd_P.Integrator_IC;

  /* InitializeConditions for Integrator: '<S5>/Integrator2' */
  q_aero2_half_quad_pd_X.Integrator2_CSTATE_h =
    q_aero2_half_quad_pd_P.Integrator2_IC_m;

  /* InitializeConditions for Integrator: '<S4>/Integrator1' incorporates:
   *  Integrator: '<S5>/Integrator1'
   */
  if (rtmIsFirstInitCond(q_aero2_half_quad_pd_M)) {
    q_aero2_half_quad_pd_X.Integrator1_CSTATE = 0.0;
    q_aero2_half_quad_pd_X.Integrator1_CSTATE_a = 0.0;
  }

  q_aero2_half_quad_pd_DW.Integrator1_DWORK1 = true;

  /* End of InitializeConditions for Integrator: '<S4>/Integrator1' */

  /* InitializeConditions for Integrator: '<S5>/Integrator1' */
  q_aero2_half_quad_pd_DW.Integrator1_DWORK1_h = true;

  /* set "at time zero" to false */
  if (rtmIsFirstInitCond(q_aero2_half_quad_pd_M)) {
    rtmSetFirstInitCond(q_aero2_half_quad_pd_M, 0);
  }
}

/* Model terminate function */
void q_aero2_half_quad_pd_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: q_aero2_half_quad_pd/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    t_uint32 num_final_digital_outputs = 0;
    t_uint32 num_final_other_outputs = 0;
    hil_task_stop_all(q_aero2_half_quad_pd_DW.HILInitialize_Card);
    hil_monitor_stop_all(q_aero2_half_quad_pd_DW.HILInitialize_Card);
    is_switching = false;
    if ((q_aero2_half_quad_pd_P.HILInitialize_AOTerminate && !is_switching) ||
        (q_aero2_half_quad_pd_P.HILInitialize_AOExit && is_switching)) {
      q_aero2_half_quad_pd_DW.HILInitialize_AOVoltages[0] =
        q_aero2_half_quad_pd_P.HILInitialize_AOFinal;
      q_aero2_half_quad_pd_DW.HILInitialize_AOVoltages[1] =
        q_aero2_half_quad_pd_P.HILInitialize_AOFinal;
      num_final_analog_outputs = 2U;
    } else {
      num_final_analog_outputs = 0;
    }

    if ((q_aero2_half_quad_pd_P.HILInitialize_DOTerminate && !is_switching) ||
        (q_aero2_half_quad_pd_P.HILInitialize_DOExit && is_switching)) {
      q_aero2_half_quad_pd_DW.HILInitialize_DOBits[0] =
        q_aero2_half_quad_pd_P.HILInitialize_DOFinal;
      q_aero2_half_quad_pd_DW.HILInitialize_DOBits[1] =
        q_aero2_half_quad_pd_P.HILInitialize_DOFinal;
      num_final_digital_outputs = 2U;
    } else {
      num_final_digital_outputs = 0;
    }

    if ((q_aero2_half_quad_pd_P.HILInitialize_OOTerminate && !is_switching) ||
        (q_aero2_half_quad_pd_P.HILInitialize_OOExit && is_switching)) {
      num_final_other_outputs = 3U;
    } else {
      num_final_other_outputs = 0;
    }

    if (0
        || num_final_analog_outputs > 0
        || num_final_digital_outputs > 0
        || num_final_other_outputs > 0
        ) {
      /* Attempt to write the final outputs atomically (due to firmware issue in old Q2-USB). Otherwise write channels individually */
      result = hil_write(q_aero2_half_quad_pd_DW.HILInitialize_Card
                         , q_aero2_half_quad_pd_P.HILInitialize_AOChannels,
                         num_final_analog_outputs
                         , NULL, 0
                         , q_aero2_half_quad_pd_P.HILInitialize_DOChannels,
                         num_final_digital_outputs
                         , q_aero2_half_quad_pd_P.HILInitialize_OOChannels,
                         num_final_other_outputs
                         , &q_aero2_half_quad_pd_DW.HILInitialize_AOVoltages[0]
                         , NULL
                         , (t_boolean *)
                         &q_aero2_half_quad_pd_DW.HILInitialize_DOBits[0]
                         , q_aero2_half_quad_pd_P.HILInitialize_OOFinal
                         );
      if (result == -QERR_HIL_WRITE_NOT_SUPPORTED) {
        t_error local_result;
        result = 0;

        /* The hil_write operation is not supported by this card. Write final outputs for each channel type */
        if (num_final_analog_outputs > 0) {
          local_result = hil_write_analog
            (q_aero2_half_quad_pd_DW.HILInitialize_Card,
             q_aero2_half_quad_pd_P.HILInitialize_AOChannels,
             num_final_analog_outputs,
             &q_aero2_half_quad_pd_DW.HILInitialize_AOVoltages[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_digital_outputs > 0) {
          local_result = hil_write_digital
            (q_aero2_half_quad_pd_DW.HILInitialize_Card,
             q_aero2_half_quad_pd_P.HILInitialize_DOChannels,
             num_final_digital_outputs, (t_boolean *)
             &q_aero2_half_quad_pd_DW.HILInitialize_DOBits[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_other_outputs > 0) {
          local_result = hil_write_other
            (q_aero2_half_quad_pd_DW.HILInitialize_Card,
             q_aero2_half_quad_pd_P.HILInitialize_OOChannels,
             num_final_other_outputs,
             q_aero2_half_quad_pd_P.HILInitialize_OOFinal);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(q_aero2_half_quad_pd_M, _rt_error_message);
        }
      }
    }

    hil_task_delete_all(q_aero2_half_quad_pd_DW.HILInitialize_Card);
    hil_monitor_delete_all(q_aero2_half_quad_pd_DW.HILInitialize_Card);
    hil_close(q_aero2_half_quad_pd_DW.HILInitialize_Card);
    q_aero2_half_quad_pd_DW.HILInitialize_Card = NULL;
  }
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/

/* Solver interface called by GRT_Main */
#ifndef USE_GENERATED_SOLVER

void rt_ODECreateIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEDestroyIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEUpdateContinuousStates(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

#endif

void MdlOutputs(int_T tid)
{
  q_aero2_half_quad_pd_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  q_aero2_half_quad_pd_update();
  UNUSED_PARAMETER(tid);
}

void MdlInitializeSizes(void)
{
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
}

void MdlStart(void)
{
  q_aero2_half_quad_pd_initialize();
}

void MdlTerminate(void)
{
  q_aero2_half_quad_pd_terminate();
}

/* Registration function */
RT_MODEL_q_aero2_half_quad_pd_T *q_aero2_half_quad_pd(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)q_aero2_half_quad_pd_M, 0,
                sizeof(RT_MODEL_q_aero2_half_quad_pd_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&q_aero2_half_quad_pd_M->solverInfo,
                          &q_aero2_half_quad_pd_M->Timing.simTimeStep);
    rtsiSetTPtr(&q_aero2_half_quad_pd_M->solverInfo, &rtmGetTPtr
                (q_aero2_half_quad_pd_M));
    rtsiSetStepSizePtr(&q_aero2_half_quad_pd_M->solverInfo,
                       &q_aero2_half_quad_pd_M->Timing.stepSize0);
    rtsiSetdXPtr(&q_aero2_half_quad_pd_M->solverInfo,
                 &q_aero2_half_quad_pd_M->derivs);
    rtsiSetContStatesPtr(&q_aero2_half_quad_pd_M->solverInfo, (real_T **)
                         &q_aero2_half_quad_pd_M->contStates);
    rtsiSetNumContStatesPtr(&q_aero2_half_quad_pd_M->solverInfo,
      &q_aero2_half_quad_pd_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&q_aero2_half_quad_pd_M->solverInfo,
      &q_aero2_half_quad_pd_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&q_aero2_half_quad_pd_M->solverInfo,
      &q_aero2_half_quad_pd_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&q_aero2_half_quad_pd_M->solverInfo,
      &q_aero2_half_quad_pd_M->periodicContStateRanges);
    rtsiSetContStateDisabledPtr(&q_aero2_half_quad_pd_M->solverInfo, (boolean_T**)
      &q_aero2_half_quad_pd_M->contStateDisabled);
    rtsiSetErrorStatusPtr(&q_aero2_half_quad_pd_M->solverInfo,
                          (&rtmGetErrorStatus(q_aero2_half_quad_pd_M)));
    rtsiSetRTModelPtr(&q_aero2_half_quad_pd_M->solverInfo,
                      q_aero2_half_quad_pd_M);
  }

  rtsiSetSimTimeStep(&q_aero2_half_quad_pd_M->solverInfo, MAJOR_TIME_STEP);
  rtsiSetIsMinorTimeStepWithModeChange(&q_aero2_half_quad_pd_M->solverInfo,
    false);
  rtsiSetIsContModeFrozen(&q_aero2_half_quad_pd_M->solverInfo, false);
  q_aero2_half_quad_pd_M->intgData.f[0] = q_aero2_half_quad_pd_M->odeF[0];
  q_aero2_half_quad_pd_M->contStates = ((real_T *) &q_aero2_half_quad_pd_X);
  q_aero2_half_quad_pd_M->contStateDisabled = ((boolean_T *)
    &q_aero2_half_quad_pd_XDis);
  q_aero2_half_quad_pd_M->Timing.tStart = (0.0);
  rtsiSetSolverData(&q_aero2_half_quad_pd_M->solverInfo, (void *)
                    &q_aero2_half_quad_pd_M->intgData);
  rtsiSetSolverName(&q_aero2_half_quad_pd_M->solverInfo,"ode1");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = q_aero2_half_quad_pd_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    q_aero2_half_quad_pd_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    q_aero2_half_quad_pd_M->Timing.sampleTimes =
      (&q_aero2_half_quad_pd_M->Timing.sampleTimesArray[0]);
    q_aero2_half_quad_pd_M->Timing.offsetTimes =
      (&q_aero2_half_quad_pd_M->Timing.offsetTimesArray[0]);

    /* task periods */
    q_aero2_half_quad_pd_M->Timing.sampleTimes[0] = (0.0);
    q_aero2_half_quad_pd_M->Timing.sampleTimes[1] = (0.002);

    /* task offsets */
    q_aero2_half_quad_pd_M->Timing.offsetTimes[0] = (0.0);
    q_aero2_half_quad_pd_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(q_aero2_half_quad_pd_M, &q_aero2_half_quad_pd_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = q_aero2_half_quad_pd_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    q_aero2_half_quad_pd_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(q_aero2_half_quad_pd_M, 30.0);
  q_aero2_half_quad_pd_M->Timing.stepSize0 = 0.002;
  q_aero2_half_quad_pd_M->Timing.stepSize1 = 0.002;
  rtmSetFirstInitCond(q_aero2_half_quad_pd_M, 1);

  /* External mode info */
  q_aero2_half_quad_pd_M->Sizes.checksums[0] = (3408898864U);
  q_aero2_half_quad_pd_M->Sizes.checksums[1] = (981065413U);
  q_aero2_half_quad_pd_M->Sizes.checksums[2] = (171580317U);
  q_aero2_half_quad_pd_M->Sizes.checksums[3] = (245212639U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[3];
    q_aero2_half_quad_pd_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    systemRan[1] = &rtAlwaysEnabled;
    systemRan[2] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(q_aero2_half_quad_pd_M->extModeInfo,
      &q_aero2_half_quad_pd_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(q_aero2_half_quad_pd_M->extModeInfo,
                        q_aero2_half_quad_pd_M->Sizes.checksums);
    rteiSetTPtr(q_aero2_half_quad_pd_M->extModeInfo, rtmGetTPtr
                (q_aero2_half_quad_pd_M));
  }

  q_aero2_half_quad_pd_M->solverInfoPtr = (&q_aero2_half_quad_pd_M->solverInfo);
  q_aero2_half_quad_pd_M->Timing.stepSize = (0.002);
  rtsiSetFixedStepSize(&q_aero2_half_quad_pd_M->solverInfo, 0.002);
  rtsiSetSolverMode(&q_aero2_half_quad_pd_M->solverInfo,
                    SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  q_aero2_half_quad_pd_M->blockIO = ((void *) &q_aero2_half_quad_pd_B);
  (void) memset(((void *) &q_aero2_half_quad_pd_B), 0,
                sizeof(B_q_aero2_half_quad_pd_T));

  /* parameters */
  q_aero2_half_quad_pd_M->defaultParam = ((real_T *)&q_aero2_half_quad_pd_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &q_aero2_half_quad_pd_X;
    q_aero2_half_quad_pd_M->contStates = (x);
    (void) memset((void *)&q_aero2_half_quad_pd_X, 0,
                  sizeof(X_q_aero2_half_quad_pd_T));
  }

  /* disabled states */
  {
    boolean_T *xdis = (boolean_T *) &q_aero2_half_quad_pd_XDis;
    q_aero2_half_quad_pd_M->contStateDisabled = (xdis);
    (void) memset((void *)&q_aero2_half_quad_pd_XDis, 0,
                  sizeof(XDis_q_aero2_half_quad_pd_T));
  }

  /* states (dwork) */
  q_aero2_half_quad_pd_M->dwork = ((void *) &q_aero2_half_quad_pd_DW);
  (void) memset((void *)&q_aero2_half_quad_pd_DW, 0,
                sizeof(DW_q_aero2_half_quad_pd_T));

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    q_aero2_half_quad_pd_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 22;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Initialize Sizes */
  q_aero2_half_quad_pd_M->Sizes.numContStates = (5);/* Number of continuous states */
  q_aero2_half_quad_pd_M->Sizes.numPeriodicContStates = (0);
                                      /* Number of periodic continuous states */
  q_aero2_half_quad_pd_M->Sizes.numY = (0);/* Number of model outputs */
  q_aero2_half_quad_pd_M->Sizes.numU = (0);/* Number of model inputs */
  q_aero2_half_quad_pd_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  q_aero2_half_quad_pd_M->Sizes.numSampTimes = (2);/* Number of sample times */
  q_aero2_half_quad_pd_M->Sizes.numBlocks = (52);/* Number of blocks */
  q_aero2_half_quad_pd_M->Sizes.numBlockIO = (14);/* Number of block outputs */
  q_aero2_half_quad_pd_M->Sizes.numBlockPrms = (142);/* Sum of parameter "widths" */
  return q_aero2_half_quad_pd_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
