#include "kv.h"

extern INDEX indexTable;

int GET(REQUEST *request)
{
    static Buffer[MAX_VALUE];
    int length = get(request);
    if(length >= 0)
    { // Stored
        fseek(disk, request->address, SEEK_SET);
        fread(Buffer, 1, length, disk);
        Buffer[length+1] = '\n';
        printf("key : %s, value : %s \n",request->key, Buffer);
    }
    else
    {
        // Not Stored
        printf("Not Stored for key : %s \n",request->key);
    }
    
}

void INSERT(REQUEST *request)
{

    calOff(&metadata, request);
    fseek(disk, request->address, SEEK_SET);
    if(fwrite(request->value, 1, sizeof(request->value), disk)<0)
    {
        printf("Insertion Failed for key : %s, value : %s\n",request->key, request->value);
    }
    else
    {
        insert(request);  
    }
}

void DELETE(REQUEST *request)
{
    /* I don't like this
    * No Compaction
    */
   if(!delete(request))
   {// Delete failure
        printf("Not Stored for key : %s \n",request->key);
   }
   else
   {
        printf("Deleted key : %s \n",request->key);

   }

}

void calOff(META *meta, REQUEST *request){
    request->address = meta->curOffset;
    meta->curOffset += sizeof(request->value);
}