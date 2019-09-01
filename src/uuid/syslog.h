/*
 * uuid-syslog - Syslog service
 * Copyright 2019  Simon Arlott
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef UUID_SYSLOG_H_
#define UUID_SYSLOG_H_

#include <Arduino.h>
#ifdef ARDUINO_ARCH_ESP8266
# include <ESP8266WiFi.h>
#else
# include <WiFi.h>
#endif
#include <WiFiUdp.h>
#include <time.h>

#ifndef UUID_SYSLOG_HAVE_GETTIMEOFDAY
# if defined(ARDUINO_ARCH_ESP8266) || defined(ARDUINIO_ARCH_ESP32)
// time() does not return UTC on the ESP8266: https://github.com/esp8266/Arduino/issues/4637
#  define UUID_SYSLOG_HAVE_GETTIMEOFDAY 1
# else
#  define UUID_SYSLOG_HAVE_GETTIMEOFDAY 0
# endif
#endif

#include <list>
#include <memory>
#include <string>

#include <uuid/log.h>

namespace uuid {

/**
 * Syslog service.
 *
 * - <a href="https://github.com/nomis/mcu-uuid-syslog/">Git Repository</a>
 * - <a href="https://mcu-uuid-syslog.readthedocs.io/">Documentation</a>
 */
namespace syslog {

/**
 * Log handler for sending messages to a syslog server.
 *
 * @since 1.0.0
 */
class SyslogService: public uuid::log::Handler {
public:
	static constexpr size_t MAX_LOG_MESSAGES = 50; /*!< Maximum number of log messages to buffer before they are output. @since 1.0.0 */
	static constexpr uint16_t DEFAULT_PORT = 514; /*!< Default UDP port to send messages to. @since 1.0.0 */

	/**
	 * Create a new syslog service log handler.
	 *
	 * @since 1.0.0
	 */
	SyslogService() = default;

	~SyslogService();

	/**
	 * Register the log handler with the logging framework.
	 *
	 * @since 1.0.0
	 */
	void start();

	/**
	 * Get the current log level.
	 *
	 * This only affects newly received log messages, not messages that
	 * have already been queued.
	 *
	 * @return The current log level.
	 * @since 1.0.0
	 */
	uuid::log::Level get_log_level() const;
	/**
	 * Set the current log level.
	 *
	 * Unless this is the first time the log level is being set, this
	 * only affects newly received log messages, not messages that have
	 * already been queued.
	 *
	 * @param[in] level Minimum log level that will be sent to the
	 *                  syslog server.
	 * @since 1.0.0
	 */
	void set_log_level(uuid::log::Level level);

	/**
	 * Get the maximum number of queued log messages.
	 *
	 * @return The maximum number of queued log messages.
	 * @since 1.0.0
	 */
	size_t get_maximum_log_messages();
	/**
	 * Set the maximum number of queued log messages.
	 *
	 * Defaults to SyslogService::MAX_LOG_MESSAGES.
	 *
	 * @since 1.0.0
	 */
	void set_maximum_log_messages(size_t count);

	/**
	 * Set the server to send messages to.
	 *
	 * @param[in] host IP address of the syslog server.
	 * @param[in] port UDP port to send messages to.
	 * @since 1.0.0
	 */
	void set_host(IPAddress host, uint16_t port = DEFAULT_PORT);

	/**
	 * Set local hostname.
	 *
	 * @param[in] host Hostname of this device.
	 * @since 1.0.0
	 */
	void set_hostname(std::string hostname);

	/**
	 * Dispatch queued log messages.
	 *
	 * @since 1.0.0
	 */
	void loop();

	/**
	 * Add a new log message.
	 *
	 * This will be put in a queue for output at the next loop()
	 * process. The queue has a maximum size of maximum_log_messages()
	 * and will discard the oldest message first.
	 *
	 * @param[in] message New log message, shared by all handlers.
	 * @since 1.0.0
	 */
	virtual void operator<<(std::shared_ptr<uuid::log::Message> message);

private:
	/**
	 * Log message that has been queued.
	 *
	 * Contains an identifier sequence to indicate when log messages
	 * could not be output because the queue discarded one or more
	 * messages.
	 *
	 * @since 1.0.0
	 */
	class QueuedLogMessage {
	public:
		/**
		 * Create a queued log message.
		 *
		 * @param[in] id Identifier to use for the log message on the queue.
		 * @param[in] content Log message content.
		 * @since 1.0.0
		 */
		QueuedLogMessage(unsigned long id, std::shared_ptr<uuid::log::Message> &&content);
		~QueuedLogMessage() = default;

		unsigned long id_; /*!< Sequential identifier for this log message. @since 1.0.0 */
		struct timeval time_; /*!< Time message was received. @since 1.0.0 */
		const std::shared_ptr<const uuid::log::Message> content_; /*!< Log message content. @since 1.0.0 */

	private:
		static bool time_good_; /*!< System time appears to be valid. @since 1.0.0 */
	};

	/**
	 * Remove messages that were queued before the log level was set.
	 *
	 * @param[in] level New log level
	 * @since 1.0.0
	 */
	void remove_queued_messages(uuid::log::Level level);

	/**
	 * Check if it is possible to transmit to the server.
	 *
	 * @return True if it is safe to transmit a message to the server,
	 *         otherwise false.
	 * @since 1.0.0
	 */
	bool can_transmit();

	/**
	 * Attempt to transmit one message to the server.
	 *
	 * @param[in] message Log message to be sent.
	 * @return True if the message was successfully set, otherwise
	 *         false.
	 * @since 1.0.0
	 */
	bool transmit(const QueuedLogMessage &message);

	static uuid::log::Logger logger_; /*!< uuid::log::Logger instance for syslog services. @since 1.0.0 */

	bool started_ = false; /*!< Flag to indicate that messages have started being transmitted. @since 1.0.0 */
	WiFiUDP udp_; /*!< UDP client. @since 1.0.0 */
	IPAddress host_; /*!< Host to send messages to. @since 1.0.0 */
	uint16_t port_ = DEFAULT_PORT; /*!< Port to send messages to. @since 1.0.0 */
	uint64_t last_transmit_ = 0; /*!< Last transmit time. @since 1.0.0 */
	std::string hostname_{'-'}; /*!< Local hostname. @since 1.0.0 */
	size_t maximum_log_messages_ = MAX_LOG_MESSAGES; /*!< Maximum number of log messages to buffer before they are output. @since 1.0.0 */
	unsigned long log_message_id_ = 0; /*!< The next identifier to use for queued log messages. @since 1.0.0 */
	std::list<QueuedLogMessage> log_messages_; /*!< Queued log messages, in the order they were received. @since 1.0.0 */
	bool log_messages_overflow_ = false; /*!< Check if log messages have overflowed the buffer. @since 1.0.0 */
};

} // namespace syslog

} // namespace uuid

#endif