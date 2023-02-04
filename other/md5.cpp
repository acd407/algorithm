#include <fmt/core.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>

// 错误处理
enum num_level { error = 0, warning = 1, info = 2 };
const char *levels[] = {"\033[91merror:\033[0m", "\033[95mwarning:\033[0m",
						"\033[96minfo:\033[0m"};
template <int level>
void interupt(const char *file, int line, const char *whicherr) {
	fmt::print("{}:{}: {} {}\n", file, line, levels[level], whicherr);
	if (!level)
		exit(EXIT_FAILURE);
}

#define ERROR(description)   interupt<error>(__FILE__, __LINE__, description)
#define WARNING(description) interupt<warning>(__FILE__, __LINE__, description)
#define INFO(description)    interupt<info>(__FILE__, __LINE__, description)

// md5vm类
class md5vm {
	uint32_t a, b, c, d;
	const uint32_t A = 0x67452301,
		B = 0xEFCDAB89,
		C = 0x98BADCFE,
		D = 0x10325476;
	const uint32_t s[4][4] {
		{7, 12, 17, 22},
		{5,  9, 14, 20},
		{4, 11, 16, 23},
		{6, 10, 15, 21}
	};
	uint32_t t[64];
	static inline void swap(uint32_t &a, uint32_t &b, uint32_t &c, uint32_t &d);
	void calc(const uint8_t *buf);

public:
	md5vm();
	std::string md5(std::string src);
};

inline md5vm::md5vm() {
	a = A, b = B, c = C, d = D;
	for (int i = 0; i < 64; ++i) // 4294967296 = 1 << 32
		t[i] = uint32_t(4294967296.0 * fabs(sin((double) i + 1)));
}

inline void md5vm::swap(uint32_t &a, uint32_t &b, uint32_t &c, uint32_t &d) {
	uint32_t tmp = d;
	d = c;
	c = b;
	b = a;
	a = tmp;
}

// 8个函数的定义
// 定义为4个函数和1个函数
static uint32_t F(uint32_t x, uint32_t  y, uint32_t  z) { return ((x & y) | (~x & z)); }
static uint32_t G(uint32_t x, uint32_t  y, uint32_t  z) { return ((x & z) | (y & ~z)); }
static uint32_t H(uint32_t x, uint32_t  y, uint32_t  z) { return (x ^ y ^ z); }
static uint32_t I(uint32_t x, uint32_t  y, uint32_t  z) { return (y ^ (x | ~z)); }
static decltype(F) *f[4] {F,G,H,I};

// 循环左移
template<typename T1, typename T2>
static constexpr auto ROTATE_LEFT(T1 x, T2  n) { return ((x << n) | (x >> (32 - n))); }

static uint32_t ff(uint32_t &a, uint32_t &b, uint32_t &c, uint32_t &d,
	uint32_t  m, uint32_t  s, uint32_t  t, decltype(F) *f) {
	return (a = b + (ROTATE_LEFT((a + f(b, c, d) + m + t), s)));
}

// 主处理函数
inline void md5vm::calc(const uint8_t *buf) {
	//for (int i = 0; i < 64; ++i) {
	//	fmt::print("{:0>2x}{}", buf[i], (!((i + 1) % 8)) ? '\n' : ' ');
	//}
	//putchar('\n');
	
	uint32_t *M = (uint32_t *) buf;

	const uint16_t magic_1[] {1,5,3,7};
	const uint16_t magic_2[] {0,1,5,0};
	for (size_t h = 0; h < 4; ++h)
		for (size_t i = 0; i < 4; ++i)
			for (size_t j = 0; j < 4; ++j) {
				ff(a, b, c, d, M[((i * 4 + j) * magic_1[h] + magic_2[h]) % 16], s[h][j],
					t[(i + h * 4) * 4 + j], f[h]);
				swap(a, b, c, d);
			}
	a += A, b += B, c += C, d += D;
}

static inline auto swap32(uint32_t v) {
	return ((v >> 24) | ((v & 0x00ff0000) >> 8) | ((v & 0x0000ff00) << 8) | (v << 24)); 
}

constexpr auto block_size = 64; // 每次处理部分的字节数
// 主函数
inline std::string md5vm::md5(std::string src) {
	union {
		size_t size;
		uint8_t bits[sizeof(uint64_t)];
	} len_bit {
		.size = src.length() * sizeof(uint64_t),
	};
	src.push_back((char) 0b10000000);
	if (src.length() % block_size + sizeof(uint64_t) < block_size)
		// 容得下长度
		src.append(block_size - src.length() % block_size - sizeof(uint64_t), '\0');
	else
		src.append(2 * block_size - src.length() % block_size - sizeof(uint64_t), '\0');
	for (size_t i = 0; i < sizeof(uint64_t); i++)
		src.push_back(len_bit.bits[i]);
	if (src.length() % block_size) {
		ERROR("num of '\\0' is not correct.");
	}
	size_t blocks = src.length() / block_size;
	for (size_t i = 0; i < blocks; i++) {
		md5vm::calc((const uint8_t *) src.c_str() + i * block_size);
	}
	return fmt::format("{:0>8x}{:0>8x}{:0>8x}{:0>8x}", swap32(a), swap32(b), swap32(c), swap32(d));
}

int main(int argc, char **argv) {
	if (argc != 2)
		ERROR("arguments error");
	auto md5 = new md5vm();
	fmt::print("{}", md5->md5(argv[1]));
	return 0;
}