#include <windows.h>
#include <stdio.h>
#include <dirent.h>

void installProfiles(HWND hwnd);
void updateLog(HWND hwnd, const char *message);

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    static HWND logBox;

    switch (uMsg) {
        case WM_CREATE:
            CreateWindow("BUTTON", "Install Profiles", 
                         WS_VISIBLE | WS_CHILD, 
                         50, 50, 180, 40, 
                         hwnd, (HMENU)1, NULL, NULL);
                         
            logBox = CreateWindow("EDIT", "", 
                                 WS_VISIBLE | WS_CHILD | WS_BORDER | 
                                 ES_MULTILINE | ES_READONLY | WS_VSCROLL,
                                 20, 110, 260, 120, 
                                 hwnd, NULL, NULL, NULL);
            break;
            
        case WM_COMMAND:
            if (LOWORD(wParam) == 1) {
                installProfiles(logBox);
            }
            break;
            
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
                   LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "WiFiCinstaller";

    RegisterClass(&wc);

    HWND hwnd = CreateWindow("WiFiCinstaller", "WiFi Profile Installer", 
                             WS_OVERLAPPEDWINDOW | WS_VISIBLE,
                             100, 100, 320, 280, NULL, NULL, hInstance, NULL);

    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}

void installProfiles(HWND hwnd) {
    DIR *dir;
    struct dirent *ent;
    char command[512];
    char logMessage[512];
    
    updateLog(hwnd, "Starting profile installation...");
    
    if ((dir = opendir("profiles")) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if (strstr(ent->d_name, ".xml")) {
                sprintf(command, "netsh wlan add profile filename=\"profiles\\%s\"", ent->d_name);
                system(command);
                
                sprintf(logMessage, "Installed profile: %s", ent->d_name);
                updateLog(hwnd, logMessage);
            }
        }
        closedir(dir);
        updateLog(hwnd, "All profiles installed successfully!");
    } else {
        updateLog(hwnd, "Error: 'profiles' directory not found!");
    }
}

void updateLog(HWND hwnd, const char *message) {
    char buffer[1024];
    GetWindowText(hwnd, buffer, sizeof(buffer));
    strcat(buffer, message);
    strcat(buffer, "\r\n");
    SetWindowText(hwnd, buffer);
}