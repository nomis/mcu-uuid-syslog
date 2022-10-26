mcu-uuid-syslog
===============

Description
-----------

Microcontroller syslog service

Purpose
-------

Provides a log handler that sends messages to a syslog server (using
the `RFC 5424 protocol <https://tools.ietf.org/html/rfc5424>`_).
Thread-safe (for log messages only, not configuration) on the ESP32 but
cannot be used from an interrupt context.

Dependencies
------------

* `mcu-uuid-common <https://mcu-uuid-common.readthedocs.io/>`_
* `mcu-uuid-log <https://mcu-uuid-log.readthedocs.io/>`_

Refer to the :download:`library.json <../library.json>` file for more
details.

Contents
--------

.. toctree::
   :titlesonly:
   :maxdepth: 1

   usage

Resources
---------

.. toctree::
   :titlesonly:
   :maxdepth: 1

   Source code <https://github.com/nomis/mcu-uuid-syslog>
   Releases <https://github.com/nomis/mcu-uuid-syslog/releases>
   Namespace reference <https://mcu-doxygen.uuid.uk/namespaceuuid_1_1syslog.html>
   PlatformIO library <https://registry.platformio.org/libraries/nomis/uuid-syslog>
   changelog
   Issue tracker <https://github.com/nomis/mcu-uuid-syslog/issues>
