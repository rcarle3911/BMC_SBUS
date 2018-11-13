
#ifndef BMC_SBUS_h
#define BMC_SBUS_h

#include <Arduino.h>

#define BAUDRATE 100000

class BMC_SBUS
{
	public:
		BMC_SBUS(HardwareSerial* _serialport)
		uint8_t sbusData[25];
		int16_t servos[18];
		void begin(void);
		void Servo(uint8_t ch, int16_t position);
		void Send(void);
		void Update(void);

	private:
		uint8_t byte_in_sbus;
		uint8_t bit_in_sbus;
		uint8_t ch;
		uint8_t bit_in_servo;
		HardwareSerial* serialport;
};

#endif