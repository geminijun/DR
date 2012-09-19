//! Main class containing results.
/*!
* \file cc_main.h
*
* This file contains the main class definition containing results.
*/

#ifndef cc_main_h
#define cc_main_h

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <utility>
#include <map>
#include <stack>
#include <algorithm>
using namespace std;

#define PRODUCT_REVISION "2011.10B"

#define PHY		0
#define LOG		1
#define CODE	0
#define DATA	1

#define MAX_LINE_LENGTH		  10485760

#define UNKNOWN				  0		// Unknown file type
#define DATAFILE			  1		// Data file type
#define WEB					  2		// WebCounter
#define	ADA					  3		// ADA
#define BASH				  4		// Bash
#define CSH					  5		// C-Shell
#define C_CPP				  6		// C/C++
#define CSHARP				  7		// C#
#define CSHARP_HTML			  8		// C# in HTML
#define CSHARP_XML			  9		// C# in XML
#define CSHARP_ASP_S		  10	// C# server side in ASP
#define COLDFUSION			  11	// ColdFusion
#define CFSCRIPT			  12	// ColdFusion CFScript
#define	CSS				      13	// CSS
#define	FORTRAN				  14	// Fortran
#define	HTML				  15	// HTML
#define	HTML_PHP			  16	// HTML in PHP
#define	HTML_JSP			  17	// HTML in JSP
#define	HTML_ASP			  18	// HTML in ASP
#define	HTML_CFM			  19    // HTML in ColdFusion
#define JAVA				  20	// Java
#define JAVA_JSP			  21	// Java	in JSP
#define	JAVASCRIPT			  22	// JavaScript
#define	JAVASCRIPT_HTML		  23	// JavaScript in HTML
#define	JAVASCRIPT_XML		  24	// JavaScript in XML
#define	JAVASCRIPT_PHP		  25	// JavaScript in PHP
#define	JAVASCRIPT_JSP		  26	// JavaScript in JSP
#define	JAVASCRIPT_ASP_S	  27	// JavaScript server side in ASP
#define	JAVASCRIPT_ASP_C	  28	// JavaScript client side in ASP
#define	JAVASCRIPT_CFM		  29    // Javascript in ColdFusion
#define	NEXTMIDAS			  30	// NeXtMidas
#define	XMIDAS				  31	// X-Midas
#define PASCAL				  32	// Pascal
#define	PERL				  33	// Perl
#define	PHP					  34	// PHP
#define	PYTHON				  35	// Python
#define RUBY				  36	// Ruby
#define	SQL					  37	// SQL
#define	SQL_CFM				  38	// SQL in ColdFusion
#define VB					  39	// Visual Basic
#define VBSCRIPT			  40	// VBScript
#define VBS_HTML			  41	// VBScript in HTML
#define VBS_XML				  42	// VBScript in XML
#define VBS_PHP				  43	// VBScript in PHP
#define VBS_JSP				  44	// VBScript in JSP
#define VBS_ASP_S			  45	// VBScript server side in ASP
#define VBS_ASP_C			  46	// VBScript client side in ASP
#define VBS_CFM				  47    // VBScript in ColdFusion
#define XML					  48	// XML

#define EMBEDDED_FILE_PREFIX  "*.*" // the text prepended to the temp file created for embedded code
#define DEF_LANG_NAME		  "UNDEF"

#define INPUT_FILE_LIST_OLD   "filelist.dat"
#define INPUT_FILE_LIST_NAME  "fileList.txt"
#define OUTPUT_FILE_NAME      "_outfile.txt"
#define OUTPUT_FILE_NAME_CSV  "_outfile.csv"
#define OUTPUT_FILE_CPLX	  "outfile_cplx.txt"
#define OUTPUT_FILE_CPLX_CSV  "outfile_cplx.csv"
#define OUTPUT_FILE_SUM	      "outfile_summary.txt"
#define OUTPUT_FILE_SUM_CSV   "outfile_summary.csv"
#define LOG_FILENAME		  "log.txt"

///////////////////////////////////////////////////////
// For WebCounter Only
///////////////////////////////////////////////////////

#define	WEB_PHP_START		0
#define	WEB_PHP_END			1
#define	WEB_SCRIPT_START	2
#define	WEB_SCRIPT_END		3
#define	WEB_ASP_JSP_START	4
#define	WEB_ASP_JSP_END		5
#define	WEB_PHP_START2		6
#define	WEB_CFM_START		7
#define	WEB_CFM_END			8

///////////////////////////////////////////////////////
// General Data Structures
///////////////////////////////////////////////////////

//! Structure to contain a physical line of code.
/*!
* \struct lineElement
*
* Defines a structure to contain a physical line of code.
*/
struct lineElement
{
	lineElement(unsigned int num, string str)
	{
		lineNumber = num;
		line = str;
	}
	lineElement()
	{
		lineNumber = 0;
		line = "";
	}
	unsigned int lineNumber;	//!< Line number
	string line;				//!< Line text
};

//! Vector containing all physical line elements in a file.
/*!
* \typedef filemap
*
* Defines a vector containing all physical line elements in a file.
*/
typedef vector<lineElement> filemap;

//! Map containing all logical lines in a file.
/*!
* \typedef srcLineVector
*
* Defines a map containing all logical lines in a file for differencing.
*/
typedef map<string, unsigned int> srcLineVector;

//! Vector containing a list of strings.
/*!
* \typedef StringVector
*
* Defines a vector containing a list of strings.
*/
typedef vector<string> StringVector;

//! Vector containing a list of unsigned integers.
/*!
* \typedef UIntVector
*
* Defines a vector containing a list of unsigned integers.
*/
typedef vector<unsigned int> UIntVector;

//! Pair of unsigned integers.
/*!
* \typedef UIntPair
*
* Defines a pair of unsigned integers.
*/
typedef pair<unsigned int, unsigned int> UIntPair;

//! Vector containing a list of unsigned integer pairs.
/*!
* \typedef UIntPairVector
*
* Defines a vector containing a list of unsigned integer pairs.
*/
typedef vector<UIntPair> UIntPairVector;

//! Class to hold results for each file.
/*!
* \class results
*
* Defines a class to hold file results.
*/
class results
{
public:
	results() { reset(); }
	results& operator= (const results&);
	void reset();
	void clearSLOC();
	bool addSLOC(const string &line, bool &trunc_flag);

	string error_code;					//!< Error string
	unsigned int blank_lines;			//!< # of blank lines
	unsigned int comment_lines;			//!< # of whole line comment lines
	unsigned int e_comm_lines;			//!< # of embedded comment lines
	unsigned int directive_lines[2];	//!< # of compiler directive lines
	unsigned int data_lines[2];			//!< # of data declaration lines
	unsigned int exec_lines[2];			//!< # of executable lines
	unsigned int SLOC_lines[2];			//!< # of SLOC lines
	unsigned int total_lines;			//!< # of total lines
	unsigned int cmplx_math_lines;		//!< # of math function call lines
	unsigned int cmplx_trig_lines;		//!< # of trig function call lines
	unsigned int cmplx_logarithm_lines;	//!< # of logarithm function call lines
	unsigned int cmplx_calc_lines;		//!< # of calculations
	unsigned int cmplx_cond_lines;		//!< # of conditionals
	unsigned int cmplx_logic_lines;		//!< # of logical operations
	unsigned int cmplx_preproc_lines;	//!< # of preprocessor directive lines for complexity
	unsigned int cmplx_assign_lines;	//!< # of assignments
	unsigned int cmplx_pointer_lines;	//!< # of pointers
	unsigned int trunc_lines;			//!< # of truncated logical lines
	bool   e_flag;						//!< Set to true if error occurs during processing
	string file_name;					//!< File name
	int    file_type;					//!< File type (DATA, CODE)
	unsigned int class_type;			//!< File class type
	size_t lsloc_truncate;				//!< # of characters allowed in LSLOC for differencing (0=no truncation)

	UIntVector directive_count;			//!< Count of each directive statement keyword
	UIntVector data_name_count;			//!< Count of each data statement keyword
	UIntVector exec_name_count;			//!< Count of each executable statement keyword

	UIntVector math_func_count;			//!< Count of math functions
	UIntVector trig_func_count;			//!< Count of trigonometric functions
	UIntVector log_func_count;			//!< Count of logarithmic functions
	UIntVector cmplx_calc_count;		//!< Count of calculations
	UIntVector cmplx_cond_count;		//!< Count of conditionals
	UIntVector cmplx_logic_count;		//!< Count of logicals
	UIntVector cmplx_preproc_count;		//!< Count of preprocessor directives
	UIntVector cmplx_assign_count;		//!< Count of assignments
	UIntVector cmplx_pointer_count;		//!< Count of pointers
	UIntVector cmplx_nestloop_count;	//!< Count of nested loop levels

	// differencing
	bool firstDuplicate;				//!< Is this file the first (source) duplicate? (printed in main counting file)
	bool duplicate;						//!< Is this file a duplicate? (printed in Duplicates counting file)
	bool matched;						//!< Has matching file been found for differencing?
	srcLineVector mySLOCLines;			//!< Contains the actual logical lines of code for differencing
};

//! Pair containing a filemap and a results set.
/*!
* \typedef SourceFileElement
*
* Defines a pair containing a filemap and a results set.
*/
typedef pair<filemap, results> SourceFileElement;

#endif
