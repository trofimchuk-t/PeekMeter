#include "PeekMeter.h"
#include "CPeekMeter.h"

static CPeekMeter peekMeter;

__declspec(dllexport) float GetLevel()
{
	return peekMeter.GetPeekLevel();
}

__declspec(dllexport) int GetChannelsCount()
{
	return peekMeter.GetChannelsCount();
}

__declspec(dllexport) bool GetLevels(int channelsCount, float *levelsArr)
{
	return peekMeter.GetPeekLevels(channelsCount, levelsArr);
}