//the basic avoid white line
#include <Zumo32U4.h>
//#include <ZumoBuzzer.h>
// --- Enums ---

// States. Here we just start out with a couple.
enum State { //?
  pause_state,
  run_state
};

// --- Constants

// What speed to run the motor
const int motorSpeed = 200;

// What value do we count as black?
const int blackColor = 900;

// --- Global Variables ---

Zumo32U4LCD lcd;
Zumo32U4LineSensors lineSensors;
unsigned int lineSensorValues[3]; // Y 3?
Zumo32U4Motors motors;
Zumo32U4ButtonA buttonA;

State state = pause_state;

// --- Setup Function
void setup() {
  // Initialize the line sensors, and turn on the LEDs for them.
  lineSensors.initThreeSensors();
  lineSensors.emittersOn();
}

// --- Main loop function
void loop() {
  // - Read in the values
  lineSensors.read(lineSensorValues);

  // Buttons
  bool buttonPress = buttonA.getSingleDebouncedPress();

  // - Change states
  if(buttonPress && state == pause_state) {
    state = run_state;
  }

  else if(buttonPress && state == run_state) {
    state = pause_state;
  }

  // - Set motor speeds
  if(state == run_state) {
    if(lineSensorValues[0] > blackColor && lineSensorValues[2] < blackColor) { // look up lineSensorValue // if it is greater than black color then it is white
      // There's a line to the left. Veer right.
      motors.setSpeeds(motorSpeed, -motorSpeed);
    }
    else if(lineSensorValues[0] < blackColor && lineSensorValues[2] > blackColor) {
      // There's  line to the right. Veer left.
      motors.setSpeeds(-motorSpeed, motorSpeed);
    } else if(lineSensorValues[0] > blackColor && lineSensorValues[2] > blackColor) {
      // Ok, we are straight in on a line. Back up and spin.
      
      // This 'blocking' so it ignores button pushes, so it isn't possible to 'pause'
      // while doing this. You should code something better.
      motors.setSpeeds(-motorSpeed, -motorSpeed);
      delay(500);
      motors.setSpeeds(-motorSpeed, motorSpeed);
      delay(500);
    } else {
      // No lines. Go forward.
      motors.setSpeeds(motorSpeed, motorSpeed);
    }
  }
  else if(state == pause_state) {
    motors.setSpeeds(0, 0);
  }
  
  // Display the values.
  // Divide by 10 because our screen isn't large.
 lcd.gotoXY(0, 0);
  lcd.print(lineSensorValues[0] / 10);
  lcd.print("  ");

  // Second value
  lcd.gotoXY(5, 0);
  lcd.print(lineSensorValues[1] / 10);
  lcd.print("  ");

  // Third value
  lcd.gotoXY(0, 1);
  lcd.print(lineSensorValues[2] / 10);
  lcd.print("  ");

  // State
  lcd.gotoXY(5, 1);
  lcd.print(state);
  lcd.print("  ");
  delay(2);
}

/*// Sound Effects
ZumoBuzzer buzzer;
const char sound_effect[] PROGMEM = "O4 T100 V15 L4 MS g12>c12>e12>G6>E12 ML>G2"; // "charge" melody
// use V0 to suppress sound effect; v15 for max volume

Zumo32U4Buzzer buzzer;
void loop() 
{
  // Start playing a tone with frequency 440 Hz at maximum
  // volume (15) for 200 milliseconds.
  buzzer.playFrequency(440, 200, 15);

  // Delay to give the tone time to finish.
  delay(1000);

  // Start playing note A in octave 4 at maximum volume
  // volume (15) for 2000 milliseconds.
  buzzer.playNote(NOTE_A(4), 2000, 15);

  // Wait for 200 ms and stop playing note.
  delay(200);
  buzzer.stopPlaying();


  delay(1000);
}*/

/* This example uses the Zumo32U4PrimeBuzzer class to play a
series of notes on the buzzer.

This example demonstrates the use of the playFrequency(),
playNote(), and playFromProgramSpace() functions, which play
entirely in the background, requiring no further action from the
user once the function is called.  The CPU is then free to
execute other code while the buzzer plays.

This example also shows how to use the stopPlaying() function to
stop the buzzer, and it shows how to use the isPlaying() function
to tell whether the buzzer is still playing or not. */

//#include <Wire.h>
//#include <Zumo32U4.h>
////#include <PololuBuzzer.h>

Zumo32U4Buzzer buzzer;

// Store this song in program space using the PROGMEM macro.
// Later we will play it directly from program space, bypassing
// the need to load it all into RAM first.
const char fugue[] PROGMEM =
  "O4 T100 V15 L4 MS g12>c12>e12>G6>E12 ML>G2"; // charge

  //" ! O5 L07 >c# >c# g# g# g# g# f# e f# g# g# >c# >c# g# g# g# f# e f# g# g# g# g# g# b"
  //"b >c# g# g# g# g# b b >c# g# g# g# f# e e g# f# e e e e e"
  //"! O5 L10 " 
  //"cdefgab>c >cbagfedc"
  //"! O5 L07 ccggaagg ffeeddc aaggffee aaggffee ccggaagg ffeeddc";
  //"! O5 L16 agafaea dac+adaea fa<aa<bac#a dac#adaea f"
//  "O6 dcd<b-d<ad<g d<f+d<gd<ad<b- d<dd<ed<f+d<g d<f+d<gd<ad"
//  "L8 MS <b-d<b-d MLe-<ge-<g MSc<ac<a ML d<fd<f O5 MS b-gb-g"
//  "ML >c#e>c#e MS afaf ML gc#gc# MS fdfd ML e<b-e<b-"
//  "O6 L16ragafaea dac#adaea fa<aa<bac#a dac#adaea faeadaca"
//  "<b-acadg<b-g egdgcg<b-g <ag<b-gcf<af dfcf<b-f<af"
//  "<gf<af<b-e<ge c#e<b-e<ae<ge <fe<ge<ad<fd"
//  "O5 e>ee>ef>df>d b->c#b->c#a>df>d e>ee>ef>df>d"
//  "e>d>c#>db>d>c#b >c#agaegfe f O6 dc#dfdc#<b c#4";

void setup()       // run once, when the sketch starts
{
}

void loop()        // run over and over again
{
  // Start playing a tone with frequency 440 Hz at maximum
  // volume (15) for 200 milliseconds.
  buzzer.playFrequency(440, 200, 1);

  // Delay to give the tone time to finish.
  //delay(1000);
  delay(200);

  // Start playing note A in octave 4 at maximum volume
  // volume (15) for 2000 milliseconds.
  //buzzer.playNote(NOTE_A(4), 2000, 15);
  buzzer.playNote(NOTE_A(4), 200, 1);

  // Wait for 200 ms and stop playing note.
  delay(200);
  buzzer.stopPlaying();

  //delay(1000);
  delay(200);

  // Start playing a fugue from program space.
  buzzer.playFromProgramSpace(fugue);

  // Wait until it is done playing.
  while(buzzer.isPlaying()){ }

  //delay(1000);
  delay(200);
}
