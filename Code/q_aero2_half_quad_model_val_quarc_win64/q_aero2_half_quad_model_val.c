/*
 * q_aero2_half_quad_model_val.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "q_aero2_half_quad_model_val".
 *
 * Model version              : 7.2
 * Simulink Coder version : 24.2 (R2024b) 21-Jun-2024
 * C source code generated on : Tue Jun 30 15:11:42 2026
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "q_aero2_half_quad_model_val.h"
#include "rtwtypes.h"
#include "q_aero2_half_quad_model_val_private.h"
#include <string.h>
#include "rt_nonfinite.h"
#include "q_aero2_half_quad_model_val_dt.h"

/* Block signals (default storage) */
B_q_aero2_half_quad_model_val_T q_aero2_half_quad_model_val_B;

/* Continuous states */
X_q_aero2_half_quad_model_val_T q_aero2_half_quad_model_val_X;

/* Disabled State Vector */
XDis_q_aero2_half_quad_model__T q_aero2_half_quad_model_va_XDis;

/* Block states (default storage) */
DW_q_aero2_half_quad_model_va_T q_aero2_half_quad_model_val_DW;

/* Real-time model */
static RT_MODEL_q_aero2_half_quad_mo_T q_aero2_half_quad_model_val_M_;
RT_MODEL_q_aero2_half_quad_mo_T *const q_aero2_half_quad_model_val_M =
  &q_aero2_half_quad_model_val_M_;

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
  int_T nXc = 4;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);
  rtsiSetdX(si, f0);
  q_aero2_half_quad_model_val_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; ++i) {
    x[i] += h * f0[i];
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model output function */
void q_aero2_half_quad_model_val_output(void)
{
  real_T rtb_HILReadTimebase_o1;
  real_T rtb_HILReadTimebase_o2;
  real_T rtb_HILReadTimebase_o3;
  real_T tmp_0;
  boolean_T tmp;
  if (rtmIsMajorTimeStep(q_aero2_half_quad_model_val_M)) {
    /* set solver stop time */
    if (!(q_aero2_half_quad_model_val_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&q_aero2_half_quad_model_val_M->solverInfo,
                            ((q_aero2_half_quad_model_val_M->Timing.clockTickH0
        + 1) * q_aero2_half_quad_model_val_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&q_aero2_half_quad_model_val_M->solverInfo,
                            ((q_aero2_half_quad_model_val_M->Timing.clockTick0 +
        1) * q_aero2_half_quad_model_val_M->Timing.stepSize0 +
        q_aero2_half_quad_model_val_M->Timing.clockTickH0 *
        q_aero2_half_quad_model_val_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(q_aero2_half_quad_model_val_M)) {
    q_aero2_half_quad_model_val_M->Timing.t[0] = rtsiGetT
      (&q_aero2_half_quad_model_val_M->solverInfo);
  }

  tmp = rtmIsMajorTimeStep(q_aero2_half_quad_model_val_M);
  if (tmp) {
    /* S-Function (hil_read_timebase_block): '<Root>/HIL Read Timebase' */

    /* S-Function Block: q_aero2_half_quad_model_val/HIL Read Timebase (hil_read_timebase_block) */
    {
      t_error result;
      result = hil_task_read(q_aero2_half_quad_model_val_DW.HILReadTimebase_Task,
        1,
        NULL,
        &q_aero2_half_quad_model_val_DW.HILReadTimebase_EncoderBuffer,
        NULL,
        &q_aero2_half_quad_model_val_DW.HILReadTimebase_OtherBuffer[0]
        );
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_aero2_half_quad_model_val_M, _rt_error_message);
      } else {
        rtb_HILReadTimebase_o1 =
          q_aero2_half_quad_model_val_DW.HILReadTimebase_EncoderBuffer;
        rtb_HILReadTimebase_o2 =
          q_aero2_half_quad_model_val_DW.HILReadTimebase_OtherBuffer[0];
        rtb_HILReadTimebase_o3 =
          q_aero2_half_quad_model_val_DW.HILReadTimebase_OtherBuffer[1];
      }
    }
  }

  /* Step: '<Root>/Step' */
  if (q_aero2_half_quad_model_val_M->Timing.t[0] <
      q_aero2_half_quad_model_val_P.Step_Time) {
    tmp_0 = q_aero2_half_quad_model_val_P.Step_Y0;
  } else {
    tmp_0 = q_aero2_half_quad_model_val_P.Step_YFinal;
  }

  /* Gain: '<Root>/Gain' incorporates:
   *  Step: '<Root>/Step'
   */
  q_aero2_half_quad_model_val_B.Gain = q_aero2_half_quad_model_val_P.Gain_Gain *
    tmp_0;

  /* Gain: '<Root>/For +ve  response' */
  q_aero2_half_quad_model_val_B.Forveresponse =
    q_aero2_half_quad_model_val_P.Forveresponse_Gain *
    q_aero2_half_quad_model_val_B.Gain;
  if (tmp) {
    /* S-Function (hil_write_analog_block): '<Root>/HIL Write Analog' */

    /* S-Function Block: q_aero2_half_quad_model_val/HIL Write Analog (hil_write_analog_block) */
    {
      t_error result;
      q_aero2_half_quad_model_val_DW.HILWriteAnalog_Buffer[0] =
        q_aero2_half_quad_model_val_B.Forveresponse;
      q_aero2_half_quad_model_val_DW.HILWriteAnalog_Buffer[1] =
        q_aero2_half_quad_model_val_B.Gain;
      result = hil_write_analog
        (q_aero2_half_quad_model_val_DW.HILInitialize_Card,
         q_aero2_half_quad_model_val_P.HILWriteAnalog_channels, 2,
         &q_aero2_half_quad_model_val_DW.HILWriteAnalog_Buffer[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_aero2_half_quad_model_val_M, _rt_error_message);
      }
    }

    /* Gain: '<Root>/counts to rad' */
    q_aero2_half_quad_model_val_B.hardware =
      q_aero2_half_quad_model_val_P.countstorad_Gain * rtb_HILReadTimebase_o1;
  }

  /* TransferFcn: '<Root>/Haf-Quadrotor Model3' */
  q_aero2_half_quad_model_val_B.model = 0.0;
  q_aero2_half_quad_model_val_B.model +=
    q_aero2_half_quad_model_val_P.HafQuadrotorModel3_C[0] *
    q_aero2_half_quad_model_val_X.HafQuadrotorModel3_CSTATE[0];
  q_aero2_half_quad_model_val_B.model +=
    q_aero2_half_quad_model_val_P.HafQuadrotorModel3_C[1] *
    q_aero2_half_quad_model_val_X.HafQuadrotorModel3_CSTATE[1];
  if (tmp) {
    /* Gain: '<Root>/Counts//s to rad//s' */
    q_aero2_half_quad_model_val_B.Countsstorads =
      q_aero2_half_quad_model_val_P.Countsstorads_Gain * rtb_HILReadTimebase_o2;
  }

  /* TransferFcn: '<Root>/Transfer Fcn' */
  q_aero2_half_quad_model_val_B.measuredrate = 0.0;
  q_aero2_half_quad_model_val_B.measuredrate +=
    q_aero2_half_quad_model_val_P.TransferFcn_C *
    q_aero2_half_quad_model_val_X.TransferFcn_CSTATE;

  /* TransferFcn: '<Root>/Haf-Quadrotor Model1' */
  q_aero2_half_quad_model_val_B.model_i = 0.0;
  q_aero2_half_quad_model_val_B.model_i +=
    q_aero2_half_quad_model_val_P.HafQuadrotorModel1_C *
    q_aero2_half_quad_model_val_X.HafQuadrotorModel1_CSTATE;
  if (tmp) {
    /* Gain: '<Root>/Counts to rad//s' */
    q_aero2_half_quad_model_val_B.Countstorads =
      q_aero2_half_quad_model_val_P.Countstorads_Gain * rtb_HILReadTimebase_o3;
  }
}

/* Model update function */
void q_aero2_half_quad_model_val_update(void)
{
  if (rtmIsMajorTimeStep(q_aero2_half_quad_model_val_M)) {
    rt_ertODEUpdateContinuousStates(&q_aero2_half_quad_model_val_M->solverInfo);
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
  if (!(++q_aero2_half_quad_model_val_M->Timing.clockTick0)) {
    ++q_aero2_half_quad_model_val_M->Timing.clockTickH0;
  }

  q_aero2_half_quad_model_val_M->Timing.t[0] = rtsiGetSolverStopTime
    (&q_aero2_half_quad_model_val_M->solverInfo);

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
    if (!(++q_aero2_half_quad_model_val_M->Timing.clockTick1)) {
      ++q_aero2_half_quad_model_val_M->Timing.clockTickH1;
    }

    q_aero2_half_quad_model_val_M->Timing.t[1] =
      q_aero2_half_quad_model_val_M->Timing.clockTick1 *
      q_aero2_half_quad_model_val_M->Timing.stepSize1 +
      q_aero2_half_quad_model_val_M->Timing.clockTickH1 *
      q_aero2_half_quad_model_val_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Derivatives for root system: '<Root>' */
void q_aero2_half_quad_model_val_derivatives(void)
{
  XDot_q_aero2_half_quad_model__T *_rtXdot;
  _rtXdot = ((XDot_q_aero2_half_quad_model__T *)
             q_aero2_half_quad_model_val_M->derivs);

  /* Derivatives for TransferFcn: '<Root>/Haf-Quadrotor Model3' */
  _rtXdot->HafQuadrotorModel3_CSTATE[0] =
    q_aero2_half_quad_model_val_P.HafQuadrotorModel3_A[0] *
    q_aero2_half_quad_model_val_X.HafQuadrotorModel3_CSTATE[0];
  _rtXdot->HafQuadrotorModel3_CSTATE[0] +=
    q_aero2_half_quad_model_val_P.HafQuadrotorModel3_A[1] *
    q_aero2_half_quad_model_val_X.HafQuadrotorModel3_CSTATE[1];
  _rtXdot->HafQuadrotorModel3_CSTATE[1] =
    q_aero2_half_quad_model_val_X.HafQuadrotorModel3_CSTATE[0];
  _rtXdot->HafQuadrotorModel3_CSTATE[0] += q_aero2_half_quad_model_val_B.Gain;

  /* Derivatives for TransferFcn: '<Root>/Transfer Fcn' */
  _rtXdot->TransferFcn_CSTATE = q_aero2_half_quad_model_val_P.TransferFcn_A *
    q_aero2_half_quad_model_val_X.TransferFcn_CSTATE;
  _rtXdot->TransferFcn_CSTATE += q_aero2_half_quad_model_val_B.Countstorads;

  /* Derivatives for TransferFcn: '<Root>/Haf-Quadrotor Model1' */
  _rtXdot->HafQuadrotorModel1_CSTATE =
    q_aero2_half_quad_model_val_P.HafQuadrotorModel1_A *
    q_aero2_half_quad_model_val_X.HafQuadrotorModel1_CSTATE;
  _rtXdot->HafQuadrotorModel1_CSTATE += q_aero2_half_quad_model_val_B.Gain;
}

/* Model initialize function */
void q_aero2_half_quad_model_val_initialize(void)
{
  /* Start for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: q_aero2_half_quad_model_val/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("quanser_aero2_usb", "0@tcpip://localhost:18950",
                      &q_aero2_half_quad_model_val_DW.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(q_aero2_half_quad_model_val_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_watchdog_clear
      (q_aero2_half_quad_model_val_DW.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(q_aero2_half_quad_model_val_M, _rt_error_message);
      return;
    }

    if ((q_aero2_half_quad_model_val_P.HILInitialize_AIPStart && !is_switching) ||
        (q_aero2_half_quad_model_val_P.HILInitialize_AIPEnter && is_switching))
    {
      q_aero2_half_quad_model_val_DW.HILInitialize_AIMinimums[0] =
        (q_aero2_half_quad_model_val_P.HILInitialize_AILow);
      q_aero2_half_quad_model_val_DW.HILInitialize_AIMinimums[1] =
        (q_aero2_half_quad_model_val_P.HILInitialize_AILow);
      q_aero2_half_quad_model_val_DW.HILInitialize_AIMaximums[0] =
        q_aero2_half_quad_model_val_P.HILInitialize_AIHigh;
      q_aero2_half_quad_model_val_DW.HILInitialize_AIMaximums[1] =
        q_aero2_half_quad_model_val_P.HILInitialize_AIHigh;
      result = hil_set_analog_input_ranges
        (q_aero2_half_quad_model_val_DW.HILInitialize_Card,
         q_aero2_half_quad_model_val_P.HILInitialize_AIChannels, 2U,
         &q_aero2_half_quad_model_val_DW.HILInitialize_AIMinimums[0],
         &q_aero2_half_quad_model_val_DW.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_aero2_half_quad_model_val_M, _rt_error_message);
        return;
      }
    }

    if ((q_aero2_half_quad_model_val_P.HILInitialize_AOPStart && !is_switching) ||
        (q_aero2_half_quad_model_val_P.HILInitialize_AOPEnter && is_switching))
    {
      q_aero2_half_quad_model_val_DW.HILInitialize_AOMinimums[0] =
        (q_aero2_half_quad_model_val_P.HILInitialize_AOLow);
      q_aero2_half_quad_model_val_DW.HILInitialize_AOMinimums[1] =
        (q_aero2_half_quad_model_val_P.HILInitialize_AOLow);
      q_aero2_half_quad_model_val_DW.HILInitialize_AOMaximums[0] =
        q_aero2_half_quad_model_val_P.HILInitialize_AOHigh;
      q_aero2_half_quad_model_val_DW.HILInitialize_AOMaximums[1] =
        q_aero2_half_quad_model_val_P.HILInitialize_AOHigh;
      result = hil_set_analog_output_ranges
        (q_aero2_half_quad_model_val_DW.HILInitialize_Card,
         q_aero2_half_quad_model_val_P.HILInitialize_AOChannels, 2U,
         &q_aero2_half_quad_model_val_DW.HILInitialize_AOMinimums[0],
         &q_aero2_half_quad_model_val_DW.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_aero2_half_quad_model_val_M, _rt_error_message);
        return;
      }
    }

    if ((q_aero2_half_quad_model_val_P.HILInitialize_AOStart && !is_switching) ||
        (q_aero2_half_quad_model_val_P.HILInitialize_AOEnter && is_switching)) {
      q_aero2_half_quad_model_val_DW.HILInitialize_AOVoltages[0] =
        q_aero2_half_quad_model_val_P.HILInitialize_AOInitial;
      q_aero2_half_quad_model_val_DW.HILInitialize_AOVoltages[1] =
        q_aero2_half_quad_model_val_P.HILInitialize_AOInitial;
      result = hil_write_analog
        (q_aero2_half_quad_model_val_DW.HILInitialize_Card,
         q_aero2_half_quad_model_val_P.HILInitialize_AOChannels, 2U,
         &q_aero2_half_quad_model_val_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_aero2_half_quad_model_val_M, _rt_error_message);
        return;
      }
    }

    if (q_aero2_half_quad_model_val_P.HILInitialize_AOReset) {
      q_aero2_half_quad_model_val_DW.HILInitialize_AOVoltages[0] =
        q_aero2_half_quad_model_val_P.HILInitialize_AOWatchdog;
      q_aero2_half_quad_model_val_DW.HILInitialize_AOVoltages[1] =
        q_aero2_half_quad_model_val_P.HILInitialize_AOWatchdog;
      result = hil_watchdog_set_analog_expiration_state
        (q_aero2_half_quad_model_val_DW.HILInitialize_Card,
         q_aero2_half_quad_model_val_P.HILInitialize_AOChannels, 2U,
         &q_aero2_half_quad_model_val_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_aero2_half_quad_model_val_M, _rt_error_message);
        return;
      }
    }

    result = hil_set_digital_directions
      (q_aero2_half_quad_model_val_DW.HILInitialize_Card, NULL, 0U,
       q_aero2_half_quad_model_val_P.HILInitialize_DOChannels, 2U);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(q_aero2_half_quad_model_val_M, _rt_error_message);
      return;
    }

    if ((q_aero2_half_quad_model_val_P.HILInitialize_DOStart && !is_switching) ||
        (q_aero2_half_quad_model_val_P.HILInitialize_DOEnter && is_switching)) {
      q_aero2_half_quad_model_val_DW.HILInitialize_DOBits[0] =
        q_aero2_half_quad_model_val_P.HILInitialize_DOInitial;
      q_aero2_half_quad_model_val_DW.HILInitialize_DOBits[1] =
        q_aero2_half_quad_model_val_P.HILInitialize_DOInitial;
      result = hil_write_digital
        (q_aero2_half_quad_model_val_DW.HILInitialize_Card,
         q_aero2_half_quad_model_val_P.HILInitialize_DOChannels, 2U, (t_boolean *)
         &q_aero2_half_quad_model_val_DW.HILInitialize_DOBits[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_aero2_half_quad_model_val_M, _rt_error_message);
        return;
      }
    }

    if (q_aero2_half_quad_model_val_P.HILInitialize_DOReset) {
      q_aero2_half_quad_model_val_DW.HILInitialize_DOStates[0] =
        q_aero2_half_quad_model_val_P.HILInitialize_DOWatchdog;
      q_aero2_half_quad_model_val_DW.HILInitialize_DOStates[1] =
        q_aero2_half_quad_model_val_P.HILInitialize_DOWatchdog;
      result = hil_watchdog_set_digital_expiration_state
        (q_aero2_half_quad_model_val_DW.HILInitialize_Card,
         q_aero2_half_quad_model_val_P.HILInitialize_DOChannels, 2U, (const
          t_digital_state *)
         &q_aero2_half_quad_model_val_DW.HILInitialize_DOStates[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_aero2_half_quad_model_val_M, _rt_error_message);
        return;
      }
    }

    if ((q_aero2_half_quad_model_val_P.HILInitialize_EIPStart && !is_switching) ||
        (q_aero2_half_quad_model_val_P.HILInitialize_EIPEnter && is_switching))
    {
      q_aero2_half_quad_model_val_DW.HILInitialize_QuadratureModes[0] =
        q_aero2_half_quad_model_val_P.HILInitialize_EIQuadrature;
      q_aero2_half_quad_model_val_DW.HILInitialize_QuadratureModes[1] =
        q_aero2_half_quad_model_val_P.HILInitialize_EIQuadrature;
      q_aero2_half_quad_model_val_DW.HILInitialize_QuadratureModes[2] =
        q_aero2_half_quad_model_val_P.HILInitialize_EIQuadrature;
      q_aero2_half_quad_model_val_DW.HILInitialize_QuadratureModes[3] =
        q_aero2_half_quad_model_val_P.HILInitialize_EIQuadrature;
      result = hil_set_encoder_quadrature_mode
        (q_aero2_half_quad_model_val_DW.HILInitialize_Card,
         q_aero2_half_quad_model_val_P.HILInitialize_EIChannels, 4U,
         (t_encoder_quadrature_mode *)
         &q_aero2_half_quad_model_val_DW.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_aero2_half_quad_model_val_M, _rt_error_message);
        return;
      }
    }

    if ((q_aero2_half_quad_model_val_P.HILInitialize_EIStart && !is_switching) ||
        (q_aero2_half_quad_model_val_P.HILInitialize_EIEnter && is_switching)) {
      q_aero2_half_quad_model_val_DW.HILInitialize_InitialEICounts[0] =
        q_aero2_half_quad_model_val_P.HILInitialize_EIInitial;
      q_aero2_half_quad_model_val_DW.HILInitialize_InitialEICounts[1] =
        q_aero2_half_quad_model_val_P.HILInitialize_EIInitial;
      q_aero2_half_quad_model_val_DW.HILInitialize_InitialEICounts[2] =
        q_aero2_half_quad_model_val_P.HILInitialize_EIInitial;
      q_aero2_half_quad_model_val_DW.HILInitialize_InitialEICounts[3] =
        q_aero2_half_quad_model_val_P.HILInitialize_EIInitial;
      result = hil_set_encoder_counts
        (q_aero2_half_quad_model_val_DW.HILInitialize_Card,
         q_aero2_half_quad_model_val_P.HILInitialize_EIChannels, 4U,
         &q_aero2_half_quad_model_val_DW.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_aero2_half_quad_model_val_M, _rt_error_message);
        return;
      }
    }

    if ((q_aero2_half_quad_model_val_P.HILInitialize_OOStart && !is_switching) ||
        (q_aero2_half_quad_model_val_P.HILInitialize_OOEnter && is_switching)) {
      result = hil_write_other(q_aero2_half_quad_model_val_DW.HILInitialize_Card,
        q_aero2_half_quad_model_val_P.HILInitialize_OOChannels, 3U,
        q_aero2_half_quad_model_val_P.HILInitialize_OOInitial);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_aero2_half_quad_model_val_M, _rt_error_message);
        return;
      }
    }

    if (q_aero2_half_quad_model_val_P.HILInitialize_OOReset) {
      result = hil_watchdog_set_other_expiration_state
        (q_aero2_half_quad_model_val_DW.HILInitialize_Card,
         q_aero2_half_quad_model_val_P.HILInitialize_OOChannels, 3U,
         q_aero2_half_quad_model_val_P.HILInitialize_OOWatchdog);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(q_aero2_half_quad_model_val_M, _rt_error_message);
        return;
      }
    }
  }

  /* Start for S-Function (hil_read_timebase_block): '<Root>/HIL Read Timebase' */

  /* S-Function Block: q_aero2_half_quad_model_val/HIL Read Timebase (hil_read_timebase_block) */
  {
    t_error result;
    result = hil_task_create_reader
      (q_aero2_half_quad_model_val_DW.HILInitialize_Card,
       q_aero2_half_quad_model_val_P.HILReadTimebase_SamplesInBuffer,
       NULL, 0U,
       &q_aero2_half_quad_model_val_P.HILReadTimebase_EncoderChannels, 1U,
       NULL, 0U,
       q_aero2_half_quad_model_val_P.HILReadTimebase_OtherChannels, 2U,
       &q_aero2_half_quad_model_val_DW.HILReadTimebase_Task);
    if (result >= 0) {
      result = hil_task_set_buffer_overflow_mode
        (q_aero2_half_quad_model_val_DW.HILReadTimebase_Task,
         (t_buffer_overflow_mode)
         (q_aero2_half_quad_model_val_P.HILReadTimebase_OverflowMode - 1));
    }

    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(q_aero2_half_quad_model_val_M, _rt_error_message);
    }
  }

  /* InitializeConditions for TransferFcn: '<Root>/Haf-Quadrotor Model3' */
  q_aero2_half_quad_model_val_X.HafQuadrotorModel3_CSTATE[0] = 0.0;
  q_aero2_half_quad_model_val_X.HafQuadrotorModel3_CSTATE[1] = 0.0;

  /* InitializeConditions for TransferFcn: '<Root>/Transfer Fcn' */
  q_aero2_half_quad_model_val_X.TransferFcn_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<Root>/Haf-Quadrotor Model1' */
  q_aero2_half_quad_model_val_X.HafQuadrotorModel1_CSTATE = 0.0;
}

/* Model terminate function */
void q_aero2_half_quad_model_val_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<Root>/HIL Initialize' */

  /* S-Function Block: q_aero2_half_quad_model_val/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    t_uint32 num_final_digital_outputs = 0;
    t_uint32 num_final_other_outputs = 0;
    hil_task_stop_all(q_aero2_half_quad_model_val_DW.HILInitialize_Card);
    hil_monitor_stop_all(q_aero2_half_quad_model_val_DW.HILInitialize_Card);
    is_switching = false;
    if ((q_aero2_half_quad_model_val_P.HILInitialize_AOTerminate &&
         !is_switching) || (q_aero2_half_quad_model_val_P.HILInitialize_AOExit &&
         is_switching)) {
      q_aero2_half_quad_model_val_DW.HILInitialize_AOVoltages[0] =
        q_aero2_half_quad_model_val_P.HILInitialize_AOFinal;
      q_aero2_half_quad_model_val_DW.HILInitialize_AOVoltages[1] =
        q_aero2_half_quad_model_val_P.HILInitialize_AOFinal;
      num_final_analog_outputs = 2U;
    } else {
      num_final_analog_outputs = 0;
    }

    if ((q_aero2_half_quad_model_val_P.HILInitialize_DOTerminate &&
         !is_switching) || (q_aero2_half_quad_model_val_P.HILInitialize_DOExit &&
         is_switching)) {
      q_aero2_half_quad_model_val_DW.HILInitialize_DOBits[0] =
        q_aero2_half_quad_model_val_P.HILInitialize_DOFinal;
      q_aero2_half_quad_model_val_DW.HILInitialize_DOBits[1] =
        q_aero2_half_quad_model_val_P.HILInitialize_DOFinal;
      num_final_digital_outputs = 2U;
    } else {
      num_final_digital_outputs = 0;
    }

    if ((q_aero2_half_quad_model_val_P.HILInitialize_OOTerminate &&
         !is_switching) || (q_aero2_half_quad_model_val_P.HILInitialize_OOExit &&
         is_switching)) {
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
      result = hil_write(q_aero2_half_quad_model_val_DW.HILInitialize_Card
                         ,
                         q_aero2_half_quad_model_val_P.HILInitialize_AOChannels,
                         num_final_analog_outputs
                         , NULL, 0
                         ,
                         q_aero2_half_quad_model_val_P.HILInitialize_DOChannels,
                         num_final_digital_outputs
                         ,
                         q_aero2_half_quad_model_val_P.HILInitialize_OOChannels,
                         num_final_other_outputs
                         ,
                         &q_aero2_half_quad_model_val_DW.HILInitialize_AOVoltages
                         [0]
                         , NULL
                         , (t_boolean *)
                         &q_aero2_half_quad_model_val_DW.HILInitialize_DOBits[0]
                         , q_aero2_half_quad_model_val_P.HILInitialize_OOFinal
                         );
      if (result == -QERR_HIL_WRITE_NOT_SUPPORTED) {
        t_error local_result;
        result = 0;

        /* The hil_write operation is not supported by this card. Write final outputs for each channel type */
        if (num_final_analog_outputs > 0) {
          local_result = hil_write_analog
            (q_aero2_half_quad_model_val_DW.HILInitialize_Card,
             q_aero2_half_quad_model_val_P.HILInitialize_AOChannels,
             num_final_analog_outputs,
             &q_aero2_half_quad_model_val_DW.HILInitialize_AOVoltages[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_digital_outputs > 0) {
          local_result = hil_write_digital
            (q_aero2_half_quad_model_val_DW.HILInitialize_Card,
             q_aero2_half_quad_model_val_P.HILInitialize_DOChannels,
             num_final_digital_outputs, (t_boolean *)
             &q_aero2_half_quad_model_val_DW.HILInitialize_DOBits[0]);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (num_final_other_outputs > 0) {
          local_result = hil_write_other
            (q_aero2_half_quad_model_val_DW.HILInitialize_Card,
             q_aero2_half_quad_model_val_P.HILInitialize_OOChannels,
             num_final_other_outputs,
             q_aero2_half_quad_model_val_P.HILInitialize_OOFinal);
          if (local_result < 0) {
            result = local_result;
          }
        }

        if (result < 0) {
          msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
            (_rt_error_message));
          rtmSetErrorStatus(q_aero2_half_quad_model_val_M, _rt_error_message);
        }
      }
    }

    hil_task_delete_all(q_aero2_half_quad_model_val_DW.HILInitialize_Card);
    hil_monitor_delete_all(q_aero2_half_quad_model_val_DW.HILInitialize_Card);
    hil_close(q_aero2_half_quad_model_val_DW.HILInitialize_Card);
    q_aero2_half_quad_model_val_DW.HILInitialize_Card = NULL;
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
  q_aero2_half_quad_model_val_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  q_aero2_half_quad_model_val_update();
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
  q_aero2_half_quad_model_val_initialize();
}

void MdlTerminate(void)
{
  q_aero2_half_quad_model_val_terminate();
}

/* Registration function */
RT_MODEL_q_aero2_half_quad_mo_T *q_aero2_half_quad_model_val(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)q_aero2_half_quad_model_val_M, 0,
                sizeof(RT_MODEL_q_aero2_half_quad_mo_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&q_aero2_half_quad_model_val_M->solverInfo,
                          &q_aero2_half_quad_model_val_M->Timing.simTimeStep);
    rtsiSetTPtr(&q_aero2_half_quad_model_val_M->solverInfo, &rtmGetTPtr
                (q_aero2_half_quad_model_val_M));
    rtsiSetStepSizePtr(&q_aero2_half_quad_model_val_M->solverInfo,
                       &q_aero2_half_quad_model_val_M->Timing.stepSize0);
    rtsiSetdXPtr(&q_aero2_half_quad_model_val_M->solverInfo,
                 &q_aero2_half_quad_model_val_M->derivs);
    rtsiSetContStatesPtr(&q_aero2_half_quad_model_val_M->solverInfo, (real_T **)
                         &q_aero2_half_quad_model_val_M->contStates);
    rtsiSetNumContStatesPtr(&q_aero2_half_quad_model_val_M->solverInfo,
      &q_aero2_half_quad_model_val_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&q_aero2_half_quad_model_val_M->solverInfo,
      &q_aero2_half_quad_model_val_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr
      (&q_aero2_half_quad_model_val_M->solverInfo,
       &q_aero2_half_quad_model_val_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&q_aero2_half_quad_model_val_M->solverInfo,
      &q_aero2_half_quad_model_val_M->periodicContStateRanges);
    rtsiSetContStateDisabledPtr(&q_aero2_half_quad_model_val_M->solverInfo,
      (boolean_T**) &q_aero2_half_quad_model_val_M->contStateDisabled);
    rtsiSetErrorStatusPtr(&q_aero2_half_quad_model_val_M->solverInfo,
                          (&rtmGetErrorStatus(q_aero2_half_quad_model_val_M)));
    rtsiSetRTModelPtr(&q_aero2_half_quad_model_val_M->solverInfo,
                      q_aero2_half_quad_model_val_M);
  }

  rtsiSetSimTimeStep(&q_aero2_half_quad_model_val_M->solverInfo, MAJOR_TIME_STEP);
  rtsiSetIsMinorTimeStepWithModeChange
    (&q_aero2_half_quad_model_val_M->solverInfo, false);
  rtsiSetIsContModeFrozen(&q_aero2_half_quad_model_val_M->solverInfo, false);
  q_aero2_half_quad_model_val_M->intgData.f[0] =
    q_aero2_half_quad_model_val_M->odeF[0];
  q_aero2_half_quad_model_val_M->contStates = ((real_T *)
    &q_aero2_half_quad_model_val_X);
  q_aero2_half_quad_model_val_M->contStateDisabled = ((boolean_T *)
    &q_aero2_half_quad_model_va_XDis);
  q_aero2_half_quad_model_val_M->Timing.tStart = (0.0);
  rtsiSetSolverData(&q_aero2_half_quad_model_val_M->solverInfo, (void *)
                    &q_aero2_half_quad_model_val_M->intgData);
  rtsiSetSolverName(&q_aero2_half_quad_model_val_M->solverInfo,"ode1");

  /* Initialize timing info */
  {
    int_T *mdlTsMap =
      q_aero2_half_quad_model_val_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    q_aero2_half_quad_model_val_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    q_aero2_half_quad_model_val_M->Timing.sampleTimes =
      (&q_aero2_half_quad_model_val_M->Timing.sampleTimesArray[0]);
    q_aero2_half_quad_model_val_M->Timing.offsetTimes =
      (&q_aero2_half_quad_model_val_M->Timing.offsetTimesArray[0]);

    /* task periods */
    q_aero2_half_quad_model_val_M->Timing.sampleTimes[0] = (0.0);
    q_aero2_half_quad_model_val_M->Timing.sampleTimes[1] = (0.002);

    /* task offsets */
    q_aero2_half_quad_model_val_M->Timing.offsetTimes[0] = (0.0);
    q_aero2_half_quad_model_val_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(q_aero2_half_quad_model_val_M,
             &q_aero2_half_quad_model_val_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = q_aero2_half_quad_model_val_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    q_aero2_half_quad_model_val_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(q_aero2_half_quad_model_val_M, 70.0);
  q_aero2_half_quad_model_val_M->Timing.stepSize0 = 0.002;
  q_aero2_half_quad_model_val_M->Timing.stepSize1 = 0.002;

  /* External mode info */
  q_aero2_half_quad_model_val_M->Sizes.checksums[0] = (2437157578U);
  q_aero2_half_quad_model_val_M->Sizes.checksums[1] = (1747851101U);
  q_aero2_half_quad_model_val_M->Sizes.checksums[2] = (2273037151U);
  q_aero2_half_quad_model_val_M->Sizes.checksums[3] = (1161550978U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[1];
    q_aero2_half_quad_model_val_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(q_aero2_half_quad_model_val_M->extModeInfo,
      &q_aero2_half_quad_model_val_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(q_aero2_half_quad_model_val_M->extModeInfo,
                        q_aero2_half_quad_model_val_M->Sizes.checksums);
    rteiSetTPtr(q_aero2_half_quad_model_val_M->extModeInfo, rtmGetTPtr
                (q_aero2_half_quad_model_val_M));
  }

  q_aero2_half_quad_model_val_M->solverInfoPtr =
    (&q_aero2_half_quad_model_val_M->solverInfo);
  q_aero2_half_quad_model_val_M->Timing.stepSize = (0.002);
  rtsiSetFixedStepSize(&q_aero2_half_quad_model_val_M->solverInfo, 0.002);
  rtsiSetSolverMode(&q_aero2_half_quad_model_val_M->solverInfo,
                    SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  q_aero2_half_quad_model_val_M->blockIO = ((void *)
    &q_aero2_half_quad_model_val_B);
  (void) memset(((void *) &q_aero2_half_quad_model_val_B), 0,
                sizeof(B_q_aero2_half_quad_model_val_T));

  /* parameters */
  q_aero2_half_quad_model_val_M->defaultParam = ((real_T *)
    &q_aero2_half_quad_model_val_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &q_aero2_half_quad_model_val_X;
    q_aero2_half_quad_model_val_M->contStates = (x);
    (void) memset((void *)&q_aero2_half_quad_model_val_X, 0,
                  sizeof(X_q_aero2_half_quad_model_val_T));
  }

  /* disabled states */
  {
    boolean_T *xdis = (boolean_T *) &q_aero2_half_quad_model_va_XDis;
    q_aero2_half_quad_model_val_M->contStateDisabled = (xdis);
    (void) memset((void *)&q_aero2_half_quad_model_va_XDis, 0,
                  sizeof(XDis_q_aero2_half_quad_model__T));
  }

  /* states (dwork) */
  q_aero2_half_quad_model_val_M->dwork = ((void *)
    &q_aero2_half_quad_model_val_DW);
  (void) memset((void *)&q_aero2_half_quad_model_val_DW, 0,
                sizeof(DW_q_aero2_half_quad_model_va_T));

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    q_aero2_half_quad_model_val_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 22;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Initialize Sizes */
  q_aero2_half_quad_model_val_M->Sizes.numContStates = (4);/* Number of continuous states */
  q_aero2_half_quad_model_val_M->Sizes.numPeriodicContStates = (0);
                                      /* Number of periodic continuous states */
  q_aero2_half_quad_model_val_M->Sizes.numY = (0);/* Number of model outputs */
  q_aero2_half_quad_model_val_M->Sizes.numU = (0);/* Number of model inputs */
  q_aero2_half_quad_model_val_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  q_aero2_half_quad_model_val_M->Sizes.numSampTimes = (2);/* Number of sample times */
  q_aero2_half_quad_model_val_M->Sizes.numBlocks = (16);/* Number of blocks */
  q_aero2_half_quad_model_val_M->Sizes.numBlockIO = (8);/* Number of block outputs */
  q_aero2_half_quad_model_val_M->Sizes.numBlockPrms = (147);/* Sum of parameter "widths" */
  return q_aero2_half_quad_model_val_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
