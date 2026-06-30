/*
 * Simulink.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "Simulink".
 *
 * Model version              : 1.1
 * Simulink Coder version : 24.2 (R2024b) 21-Jun-2024
 * C source code generated on : Tue Jun 30 13:40:36 2026
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Simulink.h"
#include "rtwtypes.h"
#include "Simulink_private.h"
#include <string.h>
#include "Simulink_dt.h"

/* Block signals (default storage) */
B_Simulink_T Simulink_B;

/* Continuous states */
X_Simulink_T Simulink_X;

/* Disabled State Vector */
XDis_Simulink_T Simulink_XDis;

/* Block states (default storage) */
DW_Simulink_T Simulink_DW;

/* Real-time model */
static RT_MODEL_Simulink_T Simulink_M_;
RT_MODEL_Simulink_T *const Simulink_M = &Simulink_M_;

/*
 * This function updates continuous states using the ODE3 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  /* Solver Matrices */
  static const real_T rt_ODE3_A[3] = {
    1.0/2.0, 3.0/4.0, 1.0
  };

  static const real_T rt_ODE3_B[3][3] = {
    { 1.0/2.0, 0.0, 0.0 },

    { 0.0, 3.0/4.0, 0.0 },

    { 2.0/9.0, 1.0/3.0, 4.0/9.0 }
  };

  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE3_IntgData *id = (ODE3_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T hB[3];
  int_T i;
  int_T nXc = 2;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  Simulink_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  Simulink_output();
  Simulink_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  Simulink_output();
  Simulink_derivatives();

  /* tnew = t + hA(3);
     ynew = y + f*hB(:,3); */
  for (i = 0; i <= 2; i++) {
    hB[i] = h * rt_ODE3_B[2][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, tnew);
  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model output function */
void Simulink_output(void)
{
  real_T lastTime;
  real_T rtb_HILRead;
  real_T rtb_HILReadEncoderTimebase;
  real_T *lastU;
  boolean_T tmp;
  if (rtmIsMajorTimeStep(Simulink_M)) {
    /* set solver stop time */
    if (!(Simulink_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&Simulink_M->solverInfo,
                            ((Simulink_M->Timing.clockTickH0 + 1) *
        Simulink_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&Simulink_M->solverInfo,
                            ((Simulink_M->Timing.clockTick0 + 1) *
        Simulink_M->Timing.stepSize0 + Simulink_M->Timing.clockTickH0 *
        Simulink_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(Simulink_M)) {
    Simulink_M->Timing.t[0] = rtsiGetT(&Simulink_M->solverInfo);
  }

  tmp = rtmIsMajorTimeStep(Simulink_M);
  if (tmp) {
    /* S-Function (hil_read_encoder_timebase_block): '<Root>/HIL Read Encoder Timebase' */

    /* S-Function Block: Simulink/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
    {
      t_error result;
      result = hil_task_read_encoder(Simulink_DW.HILReadEncoderTimebase_Task, 1,
        &Simulink_DW.HILReadEncoderTimebase_Buffer);
      if (result < 0) {
        rtb_HILReadEncoderTimebase = 0;
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Simulink_M, _rt_error_message);
      } else {
        rtb_HILReadEncoderTimebase = Simulink_DW.HILReadEncoderTimebase_Buffer;
      }
    }

    /* Gain: '<Root>/Gain' incorporates:
     *  Constant: '<Root>/Constant'
     */
    rtb_HILRead = Simulink_P.Gain_Gain * Simulink_P.Constant_Value;

    /* S-Function (hil_write_analog_block): '<Root>/HIL Write Analog' */

    /* S-Function Block: Simulink/HIL Write Analog (hil_write_analog_block) */
    {
      t_error result;
      Simulink_DW.HILWriteAnalog_Buffer[0] = rtb_HILRead;
      Simulink_DW.HILWriteAnalog_Buffer[1] = 0.0;
      result = hil_write_analog(Simulink_DW.HILInitialize_Card,
        Simulink_P.HILWriteAnalog_channels, 2,
        &Simulink_DW.HILWriteAnalog_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Simulink_M, _rt_error_message);
      }
    }

    /* Gain: '<Root>/Gain1' */
    Simulink_B.Gain1 = Simulink_P.Gain1_Gain * rtb_HILReadEncoderTimebase;
  }

  /* Derivative: '<Root>/Derivative' incorporates:
   *  Derivative: '<Root>/Derivative1'
   */
  rtb_HILReadEncoderTimebase = Simulink_M->Timing.t[0];
  if ((Simulink_DW.TimeStampA >= rtb_HILReadEncoderTimebase) &&
      (Simulink_DW.TimeStampB >= rtb_HILReadEncoderTimebase)) {
    /* Derivative: '<Root>/Derivative' */
    Simulink_B.Derivative = 0.0;
  } else {
    lastTime = Simulink_DW.TimeStampA;
    lastU = &Simulink_DW.LastUAtTimeA;
    if (Simulink_DW.TimeStampA < Simulink_DW.TimeStampB) {
      if (Simulink_DW.TimeStampB < rtb_HILReadEncoderTimebase) {
        lastTime = Simulink_DW.TimeStampB;
        lastU = &Simulink_DW.LastUAtTimeB;
      }
    } else if (Simulink_DW.TimeStampA >= rtb_HILReadEncoderTimebase) {
      lastTime = Simulink_DW.TimeStampB;
      lastU = &Simulink_DW.LastUAtTimeB;
    }

    /* Derivative: '<Root>/Derivative' */
    Simulink_B.Derivative = (Simulink_B.Gain1 - *lastU) /
      (rtb_HILReadEncoderTimebase - lastTime);
  }

  /* End of Derivative: '<Root>/Derivative' */

  /* TransferFcn: '<Root>/Deriv + LPF' */
  Simulink_B.DerivLPF = 0.0;
  Simulink_B.DerivLPF += Simulink_P.DerivLPF_C * Simulink_X.DerivLPF_CSTATE;
  Simulink_B.DerivLPF += Simulink_P.DerivLPF_D * Simulink_B.Gain1;

  /* TransferFcn: '<Root>/LPF' */
  Simulink_B.LPF = 0.0;
  Simulink_B.LPF += Simulink_P.LPF_C * Simulink_X.LPF_CSTATE;
  if (tmp) {
    /* S-Function (hil_read_block): '<Root>/HIL Read' */

    /* S-Function Block: Simulink/HIL Read (hil_read_block) */
    {
      t_error result = hil_read(Simulink_DW.HILInitialize_Card,
        NULL, 0U,
        NULL, 0U,
        NULL, 0U,
        &Simulink_P.HILRead_other_channels, 1U,
        NULL,
        NULL,
        NULL,
        &Simulink_DW.HILRead_OtherBuffer
        );
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Simulink_M, _rt_error_message);
      } else {
        rtb_HILRead = Simulink_DW.HILRead_OtherBuffer;
      }
    }

    /* Gain: '<Root>/Gain3' */
    Simulink_B.Realspeed = Simulink_P.Gain3_Gain * rtb_HILRead;

    /* Gain: '<Root>/Gain2' */
    Simulink_B.Gain2 = Simulink_P.Gain2_Gain * Simulink_B.Gain1;
  }

  /* Derivative: '<Root>/Derivative1' */
  if ((Simulink_DW.TimeStampA_o >= rtb_HILReadEncoderTimebase) &&
      (Simulink_DW.TimeStampB_g >= rtb_HILReadEncoderTimebase)) {
    /* Derivative: '<Root>/Derivative1' */
    Simulink_B.Derivative1 = 0.0;
  } else {
    lastTime = Simulink_DW.TimeStampA_o;
    lastU = &Simulink_DW.LastUAtTimeA_k;
    if (Simulink_DW.TimeStampA_o < Simulink_DW.TimeStampB_g) {
      if (Simulink_DW.TimeStampB_g < rtb_HILReadEncoderTimebase) {
        lastTime = Simulink_DW.TimeStampB_g;
        lastU = &Simulink_DW.LastUAtTimeB_o;
      }
    } else if (Simulink_DW.TimeStampA_o >= rtb_HILReadEncoderTimebase) {
      lastTime = Simulink_DW.TimeStampB_g;
      lastU = &Simulink_DW.LastUAtTimeB_o;
    }

    /* Derivative: '<Root>/Derivative1' */
    Simulink_B.Derivative1 = (Simulink_B.Gain1 - *lastU) /
      (rtb_HILReadEncoderTimebase - lastTime);
  }
}

/* Model update function */
void Simulink_update(void)
{
  real_T *lastU;

  /* Update for Derivative: '<Root>/Derivative' */
  if (Simulink_DW.TimeStampA == (rtInf)) {
    Simulink_DW.TimeStampA = Simulink_M->Timing.t[0];
    lastU = &Simulink_DW.LastUAtTimeA;
  } else if (Simulink_DW.TimeStampB == (rtInf)) {
    Simulink_DW.TimeStampB = Simulink_M->Timing.t[0];
    lastU = &Simulink_DW.LastUAtTimeB;
  } else if (Simulink_DW.TimeStampA < Simulink_DW.TimeStampB) {
    Simulink_DW.TimeStampA = Simulink_M->Timing.t[0];
    lastU = &Simulink_DW.LastUAtTimeA;
  } else {
    Simulink_DW.TimeStampB = Simulink_M->Timing.t[0];
    lastU = &Simulink_DW.LastUAtTimeB;
  }

  *lastU = Simulink_B.Gain1;

  /* End of Update for Derivative: '<Root>/Derivative' */

  /* Update for Derivative: '<Root>/Derivative1' */
  if (Simulink_DW.TimeStampA_o == (rtInf)) {
    Simulink_DW.TimeStampA_o = Simulink_M->Timing.t[0];
    lastU = &Simulink_DW.LastUAtTimeA_k;
  } else if (Simulink_DW.TimeStampB_g == (rtInf)) {
    Simulink_DW.TimeStampB_g = Simulink_M->Timing.t[0];
    lastU = &Simulink_DW.LastUAtTimeB_o;
  } else if (Simulink_DW.TimeStampA_o < Simulink_DW.TimeStampB_g) {
    Simulink_DW.TimeStampA_o = Simulink_M->Timing.t[0];
    lastU = &Simulink_DW.LastUAtTimeA_k;
  } else {
    Simulink_DW.TimeStampB_g = Simulink_M->Timing.t[0];
    lastU = &Simulink_DW.LastUAtTimeB_o;
  }

  *lastU = Simulink_B.Gain1;

  /* End of Update for Derivative: '<Root>/Derivative1' */
  if (rtmIsMajorTimeStep(Simulink_M)) {
    rt_ertODEUpdateContinuousStates(&Simulink_M->solverInfo);
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
  if (!(++Simulink_M->Timing.clockTick0)) {
    ++Simulink_M->Timing.clockTickH0;
  }

  Simulink_M->Timing.t[0] = rtsiGetSolverStopTime(&Simulink_M->solverInfo);

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
    if (!(++Simulink_M->Timing.clockTick1)) {
      ++Simulink_M->Timing.clockTickH1;
    }

    Simulink_M->Timing.t[1] = Simulink_M->Timing.clockTick1 *
      Simulink_M->Timing.stepSize1 + Simulink_M->Timing.clockTickH1 *
      Simulink_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Derivatives for root system: '<Root>' */
void Simulink_derivatives(void)
{
  XDot_Simulink_T *_rtXdot;
  _rtXdot = ((XDot_Simulink_T *) Simulink_M->derivs);

  /* Derivatives for TransferFcn: '<Root>/Deriv + LPF' */
  _rtXdot->DerivLPF_CSTATE = Simulink_P.DerivLPF_A * Simulink_X.DerivLPF_CSTATE;
  _rtXdot->DerivLPF_CSTATE += Simulink_B.Gain1;

  /* Derivatives for TransferFcn: '<Root>/LPF' */
  _rtXdot->LPF_CSTATE = Simulink_P.LPF_A * Simulink_X.LPF_CSTATE;
  _rtXdot->LPF_CSTATE += Simulink_B.Derivative1;
}

/* Model initialize function */
void Simulink_initialize(void)
{
  /* Start for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: Simulink/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("quanser_aero2_usb", "0@tcpip://localhost:18950",
                      &Simulink_DW.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(Simulink_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_set_card_specific_options(Simulink_DW.HILInitialize_Card, " ",
      2);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(Simulink_M, _rt_error_message);
      return;
    }

    result = hil_watchdog_clear(Simulink_DW.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(Simulink_M, _rt_error_message);
      return;
    }

    if ((Simulink_P.HILInitialize_AIPStart && !is_switching) ||
        (Simulink_P.HILInitialize_AIPEnter && is_switching)) {
      Simulink_DW.HILInitialize_AIMinimums[0] = (Simulink_P.HILInitialize_AILow);
      Simulink_DW.HILInitialize_AIMinimums[1] = (Simulink_P.HILInitialize_AILow);
      Simulink_DW.HILInitialize_AIMaximums[0] = Simulink_P.HILInitialize_AIHigh;
      Simulink_DW.HILInitialize_AIMaximums[1] = Simulink_P.HILInitialize_AIHigh;
      result = hil_set_analog_input_ranges(Simulink_DW.HILInitialize_Card,
        Simulink_P.HILInitialize_AIChannels, 2U,
        &Simulink_DW.HILInitialize_AIMinimums[0],
        &Simulink_DW.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Simulink_M, _rt_error_message);
        return;
      }
    }

    if ((Simulink_P.HILInitialize_AOPStart && !is_switching) ||
        (Simulink_P.HILInitialize_AOPEnter && is_switching)) {
      Simulink_DW.HILInitialize_AOMinimums[0] = (Simulink_P.HILInitialize_AOLow);
      Simulink_DW.HILInitialize_AOMinimums[1] = (Simulink_P.HILInitialize_AOLow);
      Simulink_DW.HILInitialize_AOMaximums[0] = Simulink_P.HILInitialize_AOHigh;
      Simulink_DW.HILInitialize_AOMaximums[1] = Simulink_P.HILInitialize_AOHigh;
      result = hil_set_analog_output_ranges(Simulink_DW.HILInitialize_Card,
        Simulink_P.HILInitialize_AOChannels, 2U,
        &Simulink_DW.HILInitialize_AOMinimums[0],
        &Simulink_DW.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Simulink_M, _rt_error_message);
        return;
      }
    }

    if ((Simulink_P.HILInitialize_AOStart && !is_switching) ||
        (Simulink_P.HILInitialize_AOEnter && is_switching)) {
      Simulink_DW.HILInitialize_AOVoltages[0] =
        Simulink_P.HILInitialize_AOInitial;
      Simulink_DW.HILInitialize_AOVoltages[1] =
        Simulink_P.HILInitialize_AOInitial;
      result = hil_write_analog(Simulink_DW.HILInitialize_Card,
        Simulink_P.HILInitialize_AOChannels, 2U,
        &Simulink_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Simulink_M, _rt_error_message);
        return;
      }
    }

    if (Simulink_P.HILInitialize_AOReset) {
      Simulink_DW.HILInitialize_AOVoltages[0] =
        Simulink_P.HILInitialize_AOWatchdog;
      Simulink_DW.HILInitialize_AOVoltages[1] =
        Simulink_P.HILInitialize_AOWatchdog;
      result = hil_watchdog_set_analog_expiration_state
        (Simulink_DW.HILInitialize_Card, Simulink_P.HILInitialize_AOChannels, 2U,
         &Simulink_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Simulink_M, _rt_error_message);
        return;
      }
    }

    result = hil_set_digital_directions(Simulink_DW.HILInitialize_Card, NULL, 0U,
      Simulink_P.HILInitialize_DOChannels, 2U);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(Simulink_M, _rt_error_message);
      return;
    }

    if ((Simulink_P.HILInitialize_DOStart && !is_switching) ||
        (Simulink_P.HILInitialize_DOEnter && is_switching)) {
      Simulink_DW.HILInitialize_DOBits[0] = Simulink_P.HILInitialize_DOInitial;
      Simulink_DW.HILInitialize_DOBits[1] = Simulink_P.HILInitialize_DOInitial;
      result = hil_write_digital(Simulink_DW.HILInitialize_Card,
        Simulink_P.HILInitialize_DOChannels, 2U, (t_boolean *)
        &Simulink_DW.HILInitialize_DOBits[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Simulink_M, _rt_error_message);
        return;
      }
    }

    if (Simulink_P.HILInitialize_DOReset) {
      Simulink_DW.HILInitialize_DOStates[0] =
        Simulink_P.HILInitialize_DOWatchdog;
      Simulink_DW.HILInitialize_DOStates[1] =
        Simulink_P.HILInitialize_DOWatchdog;
      result = hil_watchdog_set_digital_expiration_state
        (Simulink_DW.HILInitialize_Card, Simulink_P.HILInitialize_DOChannels, 2U,
         (const t_digital_state *) &Simulink_DW.HILInitialize_DOStates[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Simulink_M, _rt_error_message);
        return;
      }
    }

    if ((Simulink_P.HILInitialize_EIPStart && !is_switching) ||
        (Simulink_P.HILInitialize_EIPEnter && is_switching)) {
      Simulink_DW.HILInitialize_QuadratureModes[0] =
        Simulink_P.HILInitialize_EIQuadrature;
      Simulink_DW.HILInitialize_QuadratureModes[1] =
        Simulink_P.HILInitialize_EIQuadrature;
      Simulink_DW.HILInitialize_QuadratureModes[2] =
        Simulink_P.HILInitialize_EIQuadrature;
      Simulink_DW.HILInitialize_QuadratureModes[3] =
        Simulink_P.HILInitialize_EIQuadrature;
      result = hil_set_encoder_quadrature_mode(Simulink_DW.HILInitialize_Card,
        Simulink_P.HILInitialize_EIChannels, 4U, (t_encoder_quadrature_mode *)
        &Simulink_DW.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Simulink_M, _rt_error_message);
        return;
      }
    }

    if ((Simulink_P.HILInitialize_EIStart && !is_switching) ||
        (Simulink_P.HILInitialize_EIEnter && is_switching)) {
      Simulink_DW.HILInitialize_InitialEICounts[0] =
        Simulink_P.HILInitialize_EIInitial;
      Simulink_DW.HILInitialize_InitialEICounts[1] =
        Simulink_P.HILInitialize_EIInitial;
      Simulink_DW.HILInitialize_InitialEICounts[2] =
        Simulink_P.HILInitialize_EIInitial;
      Simulink_DW.HILInitialize_InitialEICounts[3] =
        Simulink_P.HILInitialize_EIInitial;
      result = hil_set_encoder_counts(Simulink_DW.HILInitialize_Card,
        Simulink_P.HILInitialize_EIChannels, 4U,
        &Simulink_DW.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Simulink_M, _rt_error_message);
        return;
      }
    }

    if ((Simulink_P.HILInitialize_OOStart && !is_switching) ||
        (Simulink_P.HILInitialize_OOEnter && is_switching)) {
      result = hil_write_other(Simulink_DW.HILInitialize_Card,
        Simulink_P.HILInitialize_OOChannels, 3U,
        Simulink_P.HILInitialize_OOInitial);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Simulink_M, _rt_error_message);
        return;
      }
    }

    if (Simulink_P.HILInitialize_OOReset) {
      result = hil_watchdog_set_other_expiration_state
        (Simulink_DW.HILInitialize_Card, Simulink_P.HILInitialize_OOChannels, 3U,
         Simulink_P.HILInitialize_OOWatchdog);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(Simulink_M, _rt_error_message);
        return;
      }
    }
  }

  /* Start for S-Function (hil_read_encoder_timebase_block): '<Root>/HIL Read Encoder Timebase' */

  /* S-Function Block: Simulink/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
  {
    t_error result;
    result = hil_task_create_encoder_reader(Simulink_DW.HILInitialize_Card,
      Simulink_P.HILReadEncoderTimebase_SamplesI,
      &Simulink_P.HILReadEncoderTimebase_Channels, 1,
      &Simulink_DW.HILReadEncoderTimebase_Task);
    if (result >= 0) {
      result = hil_task_set_buffer_overflow_mode
        (Simulink_DW.HILReadEncoderTimebase_Task, (t_buffer_overflow_mode)
         (Simulink_P.HILReadEncoderTimebase_Overflow - 1));
    }

    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(Simulink_M, _rt_error_message);
    }
  }

  /* InitializeConditions for Derivative: '<Root>/Derivative' */
  Simulink_DW.TimeStampA = (rtInf);
  Simulink_DW.TimeStampB = (rtInf);

  /* InitializeConditions for TransferFcn: '<Root>/Deriv + LPF' */
  Simulink_X.DerivLPF_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<Root>/LPF' */
  Simulink_X.LPF_CSTATE = 0.0;

  /* InitializeConditions for Derivative: '<Root>/Derivative1' */
  Simulink_DW.TimeStampA_o = (rtInf);
  Simulink_DW.TimeStampB_g = (rtInf);
}

/* Model terminate function */
void Simulink_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: Simulink/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    t_uint32 num_final_digital_outputs = 0;
    t_uint32 num_final_other_outputs = 0;
    hil_task_stop_all(Simulink_DW.HILInitialize_Card);
    hil_monitor_stop_all(Simulink_DW.HILInitialize_Card);
    is_switching = false;
    if ((Simulink_P.HILInitialize_AOTerminate && !is_switching) ||
        (Simulink_P.HILInitialize_AOExit && is_switching)) {
      Simulink_DW.HILInitialize_AOVoltages[0] = Simulink_P.HILInitialize_AOFinal;
      Simulink_DW.HILInitialize_AOVoltages[1] = Simulink_P.HILInitialize_AOFinal;
      num_final_analog_outputs = 2U;
    } else {
      num_final_analog_outputs = 0;
    }

    if ((Simulink_P.HILInitialize_DOTerminate && !is_switching) ||
        (Simulink_P.HILInitialize_DOExit && is_switching)) {
      Simulink_DW.HILInitialize_DOBits[0] = Simulink_P.HILInitialize_DOFinal;
      Simulink_DW.HILInitialize_DOBits[1] = Simulink_P.HILInitialize_DOFinal;
      num_final_digital_outputs = 2U;
    } else {
      num_final_digital_outputs = 0;
    }

    if ((Simulink_P.HILInitialize_OOTerminate && !is_switching) ||
        (Simulink_P.HILInitialize_OOExit && is_switching)) {
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
      result = hil_write(Simulink_DW.HILInitialize_Card
                         , Simulink_P.HILInitialize_AOChannels,
                         num_final_analog_outputs
                         , NULL, 0
                         , Simulink_P.HILInitialize_DOChannels,
                         num_final_digital_outputs
                         , Simulink_P.HILInitialize_OOChannels,
                         num_final_other_outputs
                         , &Simulink_DW.HILInitialize_AOVoltages[0]
                         , NULL
                         , (t_boolean *) &Simulink_DW.HILInitialize_DOBits[0]
                         , Simulink_P.HILInitialize_OOFinal
                         );
      if (result == -QERR_HIL_WRITE_NOT_SUPPORTED) {
        t_error local_result;
        result = 0;

        /* The hil_write operation is not supported by this card. Write final outputs for each channel type */
        if (num_final_analog_outputs > 0) {
          local_result = hil_write_analog(Simulink_DW.HILInitialize_Card,
            Simulink_P.HILInitialize_AOChannels, num_final_analog_outputs,
            &Simulink_DW.HILInitialize_AOVoltages[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_digital_outputs > 0) {
          local_result = hil_write_digital(Simulink_DW.HILInitialize_Card,
            Simulink_P.HILInitialize_DOChannels, num_final_digital_outputs,
            (t_boolean *) &Simulink_DW.HILInitialize_DOBits[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_other_outputs > 0) {
          local_result = hil_write_other(Simulink_DW.HILInitialize_Card,
            Simulink_P.HILInitialize_OOChannels, num_final_other_outputs,
            Simulink_P.HILInitialize_OOFinal);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(Simulink_M, _rt_error_message);
        }
      }
    }

    hil_task_delete_all(Simulink_DW.HILInitialize_Card);
    hil_monitor_delete_all(Simulink_DW.HILInitialize_Card);
    hil_close(Simulink_DW.HILInitialize_Card);
    Simulink_DW.HILInitialize_Card = NULL;
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
  Simulink_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  Simulink_update();
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
  Simulink_initialize();
}

void MdlTerminate(void)
{
  Simulink_terminate();
}

/* Registration function */
RT_MODEL_Simulink_T *Simulink(void)
{
  /* Registration code */

  /* initialize real-time model */
  (void) memset((void *)Simulink_M, 0,
                sizeof(RT_MODEL_Simulink_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&Simulink_M->solverInfo,
                          &Simulink_M->Timing.simTimeStep);
    rtsiSetTPtr(&Simulink_M->solverInfo, &rtmGetTPtr(Simulink_M));
    rtsiSetStepSizePtr(&Simulink_M->solverInfo, &Simulink_M->Timing.stepSize0);
    rtsiSetdXPtr(&Simulink_M->solverInfo, &Simulink_M->derivs);
    rtsiSetContStatesPtr(&Simulink_M->solverInfo, (real_T **)
                         &Simulink_M->contStates);
    rtsiSetNumContStatesPtr(&Simulink_M->solverInfo,
      &Simulink_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&Simulink_M->solverInfo,
      &Simulink_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&Simulink_M->solverInfo,
      &Simulink_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&Simulink_M->solverInfo,
      &Simulink_M->periodicContStateRanges);
    rtsiSetContStateDisabledPtr(&Simulink_M->solverInfo, (boolean_T**)
      &Simulink_M->contStateDisabled);
    rtsiSetErrorStatusPtr(&Simulink_M->solverInfo, (&rtmGetErrorStatus
      (Simulink_M)));
    rtsiSetRTModelPtr(&Simulink_M->solverInfo, Simulink_M);
  }

  rtsiSetSimTimeStep(&Simulink_M->solverInfo, MAJOR_TIME_STEP);
  rtsiSetIsMinorTimeStepWithModeChange(&Simulink_M->solverInfo, false);
  rtsiSetIsContModeFrozen(&Simulink_M->solverInfo, false);
  Simulink_M->intgData.y = Simulink_M->odeY;
  Simulink_M->intgData.f[0] = Simulink_M->odeF[0];
  Simulink_M->intgData.f[1] = Simulink_M->odeF[1];
  Simulink_M->intgData.f[2] = Simulink_M->odeF[2];
  Simulink_M->contStates = ((real_T *) &Simulink_X);
  Simulink_M->contStateDisabled = ((boolean_T *) &Simulink_XDis);
  Simulink_M->Timing.tStart = (0.0);
  rtsiSetSolverData(&Simulink_M->solverInfo, (void *)&Simulink_M->intgData);
  rtsiSetSolverName(&Simulink_M->solverInfo,"ode3");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = Simulink_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    Simulink_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    Simulink_M->Timing.sampleTimes = (&Simulink_M->Timing.sampleTimesArray[0]);
    Simulink_M->Timing.offsetTimes = (&Simulink_M->Timing.offsetTimesArray[0]);

    /* task periods */
    Simulink_M->Timing.sampleTimes[0] = (0.0);
    Simulink_M->Timing.sampleTimes[1] = (0.002);

    /* task offsets */
    Simulink_M->Timing.offsetTimes[0] = (0.0);
    Simulink_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(Simulink_M, &Simulink_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = Simulink_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    Simulink_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(Simulink_M, -1);
  Simulink_M->Timing.stepSize0 = 0.002;
  Simulink_M->Timing.stepSize1 = 0.002;

  /* External mode info */
  Simulink_M->Sizes.checksums[0] = (208607193U);
  Simulink_M->Sizes.checksums[1] = (2410890202U);
  Simulink_M->Sizes.checksums[2] = (2172331919U);
  Simulink_M->Sizes.checksums[3] = (1432870620U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[1];
    Simulink_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(Simulink_M->extModeInfo,
      &Simulink_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(Simulink_M->extModeInfo, Simulink_M->Sizes.checksums);
    rteiSetTPtr(Simulink_M->extModeInfo, rtmGetTPtr(Simulink_M));
  }

  Simulink_M->solverInfoPtr = (&Simulink_M->solverInfo);
  Simulink_M->Timing.stepSize = (0.002);
  rtsiSetFixedStepSize(&Simulink_M->solverInfo, 0.002);
  rtsiSetSolverMode(&Simulink_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  Simulink_M->blockIO = ((void *) &Simulink_B);
  (void) memset(((void *) &Simulink_B), 0,
                sizeof(B_Simulink_T));

  /* parameters */
  Simulink_M->defaultParam = ((real_T *)&Simulink_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &Simulink_X;
    Simulink_M->contStates = (x);
    (void) memset((void *)&Simulink_X, 0,
                  sizeof(X_Simulink_T));
  }

  /* disabled states */
  {
    boolean_T *xdis = (boolean_T *) &Simulink_XDis;
    Simulink_M->contStateDisabled = (xdis);
    (void) memset((void *)&Simulink_XDis, 0,
                  sizeof(XDis_Simulink_T));
  }

  /* states (dwork) */
  Simulink_M->dwork = ((void *) &Simulink_DW);
  (void) memset((void *)&Simulink_DW, 0,
                sizeof(DW_Simulink_T));

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    Simulink_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 21;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Initialize Sizes */
  Simulink_M->Sizes.numContStates = (2);/* Number of continuous states */
  Simulink_M->Sizes.numPeriodicContStates = (0);
                                      /* Number of periodic continuous states */
  Simulink_M->Sizes.numY = (0);        /* Number of model outputs */
  Simulink_M->Sizes.numU = (0);        /* Number of model inputs */
  Simulink_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  Simulink_M->Sizes.numSampTimes = (2);/* Number of sample times */
  Simulink_M->Sizes.numBlocks = (20);  /* Number of blocks */
  Simulink_M->Sizes.numBlockIO = (7);  /* Number of block outputs */
  Simulink_M->Sizes.numBlockPrms = (92);/* Sum of parameter "widths" */
  return Simulink_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
