/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "stdafx.h"

#include "SDL.h"
#include "SDL_image.h"
#include "someVideoParms.h"

#define  _SOMEVIDEOTHREAD_CPP_
#include "someVideoThread.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

VideoThread::VideoThread()
{
   // Set member variables.
   mValidFlag = false;

   mDisplay = gVideoParms.mDisplay;
   mWindow = 0;
   mSurface = 0;
   mImage = 0;
   mRenderer = 0;

   mWindowW = gVideoParms.mWindowWidth;
   mWindowH = gVideoParms.mWindowHeight;
   mRectH = 200;
   mRectW = 200;

   mForeColor[0] = 0;
   mForeColor[1] = 0;
   mForeColor[2] = 0;
   mForeColor[3] = 0;

   mBackColor[0] = 0;
   mBackColor[1] = 0;
   mBackColor[2] = 0;
   mBackColor[3] = 0;

   mRectA.x = mWindowW/4 - mRectW/2;
   mRectA.y = mWindowH/2 - mRectH/2;
   mRectA.w = mRectW;
   mRectA.h = mRectH;

   mRectB.x = (3*mWindowW)/4 - mRectW/2;
   mRectB.y = mWindowH/2 - mRectH/2;
   mRectB.w = mRectW;
   mRectB.h = mRectH;

   mDraw1EventType = 0;
   mDraw2EventType = 0;
   mStartTime = 0.0;
   mStopTime = 0.0;
}

VideoThread::~VideoThread()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************

void VideoThread::show()
{
   Prn::print(0, "VideoMsgPort");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Thread init function. This is called by the base class immediately 
// after the thread starts running. It initializes SDL and creates the
// thread SDL window and associated resources.

void VideoThread::threadInitFunction()
{
   int tRet = 0;
   Prn::print(Prn::ThreadInit1, "VideoThread::threadInitFunction");

   // Initialize the video subsystem.
   Prn::print(Prn::ThreadInit1, "SDL_Init");
   tRet = SDL_Init(SDL_INIT_VIDEO);
   if (tRet)
   {
      Prn::print(Prn::ThreadInit1, "ERROR SDL_Init");
      mValidFlag = false;
      return;
   }

   Prn::print(Prn::ThreadInit1, "IMG_Init");
   tRet = IMG_Init(IMG_INIT_PNG);
   if (tRet != IMG_INIT_PNG)
   {
      Prn::print(Prn::ThreadInit1, "ERROR IMG_Init");
      Prn::print(Prn::ThreadInit1, "IMG_Init SDL_GetError  %s\n", SDL_GetError());
      Prn::print(Prn::ThreadInit1, "IMG_GetError  %s\n", IMG_GetError());
      mValidFlag = false;
      return;
   }

   mValidFlag = true;

   // Initialize event types.
   mDraw1EventType = SDL_RegisterEvents(1);
   mDraw2EventType = SDL_RegisterEvents(1);

   // Create the window and renderer.
   doVideoStart();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Thread run function. This is called by the base class immediately 
// after the thread init function. It runs a loop that waits on SDL
// events and processes posted events. The loop exits when it receives
// a quit event.

void VideoThread::threadRunFunction()
{
   Prn::print(Prn::ThreadRun1, "VideoThread::threadRunFunction BEGIN %s", my_string_from_bool(mValidFlag));
   if (!mValidFlag) return;

   // Loop to wait for posted events and process them.
   while (true)
   {
      // Wait for an event.
      SDL_Event tEvent;
      SDL_WaitEvent(&tEvent);
      Prn::print(Prn::ThreadRun3, "event %d", tEvent.type);

      // Exit the loop if a quit event was posted.
      if (tEvent.type == SDL_QUIT) break;
      if (tEvent.type == SDL_MOUSEBUTTONDOWN) break;

      // Draw something if a draw event was posted.
      if (tEvent.type == mDraw1EventType)
      {
         doVideoDraw1(&tEvent);
      }
      if (tEvent.type == mDraw2EventType)
      {
         doVideoDraw2(&tEvent);
      }
   }

   Prn::print(Prn::ThreadRun1, "VideoThread::threadRunFunction END");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Thread exit function. This is called by the base class immediately
// before the thread is terminated. It releases SDL resources and closes
// the thread SDL window.

void VideoThread::threadExitFunction()
{
   Prn::print(Prn::ThreadInit1, "VideoThread::threadExitFunction");

   // Finish the SDL window.
   doVideoFinish();

   // Finalize the video subsystem.
   SDL_Quit();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Thread shutdown function. This posts an SDL quit event that causes
// the thread event loop to exit.

void VideoThread::shutdownThread()
{
   // Post a quit event.
   SDL_Event tEvent;
   SDL_memset(&tEvent, 0, sizeof(tEvent));
   tEvent.type = SDL_QUIT;
   SDL_PushEvent(&tEvent);

   // Wait for the thread to terminate.
   BaseClass::waitForThreadTerminate();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Post an event to draw something.

void VideoThread::postDraw1(int aCode)
{

   // Post the event.
   SDL_Event tEvent;
   SDL_memset(&tEvent, 0, sizeof(tEvent));
   tEvent.type = mDraw1EventType;
   tEvent.user.code = aCode;
   tEvent.user.data1 = 0;
   tEvent.user.data2 = 0;
   SDL_PushEvent(&tEvent);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Post an event to draw something.

void VideoThread::postDraw2(int aCode)
{
   // Post the event.
   SDL_Event tEvent;
   SDL_memset(&tEvent, 0, sizeof(tEvent));
   tEvent.type = mDraw2EventType;
   tEvent.user.code = aCode;
   tEvent.user.data1 = 0;
   tEvent.user.data2 = 0;
   SDL_PushEvent(&tEvent);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace