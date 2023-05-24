#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdexcept>
#include <initializer_list>
#include <vector>

class BN { // reverse storage
    public:
        size_t length = 0;
        uint32_t* bits;
        void print() {
            size_t i = length;
            while (i)
                printf ("%08x", bits[--i]);
            printf ("\n");
        }
        BN() {};
        BN(char* s) {
            uint32_t n = atoll(s);
            if (n <= 0) {
                throw std::invalid_argument("input argument must be a positive number string, and less than UINT_MAX");
            }
            bits = new uint32_t{n};
            length = 1;
        }
        BN(std::initializer_list<uint32_t> l) {
            length = l.size();
            bits = (*new std::vector<uint32_t> {l}).data();
        }
        BN (int l, uint32_t* ptr): length(l), bits(ptr) {}
        void add (BN);
        void mul (BN);
};

void BN::add (BN source) {
    uint32_t* _ =
        (uint32_t*) realloc (bits, __max (length, source.length) + 1);
    if (bits == 0)
        bits = _;
    for (size_t i = length; i < __max (length, source.length) + 1; i++)
        bits[i] = 0;
    for (size_t i = 0; i < __max (length, source.length); i++) {
        uint64_t buff = (uint64_t) bits[i] + source.bits[i];
        if (buff > UINT_MAX) {
            uint32_t* ptr = (uint32_t*) &buff;
            bits[i] = *ptr;
            bits[i + 1] += *(ptr + 1);
        } else
            bits[i] += source.bits[i];
    }
    if (bits[__max (length, source.length)] != 0)
        length = __max (length, source.length) + 1;
    else
        length = __max (length, source.length);
}
void operator+= (BN& target, BN source) {
    target.add (source);
}

BN plus (BN target, BN source) {
    uint32_t* buff = (uint32_t*) malloc (sizeof (uint32_t) * target.length);
    for (size_t i = 0; i < target.length; i++)
        buff[i] = target.bits[i];
    target.add (source);
    BN ret;
    ret.length = target.length;
    ret.bits = target.bits;
    target.bits = buff;
    return ret;
}
BN operator+ (BN target, BN source) {
    return plus (target, source);
}

void BN::mul (BN source) {
    // 64位缓冲区
    uint64_t* buff = new uint64_t[length + source.length]{0};
    // 主计算
    for (size_t i = 0; i < length; i++)
        for (size_t j = 0; j < source.length; j++) {
            buff[i + j] += (uint64_t) bits[i] * source.bits[j];
            if (buff[i + j] > UINT_MAX) { // 判断进位
                // 用指针取高32位
                uint32_t* ptr = (uint32_t*) & (buff[i + j]);
                buff[i + j + 1] += *++ptr; // ptr指向低位，ptr+1指向高位
                *ptr = 0;
            }
        }
    // 检测大小
    size_t i = 0;
    while (i < length + source.length && buff[i])
        i++;
    length = i;
    // 重新分配内存
    uint32_t* _ = (uint32_t*) realloc (bits, i * sizeof (uint32_t));
    if (bits == 0)
        bits = _;
    // 拷贝
    for (size_t j = 0; j < i; j++)
        bits[j] = (uint32_t) buff[j];
    // 销毁
    delete[] buff;
}
void operator*= (BN& target, BN source) {
    target.mul (source);
}

BN times (BN target, BN source) {
    uint64_t* buff =
        (uint64_t*) calloc (target.length + source.length, sizeof (uint64_t));
    for (size_t i = 0; i < target.length; i++)
        for (size_t j = 0; j < source.length; j++) {
            buff[i + j] += (uint64_t) target.bits[i] * source.bits[j];
            if (buff[i + j] > UINT_MAX) {
                uint32_t* ptr = (uint32_t*) & (buff[i + j]); // higher 32 bits
                buff[i + j + 1] += *++ptr;
                *ptr = 0;
            }
        }
    size_t i = 0;
    while (i < target.length + source.length && buff[i])
        i++;
    BN ret;
    ret.bits = (uint32_t*) malloc (i * sizeof (uint32_t));
    ret.length = i;
    for (size_t j = 0; j < i; j++)
        ret.bits[j] = (uint32_t) buff[j];
    return ret;
    free (buff);
}
BN operator* (BN target, BN source) {
    return times (target, source);
}
