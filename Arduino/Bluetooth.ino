#include <cstdio>
#include <CurieBLE.h>

#define CONNECTION_BUTTON_PIN 6
#define CONNECTION_LED_PIN 7

#define COUNT_UUID "b4fe2d08-1a07-42bc-bddc-3c0aef4874c6"
#define CLOSED_UUID_BASE "32191b92-68a4-4c63-a990-5995c5ba2"
#define TOGGLE_UUID_BASE "ccd1dc5a-c16b-4969-8372-92094b3af"

BLEPeripheral blePeripheral; // This device.

BLEService drawerService( "3205de0b-9f88-4f82-9fa4-590fac4fd4ef" );
BLEIntCharacteristic countCharacteristic( COUNT_UUID, BLERead );
BLECharCharacteristic * closedCharacteristic[DOOR_COUNT];
BLECharCharacteristic * toggleCharacteristic[DOOR_COUNT];

char * getUUID( String base, int n ) {

  char * buf = (char *) malloc( ( base.length() + 3 + 1 ) * sizeof( char ) );
  sprintf( buf, "%s%03d", base.c_str(), n );
  return buf;
  
}

void enableBt() {

  blePeripheral.setLocalName( "Controllable Drawer" );
  blePeripheral.setAdvertisedServiceUuid( drawerService.uuid() );

  // Register service and count.
  blePeripheral.addAttribute( drawerService );
  blePeripheral.addAttribute( countCharacteristic );
  countCharacteristic.setValue( DOOR_COUNT );

  for ( int i = 0; i < DOOR_COUNT; i++ ) {

    char * closedUUID = getUUID( CLOSED_UUID_BASE, i );
    char * toggleUUID = getUUID( TOGGLE_UUID_BASE, i );
    closedCharacteristic[i] = new BLECharCharacteristic( closedUUID, BLERead | BLENotify );
    toggleCharacteristic[i] = new BLECharCharacteristic( toggleUUID, BLEWrite );
    free( closedUUID );
    free( toggleUUID );

    // Register characteristics.
    blePeripheral.addAttribute( *( closedCharacteristic[i] ) );
    blePeripheral.addAttribute( *( toggleCharacteristic[i] ) );

    // Set initial values.
    closedCharacteristic[i]->setValue( closed[i] ? 1 : 0 );
    toggleCharacteristic[i]->setValue( 0 );
    
  }

  // Begin advertising BLE service.
  blePeripheral.begin();
  
}

void refresh() {

  BLECentral central = blePeripheral.central();
  if ( central ) {

    for ( int i = 0; i < DOOR_COUNT; i++ ) {

      if ( ( closedCharacteristic[i]->value() != 0 ) != closed[i] ) {
        closedCharacteristic[i]->setValue( closed[i] ? 1 : 0 );
      }
      
      if ( toggleCharacteristic[i]->value() != 0 ) {
        shouldToggle[i] = true;
        toggleCharacteristic[i]->setValue( false );
      }
      
    }
    
  }
  
}

