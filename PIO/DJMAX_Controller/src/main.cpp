#include <Arduino.h>
#include <ESP32Encoder.h>

// left stick: 16 - 388 - 762

#define ENCODER_DO_NOT_USE_INTERRUPTS
#define DAC_BASE_VALUE 127
#define DAC_MINI_VALUE 0
#define DAC_MAXI_VALUE 254
#define RIGHT_DAC_PIN  26
#define ENC0_0_PIN     18
#define ENC0_1_PIN     19
#define ENC1_0_PIN     16	// Or Left button
#define ENC1_1_PIN     17	// Or Right button

#define LBTN 16
#define RBTN 17

#define KEYMODE 1 // { 0: Encoder, 1: Switch }

ESP32Encoder encoder0;
ESP32Encoder encoder1;

long prevms             = 0;
long prevPosition_Ecdr0 = -1;
long prevPosition_Ecdr1 = -1;

void setup() {
	Serial.begin(115200);

	#if KEYMODE == 0
	ESP32Encoder::useInternalWeakPullResistors = UP;

	encoder0.attachHalfQuad(ENC0_0_PIN, ENC0_1_PIN);
	encoder1.attachHalfQuad(ENC1_0_PIN, ENC1_1_PIN);

	encoder0.resumeCount();
	encoder1.resumeCount();

	encoder0.clearCount();
	encoder1.clearCount();

	prevms = millis();
	#else
	pinMode(LBTN, INPUT);
	pinMode(RBTN, INPUT);
	#endif
}

void loop() {
	#if KEYMODE == 0
	long crtPosition_Ecdr0 = DAC_BASE_VALUE + encoder0.getCount();
	long crtPosition_Ecdr1 = DAC_BASE_VALUE + encoder1.getCount();

	if (crtPosition_Ecdr0 < DAC_MINI_VALUE
	|| crtPosition_Ecdr1 < DAC_MINI_VALUE
	|| crtPosition_Ecdr0 > DAC_MAXI_VALUE
	|| crtPosition_Ecdr1 > DAC_MAXI_VALUE) {
		prevPosition_Ecdr0 = -1;
		prevPosition_Ecdr1 = -1;

		if (crtPosition_Ecdr0 < DAC_MINI_VALUE) crtPosition_Ecdr0 = DAC_MINI_VALUE;
		if (crtPosition_Ecdr1 < DAC_MINI_VALUE) crtPosition_Ecdr1 = DAC_MINI_VALUE;
		if (crtPosition_Ecdr0 > DAC_MAXI_VALUE) crtPosition_Ecdr0 = DAC_MAXI_VALUE;
		if (crtPosition_Ecdr1 > DAC_MAXI_VALUE) crtPosition_Ecdr1 = DAC_MAXI_VALUE;
	}

	long crtms = millis();

	if (crtms - prevms >= 15
	 	&& (prevPosition_Ecdr0 != crtPosition_Ecdr0 || prevPosition_Ecdr1 != crtPosition_Ecdr1)) {

		Serial.println(
			"Encoder count = "
			+ String((int32_t)crtPosition_Ecdr0)
			+ " "
			+ String((int32_t)crtPosition_Ecdr1)
		);

		dacWrite(DAC1, crtPosition_Ecdr0);
		dacWrite(DAC2, crtPosition_Ecdr1);

		prevPosition_Ecdr0 = crtPosition_Ecdr0;
		prevPosition_Ecdr1 = crtPosition_Ecdr1;
		prevms = crtms;

		encoder0.clearCount();
		encoder1.clearCount();
	}
	#else
	int L_BTN = digitalRead(LBTN);
	int R_BTN = digitalRead(RBTN);

	if (L_BTN == HIGH) {
		Serial.print(millis());
		Serial.print(':');
		Serial.print(L_BTN);
		Serial.println(": L_BTN");
		dacWrite(DAC1, 255);
	}
	if (R_BTN == HIGH) {
		Serial.print(millis());
		Serial.print(':');
		Serial.print(R_BTN);
		Serial.println("R_BTN");
		dacWrite(DAC2, 255);
	}
	#endif
}