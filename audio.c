#define AUDIO_BASE 0xFF203040
#define SW 0xff200040

int main(void) {
  volatile int* audio_ptr = (int*) AUDIO_BASE;
  volatile int* sw = (int*) SW;
  int left, right, fifospace;

  // Define constants
  const int SAMPLE_RATE = 8000;  // Audio sample rate in Hz
  const int AUDIBLE_RANGE_MIN = 100;  // Minimum audible frequency in Hz
  const int AUDIBLE_RANGE_MAX = 2000;  // Maximum audible frequency in Hz
  const int NUM_SWITCHES = 10;
  const int FREQUENCY_STEPS = (AUDIBLE_RANGE_MAX - AUDIBLE_RANGE_MIN) / NUM_SWITCHES;

  // Initialize variables
  int sample_count = 0;
  int duty_cycle = 50; // 50% duty cycle for square wave
	int toggle_counter = 0;
	int toggle_val = 0;

  while (1) {

    // Initialize frequency with minimum frequency
    int frequency = AUDIBLE_RANGE_MIN;

    // Read switch states
    int sw_state = *(sw);

    // Update frequency based on pressed switches. Works for a single switch press
    for (int i = 0; i < NUM_SWITCHES; i++) {
        if (sw_state & (1 << i)) { // If switch is pressed, update frequency
            frequency = AUDIBLE_RANGE_MIN + i * FREQUENCY_STEPS;
            break;
        }
    }

	  int sample;
	  
	  if(toggle_counter == 100){
		  printf("toggled\n");
	  if(toggle_val == 1) toggle_val =0;
		  else toggle_val =1;
		  toggle_counter = 0;
	  }
	  toggle_counter++;
	  if(toggle_val == 0){
		  duty_cycle = 20;
		  // Generate square wave sample
		       sample = (sample_count % (SAMPLE_RATE / frequency) < (duty_cycle / 100.0 * (SAMPLE_RATE / frequency))) ? 0xFFFF : 0; 

	  } else {
		  		  duty_cycle = 70;

		  // Generate square wave sample
		     sample = (sample_count % (SAMPLE_RATE / frequency) < (duty_cycle / 100.0 * (SAMPLE_RATE / frequency))) ? 0xFFFF : 0; 
  
	  }
   
    // Write sample to left and right channels
    *(audio_ptr + 2) = sample;
    *(audio_ptr + 3) = sample;

    // Increment sample counter
    sample_count++;

    fifospace = *(audio_ptr + 1); // read the audio port fifospace register
     if((fifospace & 0x000000FF) > 0){
            left = *(audio_ptr + 2); // Read the left channel input data
            right = *(audio_ptr + 3); // Read the right channel input data

            *(audio_ptr + 2) = right; // Write the right channel input data to the left channel
            *(audio_ptr + 3) = left; // Write the left channel input data to the right channel
     } // sound is coming out
}

  return 0;
}
