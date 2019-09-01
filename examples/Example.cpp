#include <Arduino.h>
#ifdef ARDUINO_ARCH_ESP8266
# include <ESP8266WiFi.h>
#else
# include <WiFi.h>
#endif
#include <uuid/log.h>
#include <uuid/syslog.h>

static uuid::syslog::SyslogService syslog;

void setup() {
	static uuid::log::Logger logger{F("setup")};

	syslog.start();
	/* Retrieve settings after calling start()
	 * in case the settings read process logs
	 * some messages.
	 */
	syslog.set_log_level(uuid::log::DEBUG);
	syslog.set_host(IPAddress(192, 168, 0, 1));
	syslog.set_hostname("example");

	WiFi.persistent(false);
	WiFi.mode(WIFI_STA);
	WiFi.begin("SSID", "password");

	Serial.begin(115200);

	logger.info(F("Application started"));
}

void loop() {
	static uuid::log::Logger logger{F("loop")};
	static unsigned int i = 0;

	uuid::loop();
	syslog.loop();

	logger.debug(F("Hello %u World!"), i++);

	delay(1000);
}
