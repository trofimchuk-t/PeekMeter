#include "PeekMeter.h"

CPeekMeter::CPeekMeter()
{
	CoInitialize(NULL);

	hr = CoCreateInstance(__uuidof(MMDeviceEnumerator),
						  NULL,
						  CLSCTX_INPROC_SERVER,
						  __uuidof(IMMDeviceEnumerator),
						  (void **)&pEnumerator);

	if (FAILED(hr))
	{
		this->~CPeekMeter();
	}

	hr = pEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &pDevice);

	if (FAILED(hr))
	{
		this->~CPeekMeter();
	}

	hr = pDevice->Activate(__uuidof(IAudioMeterInformation),
						   CLSCTX_ALL,
						   NULL,
						   (void **)&pMeterInfo);

	if (FAILED(hr))
	{
		this->~CPeekMeter();
	}
}

CPeekMeter::~CPeekMeter()
{
	SAFE_RELEASE(pEnumerator)
	SAFE_RELEASE(pDevice)
	SAFE_RELEASE(pMeterInfo)
	CoUninitialize();
}

float CPeekMeter::GetPeekLevel()
{
	static float peak = 0;

	hr = pMeterInfo->GetPeakValue(&peak);
	return peak;
}

__declspec(dllexport) float GetLevel()
{
	static CPeekMeter p;
	return p.GetPeekLevel();
}