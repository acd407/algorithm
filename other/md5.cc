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

constexpr auto block_size = 64; // 每次处理部分的字节数

unsigned int t[64];

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

const unsigned int s[4][4] {
    {7, 12, 17, 22},
    {5,  9, 14, 20},
    {4, 11, 16, 23},
    {6, 10, 15, 21}
};

static inline void swap (uint32_t &a, uint32_t &b, uint32_t &c, uint32_t &d) {
    uint32_t tmp = d;
    d = c;
    c = b;
    b = a;
    a = tmp;
}
const uint32_t  A = 0x67452301,
                B = 0xEFCDAB89,
                C = 0x98BADCFE,
                D = 0x10325476;
uint32_t a = A, b = B, c = C, d = D;
void calc(const uint8_t *buf) {
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

int main (int argc, char **argv) {
    if (argc != 2)
        ERROR ("arguments not enough!");
    FILE *fp {fopen (argv[1], "rb")};
    if (! fp)
        ERROR ("file open error!");

    // 获取文件长度
    fseek (fp, 0, SEEK_END);
    uint64_t file_size {(uint64_t) ftell (fp)};
    rewind (fp);

    // 初始化64个整数
    for (int i = 0; i < 64; ++i) { // 4294967296 = 1 << 32
        t[i] = (unsigned int) (4294967296.0 * fabs (sin ((double) i + 1)));
    }

    uint8_t *buf {(uint8_t *) malloc (block_size)};

    while (true) {
        size_t read_size {fread (buf, 1, block_size, fp)};
        if (read_size < block_size) { // 读到末尾了
            // 写得下8个末尾长度字节和一个标志
            if (read_size + 8 + 1 < block_size) {
                int i = read_size;
                buf[i] = 0x80; // 填1
                while (i < block_size - 8)
                    buf[i++] = 0x00; // 填0
                // 写入文件大小
                *((uint64_t *) (buf + i)) = (file_size * 8);
                calc (buf);
                break;
            } else { // 填充1再使用一个block
                int i = read_size;
                buf[i] = 0x80; // 填1
                while (i < block_size)
                    buf[i++] = 0x00; // 填0
                calc (buf);

                i = 0;
                while (i < block_size - 8)
                    buf[i++] = 0x00; // 填0
                // 写入文件大小
                *((uint64_t *) (buf + i)) = (file_size * 8);
                calc (buf);
                break;
            }
        } else { // 正常读取
            calc (buf);
        }
    }
    fmt::print ("{:0>8x}{:0>8x}{:0>8x}{:0>8x}", swap32(a), swap32(b), swap32(c), swap32(d));
    free (fp);
    return 0;
}