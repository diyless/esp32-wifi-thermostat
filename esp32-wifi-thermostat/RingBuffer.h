#ifndef RINGBUFFER_h
#define RINGBUFFER_h

#include <stdlib.h>
#include <inttypes.h>

struct ChartItem {
	uint8_t status;
	uint8_t ch_temperature;
	uint8_t room_temperature;
	uint8_t modulation;
	bool marked;
};


template <typename T, uint16_t Size>
class RingBuffer {
private:
	const uint16_t size;
	T buf[Size];
	T* write_p;
	T* read_p;
	T* end_p;
	uint16_t count;
public:
	RingBuffer() : size(Size), write_p(buf), read_p(buf), end_p(buf + Size), count(0) {}

	T* push() {
		T* result = write_p++;
		if (write_p == end_p) write_p = buf;
		if (count < size) {
			count++;
		}
		else {
			read_p++;
			if (read_p == end_p) read_p = buf;
		}
		return result;
	}

	T* peek(uint16_t index = 0) {
		if (index >= count) {
			return NULL;
		}
		T* result = read_p + index;
		if (result >= end_p) {
			result = buf + (result - end_p);
		}
		return result;
	}

	T* pop() {
		if (count <= 0) {
			return NULL;
		}
		T* result = read_p++;
		count--;
		if (read_p == end_p) read_p = buf;
		return result;
	}

	uint16_t getCount() const {
		return count;
	}

	uint16_t getSize() const {
		return size;
	}

	bool isEmpty() const {
		return count <= 0;
	}

	bool isFull() const {
		return count >= size;
	}
};

#endif
