#line 2 "BrokerCommonTest.ino"

#include <Arduino.h>
#include <AUnit.h>
#include <AceTime.h>

using ace_time::zoneinfo::findShortName;

test(findShortStringTest_cstring) {
  assertEqual("", findShortName(""));
  assertEqual("a", findShortName("a"));
  assertEqual("", findShortName("a/"));
  assertEqual("b", findShortName("a/b"));
  assertEqual("", findShortName("a/b/"));
  assertEqual("c", findShortName("a/b/c"));
}

test(findShortStringTest_fstring) {
  assertEqual("", findShortName(F("")));
  assertEqual("a", findShortName(F("a")));
  assertEqual("", findShortName(F("a/")));
  assertEqual("b", findShortName(F("a/b")));
  assertEqual("", findShortName(F("a/b/")));
  assertEqual("c", findShortName(F("a/b/c")));
}

//---------------------------------------------------------------------------

void setup() {
#if ! defined(EPOXY_DUINO)
  delay(1000); // wait to prevent garbage on SERIAL_PORT_MONITOR
#endif
  SERIAL_PORT_MONITOR.begin(115200);
  while (!SERIAL_PORT_MONITOR); // Leonardo/Micro
#if defined(EPOXY_DUINO)
  SERIAL_PORT_MONITOR.setLineModeUnix();
#endif
}

void loop() {
  aunit::TestRunner::run();
}
