#include "PeekMeter.h"



CPeekMeter::CPeekMeter()
{
	CoInitialize(NULL);

	hr = CoCreateInstance(__uuidof(MMDeviceEnumerator),
                          NULL, CLSCTX_INPROC_SERVER,
                          __uuidof(IMMDeviceEnumerator),
                          (void**)&pEnumerator);

	if(FAILED(hr))
		this->~CPeekMeter();

	hr = pEnumerator->GetDefaultAudioEndpoint(eRender, eConsole, &pDevice);
	if(FAILED(hr))
		this->~CPeekMeter();

	hr = pDevice->Activate(__uuidof(IAudioMeterInformation),
                           CLSCTX_ALL, NULL, (void**)&pMeterInfo);
	if(FAILED(hr))
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

//BOOL WINAPI DllMain(
//    HINSTANCE hinstDLL,  // handle to DLL module
//    DWORD fdwReason,     // reason for calling function
//    LPVOID lpReserved )  // reserved
//{
//    // Perform actions based on the reason for calling.
//    switch( fdwReason ) 
//    { 
//        case DLL_PROCESS_ATTACH:
//         // Initialize once for each new process.
//         // Return FALSE to fail DLL load.
//            break;
//
//        case DLL_THREAD_ATTACH:
//         // Do thread-specific initialization.
//            break;
//
//        case DLL_THREAD_DETACH:
//         // Do thread-specific cleanup.
//            break;
//
//        case DLL_PROCESS_DETACH:
//         // Perform any necessary cleanup.
//            break;
//    }
//    return TRUE;  // Successful DLL_PROCESS_ATTACH.
//}