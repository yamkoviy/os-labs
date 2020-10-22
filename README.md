# Memory Allocator

## Lab1 - C++ implementation of memory allocator

## Header
Під **Header** виділяється 5 байтів:
1. 1 байт використовується для перевірки вільності блоку (offsetBlockAvailability)
2. 5 байт містить інформацію про розмір блоку, не враховуючи розмір хідера

## Main Functions
1. mem_alloc - функція виділяє блок пам'яті заданого розміру в size байт. Якщо 
блок пам'яті був виділений успішно, функція повертає адресу початку цього блоку, в
протилежному випадку повертає NULL.
2. mem_realloc - функція змінює розмір блоку пам'яті с адресою addr до size байт. Якщо 
вдалось змінити розмір блоку пам'яті, то функція повертає адресу нового блоку пам'яті, інакше функція
повертає NULL і не руйнує старий блок пам'яті. Якщо addr рівний NULL, то виклик
функції аналогічний виклику mem_alloc(size).
3. mem_free - функція звільняє виділений блок пам'яті.

## Examples

Allocator allocator(128);
allocator.mem_dump();
____
void* addr1 = allocator.mem_alloc(20);
allocator.mem_dump();
____
void* addr2 = allocator.mem_alloc(15);
allocator.mem_dump();
____
addr1 = allocator.mem_alloc(40);
allocator.mem_dump();
____
addr1 = allocator.mem_realloc(addr1, 30);
allocator.mem_dump();
____
allocator.mem_free(addr2);
allocator.mem_dump();
____
allocator.mem_free(addr1);
allocator.mem_dump();
____
addr1 = allocator.mem_alloc(20);
allocator.mem_dump();
____
