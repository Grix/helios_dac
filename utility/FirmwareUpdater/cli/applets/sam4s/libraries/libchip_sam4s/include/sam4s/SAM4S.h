/* %ATMEL_LICENCE% */

#ifndef _SAM4S_
#define _SAM4S_

#if defined __SAM4S4A__
  #include "SAM4S4A.h"
#elif defined __SAM4S4B__
  #include "SAM4S4B.h"
#elif defined __SAM4S4C__
  #include "SAM4S4C.h"
#elif defined __SAM4S8A__
  #include "SAM4S8A.h"
#elif defined __SAM4S8B__
  #include "SAM4S8B.h"
#elif defined __SAM4S8C__
  #include "SAM4S8C.h"
#elif defined __SAM4S16A__
  #include "SAM4S16A.h"
#elif defined __SAM4S16B__
  #include "SAM4S16B.h"
#elif defined __SAM4S16C__
  #include "SAM4S16C.h"
#elif defined __SAM4SD32B__
  #include "SAM4SD32B.h"
#elif defined __SAM4SD32C__
  #include "SAM4SD32C.h"
#elif defined __SAM4S2C__
  #include "SAM4S2C.h"
#else
  #error Library does not support the specified device.
#endif

#endif /* _SAM4S_ */
