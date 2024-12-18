unsigned int WDT_INT = 0;

/*
   Function to get the next unused CPU interrupt and return it.
   Inputs: 
      start: the interrupt number to start trying from
   Output: the lowest unused CPU interrupt
*/
unsigned int getNextCPUINT(unsigned int start) {
   unsigned int tryInt = start + 1;
      while (tryInt < 32) {
         if (NVIC_GetEnableIRQ((IRQn_Type) tryInt) == 0) {
            return tryInt;
         }
      tryInt++;
   }
}

/*
   Function to initialize the WDT peripheral.
   Inputs: None
   Output: None
*/
void initWDT() {
  WDT_INT = getNextCPUINT(1);
  R_WDT->WDTCR = (R_WDT->WDTCR & ~(R_WDT_WDTCR_CKS_Msk | R_WDT_WDTCR_TOPS_Msk)) 
                    | (0b11 << R_WDT_WDTCR_RPES_Pos)
                    | (0b11 << R_WDT_WDTCR_RPSS_Pos) 
                    | (0b1000 << R_WDT_WDTCR_CKS_Pos)
                    | (0b10 << R_WDT_WDTCR_TOPS_Pos);

  // Enable WDT when debugger is connected
  R_DEBUG->DBGSTOPCR_b.DBGSTOP_WDT = 0;
  R_WDT->WDTSR = 0; // clear watchdog status;

  R_WDT->WDTRCR &= (0b1 << 7);
  R_ICU->IELSR[WDT_INT] = (0x025 << R_ICU_IELSR_IELS_Pos);

  // CMSIS
  NVIC_SetVector((IRQn_Type) WDT_INT, (uint32_t) &wdtISR); // set vector entry to our handler
  NVIC_SetPriority((IRQn_Type) WDT_INT, 14); // Priority lower than Serial (12)
  NVIC_EnableIRQ((IRQn_Type) WDT_INT);
}

/*
   Function to pet the watchdog.
   Inputs: None
   Output: None
*/
void petWDT() {
  R_WDT->WDTRR = 0x00;
  R_WDT->WDTRR = 0xFF;
}

/*
   ISR to run when the watchdog triggers. Will hang the code indefinitely.
   Inputs: None
   Output: None
*/
void wdtISR() {
  Serial.println("WOOF!!!");
  while(true);
}