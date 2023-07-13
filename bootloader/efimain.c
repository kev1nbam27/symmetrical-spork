#include <efi/efi.h>
#include <efi/eficon.h>
#include <efi/efidevp.h>
#include <efi/efilib.h>
#include <efi/efiprot.h>
#include <efi/x86_64/efibind.h>

EFI_STATUS EFIAPI efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable) {
    InitializeLib(ImageHandle, SystemTable);
    uefi_call_wrapper(SystemTable->ConOut->Reset, 2, SystemTable->ConOut, 1); // clear screen
    uefi_call_wrapper(SystemTable->ConOut->SetAttribute, 2, SystemTable->ConOut, EFI_LIGHTMAGENTA); // change foreground colour
    uefi_call_wrapper(SystemTable->ConOut->OutputString, 2, SystemTable->ConOut, L"    __  __     ____                             __    ____\r\n   / / / /__  / / /___     _      ______  _____/ /___/ / /\r\n  / /_/ / _ \\/ / / __ \\   | | /| / / __ \\/ ___/ / __  / / \r\n / __  /  __/ / / /_/ /   | |/ |/ / /_/ / /  / / /_/ /_/  \r\n/_/ /_/\\___/_/_/\\____/    |__/|__/\\____/_/  /_/\\__,_(_)\r\n\n\n"); // display "Hello world! in ascii art
    uefi_call_wrapper(SystemTable->ConOut->SetAttribute, 2, SystemTable->ConOut, EFI_LIGHTGRAY); // change foreground colour

    EFI_LOADED_IMAGE *LoadedImage = NULL;
    EFI_DEVICE_PATH *DevicePath = NULL;

    // get info about the image
    uefi_call_wrapper(SystemTable->BootServices->HandleProtocol, 3, ImageHandle, &LoadedImageProtocol, (void **) &LoadedImage);
    uefi_call_wrapper(SystemTable->BootServices->HandleProtocol, 3, LoadedImage->DeviceHandle, &DevicePathProtocol, (void **) &DevicePath);

    // print it
    Print(L"Image device : %s\n", DevicePathToStr(DevicePath));
    Print(L"Image file   : %s\n", DevicePathToStr(LoadedImage->FilePath));
    Print(L"Image base   : 0x%X\n", LoadedImage->ImageBase);
    Print(L"Image size   : %ldK\n", LoadedImage->ImageSize/1000);

    while (1) {};

    return EFI_SUCCESS;
}
