#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <SDL2/SDL.h>

#include "gameData.h"
#include "gameFunctions.h"



// stolen code, please don't arrest me
long long current_timestamp() {
    struct timeval te;
    gettimeofday(&te, NULL); // get current time
    long long milliseconds = te.tv_sec*1000LL + te.tv_usec/1000; // calculate milliseconds
    return milliseconds;
}

void hasHitNotes(struct songInfo *songInfoPointer, long long currentTime,
                 bool greenButton,bool redButton, bool yellowButton,
                 bool blueButton, bool orangeButton, bool hasStrummed){

  int lagCompensation = 275;
  int allowance = 100;
  // the time needs to be adjusted so that everything stays in sync.
  float adjustedTime = currentTime * songInfoPointer->videoSpeed;
  // this function takes a lot of inputs and determines weather a player has
  // hit a note. This is quite a complex function, since. A single note
  // can be hit lots of different ways.If it is a red note, a green note
  // can be held down at the same time and it still counts as a hit.
  // also, we need to concider notes which need to be held down, and HOPO
  // notes. But we will get to that bit later
  int currentNoteTime = songInfoPointer->noteTiming[songInfoPointer->currentNote];
  int currentNoteColour = songInfoPointer->noteColour[songInfoPointer->currentNote];
  int nextNoteTime = songInfoPointer->noteTiming[(songInfoPointer->currentNote)+1];
  int nextNoteColour = songInfoPointer->noteColour[(songInfoPointer->currentNote)+1];
  int currentNoteHolding = songInfoPointer->noteDuration[songInfoPointer->currentNote];
  int nextNoteHolding = songInfoPointer->noteDuration[(songInfoPointer->currentNote)+1];

  // This section deals with held notes
  if(songInfoPointer->currentNote < songInfoPointer-> totalSongNotes){

    if(greenButton && songInfoPointer->greenHolding > currentTime){
      songInfoPointer->score += songInfoPointer->multiplier;
      songInfoPointer->flame1 = 0;
    }
    if(redButton && songInfoPointer->redHolding > currentTime){
      songInfoPointer->score += songInfoPointer->multiplier;
      songInfoPointer->flame2 = 0;
    }
    if(yellowButton && songInfoPointer->yellowHolding > currentTime){
      songInfoPointer->score += songInfoPointer->multiplier;
      songInfoPointer->flame3 = 0;
    }
    if(blueButton && songInfoPointer->blueHolding > currentTime){
      songInfoPointer->score += songInfoPointer->multiplier;
      songInfoPointer->flame4 = 0;

    }
    if(orangeButton && songInfoPointer->orangeHolding > currentTime){
      songInfoPointer->score += songInfoPointer->multiplier;
      songInfoPointer->flame5 = 0;
    }

  }


  if(hasStrummed){

    // checks weather the timing is right
    if(adjustedTime-lagCompensation-allowance < currentNoteTime
    && adjustedTime-lagCompensation+allowance > currentNoteTime){

      // This if statement is huge. Basically it checks that only the greenButton
      // button is held, or only the red, or only the yellow and so on.
      // although in the game, you can choose to hold down the note below,
      // e.g holding yellow and green is fine if you are playing a yellow note
      // but holding yellow and green if not fine for a green note.

      if(nextNoteTime == currentNoteTime){
        // this checks that exactly two notes are held down
        // and they are the same as the ones in the file
        if(
          (currentNoteColour == 0 && greenButton == true ||
          currentNoteColour == 1 && redButton == true ||
          currentNoteColour == 2 && yellowButton == true ||
          currentNoteColour == 3 && blueButton == true ||
          currentNoteColour == 4 && orangeButton == true) &&
          (nextNoteColour == 0 && greenButton == true ||
          nextNoteColour == 1 && redButton == true ||
          nextNoteColour == 2 && yellowButton == true ||
          nextNoteColour == 3 && blueButton == true ||
          nextNoteColour == 4 && orangeButton == true))
          {
            // updating informaion
            songInfoPointer->currentNote += 2;
            songInfoPointer->notesHit += 2;
            songInfoPointer->streak += 2;
            if((songInfoPointer->streak%10 == 0 || (songInfoPointer->streak)-1%10 == 0) && songInfoPointer->multiplier < 4)
              songInfoPointer->multiplier++;
            if(songInfoPointer->streak > 100)
              songInfoPointer->multiplier = 8;


            if(songInfoPointer->rockOMeter < 100)
              songInfoPointer->rockOMeter+=2;
            songInfoPointer->score += 100 * songInfoPointer->multiplier;

            // setting up flames and holding notesHit
            // means that the game can tell if a note needs to be held down
            // so the player can hold them for more points
            if(currentNoteColour == 0){
              songInfoPointer->flame1 = 0;
              songInfoPointer->greenHolding = currentTime + currentNoteHolding*songInfoPointer->videoSpeed;
            }
            if(currentNoteColour == 1){
              songInfoPointer->flame2 = 0;
              songInfoPointer->redHolding = currentTime + currentNoteHolding*songInfoPointer->videoSpeed;
            }
            if(currentNoteColour == 2){
              songInfoPointer->flame3 = 0;
              songInfoPointer->yellowHolding = currentTime + currentNoteHolding*songInfoPointer->videoSpeed;
            }
            if(currentNoteColour == 3){
              songInfoPointer->flame4 = 0;
              songInfoPointer->blueHolding = currentTime + currentNoteHolding*songInfoPointer->videoSpeed;
            }
            if(currentNoteColour == 4){
              songInfoPointer->flame5 = 0;
              songInfoPointer->orangeHolding = currentTime + currentNoteHolding*songInfoPointer->videoSpeed;
            }
            if(nextNoteColour == 0){
              songInfoPointer->flame1 = 0;
              songInfoPointer->greenHolding = currentTime + nextNoteHolding*songInfoPointer->videoSpeed;
            }
            if(nextNoteColour == 1){
              songInfoPointer->flame2 = 0;
              songInfoPointer->redHolding = currentTime + nextNoteHolding*songInfoPointer->videoSpeed;
            }
            if(nextNoteColour == 2){
              songInfoPointer->flame3 = 0;
              songInfoPointer->yellowHolding = currentTime + nextNoteHolding*songInfoPointer->videoSpeed;
            }
            if(nextNoteColour == 3){
              songInfoPointer->flame4 = 0;
              songInfoPointer->blueHolding = currentTime + nextNoteHolding*songInfoPointer->videoSpeed;
            }
            if(nextNoteColour == 4){
              songInfoPointer->flame5 = 0;
              songInfoPointer->orangeHolding = currentTime + nextNoteHolding*songInfoPointer->videoSpeed;
            }
          }
      }
      else if((currentNoteColour == 0 && greenButton == true &&
        redButton == false && yellowButton == false &&
        blueButton == false && orangeButton == false) ||
        (currentNoteColour == 1 && redButton == true &&
          yellowButton == false && blueButton == false &&
          orangeButton == false) ||
        (currentNoteColour == 2 && yellowButton == true &&
           blueButton == false && orangeButton == false) ||
        (currentNoteColour == 3 && blueButton == true && orangeButton == false)||
        currentNoteColour == 4 && orangeButton == true )
      {
        if(currentNoteColour == 0){
          songInfoPointer->flame1 = 0;
          songInfoPointer->greenHolding = currentTime + currentNoteHolding*songInfoPointer->videoSpeed;
        }
        if(currentNoteColour == 1){
          songInfoPointer->flame2 = 0;
          songInfoPointer->redHolding = currentTime + currentNoteHolding*songInfoPointer->videoSpeed;
        }
        if(currentNoteColour == 2){
          songInfoPointer->flame3 = 0;
          songInfoPointer->yellowHolding = currentTime + currentNoteHolding*songInfoPointer->videoSpeed;
        }
        if(currentNoteColour == 3){
          songInfoPointer->flame4 = 0;
          songInfoPointer->blueHolding = currentTime + currentNoteHolding*songInfoPointer->videoSpeed;
        }
        if(currentNoteColour == 4){
          songInfoPointer->flame5 = 0;
          songInfoPointer->orangeHolding = currentTime + currentNoteHolding*songInfoPointer->videoSpeed;
        }

        // updating informaion

        songInfoPointer->currentNote ++;
        songInfoPointer->notesHit ++;
        songInfoPointer->streak ++;
        if(songInfoPointer->streak%10 == 0 && songInfoPointer->multiplier < 4)
          songInfoPointer->multiplier++;
        if(songInfoPointer->rockOMeter < 100)
          songInfoPointer->rockOMeter+=1;
        songInfoPointer->score += 50 * songInfoPointer->multiplier;
        if(songInfoPointer->streak > 100)
          songInfoPointer->multiplier = 8;
      }
    }


    else{
      // player has missed a note

      songInfoPointer->notesMissed ++;
      songInfoPointer->streak = 0;
      songInfoPointer->multiplier = 1;
      songInfoPointer->rockOMeter-=1;
    }
  }
  if(adjustedTime-lagCompensation-allowance > currentNoteTime)
  {
    // Missed a note
    songInfoPointer->streak = 0;
    songInfoPointer->currentNote++;
    songInfoPointer->notesMissed ++;
    songInfoPointer->multiplier = 1;
    songInfoPointer->rockOMeter-=1;
  }


  // buttons contains true or false values to check weather a note has been hasHitNotes
  // or not

}



// read keyboard input
// this also checks weather the player has hit a note or note, yes please. I meaaaaaan.
void input(struct songInfo *songInfoPointer, long long currentTime){
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    SDL_PumpEvents();

    greenButton = false;
    redButton = false;
    yellowButton = false;
    blueButton = false;
    orangeButton = false;
    strumKey = false;
    strumUp = false;
    strumDown = false;
    if (state[SDL_SCANCODE_F1] || state[SDL_SCANCODE_1]) {
        greenButton = true;
    }
    if (state[SDL_SCANCODE_F2] || state[SDL_SCANCODE_2]) {
        redButton = true;
    }
    if (state[SDL_SCANCODE_F3] || state[SDL_SCANCODE_3]) {
        yellowButton = true;
    }
    if (state[SDL_SCANCODE_F4] || state[SDL_SCANCODE_4]) {
        blueButton = true;
    }
    if (state[SDL_SCANCODE_F5] || state[SDL_SCANCODE_5]) {
        orangeButton = true;
    }

    if (state[SDL_SCANCODE_UP]) {
      if(canStrum == true)
      {
        strumKey = true;
        canStrum = false;
        strumDown = true;
      }
    }
    else
    {
        canStrum = true;
    }


    if (state[SDL_SCANCODE_LEFT]) {
      if(canStrum2 == true)
      {
        strumKey = true;
        canStrum2 = false;
        strumUp = true;
      }
    }
    else
    {
        canStrum2 = true;
    }


    if (state[SDL_SCANCODE_ESCAPE]) {
        exit(0);
    }


    // the user has strummed, so we pass different arguments
    if(strumKey == true){
      hasHitNotes(songInfoPointer,currentTime,greenButton,redButton,yellowButton,blueButton,orangeButton,true);
    }
    // the user has not strummed so this will only be for hopos and holding notes
    else{
      hasHitNotes(songInfoPointer,currentTime,greenButton,redButton,yellowButton,blueButton,orangeButton,false);

    }
    return;
}



void readSongFromFile(char fileName[],struct songInfo *songInfoPointer,int songID){
  //songs/test/notes.chart
  FILE *file;
  file = fopen(fileName,"r");
  char line[256];
  char *linePtr;
  char *brokenLine;

  int lineNumber = 0; // This will increase for every line
  int flag = 0; // this is to remove the star powers so that they don't cuase problems
  bool startToRead = false;

  float videoSpeeds[] = {0,0.96,1,1.026,1.12,0.645,1.27,0.875,0.92,0.632,0.785};

  songInfoPointer->videoSpeed = videoSpeeds[songID];
  // these are the flames used to show if the player has hit a noteAge
  // or not. The value represents their relative height. With 50 being
  // and offscreen value so that they cannot be seen. They are set to a 0 when
  // a player hits a note, before moving upwards and offscreen.
  songInfoPointer->flame1 = 100;
  songInfoPointer->flame2 = 100;
  songInfoPointer->flame3 = 100;
  songInfoPointer->flame4 = 100;
  songInfoPointer->flame5 = 100;
  songInfoPointer->score = 0;
  songInfoPointer->streak = 0;
  songInfoPointer->totalSongNotes = 0;
  songInfoPointer->currentNote = 0;
  songInfoPointer->notesHit = 0;
  songInfoPointer->notesMissed = 0;
  songInfoPointer->rockOMeter = 50;
  songInfoPointer->multiplier = 1;
  songInfoPointer->greenHolding = 0;
  songInfoPointer->redHolding = 0;
  songInfoPointer->yellowHolding = 0;
  songInfoPointer->blueHolding = 0;
  songInfoPointer->orangeHolding = 0;
  memset(&songInfoPointer->noteDuration[0], 0, sizeof(songInfoPointer->noteDuration));
  memset(&songInfoPointer->noteColour[0], 0, sizeof(songInfoPointer->noteColour));
  memset(&songInfoPointer->noteTiming[0], 0, sizeof(songInfoPointer->noteTiming));
  memset(&songInfoPointer->starPowerStart[0], 0, sizeof(songInfoPointer->starPowerStart));
  memset(&songInfoPointer->starPowerLength[0], 0, sizeof(songInfoPointer->starPowerLength));


  while (fgets(line, sizeof(line), file)) {

      if(startToRead)
      {
        if(strlen(line) > 5) // making sure the line has enough data to parse through
        {
          flag = 0;
          brokenLine = strtok(line," \t=");
          songInfoPointer->noteTiming[lineNumber] = atoi(brokenLine);
          brokenLine = strtok (NULL, " \t=");
          if(strcmp(brokenLine,"S") == 0)
          {
            flag = 1;
          }
          brokenLine = strtok (NULL, " \t=");
          songInfoPointer->noteColour[lineNumber] = atoi(brokenLine);
          brokenLine = strtok (NULL, " \t=");
          songInfoPointer->noteDuration[lineNumber] = atoi(brokenLine);
          if(flag == 0){
            lineNumber ++;
            songInfoPointer->totalSongNotes++;
          }

        }
      }

      if(strncmp(line,"[ExpertSingle]",14) == 0){
          startToRead = true;
      }
      else{
      }
  }

  fclose(file);
}




void printoutNotes(struct songInfo *songInfoPointer, long long currentTime ){

  int i = 0;

  if(currentTime > songInfoPointer->noteTiming[songInfoPointer->currentNote]){

  	// show note on screen
  	for(i=0;i<3*songInfoPointer->noteColour[songInfoPointer->currentNote];i++){
  		printf("   ");
  	}
  	++songInfoPointer->currentNote;
  	printf("O00"); // The O represents the note
  }
  else{
    printf("\n");
  }
}
