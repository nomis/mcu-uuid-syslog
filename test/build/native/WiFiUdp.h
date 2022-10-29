/*
 *  Udp.cpp: Library to send/receive UDP packets.
 *
 * NOTE: UDP is fast, but has some important limitations (thanks to Warren Gray for mentioning these)
 * 1) UDP does not guarantee the order in which assembled UDP packets are received. This
 * might not happen often in practice, but in larger network topologies, a UDP
 * packet can be received out of sequence.
 * 2) UDP does not guard against lost packets - so packets *can* disappear without the sender being
 * aware of it. Again, this may not be a concern in practice on small local networks.
 * For more information, see http://www.cafeaulait.org/course/week12/35.html
 *
 * MIT License:
 * Copyright (c) 2008 Bjoern Hartmann
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * bjoern@cs.stanford.edu 12/30/2008
 */

#ifndef _WIFIUDP_H_
#define _WIFIUDP_H_

#include <Arduino.h>
#include <Udp.h>
#include <cbuf.h>

#include <list>
#include <vector>

class NativeUdpPacket {
public:
	IPAddress addr;
	uint16_t port;
	std::vector<char> data;
};

extern std::list<NativeUdpPacket> native_packets;

class WiFiUDP : public UDP {
private:
  NativeUdpPacket native_packet;
public:
  WiFiUDP() {};
  ~WiFiUDP() {};
  uint8_t begin(IPAddress a, uint16_t p);
  uint8_t begin(uint16_t p);
  uint8_t beginMulticast(IPAddress a, uint16_t p);
  void stop();
  int beginMulticastPacket();
  int beginPacket();
  int beginPacket(IPAddress ip, uint16_t port) override {
    native_packet.addr = ip;
    native_packet.port = port;
    return 1;
  };
  int endPacket() override {
    native_packet.data.push_back(0);
    native_packets.push_back(std::move(native_packet));
    native_packet = {};
    return 1;
  };
  size_t write(uint8_t c) override {
    native_packet.data.push_back(c);
    return 1;
  };
  size_t write(const uint8_t *buffer, size_t size) override {
    native_packet.data.insert(native_packet.data.end(), buffer, buffer + size);
    return size;
  };
  int parsePacket();
  int available() override { return 0; };
  int read() override { return -1; };
  int peek() override { return -1; };
  IPAddress remoteIP();
  uint16_t remotePort();
};

#endif /* _WIFIUDP_H_ */
