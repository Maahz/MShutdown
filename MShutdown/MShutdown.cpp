#include <Windows.h>
#include "Worker.h"
#include <iostream>


HHOOK _hook;

KBDLLHOOKSTRUCT kbdStruct;

LRESULT CALLBACK HookCallback(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode >= 0)
    {
        kbdStruct = *((KBDLLHOOKSTRUCT*)lParam);

        BYTE KeyboardState[256] = {};

        wchar_t UnicodeCharacter[3] = {};

        GetKeyState(VK_SHIFT);
        GetKeyState(VK_MENU);
        //GetKeyboardState(KeyboardState);

        ToUnicodeEx((UINT)kbdStruct.vkCode, (UINT)kbdStruct.scanCode, KeyboardState, UnicodeCharacter, sizeof(UnicodeCharacter) / sizeof(*UnicodeCharacter) - 1, (UINT)kbdStruct.flags, GetKeyboardLayout(0));

        switch (wParam)
        {

            //---KB Hooks---
        case WM_KEYDOWN:
            if (GetKeyState(VK_CONTROL) && GetKeyState(VK_SHIFT))
            {
                if ((char)UnicodeCharacter[0] == 'q')
                {
                    Worker::Shutdown();
                }
            }
            
            break;
        }

    }
    return CallNextHookEx(_hook, nCode, wParam, lParam);
}


int main()
{   
    //Hide console window
    ShowWindow(GetConsoleWindow(), SW_HIDE);

    //Setup low level keyboard hook
    _hook = SetWindowsHookEx(WH_KEYBOARD_LL, HookCallback, NULL, 0);

    MSG msg;
    while (GetMessage(&msg, 0, 0, 0))
    {
        PeekMessage(&msg, 0, 0, 0, 0x0001);
        Sleep(1);
    }
        
}
