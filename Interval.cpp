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

/* --- Time Stamp --- */

/* Set stamp on Initialization */
timestamp::timestamp(time (*f)()) : getTime(f) {
	stamp = getTime();
}

/* Set stamp */
void timestamp::setStamp() {
	stamp = getTime();
}

/* Setting stamp in future (or even past) */
void timestamp::setStamp(time t) {
	stamp = getTime() + t;
}

/* Check wether stamp has expired a specific time */
bool timestamp::olderThan(time t) {
	return (getTime() >= stamp + t);
}

/* Check wether future stamp has expired (awlays true on setStamp() */
bool timestamp::expired() {
	return (getTime() >= stamp);
}

/* Get passed time since stamp (in ms) */
time_ms timestamp::timeSinceStamp() {
	return getTime() - stamp;
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
