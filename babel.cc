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
		printf("░░");
	}

	void pixel(bool b){
		printf(b ? "██" : "  ");
	}

	template<uint8_t W, uint8_t Columns>
	void ln(){
		for(uint8_t c = 0; c < Columns; ++c){
			shade();

			for(uint8_t i = 0; i < W; ++i)
				shade();

			shade();
		}

		printf("\n");
	}

	template<uint8_t W, uint8_t Columns>
	void gen(uint64_t a){
		ln<W, Columns>();

		for(uint8_t y = 0; y < W; ++y){
			for(uint8_t column = 0; column < Columns; ++column){
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

constexpr uint64_t MAX		= 5;
constexpr uint64_t LEN		= 1 << (MAX * MAX);
constexpr uint8_t  COLUMNS	= 13;

int main(){
	for(uint64_t i = 0; i < LEN; i += COLUMNS)
		gen<MAX, COLUMNS>(i);
}

