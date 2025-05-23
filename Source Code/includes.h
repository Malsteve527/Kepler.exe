#include <Windows.h>
#include <iostream>
#include <cmath>
#define PI 3.141592653589793238462643383279502884
extern "C" NTSTATUS NTAPI RtlAdjustPrivilege(ULONG, BOOLEAN, BOOLEAN, PBOOLEAN);
extern "C" NTSTATUS NTAPI NtRaiseHardError(LONG, ULONG, ULONG, PULONG_PTR, ULONG, PULONG);