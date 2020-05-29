/* Copyright (C) 2019-2020 Lee C. Bussy (@LBussy)

This file is part of Lee Bussy's Keg Cop (keg-cop).

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE. */

#ifndef CONFIG_H
#define CONFIG_H

//////////////////////////////////////////////////////////////////////////
//
// Determine whether Raspberry Pints Compatible reports are sent via serial
//
#ifndef RPINTS
#define RPINTS false
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Determine whether RPRints Compatible RandR+ version reports are sent
//
#ifndef RANDR
#define RANDR false
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Determine whether the solenoid relay is on or off
//
#ifndef TSOL
#define TSOL false
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// SPIFFS Editor Username
//
#ifndef SPIFFSEDITUSER
#define SPIFFSEDITUSER "admin"
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// SPIFFS Editor Username
//
#ifndef SPIFFSEDITPW
#define SPIFFSEDITPW "p@ssword"
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Set verbosity of debug messages 0-6
//
//      * 0 - LOG_LEVEL_SILENT     no output
//      * 1 - LOG_LEVEL_FATAL      fatal errors
//      * 2 - LOG_LEVEL_ERROR      all errors
//      * 3 - LOG_LEVEL_WARNING    errors, and warnings
//      * 4 - LOG_LEVEL_NOTICE     errors, warnings and notices
//      * 5 - LOG_LEVEL_TRACE      errors, warnings, notices & traces
//      * 6 - LOG_LEVEL_VERBOSE    all
//
// Uncomment #define for logging level desired.
//
#ifndef LOG_LEVEL
// #define LOG_LEVEL LOG_LEVEL_SILENT     // No output
// #define LOG_LEVEL LOG_LEVEL_FATAL      // Fatal errors
// #define LOG_LEVEL LOG_LEVEL_ERROR      // All errors
// #define LOG_LEVEL LOG_LEVEL_WARNING    // Errors, and warnings
// #define LOG_LEVEL LOG_LEVEL_NOTICE     // Errors, warnings and notices
// #define LOG_LEVEL LOG_LEVEL_TRACE      // Errors, warnings, notices & traces
#define LOG_LEVEL LOG_LEVEL_VERBOSE // All
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Define API Key (identifies application to target)
//
#ifndef API_KEY
#define API_KEY "Keg Cop"
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Define data KNAME (identifies sensor/keezer source to target)
//
#ifndef KNAME
#define KNAME "Kegerator 1"
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Define build version (Git tag from PIO Env)
//
#ifndef VERSION_STRING
#define VERSION_STRING PIO_SRC_TAG
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Define build commit (Git commit from PIO Env)
//
#ifndef BUILD_NAME
#define BUILD_NAME PIO_SRC_REV
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Set WiFi Channel (1, 6, 11 are the only ones which should be used)
// https://www.metageek.com/training/resources/why-channels-1-6-11.html
//
#ifndef WIFI_CHAN
#define WIFI_CHAN 1
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Set WiFi country (US, JP or CN)
// US = 1-11, CN = 1-13, JP = 1-14
//
#ifndef WIFI_COUNTRY
#define WIFI_COUNTRY "US"
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Set serial baud rate (if not set via PlatformIO build flag)
//
#ifndef BAUD
#define BAUD 115200
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Set Rasperry Pints baud rate
//
#ifndef RPBAUD
#define RPBAUD 9600
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Access Point name
//
#ifndef APNAME
#define APNAME "kegcop"
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Access point password
//
#ifndef AP_PASSWD
#define AP_PASSWD "kegcop12"
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// File name for configuration JSON
//
#ifndef FILENAME
#define FILENAME "/config.json"
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Set Version JSON location
//
#ifndef VERSIONJSONLOC
#define VERSIONJSONLOC "http://www.kegcop.com/firmware/version.json"
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Poll Brew Bubbles server for available version (time in seconds)
//
#ifndef POLLSERVERVERSION
#define POLLSERVERVERSION 1800
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Firmware URL
//
#ifndef FIRMWAREURL
#define FIRMWAREURL "http://www.kegcop.com/firmware/firmware.bin"
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// SPIFFS URL
//
#ifndef SPIFFSURL
#define SPIFFSURL "http://www.kegcop.com/firmware/spiffs.bin"
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Default host name
//
#ifndef HOSTNAME
#define HOSTNAME "kegcop"
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Reset mDNS to help the connectiviy issues
//
#ifndef MDNSTIMER
#define MDNSTIMER 3600
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Reboot timer
//
#ifndef REBOOTTIMER
#define REBOOTTIMER 86400
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Default Cop name
//
#ifndef BRWYNAME
#define BRWYNAME "My Homebrew"
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Define reset WiFi on boot pin - reset if pulled low on boot
//
#ifndef RESETWIFI
#define RESETWIFI 13
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Default beer name
//
#ifndef DEFAULTBEER
#define DEFAULTBEER "Pudswiller Doors"
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// File name for flow configuration JSON
//
#ifndef FLOWFILENAME
#define FLOWFILENAME "/flow.json"
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Flow speed in oz/sec at which to trigger a kicked keg
//
#ifndef KICKSPEED
#define KICKSPEED 2
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Number of taps
//
#ifndef NUMTAPS
#define NUMTAPS 8
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Input pin for keg 0 flow
//
#ifndef FLOW0
#define FLOW0 0
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Input pin for keg 1 flow
//
#ifndef FLOW1
#define FLOW1 4
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Input pin for keg 2 flow
//
#ifndef FLOW2
#define FLOW2 17
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Input pin for keg 3 flow
//
#ifndef FLOW3
#define FLOW3 18
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Input pin for keg 4 flow
//
#ifndef FLOW4
#define FLOW4 19
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Input pin for keg 5 flow
//
#ifndef FLOW5
#define FLOW5 21
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Input pin for keg 6 flow
//
#ifndef FLOW6
#define FLOW6 22
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Input pin for keg 7 flow
//
#ifndef FLOW7
#define FLOW7 23
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Keg Size in Gallons
//
#ifndef KEGSIZE
#define KEGSIZE 5
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Pulses per gallon default (based on SF-800)
//
#ifndef PPU
#define PPU 21120
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Define units format (true = Imperial, false = Metric)
//
#ifndef IMPERIAL
#define IMPERIAL true
#define FMIN (double)33
#define FMAX (double)80
#define CMIN (double)1
#define CMAX (double).5
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Define number of sensors
//
#ifndef NUMSENSOR
#define NUMSENSOR 5
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Define room temp sensor name
//
#ifndef ROOMTEMP
#define ROOMTEMP "Room"
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Define room temp sensor pin
//
#ifndef TOWERTEMP
#define TOWERTEMP "Tower"
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Define room temp sensor pin
//
#ifndef UPPERTEMP
#define UPPERTEMP "Upper Chamber"
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Define room temp sensor pin
//
#ifndef LOWERTEMP
#define LOWERTEMP "Lower Chamber"
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Define room temp sensor pin
//
#ifndef KEGTEMP
#define KEGTEMP "Keg"
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Define room temp sensor pin
//
#ifndef ROOMSENSE
#define ROOMSENSE 32
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Define tower temp sensor pin
//
#ifndef TOWERSENSE
#define TOWERSENSE 33
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Define upper chamber temp sensor pin
//
#ifndef UCHAMBSENSE
#define UCHAMBSENSE 25
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Define lower chamber temp sensor pin
//
#ifndef LCHAMBSENSE
#define LCHAMBSENSE 26
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Define keg temp sensor pin
//
#ifndef KEGSENSE
#define KEGSENSE 14
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Define cool actuator pin
//
#ifndef COOL
#define COOL 27
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Default setpoint
//
#ifndef DEFSET
#define DEFSET 40.0
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Default control point
//
#ifndef DEFCON
// #define DEFCON 0 // Room
// #define DEFCON 1 // Tower
// #define DEFCON 2 // Upper Chamber
// #define DEFCON 3 // Lower Chamber
#define DEFCON 4 // Keg
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Cooling Delay - Default 5 mins (in millis())
//
#ifndef COOLDELAY
#define COOLDELAY 2 * 60 * 1000
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Minimum on time - Default 2 mins (in millis())
//
#ifndef MINON
#define MINON 1 * 60 * 1000
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Define solenoid actuator pin
//
#ifndef SOLENOID
#define SOLENOID 16
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Loop time in seconds for flow meter registration
//
#ifndef TAPLOOP
#define TAPLOOP 1
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Delay time in milleseconds for detecting a constant pour
//
#ifndef POURDELAY
#define POURDELAY 300
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Loop time in seconds for temp sampling
//
#ifndef TEMPLOOP
#define TEMPLOOP 10
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Num readings in window for temp avg (window = TEMPLOOP * TEMPAVG secs)
//
#ifndef TEMPAVG
#define TEMPAVG 6
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Resolution time in microseconds (de-bouncer) - Must be declared as an UL
//
#ifndef RESOLUTION
#define RESOLUTION 500UL
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Frequency with which to blink LED when loading config fails
//
#ifndef CONFIGBLINK
#define CONFIGBLINK 2000UL // 2000ms each state = 4000ms per cycle = 0.25Hz
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Frequency with which to blink LED when in Access Point blocking loop
//
#ifndef APBLINK
#define APBLINK 1000UL // 1000ms each state = 2000ms per cycle = 0.5Hz
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Frequency with which to blink LED when in Station Connect blocking loop
//
#ifndef STABLINK
#define STABLINK 333UL // 333ms each state = 666ms per cycle = ~1.5Hz
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Frequency with which to blink LED when in NTP blocking loop
//
#ifndef NTPBLINK
#define NTPBLINK 50UL // 50ms each state = 100ms per cycle = 10Hz
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Port for local web services
//
#ifndef PORT
#define PORT 80
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Default Target Frequency (default 1 minute)
//
#ifndef TARGETFREQ
#define TARGETFREQ 0
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// NTP Server
//
#ifndef TIMESERVER
#define TIMESERVER "pool.ntp.org", "time.nist.gov"
#endif
//
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Output pin for LED
//
#ifndef LED
#define LED LED_BUILTIN
#endif
//
//////////////////////////////////////////////////////////////////////////

#endif // CONFIG_H
