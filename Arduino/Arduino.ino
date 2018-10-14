#include <Servo.h>

#define DOOR_COUNT 2
const int BUTTON_PINS[] = { 2, 4 };
const int LED_PINS[] = { 3, 5 };
const int SERVO_PINS[] = { 11, 12 };

#define FLASH_DELAY 100
#define MOVE_DELAY 10
#define MOVE_INCREMENT 1

#define CLOSED_ANGLE 0
#define OPEN_ANGLE 30

Servo doors[DOOR_COUNT];
volatile bool shouldToggle[DOOR_COUNT];
bool closed[DOOR_COUNT];

/*
 * Sets the state of the LEDs in the board.
 * 
 * state - The state to set the LEDs to.
 */
void setLeds( int state ) {

  for ( const int ledPin : LED_PINS ) {

    digitalWrite( ledPin, state );
    
  }
  
}

/*
 * Flashes all the LEDs in the board.
 * 
 * n - The amount of times to flash.
 */
void flash( int n ) {

  for ( int i = 0; i < n; i++ ) {

    setLeds( HIGH );
    delay( FLASH_DELAY );
    setLeds( LOW );

    if ( i < n - 1 ) {
      delay( FLASH_DELAY );
    }

  }
  
}

/*
 * Opens a door.
 * 
 * doorN - The number of the door to open.
 */
void openDoor( int doorN ) {

  if ( !closed[doorN] ) {
    return; // Abort.
  }

  doors[doorN].attach( SERVO_PINS[doorN] );
  for ( int i = CLOSED_ANGLE + 1; i <= OPEN_ANGLE; i += MOVE_INCREMENT ) {  

    doors[doorN].write( i );
    delay( MOVE_DELAY );
    
  }
  doors[doorN].detach();

  digitalWrite( LED_PINS[doorN], HIGH );
  closed[doorN] = false;
  
}

/*
 * Closes a door.
 * 
 * doorN - The number of the door to close.
 */
void closeDoor( int doorN ) {

  if ( closed[doorN] ) {
    return; // Abort.
  }

  doors[doorN].attach( SERVO_PINS[doorN] );
  for ( int i = OPEN_ANGLE - 1; i >= CLOSED_ANGLE; i -= MOVE_INCREMENT ) {
    
    doors[doorN].write( i );
    delay( MOVE_DELAY );
    
  }
  doors[doorN].detach();

  digitalWrite( LED_PINS[doorN], LOW );
  closed[doorN] = true;
  
}

/*
 * Handles a button press, by toggling the state of a door.
 * 
 * doorN - The door associated to the pressed button.
 */
void buttonPress( int doorN ) {

  shouldToggle[doorN] = true;
  
}

/*
 * Sets up the enviroment.
 */
void setup() {

  for ( int i = 0; i < DOOR_COUNT; i++ ) {

    pinMode( BUTTON_PINS[i], INPUT );
    pinMode( LED_PINS[i], OUTPUT );

    doors[i].attach( SERVO_PINS[i] );
    doors[i].write( CLOSED_ANGLE );
    doors[i].detach();

    shouldToggle[i] = false;
    closed[i] = true;
    
  }

  enableBt(); // Start bluetooth module.

  // Register button interrupts.
  attachInterrupt( digitalPinToInterrupt( BUTTON_PINS[0] ), []() { buttonPress( 0 ); }, RISING );
  attachInterrupt( digitalPinToInterrupt( BUTTON_PINS[1] ), []() { buttonPress( 1 ); }, RISING );

  flash( 5 );

}

/*
 * Keeps the LEDs aligned with the state of the associated buttons.
 */
void loop() {

  for ( int i = 0; i < DOOR_COUNT; i++ ) {

    if ( shouldToggle[i] ) {
      if ( closed[i] ) {
        openDoor( i );
      } else {
        closeDoor( i );
      }
      shouldToggle[i] = false;
    }
    
  }

  refresh(); // Update bluetooth state.

}
