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
char * base = "gsettings set org.gnome.desktop.background picture-uri file://";

/////////////////////////////////////
/*Itterators and random number seed*/
/////////////////////////////////////
srand(time(NULL));                          //Seed for rand function
int counter = 0;                            //Counter countes number of files in directory
int i = 0;                                  //Iterrator for number generator
finalDir[0] = '\0';                         //Need this to prevent garbage values
file_name[0] = '\0';
base_and_path[0] = '\0';

////////////////////////////////////
/*Cat strings to get full Dir path*/
////////////////////////////////////
strcat(finalDir, homeDir);                  
strcat(finalDir, workingDir);

pDir = opendir(finalDir);                   //Open Dir

//////////////////////////////////////////////////////
/*Check to see if Dir is good, if so open it         /
// and loop through grabbing all files not .. and . */
//////////////////////////////////////////////////////
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

closedir (pDir);                          //Return dir memeory

//////////////////////////////////////////////////////////////
/*Build the command to change wallpaper, only need file name*/
//////////////////////////////////////////////////////////////
  strcat(base_and_path, base);
  strcat(base_and_path, finalDir);
  
///////////////////////////////////////////////////////
/*Change wall paper based on mode, 1 linear, 2 random*/
///////////////////////////////////////////////////////
  changeWallpaper(counter, mode);

  return 0;
}

///////////////////////////////////////////////////////////
/*changeWallpaper(int count, int selected_mode)          */
/*                                                       */
/*Function selects a wallpaper, finishes building a      */
/* command and then runs the command in the system       */
/*Params:                                                */
/* count: number of files in directory                   */
/* Selected_mode: picks how files are selected           */
///////////////////////////////////////////////////////////
void changeWallpaper(int count, int selected_mode)
{
  int i= 0;
  ///////////////////////////////////////////////////////////////
  /*While you havent finished looping through files, keep going*/
  ///////////////////////////////////////////////////////////////
  while(1)
  {
    ///////////////////////////////////////////////////////////////
    /*Finish making the command by adding file name to a temp val*/
    ///////////////////////////////////////////////////////////////
    printf("%s\n", base_and_path);
    strcat(file_name, base_and_path);
    strcat(file_name,"'");                //Quotes allow for files with spaces in their names
    /////////////////////////////////////////
    /*Like stated, 1 is linear, 2 is random*/
    /////////////////////////////////////////
    if (selected_mode==1)
    {
      strcat(file_name, files[(i%count)]);
    }
    else if(selected_mode==2)
    {
      int rand_num = rand()%(count+1); 
      strcat(file_name,files[rand_num]);
    }
    strcat(file_name,"'");
    printf("%s\n", file_name);
    system(file_name);                    //Run in terminal
    file_name[0] = '\0';                  //Reset temp comman
    sleep(1);
    i++;
  } 
}
