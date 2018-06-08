#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>

#include "hashmap.h"

static void hashmap_size_test(void** state)
{
    struct HashMap* hashmap = HashMapInit(20);
    HashMapInsert(hashmap, "qwe", NULL);
    HashMapInsert(hashmap, "qw2e", NULL);
    HashMapInsert(hashmap, "q2we", NULL);
    HashMapInsert(hashmap, "3qwe", NULL);

    HashMapInsert(hashmap, "5qwe", NULL);
    HashMapInsert(hashmap, "5qwe", NULL);

    assert_int_equal(HashMapSize(hashmap), 5);
    HashMapFree(hashmap);
}

static void hashmap_insert_find_test(void** state)
{
    struct HashMap* hashmap = HashMapInit(20);
    HashMapInsert(hashmap, "qwe", "qwerty");
    assert_string_equal(HashMapFind(hashmap, "qwe"), "qwerty");
    HashMapInsert(hashmap, "qwe", "asdfgh");
    assert_string_equal(HashMapFind(hashmap, "qwe"), "asdfgh");

    HashMapFree(hashmap);
}

static void hashmap_remove_contains_test(void** state)
{
    struct HashMap* hashmap = HashMapInit(20);
    HashMapInsert(hashmap, "qwe", "qwerty");
    assert_true(HashMapContains(hashmap, "qwe"));
    HashMapRemove(hashmap, "qwe");
    assert_false(HashMapContains(hashmap, "qwe"));

    HashMapFree(hashmap);
}

static void hashmap_resize_test(void** state)
{
    struct HashMap* hashmap = HashMapInit(20);
    HashMapInsert(hashmap, "qwe", NULL);
    HashMapInsert(hashmap, "qw2e", NULL);
    HashMapInsert(hashmap, "q2we", NULL);
    HashMapInsert(hashmap, "3qwe", NULL);

    HashMapInsert(hashmap, "5qwe", NULL);
    HashMapInsert(hashmap, "5qwe", NULL);

    HashMapResize(hashmap, 100);
    assert_int_equal(HashMapSize(hashmap), 5);
    HashMapResize(hashmap, 1);
    assert_int_equal(HashMapSize(hashmap), 5);
    HashMapResize(hashmap, 5);
    assert_int_equal(HashMapSize(hashmap), 5);

    HashMapFree(hashmap);
}

int main(void)
{
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(hashmap_size_test),
        cmocka_unit_test(hashmap_insert_find_test),
        cmocka_unit_test(hashmap_remove_contains_test),
        cmocka_unit_test(hashmap_resize_test)
	};
    
	return cmocka_run_group_tests(tests, NULL, NULL);
}