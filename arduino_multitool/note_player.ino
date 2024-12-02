/*

  note_player.ino

  Main file for note player mode.

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
volatile int intcount;
const int CLOCKFREQ = 3000000;
unsigned int TIMER_INT;
// TODO step 2: configure port and pin for Arduino D4
const int OUT_PORT = 1;
const int OUT_PIN = 06;
void notePlayerSetup() {
  Serial.begin(9600);
  while (!Serial);

  // Grab some *unused* CPU interrupts
  TIMER_INT = getNextCPUINT(1);
  // WDT_INT = getNextCPUINT(TIMER_INT);
  // NOTE_INT = getNextCPUINT(WDT_INT);

  analogWriteResolution(10);

  // TODO step 2: Set piezo speaker as output (refer to lab 3 as needed)
  R_PFS->PORT[OUT_PORT].PIN[OUT_PIN].PmnPFS_b.PDR = 1;

  // TODO step 2: uncomment to parse song
  
  // songLen = rtttlToBuffers(song, noteFrequencies, noteDurations);
  // if (songLen == -1) {
  //   Serial.println("ERROR PARSING SONG!");
  //   while(true);
  // }

  initGPT();
  Serial.println("GPT initialized!");
  
  intcount = 0; // for testing notes
  // TODO step 2: comment out once done testing
  // testAllNotes();

  // TODO step 3: uncomment for WDT
  // initWDT();
  // pet WDT once to start the peripheral
  // petWDT();
}


void initGPT() {
  R_MSTP->MSTPCRD_b.MSTPD6 = 0; // Enable GPT peripheral
  // Make sure the count isn't started
  R_GPT2->GTCR_b.CST = 0;
  // Make sure nobody else can start the count (see 22.2.5 and 22.2.6)
  R_GPT2->GTSSR = (1 << R_GPT0_GTSSR_CSTRT_Pos); // only started w/ software
  R_GPT2->GTPSR = (1 << R_GPT0_GTPSR_CSTOP_Pos); // only stopped w/ software

  // TODO step 1 (Prelab Q5.1): Divide the GPT2 clock
  // IMPORTANT: because of a versioning issue between Arduino and Renesas, use the actual bit position *number* from the datasheet
  // instead of the field name macro defined in the header file
  // See https://github.com/arduino/ArduinoCore-renesas/issues/354 for more info
  R_GPT2->GTCR = 0b010 << 24;

  // Disable GPT interrupt on ICU for now
  R_ICU->IELSR[TIMER_INT] = 0;
  // Use the Arm CMSIS API to enable CPU interrupts
  // (overall GPT interrupt is enabled only when notes play; see playNote)
  NVIC_SetVector((IRQn_Type) TIMER_INT, (uint32_t) &gptISR); // set vector entry to our handler
  NVIC_SetPriority((IRQn_Type) TIMER_INT, 14); // Priority lower than Serial (12)
  NVIC_EnableIRQ((IRQn_Type) TIMER_INT);

  // // TODO step 4:
  // initNoteGPT();
}

/*
 * Sets configures GPT2 interrupt to play note at desired frequency
 * Non-blocking: note can play while program executes
 */
void playNote(int freq) {
  // Turn off counting while configuring
  R_GPT2->GTCR_b.CST = 0;

  // TODO step 1: Configure GPT2 to count to correct n
  // Reference prelab Q3.1 for calculation of n
  // Reference prelab Q5.2 for the GPT2 register
  // Remember that the clock frequency is stored in the constant CLOCKFREQ
  R_GPT2->GTPR = CLOCKFREQ/(2*freq);

  // TODO step 1 (Prelab Q5.4):
  // Configure the ICU to connect the GPT interrupt to the CPU interrupt to enable interrupt
  R_ICU->IELSR[TIMER_INT] = (0x06d << R_ICU_IELSR_IELS_Pos);

  // TODO step 1: re-enable the GPT count
  R_GPT2->GTCR_b.CST = 1;
}

/* Stop playing a note */
void stopPlay() {
  // TODO step 1: Turn off GPT counter and disable CPU interrupt via ICU
  R_GPT2->GTCR_b.CST = 0;
  R_ICU->IELSR[TIMER_INT] = 0;
  
  // TODO step 2: Turn off pin
  R_PFS->PORT[OUT_PORT].PIN[OUT_PIN].PmnPFS_b.PODR = 0;
}

/*
 * Play a given note for a given duration (a frequency of 0 is a rest, i.e. no sound should play for the duration)
 * Blocking: everything except interrupts will have to wait for this function
 */
void playNoteDuration(int freq, int durMillis) {
  // TODO step 1: use playNote and stopPlay to write this function
  if (freq != 0){
    playNote(freq);
  }
  delay(durMillis);
  stopPlay();
}

/* ISR that toggles a GPIO pin low/high at a configuered frequency */
void gptISR() {
  // intcount++; // USED FOR TESTING: DO NOT REMOVE

  // TODO step 2: Toggle output pin (use lab3 as reference if needed)
  R_PFS->PORT[OUT_PORT].PIN[OUT_PIN].PmnPFS_b.PODR ^= 1;

  // TODO step 1: restart count
  R_GPT2->GTCR_b.CST = 1;
  // TODO step 1: clear interrupt on MCU and CPU side (just like in Lab 3)
  R_ICU->IELSR_b[TIMER_INT].IR = 0;
  NVIC_ClearPendingIRQ((IRQn_Type) TIMER_INT);
}


void notePlayingLoop() {
  // TODO step 2: play a song
  // one call of loop() = one note of song played
  // player should pause for 2 seconds before resuming song
  // playNoteDuration(440, 100000);
  tone(D6, 440);
  // counter++;
  // if(counter == songLen){
  //   counter = 0;
  //   delay(20000);
  // }
  // // // TODO step 3: pet the watchdog
  // petWDT();

  // TODO step 4: comment out the body of this function (or just put a return at the beginning)
}
