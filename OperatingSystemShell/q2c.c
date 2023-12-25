#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>

int main(int argc, char **argv) {
    if (argc <2) {
        printf("wrong number of arguments\n");
    }
    else{
        char *file = argv[2];
        if (argc==4){
            file = argv[3];
        }
        struct stat status;
        if (stat(file, &status) == 0) {

                time_t modifiedTime = status.st_mtime;
                struct tm *timeInfo = localtime(&modifiedTime);
                int month=timeInfo->tm_mon;
                int day=timeInfo->tm_mday;
                int yr=timeInfo->tm_year+1900;
                int hr=timeInfo->tm_hour;
                int min =timeInfo->tm_min;
                int sec= timeInfo->tm_sec;
                int weekday = timeInfo->tm_wday;

                const char *dayNames[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
                const char *monthNames[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
                char* option=argv[1];
                if(strcmp(option,"-d")==0|| argc==2){
                    if(argc!=4){
                        printf("Filename: %s has been last modified on\n", file);
                        printf("%s %s %d %d:%d:%d %s %d\n", dayNames[weekday], monthNames[month],day, hr, min, sec,"IST",yr);
                    }
                }

                else if(strcmp(option,"-R")==0 ){

                    printf("Filename: %s has been last modified on\n", file);
                    printf("%s, %d %s %d %d:%d:%d %s\n", dayNames[weekday], day, monthNames[month], yr, hr, min, sec,"+0530");

                }
                if (argc==4){
                    if(strcmp(argv[2],"yesterday")==0){
                        printf("Filename: %s has been last modified on\n", file);
                        printf("%s %s %d %d:%d:%d %s %d\n", dayNames[weekday-1], monthNames[month],day-1, hr, min, sec,"IST",yr);
                    }
                    else if (strcmp(argv[2],"tomorrow")==0){
                        printf("Filename: %s has been last modified on\n", file);
                        printf("%s %s %d %d:%d:%d %s %d\n", dayNames[7%(weekday+1)], monthNames[month],day+1, hr, min, sec,"IST",yr);

                    }
                }
        }
        else{
            printf("status could not be retrieved\n");
        }    
    }
}