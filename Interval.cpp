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

/* Lightweight Arduino Interval Library by Patrick Pedersen
 * Please see Interval.h for more details */

#include "Interval.h"

typedef unsigned long time_ms;

/* --- Time Stamp --- */

/* Set stamp on Initialization */
time_stamp::time_stamp() {
	stamp = millis();
}

/* Set stamp */
void time_stamp::setStamp() {
	stamp = millis();
}

/* Setting stamp in future (or even past) */
void time_stamp::setStamp(time_ms ms) {
	stamp = millis() + ms;
}

/* Check wether stamp has expired a specific time */
bool time_stamp::olderThan(time_ms ms) {
	return (millis() >= stamp + ms);
}

/* Check wether future stamp has expired (awlays true on setStamp() */
bool time_stamp::expired() {
	return (millis() >= stamp);
}

/* Get passed time since stamp (in ms) */
time_ms time_stamp::timeSinceStamp() {
	return millis() - stamp;
}

/* --- Interval --- */

/* For Inheritance */
definable_interval::definable_interval(){}

/* Without function reference (Must be defined later */
definable_interval::definable_interval(time_ms ms) : interval_len(ms) {
	interval_time.setStamp(ms);
}

/* With function reference */
definable_interval::definable_interval(time_ms ms, void(*f)()) : interval_len(ms), onInterval(f) {
	interval_time.setStamp(ms);
}

/* Run interval */
bool definable_interval::interval() {
	bool ret;
	if(ret = interval_time.expired()) {
		onInterval();
		interval_time.setStamp(interval_len);
	}
	return ret;
}
