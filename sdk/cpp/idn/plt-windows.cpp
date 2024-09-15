// -------------------------------------------------------------------------------------------------
//  File plt-windows.c
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
//  09/2017 Dirk Apitz, created
// -------------------------------------------------------------------------------------------------

// Standard libraries
#include <stdint.h>

// Platform headers
#define _WINSOCKAPI_   /* Prevent inclusion of winsock.h in windows.h */
#include <windows.h>


// -------------------------------------------------------------------------------------------------
//  Variables
// -------------------------------------------------------------------------------------------------

int plt_monoValid = 0;
LARGE_INTEGER plt_monoCtrFreq;
LARGE_INTEGER plt_monoCtrRef;
uint32_t plt_monoTimeUS = 0;