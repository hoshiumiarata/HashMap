#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

struct ListNode
{
    char* key;
    void* value;
    struct ListNode* next;
};

struct HashMap
{
    struct ListNode** buffer;
    size_t size;
};

struct HashMap* HashMapInit(size_t N);
void HashMapResize(struct HashMap* hashmap, size_t N);
void HashMapInsert(struct HashMap* hashmap, const char* key, void* value);
void HashMapRemove(struct HashMap* hashmap, const char* key);
void* HashMapFind(struct HashMap* hashmap, const char* key);
bool HashMapContains(struct HashMap* hashmap, const char* key);
size_t HashMapSize(struct HashMap* hashmap);
void HashMapFree(struct HashMap* hashmap);