#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
key: login
val: pass
*/
#define HashNodeBuffSize 256 //макс колво значений
#define HashNodeStringSize 256 //макс длина значения

struct HashNode
{
	unsigned int key;		  // ключ
	char **value;			  // массив значений
	int len;				  // len(value)
	struct HashNode *pointer; // next значение
};
static void HashNode_init(struct HashNode *);
void HashNode_printAll(struct HashNode *);
struct HashNode *HashNode_new(unsigned int);
int HashNode_addValue(struct HashNode *, char *);
static void HashNode_delNode(struct HashNode *);
	
struct HashTable
{
	struct HashNode *head;
};
static void HashTable_init(struct HashTable *);
void HashTable_add(struct HashTable *, char *, char *);
struct HashNode *HashTable_find(struct HashTable *, char *);
void HashTable_print(struct HashTable *, char *);
unsigned int HashTable_hash(char *);
void HashNode_printAll(struct HashNode *);
static void HashTable_delAll(struct HashTable *);
void HashTable_del(struct HashTable **);

static void HashTable_init(struct HashTable *p)
{
	p->head = NULL;
}

struct HashTable *HashTable_new()
{
	struct HashTable *a = (struct HashTable *)malloc(sizeof(struct HashTable));
	HashTable_init(a);
	return a;
}

void HashTable_add(struct HashTable *p, char *key, char *value)
{
	if (!p)
	{
		return;
	}
	struct HashNode **last = &p->head; //указатель на указатель на ноду
	while (*last)
	{
		if (HashTable_hash(key) == (*last)->key)
		{
			HashNode_addValue(*last, value);
			return;
		}
		else
		{
			last = &((*last)->pointer);
		}
	}
	if (*last == NULL)
	{
		*last = HashNode_new(HashTable_hash(key));
		HashNode_addValue(*last, value);
		return;
	}
}

struct HashNode *HashTable_find(struct HashTable *p, char *key)
{
	if (!p)
	{
		return NULL;
	}
	struct HashNode *last = p->head;
	while (last)
	{
		if (HashTable_hash(key) == last->key)
		{
			return last;
		}
		else
		{
			last = last->pointer;
		}
	}
	return NULL;
}

void HashTable_print(struct HashTable *p, char *key)
{
	if (!p)
	{
		return;
	}
	struct HashNode *last = p->head;
	while (last)
	{
		HashNode_printAll(last);
		last = last->pointer;
	}
}

void HashTable_printAll(struct HashTable *p)
{
	if (!p)
	{
		return;
	}
	struct HashNode *last = p->head;
	while (last)
	{
		HashNode_printAll(last);
		last = last->pointer;
		puts("\n");
	}
}

static void HashTable_delAll(struct HashTable *p)
{
	struct HashNode *n;
	while (p->head)
	{
		n = p->head;
		p->head = p->head->pointer;
		HashNode_delNode(n);
		free(n);
	}
	p->head = NULL;
}

void HashTable_del(struct HashTable **p)
{
	if (!(*p))
	{
		return;
	}
	HashTable_delAll(*p);
	free(*p); 
	(*p) = NULL;
}

unsigned HashTable_hash(char *key)
{
	int hash = 0;
	char *p = key;
	while (*p != '\0')
	{
		hash = (hash * 1664525) + (unsigned int)(*p++) + 1013904223;
	}
	return hash;
}

/*
	add
	find
*/

static void HashNode_init(struct HashNode *p) // внутряняя функция
{
	p->key = 0;
	p->len = 0;
	p->value = (char **)malloc(sizeof(char *) * HashNodeBuffSize); // выделение памяти под массив char* = строка
	p->pointer = NULL;
}

void HashNode_printAll(struct HashNode *p)
{
	if (!p)
	{
		return;
	}
	printf("key: %d\n", p->key);
	for (int i = 0; i < p->len; i++)
	{
		printf("\t%s\n", p->value[i]);
	}
	printf("---\n");
}

struct HashNode *HashNode_new(unsigned int key)
{
	struct HashNode *a = (struct HashNode *)malloc(sizeof(struct HashNode));
	HashNode_init(a);
	a->key = key;
	return a;
}

int HashNode_addValue(struct HashNode *p, char *s)
{
	if (!p)
	{
		return -1;
	}
	if (strlen(s) == 0 || strlen(s) > 256) // пидор тест строк
	{
		return -1;
	}
	if (p->len == HashNodeBuffSize) // забитый буфер
	{
		return -1;
	}
	char *newstring = malloc(sizeof(char) * HashNodeStringSize);
	strcpy(newstring, s);
	p->value[p->len++] = newstring;
	return 0;
}

static void HashNode_delNode(struct HashNode *p)
{
	if (!p)
	{
		return;
	}
	for (unsigned int i = 0; i < p->len; i++)
	{
		free(p->value[i]);
	}
	free(p->value);
}
