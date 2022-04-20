#include <Windows.h>
#include <iostream>
#include <vector>
#include <cstdio>

std::wstring getMonitorName(HMONITOR monitor) {
    DISPLAYCONFIG_TOPOLOGY_ID currentTopologyId;
    MONITORINFOEXW info;
    info.cbSize = sizeof(info);
    GetMonitorInfoW(monitor, &info);

    UINT32 requiredPaths, requiredModes;
    GetDisplayConfigBufferSizes(QDC_ONLY_ACTIVE_PATHS, &requiredPaths, &requiredModes);
    std::vector<DISPLAYCONFIG_PATH_INFO> paths(requiredPaths);
    std::vector<DISPLAYCONFIG_MODE_INFO> modes(requiredModes);
    QueryDisplayConfig(QDC_DATABASE_CURRENT, &requiredPaths, paths.data(), &requiredModes, modes.data(), &currentTopologyId);
   
    for (auto& p : paths) {
        DISPLAYCONFIG_SOURCE_DEVICE_NAME sourceName;
        sourceName.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_SOURCE_NAME;
        sourceName.header.size = sizeof(sourceName);
        sourceName.header.adapterId = p.sourceInfo.adapterId;
        sourceName.header.id = p.sourceInfo.id;
      
        DisplayConfigGetDeviceInfo(&sourceName.header);
        if (wcscmp(info.szDevice, sourceName.viewGdiDeviceName) == 0) {
            DISPLAYCONFIG_TARGET_DEVICE_NAME name;
            name.header.type = DISPLAYCONFIG_DEVICE_INFO_GET_TARGET_NAME;
            name.header.size = sizeof(name);
            name.header.adapterId = p.sourceInfo.adapterId;
            name.header.id = p.targetInfo.id;
            DisplayConfigGetDeviceInfo(&name.header);
            return std::wstring(name.monitorFriendlyDeviceName);
        }
    }
    return L"";
}


BOOL CALLBACK MyInfoEnumProc(
    HMONITOR hMonitor,
    HDC hdcMonitor,
    LPRECT lprcMonitor,
    LPARAM dwData
)
{
    MONITORINFOEX mi;
    ZeroMemory(&mi, sizeof(mi));
    mi.cbSize = sizeof(mi);
    GetMonitorInfo(hMonitor, &mi);
    wprintf(L"DisplayDevice: %s\n", mi.szDevice);

    std::wcout << L"Name: " << getMonitorName(hMonitor) << L"\n";
    return TRUE;
}

int main()
{
    EnumDisplayMonitors(NULL, NULL, MyInfoEnumProc, 0);
    return 0;
}