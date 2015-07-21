float frand(void) {
	static unsigned x = 123456789, y = 362436069, z = 521288629, w = 88675123;
	unsigned t = x^x << 11; x = y; y = z; z = w; w ^= w >> 19 ^ t^t >> 8;
	return (float)(w*(1.0 / 4294967296.0));
}