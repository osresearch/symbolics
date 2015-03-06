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

#define KEY(normal,shifted) \
	(normal)

	//((normal) | (shifted) << 8)

static const uint16_t scancode[128] = {
0, // 0
0, // 1
KEY_INSERT, // 2 local
KEY_CAPS_LOCK, // 3 caps
KEY_LEFT_GUI, // 4 left hyper
KEY_LEFT_ALT, // 5 left meta
KEY_RIGHT_CTRL, // 6 right control
0, // 7 right super
KEY_SCROLL_LOCK, // 8 scroll
KEY_NUM_LOCK, // 9 mode lock
0, // 10
0, // 11
0, // 12
KEY_F11, // 13 select
0, // 14 left symbol
0, // 15 left super
KEY_LEFT_CTRL, // 16 left control
' ', // 17 space
KEY_RIGHT_ALT, // 18 right meta
KEY_RIGHT_GUI, // 19 right hyper
KEY_RIGHT_ARROW, // 20 end
0, // 21
0, // 22
0, // 23
'z', // 24 z
'c', // 25 c
'b', // 26 b
'm', // 27 m
'.', // 28 .
KEY_RIGHT_SHIFT, // 29 right shift
KEY_F9, // 30 repeat
KEY_F10, // 31 abort
0, // 32
0, // 33
0, // 34
KEY_LEFT_SHIFT, // 35 left shift
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
KEY_RETURN, // 52 return
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
KEY_DOWN_ARROW, // 64 line
0, // 65
0, // 66
0, // 67
KEY_F1, // 68 function
'w', // 69 w
'r', // 70 r
'y', // 71 y
'i', // 72 i
'p', // 73 p
KEY(')',']'), // 74 ) ]
KEY_PAGE_DOWN, // 75 page
0, // 76
0, // 77
0, // 78
KEY_TAB, // 79 tab
'q', // 80 q
'e', // 81 e
't', // 82 t
'u', // 83 u
'o', // 84 o
KEY('(','['), // 85 ( [
KEY_BACKSPACE, // 86 bs
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
KEY('\\', '{'), // 97 \ {
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
KEY('|','}'), // 108 | }
0, // 109
0, // 110
0, // 111
KEY_ESC, // 112 escape
KEY_F2, // 113 refresh
KEY_F3, // 114 square
KEY_F4, // 115 circle
KEY_F5, // 116 triangle
KEY_F6, // 117 clear
KEY_F7, // 118 suspend
KEY_F8, // 119 resume
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
