/*
 * Copyright 2016 Patrick Pedersen (ctx.xda@gmail.com)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/* Lightweight Interval library by Patrick Pedersen
 *
 * The goal of this library is to provide a solution for tasks that require some kind of interval pattern,
 * while barely interfearing with the entire runtime time process ulike delays. This is done by Protothreading using time stamps that get checked 
 * in an regulare pattern, being the interval. For simple time stamp interreaction, use the timestamp class that is packed with various 
 * useful functions for timestamp reading and writing. To build a interval, create an instance of definable_interval and refference onInterval to your
 * desired function. This function is then executed on every interval. To start a interval, execute the interval() member function inside of your desired loop.
 * The function will not delay runtime, instead it will skip until the interval time is reached.
 */

#ifndef INTERVAL_H_INCLUDED
#define INTERVAL_H_INCLUDED

#include <Arduino.h>

typedef unsigned long time;
typedef unsigned long time_ms;
typedef unsigned long time_us;

struct timestamp {
  timestamp(time (*f)() = &millis);
  void setStamp();
  void setStamp(time t);
  bool olderThan(time t);
  bool expired();
  time timeSinceStamp();
  time stamp;
  time (*getTime)(); // Pointer to time function (millis() or micros() etc.). Default assigned to milis();
};

struct definable_interval {
public:
  definable_interval();
  definable_interval(time_ms ms);
  definable_interval(time_ms ms, void (*onInterval)());
  void (*onInterval)();
  virtual bool interval();

protected:
  time_ms    interval_len;
  timestamp  interval_time;
};

#endif // INTERVAL_H_INCLUDED
