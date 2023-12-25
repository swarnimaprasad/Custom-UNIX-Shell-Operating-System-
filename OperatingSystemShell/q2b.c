#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
//#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char **argv) {
    char currentdirectory[100];
    if (argc != 3) {
        printf("wrong number of arguments");
    }
    else{
        if(strcmp(argv[1],"-v")==0){
            char *dir=argv[2];
            if(mkdir(dir,0777)==-1){
                printf("directory already exists \n");
            }
            else{
                printf("directory successfully created\n");
                
            }
            if(chdir(dir)==0){
                printf("directory changed successfully\n");
            }
            else{
               printf("error directory could not be changed\n");
            }
        }
        else if (strcmp(argv[1],"-r")==0){
            char *dir=argv[2];
            if(mkdir(dir,0777)==-1){
                printf("directory already exists\n");
                int ret = rmdir(dir);
                if (ret == 0){
                    printf("old directory removed successfully\n");
                }
            }
            if(mkdir(dir,0777)!=-1){
                printf("new directory successfully created\n");
            }
            if(chdir(dir)==0){
                printf("directory changed successfully\n");
            }
            else{
                printf("error directory could not be changed\n");
            }
            
           
        }
        
        else{
            printf("wrong argumnet given\n");
        }
    
        printf("current directory %s\n",getcwd(currentdirectory,100));

    }
}