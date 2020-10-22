#include <iostream>

using namespace std;

const int offsetBlockAvailablity = 1;
const int offsetCurrBlockSize = 4;
const int headerSize = 5;
const int alignment = 4;

class Allocator {
public:
	size_t totalSize;
	uint8_t* startPtr;
	int blockNumber;

	Allocator(size_t size) {
		totalSize = size;
		startPtr = (uint8_t*)malloc(totalSize);
		*(startPtr + offsetBlockAvailablity) = true;
		*(startPtr + headerSize) = totalSize - headerSize;
		blockNumber = 1;
	}

	size_t calculate_size(size_t size) {
		size_t needSize = size + headerSize;
		if (needSize % alignment == 0)
			return size;
		else {
			size_t resSize = needSize + (alignment - (needSize % alignment));
			return resSize - headerSize;
		}
	}


	void* mem_alloc(size_t size) {

		uint8_t* currentPtr = startPtr;
		size_t adjustedSize = calculate_size(size);

		for (int i = 0; i < totalSize; i++) {

			bool isAvailable = *(currentPtr + offsetBlockAvailablity);
			size_t blockSize = *(currentPtr + headerSize);


			if (isAvailable && blockSize >= adjustedSize) {

				size_t localOffset = offsetBlockAvailablity;
				*(currentPtr + localOffset) = false;

				void* startResBlockPtr = currentPtr + localOffset;

				localOffset += offsetCurrBlockSize;
				*(currentPtr + localOffset) = adjustedSize;
				localOffset += adjustedSize;

				localOffset += offsetBlockAvailablity;
				*(currentPtr + localOffset) = true;
				localOffset += offsetCurrBlockSize;
				*(currentPtr + localOffset) = blockSize - adjustedSize - headerSize;

				blockNumber++;
				return startResBlockPtr;

			}
			currentPtr += headerSize;
			currentPtr += blockSize;
		}

		return NULL;
	}


	void mem_free(void* addr) {

		uint8_t* currentPtr = startPtr;
		uint8_t* prevPtr = nullptr;

		for (int i = 0; i < blockNumber; i++) {
			bool isAvailable = *(currentPtr + offsetBlockAvailablity);
			size_t dataSize = *(currentPtr + headerSize);


			if ((currentPtr + offsetBlockAvailablity == (uint8_t*)addr) && !isAvailable) {
				*(currentPtr + offsetBlockAvailablity) = true;
				merge(prevPtr);
				return;
			}

			prevPtr = currentPtr;
			currentPtr += headerSize;
			currentPtr += dataSize;
		}
	}




	void merge(uint8_t* prevPtr) {

		uint8_t* currPtr = prevPtr;

		bool prevBlockAvailabity;
		size_t prevBlockDataSize;

		if (prevPtr == nullptr) {
			prevBlockAvailabity = false;
			prevBlockDataSize = 0;
			currPtr = startPtr;
		}
		else
		{
			prevBlockAvailabity = *(currPtr + offsetBlockAvailablity);
			prevBlockDataSize = *(currPtr + headerSize);

			currPtr += (headerSize + prevBlockDataSize);
		}

		bool currBlockAvailabity = *(currPtr + offsetBlockAvailablity);
		size_t currBlockDataSize = *(currPtr + headerSize);

		uint8_t* nextPtr = currPtr + headerSize + currBlockDataSize;

		bool nextBlockAvailabity = *(nextPtr + offsetBlockAvailablity);
		size_t nextBlockDataSize = *(nextPtr + headerSize);


		if (!prevBlockAvailabity && !nextBlockAvailabity) {
			return;
		}
		else if (!prevBlockAvailabity) {
			*(currPtr + offsetBlockAvailablity) = true;
			*(currPtr + headerSize) = currBlockDataSize + nextBlockDataSize + headerSize;
			size_t size = *(currPtr + headerSize);
			blockNumber--;
		}
		else if (!nextBlockAvailabity) {
			*(prevPtr + offsetBlockAvailablity) = true;
			*(prevPtr + headerSize) = prevBlockDataSize + headerSize + currBlockDataSize;
			blockNumber--;

		}
		else {
			*(prevPtr + offsetBlockAvailablity) = true;
			*(prevPtr + headerSize) = prevBlockDataSize + (2 * headerSize) + currBlockDataSize + nextBlockDataSize;
			blockNumber -= 2;
		}


	}

	void* mem_realloc(void* addr, size_t size) {
		uint8_t* currentPtr = startPtr;
		uint8_t* prevPtr = nullptr;

		for (int i = 0; i < blockNumber; i++) {
			bool isAvailable = *(currentPtr + offsetBlockAvailablity);
			size_t dataSize = *(currentPtr + headerSize);


			if ((currentPtr + offsetBlockAvailablity == (uint8_t*)addr) && dataSize < calculate_size(size)) {

				void* resAddress = mem_alloc(size);
				if (resAddress == NULL)
					return NULL;
				else {
					mem_free(addr);
					return resAddress;
				}
			}
			else if ((currentPtr + offsetBlockAvailablity == (uint8_t*)addr) && dataSize >= calculate_size(size)) {
				size_t adjustedSize = calculate_size(size);

				size_t localOffset = offsetBlockAvailablity;
				*(currentPtr + localOffset) = false;

				void* startResBlockPtr = currentPtr + localOffset;
				localOffset += offsetCurrBlockSize;

				*(currentPtr + localOffset) = adjustedSize;


				if (dataSize - adjustedSize - headerSize <= headerSize) {
					localOffset += dataSize;
					merge(prevPtr);
				}

				else {
					localOffset += adjustedSize;
					localOffset += offsetBlockAvailablity;
					*(currentPtr + localOffset) = true;
					localOffset += offsetCurrBlockSize;
					*(currentPtr + localOffset) = dataSize - adjustedSize - headerSize;
					blockNumber++;
					merge(currentPtr);
				}

				return startResBlockPtr;
			}

			prevPtr = currentPtr;
			currentPtr += headerSize;
			currentPtr += dataSize;
		}
		return NULL;
	}


	void mem_dump() {

		uint8_t* currentPtr = startPtr;
		size_t localOffset = 0;
		for (int i = 0; i < blockNumber; i++) {

			bool isAvailable = *(currentPtr + offsetBlockAvailablity);
			size_t dataSize = *(currentPtr + headerSize);

			cout << "Block " << i;
			if (isAvailable)
				cout << "\tAvailable";
			else
				cout << "\tNot available";
			cout << "\tData size " << dataSize;
			cout << "\tGeneral block size " << dataSize + headerSize;
			cout << "\tBlock address " << (void*)(currentPtr + offsetBlockAvailablity);
			cout << endl;

			currentPtr += headerSize;
			currentPtr += dataSize;
		}
	}
};

void main()
{

	Allocator allocator(128);
	allocator.mem_dump();

	cout << "Start ptr: " << (void*)allocator.startPtr << endl;

	void* addr1 = allocator.mem_alloc(20);
	
	cout << endl;
	allocator.mem_dump();

	cout << endl;
	void* addr2 = allocator.mem_alloc(15);
	
	cout << endl;
	allocator.mem_dump();


	cout << endl;
	addr1 = allocator.mem_alloc(40);
	
	cout << endl;
	allocator.mem_dump();

	cout << endl;
	addr1 = allocator.mem_realloc(addr1, 30);
	
	cout << endl;
	allocator.mem_dump();


	cout << endl;
	allocator.mem_free(addr2);
	cout << endl;
	allocator.mem_dump();


	cout << endl;
	allocator.mem_free(addr1);
	cout << endl;
	allocator.mem_dump();


	cout << endl;
	addr1 = allocator.mem_alloc(20);
	
	cout << endl;
	allocator.mem_dump();
}