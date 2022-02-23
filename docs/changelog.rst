Change log
==========

Unreleased_
-----------

2.1.1_ |--| 2022-02-23
----------------------

Silence irrelevant compiler warnings when building on the ESP32.

Changed
~~~~~~~

* Silence compiler warnings/errors about ``%S`` in a format string.

2.1.0_ |--| 2022-01-27
----------------------

More visibility of the log message queue and control over the rate at which
messages are dispatched.

Added
~~~~~

* Function to get the current size of the log message queue.
* Symbols to control the UDP message sending delay:

  * ``UUID_SYSLOG_UDP_BASE_MESSAGE_DELAY``
  * ``UUID_SYSLOG_UDP_IPV4_ARP_MESSAGE_DELAY``
  * ``UUID_SYSLOG_UDP_IPV6_NDP_MESSAGE_DELAY``

  It is inadvisable to change these because UDP packets may be queued and then
  discarded by the platform when the queue limit is reached.

Changed
~~~~~~~

* Relax IPv6 scope checking when waiting for a local address to allow
  either global or local unicast addresses to be used with any global
  or local unicast destination. Previously they had to be the same type.

2.0.6_ |--| 2021-04-18
----------------------

Upgrade to PlatformIO 5.

Changed
~~~~~~~

* Use PlatformIO 5 dependency specification.

2.0.5_ |--| 2021-01-17
----------------------

Upgrade to the latest version of the logging library for static
initialization and deinitialization fixes.

Changed
~~~~~~~

* Don't unregister handler explicitly in the destructor, this is now
  handled by the logging library.

2.0.4_ |--| 2019-09-22
----------------------

Fix log message transmit retries.

Fixed
~~~~~

* Log messages that failed to be sent are not left on the queue
  correctly and may cause a crash when they are retried.
* Add memory barrier around checks for log queue overflow.

2.0.3_ |--| 2019-09-21
----------------------

Feature detection fixes.

Fixed
~~~~~

* Use ``gettimeofday()`` on the ESP32.
* Don't redefine ``UUID_SYSLOG_ARP_CHECK``.

2.0.2_ |--| 2019-09-20
----------------------

Support IPv6 addresses.

Fixed
~~~~~

* Use move constructors on rvalues.
* Support for IPv6 addresses.

2.0.1_ |--| 2019-09-05
----------------------

Bug fix for trace level messages.

Fixed
~~~~~

* Use debug level for trace level messages.

2.0.0_ |--| 2019-09-03
----------------------

Additional features and API changes.

Added
~~~~~

* Functions to get all of the configuration parameters.
* Support for sending a ``-- MARK --`` message when there is no
  activity for a configurable period of time.

Changed
~~~~~~~

* Add log level to the message text.
* Lower the log level of log level change messages to ``INFO``.
* Rename ``set_host()`` to ``destination()``.
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

.. _Unreleased: https://github.com/nomis/mcu-uuid-syslog/compare/2.1.1...HEAD
.. _2.1.1: https://github.com/nomis/mcu-uuid-syslog/compare/2.1.0...2.1.1
.. _2.1.0: https://github.com/nomis/mcu-uuid-syslog/compare/2.0.6...2.1.0
.. _2.0.6: https://github.com/nomis/mcu-uuid-syslog/compare/2.0.5...2.0.6
.. _2.0.5: https://github.com/nomis/mcu-uuid-syslog/compare/2.0.4...2.0.5
.. _2.0.4: https://github.com/nomis/mcu-uuid-syslog/compare/2.0.3...2.0.4
.. _2.0.3: https://github.com/nomis/mcu-uuid-syslog/compare/2.0.2...2.0.3
.. _2.0.2: https://github.com/nomis/mcu-uuid-syslog/compare/2.0.1...2.0.2
.. _2.0.1: https://github.com/nomis/mcu-uuid-syslog/compare/2.0.0...2.0.1
.. _2.0.0: https://github.com/nomis/mcu-uuid-syslog/compare/1.0.0...2.0.0
.. _1.0.0: https://github.com/nomis/mcu-uuid-syslog/commits/1.0.0
