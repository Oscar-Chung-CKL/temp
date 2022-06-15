#pragma once

#include "include.hpp"

// The source code below is from:
// The code of this function is from: https://stackoverflow.com/questions/997946/how-to-get-current-time-and-date-in-c

const string timenow()
{
  time_t now = time(0);
  struct tm tstruct;
  char timing[80];
  tstruct = *localtime(&now);
  strftime(timing, sizeof(timing), "%Y-%m-%d.%X", &tstruct);
  return timing;
}
