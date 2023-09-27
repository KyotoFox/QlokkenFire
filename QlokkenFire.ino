#define WIFI_TIME_SYNC
// #define RTC_TIME_SYNC
// #define NTP_TIME_SYNC
#define QF_USE_ACETIME

#ifndef WIFI_TIME_SYNC
#ifdef NTP_TIME_SYNC
#undef NTP_TIME_SYNC
#warning WiFi has to be enabled to use NTP sync
#endif
#endif

// Programming pinout (Se bilde 2023-09-27)
// TX,RX,GND
// 2,3,4 (J2 fra pin 1 på top)

// Constants
char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

// Display
typedef enum
{
    KLOKKEN_ER = 0,

    FEM_OVER,
    FEM_PA,
    TI_OVER,
    TI_PA,
    KVART_OVER,
    KVART_PA,
    HALV,

    ETT,
    TO,
    TRE,
    FIRE,
    FEM,
    SEKS,
    SYV,
    ATTE,
    NI,
    TI,
    ELLEVE,
    TOLV,

    ZAP,

    MIN_1,
    MIN_2,
    MIN_3,
    MIN_4,
} WORDS;

typedef struct
{
    WORDS wordname;
    uint8_t leds[9];
} display_def;

display_def displayMap[] = {
    {KLOKKEN_ER, {70, 78, 86, 94, 102, 110, 111, 118, 126}},

    //{FEM, {85,93,101}},
    //{OVER, {7,15,23,31}},
    //{(FEM_)PA, {69,125}}
    {FEM_OVER, {85, 93, 101, 7, 15, 23, 31}},
    {FEM_PA, {85, 93, 101, 69, 125}},

    //{TI, {1,9}},
    //{TI_PA, {25,33}},
    {TI_OVER, {1, 9, 7, 15, 23, 31}},
    {TI_PA, {1, 9, 25, 33}},

    //{KVART_PA, {8,16,24,32,40,  56,64}},
    {KVART_OVER, {8, 16, 24, 32, 40, 7, 15, 23, 31}},
    {KVART_PA, {8, 16, 24, 32, 40, 56, 64}},

    {HALV, {6, 14, 22, 30}},

    {ETT, {5, 13, 21}},
    {TO, {37, 45}},
    {TRE, {61, 106, 107}},
    {FIRE, {4, 12, 20, 28}},
    {FEM, {36, 44, 52}},
    {SEKS, {60, 98, 99, 100}},
    {SYV, {3, 11, 19}},
    {ATTE, {27, 35, 43, 51}},
    {NI, {59, 90}},
    {TI, {91, 92}},

    {ELLEVE, {2, 10, 18, 26, 34, 42}},
    {TOLV, {58, 82, 83, 84}},

    // TODO:
    {MIN_1, {88}},
    {MIN_2, {89}},
    {MIN_3, {96}},
    {MIN_4, {97}},
};

// WiFi
#ifdef WIFI_TIME_SYNC
#include <WiFi.h> //ESP8266 Core WiFi Library (you most likely already have this in your sketch)

//#include <DNSServer.h>        //Local DNS Server used for redirecting all requests to the configuration portal
//#include <ESP8266WebServer.h> //Local WebServer used to serve the configuration portal
#include <WiFiManager.h>      //https://github.com/tzapu/WiFiManager WiFi Configuration Magic

WiFiManager wifiManager;

// AceTime
#ifdef QF_USE_ACETIME
    
    #define ACE_TIME_NTP_CLOCK_DEBUG 5

    #include <AceWire.h> // TwoWireInterface
    #include <Wire.h> // TwoWire, Wire
    #include <AceTimeClock.h>
    #include <AceTime.h>

    using ace_time::clock::SystemClockLoop;
    using ace_time::clock::NtpClock;
    using ace_time::clock::DS3231Clock;
    using ace_time::acetime_t;

    using WireInterface = ace_wire::TwoWireInterface<TwoWire>;
    WireInterface wireInterface(Wire);
    DS3231Clock<WireInterface> dsClock(wireInterface);

    NtpClock ntpClock("no.pool.ntp.org");
    SystemClockLoop systemClock(&ntpClock, &dsClock);

    // Time zones
    #include <Preferences.h>
    Preferences preferences;

    static const int CACHE_SIZE = 1;
    static ace_time::ExtendedZoneProcessorCache<CACHE_SIZE> zoneProcessorCache;
    static ace_time::ExtendedZoneManager manager(
        ace_time::zonedbx::kZoneAndLinkRegistrySize,
        ace_time::zonedbx::kZoneAndLinkRegistry,
        zoneProcessorCache);

    static ace_time::BasicZoneProcessor pacificProcessor;
#endif

// NTP
/*
#ifdef NTP_TIME_SYNC
#include <WiFiUdp.h>

WiFiUDP udp;

IPAddress timeServerIP; // time.nist.gov NTP server address
const char *ntpServerName = "no.pool.ntp.org";
const int NTP_PACKET_SIZE = 48;     // NTP time stamp is in the first 48 bytes of the message
byte packetBuffer[NTP_PACKET_SIZE]; // buffer to hold incoming and outgoing packets
#endif // NTP_TIME_SYNC
*/

#endif // WIFI_TIME_SYNC



// RTC
#include "RTClib.h" // Has DateTime

#ifdef RTC_TIME_SYNC

    RTC_DS1307 rtc;

#endif

// LED Matrix
#include "LedControl.h"

int maxLoad = 16;
int maxClk = 18;
int maxMosi = 23;
int maxCount = 2;

LedControl led = LedControl(maxMosi, maxClk, maxLoad, maxCount);

char timezoneSetting[100];

ace_time::TimeZone localTz;

void setup()
{
    // Debug
    Serial.begin(115200);
    Serial.println("QlokkenFire starting up...");

    // LED Init
    led.shutdown(0, false);
    led.shutdown(1, false);

    led.setIntensity(0, 15);
    led.setIntensity(1, 15);

    // led.setScanLimit(0, 1);
    // led.setScanLimit(1, 1);

    led.clearDisplay(0);
    led.clearDisplay(1);
    Serial.println("LED Initialized");


    // Preferences
    Serial.println("Getting preferences...");

    char timeZone[100];
    preferences.begin("qlokkenfire", false); 
    String storedTz = preferences.getString("tz", "Europe/Oslo");
    uint16_t serial = preferences.getUShort("serial", 0);

    Serial.print("Loaded serial: ");
    Serial.println(serial);

    Serial.print("Loaded timezone: ");
    Serial.println(storedTz);



#ifdef RTC_TIME_SYNC
    // RTC
    Serial.println("Starting RTC...");

    if (!rtc.begin()) {
        Serial.println("!! Couldn't find RTC");
        rtc = NULL;
    }
    else {
        Serial.println("RTC Started");

        if (!rtc.isrunning())
        {
            Serial.println("RTC is NOT running!");
            rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
        }

        Serial.println("RTC initialized!");
    }
#endif

#ifdef WIFI_TIME_SYNC
    // WiFi
    Serial.println("Connecting to WiFi...");

    WiFiManagerParameter timezone_config_field("tz", "Time Zone (IATA Identifier)", timezoneSetting, 100);
    wifiManager.addParameter(&timezone_config_field);

    String ssid = "QlokkenFire #";
    ssid += serial;
    wifiManager.autoConnect(ssid.c_str());

    Serial.println("WiFi connection established!");


    // AceTime
    #ifdef QF_USE_ACETIME
    Serial.println("Starting AceTime");

    Wire.begin();

    Serial.println("Starting wireInterface");
    wireInterface.begin();

    Serial.println("Starting dsClock");
    dsClock.setup();

    Serial.println("Starting ntpClock");
    ntpClock.setup();

    Serial.println("Starting systemClock");
    systemClock.setup();


    localTz = manager.createForZoneName(storedTz.c_str());
    if(localTz.isError()) {
        Serial.println("Failed to load stored TZ");
        
        localTz = manager.createForZoneName("Europe/Oslo");
        if(localTz.isError()) {
            Serial.println("Really failed to load TZ");
        }
    }
    else {
        Serial.println("Loaded tz database");
    }

    ace_time::acetime_t now = systemClock.getNow();
    ace_time::ZonedDateTime localNow = ace_time::ZonedDateTime::forEpochSeconds(now, localTz);

    Serial.print(F("AceTime is: "));
    localNow.printTo(Serial);
    Serial.println();

    #endif




/*#ifdef NTP_TIME_SYNC
    Serial.println("Starting NTP UDP...");
    udp.begin(2390);
    Serial.println("UDP OK");

    // Get server IP
    WiFi.hostByName(ntpServerName, timeServerIP);

    // Get time
    while (true)
    {
        Serial.println("Requesting time...");

        sendNTPpacket(timeServerIP);
        delay(1000);

        bool read = readNTP();
        if (read)
        {
            Serial.println("Got NTP time!");
            break;
        }
        else
        {
            Serial.println("Failed to get time, retrying...");
            delay(1000);
        }
    }
#endif*/
#endif
}

uint16_t demoLys[] = {0, 5, 8, 13, 21, 29, 55, 63, 69, 77, 85, 90, 93, 101, 109, 117, 125, 91, 110};

DateTime fakeTime = DateTime(1504393315);

DateTime dst(DateTime UTC)
{
    return DateTime(UTC.unixtime() + 3600 * 2);
}

bool firstDisplay = false;


void printCurrentTime() {
  acetime_t now = systemClock.getNow();

  // Create a time
  auto pacificTz = ace_time::TimeZone::forZoneInfo(&ace_time::zonedb::kZoneAmerica_Los_Angeles,
      &pacificProcessor);
  auto pacificTime = ace_time::ZonedDateTime::forEpochSeconds(now, pacificTz);

  Serial.print("LA time is: ");
  pacificTime.printTo(Serial);
  Serial.println();
}

void loop()
{
    systemClock.loop();

    printCurrentTime();

    ace_time::acetime_t now = systemClock.getNow();
    ace_time::ZonedDateTime localNow = ace_time::ZonedDateTime::forEpochSeconds(now, localTz);

    Serial.print(F("AceLoop is: "));
    localNow.printTo(Serial);
    Serial.println();

    Serial.print(F("Now is: "));
    Serial.print(now);
    Serial.println();

    /*Serial.print("Fetching NTP. Wifi is ");
    Serial.println(WiFi.status());
    acetime_t ntpNow = ntpClock.getNow();

    Serial.print("Got it: ");
    Serial.println(ntpNow);*/


    DateTime adjustedTime = dst(fakeTime);

    writeDate(adjustedTime);

    // Update display at the top of the minute
    if (fakeTime.second() == 0 || !firstDisplay)
    {
        displayTime(adjustedTime);
        firstDisplay = true;
    }

    fakeTime = DateTime(fakeTime.unixtime() + 1);
    delay(1000);
}

// LED Time display
void displayTime(DateTime time)
{

    uint8_t h = time.hour();
    uint8_t m = time.minute();

    led.clearDisplay(0);
    led.clearDisplay(1);

    displayWord(KLOKKEN_ER);

    if (m < 5)
    {
        displayHour(h);
    }
    else if (m < 10)
    {
        displayWord(FEM_OVER);
        displayHour(h);
    }
    else if (m < 15)
    {
        displayWord(TI_OVER);
        displayHour(h);
    }
    else if (m < 20)
    {
        displayWord(KVART_OVER);
        displayHour(h);
    }
    else if (m < 25)
    {
        displayWord(TI_PA);
        displayWord(HALV);
        displayHour(h + 1);
    }
    else if (m < 30)
    {
        displayWord(FEM_PA);
        displayWord(HALV);
        displayHour(h + 1);
    }
    else if (m < 35)
    {
        displayWord(HALV);
        displayHour(h + 1);
    }
    else if (m < 40)
    {
        displayWord(FEM_OVER);
        displayWord(HALV);
        displayHour(h + 1);
    }
    else if (m < 45)
    {
        displayWord(TI_OVER);
        displayWord(HALV);
        displayHour(h + 1);
    }
    else if (m < 50)
    {
        displayWord(KVART_PA);
        displayHour(h + 1);
    }
    else if (m < 55)
    {
        displayWord(TI_PA);
        displayHour(h + 1);
    }
    else
    {
        displayWord(FEM_PA);
        displayHour(h + 1);
    }

    // Corner LEDs (display + 0-4 min)
    uint8_t corners = m % 5;
    switch (corners)
    {
    case 4:
        displayWord(MIN_4);
    case 3:
        displayWord(MIN_3);
    case 2:
        displayWord(MIN_2);
    case 1:
        displayWord(MIN_1);
    }
}

void displayHour(uint8_t hour)
{
    switch (hour)
    {
    case 0:
    case 12:
    case 24:
        displayWord(TOLV);
        break;
    case 1:
    case 13:
        displayWord(ETT);
        break;
    case 2:
    case 14:
        displayWord(TO);
        break;
    case 3:
    case 15:
        displayWord(TRE);
        break;
    case 4:
    case 16:
        displayWord(FIRE);
        break;
    case 5:
    case 17:
        displayWord(FEM);
        break;
    case 6:
    case 18:
        displayWord(SEKS);
        break;
    case 7:
    case 19:
        displayWord(SYV);
        break;
    case 8:
    case 20:
        displayWord(ATTE);
        break;
    case 9:
    case 21:
        displayWord(NI);
        break;
    case 10:
    case 22:
        displayWord(TI);
        break;
    case 11:
    case 23:
        displayWord(ELLEVE);
        break;
    }
}

void displayWord(WORDS displayWord)
{
    Serial.print("Displaying word: ");
    Serial.println(displayWord);

    // Find the word definition
    for (uint8_t i = 0; i < (sizeof(displayMap) / sizeof(displayMap[0])); i++)
    {
        if (displayWord == displayMap[i].wordname)
        {
            Serial.println("> Found definition");

            // Find the leds to turn on
            for (uint8_t t = 0; t < (sizeof(displayMap[0].leds) / sizeof(displayMap[0].leds[0])); t++)
            {
                uint8_t ledIdx = displayMap[i].leds[t];
                if (ledIdx == 0)
                {
                    break;
                }
                ledIdx -= 1;

                Serial.print("> Turning on LED ");
                Serial.print(ledIdx);
                Serial.print(": ");

                // Decode matrix/row/col
                uint8_t matrix = ledIdx / 64;
                ledIdx -= matrix * 64;

                uint8_t row = ledIdx / 8;
                ledIdx -= row * 8;

                uint8_t col = ledIdx;

                // Turn on LED
                Serial.print(matrix);
                Serial.print(", ");
                Serial.print(row);
                Serial.print(", ");
                Serial.println(col);
                led.setLed(matrix, row, col, true);
            }
        }
    }
}

// Time
void writeDate(DateTime now)
{
    // Print RTC
    // DateTime now = rtc.now();

    Serial.print(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();
}

// NTP
#ifdef NTP_TIME_SYNC
void sendNTPpacket(IPAddress &address)
{
    Serial.println("sending NTP packet...");
    // set all bytes in the buffer to 0
    memset(packetBuffer, 0, NTP_PACKET_SIZE);
    // Initialize values needed to form NTP request
    // (see URL above for details on the packets)
    packetBuffer[0] = 0b11100011; // LI, Version, Mode
    packetBuffer[1] = 0;          // Stratum, or type of clock
    packetBuffer[2] = 6;          // Polling Interval
    packetBuffer[3] = 0xEC;       // Peer Clock Precision
    // 8 bytes of zero for Root Delay & Root Dispersion
    packetBuffer[12] = 49;
    packetBuffer[13] = 0x4E;
    packetBuffer[14] = 49;
    packetBuffer[15] = 52;

    // all NTP fields have been given values, now
    // you can send a packet requesting a timestamp:
    udp.beginPacket(address, 123); // NTP requests are to port 123
    udp.write(packetBuffer, NTP_PACKET_SIZE);
    udp.endPacket();
}

bool readNTP()
{
    int cb = udp.parsePacket();
    if (!cb)
    {
        Serial.println("no packet yet");
        return false;
    }
    else
    {
        Serial.print("packet received, length=");
        Serial.println(cb);
        // We've received a packet, read the data from it
        udp.read(packetBuffer, NTP_PACKET_SIZE); // read the packet into the buffer

        // the timestamp starts at byte 40 of the received packet and is four bytes,
        //  or two words, long. First, esxtract the two words:

        unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
        unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
        // combine the four bytes (two words) into a long integer
        // this is NTP time (seconds since Jan 1 1900):
        unsigned long secsSince1900 = highWord << 16 | lowWord;
        Serial.print("Seconds since Jan 1 1900 = ");
        Serial.println(secsSince1900);

        // now convert NTP time into everyday time:
        Serial.print("Unix time = ");
        // Unix time starts on Jan 1 1970. In seconds, that's 2208988800:
        const unsigned long seventyYears = 2208988800UL;
        // subtract seventy years:
        unsigned long epoch = secsSince1900 - seventyYears;
        // print Unix time:
        Serial.println(epoch);

        // print the hour, minute and second:
        Serial.print("The UTC time is ");      // UTC is the time at Greenwich Meridian (GMT)
        Serial.print((epoch % 86400L) / 3600); // print the hour (86400 equals secs per day)
        Serial.print(':');
        if (((epoch % 3600) / 60) < 10)
        {
            // In the first 10 minutes of each hour, we'll want a leading '0'
            Serial.print('0');
        }
        Serial.print((epoch % 3600) / 60); // print the minute (3600 equals secs per minute)
        Serial.print(':');
        if ((epoch % 60) < 10)
        {
            // In the first 10 seconds of each minute, we'll want a leading '0'
            Serial.print('0');
        }
        Serial.println(epoch % 60); // print the second

        // Set non-RTC controlled time
        fakeTime = DateTime(epoch);

        return true;
    }
}
#endif
