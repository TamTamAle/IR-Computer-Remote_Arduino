#define DECODE_NEC          // Includes Apple and Onkyo

#include <Arduino.h>

#include "PinDefinitionsAndMore.h"

#include <IRremote.h>

void setup() {
    Serial.begin(9600);

    /*
     * Start the receiver, enable feedback LED and take LED feedback pin from the internal boards definition
     */
    IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK, USE_DEFAULT_FEEDBACK_LED_PIN);

    Serial.print(F("Ready to receive IR signals at pin "));
    Serial.println(IR_RECEIVE_PIN); //Pin 2
    pinMode(11,OUTPUT);
    pinMode(10,INPUT);
    digitalWrite( 11, HIGH);
    digitalWrite( 10, LOW);
}

void loop() {
    if (IrReceiver.decode()) {

        // Print a short summary of received data
        IrReceiver.printIRResultShort(&Serial);
        if (IrReceiver.decodedIRData.protocol == UNKNOWN) {
            // We have an unknown protocol here, print more info
            IrReceiver.printIRResultRawFormatted(&Serial, true);
        }
        Serial.println();

        /*
         * !!!Important!!! Enable receiving of the next value,
         * since receiving has stopped after the end of the current received data packet.
         */
        IrReceiver.resume(); // Enable receiving of the next value

        /*
         * Finally, check the received data and perform actions according to the received command
         */
        if (IrReceiver.decodedIRData.command == 0x0) {
          digitalWrite( 11, LOW);
          digitalWrite(10,HIGH);
          delay(100);
          digitalWrite( 11, HIGH);
          digitalWrite( 10, LOW);
        }
    }
}
