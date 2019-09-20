#ifndef _homeiot_shared_h
#define _homeiot_shared_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include "RF24.h"

const long RF_SENSOR_KOTELNA_INTERNAL_TEMPERATURE_ID = 1;
const long RF_SENSOR_KOTELNA_SMOKE_TEMPERATURE_ID = 2;
const long RF_SENSOR_KOTELNA_OUTPUT_TEMPERATURE_ID = 3;
const long RF_SENSOR_KOTELNA_RETURN_TEMPERATURE_ID = 4;
const long RF_SENSOR_KOTELNA_GAS_KETTLE_TEMPERATURE_ID = 5;

const long RF_SENSOR_OUTSIDE_TEMPERATURE_ID = 10;

const uint64_t RF_KOTELNA_ADDRESS = 0xE8E8F0F0A1LL;
const uint64_t RF_OUTSIDE_ADDRESS = 0xE8E8F0F0B2LL;


int serial_putc(char c, FILE*);
void sendTemp(RF24 nRF, long id, float value, bool isListening);
void sendTemp(RF24 nRF, long id, float value);
bool checkRFValues(RF24 nRF, long sensorId, float value);
bool readData(RF24 nRF, long* sensorId, float* sensorValue);
void initRF(RF24 nRf);

#endif

