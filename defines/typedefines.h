#ifndef typedefines_h
#define typedefines_h

#ifndef decimal_n
	#include <cinttypes>
	#define decimal_n float
#endif

#ifndef signed_n // classic signed value
	#include <cinttypes>
	#define signed_n int16_t
#endif

#ifndef unsigned_n // classic unsigned value
	#include <cinttypes>
	#define unsigned_n uint16_t
#endif

#ifndef unsigned_b // unsigned big
	#include <cinttypes>
	#define unsigned_b uint32_t
#endif

#ifndef signed_b // signed big
	#include <cinttypes>
	#define signed_b int32_t
#endif

#ifndef unsigned_l // unsigned large
	#include <cinttypes>
	#define unsigned_l uint64_t
#endif

#ifndef signed_l // unsigned large
	#include <cinttypes>
	#define signed_l int64_t
#endif

#ifndef signed_h // unsigned large
	#include <cinttypes>
	#define signed_h int128_t
#endif

#ifndef time_now // time now macro
	#include <chrono>
	#define time_now std::chrono::steady_clock::now()
#endif

#ifndef steady // time point
	#include <chrono>
	#define steady std::chrono::time_point<std::chrono::steady_clock>
#endif

#endif
