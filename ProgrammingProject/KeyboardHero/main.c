#include <stdbool.h>
#include <SDL2/SDL.h>
#include <time.h>
#include <sys/time.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include "gameFunctions.h"
#include "graphicsFunctions.h"

#include "gameData.h"
#include <string.h>


Mix_Chunk *music = NULL;
Mix_Chunk *backingTrack = NULL; //


int main( void )
{
        // creates a structure and a pointer
        // which contains the game info
        struct songInfo mainSongInfo;
        struct songInfo *songInfoPointer;
        songInfoPointer = &mainSongInfo;
        int delay = 16;
        int gameState = 0; // 0 Is for the loading screen
        TTF_Init();
        TTF_Font * font = TTF_OpenFont("fonts/thin.ttf", 25);
        SDL_Color fontColour = { 200, 0, 0 };

        init();   // setup the game data
        render(gameState,songInfoPointer,0); // render initial state
        loadImages();
        // Timing variables
        long long gameStartTime = current_timestamp();
        long long currentTime = current_timestamp() - gameStartTime;
        long long previousTime = 0;
        int chosenSong = 1;

        // this is the main while loop
        // pick song --> play song --> get stats --> repeat

        while(true){
          gameStartTime = current_timestamp();
          readSongFromFile("songs/test/notes.chart",songInfoPointer,0);
          gameState = 1;
          chosenSong = 1;
          int counter = 0;
          while(chosenSong < 11){
            counter ++;
            if(counter > 10){
              input(songInfoPointer,0);
            }
            else{
              greenButton = false;
            }

            render(gameState,songInfoPointer,currentTime);
            SDL_Delay(delay);
            chosenSong = songSelection(chosenSong);
          }
          chosenSong -= 10;

          char songName[20];
              // THe lowest effort way of doing this. If it was in Python
              // I would have used a method with a lower line count. But in C
              // It just isn't worth the hour it would have took me to work out how
              // to do this.
              switch(chosenSong)
              {
                case 1: strcpy(songName, "Infected"); break;
                case 2: strcpy(songName,"SharpDressedMan"); break;
                case 3: strcpy(songName,"Stellar"); break;
                case 4: strcpy(songName,"SymphonyOfDestruction"); break;
                case 5: strcpy(songName,"Cochise"); break;
                case 6: strcpy(songName,"TakeItOff"); break;
                case 7: strcpy(songName,"MoreThanAFeeling"); break;
                case 8: strcpy(songName,"KillerQueen"); break;
                case 9: strcpy(songName,"ZiggyStardust"); break;
                case 10: strcpy(songName,"FatLip"); break;
              }

          //strcpy(songName,"test");
          int songID = chosenSong;
          char chartDirectory[100];
          memset(&chartDirectory[0], 0, sizeof(chartDirectory));
          strcat(chartDirectory,"songs/");
          strcat(chartDirectory,songName);
          strcat(chartDirectory,"/notes.chart");

          char guitarDirectory[100];
          memset(&guitarDirectory[0], 0, sizeof(guitarDirectory));
          strcat(guitarDirectory,"songs/");
          strcat(guitarDirectory,songName);
          strcat(guitarDirectory,"/guitar.ogg");

          char backingTrackDirectory[100];
          memset(&backingTrackDirectory[0], 0, sizeof(backingTrackDirectory));
          strcat(backingTrackDirectory,"songs/");
          strcat(backingTrackDirectory,songName);
          strcat(backingTrackDirectory,"/song.ogg");

          char cdDirectory[100];
          memset(&cdDirectory[0], 0, sizeof(cdDirectory));
          strcat(cdDirectory,"songs/");
          strcat(cdDirectory,songName);
          strcat(cdDirectory,"/label.png");

          char hiScoreDirectory[100];
          memset(&hiScoreDirectory[0], 0, sizeof(hiScoreDirectory));
          strcat(hiScoreDirectory,"songs/");
          strcat(hiScoreDirectory,songName);
          strcat(hiScoreDirectory,"/hiScore.txt");


          readSongFromFile(chartDirectory,songInfoPointer,songID); // this populates the mainSong info class


          // song SDL_CreateTextureFromSurface

          if( Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
          {
              return false;
          }
          music = Mix_LoadWAV(guitarDirectory);
          backingTrack = Mix_LoadWAV(backingTrackDirectory);
          Mix_PlayChannel(-1, music, 0 );
          Mix_PlayChannel(-1,backingTrack,0);
          gameState = 2; // This is for playing the song

          gameStartTime = current_timestamp(); // once songs have been loaded
          currentTime = current_timestamp() - gameStartTime;

          int endingFrames = 0; // so taht the song does not end instantly
          while( ((songInfoPointer->currentNote < songInfoPointer->totalSongNotes)||endingFrames<100) && songInfoPointer->rockOMeter > 0) {      // game loop
              if(songInfoPointer->currentNote > songInfoPointer->totalSongNotes){
                endingFrames++; // counts how many frames after the song ends.
              }
              else{
                previousTime = currentTime; // so that previous time is one step behind the last one.
                currentTime = current_timestamp() - gameStartTime;
                input(songInfoPointer,currentTime);           // keyboard input
                render(gameState,songInfoPointer,currentTime);
                drawAllNotes(songInfoPointer,currentTime,songID); // Actually doing the nice graphics, instead of just command line rubbish
                drawUI(songInfoPointer,font,fontColour,1,songName,0);
                drawFlames(songInfoPointer);
              }


              if(delay- (currentTime-previousTime) > 0)
              {
                SDL_Delay( delay - (currentTime-previousTime));
              }
          }

          int pressedContinue = -100;
          while(pressedContinue < 10000){

            if(songInfoPointer->rockOMeter < 1){
              render(4,songInfoPointer,currentTime); // shows this when they have failed the song;
              pressedContinue+= 70; // after 100 frames they will go back to song select
              SDL_Delay(delay);
            }
            else{
              input(songInfoPointer,0);
              render(3,songInfoPointer,currentTime);
              SDL_Delay(delay);
              pressedContinue = viewEndCard(cdDirectory,songInfoPointer,font,fontColour,songName,hiScoreDirectory);
              pressedContinue++;
            }

          }



          Mix_HaltChannel(-1);

    }
}
