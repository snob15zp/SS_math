#include "MathFast.h"
#include "MathSlow.h"

 int main_i;

#define ADCclock 31250
#define D_DARow 375
#define D_main_i_min (1.117*ADCclock)
#define D_main_i_max (1.213*ADCclock)
const uint32_t C_DARow=D_main_i_max-D_main_i_min;

t_U_MF_int64 DebugArray[D_DARow+2][5]; 

int main(void)
{
	
MF_main_init();	
	

while(1)
 {
//  MS_evalute(1,2,3,4);
  MF_main(0);
  main_i++;
 };

}

uint16_t DAcount;

void writetoarray(t_U_MF_int64 v1,uint64_t  v2, t_U_MF_int64 v3, t_U_MF_int64 v4 )
{

	if ((main_i>D_main_i_min)&&(main_i<D_main_i_max)&&(DAcount<D_DARow))
	{
		DebugArray[DAcount][0].u64=main_i;
		DebugArray[DAcount][1]=v1;
		DebugArray[DAcount][2].u64=v2;
		DebugArray[DAcount][3]=v3;
		DebugArray[DAcount][4]=v4;		
		
		
		
		DAcount++;
	}	


};