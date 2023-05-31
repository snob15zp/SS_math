#include <math.h>
#include "MathFast.h"
#include "MathSlow.h"


#define D_LogLevelA_offset 0
#define  D_LogLevelC_offset	0
#define  D_LogLevelIntegrator_offset 0

#ifdef __NO_MATLAB__
t_SSS_s_timeevent MS_Ovrload_time_event;
#endif

bool MS_b_alert_C140dBPeak;
bool MS_b_alert_FastA;
bool MS_b_alert_live;
bool MS_b_alert_Overload;
bool MS_b_alert_DoseM3dB;	
bool MS_b_alert_Dose;
bool MS_b_alert_hearing;

float MS_d_offset_FastA_dB;  //0.1dB
float MS_d_offset_Dose_dB;   //0.1dB 
float MS_d_offset_C_Peak_dB; //0.1dB

//MS_i32_CalibrationFactor=MS_D_CalibrationFactor;
//MS_i32_AlertLevel_C140dB_Peak=MS_D_AlertLevel_C_140bB_peak;//filterC bits
//MS_i32_AlertLevel_Cbits_Peak=153144400;	
//MS_i32_AlertLevel_FastA=(MS_D_AlertLevel_FastA);	
//MS_i32_AlertLevel_Dose=(MS_D_AlertLevel_Dose);//0.1dB


//int32_t MS_i32_AlertLevel_C140dB_Peak=MS_D_AlertLevel_C_140bB_peak;//filterC 0.1 dB
int32_t MS_i32_AlertLevel_Cbits_Peak=153144400;//filterC bits
int32_t MS_i32_AlertLevel_FastA=(MS_D_AlertLevel_FastA);//0.1dB
//extern int32_t MS_i32_AlertLevel_Overload;//ADC bits
int32_t MS_i32_AlertLevel_Dose=(MS_D_AlertLevel_Dose);//0.1dB
int32_t MS_i32_AlertLevel_DoseM3dB=((MS_D_AlertLevel_Dose)-(MS_D_AlertZone));//0.1dB;

int32_t MS_i32_Level_C_Peak_dB;//0.1dB
int32_t MS_i32_Level_FastA_dB;//0.1dB
int32_t MS_i32_Level_Dose_dB;//0.1dB

int32_t MS_i32_CalibrationFactor=MS_D_CalibrationFactor;
float MS_d_CalibrationFactor;

// for catch
uint32_t MS_Integrator_Hi_out;
int32_t MS_i32_fastAC;

#ifndef __NO_MATLAB__
uint32_t MS_couter;
uint32_t MS_matlab_time;
uint32_t MS_matlab_time_out;

int32_t MS_i32_Level_C_Peak_dB_out;//0.1dB
int32_t MS_i32_Level_FastA_dB_out;//0.1dB
int32_t MS_i32_Level_Dose_dB_out;//0.1dB

bool MS_b_alert_C140dBPeak_out;
bool MS_b_alert_FastA_out;
#endif

#ifdef __NO_MATLAB__
void MS_main(void)
{
	MS_catch();
	MS_evalute(PeakC_max,MS_i32_fastAC,MS_Integrator_Hi_out,systick_time);
}
#endif

void MS_evalute(uint32_t c, int32_t a, uint32_t i,uint32_t t)
{
 MS_EvaluteLogLevel_A(c,a,i);
 MS_Alerts(t);	
}


void MS_catch(void)
{
	#ifndef __NO_MATLAB__
	MS_matlab_time++;
	MS_matlab_time_out=MS_matlab_time;
	if ((++MS_couter)==4000)//TODO
	{ MS_couter=0;
	#endif

	catch_flag=true;
	MS_Integrator_Hi_out=IntegratorA_Hi;
	MS_i32_fastAC=i32_fastAAC;
	#ifndef __NO_MATLAB__
	};
	#endif
	
}
	
void MS_EvaluteLogLevel(void)
{
	MS_EvaluteLogLevel_A(PeakC_max,MS_i32_fastAC,MS_Integrator_Hi_out);
}

uint32_t MF_ADCOverLoad_Flag_old;
//uint32_t MF_ADCOverLoad_Flag_time;

void MS_EvaluteLogLevel_A(uint32_t c, int32_t a, uint32_t i)
{

MS_i32_Level_FastA_dB=  /*MS_D_dBscale*/(100.0*log10(a) + MS_d_offset_FastA_dB); //0.1dB *MS_D_dBscale
MS_i32_Level_Dose_dB=   /*MS_D_dBscale*/(100.0*log10(i) + (MS_d_offset_Dose_dB));	//0.1dB *MS_D_dBscale
MS_i32_Level_C_Peak_dB= /*MS_D_dBscale*/(200.0*log10(c) + MS_d_offset_C_Peak_dB);//0.1dB *MS_D_dBscale
#ifndef __NO_MATLAB__	
MS_i32_Level_C_Peak_dB_out=MS_i32_Level_C_Peak_dB;//0.1dB
MS_i32_Level_FastA_dB_out=MS_i32_Level_FastA_dB;//0.1dB
MS_i32_Level_Dose_dB_out=MS_i32_Level_Dose_dB;//0.1dB	
#endif	
}	

void MS_Alerts(uint32_t time)
{
	MS_b_alert_FastA=(MS_i32_Level_FastA_dB>MS_i32_AlertLevel_FastA);
	MS_b_alert_C140dBPeak=(PeakC_max>MS_i32_AlertLevel_Cbits_Peak);
	MS_b_alert_live=MS_b_alert_FastA||MS_b_alert_C140dBPeak;
	
#ifndef __NO_MATLAB__
MS_b_alert_FastA_out=MS_b_alert_FastA;
MS_b_alert_C140dBPeak_out=MS_b_alert_C140dBPeak;
#endif

#ifdef __NO_MATLAB__	
	if (MF_ADCOverLoad_Flag_old!=MF_ADCOverLoad_Flag)
	{ 
		MF_ADCOverLoad_Flag_old=MF_ADCOverLoad_Flag;
		SSS_SetUpTimeEvent(&MS_Ovrload_time_event,MF_ADCOverLoad_Flag_duration_US);
	}
	MS_b_alert_Overload=false;
	if (MS_Ovrload_time_event.enable)
	{	MS_b_alert_Overload=true;
		if (systick_time-MS_Ovrload_time_event.time>MS_Ovrload_time_event.dtime)
			MS_Ovrload_time_event.enable=false;
	}
#endif
	
	MS_b_alert_DoseM3dB=(MS_i32_Level_Dose_dB>(MS_i32_AlertLevel_DoseM3dB));
	
	MS_b_alert_Dose=(MS_i32_Level_Dose_dB>MS_i32_AlertLevel_Dose);
	
};





//void MS_test_EvaluteLogLevel(void)
//{
//	EvaluteLogLevel(121,1092782150);
//}


#define D_PeakFactor 15.31443999
//void MS_SetUpDefaultValue(void)
//{
//	
//MS_i32_CalibrationFactor=MS_D_CalibrationFactor;
//MS_i32_AlertLevel_C140dB_Peak=MS_D_AlertLevel_C_140bB_peak;//filterC bits
//MS_i32_AlertLevel_Cbits_Peak=153144400;	
//MS_i32_AlertLevel_FastA=(MS_D_AlertLevel_FastA);	
//MS_i32_AlertLevel_Dose=(MS_D_AlertLevel_Dose);//0.1dB
////0.1dB
////MS_i32_AlertLevel_Overload=MS_D_AlertLevel_Overload;//ADC bits
//}
	

void MS_init(void)
{
	float cflog;
	
MS_d_CalibrationFactor=((float)MS_i32_CalibrationFactor)/((float)(MS_D_CalibrationFactor));	

//MS_i32_AlertLevel_Cbits_Peak=powf(10,((float)MS_i32_AlertLevel_C140dB_Peak)/(200.0))
//	                           *D_PeakFactor/MS_d_CalibrationFactor;	
	
//MS_i32_AlertLevel_DoseM3dB=MS_i32_AlertLevel_Dose-MS_D_AlertZone;//0.1dB	

cflog=100.0*log10(MS_d_CalibrationFactor);

MS_d_offset_FastA_dB=MS_D_offset_FastA_dB+cflog;  //0.1dB
MS_d_offset_Dose_dB=MS_D_offset_Dose_dB+cflog;   //0.1dB 
MS_d_offset_C_Peak_dB=MS_D_offset_C_Peak_dB+2.0*cflog; //0.1dB	


MS_b_alert_C140dBPeak=false;
MS_b_alert_FastA=false;
MS_b_alert_live=false;	
MS_b_alert_Overload=false;
MS_b_alert_DoseM3dB=false;	
MS_b_alert_Dose=false;


MS_i32_Level_C_Peak_dB=0;//0.1dB
MS_i32_Level_FastA_dB=0;//0.1dB
MS_i32_Level_Dose_dB=0;//0.1dB
// for catch
MS_Integrator_Hi_out=0;
MS_i32_fastAC=0;

#ifndef __NO_MATLAB__
MS_couter=0;
MS_matlab_time=0;

//MS_b_alert_FastA_out=0;
//MS_b_alert_C140dBPeak_out=0;
#endif	
};
