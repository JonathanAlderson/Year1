
void drawObject( SDL_Texture *texture );
void init(void);

void draw_fretboard( SDL_Texture *texture );

void loadImages(void);
void clearScreen();
void drawItem(SDL_Texture *texture,int h,int w,int x,int y);
void render(int gameState,struct songInfo *songInfoPointer, long long currentTime);
void drawTrail(SDL_Texture *texture,int h,int w,int x,int y,int z);
void drawNote(SDL_Texture *texture,int colour, int noteAge);
void drawFlames(struct songInfo *songInfoPointer);
void drawHoops();
