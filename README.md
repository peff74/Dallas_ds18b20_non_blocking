# DS18B20 non blocking Script

This Arduino script reads a DS18B20 temperature sensor only by using the OneWire library. 
The script initiates temperature measurements, checks if the sensor is busy, and retrieves temperature data.
Without blocking 



## Script Details

The script includes the following functions:

- `setupDS18b20()`: Initializes the DS18B20 sensor and verifies its presence.
- `printAddress(byte addr[8])`: Prints the sensor's address in hexadecimal format.
- `startMeasurementDS18b20()`: Starts a new temperature measurement.
- `checkBusyDS18B20()`: Checks if the sensor is still busy with the measurement.
- `getDataDS18B20()`: Retrieves and processes the temperature data once the measurement is complete.


## Example Output

    Found device with address: 28:FF:4C:60:92:16:05:5C
    Sensor is a DS18B20
    Measurement started
    Measurement completed
    getDataDS18B20 execution time: 498 ms
    Temperature: 22.52 C
