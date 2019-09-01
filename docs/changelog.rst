Change log
==========

Unreleased_
-----------

Added
~~~~~

* Buffer messages during startup until configuration is provided.
* Automatic use of system time if it is available.
* Wait for the network to be available before transmitting.
* Explicit ARP check for the destination host on ESP8266 and ESP32.
* Rate limiting of output packets to avoid dropped messages.
* Configurable destination host and log level.
* Configurable local hostname.
* Configurable queue size.

.. |--| unicode:: U+2013 .. EN DASH

.. _Unreleased: https://github.com/nomis/mcu-uuid-syslog/compare/1.0.0...HEAD
.. _1.0.0: https://github.com/nomis/mcu-uuid-syslog/commits/1.0.0