#include <Arduino.h>
#include <ESP32Encoder.h>

// left stick: 16 - 388 - 762

#define ENCODER_DO_NOT_USE_INTERRUPTS
#define ANALOG_BASE_VALUE 388
#define ENC0_DAC_PIN      25
#define ENC0_0_PIN        36
#define ENC0_1_PIN        37
#define ENC1_DAC_PIN      26
#define ENC1_0_PIN        38
#define ENC1_1_PIN        39

ESP32Encoder encoder0;
ESP32Encoder encoder1;

long prevms             = 0;
long prevPosition_Ecdr0 = -1;
long prevPosition_Ecdr1 = -1;

void setup() {
	Serial.begin(115200);
	ESP32Encoder::useInternalWeakPullResistors = UP;

	encoder0.attachHalfQuad(ENC0_0_PIN, ENC0_1_PIN);
	encoder1.attachHalfQuad(ENC1_0_PIN, ENC1_1_PIN);

	encoder0.resumeCount();
	encoder1.resumeCount();

	encoder0.clearCount();
	encoder1.clearCount();

	prevms = millis();
}

void loop() {
	long crtPosition_Ecdr0 = encoder0.getCount();
	long crtPosition_Ecdr1 = encoder1.getCount();

	long crtms = millis();

	Serial.print(crtPosition_Ecdr0);
	Serial.print(":");
	Serial.print(crtPosition_Ecdr1);
	Serial.println(
		"Encoder count = "
		+ String((int32_t)crtPosition_Ecdr0)
		+ " "
		+ String((int32_t)crtPosition_Ecdr1)
	);

	if (crtms - prevms >= 10
	 	&& (prevPosition_Ecdr0 != crtPosition_Ecdr0 || prevPosition_Ecdr1 != crtPosition_Ecdr1)) {

		Serial.println(
			"Encoder count = "
			+ String((int32_t)crtPosition_Ecdr0)
			+ " "
			+ String((int32_t)crtPosition_Ecdr1)
		);

		prevPosition_Ecdr0 = crtPosition_Ecdr0;
		prevPosition_Ecdr1 = crtPosition_Ecdr1;
		prevms = crtms;

		encoder0.clearCount();
		encoder1.clearCount();
	}
}