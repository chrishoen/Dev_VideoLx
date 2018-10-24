#pragma once

/*==============================================================================
Some video thread class.
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "risThreadsThreads.h"
#include "SDL.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
// This is an example SDL2 video thread that creates a window and renderer and
// draws a filled rectangle.
//   
// It creates a window and a renderer and enters a loop that waits for posted
// events. If it receives a draw event then it draws a filled rectangle. If it
// receives a quit event then it exits the loop and the thread terminates.
//
// It inherits from BaseThread to obtain a basic thread functionality.

class VideoThread : public Ris::Threads::BaseThread
{
public:

   typedef Ris::Threads::BaseThread BaseClass;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Members.

   // If true then the thread SDL window was created successfully.
   bool mValidFlag;

   // SDL window resources.
   SDL_Window*      mWindow;
   SDL_Surface*     mSurface;
   SDL_Surface*     mImage;
   SDL_Renderer*    mRenderer;
   SDL_Texture*     mBackground;
   SDL_Texture*     mShape;
   SDL_RendererInfo mRenderInfo;
   SDL_Rect         mRectA;
   SDL_Rect         mRectB;

   // Widths and heights.
   int mWindowW;
   int mWindowH;
   int mRectW;
   int mRectH;

   // Window colors.
   int mForeColor[4];
   int mBackColor[4];

   // Thread window specific event types.
   unsigned int mDraw1EventType;
   unsigned int mDraw2EventType;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Constructor.
   VideoThread();
  ~VideoThread();
  void show();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods. Thread base class overloads.

   // Thread init function. This is called by the base class immediately 
   // after the thread starts running. It initializes SDL and creates the
   // thread SDL window and associated resources.
   void threadInitFunction() override;

   // Thread run function. This is called by the base class immediately 
   // after the thread init function. It runs a loop that waits on SDL
   // events and processes posted events. The loop exits when it receives
   // a quit event.
   void threadRunFunction() override;

   // Thread exit function. This is called by the base class immediately
   // before the thread is terminated. It releases SDL resources and closes
   // the thread SDL window.
   void threadExitFunction() override;

   // Thread shutdown function. This posts an SDL quit event that causes
   // the thread event loop to exit.
   void shutdownThread() override;

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Start and finish the video subsystem.
   void doVideoStart();
   void doVideoFinish();

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods. 

   // Post an event to draw something.
   void postDraw1(int aCode);
   void postDraw2(int aCode);

   // Draw something. This is requested by the posted event.
   void doVideoDraw1(SDL_Event* aEvent);
   void doVideoDraw2(SDL_Event* aEvent);

   //***************************************************************************
   //***************************************************************************
   //***************************************************************************
   // Methods.

   // Utilities.
   void showWindowFlags(SDL_Window* aWindow);
   void showRenderInfo(const char* aLabel, SDL_RendererInfo* aInfo);
   void showDisplayInfo(int tDisplayIndex);
   void showGLInfo();
   void showError();
};

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Global singular instance.

#ifdef _SOMEVIDEOTHREAD_CPP_
         VideoThread* gVideoThread;
#else
extern   VideoThread* gVideoThread;
#endif

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace
