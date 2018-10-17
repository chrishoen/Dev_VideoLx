#include "stdafx.h"

#include "SDL.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

int main(int argc,char** argv)
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize the program.

   int tRet;
   SDL_Window*   tWindow = 0;
   SDL_Surface*  tSurface = 0;
   SDL_Renderer* tRenderer = 0;
   SDL_Texture*  tBackground = 0;
   SDL_Texture*  tShape = 0;

   SDL_Rect tRectA;

   int tWindowW = 640;
   int tWindowH = 480;
   int tRectW   = 200;
   int tRectH   = 200;

   tRectA.x = tWindowW/2 - tRectW/2;
   tRectA.y = tWindowH / 2 - tRectH/2;
   tRectA.w = tRectW;
   tRectA.h = tRectH;

      // Initialize SDL.
      tRet = SDL_Init(SDL_INIT_VIDEO);

      // Create window.
      tWindow = SDL_CreateWindow("Video2",
         SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
         tWindowH, tWindowH,0);

      // Create renderer.
      tRenderer = SDL_CreateRenderer(tWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

      // Set renderer to the same size as the window.
      SDL_RenderSetLogicalSize(tRenderer, tWindowW, tWindowH);

      // Set renderer to blue.
      SDL_SetRenderDrawColor(tRenderer, 0, 0, 255, 255);

      // Clear the window and make it all blue.
      SDL_RenderClear(tRenderer);

      // Set renderer to red.
      SDL_SetRenderDrawColor(tRenderer, 255, 0, 0, 255);

      // Render the rectangle.
      SDL_RenderFillRect(tRenderer, &tRectA);

      // Render the changes above.
      SDL_RenderPresent(tRenderer);

      // Wait.
      printf("press enter\n");
      getchar();


   // Done.
   if (tRenderer) SDL_DestroyRenderer(tRenderer);
   if (tWindow)   SDL_DestroyWindow(tWindow);
   SDL_Quit();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize the program.

   printf("press enter\n");
   getchar();
   return 0;
}
