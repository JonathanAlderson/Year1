#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <math.h>

#include "gameData.h"
#include "gameFunctions.h"
#include "SDLTextures.h"


#define screenWidth 1920*0.9
#define screenHeight 1080*0.9

// this draws the fretboard to the screen, hopefully
void drawObject( SDL_Texture *texture ){

    //SDL_RenderClear(renderer);
    SDL_Rect rect;
    rect.h = screenHeight;
    rect.w = screenWidth;
    rect.x = 0;
    rect.y = 0;
    SDL_RenderCopy(renderer, texture, NULL, &rect);
}


// initialise the game data
void init(void){

    SDL_Window *window = NULL;
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());

    atexit(SDL_Quit); // set for clean-up on exit
    IMG_Init(IMG_INIT_PNG);

    SDL_CreateWindowAndRenderer(screenWidth, screenHeight, 0, &window, &renderer);
    SDL_SetWindowTitle( window, "Keyboard Hero");
    SDL_SetRenderDrawColor(renderer, 0, 0 ,0, 0);
    SDL_RenderClear(renderer);


    splashScreenSurface = IMG_Load("images/splashScreen.png");
    splashScreenTexture = SDL_CreateTextureFromSurface(renderer, splashScreenSurface);

    drawObject(splashScreenTexture);
    SDL_RenderPresent(renderer);


    greenButton = false;
    redButton = false;
    yellowButton = false;
    blueButton = false;
    orangeButton = false;
    number = 0;
    return;
}

void loadImages(void)
{
  fretboardSurface = IMG_Load("images/fretboard.png");
  backGroundSurface = IMG_Load("images/backgroundStd.png");
  starPowerBackGroundSurface = IMG_Load("images/backgroundStarPower.png");
  multiplier1Surface = IMG_Load("images/multiplier1.png");
  multiplier2Surface = IMG_Load("images/multiplier2.png");
  multiplier3Surface = IMG_Load("images/multiplier3.png");
  multiplier4Surface = IMG_Load("images/multiplier4.png");
  multiplier6Surface = IMG_Load("images/multiplier6.png");
  multiplier8Surface = IMG_Load("images/multiplier8.png");
  streakCounterSurface = IMG_Load("images/streakCounter.png");
  progressMeterSurface = IMG_Load("images/progressMeter.png");
  starPowerFretboardSurface = IMG_Load("images/starPowerFretBoard.png");
  scoreCounterSurface = IMG_Load("images/scoreCounter.png");
  hoopSurface = IMG_Load("images/hoop.png");
  flameSurface = IMG_Load("images/fire1.png");
  rockOMeterBarSurface = IMG_Load("images/rockOMeterBar.png");
  songSelectionSurface = IMG_Load("images/songSelection.png");
  pickSurface = IMG_Load("images/pick.png");



  fretboardTexture = SDL_CreateTextureFromSurface(renderer, fretboardSurface);
  backGroundTexture = SDL_CreateTextureFromSurface(renderer, backGroundSurface);
  starPowerBackGroundTexture = SDL_CreateTextureFromSurface(renderer,starPowerBackGroundSurface);
  multiplier1Texture = SDL_CreateTextureFromSurface(renderer, multiplier1Surface);
  multiplier2Texture = SDL_CreateTextureFromSurface(renderer, multiplier2Surface);
  multiplier3Texture = SDL_CreateTextureFromSurface(renderer, multiplier3Surface);
  multiplier4Texture = SDL_CreateTextureFromSurface(renderer, multiplier4Surface);
  multiplier6Texture = SDL_CreateTextureFromSurface(renderer, multiplier6Surface);
  multiplier8Texture = SDL_CreateTextureFromSurface(renderer, multiplier8Surface);
  streakCounterTexture = SDL_CreateTextureFromSurface(renderer,streakCounterSurface);
  progressMeterTexture = SDL_CreateTextureFromSurface(renderer,progressMeterSurface);
  starPowerFretboardTexture = SDL_CreateTextureFromSurface(renderer,starPowerFretboardSurface);
  scoreCounterTexture = SDL_CreateTextureFromSurface(renderer,scoreCounterSurface);
  hoopTexture = SDL_CreateTextureFromSurface(renderer,hoopSurface);
  flameTexure = SDL_CreateTextureFromSurface(renderer,flameSurface);
  rockOMeterBarTexture = SDL_CreateTextureFromSurface(renderer,rockOMeterBarSurface);
  songSelectionTexture = SDL_CreateTextureFromSurface(renderer,songSelectionSurface);
  pickTexture = SDL_CreateTextureFromSurface(renderer,pickSurface);


  greenStdNoteSurphace = IMG_Load("images/greenStdNote.png");
  redStdNoteSurphace = IMG_Load("images/redStdNote.png");
  yellowStdNoteSurphace = IMG_Load("images/yellowStdNote.png");
  blueStdNoteSurphace = IMG_Load("images/blueStdNote.png");
  orangeStdNoteSurphace = IMG_Load("images/orangeStdNote.png");
  starPowerStdNoteSurphace = IMG_Load("images/starPowerStdNote.png");
  phraseStdNoteSurphace = IMG_Load("images/phraseStdNote.png");

  greenHopoNoteSurphace = IMG_Load("images/greenHopoNote.png");
  redHopoNoteSurphace = IMG_Load("images/redHopoNote.png");
  yellowHopoNoteSurphace = IMG_Load("images/yellowHopoNote.png");
  blueHopoNoteSurphace = IMG_Load("images/blueHopoNote.png");
  orangeHopoNoteSurphace = IMG_Load("images/orangeHopoNote.png");
  starPowerHopoNoteSurphace = IMG_Load("images/starPowerHopoNote.png");
  phraseHopoNoteSurphace = IMG_Load("images/phraseHopoNote.png");

  greenStdNoteTexture = SDL_CreateTextureFromSurface(renderer,greenStdNoteSurphace);
  redStdNoteTexture = SDL_CreateTextureFromSurface(renderer,redStdNoteSurphace);
  yellowStdNoteTexture = SDL_CreateTextureFromSurface(renderer,yellowStdNoteSurphace);
  blueStdNoteTexture = SDL_CreateTextureFromSurface(renderer,blueStdNoteSurphace);
  orangeStdNoteTexture = SDL_CreateTextureFromSurface(renderer,orangeStdNoteSurphace);
  starPowerStdNoteTexture = SDL_CreateTextureFromSurface(renderer,starPowerStdNoteSurphace);
  phraseStdNoteTexture = SDL_CreateTextureFromSurface(renderer,phraseStdNoteSurphace);

  greenHopoNoteTexture = SDL_CreateTextureFromSurface(renderer,greenHopoNoteSurphace);
  redHopoNoteTexture = SDL_CreateTextureFromSurface(renderer,redHopoNoteSurphace);
  yellowHopoNoteTexture = SDL_CreateTextureFromSurface(renderer,yellowHopoNoteSurphace);
  blueHopoNoteTexture = SDL_CreateTextureFromSurface(renderer,blueHopoNoteSurphace);
  orangeHopoNoteTexture = SDL_CreateTextureFromSurface(renderer,orangeHopoNoteSurphace);
  starPowerHopoNoteTexture = SDL_CreateTextureFromSurface(renderer,starPowerHopoNoteSurphace);
  phraseHopoNoteTexture = SDL_CreateTextureFromSurface(renderer,phraseHopoNoteSurphace);

  greenTrailSurphace = IMG_Load("images/greenTrail.png");
  redTrailSurphace = IMG_Load("images/redTrail.png");
  yellowTrailSurphace = IMG_Load("images/yellowTrail.png");
  blueTrailSurphace = IMG_Load("images/blueTrail.png");
  orangeTrailSurphace = IMG_Load("images/orangeTrail.png");

  greenTrailTexture = SDL_CreateTextureFromSurface(renderer,greenTrailSurphace);
  redTrailTexture = SDL_CreateTextureFromSurface(renderer,redTrailSurphace);
  yellowTrailTexture = SDL_CreateTextureFromSurface(renderer,yellowTrailSurphace);
  blueTrailTexture = SDL_CreateTextureFromSurface(renderer,blueTrailSurphace);
  orangeTrailTexture = SDL_CreateTextureFromSurface(renderer,orangeTrailSurphace);

  songFailedSurface = IMG_Load("images/songFailed.png");
  endScreenSurface = IMG_Load("images/endScreen.png");
  songFailedTexture = SDL_CreateTextureFromSurface(renderer,songFailedSurface);
  endScreenTexture = SDL_CreateTextureFromSurface(renderer,endScreenSurface);
  return;
}





void drawItem(SDL_Texture *texture,int h,int w,int x,int y){
  SDL_Rect rect;
  rect.h = h;
  rect.w = w;
  rect.x = x;
  rect.y = y;
  SDL_RenderCopy(renderer,texture,NULL,&rect);
}


// colour determines the lane the note goes in, distance is for how long the note has been alive for
void drawNote(SDL_Texture *texture,int colour, int noteAge){

    double newNoteAge = pow(noteAge,1.9);
    SDL_Rect rect;
    rect.h = screenHeight * 0.01 + 0.0001  * newNoteAge;
    rect.w = screenWidth * 0.01 + 0.00015 * newNoteAge;
    rect.x = screenWidth * 0.50 - rect.w/2 + 25*(colour-2) + (colour-2)*0.00017*newNoteAge;
    rect.y = screenHeight * 0.32 + newNoteAge*0.0008;
    SDL_RenderCopy(renderer,texture,NULL,&rect);
}

void drawTrail(SDL_Texture *texture,int colour, int noteAge,int delay){


    double newNoteAge = pow(noteAge-delay,1.7);//*0.000001;
    SDL_Rect rect;
    rect.h = 100 +  0;//0.001 * newNoteAge;
    rect.w = 44;// + screenWidth * 0.5 + 0.00015 * newNoteAge;
    rect.x = screenWidth * 0.50 - rect.w/2 + 30*(colour-2) + (colour-2)*0.001*newNoteAge;
    rect.y = screenHeight * 0.32 + newNoteAge*0.0050;
    SDL_RenderCopy(renderer,texture,NULL,&rect);
}

void drawHoops(){
  if(greenButton){drawItem(hoopTexture,100,120,530,800);}
  if(redButton){drawItem(hoopTexture,100,120,680,800);}
  if(yellowButton){drawItem(hoopTexture,100,120,800,800);}
  if(blueButton){drawItem(hoopTexture,100,120,940,800);}
  if(orangeButton){drawItem(hoopTexture,100,120,1080,800);}
}

void drawFlames(struct songInfo *songInfoPointer){
  int flame1 = songInfoPointer->flame1;
  int flame2 = songInfoPointer->flame2;
  int flame3 = songInfoPointer->flame3;
  int flame4 = songInfoPointer->flame4;
  int flame5 = songInfoPointer->flame5;
  if(flame1<80){

    drawItem(flameTexure,100,120,530,750-flame1);
    songInfoPointer->flame1 += 3;}
  else
    drawItem(flameTexure,0,0,-500,0); // draws off screen
  if(flame2<80){
    drawItem(flameTexure,100,120,680,750-flame2);
    songInfoPointer->flame2 += 3;}
  else
    drawItem(flameTexure,0,0,-500,0); // draws off screen
  if(flame3<80){
    drawItem(flameTexure,100,120,800,750-flame3);
    songInfoPointer->flame3 += 3;}
  else
    drawItem(flameTexure,0,0,-500,0); // draws off screen
  if(flame4<80){
    drawItem(flameTexure,100,120,940,750-flame4);
    songInfoPointer->flame4 += 3;}
  else
    drawItem(flameTexure,0,0,-500,0); // draws off screen
  if(flame5<80){
    drawItem(flameTexure,100,120,1080,750-flame5);
    songInfoPointer->flame5 += 3;}
  else
    drawItem(flameTexure,0,0,-500,0); // draws off screen

  SDL_RenderPresent(renderer);
}



void drawUI(struct songInfo *songInfoPointer,TTF_Font * font,SDL_Color fontColour, int mode,char songName[],int hiScore){

  // the mode is for either during the game or for after the game
  if(mode == 1){
      if(songInfoPointer->multiplier == 1)
        drawItem(multiplier1Texture,200,200,1250,600);
      if(songInfoPointer->multiplier == 2)
        drawItem(multiplier2Texture,200,200,1250,600);
      if(songInfoPointer->multiplier == 3)
        drawItem(multiplier3Texture,200,200,1250,600);
      if(songInfoPointer->multiplier == 4)
        drawItem(multiplier4Texture,200,200,1250,600);
      if(songInfoPointer->multiplier == 6)
        drawItem(multiplier6Texture,200,200,1250,600);
      if(songInfoPointer->multiplier == 8)
        drawItem(multiplier8Texture,200,200,1250,600);

      drawItem(rockOMeterBarTexture,10,60,402,840-2.6*songInfoPointer->rockOMeter);
  }


  //const char *string = itoa(1250);
  char streakString[10];
  char scoreString[10];
  char hiScoreString[10];
  char percentageHitString[10];
  char farThroughSongString[10];

  sprintf(streakString,"%d",songInfoPointer->streak);
  sprintf(scoreString,"%d",songInfoPointer->score);
  if(hiScore > songInfoPointer->score)
    sprintf(hiScoreString,"%d",hiScore);
  else
    sprintf(hiScoreString,"%d",songInfoPointer->score);
  if(songInfoPointer->currentNote > 0){
    sprintf(percentageHitString,"%.1f",(100*songInfoPointer->notesHit)/ (songInfoPointer->notesHit+songInfoPointer->notesMissed));
    sprintf(farThroughSongString,"%.1f",(100*songInfoPointer->currentNote)/ (songInfoPointer->totalSongNotes));
  }
  else{
    sprintf(percentageHitString,"%.1f",0.0);
    sprintf(farThroughSongString,"%.1f",0.0);
  }



  SDL_DestroyTexture(farThroughSongTexture);
  SDL_DestroyTexture(scoreTexture);
  SDL_DestroyTexture(hiScoreTexture);
  SDL_DestroyTexture(streakTexture);
  SDL_DestroyTexture(percentageHitTexture);
  SDL_DestroyTexture(songNameTexture);
  SDL_FreeSurface(scoreSurface);
  SDL_FreeSurface(hiScoreSurface);
  SDL_FreeSurface(streakSurface);
  SDL_FreeSurface(percentageHitSurface);
  SDL_FreeSurface(farThroughSongSurface);
  SDL_FreeSurface(songNameSurface);

  SDL_Surface *scoreSurface = TTF_RenderText_Solid(font,scoreString,fontColour);
  SDL_Texture *scoreTexture = SDL_CreateTextureFromSurface(renderer,scoreSurface);

  SDL_Surface *hiScoreSurface = TTF_RenderText_Solid(font,hiScoreString,fontColour);
  SDL_Texture *hiScoreTexture = SDL_CreateTextureFromSurface(renderer,hiScoreSurface);

  SDL_Surface *streakSuface = TTF_RenderText_Solid(font,streakString,fontColour);
  SDL_Texture *streakTexture = SDL_CreateTextureFromSurface(renderer,streakSuface);

  SDL_Surface *percentageHitSurface = TTF_RenderText_Solid(font,percentageHitString,fontColour);
  SDL_Texture *percentageHitTexture = SDL_CreateTextureFromSurface(renderer,percentageHitSurface);

  SDL_Surface *farThroughSongSurface = TTF_RenderText_Solid(font,farThroughSongString,fontColour);
  SDL_Texture *farThroughSongTexture = SDL_CreateTextureFromSurface(renderer,farThroughSongSurface);

  SDL_Surface *songNameSurface = TTF_RenderText_Solid(font,songName,fontColour);
  SDL_Texture *songNameTexture = SDL_CreateTextureFromSurface(renderer,songNameSurface);

  if(mode == 1){
    drawItem(scoreTexture,40,60,1580,757);
    drawItem(streakTexture,40,60,1580,687);
    drawItem(percentageHitTexture,100,100,280,760);
    drawItem(farThroughSongTexture,100,100,280,660);
    drawItem(songNameTexture,60,strlen(songName)*30,100,100);
  }
  if(mode == 2){
    drawItem(scoreTexture,40,60,300,299);
    drawItem(percentageHitTexture,40,60,460,370);
    drawItem(hiScoreTexture,40,60,460,438);
    drawItem(songNameTexture,40,strlen(songName)*20,300,232);
  }



}

void drawAllNotes(struct songInfo *songInfoPointer, long long currentTime){
  //if(songInfoPointer->notesHit > 1)  //printf("Streak: %d,Score: %d,Percentage: %.2f,Completion: %.2f,Muliplier: %d,Notes Hit: %f,Notes Missed: %f,TOtla notes: %f\n",songInfoPointer->streak,songInfoPointer->score,songInfoPointer->notesHit / (songInfoPointer->notesMissed + songInfoPointer->notesHit),(songInfoPointer->notesHit+songInfoPointer->notesMissed ) / (songInfoPointer->totalSongNotes),songInfoPointer->multiplier,songInfoPointer->notesHit,songInfoPointer->notesMissed,songInfoPointer->totalSongNotes);
  // This is one of the more complex functions.
  // It creates two arrays of all the notes, HOPO's and Trails
  // it goes through the song file, and calculates which
  // songs should be on the screen, then renders then
  // the note trails are rendered in 50 px incraments
  // so they are never the exact size, they are just stacked images
  // of the trails.
  // 4000 is the guitar hero note limit


  int currentNote = 0; // which note in the array we are on
  int noteAge = 0; // how long the note has been alive for
  int noteColour = 0; // the current note colour
  int noteDuration = 0; // how long the note trail is
  int priorNoteTiming = -2000; // used for calculating Hopos' // set to a low number so that the first note cannot be a hopo
  int noteTiming = 0; // used for Hopo calculation
  int priorNoteColour = 0; // used for calculating Hopo's too
  int noteDurationReps = 0;
  int lagCompensation = 800; // to allign the audio with the video
  int hopoCutoff = 120; // max apart a note can be to count as a hopo


  // The video speed is differnt for every song and needs to be manually calculated and put into this array
  // Every song in the game has it's own number, this array contains the starPowerFretboard
  // for every song. Each song has a number beforSDL_Destre it

  SDL_Texture *allNotes[] = {greenStdNoteTexture,redStdNoteTexture,yellowStdNoteTexture,blueStdNoteTexture,orangeStdNoteTexture};
  SDL_Texture *allHopos[] = {greenHopoNoteTexture,redHopoNoteTexture,yellowHopoNoteTexture,blueHopoNoteTexture,orangeHopoNoteTexture};
  SDL_Texture *allTrails[] = {greenTrailTexture,redTrailTexture,yellowTrailTexture,blueTrailTexture,orangeTrailTexture};
  while(currentNote < 4000){
    noteDurationReps = 0;
    noteAge = currentTime*songInfoPointer->videoSpeed - songInfoPointer->noteTiming[currentNote];
    noteColour = songInfoPointer->noteColour[currentNote];
    noteDuration = songInfoPointer->noteDuration[currentNote];
    if(currentNote > 0){
      priorNoteColour = songInfoPointer->noteColour[currentNote-1];
      priorNoteTiming = songInfoPointer->noteTiming[currentNote-1];
      noteTiming = songInfoPointer->noteTiming[currentNote];
    }

    if(noteAge >= -lagCompensation && noteAge-noteDuration < 1300+lagCompensation){
        while(noteDuration-noteDurationReps > 0)
        {
          drawTrail(allTrails[noteColour],noteColour,noteAge-350+lagCompensation,noteDurationReps);
          noteDurationReps += 50;
        }
        if((noteTiming - priorNoteTiming) > 0 && (noteTiming-priorNoteTiming) < 121 && (noteColour != priorNoteColour)){
          if(currentNote >= songInfoPointer->currentNote){
            if(songInfoPointer->streak > 100)
              drawNote(starPowerHopoNoteTexture,noteColour,noteAge+lagCompensation);
            else
              drawNote(allHopos[noteColour],noteColour,noteAge+lagCompensation);

          }

        }
        else{
          if(currentNote >= songInfoPointer->currentNote && currentTime > 1000){

            if(songInfoPointer->streak > 100)
              drawNote(starPowerStdNoteTexture,noteColour,noteAge+lagCompensation);
            else
              drawNote(allNotes[noteColour],noteColour,noteAge+lagCompensation);
          }



        }
    }
    currentNote++; // apparently you can incrament a pointer?
  }

}


int songSelection( int chosenSong){
  if(chosenSong == 1) drawItem(pickTexture,40,40,420,60);
  if(chosenSong == 2) drawItem(pickTexture,40,40,560,150);
  if(chosenSong == 3) drawItem(pickTexture,40,40,398,225);
  if(chosenSong == 4) drawItem(pickTexture,40,40,628,320);
  if(chosenSong == 5) drawItem(pickTexture,40,40,400,390);
  if(chosenSong == 6) drawItem(pickTexture,40,40,456,474);
  if(chosenSong == 7) drawItem(pickTexture,40,40,580,565);
  if(chosenSong == 8) drawItem(pickTexture,40,40,460,645);
  if(chosenSong == 9) drawItem(pickTexture,40,40,490,727);
  if(chosenSong == 10) drawItem(pickTexture,40,40,358,800);
  SDL_RenderPresent(renderer);
  if(strumUp && chosenSong > 1){
    chosenSong--;
  }
  if(strumDown && chosenSong < 10){
    chosenSong++;
  }
  if(greenButton){
    return chosenSong+10;

  }
  return chosenSong;
}



// render current game state

void render(int gameState,struct songInfo *songInfoPointer, long long currentTime){
    // This is forthe loading screen
    if(gameState == 0){

      drawObject(songSelectionTexture);
    }

    if(gameState == 1){

      drawObject(songSelectionTexture); // for the song selection screen
    }
    if(gameState == 2){
      if(songInfoPointer->streak > 100){
        drawObject(starPowerBackGroundTexture);
        drawObject(starPowerFretboardTexture);
      }
      else{
        drawObject(backGroundTexture);
        drawObject(fretboardTexture);
      }

      drawItem(scoreCounterTexture,62,210,1460,740);
      drawItem(streakCounterTexture,62,210,1460,670);
      drawItem(progressMeterTexture,272,66,400,570);
      drawHoops();

    }
    // successfully completed  the song
    if(gameState == 3){
      drawObject(endScreenTexture);
    }
    // failed the song
    if(gameState == 4){
      drawObject(songFailedTexture);
      SDL_RenderPresent(renderer);
    }


    return;
}


int viewEndCard(char cdDirectory[100],struct songInfo *songInfoPointer,TTF_Font * font,SDL_Color fontColour, char songName[],char hiScoreDirectory[]){
  if(greenButton){
    return 20000; // to break the loop and go back to main menu
  }
  SDL_DestroyTexture(cdTexture);
  SDL_FreeSurface(cdSurface);

  cdSurface = IMG_Load(cdDirectory);
  cdTexture = SDL_CreateTextureFromSurface(renderer,cdSurface);
  drawItem(cdTexture,400,400,730,100);

  FILE* file = fopen (hiScoreDirectory, "r");
  int highScore = 0;
  fscanf (file, "%d", &highScore);
  fclose (file);
  drawUI(songInfoPointer,font,fontColour,2,songName,highScore);
  if(songInfoPointer->score > highScore){
    FILE* file = fopen (hiScoreDirectory, "w");
    fprintf (file, "%d", songInfoPointer->score);
    fclose (file);
  }





  SDL_RenderPresent(renderer);
}

void clearScreen(){
  //SDL_RenderClear(renderer);
}
