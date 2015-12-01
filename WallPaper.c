/*Wall paper changer
 *Final product will have two modes, random and in order
 *Made by Dylan Guldy
 *2015
 *                                */
//gsettings set org.gnome.desktop.background picture-uri file:///home/tiao/Irelia_Splash_1.jpg
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char* argv[])
{
printf("Start\n");
//int mode = argv[1];
/*Structures for directories*/
struct dirent *pDirent;                     //Struct runs through directory
DIR * pDir;                                 //Directory to open

/*Strings for Directory paths*/
char * homeDir = "/home/tiao/";             //Base to get to different files
char * workingDir = "DarkBackgrounds/";     //Example file can change when finnished
char finalDir[64];                          //Final Directory location to open

/*File names and gnu command to run*/
char * files[800];                           //List of files in folder that can be opened
char file_name[100];                         //File name that will be opened
char * base = "gsettings set org.gnome.desktop.background picture-uri file://";
char base_and_path[100];

/*Itterators and random number seed*/
srand(time(NULL));                          //Seed for rand function
int counter = 0;                            //Counter countes number of files in directory
int i = 0;                                  //Iterrator for number generator
finalDir[0] = '\0';                         //Need this to prevent garbage values
file_name[0] = '\0';
base_and_path[0] = '\0';

strcat(finalDir, homeDir);                  //Cat strings to get full Dir path
strcat(finalDir, workingDir);

printf("%s\n", finalDir);
pDir = opendir(finalDir);                   //Open Dir

  if(pDir == NULL)
  {
    printf("Directory Could not be opened\n");
    exit(1);
  }
  while((pDirent = readdir(pDir)) != NULL)
  {
      if(strcmp(pDirent->d_name,".") != 0 && strcmp(pDirent->d_name,"..") != 0)
      {
          files[counter] = pDirent->d_name;
          counter++;
      }
  }

  strcat(base_and_path, base);
  strcat(base_and_path, finalDir);
  while(i<counter)
  {
    printf("%s\n", base_and_path);
    strcat(file_name, base_and_path);
    strcat(file_name,"'");
    strcat(file_name, files[i]);
    strcat(file_name,"'");
    printf("%s\n", file_name);
    system(file_name);
    
    //printf("%d",mode);
    file_name[0] = '\0';
    sleep(1);
    i++;
  }
  closedir (pDir);
  return 0;
}
