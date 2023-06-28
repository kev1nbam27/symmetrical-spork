#include <efi/efi.h>
#include <efi/eficon.h>
#include <efi/efilib.h>
#include <efi/x86_64/efibind.h>

EFI_STATUS EFIAPI efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {
    InitializeLib(ImageHandle, SystemTable);
    uefi_call_wrapper(SystemTable->ConOut->Reset, 2, SystemTable->ConOut, 1); // clear screen
    uefi_call_wrapper(SystemTable->ConOut->SetAttribute, 2, SystemTable->ConOut, EFI_LIGHTMAGENTA); // change foreground colour
    uefi_call_wrapper(SystemTable->ConOut->OutputString, 2, SystemTable->ConOut, L"    __  __     ____                             __    ____\r\n   / / / /__  / / /___     _      ______  _____/ /___/ / /\r\n  / /_/ / _ \\/ / / __ \\   | | /| / / __ \\/ ___/ / __  / / \r\n / __  /  __/ / / /_/ /   | |/ |/ / /_/ / /  / / /_/ /_/  \r\n/_/ /_/\\___/_/_/\\____/    |__/|__/\\____/_/  /_/\\__,_(_)"); // display "Hello world! in ascii art

    while (1) {};

    return EFI_SUCCESS;
}
