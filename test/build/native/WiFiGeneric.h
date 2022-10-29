/*
 ESP8266WiFiGeneric.h - esp8266 Wifi support.
 Based on WiFi.h from Ardiono WiFi shield library.
 Copyright (c) 2011-2014 Arduino.  All right reserved.
 Modified by Ivan Grokhotkov, December 2014
 Reworked by Markus Sattler, December 2015

 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.

 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef ESP32WIFIGENERIC_H_
#define ESP32WIFIGENERIC_H_

//#include "esp_err.h"
//#include "esp_event.h"
#include <functional>
#include "WiFiType.h"
#include "IPAddress.h"
//#include "esp_smartconfig.h"
//#include "wifi_provisioning/manager.h"

typedef size_t wifi_event_id_t;

typedef enum {
    WIFI_POWER_19_5dBm = 78,// 19.5dBm
    WIFI_POWER_19dBm = 76,// 19dBm
    WIFI_POWER_18_5dBm = 74,// 18.5dBm
    WIFI_POWER_17dBm = 68,// 17dBm
    WIFI_POWER_15dBm = 60,// 15dBm
    WIFI_POWER_13dBm = 52,// 13dBm
    WIFI_POWER_11dBm = 44,// 11dBm
    WIFI_POWER_8_5dBm = 34,// 8.5dBm
    WIFI_POWER_7dBm = 28,// 7dBm
    WIFI_POWER_5dBm = 20,// 5dBm
    WIFI_POWER_2dBm = 8,// 2dBm
    WIFI_POWER_MINUS_1dBm = -4// -1dBm
} wifi_power_t;

typedef enum {
	WIFI_RX_ANT0 = 0,
	WIFI_RX_ANT1,
	WIFI_RX_ANT_AUTO
} wifi_rx_ant_t;

typedef enum {
	WIFI_TX_ANT0 = 0,
	WIFI_TX_ANT1,
	WIFI_TX_ANT_AUTO
} wifi_tx_ant_t;

class WiFiGenericClass
{
  public:
    WiFiGenericClass() {};

    void persistent(bool) {};

    static bool mode(wifi_mode_t) { return true; };

    static const char * getHostname();
    static bool setHostname(const char * hostname);
    static bool hostname(const String& aHostname) { return setHostname(aHostname.c_str()); }

  protected:
    friend class WiFiSTAClass;
};

#endif /* ESP32WIFIGENERIC_H_ */
