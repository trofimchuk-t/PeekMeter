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

__declspec(dllexport) float GetLevel()
{
	static CPeekMeter p;
	return p.GetPeekLevel();
}

void hidecursor();

void main()
{
	hidecursor();
	cout << "Hello\n";

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