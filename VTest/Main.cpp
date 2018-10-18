#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "SDL.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

void my_error(const char* aString)
{
   printf("MY_ERROR %s ERROR %s\n",aString,SDL_GetError());
   exit(1);
}

void my_wait1()
{
   while (true)
   {
      SDL_Event tEvent;
      SDL_PollEvent(&tEvent);
      if (tEvent.type == SDL_QUIT) break;
      if (tEvent.type == SDL_KEYDOWN) break;
      if (tEvent.type == SDL_MOUSEBUTTONDOWN) break;
   }
}

void my_wait2()
{
   printf("press enter\n");
   getchar();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

int main(int argc,char** argv)
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize SDL.


   putenv((char*)"FRAMEBUFFER=/dev/fb0");
   putenv((char*)"SDL_FBDEV=/dev/fb0");
   putenv((char*)"SDL_NOMOUSE=1");
   putenv((char*)"DISPLAY=:0");
   
   int tRet = SDL_Init(SDL_INIT_VIDEO);
   if (tRet) my_error("SDL_Init");
   
   printf("\n\n");
   int tNumVideoDrivers = SDL_GetNumVideoDrivers();
   printf("VideoDrivers       %d\n", tNumVideoDrivers);
   for (int i=0;i<tNumVideoDrivers;i++)
   {
      printf("VideoDriver          %s\n",SDL_GetVideoDriver(i));
   }

   printf("\n\n");
   int tNumRenderDrivers = SDL_GetNumRenderDrivers();
   printf("RenderDrivers       %d\n", tNumRenderDrivers);
   for (int i=0;i<tNumRenderDrivers;i++)
   {
      SDL_RendererInfo tInfo;      
      SDL_GetRenderDriverInfo(i,&tInfo);
      printf("\n");
      printf("RenderDriver name    %d %s\n",i,tInfo.name);
      printf("RenderDriver flags   %X\n",tInfo.flags);

      printf("RenderDriver SDL_RENDERER_SOFTWARE      %d\n",tInfo.flags & SDL_RENDERER_SOFTWARE ? 1:0);
      printf("RenderDriver SDL_RENDERER_ACCELERATED   %d\n",tInfo.flags & SDL_RENDERER_ACCELERATED ? 1:0);
      printf("RenderDriver SDL_RENDERER_PRESENTVSYNC  %d\n",tInfo.flags & SDL_RENDERER_PRESENTVSYNC ? 1:0);
      printf("RenderDriver SDL_RENDERER_TARGETTEXTURE %d\n",tInfo.flags & SDL_RENDERER_TARGETTEXTURE ? 1:0);
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Draw a window.

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

   // Create window.
   tWindow = SDL_CreateWindow("Video2",
      SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
      tWindowH, tWindowH,0);
   if(tWindow == 0) my_error("SDL_CreateWindow");

   // Create renderer.
   tRenderer = SDL_CreateRenderer(tWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
   if (tRenderer == 0) my_error("SDL_CreateRenderer");

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
   my_wait1();

   // Done.
   if (tRenderer) SDL_DestroyRenderer(tRenderer);
   if (tWindow)   SDL_DestroyWindow(tWindow);
   SDL_Quit();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Exit the program.

   return 0;
}
