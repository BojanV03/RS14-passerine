#include <stdio.h>
#include <string.h>
int main()
{
    FILE *f = fopen("Instruments.txt", "r");
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    if(f == NULL)
    {
        printf("invalid txt file");
        return -1;
    }
    int id;
    char printString[5];
    char c;
    while((read = getline(&line, &len, f)) != -1) 
    {
        sscanf(line, "%d", &id);
        line[strlen(line)-1] = 0;
   //     printf("%d ", id);
        
        printf("name = name.fromStdString(\"%s\");\n", line + sprintf(printString, "%d ", id-1));
        printf("instruments.push_back(new Instrument(%d, &name));\n\n", id-1);
    }
}
