//******************************************************************************
//******************************************************************************
//******************************************************************************

#include "stdafx.h"

#include "risCmdLineFile.h"

#define  _SOMEVIDEOPARMS_CPP_
#include "someVideoParms.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************

namespace Some
{

//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
//******************************************************************************
// Constructor.

VideoParms::VideoParms()
{
   reset();
}

void VideoParms::reset()
{
   BaseClass::reset();
   strcpy(BaseClass::mDefaultFileName, "Video_Parms.txt");

   mWindowWidth = 0;
   mWindowHeight = 0;

   mForeColor[0] = 0;
   mForeColor[1] = 0;
   mForeColor[2] = 0;
   mForeColor[3] = 0;

   mBackColor[0] = 0;
   mBackColor[1] = 0;
   mBackColor[2] = 0;
   mBackColor[3] = 0;

   mImageFilename[0] = 0;
   mSideX = 0;
   mSideY = 0;
   mTimerThreadPeriod = 0;
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Show.

void VideoParms::show()
{
   printf("\n");
   printf("VideoParms************************************************ %s\n", mTargetSection);

   printf("\n");
   printf("WindowWidthHeight     %-4d %4d\n", mWindowWidth, mWindowHeight);

   printf("\n");
   printf("ForeColor             %-4d %4d %4d %4d\n", mForeColor[0], mForeColor[1], mForeColor[2], mForeColor[3]);
   printf("BackColor             %-4d %4d %4d %4d\n", mBackColor[0], mBackColor[1], mBackColor[2], mBackColor[3]);

   printf("\n");
   printf("ImageFilename         %-10s\n", mImageFilename);

   printf("\n");
   printf("SideX                 %-4d\n", mSideX);
   printf("sideY                 %-4d\n", mSideY);
   printf("\n");
   printf("TmerThreadPeriod      %-4d\n", mTimerThreadPeriod);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Base class override: Execute a command from the command file to set a 
// member variable.  Only process commands for the target section.This is
// called by the associated command file object for each command in the file.

void VideoParms::execute(Ris::CmdLineCmd* aCmd)
{
   if (!isTargetSection(aCmd)) return;

   if (aCmd->isCmd("WindowWidthHeight"))
   {
      mWindowWidth = aCmd->argInt(1);
      mWindowHeight = aCmd->argInt(2);
   }

   if (aCmd->isCmd("ForeColor"))
   {
      mForeColor[0] = aCmd->argInt(1);
      mForeColor[1] = aCmd->argInt(2);
      mForeColor[2] = aCmd->argInt(3);
      mForeColor[3] = aCmd->argInt(4);
   }

   if (aCmd->isCmd("BackColor"))
   {
      mBackColor[0] = aCmd->argInt(1);
      mBackColor[1] = aCmd->argInt(2);
      mBackColor[2] = aCmd->argInt(3);
      mBackColor[3] = aCmd->argInt(4);
   }

   if (aCmd->isCmd("ImageFilename"))  aCmd->copyArgString(1, mImageFilename, cMaxStringSize);

   if (aCmd->isCmd("SideX"))        mSideX = aCmd->argInt(1);
   if (aCmd->isCmd("SideY"))        mSideY = aCmd->argInt(1);

   if (aCmd->isCmd("TimerThreadPeriod"))  mTimerThreadPeriod = aCmd->argInt(1);
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Calculate expanded member variables. This is called after the entire
// section of the command file has been processed.

void VideoParms::expand()
{
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
}//namespace