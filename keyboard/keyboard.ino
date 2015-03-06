/** \file
 * Symbolics to USB keyboard adapter.
 *
 * D4 Clk (Out)
 * D5 Data (In)
 * C7 Clr (Out)
 */

#define CLR_PIN		10
#define CLK_PIN		22
#define DATA_PIN	23

void setup()
{
	Serial.begin(38400);
	pinMode(DATA_PIN, INPUT_PULLUP);
	pinMode(CLR_PIN, OUTPUT);
	pinMode(CLK_PIN, OUTPUT);
}

void loop()
{
	digitalWrite(CLR_PIN, 0);
	delay(10);
	digitalWrite(CLR_PIN, 1);

	for (uint8_t i = 0 ; i < 128 ; i++)
	{
		digitalWrite(CLK_PIN, 0);
		//delay(1);
		uint8_t bit = digitalRead(DATA_PIN);
		digitalWrite(CLK_PIN, 1);
		Serial.print(bit ? ' ' : '1');
	}

	Serial.println();
}
