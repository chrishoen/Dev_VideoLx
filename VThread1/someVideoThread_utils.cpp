/*==============================================================================
==============================================================================*/

//******************************************************************************
//******************************************************************************
//******************************************************************************
#include "stdafx.h"


#include "SDL.h"

#include "someVideoThread.h"

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************

void VideoThread::showWindowFlags(SDL_Window* aWindow)
{
   unsigned int tFlags = SDL_GetWindowFlags(aWindow);
   char tString[100] = "";
   if (tFlags & SDL_WINDOW_SHOWN)      strcat(tString, "shown ");
   if (tFlags & SDL_WINDOW_HIDDEN)     strcat(tString, "hidden ");
   if (tFlags & SDL_WINDOW_FULLSCREEN) strcat(tString, "fullscreen ");
   if (tFlags & SDL_WINDOW_OPENGL)     strcat(tString, "opengl ");

   Prn::print(Prn::ThreadRun1,"WindowFlags %8X  %s", tFlags, tString);
}

void VideoThread::showRenderInfo(const char* aLabel, SDL_RendererInfo* aInfo)
{

   char tString[100] = "";
   if (aInfo->flags & SDL_RENDERER_SOFTWARE)      strcat(tString, "software ");
   if (aInfo->flags & SDL_RENDERER_ACCELERATED)   strcat(tString, "accelerated ");
   if (aInfo->flags & SDL_RENDERER_PRESENTVSYNC)  strcat(tString, "presentvsync ");
   if (aInfo->flags & SDL_RENDERER_TARGETTEXTURE) strcat(tString, "targettexture ");

   Prn::print(Prn::ThreadRun1, "RenderInfo  %-16s %-10s %5X %s", aLabel, aInfo->name, aInfo->flags, tString);
}

void VideoThread::showDisplayInfo(int tDisplayIndex)
{
   SDL_DisplayMode  tDisplayMode;
   int tRet = SDL_GetCurrentDisplayMode(0, &tDisplayMode);
   if (tRet) throw "SDL_GetCurrentDisplayMode";

   Prn::print(Prn::ThreadRun1, "Display wh             %5d %5d", tDisplayMode.w, tDisplayMode.h);
   Prn::print(Prn::ThreadRun1, "Display refresh rate   %5d", tDisplayMode.refresh_rate);
}

void VideoThread::showError()
{
   Prn::print(Prn::ThreadRun1, "ERROR %s", SDL_GetError());
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace