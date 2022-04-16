/* Encoder Library - TwoKnobs Example
 * http://www.pjrc.com/teensy/td_libs_Encoder.html
 *
 * This example code is in the public domain.
 */

// left stick: 16 - 388 - 762

#include <BMP180.h>
#include <heltec.h>

#define ENCODER_DO_NOT_USE_INTERRUPTS
#define ANALOG_BASE_VALUE 388
#define ENC0_PIN 25
#define ENC1_PIN 25
// #include <Encoder.h>

// Encoder Turn0(A0, A1);
// Encoder Turn1(A2, A3);

void setup() {
	Serial.begin(115200);
	Serial.println("TwoKnobs Encoder Test:");

	pinMode(ENC0_PIN, OUTPUT);
	pinMode(ENC1_PIN, OUTPUT);
}

long prevms             = 0;
long prevPosition_Turn0 = -1;
long prevPosition_Turn1 = -1;

void loop() {
	// long crtPosition_Turn0 = Turn0.read();
	// long crtPosition_Turn1 = Turn1.read();

	// long crtms = millis();

	// Serial.print("AN: ");
	// Serial.print(700);
	dacWrite(ENC0_PIN, 255);
	dacWrite(ENC1_PIN, 255);
	// Serial.println();

	// if (crtms - prevms > 10 && (prevPosition_Turn0 != crtPosition_Turn0 || prevPosition_Turn1 != crtPosition_Turn1)) {
	// 	Serial.print(crtPosition_Turn0 + ANALOG_BASE_VALUE);
	// 	Serial.print(':');
	// 	Serial.print(crtPosition_Turn1 + ANALOG_BASE_VALUE);
	// 	Serial.println();

	// 	prevms = crtms;
	// 	prevPosition_Turn0 = crtPosition_Turn0;
	// 	prevPosition_Turn1 = crtPosition_Turn1;

	// 	Turn0.write(0);
	// 	Turn1.write(0);
	// }

	// if a character is sent from the serial monitor,
	// reset both back to zero.
	if (Serial.available()) {
		Serial.read();
		Serial.println("Reset both knobs to zero");

		// Turn0.write(0);
		// Turn1.write(0);
	}
}