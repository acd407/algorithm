#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
//1000/math.log(10,2) = 301.0299956639812 < 302
int main () {
	char num[302] = {0};
	num[0] = 1;
	for(int _i_ = 0; _i_ < 1000; _i_++) {
		int offset = 0;
		while(offset<302) {
			num[offset] *= 2;
			offset++;
		}
		offset = 0;
		while(offset<302) {
			num[offset+1] += num[offset] / 10;
			num[offset] %= 10;
			offset++;
		}
	}
	uint64_t sum = 0;
	for(int _i_ = 0; _i_ < 302; _i_++)
		sum += num[_i_];
	printf("%lld", sum);
	return 0;
}