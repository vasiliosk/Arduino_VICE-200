#pragma once
#include <stdint.h>
#include <macros.h>

#ifndef __PINS_ARDUINO__
#define __PINS_ARDUINO__

// No analog on this design


// Frequency of the board main oscillator
#define VARIANT_MAINOSC (32768ul)

// Master clock frequency
#define VARIANT_MCK     (64000000ul)

// Pins
// ----

// Number of pins defined in PinDescription array
#ifdef __cplusplus
extern "C" unsigned int PINCOUNT_fn();
#endif
#define PINS_COUNT           (PINCOUNT_fn())

// D0..D19 only
#define NUM_DIGITAL_PINS     (20u)
#define NUM_ANALOG_INPUTS    (1u)
#define NUM_ANALOG_OUTPUTS   (0u)


// Analog pins (required by core even if you don't use analogRead)
#define PIN_A0 (14u)
static const uint8_t A0 = PIN_A0;

#define ADC_RESOLUTION 12




extern PinName digitalPinToPinName(pin_size_t P);

// Digital pins
// -----------
// These are Arduino pin *indexes*. The Nordic P0.xx/P1.xx mapping is in variant.cpp.
#define D0  (0u)   // Header pin 27 (TX1)
#define D1  (1u)   // Header pin 28 (RX1)
#define D2  (2u)   // Header pin 01
#define D3  (3u)   // Header pin 03 (RX2 label in photo)
#define D4  (4u)   // Header pin 04
#define D5  (5u)   // Header pin 06
#define D6  (6u)   // Header pin 07
#define D7  (7u)   // Header pin 09
#define D8  (8u)   // Header pin 12
#define D9  (9u)   // Header pin 13
#define D10 (10u)  // Header pin 15
#define D11 (11u)  // Header pin 16
#define D12 (12u)  // Header pin 18 (MOSI)
#define D13 (13u)  // LEDs
#define D14 (14u)  // Header pin 19 (SCK)
#define D15 (15u)  // Header pin 22 (TX2)
#define D16 (16u)  // Header pin 23
#define D17 (17u)  // Header pin 24 (SCL)
#define D18 (18u)  // Header pin 25 (SDA)
#define D19 (19u)  // Header pin 30 (MISO)

// LEDs
// ----
#define PIN_LED     (D13)
#define LED_BUILTIN PIN_LED


#define LED        (D13)   // Blue

// Serial interfaces
// -----------------
// Serial1 is your UART on the header TX1/RX1 (D0/D1)
#define PIN_SERIAL_TX (D0)
#define PIN_SERIAL_RX (D1)

#define PIN_WIRE_SDA_1  PIN_WIRE_SDA1
#define PIN_WIRE_SCL_1  PIN_WIRE_SCL1

// SPI 
#define PIN_SPI_MOSI  (D12)
#define PIN_SPI_MISO  (D19)
#define PIN_SPI_SCK   (D14)
#define PIN_SPI_SS    (D8)


static const uint8_t MOSI = PIN_SPI_MOSI;
static const uint8_t MISO = PIN_SPI_MISO;
static const uint8_t SCK  = PIN_SPI_SCK;
static const uint8_t SS   = PIN_SPI_SS;

// i2c on headers
#define PIN_WIRE_SCL  (D17)
#define PIN_WIRE_SDA  (D18)

// imu/mag i2c bus. not broken out.
#define PIN_WIRE_SDA1  (D5)    // IMU SDA
#define PIN_WIRE_SCL1  (D6)    // IMU SCL


#define WIRE_HOWMANY  2
#define WIRE_INTERFACES_COUNT 2

#define I2C_SDA   (digitalPinToPinName(PIN_WIRE_SDA))
#define I2C_SCL   (digitalPinToPinName(PIN_WIRE_SCL))
#define I2C_SDA1  (digitalPinToPinName(PIN_WIRE_SDA1))
#define I2C_SCL1  (digitalPinToPinName(PIN_WIRE_SCL1))

// These serial port names
#define SERIAL_PORT_USBVIRTUAL      SerialUSB
#define SERIAL_PORT_MONITOR         SerialUSB
#define SERIAL_PORT_HARDWARE        Serial1
#define SERIAL_PORT_HARDWARE_OPEN   Serial1

// Mbed specific defines
#define SERIAL_HOWMANY              1
#define SERIAL1_TX                  (digitalPinToPinName(PIN_SERIAL_TX))
#define SERIAL1_RX                  (digitalPinToPinName(PIN_SERIAL_RX))

#define SERIAL_CDC                  1
#define HAS_UNIQUE_ISERIAL_DESCRIPTOR
#define BOARD_VENDORID              0x2341
#define BOARD_PRODUCTID             0x805a
#define BOARD_NAME                  "VICE-200"

#define DFU_MAGIC_SERIAL_ONLY_RESET 0xb0

#define SPI_HOWMANY                 1
#define SPI_MISO                    (digitalPinToPinName(PIN_SPI_MISO))
#define SPI_MOSI                    (digitalPinToPinName(PIN_SPI_MOSI))
#define SPI_SCK                     (digitalPinToPinName(PIN_SPI_SCK))

#define digitalPinToPort(P)         (digitalPinToPinName(P)/32)

uint8_t getUniqueSerialNumber(uint8_t* name);
void _ontouch1200bps_();

#endif // __PINS_ARDUINO__
