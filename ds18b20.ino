#include <OneWire.h>
#define ONE_WIRE_BUS 2  // Define the pin for the OneWire bus

OneWire oneWire(ONE_WIRE_BUS);  // Create a OneWire object

bool ds18b20_started = false;  // Flag to check if measurement has started
bool ds18b20_busy = false;     // Flag to check if the sensor is busy
byte ds18b20_data[9];          // Array to hold data from the sensor
byte ds18b20_addr[8];          // Array to hold the sensor's address
float temperature = -127;      // Initialize temperature to an invalid value
unsigned long startTime = 0;   // Variable to store the start time of the measurement

void setupDS18b20() {
  oneWire.reset_search();               // Reset the search state
  if (!oneWire.search(ds18b20_addr)) {  // Search for the sensor's address
    Serial.println("No DS18B20 sensor found");
    return;
  }
  Serial.print("Found device with address: ");
  printAddress(ds18b20_addr);  // Print the sensor's address
  Serial.println();

  // Verify the sensor's CRC and check if it is a DS18B20
  if (OneWire::crc8(ds18b20_addr, 7) != ds18b20_addr[7] || ds18b20_addr[0] != 0x28) {
    Serial.println("Sensor is not a DS18B20");
    return;
  }
  Serial.println("Sensor is a DS18B20");
}

void printAddress(byte addr[8]) {
  // Print the sensor's address in hexadecimal format
  for (byte i = 0; i < 8; i++) {
    if (addr[i] < 16) Serial.print("0");
    Serial.print(addr[i], HEX);
    if (i < 7) {
      Serial.print(":");
    }
  }
}

void startMeasurementDS18b20() {
  // Start the temperature measurement
  if (!ds18b20_started) {
    oneWire.reset();
    oneWire.select(ds18b20_addr);
    oneWire.write(0x44);   // Start conversion without parasite power
    startTime = millis();  // Record the start time
    Serial.println("Measurement started");
    ds18b20_started = true;
    ds18b20_busy = true;
  }
}

void checkBusyDS18B20() {
  // Check if the sensor is busy with the measurement
  if (ds18b20_started && ds18b20_busy) {
    if (oneWire.read_bit()) {  // Check if measurement is complete
      Serial.println("Measurement completed");
      ds18b20_busy = false;
    } else if (millis() - startTime >= 750) {  // Check for timeout (750ms max for 12-bit resolution)
      temperature = -127;                      // Invalid temperature
      Serial.println("Timeout: Measurement assumed completed");
      ds18b20_busy = false;                    // Reset, data is now ready to read
    }
  }
}

void getDataDS18B20() {
  // Retrieve and process the temperature data
  if (ds18b20_started && !ds18b20_busy) {
    oneWire.reset();
    oneWire.select(ds18b20_addr);
    oneWire.write(0xBE);  // Read scratchpad

    for (int i = 0; i < 9; i++) {
      ds18b20_data[i] = oneWire.read();  // Read the 9 bytes of data
    }

    if (OneWire::crc8(ds18b20_data, 8) != ds18b20_data[8]) {     // Verify the sensor's CRC 
      Serial.println("CRC check failed. Invalid data received.");
      temperature = -127;                                        // Invalid temperature
    } else {
      int16_t rawTemperature = (ds18b20_data[1] << 8) | ds18b20_data[0];
      temperature = (float)rawTemperature / 16.0;
    }  

    Serial.print("getDataDS18B20 execution time: ");
    Serial.print(millis() - startTime);
    Serial.println(" ms");

    if (temperature == -127) {  // Check if the temperature is invalid
      Serial.println("No DS18B20 sensor found");
    } else {
      Serial.print("Temperature: ");
      Serial.print(temperature);
      Serial.println(" C");
      Serial.println("");
    }

    ds18b20_started = false;  // Reset for the next measurement
  }
}

void setup() {
  Serial.begin(115200);
  setupDS18b20();
}

void loop() {
  startMeasurementDS18b20();  // Start a new temperature measurement
  checkBusyDS18B20();         // Check if the sensor is still busy
  getDataDS18B20();           // Get the measurement data if ready
}
