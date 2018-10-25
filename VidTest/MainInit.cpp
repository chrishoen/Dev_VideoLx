
#include "stdafx.h"

#include "risThreadsProcess.h"

#include "someVideoParms.h"

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Initialize.

void main_initialize(int argc,char** argv)
{
   // Enter process.
   Ris::Threads::enterProcessHigh();

   // Initialize print facility.
   Prn::resetPrint();
// Prn::useConsole(1);
   Prn::initializePrint();

   // Initialize print filters.
   Prn::setFilter(Prn::ThreadInit1,     true);
   Prn::setFilter(Prn::ThreadInit1,     true);
   Prn::setFilter(Prn::ThreadRun1,      true);
   Prn::setFilter(Prn::ThreadRun2,      false);
   Prn::setFilter(Prn::ThreadRun3,      false);
   Prn::setFilter(Prn::ThreadRun4,      false);

   Prn::setFilter(Prn::View01,          true);
   Prn::setFilter(Prn::View02,          true);
   Prn::setFilter(Prn::View11,          true,  1);
   Prn::setFilter(Prn::View12,          true,  1);
   Prn::setFilter(Prn::View21,          false, 2);
   Prn::setFilter(Prn::View21,          false, 2);

   // Read parameters files.
   Some::gVideoParms.reset();
   Some::gVideoParms.readSection("default");

   // Done.
   Prn::print(0, "VThread Program**********************************************BEGIN");
   Prn::print(0, "VThread Program**********************************************BEGIN");
   Prn::print(0, "VThread Program**********************************************BEGIN");
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
// Finalize.

void main_finalize()
{
   Prn::print(0, "VThread Program**********************************************END");

   // Close print facility.
   Prn::finalizePrint();

   // Exit process.
   Ris::Threads::exitProcess();
}

//******************************************************************************
//******************************************************************************
//******************************************************************************
