#include <windows.h>
#include <setupapi.h>
#include <iostream>
#include <vector>
#include <string>
#include <wbemidl.h> // WMI için

#pragma comment(lib, "setupapi.lib")
#pragma comment(lib, "wbemuuid.lib")

void ListUsbPorts() {
    HDEVINFO deviceInfoSet = SetupDiGetClassDevs(nullptr, "USB", nullptr, DIGCF_PRESENT | DIGCF_ALLCLASSES);
    if (deviceInfoSet == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to get USB device info set." << std::endl;
        return;
    }

    SP_DEVINFO_DATA deviceInfoData;
    deviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

    std::vector<std::string> connectedDevices;

    std::cout << "USB Ports and Devices:" << std::endl;
    std::cout << "----------------------------------------------------------" << std::endl;

    for (int i = 0; SetupDiEnumDeviceInfo(deviceInfoSet, i, &deviceInfoData); i++) {
        char deviceName[256] = {0};

        // Bağlı cihazları listele
        if (SetupDiGetDeviceRegistryPropertyA(
                deviceInfoSet,
                &deviceInfoData,
                SPDRP_DEVICEDESC,
                nullptr,
                (PBYTE)deviceName,
                sizeof(deviceName),
                nullptr)) {
            connectedDevices.emplace_back(deviceName);
            std::cout << "USB Port: In Use by -> " << deviceName << std::endl;
        } else {
            std::cout << "USB Port: Unknown device (could not fetch name)" << std::endl;
        }
    }

    std::cout << "----------------------------------------------------------" << std::endl;

    // Burada yalnızca kullanılan portlar gösterildi; kullanılmayan portları tespit etmek için özel bir cihaz dizini kullanabilirsiniz.
    SetupDiDestroyDeviceInfoList(deviceInfoSet);
}

void ListNetworkAdapters() {
    HRESULT hres;

    // WMI'yi başlat
    hres = CoInitializeEx(0, COINIT_MULTITHREADED);
    if (FAILED(hres)) {
        std::cerr << "Failed to initialize COM library." << std::endl;
        return;
    }

    // Güvenlik seviyesini ayarla
    hres = CoInitializeSecurity(
        NULL,
        -1,
        NULL,
        NULL,
        RPC_C_AUTHN_LEVEL_DEFAULT,
        RPC_C_IMP_LEVEL_IMPERSONATE,
        NULL,
        EOAC_NONE,
        NULL);

    if (FAILED(hres)) {
        std::cerr << "Failed to initialize security." << std::endl;
        CoUninitialize();
        return;
    }

    IWbemLocator *pLoc = NULL;

    // WMI'ye bağlan
    hres = CoCreateInstance(
        CLSID_WbemLocator,
        0,
        CLSCTX_INPROC_SERVER,
        IID_IWbemLocator,
        (LPVOID *)&pLoc);

    if (FAILED(hres)) {
        std::cerr << "Failed to create IWbemLocator object." << std::endl;
        CoUninitialize();
        return;
    }

    IWbemServices *pSvc = NULL;

    hres = pLoc->ConnectServer(
        BSTR(L"ROOT\\CIMV2"),
        NULL,
        NULL,
        0,
        0,
        0,
        0,
        &pSvc);

    if (FAILED(hres)) {
        std::cerr << "Could not connect to WMI namespace ROOT\\CIMV2." << std::endl;
        pLoc->Release();
        CoUninitialize();
        return;
    }

    IEnumWbemClassObject *pEnumerator = NULL;
    hres = pSvc->ExecQuery(
        BSTR(L"WQL"),
        BSTR(L"SELECT * FROM Win32_NetworkAdapter"),
        WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
        NULL,
        &pEnumerator);

    if (FAILED(hres)) {
        std::cerr << "WMI query for network adapters failed." << std::endl;
        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        return;
    }

    IWbemClassObject *pclsObj = NULL;
    ULONG uReturn = 0;

    std::cout << "Network Adapters:" << std::endl;
    std::cout << "----------------------------------------------------------" << std::endl;

    while (pEnumerator) {
        HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
        if (0 == uReturn) {
            break;
        }

        VARIANT vtProp;

        // Adı al
        hr = pclsObj->Get(L"Name", 0, &vtProp, 0, 0);
        std::wcout << L"Adapter Name: " << vtProp.bstrVal << std::endl;

        // Durumu al
        hr = pclsObj->Get(L"NetConnectionStatus", 0, &vtProp, 0, 0);
        if (vtProp.vt == VT_NULL) {
            std::wcout << L"  Status: Unknown" << std::endl;
        } else if (vtProp.intVal == 2) {
            std::wcout << L"  Status: Connected" << std::endl;
        } else {
            std::wcout << L"  Status: Disconnected" << std::endl;
        }
        VariantClear(&vtProp);

        std::cout << "----------------------------------------------------------" << std::endl;

        pclsObj->Release();
    }

    pEnumerator->Release();
    pSvc->Release();
    pLoc->Release();
    CoUninitialize();
}

int main() {
    std::cout << "Listing USB Ports:" << std::endl;
    ListUsbPorts();

    std::cout << "\nListing Network Adapters:" << std::endl;
    ListNetworkAdapters();

    return 0;
}
