// -------------------------------------------------------------------------------------------------
//  File plt-windows.h
//
//  Copyright (c) 2016, 2017 DexLogic, Dirk Apitz
//
//  Permission is hereby granted, free of charge, to any person obtaining a copy
//  of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//  copies of the Software, and to permit persons to whom the Software is
//  furnished to do so, subject to the following conditions:
//
//  The above copyright notice and this permission notice shall be included in all
//  copies or substantial portions of the Software.
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//  SOFTWARE.
//
// -------------------------------------------------------------------------------------------------
//  Change History:
//
//  09/2024 Gitle Mikkelsen, adapted to take into consideration the subnet mask of network interfaces
//  06/2017 Dirk Apitz, created
// -------------------------------------------------------------------------------------------------


#ifndef PLT_WINDOWS_H
#define PLT_WINDOWS_H


// Standard libraries
#include <stdint.h>

// Platform headers
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <vector>

#pragma comment(lib, "IPHLPAPI.lib")
#pragma comment(lib, "ws2_32.lib")


// -------------------------------------------------------------------------------------------------
//  Typedefs
// -------------------------------------------------------------------------------------------------

typedef unsigned long in_addr_t;

typedef void(*IFADDR_CALLBACK_PFN)(void* callbackArg, const char* ifName, uint32_t ifIP4Addr, uint32_t ifIP4Mask);


// -------------------------------------------------------------------------------------------------
//  Inline functions
// -------------------------------------------------------------------------------------------------

inline static int plt_validateMonoTime()
{
    extern int plt_monoValid;
    extern LARGE_INTEGER plt_monoCtrFreq;
    extern LARGE_INTEGER plt_monoCtrRef;
    extern uint32_t plt_monoTimeUS;

    extern void logError(const char* fmt, ...);

    if (!plt_monoValid)
    {
        // Get performance counter frequency
        if (QueryPerformanceFrequency(&plt_monoCtrFreq) == 0)
        {
            logError("QueryPerformanceFrequency() error = %d", (int)GetLastError());
            return -1;
        }

        // Initialize performance counter reference
        if (QueryPerformanceCounter(&plt_monoCtrRef) == 0)
        {
            logError("QueryPerformanceCounter() error = %d", (int)GetLastError());
            return -1;
        }

        // Initialize internal time randomly
        plt_monoTimeUS = (uint32_t)((plt_monoCtrRef.QuadPart * 1000000) / plt_monoCtrFreq.QuadPart);
    }

    return 0;
}


inline static uint32_t plt_getMonoTimeUS(void)
{
    extern LARGE_INTEGER plt_monoCtrFreq;
    extern LARGE_INTEGER plt_monoCtrRef;
    extern uint32_t plt_monoTimeUS;

    // Get current time
    LARGE_INTEGER pctNow;
    QueryPerformanceCounter(&pctNow);

    // Update internal time and system time reference
    plt_monoTimeUS += (uint32_t)(((pctNow.QuadPart - plt_monoCtrRef.QuadPart) * 1000000) / plt_monoCtrFreq.QuadPart);
    plt_monoCtrRef = pctNow;

    return plt_monoTimeUS;
}


inline static int plt_ifAddrListVisitor(IFADDR_CALLBACK_PFN pfnCallback, void* callbackArg)
{
    extern void logError(const char* fmt, ...);

    ULONG bufferSize = 0;
    DWORD result = GetAdaptersAddresses(AF_INET, GAA_FLAG_INCLUDE_PREFIX, NULL, NULL, &bufferSize);
    if (result != ERROR_BUFFER_OVERFLOW) {
        //std::cerr << "GetAdaptersAddresses failed to get buffer size." << std::endl;
        return -1;
    }

    std::vector<BYTE> buffer(bufferSize);
    PIP_ADAPTER_ADDRESSES adapters = reinterpret_cast<PIP_ADAPTER_ADDRESSES>(buffer.data());

    result = GetAdaptersAddresses(AF_INET, GAA_FLAG_INCLUDE_PREFIX, NULL, adapters, &bufferSize);
    if (result != NO_ERROR) {
        //std::cerr << "GetAdaptersAddresses failed with error: " << result << std::endl;
        return -1;
    }

    for (PIP_ADAPTER_ADDRESSES adapter = adapters; adapter != NULL; adapter = adapter->Next) {
        //std::cout << "Adapter: " << adapter->AdapterName << std::endl;

        for (PIP_ADAPTER_UNICAST_ADDRESS unicastAddress = adapter->FirstUnicastAddress; unicastAddress != NULL; unicastAddress = unicastAddress->Next) {

            // Get the subnet mask
            if (unicastAddress->OnLinkPrefixLength) {
                UINT8 prefixLength = unicastAddress->OnLinkPrefixLength;

                struct sockaddr_in* sockaddr_ipv4 = (struct sockaddr_in*)unicastAddress->Address.lpSockaddr;
                unsigned int subnetMask = (unsigned int)(0xFFFFFFFF << (32 - prefixLength));
                subnetMask = htonl(subnetMask);

                pfnCallback(callbackArg, adapter->AdapterName, sockaddr_ipv4->sin_addr.S_un.S_addr, subnetMask);
            }
        }
    }

    return 0;
}


inline static int plt_sockStartup()
{
    // Initialize Winsock
    WSADATA wsaData;
    return WSAStartup(MAKEWORD(2, 2), &wsaData);
}


inline static int plt_sockCleanup()
{
    return WSACleanup();
}


inline static int plt_sockGetLastError()
{
    return WSAGetLastError();
}


inline static int plt_sockOpen(int domain, int type, int protocol)
{
    return (int)socket(domain, type, protocol);
}


inline static int plt_sockClose(int fdSocket)
{
    return closesocket(fdSocket);
}


inline static int plt_sockSetBroadcast(int fdSocket)
{
    char bcastOptStr[] = "1";
    return setsockopt(fdSocket, SOL_SOCKET, SO_BROADCAST, bcastOptStr, sizeof(bcastOptStr));
}


#endif

