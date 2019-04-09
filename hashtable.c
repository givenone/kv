#include "kv.h"


char* output;

void createTable()
{
    // INIT
}

int insert(REQUEST *request)
{
    /* insert key value pair in some location at TABLE 
        and 
    *  return 1 */
   hash(request->key, output);
   unsigned int index = hashIndex(output);
   while(1) // not empty
   {
       if(indexTable.Table[index].first == NULL 
       || !strcmp(indexTable.Table[index].first, DELETED) 
       || !strcmp(indexTable.Table[index].first, request->key))
       {
           break;
       }
       index = (index + 1) % TABLE_SIZE; // linear probing
   }
   // TODO : SAVE IN DISK(request.offset) -> api에서 처리

   setTable(index, request);
   return 1;

}

int get(REQUEST *request)
{
    /* get address && length (request) from key 
    *  return < 0 if not in the storage , return length otherwise.
    */
   char *temp;
   hash(request->key, temp);
   unsigned int index = hashIndex(temp);
   while(indexTable.Table[index].first != NULL)
   {
       if(!strcmp(indexTable.Table[index].first, request->key))
       {
           request->address = indexTable.Table[index].second;
           return indexTable.Table[index].length;
       }
       else
       {
           index = (index + 1) % TABLE_SIZE;
       }
       
   }
   return -1;
}

int delete(REQUEST *request)
{
    /* delete*/
    char *temp;
    hash(request->key, temp);
    unsigned int index = hashIndex(temp);
    while(indexTable.Table[index].first != NULL)
    {
        if(!strcmp(indexTable.Table[index].first, request->key))
        {// check as deleted
            indexTable.Table[index].first = DELETED;
            return 1;
        }
        else
        {
            index = (index+1) % TABLE_SIZE;
        }
    }
    return 0;
}


void setTable(unsigned int location, REQUEST *request)
{
    char *key = (char*)malloc(sizeof(request->key)); // NEED TO FREE WHEN DELETE
    strcpy(request->key, key);
    indexTable.Table[location].second = request->address;
    indexTable.Table[location].first = key;
    indexTable.Table[location].length = sizeof(request->value);
    /* set location of the table to the following address(offset)*/
}

int getAddress(unsigned int location)
{
    if(indexTable.Table[location].first == NULL || !strcmp(indexTable.Table[location].first, DELETED))
    {
        return 0;
    }
    else
    {
        return indexTable.Table[location].second;
    }
    /* get Address(offset) of the location in hashtable
    *   return 0 if empty, else return offset */
}

void hash(unsigned char *key, unsigned char *output)
{
    /* return hash value according to the KEY -> SH256 */
    size_t len = sizeof(key);
    SHA1(key, len, output);
}

unsigned int hashIndex(unsigned char* output)
{
    unsigned int i = 1;
    unsigned int arraykey = 1;
    unsigned int j = 0;

    while(i < TABLE_SIZE && j < 20)
    {
        arraykey *= output[j++];
        i *= 256;
    }
    return arraykey % TABLE_SIZE;
}