#include <rvintrin.h>
#include <assert.h>
#include <stdio.h>

#define P  0x11EDC6F41UL
#define P0  0x1EDC6F41
#define mu 0x11F91CAF6UL
#define mu1 0x8FC8E57B
#define k1  0x18571D18
#define k2  0xD7A01665
#define k3  0x3AAB4576

static inline int64_t rdinstret() { int64_t rd; asm volatile ("rdinstret %0" : "=r"(rd)); return rd; }

uint32_t crc32c_table[256] = {
	0x00000000, 0xf26b8303, 0xe13b70f7, 0x1350f3f4, 0xc79a971f, 0x35f1141c, 0x26a1e7e8, 0xd4ca64eb,
	0x8ad958cf, 0x78b2dbcc, 0x6be22838, 0x9989ab3b, 0x4d43cfd0, 0xbf284cd3, 0xac78bf27, 0x5e133c24,
	0x105ec76f, 0xe235446c, 0xf165b798, 0x030e349b, 0xd7c45070, 0x25afd373, 0x36ff2087, 0xc494a384,
	0x9a879fa0, 0x68ec1ca3, 0x7bbcef57, 0x89d76c54, 0x5d1d08bf, 0xaf768bbc, 0xbc267848, 0x4e4dfb4b,
	0x20bd8ede, 0xd2d60ddd, 0xc186fe29, 0x33ed7d2a, 0xe72719c1, 0x154c9ac2, 0x061c6936, 0xf477ea35,
	0xaa64d611, 0x580f5512, 0x4b5fa6e6, 0xb93425e5, 0x6dfe410e, 0x9f95c20d, 0x8cc531f9, 0x7eaeb2fa,
	0x30e349b1, 0xc288cab2, 0xd1d83946, 0x23b3ba45, 0xf779deae, 0x05125dad, 0x1642ae59, 0xe4292d5a,
	0xba3a117e, 0x4851927d, 0x5b016189, 0xa96ae28a, 0x7da08661, 0x8fcb0562, 0x9c9bf696, 0x6ef07595,
	0x417b1dbc, 0xb3109ebf, 0xa0406d4b, 0x522bee48, 0x86e18aa3, 0x748a09a0, 0x67dafa54, 0x95b17957,
	0xcba24573, 0x39c9c670, 0x2a993584, 0xd8f2b687, 0x0c38d26c, 0xfe53516f, 0xed03a29b, 0x1f682198,
	0x5125dad3, 0xa34e59d0, 0xb01eaa24, 0x42752927, 0x96bf4dcc, 0x64d4cecf, 0x77843d3b, 0x85efbe38,
	0xdbfc821c, 0x2997011f, 0x3ac7f2eb, 0xc8ac71e8, 0x1c661503, 0xee0d9600, 0xfd5d65f4, 0x0f36e6f7,
	0x61c69362, 0x93ad1061, 0x80fde395, 0x72966096, 0xa65c047d, 0x5437877e, 0x4767748a, 0xb50cf789,
	0xeb1fcbad, 0x197448ae, 0x0a24bb5a, 0xf84f3859, 0x2c855cb2, 0xdeeedfb1, 0xcdbe2c45, 0x3fd5af46,
	0x7198540d, 0x83f3d70e, 0x90a324fa, 0x62c8a7f9, 0xb602c312, 0x44694011, 0x5739b3e5, 0xa55230e6,
	0xfb410cc2, 0x092a8fc1, 0x1a7a7c35, 0xe811ff36, 0x3cdb9bdd, 0xceb018de, 0xdde0eb2a, 0x2f8b6829,
	0x82f63b78, 0x709db87b, 0x63cd4b8f, 0x91a6c88c, 0x456cac67, 0xb7072f64, 0xa457dc90, 0x563c5f93,
	0x082f63b7, 0xfa44e0b4, 0xe9141340, 0x1b7f9043, 0xcfb5f4a8, 0x3dde77ab, 0x2e8e845f, 0xdce5075c,
	0x92a8fc17, 0x60c37f14, 0x73938ce0, 0x81f80fe3, 0x55326b08, 0xa759e80b, 0xb4091bff, 0x466298fc,
	0x1871a4d8, 0xea1a27db, 0xf94ad42f, 0x0b21572c, 0xdfeb33c7, 0x2d80b0c4, 0x3ed04330, 0xccbbc033,
	0xa24bb5a6, 0x502036a5, 0x4370c551, 0xb11b4652, 0x65d122b9, 0x97baa1ba, 0x84ea524e, 0x7681d14d,
	0x2892ed69, 0xdaf96e6a, 0xc9a99d9e, 0x3bc21e9d, 0xef087a76, 0x1d63f975, 0x0e330a81, 0xfc588982,
	0xb21572c9, 0x407ef1ca, 0x532e023e, 0xa145813d, 0x758fe5d6, 0x87e466d5, 0x94b49521, 0x66df1622,
	0x38cc2a06, 0xcaa7a905, 0xd9f75af1, 0x2b9cd9f2, 0xff56bd19, 0x0d3d3e1a, 0x1e6dcdee, 0xec064eed,
	0xc38d26c4, 0x31e6a5c7, 0x22b65633, 0xd0ddd530, 0x0417b1db, 0xf67c32d8, 0xe52cc12c, 0x1747422f,
	0x49547e0b, 0xbb3ffd08, 0xa86f0efc, 0x5a048dff, 0x8ecee914, 0x7ca56a17, 0x6ff599e3, 0x9d9e1ae0,
	0xd3d3e1ab, 0x21b862a8, 0x32e8915c, 0xc083125f, 0x144976b4, 0xe622f5b7, 0xf5720643, 0x07198540,
	0x590ab964, 0xab613a67, 0xb831c993, 0x4a5a4a90, 0x9e902e7b, 0x6cfbad78, 0x7fab5e8c, 0x8dc0dd8f,
	0xe330a81a, 0x115b2b19, 0x020bd8ed, 0xf0605bee, 0x24aa3f05, 0xd6c1bc06, 0xc5914ff2, 0x37faccf1,
	0x69e9f0d5, 0x9b8273d6, 0x88d28022, 0x7ab90321, 0xae7367ca, 0x5c18e4c9, 0x4f48173d, 0xbd23943e,
	0xf36e6f75, 0x0105ec76, 0x12551f82, 0xe03e9c81, 0x34f4f86a, 0xc69f7b69, 0xd5cf889d, 0x27a40b9e,
	0x79b737ba, 0x8bdcb4b9, 0x988c474d, 0x6ae7c44e, 0xbe2da0a5, 0x4c4623a6, 0x5f16d052, 0xad7d5351
};

uint8_t testdata[1024] __attribute__ ((aligned)) = {
	// for i in {0..1023}; do echo $(( RANDOM % 255)), ; done | fmt
	246, 220, 231, 190, 227, 151, 204, 166, 41, 242, 111, 97, 44, 87, 184,
	121, 85, 240, 77, 11, 73, 85, 184, 192, 134, 33, 126, 194, 244, 152, 37,
	30, 109, 110, 247, 105, 119, 124, 207, 45, 228, 242, 227, 47, 158, 197,
	126, 160, 45, 94, 223, 55, 30, 11, 9, 47, 142, 229, 223, 169, 13, 232,
	58, 233, 53, 102, 249, 181, 37, 55, 182, 60, 55, 19, 212, 176, 193, 13,
	197, 224, 155, 172, 14, 149, 107, 97, 123, 19, 159, 110, 22, 244, 23,
	55, 149, 84, 103, 96, 139, 30, 5, 25, 231, 12, 151, 78, 123, 182, 191,
	207, 250, 34, 98, 214, 207, 7, 210, 8, 185, 7, 65, 57, 106, 162, 192,
	226, 56, 225, 33, 49, 25, 139, 225, 20, 107, 69, 52, 82, 54, 94, 58,
	160, 106, 206, 208, 66, 83, 144, 206, 73, 3, 165, 158, 152, 221, 237,
	205, 24, 68, 185, 56, 9, 253, 204, 172, 35, 249, 29, 202, 183, 136, 11,
	194, 115, 189, 238, 130, 205, 99, 18, 247, 162, 111, 153, 84, 18, 59,
	92, 114, 205, 194, 85, 74, 219, 246, 81, 225, 142, 98, 136, 205, 45, 234,
	253, 51, 103, 59, 217, 238, 139, 52, 72, 237, 146, 218, 99, 126, 37, 54,
	45, 131, 237, 131, 211, 5, 65, 97, 168, 43, 101, 154, 76, 180, 145, 150,
	161, 185, 188, 27, 199, 21, 208, 163, 214, 166, 23, 19, 131, 146, 47,
	250, 38, 69, 189, 175, 130, 222, 81, 186, 59, 86, 31, 199, 54, 12, 18,
	96, 170, 205, 130, 192, 186, 116, 61, 112, 135, 223, 120, 61, 23, 35,
	190, 131, 197, 163, 139, 222, 21, 202, 73, 214, 164, 129, 35, 77, 199,
	178, 3, 203, 228, 54, 132, 30, 199, 7, 253, 5, 244, 64, 93, 213, 199,
	47, 115, 99, 117, 143, 247, 204, 182, 80, 32, 151, 76, 72, 120, 149, 221,
	189, 72, 245, 18, 28, 217, 59, 225, 154, 88, 178, 75, 156, 87, 93, 160,
	92, 80, 83, 32, 107, 108, 9, 155, 203, 139, 22, 214, 111, 16, 209, 100,
	123, 56, 115, 178, 38, 0, 77, 96, 248, 106, 238, 2, 73, 202, 253, 28,
	74, 0, 207, 82, 12, 61, 212, 226, 161, 128, 12, 94, 91, 42, 160, 240,
	160, 199, 246, 195, 120, 142, 42, 18, 27, 202, 231, 226, 170, 180, 161,
	244, 1, 105, 245, 166, 213, 165, 140, 236, 156, 193, 107, 166, 147, 200,
	135, 241, 80, 22, 168, 74, 208, 248, 199, 69, 139, 160, 236, 242, 193,
	114, 224, 133, 237, 125, 121, 96, 44, 13, 131, 38, 166, 106, 70, 116,
	121, 52, 204, 135, 224, 68, 117, 69, 183, 107, 71, 237, 13, 101, 193, 9,
	146, 99, 162, 220, 172, 230, 151, 186, 204, 103, 170, 197, 124, 51, 82,
	64, 227, 63, 207, 185, 61, 71, 82, 53, 45, 2, 199, 46, 253, 138, 161,
	75, 90, 145, 204, 48, 52, 144, 225, 24, 22, 15, 97, 17, 40, 238, 172,
	251, 82, 95, 42, 149, 172, 190, 228, 196, 177, 250, 135, 91, 10, 239,
	152, 154, 179, 55, 34, 182, 171, 75, 46, 71, 91, 34, 128, 135, 200, 15,
	249, 202, 89, 208, 107, 116, 64, 84, 6, 150, 27, 194, 169, 237, 109, 162,
	54, 248, 167, 94, 95, 202, 62, 235, 42, 161, 245, 58, 134, 224, 47, 78,
	93, 1, 163, 132, 209, 252, 222, 195, 205, 162, 164, 95, 132, 194, 38,
	207, 52, 125, 10, 111, 13, 125, 182, 102, 96, 246, 243, 251, 198, 166,
	0, 5, 38, 116, 235, 214, 28, 1, 29, 245, 114, 198, 237, 1, 92, 68, 125,
	192, 33, 69, 231, 156, 0, 39, 231, 191, 103, 13, 104, 176, 47, 58, 92,
	253, 141, 128, 210, 117, 27, 246, 2, 95, 179, 234, 95, 153, 74, 142,
	127, 94, 234, 161, 159, 83, 41, 222, 222, 178, 194, 61, 17, 55, 209,
	1, 39, 199, 70, 196, 11, 4, 15, 227, 205, 19, 174, 100, 32, 43, 147,
	75, 27, 227, 190, 84, 160, 37, 45, 5, 36, 150, 42, 8, 0, 190, 67, 155,
	245, 50, 202, 250, 158, 205, 38, 103, 22, 171, 231, 90, 52, 41, 212,
	54, 145, 94, 122, 181, 121, 163, 183, 153, 142, 9, 36, 111, 160, 240,
	143, 136, 175, 61, 222, 190, 40, 179, 227, 173, 14, 212, 125, 97, 153,
	99, 71, 42, 19, 187, 211, 4, 154, 222, 199, 18, 195, 197, 77, 219, 105,
	131, 237, 242, 103, 32, 178, 114, 66, 191, 213, 43, 52, 237, 175, 80,
	195, 236, 147, 122, 135, 187, 32, 172, 89, 55, 126, 190, 22, 55, 252,
	8, 221, 73, 60, 70, 81, 159, 17, 224, 224, 85, 237, 135, 67, 92, 213,
	52, 193, 90, 42, 73, 205, 7, 14, 154, 100, 226, 164, 218, 128, 127, 46,
	246, 136, 7, 224, 108, 29, 35, 56, 191, 210, 211, 5, 70, 96, 233, 166,
	213, 30, 128, 144, 29, 37, 192, 197, 196, 118, 241, 161, 126, 182, 137,
	150, 118, 127, 113, 16, 138, 204, 109, 104, 110, 190, 56, 63, 216, 251,
	133, 96, 183, 62, 73, 193, 165, 109, 1, 61, 111, 108, 228, 159, 207, 32,
	12, 107, 190, 109, 165, 201, 102, 67, 44, 96, 156, 54, 206, 85, 132, 15,
	227, 211, 234, 97, 252, 146, 115, 191, 143, 196, 1, 143, 238, 33, 207,
	70, 240, 132, 23, 1, 10, 173, 179, 22, 166, 208, 103, 124, 17, 201, 69,
	94, 90, 137, 87, 144, 152, 141, 86, 58, 30, 80, 42, 181, 155, 114, 125,
	205, 216, 184, 135, 117, 134, 142, 160, 161, 245, 39, 13, 23, 190, 211,
	155, 14, 132, 254, 6, 109, 147, 211, 217, 117, 94, 185, 159, 234, 155,
	179, 27, 127, 62, 105, 199, 113, 136, 148, 108, 99, 7, 73, 236, 33, 33,
	156, 152, 2, 34, 14, 24, 208, 47, 217, 17, 248, 207, 233, 33, 202, 71,
	12, 253, 154, 121, 43, 72, 106, 96, 13, 203
};

uint32_t crc32c_lookup(const uint8_t *data, int len)
{
	uint32_t crc = 0xFFFFFFFF;
	const uint8_t *end = data + len;
	while (data != end) {
		int i = 255 & (crc ^ *(data++));
		crc = (crc >> 8) ^ crc32c_table[i];
	}
	return crc ^ 0xFFFFFFFF;
}

uint32_t crc32c_barrett(const uint32_t *data, int len)
{
	uint32_t crc = 0xFFFFFFFF;
	const uint32_t *end = data + len;
	while (data != end) {
		crc ^= _rv32_rev(*(data++));
		crc = _rv32_clmulr(crc, mu1);
		crc = _rv32_clmul(crc, P0);
	}
	return _rv32_rev(crc) ^ 0xFFFFFFFF;
}

uint32_t crc32c_fold(const uint64_t *data, int len)
{
	const uint64_t *end = data + len;
	uint64_t a0, a1, a2, t1, t2;

	assert(len >= 2);
	a0 = _rv64_rev(*(data++));
	a1 = _rv64_rev(*(data++));
	a0 ^= 0xFFFFFFFF00000000UL;

	// Main loop: Reduce to 2x 64 bits
	while (data != end) {
		a2 = _rv64_rev(*(data++));
		t1 = _rv64_clmulh(a0, k1);
		t2 = _rv64_clmul(a0, k1);
		a0 = a1 ^ t1;
		a1 = a2 ^ t2;
	}

	// Reduce to 64 bit, add 32 bit zero padding
	t1 = _rv64_clmulh(a0, k2);
	t2 = _rv64_clmul(a0, k2);
	a0 = (a1 >> 32) ^ t1;
	a1 = (a1 << 32) ^ t2;
	t2 = _rv64_clmul(a0, k3);
	a1 = a1 ^ t2;

	// Barrett Reduction
	t1 = _rv64_clmul(a1 >> 32, mu);
	t2 = _rv64_clmul(t1 >> 32, P);
	a0 = a1 ^ t2;

	return _rv32_rev(a0) ^ 0xFFFFFFFF;
}

uint32_t crc32c_instr(const uint64_t *data, int len)
{
	const uint64_t *end = data + len;
	uint64_t crc = 0xFFFFFFFF;

	while (data != end)
		crc = _rv_crc32c_d(crc ^ *(data++));

	return crc ^ 0xFFFFFFFF;
}

int main()
{
	uint32_t crc, ref;
	int t;

	crc = crc32c_lookup((const uint8_t*)"123456789", 9);
	printf("check 0x%08x\n", crc);
	assert(crc == 0xe3069283);

	printf("\n");

	t = rdinstret();
	crc = crc32c_lookup(testdata, 1024);
	t = rdinstret() - t;
	printf("crc32c_lookup  0x%08x %5d\n", crc, t);
	ref = crc;

	t = rdinstret();
	crc = crc32c_barrett((uint32_t*)testdata, 1024 / 4);
	t = rdinstret() - t;
	printf("crc32c_barrett 0x%08x %5d\n", crc, t);
	assert(ref == crc);

	t = rdinstret();
	crc = crc32c_fold((uint64_t*)testdata, 1024 / 8);
	t = rdinstret() - t;
	printf("crc32c_fold    0x%08x %5d\n", crc, t);
	assert(ref == crc);

	t = rdinstret();
	crc = crc32c_instr((uint64_t*)testdata, 1024 / 8);
	t = rdinstret() - t;
	printf("crc32c_instr   0x%08x %5d\n", crc, t);
	assert(ref == crc);

	printf("\n");

	return 0;
}
