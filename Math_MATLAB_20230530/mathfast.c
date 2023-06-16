#ifdef __debug__
#include "main.h"
#endif

#include "MathFast.h"
#include "MathSlow.h"
#include "FilterC_s19s29_CG1.h"
#include "FilterAC_s19s29_CG.h"





#if	((D_ADCMODE==2)||(D_ADCMODE==3))	
#define id_factor 1
#define sin1000_len 32
int32_t sin1000[sin1000_len]={     //140dB RMS     
          0/id_factor,
   25167023/id_factor,
   49366891/id_factor,
   71669617/id_factor,
   91218120/id_factor,
  107261162/id_factor,
  119182217/id_factor,
  126523167/id_factor,
  129001902/id_factor,
  126523167/id_factor,
  119182217/id_factor,
  107261162/id_factor,
   91218120/id_factor,
   71669617/id_factor,
   49366891/id_factor,
   25167023/id_factor,
          0/id_factor,
  -25167023/id_factor,
  -49366891/id_factor,
  -71669617/id_factor,
  -91218120/id_factor,
 -107261162/id_factor,
 -119182217/id_factor,
 -126523167/id_factor,
 -129001902/id_factor,
 -126523167/id_factor,
 -119182217/id_factor,
 -107261162/id_factor,
  -91218120/id_factor,
  -71669617/id_factor,
  -49366891/id_factor,
  -25167023/id_factor,
};

#endif


int32_t MF_ADCOverLoad;
uint32_t MF_ADCOverLoad_Flag;
bool catch_flag;
static int32_t	PeakC_max_current;
uint32_t	PeakC_max;


//t_U_MF_int64 MF_U_64_fastAC;
uint32_t Integrator_Hi;
uint32_t IntegratorA_Hi;
static t_U_MF_int64 Integrator;
static t_U_MF_int64 IFA_integrator_Old;
int32_t i32_fastAC;
int32_t i32_fastAAC;
//-------------- output matlab ----------
#ifndef __NO_MATLAB__
uint32_t Integrator_Hi_out;
uint32_t IntegratorA_Hi_out;

int32_t filterCout_M;
int32_t filterAout_M;

uint32_t	MF_ADCOverLoad_Flag_out;
	
#endif


static t_U_MF_int64 IntegratorData;
					
static uint8_t IntegratorIndex;


//void mathtest(void);
//void mathtest_FilterC(void);
//void mathtest_FilterAC(void);
//void fast_init(void);
void fastA_init(void);
void Int_fast_A(void);
inline t_U_MF_int64 fastmulA(int32_t A);
//void mathtest_fast(void);			


//#define D_FASTOLD 1
#define D_FAST_NEW 1
void MF_Int_Init(void)
{
#ifdef __NO_MATLAB__
	NVIC_SetPriority(KEYBRD_IRQn, 1);
  NVIC_EnableIRQ(KEYBRD_IRQn);	
#endif
}
//void KEYBRD_Handler(void)
//{
// Int_fast_A();
//}


void MF_main_init(void)
{
	MF_Int_Init();
//	fast_init();
	fastA_init();
  FilterAC_s19s29_CG_initialize();
	FilterC_s19s29_CG1_initialize();
	catch_flag=false;
	PeakC_max_current=0;
  PeakC_max=0;
	MF_ADCOverLoad=MS_D_AlertLevel_Overload;
	IFA_integrator_Old.u64=Integrator.u64;
	//Integrator_Hi=0;
	
};
void MF_main_reset(void)
{
	Integrator.u64=0;
	Integrator_Hi=0;
	IntegratorA_Hi=0;
	IFA_integrator_Old.u64=0;
};

inline void MF_main(int32_t adcoutput)
{
	int32_t filterCout;
	
  int32_t filterAout;
	
	uint32_t t;
	
	uint64_t square;
	
	if (adcoutput<0) 
		{ t=-adcoutput;}
		else 
		{t=adcoutput;};
	if (t>MF_ADCOverLoad)
	{
	                MF_ADCOverLoad_Flag++;
#ifndef __NO_MATLAB__
	MF_ADCOverLoad_Flag_out=MF_ADCOverLoad_Flag;
#endif		
	};
	
	filterCout=FilterC_s19s29_CG1_step_o(adcoutput);
	
	if (filterCout<0) 
		{ t=-filterCout;}
		else 
		{t=filterCout;};
	if (t>PeakC_max_current)
	                 PeakC_max_current=t;
	
	if (catch_flag) 
	{
	     PeakC_max=PeakC_max_current;
		   PeakC_max_current=0;
       catch_flag=0; 
	}        
	
	filterAout=FilterAC_s19s29_CG_step_o(filterCout);
	
#ifndef __NO_MATLAB__
	filterCout_M=filterCout;
	filterAout_M=filterAout;
#endif
 
#if	(D_ADCMODE!=1)		
	square=MF_sqr(filterAout<<ForIntegratorShift);
#endif	
	
	t=Integrator.u32[1];
	Integrator.u64+=(square);
#ifdef D_FASTOLD	
//---------------------	Integrator_Hi & Fast-------------------------------
	if (t>Integrator.u32[1]) 
  {Integrator_Hi++;
#ifndef __NO_MATLAB__		
	 Integrator_Hi_out=Integrator_Hi;	
#endif		
	};
	
	i32_fastAC=fast(square);
#endif	
	
#ifdef  D_FAST_NEW	
//---------------------	Integrator_Hi & Fast alternative-------------------	
	
	
	if (!((IntegratorIndex++)&IntegratorIndexMask))
	{ IntegratorData.u64=Integrator.u64;
#ifndef __NO_MATLAB__	
		Int_fast_A();//TODO FOR MATLAB
#else
   NVIC_SetPendingIRQ(KEYBRD_IRQn);	
#endif	
	}
#endif	
//-------------------- Interrupt -------------------------------------------	
	
//=========================================================================	
	//fast();//test
	//mathtest();
	//mathtest_FilterC();
	//mathtest_FilterAC();
//	mathtest_fast();
}
;



#if	((D_ADCMODE==2)||(D_ADCMODE==3))	
inline void test_MF_main_ADCEmul(void)
{
	static uint8_t i;
	i++;
	i&=0x1f;
	MF_main(sin1000[i]);
}
#endif



//void test_MF_main(void)
//{
//	while(1)
//	{
//		for(int i=0;i<sin1000_len;i++)
//		{
//			MF_main(sin1000[i]);
//		}
//			for(int i=0;i<sin1000_len;i++)
//		{
//			MF_main(-sin1000[i]);
//		}
//	};
//}

//void mathtest(void)
//{
//const int mi=2;//#define mi 2
//int32_t a[mi]={65536,-65536};
//int32_t k[mi]={1, 1};
//int32_t s[mi]={14, 14};	


//for(int i=0;i<mi;i++)
//{
//	r1[i]=mul_u18s29sh(k[i],a[i],s[i]);
//	r2[i]=mul_s32_loSR(k[i],a[i],s[i]);
//}

//}

//void mathtest_fast(void)
//{
//	for(int i=0;i<sin1000_len;i++)
//	{
//		square=((uint64_t)sin1000[i])*((uint64_t)sin1000[i]);
//		r64[i]=fast(square); 
//		
//	}
//}


//void mathtest_FilterC(void)
//{
//const int mi=2;//#define mi 2
//int32_t a[mi]={65536,-65536};
//	

//FilterC_s19s29_CG1_initialize();
//for(int i=0;i<mi;i++)
//{
//	FilterC_s19s29_CG1_U.Input=a[i];
//  FilterC_s19s29_CG1_step(); 
//	r1[i]=FilterC_s19s29_CG1_Y.Output;
//}
//FilterC_s19s29_CG1_initialize();
//for(int i=0;i<mi;i++)
//{
//	FilterC_s19s29_CG1_U.Input=a[i];
//  FilterC_s19s29_CG1_step_o(); 
//	r2[i]=FilterC_s19s29_CG1_Y.Output;
//}

//}

//void mathtest_FilterAC(void)
//{
//	

//FilterAC_s19s29_CG_initialize();
//for(int i=8;i<sin1000_len;i++)
//{
//	FilterAC_s19s29_CG_U.Input=sin1000[i];
//  FilterAC_s19s29_CG_step(); 
//	r1[i]=FilterAC_s19s29_CG_Y.Output;
//}
//FilterAC_s19s29_CG_initialize();
//for(int i=8;i<sin1000_len;i++)
//{
//	FilterAC_s19s29_CG_U.Input=sin1000[i];
//  FilterAC_s19s29_CG_step_o(); 
//	r2[i]=FilterAC_s19s29_CG_Y.Output;
//}

//}



//int32_t filterC(int32_t in) //for test in matlab
//{
//	FilterC_s19s29_CG1_U.Input=in;
//  FilterC_s19s29_CG1_step_o(); 
//	return FilterC_s19s29_CG1_Y.Output;
//}

//inline int32_t filterAC(int32_t in) //for test in matlab
//{
//	FilterAC_s19s29_CG_U.Input=in;
//  FilterAC_s19s29_CG_step_o(); 
//	return FilterAC_s19s29_CG_Y.Output;
//}

//------------------------ALT fast integrator ---------------------------
static uint64_t fastDelayA;
 t_U_MF_int64 MF_U_64_fastoutouterA;
static t_U_MF_int64 IFA_integrator_Old;


int32_t fastA(uint64_t in);
#ifndef __NO_MATLAB__
void Int_fast_A(void)
#else
void KEYBRD_Handler(void)
#endif
{
// fast	
	uint64_t t;
	
	t=IntegratorData.u64-IFA_integrator_Old.u64;
	
	i32_fastAAC=fastA(t);
// integrator	
	if (IFA_integrator_Old.u32[1]>IntegratorData.u32[1])
		  IntegratorA_Hi++;
	
#ifndef __NO_MATLAB__
IntegratorA_Hi_out=IntegratorA_Hi;
#endif

	IFA_integrator_Old=IntegratorData;
};

void fastA_init(void)
{
  
	MF_U_64_fastoutouterA.i64=0;	
	//MF_U_64_fastoutouterA.i32[1]=100000;
	fastDelayA=MF_U_64_fastoutouterA.u64;
}

inline int32_t fastA(uint64_t in)
{
	t_U_MF_int64 MF_U_64_fastMulResult;
	t_U_MF_int64 MF_U_64_fastoutinner;
	MF_U_64_fastoutinner.i64=(in>>FastInShift)+fastDelayA;
	MF_U_64_fastMulResult=fastmulA(MF_U_64_fastoutouterA.i32[1]);
	fastDelayA=(in>>FastInShift)+(MF_U_64_fastoutouterA.i64-MF_U_64_fastMulResult.i64);	
	MF_U_64_fastoutouterA.i64= MF_U_64_fastoutinner.i64;
#ifdef __debug__
	writetoarray(MF_U_64_fastoutouterA,fastDelayA,MF_U_64_fastoutinner,MF_U_64_fastMulResult);
#endif
	return MF_U_64_fastoutouterA.i32[1];	
}
#define fastFactor (33550)	
//inline
t_U_MF_int64 fastmulA(int32_t A)
{  
t_U_MF_int64 t;
uint32_t r0,r1; 
uint32_t uA;
	if (A<0) 
	{	uA=-A;
		r1=(uA>>16)*fastFactor;
		r0=(uA&0xffff)*fastFactor;
		t.u32[0]=r0<<(5+FastMulAdditionalShift);
		t.u32[1]=(r0>>(32-5-FastMulAdditionalShift))+(r1>>(16-5-FastMulAdditionalShift));
		r1=r1<<(32-(16-5-FastMulAdditionalShift));
		t.i64=-t.i64;
	}
	else
	{ uA=A;
		r1=(uA>>16)*fastFactor;
		r0=(uA&0xffff)*fastFactor;
		t.u32[0]=r0<<(5+FastMulAdditionalShift);
		t.u32[1]=(r0>>(32-5-FastMulAdditionalShift))+(r1>>(16-5-FastMulAdditionalShift));
		r1=r1<<(32-(16-5-FastMulAdditionalShift));
	}
	return t;
};	

////----------------fast-------------------
//uint64_t fastDelay;
//t_U_MF_int64 MF_U_64_fastoutouter;

//void fast_init(void)
//{
//  fastDelay=0;
//	MF_U_64_fastoutouter.i64=0;	
//}

//inline int32_t fast(uint64_t in)
//{
//	t_U_MF_int64 MF_U_64_fastMulResult;
//	t_U_MF_int64 MF_U_64_fastoutinner;
//	MF_U_64_fastoutinner.i64=(in>>FastInShift)+fastDelay;
//	MF_U_64_fastMulResult=fastmul(MF_U_64_fastoutouter.i32[1]);
//	fastDelay=(in>>FastInShift)+(MF_U_64_fastoutouter.i64-MF_U_64_fastMulResult.i64);	
//	MF_U_64_fastoutouter.i64= MF_U_64_fastoutinner.i64;
//	return MF_U_64_fastoutouter.i32[1];	
//}
//#define fastFactor 33550	
//inline t_U_MF_int64 fastmul(int32_t A)
//{ 
//t_U_MF_int64 t;
//uint32_t r0,r1; 
//uint32_t uA;
//	if (A<0) 
//	{	uA=-A;
//		r1=(uA>>16)*fastFactor;
//		r0=(uA&0xffff)*fastFactor;
//		t.u32[0]=r0<<(5);
//		t.u32[1]=(r0>>(32-5))+(r1>>(16-5));
//		r1=r1<<(32-(16-5));
//		t.u64+=r1;		
//		t.i64=-t.i64;
//	}
//	else
//	{ uA=A;
//		r1=(uA>>16)*fastFactor;
//		r0=(uA&0xffff)*fastFactor;
//		t.u32[0]=r0<<(5);
//		t.u32[1]=(r0>>(32-5))+(r1>>(16-5));
//		r1=r1<<(32-(16-5));
//		t.u64+=r1;
//	}
//	return t;
//};


//inline t_U_MF_int64 fastmul64(uint16_t K,int32_t A)
//{ 
//static	t_U_MF_int64 t;
//static	uint64_t r0,r1; //TODO optimize
//static 	uint32_t uA;
//	if (A<0) 
//	{	uA=-A;
//		uA=uA<<1;
//		r1=((uA>>16)*K);
//		r0=(uA&0xffff)*K;
//		//t.num32[0]+=r0<<5;
//		t.num64=(r0<<5)+(r1<<(5+16));
//		t.num64=-t.num64;
//	}
//	else
//	{ uA=A;
//		uA=uA<<1;
//		t.num32[1]=(uA>>16)*K;
//		r0=(uA&0xffff)*K;
//		t.num32[0]=r0<<16;
//		t.num32[1]+=(r0>>16);
//	}
//	return t;
//};

inline int32_T mul_u18s29sh(int32_T a, int32_T b, uint32_T aShift) //aShift=0 ->
{
	int32_T ab;
  uint32_T b_h;
	uint32_T b_l;
//static int32_T A;
//static int32_T B;
//	A=a;
//	B=b;
	if (b>=0)
	{
	b_h = ((uint32_T)b) >> 14;
  b_l = ((uint32_T )b) &	0x3fff;
	ab=( (b_h * a )>>(aShift-14) ) 	+  ( (b_l * a )>> (aShift) );
	}
	else
	{
		b=-b;
	b_h = ((uint32_T)b) >> 14;
  b_l = ((uint32_T )b) &	0x3fff;
	ab=( (b_h * a )>>(aShift-14) )	+ ( (b_l * a )>> (aShift));
	ab=-ab;	
	}
	return ab;
}

inline int32_T mul_u18s29sh17(int32_T a, int32_T b) //aShift=0 ->
{
	int32_T ab;
  uint32_T b_h;
	uint32_T b_l;
//static int32_T A;
//static int32_T B;
//	A=a;
//	B=b;
	if (b>=0)
	{
	b_h = ((uint32_T)b) >> 14;
  b_l = ((uint32_T )b) &	0x3fff;
	ab=( (b_h * a )>>(17-14) ) 	+  ( (b_l * a )>> (17) );
	}
	else
	{
		b=-b;
	b_h = ((uint32_T)b) >> 14;
  b_l = ((uint32_T )b) &	0x3fff;
	ab=( (b_h * a )>>(17-14) )	+ ( (b_l * a )>> (17));
	ab=-ab;	
	}
	return ab;
}



inline int32_T mul_u18s29shl(int32_T a, int32_T b, uint32_T aShift) //aShift=0 ->
{
	int32_T ab;
	uint32_T b_h;
	uint32_T b_l;
//static int32_T A;
//static int32_T B;
//	A=a;
//	B=b;
	if (b>=0)
	{
	b_h = ((uint32_T)b) >> 14;
  b_l = ((uint32_T )b) &	0x3fff;
	ab=( (b_h * a )<<(14-aShift) ) 	+  ( (b_l * a )>> (aShift) );
	}
	else
	{
		b=-b;
	b_h = ((uint32_T)b) >> 14;
  b_l = ((uint32_T )b) &	0x3fff;
	ab=( (b_h * a )<<(14-aShift) )	+ ( (b_l * a )>> (aShift));
	ab=-ab;	
	}
	return ab;
}

inline int32_T mul_u18s29sh12(int32_T a, int32_T b) //aShift=0 ->
{
	int32_T ab;
	uint32_T b_h;
	uint32_T b_l;
//static int32_T A;
//static int32_T B;
//	A=a;
//	B=b;
	if (b>=0)
	{
	b_h = ((uint32_T)b) >> 14;
  b_l = ((uint32_T )b) &	0x3fff;
	ab=( (b_h * a )<<(14-12) ) 	+  ( (b_l * a )>> (12) );
	}
	else
	{
		b=-b;
	b_h = ((uint32_T)b) >> 14;
  b_l = ((uint32_T )b) &	0x3fff;
	ab=( (b_h * a )<<(14-12) )	+ ( (b_l * a )>> (12));
	ab=-ab;	
	}
	return ab;
}

inline uint64_t MF_sqr(int32_T a) //aShift=0 ->
{
	t_U_MF_int64 a2;

	if (a<0)
	         {a=-a;};
	a2.u32[0]=(a&0xffff)*(a&0xffff);
	a2.u32[1]=((a>>16)*(a>>16)); 
  a2.u64+=(((uint64_t)((a&0xffff)*(a>>16)))<<17);
	return a2.u64;
}


inline int32_T mul_u18s29sh13(int32_T a, int32_T b) //aShift=0 ->
{
	int32_T ab;
	uint32_T b_h;
	uint32_T b_l;
//static int32_T A;
//static int32_T B;
//	A=a;
//	B=b;
	if (b>=0)
	{
	b_h = ((uint32_T)b) >> 14;
  b_l = ((uint32_T )b) &	0x3fff;
	ab=( (b_h * a )<<(14-13) ) 	+  ( (b_l * a )>> (13) );
	}
	else
	{
		b=-b;
	b_h = ((uint32_T)b) >> 14;
  b_l = ((uint32_T )b) &	0x3fff;
	ab=( (b_h * a )<<(14-13) )	+ ( (b_l * a )>> (13));
	ab=-ab;	
	}
	return ab;
}


void mul_wide_s32(int32_T in0, int32_T in1, uint32_T *ptrOutBitsHi, uint32_T
                  *ptrOutBitsLo)
{
  uint32_T absIn0;
  uint32_T absIn1;
  uint32_T in0Hi;
  uint32_T in0Lo;
  uint32_T in1Hi;
  uint32_T productHiLo;
  uint32_T productLoHi;
  absIn0 = in0 < 0 ? ~(uint32_T)in0 + 1U : (uint32_T)in0;
  absIn1 = in1 < 0 ? ~(uint32_T)in1 + 1U : (uint32_T)in1;
  in0Hi = absIn0 >> 16U;
  in0Lo = absIn0 & 65535U;
  in1Hi = absIn1 >> 16U;
  absIn0 = absIn1 & 65535U;
  productHiLo = in0Hi * absIn0;
  productLoHi = in0Lo * in1Hi;
  absIn0 *= in0Lo;
  absIn1 = 0U;
  in0Lo = (productLoHi << 16U) + absIn0;
  if (in0Lo < absIn0) {
    absIn1 = 1U;
  }

  absIn0 = in0Lo;
  in0Lo += productHiLo << 16U;
  if (in0Lo < absIn0) {
    absIn1++;
  }

  absIn0 = (((productLoHi >> 16U) + (productHiLo >> 16U)) + in0Hi * in1Hi) +
    absIn1;
  if ((in0 != 0) && ((in1 != 0) && ((in0 > 0) != (in1 > 0)))) {
    absIn0 = ~absIn0;
    in0Lo = ~in0Lo;
    in0Lo++;
    if (in0Lo == 0U) {
      absIn0++;
    }
  }

  *ptrOutBitsHi = absIn0;
  *ptrOutBitsLo = in0Lo;
}

int32_T mul_s32_loSR(int32_T a, int32_T b, uint32_T aShift)//aShift=0 -> only low bits
{
  uint32_T u32_chi;
  uint32_T u32_clo;
  mul_wide_s32(a, b, &u32_chi, &u32_clo);
  u32_clo = u32_chi << (32U - aShift) | u32_clo >> aShift;
  return (int32_T)u32_clo;
}

