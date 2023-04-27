#include "unity_config.h"
#include <stdio.h>
/* 
 * test_common tests are executed by both native + embedded targets
 * for the embedded targets we are forced to have unity_config.c in this folder.
 * however, that would then also be used on the native target.
 * So, we have to conditionally provide the native or embedded code here.
 * For simplicity, we use the global "GD32F3x0" macro that will be present
 * when compiling for our embedded targets. Otherwise, we could also check
 * some built-in macros like __ARM_EABI__, __ARM_ARCH_7M__, etc.
 */
#ifdef GD32F3x0
/* to avoid code duplication: let's use the same .c file as in the embedded folder already. */
/* a bit hacky and makes us dependent on test_embedded existing. Copy-paste code if needed. */
#include "../test_embedded/unity_config.c"
#else
/* for platform = native */
void unityOutputStart(unsigned long baudrate) { }
void unityOutputChar(char c) { putchar(c); }
void unityOutputFlush(void) { fflush(stdout); }
void unityOutputComplete(void) { }
#endif