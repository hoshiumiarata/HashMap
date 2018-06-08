#include "hashmap.h"

static uint32_t StringHash(const char* str)
{
    const uint32_t FNV_prime = 16777619;
    const uint32_t FNV_offset_basis = 0x811c9dc5;
    uint32_t hash = FNV_offset_basis;

    while (*str)
    {
        hash ^= (uint32_t)*str++;
        hash *= FNV_prime;
    }

    return hash;
};

static struct ListNode* ListNodeCreate(const char* key, void* value, struct ListNode* next)
{
    struct ListNode* node = malloc(sizeof(struct ListNode));
    node->key = malloc(sizeof(char) * strlen(key));
    strcpy(node->key, key);
    node->value = value;
    node->next = next;

    return node;
}

static void ListNodeFree(struct ListNode* node)
{
    free(node->key);
    free(node);
}

struct HashMap* HashMapInit(size_t N)
{
    struct HashMap* hashmap = malloc(sizeof(struct HashMap));
    
    hashmap->size = N;
    hashmap->buffer = calloc(hashmap->size, sizeof(struct ListNode*));

    return hashmap;
}

void HashMapResize(struct HashMap* hashmap, size_t N)
{
    size_t old_size = hashmap->size;
    struct ListNode** old_buffer = hashmap->buffer;

    hashmap->size = N;
    hashmap->buffer = calloc(hashmap->size, sizeof(struct ListNode*));

    size_t i;
    for (i = 0; i < old_size; i++)
    {
        struct ListNode* node = old_buffer[i];
        while (node)
        {
            struct ListNode* next = node->next;
            HashMapInsert(hashmap, node->key, node->value);
            ListNodeFree(node);
            node = next;
        }
    }
    free(old_buffer);
}

void HashMapInsert(struct HashMap* hashmap, const char* key, void* value)
{
    uint32_t hash = StringHash(key) % hashmap->size;
    struct ListNode* node = hashmap->buffer[hash];
    if (node)
    {
        while (node)
        {
            if (strcmp(key, node->key) == 0)
            {
                node->value = value;
                return;
            }
            node = node->next;
        }
        hashmap->buffer[hash] = ListNodeCreate(key, value, hashmap->buffer[hash]);
    }
    else
    {
        hashmap->buffer[hash] = ListNodeCreate(key, value, NULL);
    }
}


void HashMapRemove(struct HashMap* hashmap, const char* key)
{
    uint32_t hash = StringHash(key) % hashmap->size;
    struct ListNode* node = hashmap->buffer[hash];
    struct ListNode* prev = NULL;
    while (node)
    {
        if (strcmp(key, node->key) == 0)
        {
            if (prev)
                prev->next = node->next;
            else
                hashmap->buffer[hash] = node->next;

            ListNodeFree(node);
            return;
        }
        prev = node;
        node = node->next;
    }
}

void* HashMapFind(struct HashMap* hashmap, const char* key)
{
    uint32_t hash = StringHash(key) % hashmap->size;
    struct ListNode* node = hashmap->buffer[hash];
    while (node)
    {
        if (strcmp(key, node->key) == 0)
            return node->value;
        node = node->next;
    }

    return NULL;
}

bool HashMapContains(struct HashMap* hashmap, const char* key)
{
    uint32_t hash = StringHash(key) % hashmap->size;
    struct ListNode* node = hashmap->buffer[hash];
    while (node)
    {
        if (strcmp(key, node->key) == 0)
            return true;
        node = node->next;
    }

    return false;
}

size_t HashMapSize(struct HashMap* hashmap)
{
    size_t i, size = 0;
    for (i = 0; i < hashmap->size; i++)
    {
        struct ListNode* node = hashmap->buffer[i];
        for (; node; size++)
        {
            node = node->next;
        }
    }
    return size;
}

void HashMapFree(struct HashMap* hashmap)
{
    size_t i;
    for (i = 0; i < hashmap->size; i++)
    {
        struct ListNode* node = hashmap->buffer[i];
        while (node)
        {
            struct ListNode* next = node->next;
            ListNodeFree(node);
            node = next;
        }
    }
    free(hashmap->buffer);
    free(hashmap);
}