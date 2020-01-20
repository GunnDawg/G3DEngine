Download and run DXSDK_Jun10.exe to install DirectX SDK version 9.29.1962 from this page:
https://www.microsoft.com/en-us/download/confirmation.aspx?id=6812

If you get error code S1023 at the end of the install process, it means you have a newer version of the MSVC 2010 Redistributable. Run these commands in admin command prompt to uninstall the newer versions:

    MsiExec.exe /passive /X{F0C3E5D1-1ADE-321E-8167-68EF0DE699A5}
    MsiExec.exe /passive /X{1D8E6291-B0D5-35EC-8441-6616F567A0F7}

Source:
https://support.microsoft.com/en-us/help/2728613/s1023-error-when-you-install-the-directx-sdk-june-2010