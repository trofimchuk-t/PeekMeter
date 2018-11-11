#include<iostream>
#include <windows.h>
#include <mmdeviceapi.h>
#include <endpointvolume.h>
using namespace std;

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
	int GetChannelsCount();
	bool GetPeekLevels(UINT channelsCount, float *levelsArr);
	~CPeekMeter();
};

CPeekMeter::CPeekMeter()
{
	CoInitialize(NULL);

	hr = CoCreateInstance(__uuidof(MMDeviceEnumerator),
		NULL, CLSCTX_INPROC_SERVER,
		__uuidof(IMMDeviceEnumerator),
		(void**)&pEnumerator);

	if (FAILED(hr))
		this->~CPeekMeter();

	hr = pEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &pDevice);
	if (FAILED(hr))
		this->~CPeekMeter();

	hr = pDevice->Activate(__uuidof(IAudioMeterInformation),
		CLSCTX_ALL, NULL, (void**)&pMeterInfo);
	if (FAILED(hr))
		this->~CPeekMeter();
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

int CPeekMeter::GetChannelsCount()
{
	static UINT channelsCount = 0;

	hr = pMeterInfo->GetMeteringChannelCount(&channelsCount);
	return channelsCount;
}

bool CPeekMeter::GetPeekLevels(UINT channelsCount, float *levelsArr)
{
	hr = pMeterInfo->GetChannelsPeakValues(channelsCount, levelsArr);

	return hr == S_OK;
}

static CPeekMeter p;

__declspec(dllexport) float GetLevel()
{
	//static CPeekMeter p;
	return p.GetPeekLevel();
}

__declspec(dllexport) int GetChannelsCount()
{
	//static CPeekMeter p;
	return p.GetChannelsCount();
}

__declspec(dllexport) bool GetLevels(UINT channelsCount, float *levelsArr)
{
	//static CPeekMeter p;
	return p.GetPeekLevels(channelsCount, levelsArr);
}

void hidecursor();

void main()
{
	hidecursor();
	cout << "Hello\n";

	int count = GetChannelsCount();
	cout << "Channels count: " << count << "\n";

	const int MaxChannelsCount = 8;
	float levels[MaxChannelsCount] = {};
	bool status = GetLevels(count, levels);
	cout << "Level 1: " << levels[0] << "\n" << "Level 2: " << levels[1] << "\n";

	while (true) {

		float f = GetLevel();

		for (int i = 0; i < 20; ++i)
		{
			cout << ((i < f * 20) ? "=" : " ");
		}

		Sleep(15);
		cout << "\r";
	}
}

void hidecursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}