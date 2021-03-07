/* Copyright (C) 2020 Lee C. Bussy (@LBussy)

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

#include "main.h"

DoubleResetDetector *drd;

void setup()
{
    drd = new DoubleResetDetector(DRD_TIMEOUT, DRD_ADDRESS);

    if (!loadConfig())
    { // If configuration does not load, sit and blink slowly like an idiot
        pinMode(LED, OUTPUT);
        Ticker blinker;
        blinker.attach_ms(CONFIGBLINK, []() {
            digitalWrite(LED, !(digitalRead(LED)));
        });
        while (true)
        {
        };
    }

    serial();

    // Set wifi reset pin
    pinMode(RESETWIFI, INPUT_PULLUP);
    // Set LED pin
    pinMode(LED, OUTPUT);

    // Log.verbose(F("DEBUG:  IPL = %T." CR), isIPL()); // DEBUG Initial program load work

    // Check if portal is requested
    if (!config.nodrd && drd->detectDoubleReset())
    {
        Log.notice(F("DRD: Portal requested." CR));
        doWiFi(true);
    }
    else if (digitalRead(RESETWIFI) == LOW)
    {
        Log.notice(F("Pin %d low, presenting portal." CR), RESETWIFI);
        doWiFi(true);
    }
    else
    {
        Log.verbose(F("Starting WiFi." CR));
        config.nodrd = false;
        doWiFi();
    }

    // Set pin for relay
    pinMode(COOL, OUTPUT);
    digitalWrite(COOL, HIGH);

    setClock(); // Set NTP Time

#if KCWEIGH == false
    // Initialize flowmeters before checking for SPIFFS update
    if (initFlow())
        Log.notice(F("Flowmeters loaded." CR));
    else
        Log.error(F("Unable to load flowmeters." CR));
#endif

    execspiffs(); // Check for pending SPIFFS update

    mdnssetup();     // Set up mDNS responder
    tcpCleanup();    // Get rid of -8 errors
    initWebServer(); // Turn on web server
    sensorInit();    // Initialize temperature sensors
    startControl();  // Initialize temperature control
    doVersionPoll(); // Get server version at startup

    if (!Log.getLevel())
        nullDoc("d");
    else
        Log.notice(F("Started %s version %s (%s) [%s]." CR), API_KEY, version(), branch(), build());
}

void loop()
{
    // Poll temperature sensors
    Ticker pollSensors;
    pollSensors.attach(TEMPLOOP, pollTemps);

    // Update temperature control loop
    Ticker doControl;
    doControl.attach(TEMPLOOP, controlLoop);

#if KCWEIGH == false
    // Log pours
    Ticker logPour;
    logPour.attach(TAPLOOP, logFlow);
#endif

    // Poll for server version
    Ticker getThatVersion;
    getThatVersion.attach(POLLSERVERVERSION, doVersionPoll);

    // Send Keg Screen Temp Report
    Ticker doKSTempReport;
    doKSTempReport.attach(KSTEMPREPORT, setDoKSTempReport);

    // Send Target Report
    Ticker doTargetReport;
    doTargetReport.attach(config.urltarget.freq * 60, setDoTargetReport);

    while (true)
    {
        if (doNonBlock)
        {
            // Handle nonblocking portal (if configured)
            wm.process();
        }
        else
        {
            // We can do normal processing

            // Check for Target URL Timing reset
            if (config.urltarget.update)
            {
                Log.notice(F("Resetting URL Target frequency timer to %l minutes." CR), config.urltarget.freq);
                doTargetReport.detach();
                doTargetReport.attach(config.urltarget.freq * 60, setDoTargetReport);
                config.urltarget.update = false;
            }

            doOTALoop();
            tickerLoop();
            drd->loop();
            serialLoop();
            maintenanceLoop();
        }
    }
}
