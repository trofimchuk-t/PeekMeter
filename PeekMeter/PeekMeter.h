#pragma once

#include <windows.h>
#include <mmdeviceapi.h>
#include <endpointvolume.h>

#define SAFE_RELEASE(punk)  \
	if ((punk) != NULL)  \
				{ (punk)->Release(); (punk) = NULL; }

extern "C" __declspec(dllexport) float GetLevel();

class CPeekMeter
{
	HRESULT hr;
	IMMDeviceEnumerator *pEnumerator;
	IMMDevice *pDevice;
	IAudioMeterInformation *pMeterInfo;

public:

	CPeekMeter();

	float GetPeekLevel();

	~CPeekMeter();
};