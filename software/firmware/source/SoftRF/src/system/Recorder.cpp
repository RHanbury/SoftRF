/*
 * RecorderHelper.cpp
 * Copyright (C) 2016-2023 Linar Yusupov
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

#include "SoC.h"

#if !defined(ENABLE_RECORDER)
void Recorder_setup()   {}
void Recorder_loop()    {}
void Recorder_fini()    {}
#else

#include <SdFat.h>
#include <FlightRecorder.h>

#include "Recorder.h"
#include "../driver/GNSS.h"

extern SdFat uSD;

FlightRecorder FR;

void Recorder_setup()
{
  if (hw_info.storage == STORAGE_CARD ||
      hw_info.storage == STORAGE_FLASH_AND_CARD) {
     FR.begin(&uSD);
  }
}

void Recorder_loop()
{
  if (hw_info.storage == STORAGE_CARD ||
      hw_info.storage == STORAGE_FLASH_AND_CARD) {
    FR.loop(&gnss, ThisAircraft.pressure_altitude);
  }
}

void Recorder_fini()
{
  if (hw_info.storage == STORAGE_CARD ||
      hw_info.storage == STORAGE_FLASH_AND_CARD) {
    FR.end();
  }
}

#endif /* ENABLE_RECORDER */