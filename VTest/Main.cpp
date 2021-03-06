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

void my_show_window_flags(SDL_Window* aWindow)
{
   unsigned int tFlags = SDL_GetWindowFlags(aWindow);
   char tString[100]="";
   if (tFlags & SDL_WINDOW_SHOWN)      strcat(tString, "shown ");
   if (tFlags & SDL_WINDOW_HIDDEN)     strcat(tString, "hidden ");
   if (tFlags & SDL_WINDOW_FULLSCREEN) strcat(tString, "fullscreen ");
   if (tFlags & SDL_WINDOW_OPENGL)     strcat(tString, "opengl ");

   printf("WindowFlags %8X  %s\n", tFlags,tString);
}

void my_show_render_info(const char* aLabel, SDL_RendererInfo* aInfo)
{

   char tString[100]="";
   if (aInfo->flags & SDL_RENDERER_SOFTWARE)      strcat(tString, "software ");
   if (aInfo->flags & SDL_RENDERER_ACCELERATED)   strcat(tString, "accelerated ");
   if (aInfo->flags & SDL_RENDERER_PRESENTVSYNC)  strcat(tString, "presentvsync ");
   if (aInfo->flags & SDL_RENDERER_TARGETTEXTURE) strcat(tString, "targettexture ");

   printf("RenderInfo  %-16s %-10s %5X %s\n", aLabel, aInfo->name, aInfo->flags,tString);
}

void my_show_display_info(int tDisplayIndex)
{
   SDL_DisplayMode  tDisplayMode;
   int tRet = SDL_GetCurrentDisplayMode(0, &tDisplayMode);
   if (tRet) my_error("SDL_GetCurrentDisplayMode");

   printf("Display wh             %5d %5d\n", tDisplayMode.w, tDisplayMode.h);
   printf("Display refresh rate   %5d\n", tDisplayMode.refresh_rate);
}

void my_show_gl_info()
{
   int tRet;
   int tValue;
   char tString[100] = "";

   tRet = SDL_GL_GetAttribute(SDL_GL_DOUBLEBUFFER, &tValue);
   if (tRet) my_error("SDL_GL_GetAttribute");

   SDL_GL_GetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, &tValue);
   if (tValue == SDL_GL_CONTEXT_PROFILE_ES) strcpy(tString, "GLES");
   else                                     strcpy(tString, "NOT GLES");
   printf("GL_CONTEXT_PROFILE_MASK      %5d %s\n", tValue,tString);

   SDL_GL_GetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, &tValue);
   printf("GL_CONTEXT_MAJOR_VERSION     %5d\n", tValue);

   SDL_GL_GetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, &tValue);
   printf("GL_CONTEXT_MINOR_VERSION     %5d\n", tValue);

   SDL_GL_GetAttribute(SDL_GL_DOUBLEBUFFER, &tValue);
   printf("GL_DOUBLEBUFFER              %5d\n", tValue);

   SDL_GL_GetAttribute(SDL_GL_ACCELERATED_VISUAL, &tValue);
   printf("GL_ACCELERATED_VISUAL        %5d\n", tValue);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

int main(int argc,char** argv)
{
   printf("VTEST**********************************************************\n");
   printf("VTEST**********************************************************\n");
   printf("VTEST**********************************************************\n");
   
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Local variables.

   int tRet;
   int tRunCode = 1;
   SDL_Window*      tWindow = 0;
   SDL_Surface*     tSurface = 0;
   SDL_Surface*     tImage;
   SDL_Renderer*    tRenderer = 0;
   SDL_Texture*     tBackground = 0;
   SDL_Texture*     tShape = 0;
   SDL_RendererInfo tRenderInfo;
   SDL_Rect         tRectA;

   int tDisplay = 0;
   int tWindowW = 640;
   int tWindowH = 480;
   int tRectW = 200;
   int tRectH = 200;

   tWindowW = 1920;
   tWindowH = 1080;
   tWindowW = 1440;
   tWindowH = 2560;

   tRectA.x = tWindowW / 2 - tRectW / 2;
   tRectA.y = tWindowH / 2 - tRectH / 2;
   tRectA.w = tRectW;
   tRectA.h = tRectH;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Initialize SDL.

// putenv((char*)"FRAMEBUFFER=/dev/fb0");
// putenv((char*)"SDL_FBDEV=/dev/fb0");
// putenv((char*)"SDL_VIDEODRIVER=kmsdrm");
   putenv((char*)"SDL_NOMOUSE=1");
   putenv((char*)"DISPLAY=:0");
   
   printf("\n");
   printf("SDL_Init*******************************************************\n");
   tRet = SDL_Init(SDL_INIT_VIDEO);
   if (tRet) my_error("SDL_Init");
   
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Show SDL info.

   printf("\n");
   printf("VideoDrivers***************************************************\n");
   int tNumVideoDrivers = SDL_GetNumVideoDrivers();
   printf("NumVideoDrivers        %1d\n", tNumVideoDrivers);
   for (int i=0;i<tNumVideoDrivers;i++)
   {
      printf("VideoDriver            %s\n",SDL_GetVideoDriver(i));
   }

   printf("\n");
   printf("VideoDisplays***************************************************\n");
   int tNumVideoDisplays = SDL_GetNumVideoDisplays();
   printf("NumVideoDisplays       %1d\n", tNumVideoDisplays);

   printf("\n");
   printf("RendererDrivers************************************************\n");
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

   printf("\n");
   printf("CreateWindow***************************************************\n");
   unsigned int tWindowFlags = 0;
   tWindowFlags |= SDL_WINDOW_SHOWN;
   tWindowFlags |= SDL_WINDOW_BORDERLESS;
   tWindowFlags |= SDL_WINDOW_MAXIMIZED;
   tWindowFlags |= SDL_WINDOW_OPENGL;

   tWindow = SDL_CreateWindow("TVideo",
      SDL_WINDOWPOS_CENTERED_DISPLAY(tDisplay), SDL_WINDOWPOS_CENTERED_DISPLAY(tDisplay),
//    SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
      tWindowW, tWindowH,tWindowFlags);
   if(tWindow == 0) my_error("SDL_CreateWindow");

   my_show_window_flags(tWindow);
   
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Create renderer.

   if (tRunCode==1)
   {
      printf("CreateRenderer*************************************************\n");
      int tRenderDriverIndex = -1;
      tRenderDriverIndex = 0;
      unsigned int tRenderFlags = 0;
      tRenderFlags |= SDL_RENDERER_ACCELERATED;
      tRenderFlags |= SDL_RENDERER_PRESENTVSYNC;

      tRenderer = SDL_CreateRenderer(tWindow, tRenderDriverIndex, tRenderFlags);
      if (tRenderer == 0) my_error("SDL_CreateRenderer");

      // Set renderer to the same size as the window.
      SDL_RenderSetLogicalSize(tRenderer, tWindowW, tWindowH);

      SDL_GetRendererInfo(tRenderer, &tRenderInfo);
      my_show_render_info("Renderer", &tRenderInfo);
   }

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Draw the window.

   if (tRunCode == 1)
   {
      printf("DrawWindow*****************************************************\n");
      
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

      my_show_window_flags(tWindow);
   }
   
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Draw the window.

   if (tRunCode == 2)
   {
      printf("DrawWindow*****************************************************\n");
      
      tSurface = SDL_GetWindowSurface(tWindow);
      if (tSurface == 0) my_error("SDL_GetWindowSurface");

      tImage = SDL_LoadBMP("/opt/alpha/image/sails.bmp");
      if (tImage == 0) my_error("SDL_LoadBMP");

      tRet = SDL_BlitSurface(tImage, NULL, tSurface, NULL);
      if(tRet) my_error("SDL_BlitSurface");

      tRet = SDL_UpdateWindowSurface(tWindow);
      if(tRet) my_error("SDL_UpdateWindowSurface");
      my_show_window_flags(tWindow);
  
      SDL_FreeSurface(tImage);
   }
   
   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Show info.

   printf("\n");
   printf("Info************************************************************\n");

   my_show_display_info(0);
   my_show_gl_info();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Done.

   printf("Wait***********************************************************\n");
   my_wait2();

   if (tRenderer) SDL_DestroyRenderer(tRenderer);
   if (tWindow)   SDL_DestroyWindow(tWindow);
   SDL_Quit();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Exit the program.

   return 0;
}
