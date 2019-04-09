#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>

#define MAX_KEY 128
#define MAX_VALUE 256
#define TABLE_SIZE 1<<16
#define MAX_ARGUMENTS 5
#define MAXLINE 100
const char* DELETED  = ""; // hashtable deleted key

#define BLOCK_SIZE 4096
#define DISK_SIZE 1<<32
#define BLOCK_CNT DISK_SIZE / BLOCK_SIZE

typedef struct meta{
    int curBlock;
    int curOffset;
}META;

typedef struct tableMember{
    unsigned char* first; // key
    int second; // address
    int length; // length of the value
}TM;

typedef struct hash{
    TM Table[TABLE_SIZE]; // KEY, ADDRESS
    int cnt;
}INDEX;

typedef struct request{
    unsigned char key[MAX_KEY];
    unsigned char value[MAX_VALUE];
    int address;
}REQUEST;

static FILE *disk;
static META metadata;
static INDEX indexTable;



// hashtable.c
void createTable();
int get(REQUEST *request);
int insert(REQUEST *request);
int get(REQUEST *request);
void setTable(unsigned int location, REQUEST *request);
int getAddress(unsigned int location);
void hash(unsigned char *key, unsigned char *output);
unsigned int hashIndex(unsigned char* output);
