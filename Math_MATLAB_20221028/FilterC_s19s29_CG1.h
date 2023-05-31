/*
 * FilterC_s19s29_CG1.h
 *
 * Code generation for model "FilterC_s19s29_CG1".
 *
 * Model version              : 1.28
 * Simulink Coder version : 9.6 (R2021b) 14-May-2021
 * C source code generated on : Sat Sep 10 15:19:44 2022
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: ARM Compatible->ARM Cortex-M
 * Code generation objective: Execution efficiency
 * Validation result: Not run
 */



#ifndef RTW_HEADER_FilterC_s19s29_CG1_h_
#define RTW_HEADER_FilterC_s19s29_CG1_h_


#include "MathFast.h"


#include <stddef.h>
#include <string.h>
#ifndef FilterC_s19s29_CG1_COMMON_INCLUDES_
#define FilterC_s19s29_CG1_COMMON_INCLUDES_
#include "rtwtypes.h"
//#include "rtw_continuous.h"
//#include "rtw_solver.h"
#endif                                 /* FilterC_s19s29_CG1_COMMON_INCLUDES_ */

#include "FilterC_s19s29_CG1_types.h"

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
  int32_T FootDelay1_DSTATE;           /* '<S1>/FootDelay1' */
  int32_T BodyDelay21_DSTATE;          /* '<S1>/BodyDelay21' */
  int32_T BodyDelay22_DSTATE;          /* '<S1>/BodyDelay22' */
  int32_T FootDelay2_DSTATE;           /* '<S1>/FootDelay2' */
} DW_FilterC_s19s29_CG1_T;

/* External inputs (root inport signals with default storage) */
typedef struct {
  int32_T Input;                       /* '<Root>/Input' */
} ExtU_FilterC_s19s29_CG1_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  int32_T Output;                      /* '<Root>/Output' */
} ExtY_FilterC_s19s29_CG1_T;

/* Real-time Model Data Structure */
struct tag_RTM_FilterC_s19s29_CG1_T {
  const char_T *errorStatus;
};

/* Block states (default storage) */
extern DW_FilterC_s19s29_CG1_T FilterC_s19s29_CG1_DW;

/* External inputs (root inport signals with default storage) */
//extern ExtU_FilterC_s19s29_CG1_T FilterC_s19s29_CG1_U;

/* External outputs (root outports fed by signals with default storage) */
//extern ExtY_FilterC_s19s29_CG1_T FilterC_s19s29_CG1_Y;

/* Model entry point functions */
extern void FilterC_s19s29_CG1_initialize(void);
extern void FilterC_s19s29_CG1_step(void);
extern int32_t FilterC_s19s29_CG1_step_o(int32_t Input);
extern void FilterC_s19s29_CG1_terminate(void);

/* Real-time Model object */
extern RT_MODEL_FilterC_s19s29_CG1_T *const FilterC_s19s29_CG1_M;

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
 * hilite_system('FM13_3_21b/FilterC_s19s29_CG1')    - opens subsystem FM13_3_21b/FilterC_s19s29_CG1
 * hilite_system('FM13_3_21b/FilterC_s19s29_CG1/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'FM13_3_21b'
 * '<S1>'   : 'FM13_3_21b/FilterC_s19s29_CG1'
 */
#endif                                 /* RTW_HEADER_FilterC_s19s29_CG1_h_ */
