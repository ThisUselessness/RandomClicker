#include <windows.h>
#include <thread>

#define Button1 6

bool Status = false;

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_DESTROY: PostQuitMessage(0); break;

    case WM_COMMAND:
        if (LOWORD(wParam) == 6) {
            if (Status == false) {
                MessageBox(NULL, L"Рандомный кликер включён\nэкстренная кнопка выключения -> F3", L"RandomClicker", MB_OK);
                Status = true;
            }
            else if (Status == true) { MessageBox(NULL, L"Рандомный кликер уже включён !\nэкстренная кнопка выключения -> F3", L"RandomClicker", MB_OK); }
        }

    default: return DefWindowProc(hwnd, message, wParam, lParam); break;
    }
}

ATOM myRegistryClass(HINSTANCE hInst, int cmdMode) {
    WNDCLASS cw;
    cw.style = CS_VREDRAW | CS_HREDRAW;
    cw.cbClsExtra = 0;
    cw.cbWndExtra = 0;
    cw.hbrBackground = (HBRUSH)(COLOR_WINDOW + 0);
    cw.hCursor = LoadCursor(NULL, IDC_ARROW);
    cw.hIcon = LoadIcon(NULL, IDC_NO);
    cw.hInstance = hInst;
    cw.lpfnWndProc = WndProc;
    cw.lpszClassName = L"WinC";
    cw.lpszMenuName = NULL;

    RegisterClass(&cw);

    return 0;
}

void Funcs() {
    while (true) {
        if (Status == true) {
            SetCursorPos(1 + rand() % 2600, 1 + rand() % 1440);
            mouse_event(MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
            Sleep(60);
        }
        if (GetAsyncKeyState(VK_F3) && Status == true) {
            MessageBox(NULL, L"Рандомный кликер выключён", L"RandomClicer", MB_OK);
            Status = false;
        }
    }
}

BOOL InitInstance(HINSTANCE hInst, int Mode) {
    HWND MainWIN = CreateWindow(L"WinC", L"RandomClicker", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 300, 200, NULL, NULL, hInst, NULL);
    HWND WButton1 = CreateWindowEx(NULL, L"Button", L"Включить", WS_VISIBLE | WS_CHILD | WS_BORDER, 96, 40, 100, 64, MainWIN, (HMENU)Button1, hInst, NULL);

    std::thread(Funcs).detach();

    ShowWindow(MainWIN, Mode);
    UpdateWindow(MainWIN);

    return TRUE;
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR IpszCmdParam, int cmdShow) {
    MSG msg;
    myRegistryClass(hInst, cmdShow);
    InitInstance(hInst, cmdShow);

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}