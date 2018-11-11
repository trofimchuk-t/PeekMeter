#pragma once

#include <windows.h>
#include <mmdeviceapi.h>
#include <endpointvolume.h>

#define SAFE_RELEASE(punk)  \
	if ((punk) != NULL)  \
				{ (punk)->Release(); (punk) = NULL; }

class CPeekMeter
{
	HRESULT hr;
	IMMDeviceEnumerator *pEnumerator;
	IMMDevice *pDevice;
	IAudioMeterInformation *pMeterInfo;

public:

	CPeekMeter();

	float GetPeekLevel();

	int GetChannelsCount();

	bool GetPeekLevels(int channelsCount, float *levelsArr);

	~CPeekMeter();
};