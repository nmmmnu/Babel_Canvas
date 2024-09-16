#include <cstdint>
#include <cassert>

#include <cstdio>

namespace {
	constexpr uint64_t mask(uint8_t a){
		assert(a >= 0 && a < 64);

		return uint64_t{ 1 } << a;
	}

	template<uint8_t W>
	constexpr bool matrix(uint64_t a, uint8_t x, uint8_t y){
		auto const z = y * W + x;

		return a & mask(z);
	}

	void shade(){
		printf(" 127 127 127 ");
	}

	void pixel(bool b){
		printf(b ? " 255 255 255 " : " 0 0 0 ");
	}

	template<uint8_t W, uint16_t Columns>
	void ln(){
		for(uint16_t c = 0; c < Columns; ++c){
			shade();

			for(uint8_t i = 0; i < W; ++i)
				shade();

			shade();
		}

		printf("\n");
	}

	template<uint8_t W, uint16_t Columns>
	void gen(uint64_t a){
		ln<W, Columns>();

		for(uint8_t y = 0; y < W; ++y){
			for(uint16_t column = 0; column < Columns; ++column){
				shade();

				for(uint8_t x = 0; x < W; ++x){
					auto const b = matrix<W>(a + column, x, y);

					pixel(b);
				}

				shade();
			}

			printf("\n");
		}

		ln<W, Columns>();
	}

} // anonymous namespace

template<int>
struct Conf;

template<>
struct Conf<3>{
	constexpr static uint64_t MAX		= 3;
	constexpr static uint16_t COLUMNS	= 32;
};

template<>
struct Conf<4>{
	constexpr static uint64_t MAX		= 4;
	constexpr static uint16_t COLUMNS	= 64;
};

template<>
struct Conf<5>{
	constexpr static uint64_t MAX		= 5;
	constexpr static uint16_t COLUMNS	= 512;
};

template<>
struct Conf<6>{
	constexpr static uint64_t MAX		= 5;
	constexpr static uint16_t COLUMNS	= 4096;
};

using MyConf = Conf<3>;

constexpr uint64_t MAX		= MyConf::MAX;
constexpr uint16_t COLUMNS	= MyConf::COLUMNS;

constexpr uint64_t TOTAL	= 1 << (MAX * MAX);

constexpr uint64_t IMAGE_X = (MAX + 2) * COLUMNS;
constexpr uint64_t IMAGE_Y = (MAX + 2) * (TOTAL / COLUMNS);

int main(){
	printf("P3\n");
	printf("%u %u\n", IMAGE_X, IMAGE_Y);
	printf("255\n");

	for(uint64_t i = 0; i < TOTAL; i += COLUMNS)
		gen<MAX, COLUMNS>(i);
}

