#include "stdafx.h"

#include <iostream>
#include <stdexcept>

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

   try
   {
      putenv((char*)"FRAMEBUFFER=/dev/fb0");
      putenv((char*)"SDL_FBDEV=/dev/fb0");
      putenv((char*)"SDL_NOMOUSE=1");

      // Initialize SDL.
      tRet = SDL_Init(SDL_INIT_VIDEO);
      if (tRet) throw std::runtime_error("SDL_Init");

      // Create window.
      tWindow = SDL_CreateWindow("Video2",
         SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
         tWindowH, tWindowH,0);
      if(tWindow == 0) throw std::runtime_error("SDL_CreateWindow");

      // Create renderer.
      tRenderer = SDL_CreateRenderer(tWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
      if (tRenderer == 0) throw std::runtime_error("SDL_CreateRenderer");

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

   }
   catch (std::exception& e)
   {
      printf("main FAIL %s\n",e.what());
   }

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
