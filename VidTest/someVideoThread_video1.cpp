/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "stdafx.h"


#include "SDL.h"
#include "SDL_image.h"

#include "risProgramTime.h"
#include "risAlphaDir.h"

#include "someVideoParms.h"
#include "someVideoThread.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Draw some video.

void VideoThread::doVideoStart()
{
   Prn::print(Prn::ThreadRun1, "VideoThread::doVideoStart");

   try
   {
      //************************************************************************
      //************************************************************************
      //************************************************************************
      // Copy variables.

      mForeColor[0] = gVideoParms.mForeColor[0];
      mForeColor[1] = gVideoParms.mForeColor[1];
      mForeColor[2] = gVideoParms.mForeColor[2];
      mForeColor[3] = gVideoParms.mForeColor[3];

      mBackColor[0] = gVideoParms.mBackColor[0];
      mBackColor[1] = gVideoParms.mBackColor[1];
      mBackColor[2] = gVideoParms.mBackColor[2];
      mBackColor[3] = gVideoParms.mBackColor[3];

      //************************************************************************
      //************************************************************************
      //************************************************************************
      // Show SDL info.

      Prn::print(Prn::ThreadRun1, "");
      Prn::print(Prn::ThreadRun1, "VideoDrivers***************************************************");
      int tNumVideoDrivers = SDL_GetNumVideoDrivers();
      Prn::print(Prn::ThreadRun1, "NumVideoDrivers        %1d", tNumVideoDrivers);
      for (int i = 0; i < tNumVideoDrivers; i++)
      {
         Prn::print(Prn::ThreadRun1, "VideoDriver            %s", SDL_GetVideoDriver(i));
      }

      Prn::print(Prn::ThreadRun1, "");
      Prn::print(Prn::ThreadRun1, "VideoDisplays***************************************************");
      int tNumVideoDisplays = SDL_GetNumVideoDisplays();
      Prn::print(Prn::ThreadRun1, "NumVideoDisplays       %1d", tNumVideoDisplays);
      for (int i = 0; i < tNumVideoDisplays; i++)
      {
         showDisplayInfo(i);
      }

      Prn::print(Prn::ThreadRun1, "");
      Prn::print(Prn::ThreadRun1, "RendererDrivers************************************************");
      int tNumRenderDrivers = SDL_GetNumRenderDrivers();
      Prn::print(Prn::ThreadRun1, "NumRenderDrivers       %1d", tNumRenderDrivers);
      for (int i = 0; i < tNumRenderDrivers; i++)
      {
         SDL_GetRenderDriverInfo(i, &mRenderInfo);
         showRenderInfo("RenderDriver", &mRenderInfo);
      }

      Prn::print(Prn::ThreadRun1, "");
      Prn::print(Prn::ThreadRun1, "GL info*********************************************************");
      showGLInfo();

      //************************************************************************
      //************************************************************************
      //************************************************************************
      // Calculate variables.

      int tRet = SDL_GetCurrentDisplayMode(mDisplay, &mDisplayMode);
      mWindowW = mDisplayMode.w;
      mWindowH = mDisplayMode.h;
      mRectW = mDisplayMode.w/8;
      mRectH = mDisplayMode.w/8;

      mRectA.x = mWindowW/4 - mRectW/2;
      mRectA.y = mWindowH/2 - mRectH/2;
      mRectA.w = mRectW;
      mRectA.h = mRectH;

      mRectB.x = (3*mWindowW)/4 - mRectW/2;
      mRectB.y = mWindowH/2 - mRectH/2;
      mRectB.w = mRectW;
      mRectB.h = mRectH;

      //************************************************************************
      //************************************************************************
      //************************************************************************
      // Create window.

      Prn::print(Prn::ThreadRun1, "");
      Prn::print(Prn::ThreadRun1, "CreateWindow***************************************************");
      unsigned int tWindowFlags = 0;
      tWindowFlags |= SDL_WINDOW_SHOWN;
      tWindowFlags |= SDL_WINDOW_BORDERLESS;
      tWindowFlags |= SDL_WINDOW_MAXIMIZED;
      tWindowFlags |= SDL_WINDOW_OPENGL;

      mWindow = SDL_CreateWindow("VideoThread",
         SDL_WINDOWPOS_CENTERED_DISPLAY(mDisplay), SDL_WINDOWPOS_CENTERED_DISPLAY(mDisplay),
         mWindowW, mWindowH, tWindowFlags);
      if (mWindow == 0) throw "SDL_CreateWindow";

      showWindowInfo(mWindow);

      //************************************************************************
      //************************************************************************
      //************************************************************************
      // Create renderer.

      Prn::print(Prn::ThreadRun1, "CreateRenderer*************************************************");

      int tRenderDriverIndex = -1;
      tRenderDriverIndex = 0;
      unsigned int tRenderFlags = 0;
      tRenderFlags |= SDL_RENDERER_ACCELERATED;
      tRenderFlags |= SDL_RENDERER_PRESENTVSYNC;

      mRenderer = SDL_CreateRenderer(mWindow, tRenderDriverIndex, tRenderFlags);
      if (mRenderer == 0) throw "SDL_CreateRenderer";

      // Set renderer to the same size as the window.
      SDL_RenderSetLogicalSize(mRenderer, mWindowW, mWindowH);

      // Show.
      showRendererInfo(mRenderer);

      //************************************************************************
      //************************************************************************
      //************************************************************************
      // Draw the window.

      Prn::print(Prn::ThreadRun1, "DrawWindow*****************************************************");

      // Disable the mouse.
      SDL_ShowCursor(SDL_DISABLE);

      // Set renderer to the background color.
      SDL_SetRenderDrawColor(mRenderer, mBackColor[0], mBackColor[1], mBackColor[2], mBackColor[3]);

      // Clear the window and make it all background color.
      SDL_RenderClear(mRenderer);

      // Render the changes above.
      SDL_RenderPresent(mRenderer);
   }
   catch (const char* aString)
   {
      Prn::print(Prn::ThreadRun1, "EXCEPTION %s", aString, SDL_GetError());
      mValidFlag = false;
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Draw some video.

void VideoThread::doVideoFinish()
{
   Prn::print(Prn::ThreadRun1, "VideoThread::doVideoFinish");

   if (mRenderer) SDL_DestroyRenderer(mRenderer);
   if (mWindow)   SDL_DestroyWindow(mWindow);
   mRenderer = 0;
   mWindow = 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Draw some video.

void VideoThread::doVideoDraw1(SDL_Event* aEvent)
{
   int tRet = 0;
   int aCode = aEvent->user.code;
   Prn::print(Prn::ThreadRun2, "VideoThread::doVideoDraw1 %d", aCode);

   mStartTime = Ris::getCurrentProgramTime();
   try
   {
      //************************************************************************
      //************************************************************************
      //************************************************************************
      // Draw the window.

      // Set renderer to blue.
      tRet = SDL_SetRenderDrawColor(mRenderer, mBackColor[0], mBackColor[1], mBackColor[2], mBackColor[3]);
      if (tRet) throw "SDL_SetRenderDrawColor";

      // Clear the window and make it all blue.
      tRet = SDL_RenderClear(mRenderer);
      if (tRet) throw "SDL_RenderClear";

      // Set renderer to red.
      tRet = SDL_SetRenderDrawColor(mRenderer, mForeColor[0], mForeColor[1], mForeColor[2], mForeColor[3]);
      if (tRet) throw "SDL_SetRenderDrawColor";

      // Render the rectangle.
      SDL_Rect tRect = mRectA;
      if (aCode == 0) tRect = mRectA;
      if (aCode == 1) tRect = mRectB;
      SDL_RenderFillRect(mRenderer, &tRect);

      // Render the changes above.
      SDL_RenderPresent(mRenderer);
   }
   catch (const char* aString)
   {
      Prn::print(Prn::ThreadRun1, "EXCEPTION %s", aString, SDL_GetError());
      mValidFlag = false;
   }

   // Metrics.
   mStopTime = Ris::getCurrentProgramTime();
   // Print the draw latency.
   if (gVideoParms.mShowCode != 0)
   {
      Prn::print(Prn::ThreadRun1, "Latency %6.3f", mStopTime - mStartTime);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Draw some video.

void VideoThread::doVideoDraw2(SDL_Event* aEvent)
{
   // Metrics.
   mStartTime = Ris::getCurrentProgramTime();

   int tRet = 0;
   int tCode = aEvent->user.code;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Image file name.

   char tFilename[200];
   char tBuffer[100];
   if (tCode == 0)
   {
      strcpy(tFilename, Ris::getAlphaFilePath_Image(tBuffer, gVideoParms.mImageFilename0));
   }
   else
   {
      strcpy(tFilename, Ris::getAlphaFilePath_Image(tBuffer, gVideoParms.mImageFilename1));
   }
   Prn::print(Prn::ThreadRun1, "doVideoDraw2 %s", tFilename);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Draw the image.
   try
   {
      // Load the texture from the png file.
      SDL_Texture* tTexture = IMG_LoadTexture(mRenderer, tFilename);
      if (!tTexture) throw "IMG_LoadTexture";

      int tWidth, tHeight;
      SDL_QueryTexture(tTexture, NULL, NULL, &tWidth, &tHeight);
      Prn::print(Prn::ThreadRun1, "LoadTexture %4d %4d", tWidth,tHeight);

      // Render the texture.
      SDL_RenderCopy(mRenderer, tTexture, NULL, NULL);
      SDL_DestroyTexture(tTexture);

      // Display the renderer changes.
      SDL_RenderPresent(mRenderer);
   }
   catch (const char* aString)
   {
      Prn::print(Prn::ThreadRun1, "EXCEPTION %s", aString, SDL_GetError());
      mValidFlag = false;
   }

   // Metrics.
   mStopTime = Ris::getCurrentProgramTime();
   // Print the draw latency.
   if (gVideoParms.mShowCode != 0)
   {
      Prn::print(Prn::ThreadRun1, "Latency %6.3f", mStopTime - mStartTime);
   }
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//name;space