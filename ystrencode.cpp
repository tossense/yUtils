#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;

int main(int argc, char *argv[])
{
    string line;
    while(getline(cin, line))
    {
        for(size_t i=0; i<line.size(); ++i)
        {
            if(line[i]>='a' && line[i]<='z')
                printf("%c", line[i]);
            else if(line[i]>='A' && line[i]<='Z')
                printf("%c", line[i]);
            else if(line[i]>='0' && line[i]<='9')
                printf("%c", line[i]);
            else
                printf("%%%x", static_cast<unsigned char>(line[i]));
        }
        printf("\n");
    }
    return 0;
}

