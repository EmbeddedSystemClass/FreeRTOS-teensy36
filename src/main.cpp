#include <FlexCAN.h>
#include <Arduino.h>
#include <usb_dev.h>
//#include <Serial1.h>

class ExampleClass : public CANListener 
{
	public:
		void printFrame(CAN_message_t &frame, int mailbox);
		bool frameHandler(CAN_message_t &frame, int mailbox, uint8_t controller); //overrides the parent version so we can actually do something
};

void ExampleClass::printFrame(CAN_message_t &frame, int mailbox)
{
	Serial1.print("ID: ");
	Serial1.print(frame.id, HEX);
	Serial1.print(" Data: ");
	for (int c = 0; c < frame.len; c++) 
	{
		Serial1.print(frame.buf[c], HEX);
		Serial1.write(' ');
	}
	Serial1.write('\r');
	Serial1.write('\n');
	Serial1.flush();
}
bool lol=1;
bool ExampleClass::frameHandler(CAN_message_t &frame, int mailbox,uint8_t controller)
{
	//cli();
	digitalWrite(13, lol);
	lol=!lol;
	Serial1.print("ID: ");
	Serial1.print(frame.id, HEX);
	Serial1.print(" Data: ");
	digitalWrite(13, lol);
	Serial1.print(frame.len, HEX);
	lol=!lol;
	
	//printFrame(frame, mailbox);
	//sei();
	return true;
}
ExampleClass exampleClass;
// -------------------------------------------------------------
void setup(void)
{
	//usb_init();
	Serial1.begin(9600);
	pinMode(13, OUTPUT);
	digitalWrite(13, HIGH);
	delayMicroseconds(1000000);
	digitalWrite(13, LOW);
	delayMicroseconds(1000000);
	digitalWrite(13, HIGH);
	delayMicroseconds(1000000);
	digitalWrite(13, LOW);
	/*delayMicroseconds(1000000);
	digitalWrite(13, HIGH);
	delayMicroseconds(1000000);
	digitalWrite(13, LOW);
	delayMicroseconds(1000000);*/
	Serial1.println(F("Hello Teensy 3.6 dual CAN Test With Objects."));
	Serial1.flush();
	delayMicroseconds(1000000);
	Can0.begin(500000);  
	Can0.attachObj(&exampleClass);
	exampleClass.attachGeneralHandler();
}
// -------------------------------------------------------------
int main()
{
	setup();
	int i=0;
	while(1)
	{
		//Serial1.println(i++);
		//Serial1.println(F("waiting..."));
		i=(Can0.available()?1/*Serial1.println("Can available")*/:0);
		Serial1.flush();
		//delayMicroseconds(1000000);
	}
	i--;
	return 0;
}