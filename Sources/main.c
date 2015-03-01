#include "main.h"

extern byte rowsC;

void main(void) {
  /* put your own code here */
  
  INIT_PLL(PLL80);
  initSCI();
  initPort();
  initOv7620();
	EnableInterrupts;
  
  for(;;){
    if(rowsC){
      PORTB = ~PORTB;
      sendPicture();    
    }  
  }
}
