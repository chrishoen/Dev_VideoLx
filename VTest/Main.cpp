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

void my_show_render_info(char* aLabel, SDL_RendererInfo* aInfo)
{

   char tString[100]="";
   if (aInfo->flags & SDL_RENDERER_SOFTWARE)      strcat(tString, "software ");
   if (aInfo->flags & SDL_RENDERER_ACCELERATED)   strcat(tString, "accelerated ");
   if (aInfo->flags & SDL_RENDERER_PRESENTVSYNC)  strcat(tString, "presentvsync ");
   if (aInfo->flags & SDL_RENDERER_TARGETTEXTURE) strcat(tString, "targettexture ");

   printf("RenderInfo  %-16s %-10s %5X %s\n", aLabel, aInfo->name, aInfo->flags,tString);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

int main(int argc,char** argv)
{
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Local variables.

   SDL_Window*      tWindow = 0;
   SDL_Surface*     tSurface = 0;
   SDL_Renderer*    tRenderer = 0;
   SDL_Texture*     tBackground = 0;
   SDL_Texture*     tShape = 0;
   SDL_RendererInfo tRenderInfo;
   SDL_Rect         tRectA;

   int tWindowW = 640;
   int tWindowH = 480;
   int tRectW = 200;
   int tRectH = 200;

   tRectA.x = tWindowW / 2 - tRectW / 2;
   tRectA.y = tWindowH / 2 - tRectH / 2;
   tRectA.w = tRectW;
   tRectA.h = tRectH;

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
   
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Show SDL info.

   printf("\n\n");
   int tNumVideoDrivers = SDL_GetNumVideoDrivers();
   printf("NumVideoDrivers        %1d\n", tNumVideoDrivers);
   for (int i=0;i<tNumVideoDrivers;i++)
   {
      printf("VideoDriver            %s\n",SDL_GetVideoDriver(i));
   }

   printf("\n\n");
   int tNumRenderDrivers = SDL_GetNumRenderDrivers();
   printf("NumRenderDrivers       %1d\n", tNumRenderDrivers);
   for (int i=0;i<tNumRenderDrivers;i++)
   {
      SDL_GetRenderDriverInfo(i,&tRenderInfo);
      my_show_render_info("RenderDriver", &tRenderInfo);
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Create window.

   unsigned int tWindowFlags = 0;
// tWindowFlags |= SDL_WINDOW_FULLSCREEN_DESKTOP;

   tWindow = SDL_CreateWindow("Video2",
      SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
      tWindowH, tWindowH,tWindowFlags);
   if(tWindow == 0) my_error("SDL_CreateWindow");

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Create renderer.

   int tRenderDriverIndex = -1;
   unsigned int tRenderFlags = 0;
   tRenderFlags |= SDL_RENDERER_ACCELERATED;
   tRenderFlags |= SDL_RENDERER_PRESENTVSYNC;

   tRenderer = SDL_CreateRenderer(tWindow, tRenderDriverIndex, tRenderFlags);
   if (tRenderer == 0) my_error("SDL_CreateRenderer");

   // Set renderer to the same size as the window.
   SDL_RenderSetLogicalSize(tRenderer, tWindowW, tWindowH);

   SDL_GetRendererInfo(tRenderer, &tRenderInfo);
   my_show_render_info("Renderer", &tRenderInfo);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Draw the window.

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

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
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
