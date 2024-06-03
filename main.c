#include "HashTable.c"


int main()
{
	struct HashTable *h = HashTable_new();
	// HashTable_printAll(h);
	HashTable_add(h, "vovager2003", "airbus");
	HashTable_add(h, "vovager2003", "sajflfjsdfd");
	HashTable_add(h, "vovager2003", "aodjkfjdks");
	HashTable_add(h, "123", "ssf");
	HashTable_add(h, "123", "sso");
	HashTable_add(h, "123", "ssd");
	HashTable_add(h, "d", "fhfhfh");
	HashTable_printAll(h);
	HashTable_del(&h);
	puts("----\n");
	HashTable_printAll(h);


	// struct HashNode *n;
	// n = HashTable_find(h, "vovager2003");
	// HashNode_printAll(n);
	// n = HashTable_find(h, "123");
	// HashNode_printAll(n);
	// n = HashTable_find(h, "d");
	// HashNode_printAll(n);
	return 0;
}
