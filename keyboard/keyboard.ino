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

static const uint16_t scancode[128] = {
0, // 0
0, // 1
0, // 2 local
0, // 3 caps
0, // 4 left hyper
0, // 5 left meta
0, // 6 right control
0, // 7 right super
0, // 8 scroll
0, // 9 mode lock
0, // 10
0, // 11
0, // 12
0, // 13 select
0, // 14 left symbol
0, // 15 left super
0, // 16 left control
0, // 17 space
0, // 18 right meta
0, // 19 right hyper
0, // 20 end
0, // 21
0, // 22
0, // 23
'z', // 24 z
'c', // 25 c
'b', // 26 b
'm', // 27 m
'.', // 28 .
0, // 29 right shift
0, // 30 repeat
0, // 31 abort
0, // 32
0, // 33
0, // 34
0, // 35 left shift
'x', // 36 x
'v', // 37 v
'n', // 38 n
',', // 39 ,
'/', // 40 /
0, // 41 right symbol
0, // 42
0, // 43
0, // 44
0, // 45
0, // 46 rubout
's', // 47 s
'f', // 48 f
'h', // 49 h
'k', // 50 k
';', // 51 ;
0, // 52 return
0, // 53 complete
0, // 54
0, // 55
0, // 56
0, // 57 network
'a', // 58 a
'd', // 59 d
'g', // 60 g
'j', // 61 j
'l', // 62 l
'\'', // 63 '
0, // 64 line
0, // 65
0, // 66
0, // 67
0, // 68 function
'w', // 69 w
'r', // 70 r
'y', // 71 y
'i', // 72 i
'p', // 73 p
0, // 74 ) ]
0, // 75 page
0, // 76
0, // 77
0, // 78
'\t', // 79 tab
'q', // 80 q
'e', // 81 e
't', // 82 t
'u', // 83 u
'o', // 84 o
0, // 85 ( [
0, // 86 bs
0, // 87
0, // 88
0, // 89
0, // 90 :
'2', // 91 2
'4', // 92 4
'6', // 93 6
'8', // 94 8
'0', // 95 0
'=', // 96 =
0, // 97 \ {
0, // 98
0, // 99
0, // 100
'1', // 101 1
'3', // 102 3
'5', // 103 5
'7', // 104 7
'9', // 105 9
'-', // 106 -
'`', // 107 `
0, // 108 | }
0, // 109
0, // 110
0, // 111
0, // 112 escape
0, // 113 refresh
0, // 114 square
0, // 115 circle
0, // 116 triangle
0, // 117 clear
0, // 118 suspend
0, // 119 resume
};

void setup()
{
	Serial.begin(38400);
	//Keyboard.begin();
	pinMode(DATA_PIN, INPUT_PULLUP);
	pinMode(CLR_PIN, OUTPUT);
	pinMode(CLK_PIN, OUTPUT);
}

static uint8_t press[128];

void loop()
{
	digitalWrite(CLR_PIN, 0);
	delay(10);
	digitalWrite(CLR_PIN, 1);

	int count = 0;

	for (uint8_t i = 0 ; i < 128 ; i++)
	{
		digitalWrite(CLK_PIN, 0);
		//delay(1);
		uint8_t bit = !digitalRead(DATA_PIN);
		digitalWrite(CLK_PIN, 1);

		const uint16_t s = scancode[i];
		if (press[i] ^ bit == 0)
			continue;

		// state change!
		press[i] = bit;

		if (!s)
		{
			// an unknown/unhandled key
			Serial.print(bit ? i : -i);
			Serial.print(' ');
			count++;
		} else
		if (bit)
		{
			Keyboard.press(s);
		} else {
			Keyboard.release(s);
		}
	}

	if (count)
		Serial.println();
}
