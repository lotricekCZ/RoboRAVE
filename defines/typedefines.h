#ifndef typedefines_h
#define typedefines_h

#ifndef decimal_n
	#define decimal_n float
#endif

#ifndef signed_n // classic signed value
	#include <inttypes.h>
	#define signed_n int16_t
#endif

#ifndef unsigned_n // classic unsigned value
	#include <inttypes.h>
	#define unsigned_n uint16_t
#endif

#ifndef unsigned_b // unsigned big
	#include <inttypes.h>
	#define unsigned_b uint32_t
#endif

#ifndef unsigned_l // unsigned large
	#include <inttypes.h>
	#define unsigned_l uint64_t
#endif

#ifndef signed_l // unsigned large
	#include <inttypes.h>
	#define signed_l int64_t
#endif

#ifndef signed_b // signed big
	#include <inttypes.h>
	#define signed_b int32_t
#endif

#endif
