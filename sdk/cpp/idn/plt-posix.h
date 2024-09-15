// -------------------------------------------------------------------------------------------------
//  File plt-posix.h
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
//  06/2017 Dirk Apitz, created
// -------------------------------------------------------------------------------------------------


#ifndef PLT_POSIX_H
#define PLT_POSIX_H


// Standard libraries
#include <unistd.h>
#include <errno.h>

// Platform headers
#include <arpa/inet.h>

typedef void (*IFADDR_CALLBACK_PFN)(void* callbackArg, const char* ifName, uint32_t ifIP4Addr, uint32_t ifIP4Mask);

#ifdef __APPLE__
#include <sys/types.h>
#include <sys/_types/_timespec.h>
#include <mach/mach.h>
#include <mach/clock.h>
#include <mach/mach_time.h>

#define TIMER_ABSTIME -1
#define MT_NANO (+1.0E-9)
#define MT_GIGA UINT64_C(1000000000)

// TODO create a list of timers,
static double mt_timebase = 0.0;
static uint64_t mt_timestart = 0;
inline int mach_clock_gettime(int clk_id, struct timespec *tp)
{
    kern_return_t retval = KERN_SUCCESS;
    if( clk_id == TIMER_ABSTIME) {
        if (!mt_timestart) { // only one timer, initilized on the first call to the TIMER
            mach_timebase_info_data_t tb = { 0 };
            mach_timebase_info(&tb);
            mt_timebase = tb.numer;
            mt_timebase /= tb.denom;
            mt_timestart = mach_absolute_time();
        }
        
        double diff = (mach_absolute_time() - mt_timestart) * mt_timebase;
        tp->tv_sec = diff * MT_NANO;
        tp->tv_nsec = diff - (tp->tv_sec * MT_GIGA);
    }
    else { // other clk_ids are mapped to the coresponding mach clock_service
        clock_serv_t cclock;
        mach_timespec_t mts;
        
        host_get_clock_service(mach_host_self(), clk_id, &cclock);
        retval = clock_get_time(cclock, &mts);
        mach_port_deallocate(mach_task_self(), cclock);
        
        tp->tv_sec = mts.tv_sec;
        tp->tv_nsec = mts.tv_nsec;
    }
    
    return retval;
}
#else
#include <time.h>
#endif

// -------------------------------------------------------------------------------------------------
//  Inline functions
// -------------------------------------------------------------------------------------------------

inline static int plt_validateMonoTime()
{
    extern int plt_monoValid;
    extern struct timespec plt_monoRef;
    extern uint32_t plt_monoTimeUS;
    

    if(!plt_monoValid)
    {
        // Initialize time reference
#ifdef __APPLE__
        if(mach_clock_gettime(SYSTEM_CLOCK, &plt_monoRef) < 0) return -1;
#else
        if(clock_gettime(CLOCK_MONOTONIC, &plt_monoRef) < 0) return -1;
#endif
        
        
        // Initialize internal time randomly
        plt_monoTimeUS = (uint32_t)((plt_monoRef.tv_sec * 1000000ul) + (plt_monoRef.tv_nsec / 1000));
        plt_monoValid = 1;
    }

    return 0;
}


inline static uint32_t plt_getMonoTimeUS()
{
    extern struct timespec plt_monoRef;
    extern uint32_t plt_monoTimeUS;

    // Get current time
    struct timespec tsNow, tsDiff;
#ifdef __APPLE__
    mach_clock_gettime(SYSTEM_CLOCK, &tsNow);
#else
    clock_gettime(CLOCK_MONOTONIC, &tsNow);
#endif

    // Determine difference to reference time
    if(tsNow.tv_nsec < plt_monoRef.tv_nsec) 
    {
        tsDiff.tv_sec = (tsNow.tv_sec - plt_monoRef.tv_sec) - 1;
        tsDiff.tv_nsec = (1000000000 + tsNow.tv_nsec) - plt_monoRef.tv_nsec;
    } 
    else 
    {
        tsDiff.tv_sec = tsNow.tv_sec - plt_monoRef.tv_sec;
        tsDiff.tv_nsec = tsNow.tv_nsec - plt_monoRef.tv_nsec;
    }

    // Update internal time and system time reference
    plt_monoTimeUS += (uint32_t)((tsDiff.tv_sec * 1000000) + (tsDiff.tv_nsec / 1000));
    plt_monoRef = tsNow;

    return plt_monoTimeUS;
}


inline static int plt_usleep(unsigned usec)
{
    return usleep(usec);
}


inline static FILE *plt_fopen(const char *filename, const char *mode)
{
    return fopen(filename, mode);
}


inline static int plt_sockStartup()
{
    return 0;
}


inline static int plt_sockCleanup()
{
    return 0;
}


inline static int plt_sockGetLastError()
{
    return errno;
}


inline static int plt_sockOpen(int domain, int type, int protocol)
{
    return socket(domain, type, protocol);
}


inline static int plt_sockClose(int fdSocket)
{
    return close(fdSocket);
}

inline static int plt_sockSetBroadcast(int fdSocket)
{
//#ifdef __APPLE__
    int bcastOptStr[] = {1};
//#else
//    char bcastOptStr[] = "1";
//#endif
    return setsockopt(fdSocket, SOL_SOCKET, SO_BROADCAST, bcastOptStr, sizeof(bcastOptStr));
}

inline static int plt_ifAddrListVisitor(IFADDR_CALLBACK_PFN pfnCallback, void *callbackArg)
{
    // Find all interfaces
    struct ifaddrs *ifaddr;
    if(getifaddrs(&ifaddr) == -1) return errno;

    // Walk through all interfaces
    for(struct ifaddrs *ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next)
    {
        if(ifa->ifa_addr == NULL) continue;
        if(ifa->ifa_addr->sa_family != AF_INET) continue;

        // Invoke callback on interface
        struct sockaddr_in *ifSockAddr = (struct sockaddr_in *)ifa->ifa_addr;
        struct sockaddr_in *ifSockMask = (struct sockaddr_in *)ifa->ifa_netmask;
        pfnCallback(callbackArg, ifa->ifa_name, (uint32_t)(ifSockAddr->sin_addr.s_addr), (uint32_t)(ifSockMask->sin_addr.s_addr));
    }

    // Interface list is dynamically allocated and must be freed
    freeifaddrs(ifaddr);

    return 0;
}

#endif

