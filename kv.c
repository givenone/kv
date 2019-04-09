#include "kv.h"


int main(int argc, char** argvs)
{
    /* first setting (load table, .... , etc) when started.
    *   need to save table before terminated
    *   repeatedly wait for query
    *   argv[0] => file path name
    */
   if(disk = fopen(argvs[0],"r+") < 0)
   {

   }

   char cmdline[MAXLINE];
   while(1)
   {
       	if ((fgets(cmdline, MAXLINE, stdin) == NULL) && ferror(stdin))
	        app_error("fgets error");
	    if (feof(stdin)) { /* End of file (ctrl-d) */
	        fflush(stdout);
            // TODO : save TABLE!!!
            fclose(argvs[0]);
	        exit(0);
        }
        char* arguments[MAX_ARGUMENTS];
        parseApi(cmdline, arguments);
        executeApi(arguments);
   }

   //TODO : Api 마다 실행
}

void parseApi(char *cmdline, char**arguments)
{
    //TODO : parse the api request
    static char array[MAXLINE];
    char *buf = array;

    strcpy(buf, cmdline);

    buf[strlen(buf)-1] = ' '; // \n을 ' '으로 변경
    while(*buf && (*buf == ' '))
    {
        buf++; // leading space
    }

    int argc = 0;    
    char *delim = strchr(buf, ' ');
    while(delim)
    {
        arguments[argc++] = buf;
        *delim = '\0';
        buf = delim + 1;
        while (*buf && (*buf == ' ')) /* ignore spaces */
	    {
            buf++;
        }   

	    delim = strchr(buf, ' ');
	
    }
    arguments[argc] = NULL;

}

void executeApi(char **arguments)
{
    /*TODO : execute following API
    * return < 0 if an error occured
    * 1. GET KEY : 1 = success, 0 = failure 
    * 2. INSERT KEY VALUE : 1 = success, 0 = failure
    * 3. DELETE KEY : 1 = success, 0 = failure
    */
    REQUEST request;

    if(!strcmp(arguments[0], "GET"))
    {
        strcpy(request.key, arguments[1]);
        GET(&request);
    }
    else if(!strcmp(arguments[0], "INSERT"))
    {
        strcpy(request.key, arguments[1]);
        strcpy(request.value, arguments[2]);
        INSERT(&request);
    }
    else if(!strcmp(arguments[0], "DELETE"))
    {
        strcpy(request.key, arguments[1]);
        DELETE(&request);
    }
    else
    {// RETURN
        printf("No Such API (%s)\n", arguments[0]);
    }


}


