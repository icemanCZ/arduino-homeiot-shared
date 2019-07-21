#include "homeiot_shared.h"
#include "RF24.h"

int serial_putc(char c, FILE*)
{
	Serial.write(c);
	return c;
}

void initRF(RF24 nRF) 
{
	nRF.setChannel(82);
	nRF.setDataRate(RF24_250KBPS);
	nRF.setPALevel(RF24_PA_HIGH);
}

typedef struct {
	long sensorId;
	float value;
} payload;

payload data;


void sendTemp(RF24 nRF, long id, float value, bool isListening)
{
	Serial.println("Odesilam teplotu cidla " + String(id) + ": " + String(value));
	if (isListening)
		nRF.stopListening();
	//if (!nRF.write(&id, sizeof(id)))
	//{
	//	Serial.println(F("Chyba pri odesilani 1!"));
	//}
	//delay(10);
	//if (!nRF.write(&value, sizeof(value)))
	//{
	//	Serial.println(F("Chyba pri odesilani 2!"));
	//}
	data.sensorId = id;
	data.value = value;
	if (!nRF.write(&data, sizeof(data)))
	{
		Serial.println(F("Chyba pri odesilani 2!"));
	}
	if (isListening)
		nRF.startListening();
	Serial.println(F("Odeslano"));
}

void sendTemp(RF24 nRF, long id, float value) 
{
	sendTemp(nRF, id, value, false);
}

bool checkRFValues(RF24 nRF, long sensorId, float value)
{
	if (sensorId > 1000 || sensorId <= 0)
	{
		// data order error, flush
		Serial.println("Prijata hodnota id senzoru neni validni.");
		nRF.flush_rx();
		return false;
	}
	if (value > 1000 || value == 0)
	{
		// data order error, flush
		Serial.println("Prijata hodnota namerenych dat neni validni");
		nRF.flush_rx();
		return false;
	}
	return true;
}

bool readData(RF24 nRF, long* sensorId, float* sensorValue)
{
	//nRF.read(sensorId, sizeof(long));
	//int cnt = 0;
	//while (!nRF.available() && cnt++ < 5) { delay(10); };
	//nRF.read(sensorValue, sizeof(float));

	nRF.read(&data, sizeof(data));
	*sensorId = data.sensorId;
	*sensorValue = data.value;

	if (!checkRFValues(nRF, *sensorId, *sensorValue))
		return false;

	return true;
}