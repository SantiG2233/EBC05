/*
 Name:		Códigos_de_error.ino
 Created:	01/07/2020
 Author:	Ángel
*/

#define colorOut 19
#define S0 2
#define S1 4
#define S2 16
#define S3 17

#define B 0
#define Y 1
#define R 2
#define time 1000000

uint8_t color;

int state = 0;

int countY = 0, countR = 0;
int ind = 0;

int dec = 0, uni = 0;

int num = 0;

// the setup function runs once when you press reset or power the board
void setup() {
	pinMode(colorOut, INPUT);
	
	Serial.begin(9600);
}

// the loop function runs over and over again until power down or reset
void loop() {

	state = pulseIn(colorOut, HIGH);

	if (state >= 500 && state <= 600) {
		countY += 1;

		if (color != R && countY > 9) {
			countY = 0;
		}

		else if (color == R)
			ind = 1;

		else if (color == Y && ind == 1) {

		}

		else
			color = Y;
	}

	else if (state >= 700 && state <= 800) {

		if (color == Y && ind == 0) {
			countR = 1;
			ind = 1;
		}

		else if (color == R && ind == 1) {
			countR = 2;
			dec = countY;
		}

		color = R;
	}

	else if (state >= 100 && state <= 200) {
		color = B;
	}
}


void find_code() {

	countY = 0;
	countY = 0;

	switch (num) {
	case 12:;
		break;

	case 13:;
		break;

	case 14:;
		break;

	case 15:;
		break;

	case 16:;
		break;

	case 17:;
		break;

	case 18:;
		break;

	case 22:;
		break;

	case 23:;
		break;

	case 24:;
		break;

	case 25:;
		break;

	case 26:;
		break;

	case 27:;
		break;

	case 28:;
		break;

	case 29:;
		break;

	case 31:;
		break;

	case 32:;
		break;

	case 33:;
		break;

	case 34:;
		break;

	case 35:;
		break;

	case 36:;
		break;

	case 37:;
		break;

	case 38:;
		break;

	case 39:;
		break;

	case 41:;
		break;

	case 42:;
		break;

	case 43:;
		break;

	case 44:;
		break;

	case 45:;
		break;

	case 46:;
		break;

	case 47:;
		break;

	case 48:;
		break;

	case 49:;
		break;

	case 51:;
		break;

	case 52:;
		break;

	case 53:;
		break;

	case 54:;
		break;

	case 55:;
		break;

	case 56:;
		break;

	case 57:;
		break;

	case 58:;
		break;

	case 59:;
		break;

	case 60:;
		break;

	case 61:;
		break;

	case 62:;
		break;

	case 63:;
		break;

	case 64:;
		break;

	case 65:;
		break;

	case 66:;
		break;

	case 67:;
		break;

	case 68:;
		break;

	case 69:;
		break;

	case 71:;
		break;

	case 72:;
		break;

	case 73:;
		break;

	case 74:;
		break;

	case 75:;
		break;

	case 87:;
		break;

	case 89:;
		break;

	case 91:;
		break;

	case 92:;
		break;

	case 93:;
		break;

	case 94:;
		break;

	case 98:;
		break;

	case 99:;
		break;
	}

}