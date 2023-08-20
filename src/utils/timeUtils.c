#include "timeUtils.h"

void convertTimestamp(unsigned int timestamp, char *formattedTime, int formattedTimeLength)
{
    time_t rawTime = timestamp;
    struct tm *timeInfo;
    timeInfo = gmtime(&rawTime);

    strftime(formattedTime, formattedTimeLength, "%Y-%m-%d %H:%M:%S", timeInfo);
}