/*
 * FilterAC_s19s29_CG.c
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

#include "FilterAC_s19s29_CG.h"
#include "FilterAC_s19s29_CG_private.h"

/* Block states (default storage) */
DW_FilterAC_s19s29_CG_T FilterAC_s19s29_CG_DW;

/* External inputs (root inport signals with default storage) */
//ExtU_FilterAC_s19s29_CG_T FilterAC_s19s29_CG_U;

/* External outputs (root outports fed by signals with default storage) */
//ExtY_FilterAC_s19s29_CG_T FilterAC_s19s29_CG_Y;

/* Real-time model */
static RT_MODEL_FilterAC_s19s29_CG_T FilterAC_s19s29_CG_M_;
RT_MODEL_FilterAC_s19s29_CG_T *const FilterAC_s19s29_CG_M =
  &FilterAC_s19s29_CG_M_;
//void mul_wide_s32(int32_T in0, int32_T in1, uint32_T *ptrOutBitsHi, uint32_T
//                  *ptrOutBitsLo)
//{
//  uint32_T absIn0;
//  uint32_T absIn1;
//  uint32_T in0Hi;
//  uint32_T in0Lo;
//  uint32_T in1Hi;
//  uint32_T productHiLo;
//  uint32_T productLoHi;
//  absIn0 = in0 < 0 ? ~(uint32_T)in0 + 1U : (uint32_T)in0;
//  absIn1 = in1 < 0 ? ~(uint32_T)in1 + 1U : (uint32_T)in1;
//  in0Hi = absIn0 >> 16U;
//  in0Lo = absIn0 & 65535U;
//  in1Hi = absIn1 >> 16U;
//  absIn0 = absIn1 & 65535U;
//  productHiLo = in0Hi * absIn0;
//  productLoHi = in0Lo * in1Hi;
//  absIn0 *= in0Lo;
//  absIn1 = 0U;
//  in0Lo = (productLoHi << 16U) + absIn0;
//  if (in0Lo < absIn0) {
//    absIn1 = 1U;
//  }

//  absIn0 = in0Lo;
//  in0Lo += productHiLo << 16U;
//  if (in0Lo < absIn0) {
//    absIn1++;
//  }

//  absIn0 = (((productLoHi >> 16U) + (productHiLo >> 16U)) + in0Hi * in1Hi) +
//    absIn1;
//  if ((in0 != 0) && ((in1 != 0) && ((in0 > 0) != (in1 > 0)))) {
//    absIn0 = ~absIn0;
//    in0Lo = ~in0Lo;
//    in0Lo++;
//    if (in0Lo == 0U) {
//      absIn0++;
//    }
//  }

//  *ptrOutBitsHi = absIn0;
//  *ptrOutBitsLo = in0Lo;
//}

//int32_T mul_s32_loSR(int32_T a, int32_T b, uint32_T aShift)
//{
//  uint32_T u32_chi;
//  uint32_T u32_clo;
//  mul_wide_s32(a, b, &u32_chi, &u32_clo);
//  u32_clo = u32_chi << (32U - aShift) | u32_clo >> aShift;
//  return (int32_T)u32_clo;
//}

/* Model step function */
int32_t FilterAC_s19s29_CG_step_o(int32_t Input)
{
  int32_T rtb_HeadSum1;
  int32_T rtb_HeadSum1_tmp;
	int32_t Output;
	

  /* Sum: '<S1>/HeadSum1' incorporates:
   *  Delay: '<S1>/BodyDelay21'
   *  Inport: '<Root>/Input'
   *  Sum: '<S1>/FootSum1'
   */
  rtb_HeadSum1_tmp = Input << 1;
  rtb_HeadSum1 = (FilterAC_s19s29_CG_DW.BodyDelay21_DSTATE >> 1) +
    rtb_HeadSum1_tmp;

  /* Outport: '<Root>/Output' incorporates:
   *  Sum: '<S1>/HeadSum1'
   */
  Output = rtb_HeadSum1;

  /* Update for Delay: '<S1>/BodyDelay21' incorporates:
   *  Delay: '<S1>/FootDelay1'
   *  Gain: '<S1>/a(2)(1)'
   *  Gain: '<S1>/b(2)(1)'
   *  Inport: '<Root>/Input'
   *  Sum: '<S1>/BodyLSum21'
   *  Sum: '<S1>/BodyRSum21'
   *  Sum: '<S1>/HeadSum1'
   */
  FilterAC_s19s29_CG_DW.BodyDelay21_DSTATE = ((-2 * Input +
    (FilterAC_s19s29_CG_DW.FootDelay1_DSTATE >> 2)) + mul_u18s29sh17(+120847,             //17--
    rtb_HeadSum1/*, 17U*/)) << 2;

  /* Update for Delay: '<S1>/FootDelay1' incorporates:
   *  Gain: '<S1>/a(3)(1)'
   *  Sum: '<S1>/FootSum1'
   *  Sum: '<S1>/HeadSum1'
   */
  FilterAC_s19s29_CG_DW.FootDelay1_DSTATE = (rtb_HeadSum1_tmp - mul_u18s29sh13
    (6937, rtb_HeadSum1/*, 13U*/)) << 1;   
                                                  //13
	return Output;
}

/* Model step function */
//void FilterAC_s19s29_CG_step(void)
//{
//  int32_T rtb_HeadSum1;
//  int32_T rtb_HeadSum1_tmp;

//  /* Sum: '<S1>/HeadSum1' incorporates:
//   *  Delay: '<S1>/BodyDelay21'
//   *  Inport: '<Root>/Input'
//   *  Sum: '<S1>/FootSum1'
//   */
//  rtb_HeadSum1_tmp = FilterAC_s19s29_CG_U.Input << 1;
//  rtb_HeadSum1 = (FilterAC_s19s29_CG_DW.BodyDelay21_DSTATE >> 1) +
//    rtb_HeadSum1_tmp;

//  /* Outport: '<Root>/Output' incorporates:
//   *  Sum: '<S1>/HeadSum1'
//   */
//  FilterAC_s19s29_CG_Y.Output = rtb_HeadSum1;

//  /* Update for Delay: '<S1>/BodyDelay21' incorporates:
//   *  Delay: '<S1>/FootDelay1'
//   *  Gain: '<S1>/a(2)(1)'
//   *  Gain: '<S1>/b(2)(1)'
//   *  Inport: '<Root>/Input'
//   *  Sum: '<S1>/BodyLSum21'
//   *  Sum: '<S1>/BodyRSum21'
//   *  Sum: '<S1>/HeadSum1'
//   */
//  FilterAC_s19s29_CG_DW.BodyDelay21_DSTATE = ((-2 * Input +
//    (FilterAC_s19s29_CG_DW.FootDelay1_DSTATE >> 2)) - mul_s32_loSR(-120847,
//    rtb_HeadSum1, 17U)) << 2;

//  /* Update for Delay: '<S1>/FootDelay1' incorporates:
//   *  Gain: '<S1>/a(3)(1)'
//   *  Sum: '<S1>/FootSum1'
//   *  Sum: '<S1>/HeadSum1'
//   */
//  FilterAC_s19s29_CG_DW.FootDelay1_DSTATE = (rtb_HeadSum1_tmp - mul_s32_loSR
//    (6937, rtb_HeadSum1, 13U)) << 1;
//}



/* Model initialize function */
void FilterAC_s19s29_CG_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(FilterAC_s19s29_CG_M, (NULL));

  /* states (dwork) */
  (void) memset((void *)&FilterAC_s19s29_CG_DW, 0,
                sizeof(DW_FilterAC_s19s29_CG_T));

  /* external inputs */
//  FilterAC_s19s29_CG_U.Input = 0;

  /* external outputs */
//  FilterAC_s19s29_CG_Y.Output = 0;

  /* InitializeConditions for Delay: '<S1>/BodyDelay21' */
  FilterAC_s19s29_CG_DW.BodyDelay21_DSTATE = 0;

  /* InitializeConditions for Delay: '<S1>/FootDelay1' */
  FilterAC_s19s29_CG_DW.FootDelay1_DSTATE = 0;
}

/* Model terminate function */
void FilterAC_s19s29_CG_terminate(void)
{
  /* (no terminate code required) */
}
