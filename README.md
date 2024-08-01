# Non blocking DS18B20 Arduino Script

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


## How to use

1. Connect the DS18B20 sensor to your Arduino board:
   - VCC to 3.3V
   - GND to GND
   - Data to digital pin 2 (configured as `ONE_WIRE_BUS` in the script)
   - A pull-up resistor (4.7kΩ) between VCC and Data

2. Install the OneWire library in your Arduino IDE:
   - Go to **Sketch > Include Library > Manage Libraries...**
   - Search for **OneWire** and install it (2.3.8)

3. Clone or download this repository, or copy the code.
4. Open the script in your Arduino IDE.
5. Upload the script to your Arduino board.
6. Enjoy

[![Hits](https://hits.seeyoufarm.com/api/count/incr/badge.svg?url=https%3A%2F%2Fgithub.com%2Fpeff74%2FDallas_ds18b20_non_blocking&count_bg=%2379C83D&title_bg=%23555555&icon=&icon_color=%23E7E7E7&title=hits&edge_flat=false)](https://hits.seeyoufarm.com)
