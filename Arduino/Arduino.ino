#include <mutex>

#include <Servo.h>

#define DOOR_COUNT 2
const int BUTTON_PINS[] = { 2, 4 };
const int LED_PINS[] = { 3, 5 };
const int SERVO_PINS[] = { 11, 12 };

#define FLASH_DELAY 100
#define MOVE_DELAY 50

#define CLOSED_ANGLE 0
#define OPEN_ANGLE 80

Servo doors[DOOR_COUNT];
volatile bool moving[DOOR_COUNT];
bool closed[DOOR_COUNT];

void setLeds( int state ) {

  for ( const int ledPin : LED_PINS ) {

    digitalWrite( ledPin, state );
    
  }
  
}

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

void openDoor( int doorN ) {

  noInterrupts();
  if ( moving[doorN] || !closed[doorN] ) {
    interrupts();
    return; // Abort.
  }
  moving[doorN] = true;
  interrupts();

  doors[doorN].write( OPEN_ANGLE );
  delay( MOVE_DELAY );

  closed[doorN] = false;
  moving[doorN] = false;
  
}

void closeDoor( int doorN ) {

  noInterrupts();
  if ( moving[doorN] || closed[doorN] ) {
    interrupts();
    return; // Abort.
  }
  moving[doorN] = true;
  interrupts();

  doors[doorN].write( CLOSED_ANGLE );
  delay( MOVE_DELAY );

  closed[doorN] = true;
  moving[doorN] = false;
  
}

void buttonPress( int doorN ) {

  if ( closed[doorN] ) {
    openDoor( doorN );
  } else {
    closeDoor( doorN );
  }
  
}

void setup() {

  for ( int i = 0; i < DOOR_COUNT; i++ ) {

    pinMode( BUTTON_PINS[i], INPUT );
    pinMode( LED_PINS[i], OUTPUT );

    doors[i].attach( SERVO_PINS[i] );
    doors[i].write( CLOSED_ANGLE );

    moving[i] = false;
    closed[i] = true;
    
  }

  // Register button interrupts.
  attachInterrupt( digitalPinToInterrupt( BUTTON_PINS[0] ), []() { buttonPress( 0 ); }, RISING );
  attachInterrupt( digitalPinToInterrupt( BUTTON_PINS[1] ), []() { buttonPress( 1 ); }, RISING );

  flash( 5 );

}

void loop() {

  for ( int i = 0; i < DOOR_COUNT; i++ ) {

    digitalWrite( LED_PINS[i], digitalRead( BUTTON_PINS[i] ) );
    
  }

}
