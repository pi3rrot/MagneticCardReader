# Magnetic Card Reader 
# This is for arduino board
# It don't work at this state... but still in progress :)
# Pi3rrot 08/08/2012

#define STROBE_PIN 2
#define DATA_PIN 3
#define PC_PIN 6

unsigned char buffer[35] = { 0 };
int strobe = 0;

bool presenceCard()
{
	return digitalRead(PC_PIN) == LOW;
}

int readCard()
{
	int bit = 0;
	
	strobe = 0;
	while(presenceCard())
	{
		while (presenceCard() && digitalRead(STROBE_PIN) == LOW);
		if (!presenceCard())
			return strobe;

		bit = digitalRead(DATA_PIN);
		buffer[strobe / 7] |= (bit << (7 - (strobe % 7)));
		strobe++;

		while (presenceCard() && digitalRead(STROBE_PIN) == HIGH);
	}
	
	return strobe;
}

void setup()
{
	pinMode(STROBE_PIN, INPUT);
	pinMode(DATA_PIN, INPUT);
	pinMode(PC_PIN, INPUT);
	
	Serial.begin(9600);
}

void loop()
{
	int strobe = readCard();
	if (strobe > 0)
	{
		Serial.print("nb strobes = ");
		Serial.println(strobe);
		Serial.print("data = ");
		
		for (int i = 0; i < (strobe / 8) + 1; i++)
		{
			Serial.print(buffer[i], HEX);
			Serial.print(" ");
		}
		Serial.print("\r\n\r\n");
	}
}

