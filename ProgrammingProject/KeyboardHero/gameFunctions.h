struct songInfo{
        int currentNote;
        int noteDuration[10000]; 	// how long the player has to hold the note for
        int noteColour[10000];   	// what colour the note is
        int noteTiming[10000];   	// when the note plays in the song
        int starPowerStart[100]; 	// star power start time
        int starPowerLength[100];	// how long the star power lasts for
        float videoSpeed;
        int flame1;
        int flame2;
        int flame3;
        int flame4;
        int flame5;
        int score;
        int streak;
        float totalSongNotes;
        float notesHit;
        float notesMissed;
        int rockOMeter;
        int multiplier;
        int greenHolding;
        int redHolding;
        int yellowHolding;
        int blueHolding;
        int orangeHolding;
  };

void input(struct songInfo *songInfoPointer, long long currentTime);

long long current_timestamp();
void printoutNotes(struct songInfo *singInfoPointer, long long currentTime );
void readSongFromFile(char fileName[],struct songInfo *songInfoPointer,int songID);
void hasHitNotes(struct songInfo *songInfoPointer, long long currentTime,
                 bool greenButton,bool redButton, bool yellowButton,
                 bool blueButton, bool orangeButton, bool hasStrummed);
