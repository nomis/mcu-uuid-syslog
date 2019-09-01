Usage
=====

.. code:: c++

   #include <uuid/syslog.h>

Create a |uuid::syslog::SyslogService|_ and call |start()|_. Then set
the destination host, log level and optional local hostname.

The default log level is |uuid::log::Level::ALL| so it can capture
messages logged during startup before any configuration is read.

When WiFi connectivity is available the queued messages will be sent.

On ESP8266 and ESP32 platforms an ARP query will be made every second
until a route to the destination host is available, before sending
messages at a rate of 100 per second. On other platforms messages will
be sent at a rate of 10 per second to allow time for ARP lookups to
complete and avoid dropping messages.

Whenever possible, the current system time is included in the outgoing
syslog message.

Example
-------

.. literalinclude:: ../examples/Example.cpp

.. |uuid::syslog::SyslogService| replace:: ``uuid::syslog::SyslogService``
.. _uuid::syslog::SyslogService: https://mcu-doxygen.uuid.uk/classuuid_1_1syslog_1_1SyslogService.html

.. |uuid::log::Level::ALL| replace:: ``uuid::log:Level::ALL``
.. _uuid::log::Level::ALL: https://mcu-doxygen.uuid.uk/namespaceuuid_1_1log.html#a3e74b277087df0622d1778698f1a45dca6fed2f923983459f91ab90ef08cbdeea

.. |start()| replace:: ``start()``
.. _start(): https://mcu-doxygen.uuid.uk/classuuid_1_1syslog_1_1SyslogService.html#ae03a4d85f9c01a880989140075dc922d
