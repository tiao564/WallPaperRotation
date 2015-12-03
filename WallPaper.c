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

void changeWallpaper(int count, int selected_mode);

/////////////////////////////////////
/*File names and gnu command to run*/
/////////////////////////////////////
char * files[800];                           //List of files in folder that can be opened
char file_name[100];                         //File name that will be opened
char base_and_path[100];



int main(int argc, char* argv[])
{
printf("Start\n");

///////////////////////////////////////////////////////
/*Get mode for program, rotating, random, controlled?*/
///////////////////////////////////////////////////////
if (argc<2)
{
  printf("Not enough arguments, exiting.\n");
  exit(1);
}
int mode = atoi(argv[1]);

//////////////////////////////
/*Structures for directories*/
//////////////////////////////
struct dirent *pDirent;                     //Struct runs through directory
DIR * pDir;                                 //Directory to open

///////////////////////////////
/*Strings for Directory paths*/
///////////////////////////////
char * homeDir = "/home/tiao/";             //Base to get to different files
char * workingDir = "DarkBackgrounds/";     //Example file can change when finnished
char finalDir[64];                          //Final Directory location to open

/////////////////////////////////////
/*File names and gnu command to run*/
/////////////////////////////////////
//char * files[800];                           //List of files in folder that can be opened
//char file_name[100];                         //File name that will be opened
char * base = "gsettings set org.gnome.desktop.background picture-uri file://";
//char base_and_path[100];

/////////////////////////////////////
/*Itterators and random number seed*/
/////////////////////////////////////
srand(time(NULL));                          //Seed for rand function
int counter = 0;                            //Counter countes number of files in directory
int i = 0;                                  //Iterrator for number generator
int rand_num;
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
  
  changeWallpaper(counter, mode);

  closedir (pDir);
  return 0;
}

void changeWallpaper(int count, int selected_mode)
{
  int i= 0;
  while(i<count)
  {
    printf("%s\n", base_and_path);
    strcat(file_name, base_and_path);
    strcat(file_name,"'");                //Quotes allow for files with spaces in their names
    if (selected_mode==1)
    {
      strcat(file_name, files[i]);
    }
    if(selected_mode==2)
    {
      int rand_num = rand()%(count+1); 
      strcat(file_name,files[rand_num]);
    }
    strcat(file_name,"'");
    printf("%s\n", file_name);
    system(file_name);
    file_name[0] = '\0';
    sleep(1);
    i++;
  } 
}
