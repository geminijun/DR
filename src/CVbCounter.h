//! Code counter class definition for the Visual Basic language.
/*!
* \file CVbCounter.h
*
* This file contains the code counter class definition for the Visual Basic language.
*/

#ifndef CVbCounter_h
#define CVbCounter_h

#include "CCodeCounter.h"

//! Visual Basic code counter class.
/*!
* \class CVbCounter
*
* Defines the Visual Basic code counter class.
*/
class CVbCounter : public CCodeCounter
{
public:
	CVbCounter();

protected:
  virtual int CountDirectiveSLOC(filemap* fmap, results* result, filemap* fmapBak = NULL);
  virtual int LanguageSpecificProcess(filemap* fmap, results* result, filemap* fmapBak = NULL);
  virtual int CountComplexity(filemap* fmap, results* result);

  StringVector exclude_start_keywords;		//!< SLOC lines excluded from counts starting with keywords
  int ParseFunctionName(string line, string &lastline, stack<string> &functionStack, string &functionName);
};

#endif
