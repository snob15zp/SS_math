#include "MathFast.h"
#include "MathSlow.h"

 int i;

int main(void)
{
	
MF_main_init();	
	

 while(1)
 {
//  MS_evalute(1,2,3,4);
  MF_main(0);
  i++;
 };

}
