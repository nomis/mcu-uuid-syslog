Change log
==========

Unreleased_
-----------

Added
~~~~~

* Functions to get all of the configuration parameters.
* Support for sending a ``-- MARK --`` message when there is no
  activity for a configurable period of time.

Changed
~~~~~~~

* Add log level to the message text.
* Lower the log level of log level change messages to ``INFO``.
* Rename ``set_host()`` to ``set_destination()``.
* Remove ``get_`` and ``set_`` from function names.

Fixed
~~~~~

* Function to set the maximum number of log messages is no longer
  limited to 0 or 1.

1.0.0_ |--| 2019-09-01
----------------------

First stable release.

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
