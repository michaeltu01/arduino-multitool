unsigned int WDT_INT = 0;

/* Get next unused CPU interrupt > start */
unsigned int getNextCPUINT(unsigned int start) {
   unsigned int tryInt = start + 1;
      while (tryInt < 32) {
         if (NVIC_GetEnableIRQ((IRQn_Type) tryInt) == 0) {
            return tryInt;
         }
      tryInt++;
   }
}

/* Initialize the WDT peripheral */
void initWDT() {
  WDT_INT = getNextCPUINT(1);
  // TODO step 3 (prelab Qs6.1-6.2)
  // Remember to use a 100% refresh window, unlike the prelab!
  R_WDT->WDTCR = (R_WDT->WDTCR & ~(R_WDT_WDTCR_CKS_Msk | R_WDT_WDTCR_TOPS_Msk)) 
                    | (0b11 << R_WDT_WDTCR_RPES_Pos)
                    | (0b11 << R_WDT_WDTCR_RPSS_Pos) 
                    | (0b1000 << R_WDT_WDTCR_CKS_Pos)
                    | (0b10 << R_WDT_WDTCR_TOPS_Pos);

  // Enable WDT when debugger is connected
  R_DEBUG->DBGSTOPCR_b.DBGSTOP_WDT = 0;
  R_WDT->WDTSR = 0; // clear watchdog status;

  // TODO step 3 (prelab Qs6.4-6.5): Make the watchdog trigger an interrupt
  // and use the ICU to connect it to the CPU
  // Make sure to call the correct CMSIS functions as well!
  R_WDT->WDTRCR &= (0b1 << 7);
  R_ICU->IELSR[WDT_INT] = (0x025 << R_ICU_IELSR_IELS_Pos);

  // CMSIS
  NVIC_SetVector((IRQn_Type) WDT_INT, (uint32_t) &wdtISR); // set vector entry to our handler
  NVIC_SetPriority((IRQn_Type) WDT_INT, 14); // Priority lower than Serial (12)
  NVIC_EnableIRQ((IRQn_Type) WDT_INT);
}

/* pet the watchdog */
void petWDT() {
  // TODO step 3 (prelab Q6.3)
  R_WDT->WDTRR = 0x00;
  R_WDT->WDTRR = 0xFF;
}

/* ISR when WDT triggers */
void wdtISR() {
  Serial.println("WOOF!!!");
  while(true);
}