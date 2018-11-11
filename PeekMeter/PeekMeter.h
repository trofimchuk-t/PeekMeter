#pragma once

extern "C" __declspec(dllexport) float GetLevel();
extern "C" __declspec(dllexport) bool GetLevels(int channelsCount, float *levelsArr);
extern "C" __declspec(dllexport) int GetChannelsCount();