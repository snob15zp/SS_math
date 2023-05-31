/*
 * FilterAC_s19s29_CG.h
 *
 * Code generation for model "FilterAC_s19s29_CG".
 *
 * Model version              : 1.38
 * Simulink Coder version : 9.6 (R2021b) 14-May-2021
 * C source code generated on : Thu Oct  6 20:07:40 2022
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objective: Execution efficiency
 * Validation result: Not run
 */

#include "MathFast.h"

#ifndef RTW_HEADER_FilterAC_s19s29_CG_h_
#define RTW_HEADER_FilterAC_s19s29_CG_h_
#include <stddef.h>
#include <string.h>
#ifndef FilterAC_s19s29_CG_COMMON_INCLUDES_
#define FilterAC_s19s29_CG_COMMON_INCLUDES_
#include "rtwtypes.h"
//#include "rtw_continuous.h"
//#include "rtw_solver.h"
#endif                                 /* FilterAC_s19s29_CG_COMMON_INCLUDES_ */

#include "FilterAC_s19s29_CG_types.h"

/* Shared type includes */
#include "multiword_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

/* Block states (default storage) for system '<Root>' */
typedef struct {
  int32_T BodyDelay21_DSTATE;          /* '<S1>/BodyDelay21' */
  int32_T FootDelay1_DSTATE;           /* '<S1>/FootDelay1' */
} DW_FilterAC_s19s29_CG_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  int32_T Input;                       /* '<Root>/Input' */
} ExtU_FilterAC_s19s29_CG_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  int32_T Output;                      /* '<Root>/Output' */
} ExtY_FilterAC_s19s29_CG_T;

/* Real-time Model Data Structure */
struct tag_RTM_FilterAC_s19s29_CG_T {
  const char_T *errorStatus;
};

/* Block states (default storage) */
extern DW_FilterAC_s19s29_CG_T FilterAC_s19s29_CG_DW;

/* External inputs (root inport signals with default storage) */
//extern ExtU_FilterAC_s19s29_CG_T FilterAC_s19s29_CG_U;

/* External outputs (root outports fed by signals with default storage) */
//extern ExtY_FilterAC_s19s29_CG_T FilterAC_s19s29_CG_Y;

/* Model entry point functions */
extern void FilterAC_s19s29_CG_initialize(void);
extern void FilterAC_s19s29_CG_step(void);
extern int32_t FilterAC_s19s29_CG_step_o(int32_t Input);
extern void FilterAC_s19s29_CG_terminate(void);

/* Real-time Model object */
extern RT_MODEL_FilterAC_s19s29_CG_T *const FilterAC_s19s29_CG_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Note that this particular code originates from a subsystem build,
 * and has its own system numbers different from the parent model.
 * Refer to the system hierarchy for this subsystem below, and use the
 * MATLAB hilite_system command to trace the generated code back
 * to the parent model.  For example,
 *
 * hilite_system('FM13_4_21b/FilterAC_s19s29_CG')    - opens subsystem FM13_4_21b/FilterAC_s19s29_CG
 * hilite_system('FM13_4_21b/FilterAC_s19s29_CG/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'FM13_4_21b'
 * '<S1>'   : 'FM13_4_21b/FilterAC_s19s29_CG'
 */
#endif                                 /* RTW_HEADER_FilterAC_s19s29_CG_h_ */
