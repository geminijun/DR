//! Main counting object class methods.
/*!
* \file MainObject.cpp
*
* This file contains the main counting object class methods.
*/

#include "MainObject.h"
#include "CUtil.h"
#include "CmpMngr.h"
#include <sstream>

/*!
* Constructs a MainObject object.
*/
MainObject::MainObject()
{
	counter = 0;

	isDiff = false;					// default not differencing files
	outDir = "";					// default output directory is current directory
	duplicate_threshold = 0;		// default duplicate files threshold
	lsloc_truncate = 10000;			// default LSLOC maximum characters for truncation (0=no truncation)
	print_cmplx = true;				// default print complexity and keyword counts
	print_cyclomatic_cmplx = false;	// default don't print cyclomatic complexity
	print_csv = true;				// default print CSV report files
	print_ascii = false;			// default don't print ASCII text report files
	print_legacy = false;			// default don't print legacy ASCII text report files
	print_unified = false;			// default don't print all counting files to a single unified file
	clearCaseFile = false;			// default don't process Clear Case file names
	followSymLinks = true;			// default follow symbolic links
	use_CommandLine = false;		// default read all files from fileList file

	CCodeCounter* tmp;

	tmp = new CCodeCounter;
	CounterForEachLanguage.insert(map<int, CCodeCounter*>::value_type(UNKNOWN		,tmp));

	tmp = new CDataCounter;
	CounterForEachLanguage.insert(map<int, CCodeCounter*>::value_type(DATAFILE		,tmp));

	tmp = new CWebCounter;
	CounterForEachLanguage.insert(map<int, CCodeCounter*>::value_type(WEB			,tmp));

	tmp = new CAdaCounter;
	CounterForEachLanguage.insert(map<int, CCodeCounter*>::value_type(ADA			,tmp));

	tmp = new CBashCounter;
	CounterForEachLanguage.insert(map<int, CCodeCounter*>::value_type(BASH			,tmp));

	tmp = new CCshCounter;
	CounterForEachLanguage.insert(map<int, CCodeCounter*>::value_type(CSH			,tmp));

	tmp = new CCCounter;
	CounterForEachLanguage.insert(map<int, CCodeCounter*>::value_type(C_CPP			,tmp));

	tmp = new CCsharpCounter;
	CounterForEachLanguage.insert(map<int, CCodeCounter*>::value_type(CSHARP		,tmp));

	tmp = new CCsharpHtmlCounter;
	CounterForEachLanguage.insert(map<int, CCodeCounter*>::value_type(CSHARP_HTML	,tmp));

	tmp = new CCsharpXmlCounter;
	CounterForEachLanguage.insert(map<int, CCodeCounter*>::value_type(CSHARP_XML	,tmp));

	tmp = new CCsharpAspCounter;
	CounterForEachLanguage.insert(map<int, CCodeCounter*>::value_type(CSHARP_ASP_S	,tmp));

	tmp = new CColdFusionCounter;
	CounterForEachLanguage.insert(map<int, CCodeCounter*>::value_type(COLDFUSION	,tmp));

	tmp = new CCFScriptCounter;
	CounterForEachLanguage.insert(map<int, CCodeCounter*>::value_type(CFSCRIPT		,tmp));

	tmp = new CCssCounter;
	CounterForEachLanguage.insert(map<int, CCodeCounter*>::value_type(CSS			,tmp));

	tmp = new CFortranCounter;
	CounterForEachLanguage.insert(map<int, CCodeCounter*>::value_type(FORTRAN		,tmp));

	tmp = new CHtmlCounter;
	CounterForEachLanguage.insert(map<int, CCodeCounter*>::value_type(HTML			,tmp));

	tmp = new CHtmlPhpCounter;
	CounterForEachLanguage.insert(map<int, CCodeCounter*>::value_type(HTML_PHP		,tmp));

	tmp = new CHtmlJspCounter;
	CounterForEachLanguage.insert(map<int, CCodeCounter*>::value_type(HTML_JSP		,tmp));

	tmp = new CHtmlAspCounter;
	CounterForEachLanguage.insert(map<int, CCodeCounter*>::value_type(HTML_ASP		,tmp));

	tmp = new CHtmlColdFusionCounter;
	CounterForEachLanguage.insert(map<int, CCodeCounter*>::value_type(HTML_CFM		,tmp));

	tmp = new CJavaCounter;
	CounterForEachLanguage.insert(map<int, CCodeCounter*>::value_type(JAVA			,tmp));

	tmp = new CJavaJspCounter;
	CounterForEachLanguage.insert(map<int, CCodeCounter*>::value_type(JAVA_JSP		,tmp));

	tmp = new CJavascriptCounter;
	CounterForEachLanguage.insert(map<int, CCodeCounter*>::value_type(JAVASCRIPT	,tmp));

	tmp = new CJavascriptHtmlCounter;
	CounterForEachLanguage.insert(map<int, CCodeCounter*>::value_type(JAVASCRIPT_HTML,tmp));

	tmp = new CJavascriptXmlCounter;
	CounterForEachLanguage.insert(map<int, CCodeCounter*>::value_type(JAVASCRIPT_XML,tmp));

	tmp = new CJavascriptPhpCounter;
	CounterForEachLanguage.insert(map<int, CCodeCounter*>::value_type(JAVASCRIPT_PHP,tmp));

	tmp = new CJavascriptJspCounter;
	CounterForEachLanguage.insert(map<int, CCodeCounter*>::value_type(JAVASCRIPT_JSP,tmp));

	tmp = new CJavascriptAspServerCounter;
	CounterForEachLanguage.insert(map<int, CCodeCounter*>::value_type(JAVASCRIPT_ASP_S,tmp));

	tmp = new CJavascriptAspClientCounter;
	CounterForEachLanguage.insert(map<int, CCodeCounter*>::value_type(JAVASCRIPT_ASP_C,tmp));

	tmp = new CJavascriptColdFusionCounter;
	CounterForEachLanguage.insert(map<int, CCodeCounter*>::value_type(JAVASCRIPT_CFM,tmp));

	tmp = new CNeXtMidasCounter;
	CounterForEachLanguage.insert(map<int, CCodeCounter*>::value_type(NEXTMIDAS		,tmp));

	tmp = new CXMidasCounter;
	CounterForEachLanguage.insert(map<int, CCodeCounter*>::value_type(XMIDAS		,tmp));

	tmp = new CPascalCounter;
	CounterForEachLanguage.insert(map<int, CCodeCounter*>::value_type(PASCAL		,tmp));

	tmp = new CPerlCounter;
	CounterForEachLanguage.insert(map<int, CCodeCounter*>::value_type(PERL			,tmp));

	tmp = new CPhpCounter;
	CounterForEachLanguage.insert(map<int, CCodeCounter*>::value_type(PHP			,tmp));

	tmp = new CPythonCounter;
	CounterForEachLanguage.insert(map<int, CCodeCounter*>::value_type(PYTHON		,tmp));

	tmp = new CRubyCounter;
	CounterForEachLanguage.insert(map<int, CCodeCounter*>::value_type(RUBY			,tmp));

	tmp = new CSqlCounter;
	CounterForEachLanguage.insert(map<int, CCodeCounter*>::value_type(SQL			,tmp));

	tmp = new CSqlColdFusionCounter;
	CounterForEachLanguage.insert(map<int, CCodeCounter*>::value_type(SQL_CFM		,tmp));

	tmp = new CVbCounter;
	CounterForEachLanguage.insert(map<int, CCodeCounter*>::value_type(VB			,tmp));

	tmp = new CVbscriptCounter;
	CounterForEachLanguage.insert(map<int, CCodeCounter*>::value_type(VBSCRIPT		,tmp));

	tmp = new CVbsHtmlCounter;
	CounterForEachLanguage.insert(map<int, CCodeCounter*>::value_type(VBS_HTML		,tmp));

	tmp = new CVbsXmlCounter;
	CounterForEachLanguage.insert(map<int, CCodeCounter*>::value_type(VBS_XML		,tmp));

	tmp = new CVbsPhpCounter;
	CounterForEachLanguage.insert(map<int, CCodeCounter*>::value_type(VBS_PHP		,tmp));

	tmp = new CVbsJspCounter;
	CounterForEachLanguage.insert(map<int, CCodeCounter*>::value_type(VBS_JSP		,tmp));

	tmp = new CVbsAspServerCounter;
	CounterForEachLanguage.insert(map<int, CCodeCounter*>::value_type(VBS_ASP_S		,tmp));

	tmp = new CVbsAspClientCounter;
	CounterForEachLanguage.insert(map<int, CCodeCounter*>::value_type(VBS_ASP_C		,tmp));

	tmp = new CVbsColdFusionCounter;
	CounterForEachLanguage.insert(map<int, CCodeCounter*>::value_type(VBS_CFM		,tmp));

	tmp = new CXmlCounter;
	CounterForEachLanguage.insert(map<int, CCodeCounter*>::value_type(XML			,tmp));

	// initialize the count lists
	ResetCounterCounts();
}

/*!
* Destroys a MainObject object.
*/
MainObject::~MainObject()
{
	for (map<int, CCodeCounter*>::iterator iter = CounterForEachLanguage.begin(); iter != CounterForEachLanguage.end(); iter++)
	{
		delete iter->second;
		iter->second = 0;
	}
}

/*!
* Resets all count lists (e.g., directive_count, data_name_count, etc.).
*/
void MainObject::ResetCounterCounts()
{
	for (map<int, CCodeCounter*>::iterator iter = CounterForEachLanguage.begin(); iter != CounterForEachLanguage.end(); iter++)
		iter->second->InitializeCounts();
}

/*!
* Updates count lists (e.g., directive_count, data_name_count, etc.) based on file counts.
*
* \param useListA use file list A? (otherwise use list B)
*/
void MainObject::UpdateCounterCounts(bool useListA)
{
	int i;
	unsigned int class_type;
	WebType webType;
	SourceFileList::iterator its;
	SourceFileList* mySourceFile = (useListA) ? &SourceFileA : &SourceFileB;
	StringVector::iterator icnts, icnte;
	UIntPairVector::iterator icntc;
	UIntVector::iterator icnt;
	CCodeCounter* counter;
	CWebCounter* webCounter;

	ResetCounterCounts();

	for (its = mySourceFile->begin(); its != mySourceFile->end(); its++)
	{
		class_type = its->second.class_type;
		counter = CounterForEachLanguage[class_type];
		for (i = 0; i < 12; i++)
		{
			switch (i)
			{
			case 0:
				icnts = counter->directive.begin();
				icnte = counter->directive.end();
				icntc = counter->directive_count.begin();
				icnt = its->second.directive_count.begin();
				break;
			case 1:
				icnts = counter->data_name_list.begin();
				icnte = counter->data_name_list.end();
				icntc = counter->data_name_count.begin();
				icnt = its->second.data_name_count.begin();
				break;
			case 2:
				icnts = counter->exec_name_list.begin();
				icnte = counter->exec_name_list.end();
				icntc = counter->exec_name_count.begin();
				icnt = its->second.exec_name_count.begin();
				break;
			case 3:
				icnts = counter->math_func_list.begin();
				icnte = counter->math_func_list.end();
				icntc = counter->math_func_count.begin();
				icnt = its->second.math_func_count.begin();
				break;
			case 4:
				icnts = counter->trig_func_list.begin();
				icnte = counter->trig_func_list.end();
				icntc = counter->trig_func_count.begin();
				icnt = its->second.trig_func_count.begin();
				break;
			case 5:
				icnts = counter->log_func_list.begin();
				icnte = counter->log_func_list.end();
				icntc = counter->log_func_count.begin();
				icnt = its->second.log_func_count.begin();
				break;
			case 6:
				icnts = counter->cmplx_calc_list.begin();
				icnte = counter->cmplx_calc_list.end();
				icntc = counter->cmplx_calc_count.begin();
				icnt = its->second.cmplx_calc_count.begin();
				break;
			case 7:
				icnts = counter->cmplx_cond_list.begin();
				icnte = counter->cmplx_cond_list.end();
				icntc = counter->cmplx_cond_count.begin();
				icnt = its->second.cmplx_cond_count.begin();
				break;
			case 8:
				icnts = counter->cmplx_logic_list.begin();
				icnte = counter->cmplx_logic_list.end();
				icntc = counter->cmplx_logic_count.begin();
				icnt = its->second.cmplx_logic_count.begin();
				break;
			case 9:
				icnts = counter->cmplx_preproc_list.begin();
				icnte = counter->cmplx_preproc_list.end();
				icntc = counter->cmplx_preproc_count.begin();
				icnt = its->second.cmplx_preproc_count.begin();
				break;
			case 10:
				icnts = counter->cmplx_assign_list.begin();
				icnte = counter->cmplx_assign_list.end();
				icntc = counter->cmplx_assign_count.begin();
				icnt = its->second.cmplx_assign_count.begin();
				break;
			case 11:
				icnts = counter->cmplx_pointer_list.begin();
				icnte = counter->cmplx_pointer_list.end();
				icntc = counter->cmplx_pointer_count.begin();
				icnt = its->second.cmplx_pointer_count.begin();
				break;
			}
			while (icnts != icnte)
			{
				if (its->second.duplicate)
					(*icntc).second += (*icnt);
				else
					(*icntc).first += (*icnt);
				icnts++;
				icnt++;
				icntc++;
			}
		}
		if (its->second.duplicate)
		{
			counter->counted_dupFiles++;

			if (useListA)
				counter->total_dupFilesA++;
			else
				counter->total_dupFilesB++;

			if (class_type == WEB)
			{
				// get web file class
				webCounter = (CWebCounter *)counter;
				webType = webCounter->GetWebType(its->second.file_name);
				if (webType == WEB_PHP)
				{
					if (useListA)
						webCounter->total_php_dupFilesA++;
					else
						webCounter->total_php_dupFilesB++;
				}
				else if (webType == WEB_ASP)
				{
					if (useListA)
						webCounter->total_asp_dupFilesA++;
					else
						webCounter->total_asp_dupFilesB++;
				}
				else if (webType == WEB_JSP)
				{
					if (useListA)
						webCounter->total_jsp_dupFilesA++;
					else
						webCounter->total_jsp_dupFilesB++;
				}
				else if (webType == WEB_XML)
				{
					if (useListA)
						webCounter->total_xml_dupFilesA++;
					else
						webCounter->total_xml_dupFilesB++;
				}
				else if (webType == WEB_CFM)
				{
					if (useListA)
						webCounter->total_cfm_dupFilesA++;
					else
						webCounter->total_cfm_dupFilesB++;
				}
				else
				{
					if (useListA)
						webCounter->total_htm_dupFilesA++;
					else
						webCounter->total_htm_dupFilesB++;
				}
			}
		}
		else
			counter->counted_files++;
	}
}

/*!
* Main counting process.
*
* \param argc number of arguments
* \param argv argument list
*
* \return function status
*/
int MainObject::MainProcess(int argc, char *argv[])
{
	/*
		Counting Process:
		1. Parse options
		2. Read input files
		3. Run counter on baseline files
		4. Identify duplicate files
		5. Print all results data
	*/

	vector<string> listFileNames;
	BaselineFileName1 = INPUT_FILE_LIST_NAME;

	// parse the command line input
	if (!ParseCommandLine(argc, argv))
		ShowUsage();

	// generate user-defined language extension map
	if (userExtMapFile.length() != 0)
		ReadUserExtMapping(userExtMapFile);

	// read the source files
	if (listFilesToBeSearched.size() != 0)
		CUtil::ListAllFiles(dirnameA, listFilesToBeSearched, listFileNames, followSymLinks);
	
	cout << "Reading source files..."; 
	if (!ReadAllFiles(listFileNames, BaselineFileName1))
		return 0;
	cout << ".......................DONE" << endl;

	// count files
	cout << "Performing files analysis and counting...";
	ProcessSourceList();
	if (duplicate_threshold >= 0.0)
		FindDuplicateFiles(SourceFileA, duplicateFilesInA1, duplicateFilesInA2);
	UpdateCounterCounts();

	// print the counting results (SLOC counts and complexity counts)
	cout << "Generating results to files...";
	if (print_unified)
		PrintTotalCountResults(true, "", &duplicateFilesInA2);
	else
		PrintCountResults(true, "", &duplicateFilesInA2);

	if (print_cmplx)
		PrintComplexityResults();

	if (duplicate_threshold >= 0.0)
	{
		if (print_unified)
			PrintTotalCountResults(true, "Duplicates-", &duplicateFilesInA2, false);
		else
			PrintCountResults(true, "Duplicates-", &duplicateFilesInA2, false);
		if (print_cmplx)
			PrintComplexityResults(true, "Duplicates-", true);
		PrintDuplicateSummary();
	}
	cout << "................DONE" << endl;

	return 1;
}

/*!
* Parses the command line arguments.
*
* \param argc number of arguments
* \param argv argument list
*
* \return method status
*/
int MainObject::ParseCommandLine(int argc, char *argv[])
{
	int i;
	string arg, cmdStr;

	// capture command line and strip executable path
	arg = argv[0];
	cmdStr = CUtil::ExtractFilename(arg);
	for (i = 1; i < argc; i++)
	{
		arg = argv[i];
		cmdStr += " " + arg;
	}
	cmdLine = cmdStr;

	for (i = 1; i < argc; i++)
	{
		arg = argv[i];

		if (arg == "-v")
		{
			cout << "UCC version " << PRODUCT_REVISION << endl;
			exit(0);
		}
		else if (arg == "-dir")
		{
			// read the two baseline directory names and the extract the names
			// of the file extensions to be searched
			if ((isDiff && i + 3 > argc) || (!isDiff && i + 2 > argc))
			{
				string err = "Error: Unable to parse command line args";
				cout << err << endl;
				CUtil::AddError(err);
				return 0;
			}

			// extract the directory names for BaselineA and BaselineB (if applicable)
			use_CommandLine = true;
			i++;
			dirnameA = argv[i];
			i++;
			if (isDiff)
			{
				dirnameB = argv[i];
				i++;
			}

			// extract the names of the all file extensions to be searched
			for (; i < argc; i++)
			{
				// command line arguments can be mentioned in any sequence
				// search until you do not come across the end of arguments or
				// another command line argument
				arg = argv[i];
				if (arg.find_first_of('-') == 0)	// '-' indicates a new argument
					break;
				else
					listFilesToBeSearched.push_back(arg);
			}
			if (listFilesToBeSearched.size() == 0)
			{
				// add all files as the default
				listFilesToBeSearched.push_back("*.*");
			}
		}

		// Return from the loop if all arguments have been processed.
		if (i == argc)
			return 1;

		if (arg == "-i1")
		{
			// extract the BaselineA file
			if (i + 1 > argc)
			{
				string err = "Error: Unable to parse command line args";
				cout << err << endl;
				CUtil::AddError(err);
				return 0;
			}
			i++;

			ifstream infile;
			infile.open(argv[i], ifstream::in);
			infile.close();
			if (infile.fail())
			{
				// file did not exist
				string err = "Error: Unable to open baseline file (";
				err += argv[i];
				err += ")";
				cout << err << endl;
				CUtil::AddError(err);
				return 0;
			}
			BaselineFileName1 = string(argv[i]);
		}
		else if (arg == "-i2" && isDiff)
		{
			// extract the BaselineB file
			if (i + 1 > argc)
			{
				string err = "Error: Unable to parse command line args";
				cout << err << endl;
				CUtil::AddError(err);
				return 0;
			}
			i++;

			ifstream infile;
			infile.open(argv[i], ifstream::in);
			infile.close();
			if (infile.fail())
			{
				// file did not exist
				string err = "Error: Unable to open baseline file (";
				err += argv[i];
				err += ")";
				cout << err << endl;
				CUtil::AddError(err);
				return 0;
			}
			BaselineFileName2 = string(argv[i]);
		}
		else if (arg == "-outdir")
		{
			// extract the output directory name
			if (i + 1 > argc)
			{
				string err = "Error: Unable to parse command line args";
				cout << err << endl;
				CUtil::AddError(err);
				return 0;
			}
			i++;
			outDir = argv[i];

			// attempt to create the specified directory (if exists, this will do nothing)
#ifdef UNIX
			// trim trailing '/' character
			if (outDir.length() > 1 && outDir[outDir.length()-1] == '/')
				outDir = outDir.substr(0, outDir.length() - 1);
#else
			// trim trailing '\' or '/' character
			if (outDir.length() > 1 && (outDir[outDir.length()-1] == '\\' || outDir[outDir.length()-1] == '/'))
				outDir = outDir.substr(0, outDir.length() - 1);
#endif
			if (CUtil::MkPath(outDir) == 0)
			{
				string err = "Error: Unable to create output directory (";
				err += outDir;
				err += ")";
				cout << err << endl;
				CUtil::AddError(err);
				return 0;
			}
			
			// add trailing slash and initialize the error log file path
#ifdef UNIX
			outDir.append("/");
#else
			outDir.append("\\");
#endif
			CUtil::AddError("", outDir);
		}
		else if (arg == "-extfile")
		{
			// read the user defined language extension map
			if (i + 2 > argc)
			{
				string err = "Error: Unable to parse command line args";
				cout << err << endl;
				CUtil::AddError(err);
				return 0;
			}
			i++;
			userExtMapFile = argv[i];
		}
		else if (arg == "-t" && isDiff)
		{
			if (i + 1 > argc)
				return 0;
			else
			{
				i++;
				double myMatch = atof(argv[i]);
				if (myMatch >= 0 && myMatch <= 100)
					match_threshold = myMatch;
				else
					return 0;
			}
		}
		else if (arg == "-tdup")
		{
			if (i + 1 > argc)
				return 0;
			else
			{
				i++;
				if (duplicate_threshold >= 0.0)
				{
					double myDup = atof(argv[i]);
					if (myDup <= 100.0)
					{
						if (myDup < 0.0)
							myDup = -1.0;
						duplicate_threshold = myDup;
					}
					else
						return 0;
				}
			}
		}
		else if (arg == "-nodup")
		{
			duplicate_threshold = -1.0;
		}
		else if (arg == "-trunc")
		{
			if (i + 1 > argc)
				return 0;
			else
			{
				i++;
				int myTrunc = atoi(argv[i]);
				if (myTrunc >= 0)
					lsloc_truncate = myTrunc;
				else
					return 0;
			}
		}
		else if (arg == "-d" && isDiff)
		{
			// ignore
		}
		else if (arg == "-cf")
		{
			// support ClearCase files
			clearCaseFile = true;
		}
		else if (arg == "-unified")
		{
			print_unified = true;
		}
		else if (arg == "-ascii")
		{
			print_csv = false;
			if (!print_legacy)
				print_ascii = true;
			else
				print_ascii = false;
		}
		else if (arg == "-legacy")
		{
			print_csv = false;
			print_ascii = false;
			print_legacy = true;
		}
		else if (arg == "-nocomplex")
		{
			print_cmplx = false;
		}
		else if (arg == "-cyclomatic")
		{
			print_cyclomatic_cmplx = true;
		}
#ifdef UNIX
		else if (arg == "-nolinks")
		{
			// disable following symbolic links
			followSymLinks = false;
		}
#endif
		else
			return 0;
	}
	return 1;
}

/*!
* Shows program usage and terminates application.
*
* \param option usage option (default="")
* \param do_exit exit after display (default=true)
*/
void MainObject::ShowUsage(const string &option, bool do_exit)
{
	if (option == "-v")
	{
		cout << "Usage: ucc -v" << endl << endl;
		cout << " -v: Displays the current version of UCC being executed" << endl;		
	}
	else if (option == "-d" || option == "-i1" || option == "-i2" || option == "-t")
	{
		cout << "Usage: ucc -d [-i1 <fileListA>] [-i2 <fileListB>] [-t <#>]" << endl << endl;
		cout << " -d: Enables the differencing function. If not specified, only the" << endl;
		cout << "     counting functions will execute." << endl << endl;
		cout << " Related Options:" << endl << endl;
		cout << "  -i1 <fileListA>: File containing a list of files to be used as" << endl;
		cout << "                   Baseline A for counting or comparison if -d is specified." << endl;
		cout << "                   If -i1 is not specified, the file 'fileListA.txt' will be" << endl;
		cout << "                   used as the default if -d is specified, and the file" << endl;
		cout << "                   'fileList.txt' will be used as the default without -d." << endl << endl;
		cout << "  -i2 <fileListB>: File containing a list of files to be be used as" << endl;
		cout << "                   Baseline B for comparison to Baseline A." << endl;
		cout << "                   If -i2 is not specified, the file 'fileListB.txt' will be" << endl;
		cout << "                   used as the default if -d is specified." << endl << endl;
		cout << "  -t <#>:          Specifies the percentage of common characters between two" << endl;
		cout << "                   lines of code that are being compared in order to determine" << endl;
		cout << "                   whether the line is modified or replaced. If the percentage of" << endl;
		cout << "                   common characters between the compared lines is greater than" << endl;
		cout << "                   the specified threshold, the line is considered replaced and" << endl;
		cout << "                   will be counted as one line deleted and one line added." << endl;
		cout << "                   Otherwise, it will be counted as one modified line." << endl;
		cout << "                   The valid range is 0 to 100 and defaults to 60." << endl;
	}
	else if (option == "-tdup")
	{
		cout << "Usage: ucc -tdup <#>" << endl << endl;
		cout << " -tdup <#>: Specifies the percentage of logical source lines of code (LSLOC)" << endl;
		cout << "            that have changed between two files of the same name in order to" << endl;
		cout << "            determine whether the files are duplicates. If the percentage of" << endl;
		cout << "            common LSLOC between two files is less than or equal to the" << endl;
		cout << "            specified threshold, the files are considered duplicates." << endl;
		cout << "            This method compares LSLOC similar to the differencing function" << endl;
		cout << "            and ignores formatting including blank lines and comments." << endl;
		cout << "            Note that files of different names may be checked for an exact" << endl;
		cout << "            physical match. The valid range is 0 to 100 and defaults to 0." << endl;
	}
	else if (option == "-trunc")
	{
		cout << "Usage: ucc -trunc <#>" << endl << endl;
		cout << " -trunc <#>: Specifies the maximum number of characters allowed in a logical" << endl;
		cout << "             source line of code (LSLOC). Any characters beyond the specified" << endl;
		cout << "             threshold will be truncated and ignored when compared." << endl;
		cout << "             If the truncation is disabled by setting the threshold to 0" << endl;
		cout << "             or the threshold is set too high, very long LSLOC may significantly" << endl;
		cout << "             degrade performance." << endl;
	}
	else if (option == "-cf")
	{
		cout << "Usage: ucc -cf" << endl << endl;
		cout << " -cf: Indicates that the target files were retrieved from" << endl;
		cout << "      IBM Rational ClearCase. ClearCase appends information at the end" << endl;
		cout << "      of file names beginning with '@@'. Use of this option strips" << endl;
		cout << "      all characters after the last '@@' sequence from the file name." << endl;
	}
	else if (option == "-dir")
	{
		cout << "Usage: ucc -dir <dirA> [<dirB>] <fileSpecs>" << endl << endl; 
		cout << " -dir: Specifies the directories and file types to be searched for files" << endl;
		cout << "       to be counted or compared. The directories dirA and dirB indicate" << endl;
		cout << "       the directories to be searched for each baseline. The fileSpecs indicate" << endl;
		cout << "       the file type specifications (typically containing search wildcards)." << endl;
		cout << "       The specified directories will be searched recursively." << endl << endl;
		cout << " Option Parameters:" << endl << endl;
		cout << "    <dirA>:      Specifies the directory of Baseline A to be searched for files" << endl;
		cout << "                 to be counted or compared." << endl << endl;
		cout << "    <dirB>:      If the -d option is specified, this specifies the directory" << endl;
		cout << "                 of Baseline B to be searched for files to be compared." << endl << endl;
		cout << "    <fileSpecs>: One or more specification of file types to be included" << endl;
		cout << "                 in the file search. Each file specification is separated" << endl;
		cout << "                 by whitespace and typically contains search wildcards."  << endl;
		cout << "                 For example:" << endl;
		cout << "                   *.cpp *.h *.java" << endl;
	}
	else if (option == "-outdir")
	{
		cout << "Usage: ucc -outdir <outDir>" << endl << endl;
		cout << " -outdir <outDir>: Specifies the directory where output files will be written." << endl;
		cout << "                   If this is not specified, the output files will be written" << endl;
		cout << "                   to the working directory by default. This option prevents" << endl;
		cout << "                   overwriting output files from multiple runs and allows for" << endl;
		cout << "                   batch execution and output organization." << endl;
	}
	else if (option == "-extfile")
	{
		cout << "Usage: ucc -extfile <extFile>" << endl << endl;
		cout << " -extfile <extFile>: Specifies a file containing user specified file extensions" << endl;
		cout << "                     for any of the available language counters. Any language" << endl;
		cout << "                     counter specified within this file will have its associated" << endl;
		cout << "                     extensions replaced. If a language is specified with no" << endl;
		cout << "                     extensions, the language counter will be disabled." << endl;
		cout << "                     The file format contains a single line entry for each" << endl;
		cout << "                     language. Single or multi-line comments may be included" << endl;
		cout << "                     with square brackets []. For example:" << endl << endl;
		cout << "                       C_CPP = *.cpp, *.h  [C/C++ extensions]" << endl << endl;
		cout << "                     Please see the user manual for available language counter" << endl;
		cout << "                     names." << endl;
	}
	else if (option == "-unified")
	{
		cout << "Usage: ucc -unified" << endl << endl;
		cout << " -unified: Prints language report files to a single unified report file." << endl;
		cout << "           The results are written to 'TOTAL_outfile.csv' or 'TOTAL_outfile.txt'." << endl;
		cout << "           In the absence of this option, results for each language are written" << endl;
		cout << "           to separate files." << endl;
	}
	else if (option == "-ascii")
	{
		cout << "Usage: ucc -ascii" << endl << endl;
		cout << " -ascii: Prints ASCII text (*.txt) report files instead of CSV (*.csv) files." << endl;
		cout << "         The content of the ASCII format is identical to the CSV format." << endl;
	}
	else if (option == "-legacy")
	{
		cout << "Usage: ucc -legacy" << endl << endl;
		cout << " -legacy: Prints legacy formatted ASCII text report files instead of" << endl;
		cout << "          the current format of the CSV or text files. The purpose of this" << endl;
		cout << "          option is to maintain backward compatibility with some older" << endl;
		cout << "          UCC results post-processing software systems." << endl;
	}
	else if (option == "-nodup")
	{
		cout << "Usage: ucc -nodup" << endl << endl;
		cout << " -nodup: Prevents separate processing of duplicate files. This avoids extra" << endl;
		cout << "         processing time to determine the presence of duplicate files within" << endl;
		cout << "         each baseline. With this option, all files will be counted and reported" << endl;
		cout << "         together, regardless of whether they are duplicates. Otherwise, files" << endl;
		cout << "         within a baseline will be checked for duplicates and results will" << endl;
		cout << "         be reported separately. Please see the user manual for details." << endl;
	}
	else if (option == "-nocomplex")
	{
		cout << "Usage: ucc -nocomplex" << endl << endl;
		cout << " -nocomplex: Disables printing of keyword counts and processing of complexity" << endl;
		cout << "             metrics. This can reduce processing time and limit reports." << endl;
	}
	else if (option == "-cyclomatic")
	{
		cout << "Usage: ucc -cyclomatic" << endl << endl;
		cout << " -cyclomatic: Enables printing of cyclomatic complexity metrics when available." << endl;
		cout << "              This is overridden by -nocomplex." << endl;
	}
#ifdef UNIX
	else if (option == "-nolinks")
	{
		cout << "Usage: ucc -nolinks" << endl << endl;
		cout << " -nolinks: Disables following symbolic links to directories and counting" << endl;
		cout << "           of links to files on Unix systems. This can prevent duplicate file counts." << endl;
	}
#endif
	else if (option == "-h" || option == "-help")
	{
		cout << "Usage: ucc -help <option>" << endl << endl;
		cout << " -help <option>: Without a specified option, this displays the list of command" << endl;
		cout << "                 line options. If a command line option is specified, detailed" << endl;
		cout << "                 usage information for the specified option is displayed." << endl;
	}
	else
	{
		cout << "Usage: ucc [-v] [-d [-i1 fileListA] [-i2 <fileListB>] [-t <#>]] [-tdup <#>]" << endl;
		cout << "           [-trunc <#>] [-cf] [-dir <dirA> [<dirB>] <fileSpecs>]" << endl;
		cout << "           [-outdir <outDir>] [-extfile <extFile>] [-unified] [-ascii] [-legacy]" << endl;
#ifdef UNIX
		cout << "           [-nodup] [-nocomplex] [-cyclomatic] [-nolinks] [-help [<option>]]" << endl << endl;
#else
		cout << "           [-nodup] [-nocomplex] [-cyclomatic] [-help [<option>]]" << endl << endl;
#endif
		cout << "Options:" << endl;
		cout << " -v                 Lists the current version number." << endl;
		cout << " -d                 Runs the differencing function." << endl;
		cout << "                      If not specified, runs the counting function." << endl;
		cout << " -i1 <fileListA>    Filename containing filenames in the Baseline A." << endl;
		cout << " -i2 <fileListB>    Filename containing filenames in the Baseline B." << endl;
		cout << " -t <#>             Specifies the threshold percentage for a modified line." << endl;
		cout << "                      (DEFAULTS TO 60)." << endl;
		cout << " -tdup <#>          Specifies the threshold percentage for duplicated files -" << endl;
		cout << "                      the maximum percent difference between two files of the" << endl;
		cout << "                      same name in a baseline to be considered duplicates." << endl;
		cout << "                      (DEFAULTS TO 0)" << endl;
		cout << " -trunc <#>         Specifies the maximum number of characters allowed in a" << endl;
		cout << "                      logical SLOC. Additional characters will be truncated." << endl;
		cout << "                      (DEFAULTS TO 10,000, use 0 for no truncation)" << endl;
		cout << " -cf                Indicated that target files were retrieved from ClearCase." << endl;
		cout << "                      Restored the original filename before counting." << endl;
		cout << " -dir               Specifies the following directories and file specifications: " << endl;
		cout << "      <dirA>          Name of the directory containing source files." << endl;
		cout << "                        If -d is given, dirA is the directory for Baseline A." << endl;
		cout << "      <dirB>          Name of the directory for Baseline B only if -d is given." << endl;
		cout << "      <fileSpecs>     File specifications, wildcard chars ? * are allowed." << endl;
		cout << "                        For example, *.cpp *.h" << endl;
		cout << " -outdir <outDir>   Specifies the directory to store the output files." << endl;
		cout << " -extfile <extFile> Indicates language extension mapping filename" << endl;
		cout << " -unified           Prints language report files to a single unified report file." << endl;
		cout << " -ascii             Prints ASCII text report files instead of CSV files." << endl;
		cout << " -legacy            Prints legacy formatted ASCII text report files" << endl;
		cout << "                      instead of the current format of the CSV or text files." << endl;
		cout << " -nodup             Disables separate processing of duplicate files." << endl;
		cout << " -nocomplex         Disables printing complexity reports or keyword counts." << endl;
		cout << " -cyclomatic        Enables printing cyclomatic complexity report." << endl;
#ifdef UNIX
		cout << " -nolinks           Disables following symbolic links to directories and files." << endl;
#endif
		cout << " -help <option>     Displays this usage or usage for a specified option." << endl;
	}
	if (do_exit)
		exit(1);
}

/*!
* Displays file counting progress.
*
* \param disp percentage to display
* \param count_progress count of files processed
* \param sizeo total number of files
*/
void MainObject::ShowProgress(unsigned int disp, unsigned int count_progress, unsigned int sizeo)
{
	if (sizeo == 1)
		cout << ".....100%";
	else
	{
		if (count_progress == 1)
			cout << ".....";
		else
			cout << "\b\b\b\b";
		if (disp < 10)
			cout << "..";
		else if (disp < 100)
			cout << ".";
		cout << disp << "%";
	}
	cout.flush();
}

/*!
* Read user-defined language extension map file.
*
* \param extMapFile language extension map file
*/
void MainObject::ReadUserExtMapping(const string &extMapFile)
{
	ifstream readFile;
	string line, str;
	string language;
	string extension;
	char *context = NULL;
	int flag;
	string token;
	size_t pos1, pos2;
	bool foundc = false;
	readFile.open(extMapFile.c_str(), ifstream::in);
	if (readFile.is_open())
	{
		while (readFile.good())
		{
			getline(readFile, line);
			line = CUtil::TrimString(line);
			flag = 0;

			// process embedded, whole, or multi-line comments (delimited by [])
			if (foundc)
			{
				pos2 = line.find_first_of(']');
				if (pos2 != string::npos)
				{
					if (pos2 >= line.size() - 1)
						line.clear();
					else
						line = line.substr(pos2 + 1);
					foundc = false;
				}
				else
					continue;
			}
			pos1 = line.find_first_of('[');
			while (pos1 != string::npos)
			{
				if (pos1 == 0)
					str = "";
				else
					str = line.substr(0, pos1);
				pos2 = line.find_first_of(']');
				if (pos2 != string::npos)
				{
					if (pos2 >= line.size() - 1)
						line = str;
					else
						line = str + line.substr(pos2 + 1);
				}
				else
				{
					line = str;
					foundc = true;
				}
				pos1 = line.find_first_of('[');
			}

			if (line.size() > 0)
			{
				istringstream iss(line);
				while (getline(iss, token, '='))
				{
					if (flag == 0)
					{
						language = CUtil::TrimString(token);
						flag = 1;
					}
					else
					{
						extension = CUtil::TrimString(token);
						flag = 0;
					}
				}
				LanguageExtensionMap.insert(std::pair<std::string, std::string>(language, extension));
			}
		}
	}	
	readFile.close();
	CreateExtMap();
}

/*!
* Create user-defined language extension map.
*/
void MainObject::CreateExtMap()
{
	size_t i, j;
	string token, lang_name;
	bool found, updateWeb = false;
	CCodeCounter *langCounter;
	CWebCounter *webCounter = (CWebCounter *)CounterForEachLanguage[WEB];
	StringVector *webExten;

	for (std::map< std::string, std::string >::const_iterator iter = LanguageExtensionMap.begin();
		iter != LanguageExtensionMap.end(); ++iter)
	{
		// check for a counter for the specified language
		lang_name = CUtil::ToLower(iter->first);
		langCounter = NULL;
		for (i = 0; i < CounterForEachLanguage.size(); i++)
		{
			if (CounterForEachLanguage[i]->classtype == WEB)
			{
				found = false;
				for (j = 0; j < webCounter->web_lang_names.size(); j++)
				{
					if (lang_name.compare(CUtil::ToLower(webCounter->web_lang_names[j])) == 0)
					{
						langCounter = CounterForEachLanguage[i];
						updateWeb = true;
						found = true;
						break;
					}
				}
				if (found)
					break;
			}
			else if (lang_name.compare(CUtil::ToLower(CounterForEachLanguage[i]->language_name)) == 0)
			{
				langCounter = CounterForEachLanguage[i];
				break;
			}
		}
		if (langCounter != NULL)
		{
			if (langCounter->classtype == WEB)
			{
				if (lang_name == "asp")
					webExten = &(webCounter->file_exten_asp);
				else if (lang_name == "jsp")
					webExten = &(webCounter->file_exten_jsp);
				else if (lang_name == "php")
					webExten = &(webCounter->file_exten_php);
				else if (lang_name == "coldfusion")
					webExten = &(webCounter->file_exten_cfm);
				else if (lang_name == "xml")
					webExten = &(webCounter->file_exten_xml);
				else
					webExten = &(webCounter->file_exten_htm);

				webExten->clear();						// optional line if existing map is to be erased
				istringstream iss(iter->second);
				while (getline(iss, token, ','))
					webExten->push_back(CUtil::TrimString(token));
			}
			else
			{
				langCounter->file_extension.clear();	// optional line if existing map is to be erased
				istringstream iss(iter->second);
				while (getline(iss, token, ','))
					langCounter->file_extension.push_back(CUtil::TrimString(token));
			}
		}
		else
		{
			string err = "Error: ";
			err += iter->first;
			err += " is not a supported language as specified in the language extension file";
			cout << endl << err << endl;
			CUtil::AddError(err);
		}
	}

	// update web extensions if changed
	if (updateWeb)
		webCounter->UpdateWebFileExt();
}

/*!
* Reads all files into memory.
*
* \param inputFileVector list of files to count (may be empty if inputFileList is given)
* \param inputFileList file containing list of files to count (if any)
* \param useListA use file list A? (otherwise use list B)
*
* \return method status
*/
int MainObject::ReadAllFiles(StringVector &inputFileVector, string const &inputFileList, bool useListA)
{
	filemap fmap;
	results r;
	r.lsloc_truncate = lsloc_truncate;
	std::vector<std::string>::iterator itVectorData;
	string fileName, clearCaseCroppedFile;
	WebType webType;
	string oneline;
	bool lineTooLong;
	bool isErr = false;
	unsigned int lineNum = 0;
	unsigned int fileclass;
	CWebCounter *webCounter;

    // if the size of the vector is zero read from the files
	if (inputFileVector.size() == 0 && inputFileList.size() > 0)
	{
	    ifstream fl;
		fl.open(inputFileList.c_str(), ifstream::in);

		if (!fl.is_open())
		{
			// try old input file name
			fl.open(INPUT_FILE_LIST_OLD, ifstream::in);
			if (!fl.is_open())
			{
				string err = "Error: Unable to open list file (";
				err += inputFileList;
				err += ")";
				cout << endl << err << endl;
				CUtil::AddError(err);
				return 0;
			}
		}
		fl.clear();
		fl.seekg(0, ios::beg);

		StringVector searchFiles;
		searchFiles.push_back("*.*");
		while (fl.good())
		{
			getline(fl, fileName);
			if (!CUtil::CheckBlank(fileName))
			{
				if (clearCaseFile)
					inputFileVector.push_back(fileName);
				else
				{
					// expand if item is a directory
					if (!CUtil::ListAllFiles(fileName, searchFiles, inputFileVector, followSymLinks))
						inputFileVector.push_back(fileName);
				}
			}
		}
		fl.close();
	}

	// loop through all the listed or extracted file names
	for (itVectorData = inputFileVector.begin(); itVectorData != inputFileVector.end(); itVectorData++)
	{
		fileName = *(itVectorData);
		r.e_flag = false;
		r.error_code = "";

		fileName = CUtil::TrimString(fileName);
		if (clearCaseFile)
		{
			// handle the @@ from ClearCase
			clearCaseCroppedFile = CUtil::ConvertClearCaseFile(fileName);
			fileclass = DecideLanguage(clearCaseCroppedFile, false);
		}
		else
			fileclass = DecideLanguage(fileName, false);
		if (fileclass == UNKNOWN)
		{
			WriteUncountedFile("Unknown File Extension", fileName, useListA, print_csv, outDir);
			continue;
		}
		else
		{
			if (useListA)
				counter->total_filesA++;
			else
				counter->total_filesB++;
			
			if (fileclass == WEB)
			{
				// get web file class
				webCounter = (CWebCounter *)counter;
				webType = webCounter->GetWebType(clearCaseFile ? clearCaseCroppedFile : fileName);
				if (webType == WEB_PHP)
				{
					if (useListA)
						webCounter->total_php_filesA++;
					else
						webCounter->total_php_filesB++;
				}
				else if (webType == WEB_ASP)
				{
					if (useListA)
						webCounter->total_asp_filesA++;
					else
						webCounter->total_asp_filesB++;
				}
				else if (webType == WEB_JSP)
				{
					if (useListA)
						webCounter->total_jsp_filesA++;
					else
						webCounter->total_jsp_filesB++;
				}
				else if (webType == WEB_XML)
				{
					if (useListA)
						webCounter->total_xml_filesA++;
					else
						webCounter->total_xml_filesB++;
				}
				else if (webType == WEB_CFM)
				{
					if (useListA)
						webCounter->total_cfm_filesA++;
					else
						webCounter->total_cfm_filesB++;
				}
				else
				{
					if (useListA)
						webCounter->total_htm_filesA++;
					else
						webCounter->total_htm_filesB++;
				}
			}
		}

		// read all files
		if (fileName.size() > 0)
		{
			fmap.clear();
			lineNum = 0;
			ifstream fr(fileName.c_str(), ios::in);
			if (!fr.is_open())
			{
				r.e_flag = true;
				r.error_code = "Unable to open file";
				string err = "Error: ";
				err += r.error_code;
				err += " (";
				err += fileName;
				err += ")";
				if (!isErr)
					cout << endl;
				isErr = true;
				cout << err << endl;
				CUtil::AddError(err);
				WriteUncountedFile("Not Readable", fileName, useListA, print_csv, outDir);
			}
			else 
			{
				// fmap.clear();
				getline(fr, oneline);
				lineTooLong = false;
				while (fr.good())
				{
					lineNum++;
					if (fileclass != FORTRAN && fileclass != PYTHON)	// column location and/or white space is significant
						oneline = CUtil::TrimString(oneline);
					if (oneline.length() > MAX_LINE_LENGTH)
					{
						lineTooLong = true;
						break;
					}
					oneline = CUtil::ReplaceSmartQuotes(oneline);
					lineElement element(lineNum, oneline);
					fmap.push_back(element);
					getline(fr, oneline);
				}
				fr.clear();
				fr.close();

				oneline = CUtil::TrimString(oneline);
				if (oneline.length() > MAX_LINE_LENGTH)
					lineTooLong = true;

				if (lineTooLong)
				{
					r.e_flag = true;
					r.error_code = "Line too long";
					string err = "Error: ";
					err += r.error_code;
					err += ", file skipped (";
					err += fileName;
					err += ")";
					if (!isErr)
						cout << endl;
					isErr = true;
					cout << err << endl;
					CUtil::AddError(err);
					fmap.clear();  // don't bother processing the file if an error is just going to be reported.				
					WriteUncountedFile("Excessive Line Length", fileName, useListA, print_csv, outDir);
				} 
				else if (!oneline.empty())
				{
					lineNum++;
					lineElement element(lineNum, oneline);
					fmap.push_back(element);
				}
				else if (fmap.size() == 0)
				{
					string err = "Warning: File is empty (";
					err += fileName;
					err += ")";
					if (!isErr)
						cout << endl;
					isErr = true;
					cout << err << endl;
					CUtil::AddError(err);
				}
			}
			// if the filename was modified by ClearCase, use the cropped name
			if (clearCaseFile)
				r.file_name = clearCaseCroppedFile;
			else
				r.file_name = fileName;

			// depending on which source file we are on...
			SourceFileElement s_element(fmap, r);
			(useListA) ? SourceFileA.push_back(s_element) : SourceFileB.push_back(s_element);			
		}
	}
	return 1;
}

/*!
* Process source file list and call relevant counter for each file.
*
* \param useListA use file list A? (otherwise use list B)
*/
void MainObject::ProcessSourceList(bool useListA)
{
	SourceFileList* mySrcFileList = (useListA) ? &SourceFileA: &SourceFileB;
	string errList;

	size_t embFile;
	unsigned int count_progress = 1;
	unsigned int disp = 0;
	unsigned int sizeo = (unsigned int)mySrcFileList->size();
	for (SourceFileList::iterator i = mySrcFileList->begin(); i != mySrcFileList->end(); i++)
	{
		// handle any exception that may occur un-handled in the counting functions
		try
		{
			embFile = i->second.file_name.find(EMBEDDED_FILE_PREFIX);
			if (embFile == string::npos)
			{
				disp = ((count_progress * 100) / sizeo);
				ShowProgress(disp, count_progress, sizeo);
				count_progress++;
			}

			// examines the file and sets counter to the correct language counter
			DecideLanguage(i->second.file_name);
			i->second.file_type = (counter->classtype == UNKNOWN || counter->classtype == DATAFILE) ? DATA : CODE;
			i->second.class_type = counter->classtype;
			counter->CountSLOC(&(i->first), &(i->second));
			if (i->second.trunc_lines > 0)
			{
				stringstream ss;
				ss << "Warning: Truncated ";
				ss << i->second.trunc_lines;
				ss << " line(s) in file (";
				ss << i->second.file_name;
				ss << ")";
				string err = ss.str();
				errList += err + "\n";
				CUtil::AddError(err);
			}

			// if webcounter, insert the separation file into list
			if (counter->classtype == WEB)
			{
				SourceFileList::iterator pos = i;
				pos++;
				map<int, SourceFileElement>* smap = ((CWebCounter*)counter)->GetSeparationMap();
				for (map<int, SourceFileElement>::iterator iter = smap->begin(); iter != smap->end(); iter++)
				{
					if (iter->second.first.size() > 0)
					{
						(useListA) ? SourceFileA.insert(pos, iter->second) : SourceFileB.insert(pos, iter->second);
					}
				}
			}
		}
		catch (...)
		{
			string err = "Error: Unable to count file (";
			err += i->second.file_name;
			err += ")";
			errList += err + "\n";
			CUtil::AddError(err);
			WriteUncountedFile("Unhandled Counting Error", i->second.file_name, useListA, print_csv, outDir);
		}
	}

	if (mySrcFileList->size() > 0)
		cout << "\b\b\b\b\b\b\b\b\b";
	cout << ".....DONE" << endl;
	if (!errList.empty())
		cout << errList;
}

/*!
* Adds an uncounted file log.
*
* \param msg message string
* \param uncFile uncounted file path
* \param useListA use file list A? (otherwise use list B)
* \param csvOutput CSV file stream? (otherwise ASCII text file)
* \param outDir output directory (used to initialize)
*/
void MainObject::WriteUncountedFile(const string &msg, const string &uncFile, bool useListA, bool csvOutput, const string &outDir)
{
	static ofstream uncFileA;
	static ofstream uncFileB;
	static string filePathA;
	static string filePathB;
	ofstream *uncFS;
	string fileName, filePath;

	if (uncFile.empty())
		return;

	// open the uncounted files output file if not already opened
	if (useListA)
	{
		filePath = filePathA;
		uncFS = &uncFileA;
	}
	else
	{
		filePath = filePathB;
		uncFS = &uncFileB;
	}
	if (filePath.empty())
	{
		fileName = "";
		if (isDiff)
		{
			if (useListA)
				fileName = "Baseline-A-";
			else
				fileName = "Baseline-B-";
		}
		if (csvOutput)
			fileName += UNCOUNTED_FILES_CSV;
		else
			fileName += UNCOUNTED_FILES;

		if (outDir.empty())
			filePath = fileName;
		else
			filePath = outDir + fileName;
		if (useListA)
			filePathA = filePath;
		else
			filePathB = filePath;
	}
	if (!(*uncFS).is_open())
	{
		(*uncFS).open(filePath.c_str(), ofstream::out);
		if (!(*uncFS).is_open())
		{
			string err = "Error: Failed to open uncounted files output file (";
			err += filePath;
			err += ")";
			cout << err << endl;
			CUtil::AddError(err);
			return;
		}
		CUtil::PrintFileHeader(*uncFS, "UNCOUNTED FILES", cmdLine);
		if (csvOutput)
			(*uncFS) << "Message,Uncounted File" << endl;
		else
		{
			(*uncFS).setf(ofstream::left);
			(*uncFS).width(45);
			(*uncFS) << "Message";
			(*uncFS).unsetf(ofstream::left);
			(*uncFS).width(5);
			(*uncFS) << "  |  ";
			(*uncFS).width(3);
			(*uncFS).setf(ofstream::left);
			(*uncFS).width(45);
			(*uncFS) << "Uncounted File";
			(*uncFS) << endl;
			for (int y = 0; y < 90; y++)
				(*uncFS) << "-";
		}
	}
	if (csvOutput)
		(*uncFS) << msg << "," << uncFile << endl;
	else
	{
		(*uncFS) << endl;
		(*uncFS).setf(ofstream::left);
		(*uncFS).width(45);
		(*uncFS) << msg;
		(*uncFS).unsetf(ofstream::left);
		(*uncFS).width(5);
		(*uncFS) << "  |  ";
		(*uncFS).setf(ofstream::left);
		(*uncFS).width(45);
		(*uncFS) << uncFile;
	}
	return;
}

/*!
* Determines which counter can be used for a file.
*
* \param file_name file name
* \param setCounter set the current counter?
*
* \return language class type
*/
unsigned int MainObject::DecideLanguage(const string &file_name, bool setCounter)
{
	bool found = false;
	for (map<int, CCodeCounter*>::iterator iter = CounterForEachLanguage.begin(); iter != CounterForEachLanguage.end(); iter++)
	{
		if (iter->second->IsSupportedFileExtension(file_name))
		{
			found = true;
			counter = iter->second;
			if (setCounter && print_cmplx)
			{
				counter->isPrintKeyword = true;
				if (print_cyclomatic_cmplx)
					counter->isPrintCyclomatic = true;
			}
			break;
		}
	}
	if (!found)
		counter = CounterForEachLanguage[UNKNOWN];
	return counter->classtype;
}

/*!
* Checks whether a file has a supported extension (can be counted by UCC).
*
* \param file_name file name
*
* \return supported file extension?
*/
bool MainObject::IsSupportedFileExtension(const string &file_name) 
{
	for (map<int,CCodeCounter*>::iterator iter = CounterForEachLanguage.begin(); iter != CounterForEachLanguage.end(); iter++)
	{
		if (iter->second->IsSupportedFileExtension(file_name))
			return true;
	}
	return false;
}

/*!
* Retrieves the language name for a file.
*
* \param class_type file classification type
* \param file_name file name
*
* \return language name
*/
string MainObject::GetLanguageName(unsigned int class_type, const string &file_name) 
{
	if (class_type == WEB && file_name.length() > 0)
	{
		CWebCounter *webCounter = (CWebCounter*)CounterForEachLanguage[WEB];
		WebType webType = webCounter->GetWebType(file_name);
		return(webCounter->GetWebLangName(webType));
	}
	else if (class_type < CounterForEachLanguage.size())
		return CounterForEachLanguage[class_type]->language_name;
	else
		return DEF_LANG_NAME;
}

/*!
* Prints the counting results for a set of files.
*
* \param useListA use file list A? (otherwise use list B)
* \param outputFileNamePrePend name to prepend to the output file
* \param filesToPrint list of files to include or exclude
* \param excludeFiles exclude files? (if true excludes files in filesToPrint; if false includes only files in filesToPrint)
*
* \return method status
*/
int MainObject::PrintCountResults(bool useListA, const string &outputFileNamePrePend, StringVector *filesToPrint, bool excludeFiles)
{
	ofstream* pout;
	ofstream* pout_csv;
	TotalValueMap total;
	WebTotalValueMap webtotal;
	unsigned int class_type;
	StringVector::iterator sit;
	CWebCounter *webCounter;
	WebType webType;

	// skip if all files are excluded
	if (filesToPrint != NULL && filesToPrint->size() < 1 && !excludeFiles)
		return 0;

	SourceFileList::iterator its;
	SourceFileList* mySourceFile = (useListA) ? &SourceFileA : &SourceFileB;
	for (its = mySourceFile->begin(); its != mySourceFile->end(); its++)
	{
		if (filesToPrint != NULL && filesToPrint->size() > 0)
		{
			// restrict based on those files in the filesToPrint list
			sit = filesToPrint->begin();
			while (sit != filesToPrint->end() && its->second.file_name.compare((*sit)) != 0)
				sit++;

			if (excludeFiles)
			{
				// skip the file if in the filesToPrint list
				if (sit != filesToPrint->end())
					continue;
			}
			else
			{
				 // skip the file if NOT in the filesToPrint list
				if (sit == filesToPrint->end())
					continue;
			}
		}

		if (its->second.class_type == WEB)
		{
			SourceFileList::iterator startpos = its;
			SourceFileList::iterator endpos = ++startpos;
			for (; endpos!= mySourceFile->end(); endpos++)
			{
				if (endpos->second.file_name.find(EMBEDDED_FILE_PREFIX) == string::npos)
					break;
			}
			webType = ((CWebCounter*)CounterForEachLanguage[WEB])->GetWebType(its->second.file_name);
			if (print_ascii || print_legacy)
			{
				pout = ((CWebCounter*)CounterForEachLanguage[WEB])->GetOutputStream(webType, outDir + outputFileNamePrePend, cmdLine, false, print_legacy);
				if (pout == NULL)
				{
					string err = "Error: Unable to create file (";
					err += outputFileNamePrePend;
					if (webType == WEB_PHP)
						err += "PHP";
					else if (webType == WEB_ASP)
						err += "ASP";
					else if (webType == WEB_JSP)
						err += "JSP";
					else if (webType == WEB_XML)
						err += "XML";
					else if (webType == WEB_CFM)
						err += "ColdFusion";
					else
						err += "HTML";
					err += OUTPUT_FILE_NAME;
					err += "). Operation aborted.";
					cout << err << endl;
					CUtil::AddError(err);
					return 0;
				}
			}
			if (print_csv)
			{
				pout_csv = ((CWebCounter*)CounterForEachLanguage[WEB])->GetOutputStream(webType, outDir + outputFileNamePrePend, cmdLine, true);
				if (pout_csv == NULL)
				{
					string err = "Error: Unable to create file (";
					err += outputFileNamePrePend;
					if (webType == WEB_PHP)
						err += "PHP";
					else if (webType == WEB_ASP)
						err += "ASP";
					else if (webType == WEB_JSP)
						err += "JSP";
					else if (webType == WEB_XML)
						err += "XML";
					else if (webType == WEB_CFM)
						err += "ColdFusion";
					else
						err += "HTML";
					err += OUTPUT_FILE_NAME_CSV;
					err += "). Operation aborted.";
					cout << err << endl;
					CUtil::AddError(err);
					return 0;
				}
			}

			if (webType == WEB_PHP)
			{
				results r_htm;
				results r_js;
				results r_vbs;
				results r_php;
				for (SourceFileList::iterator i = startpos; i!= endpos; i++)
				{
					switch (i->second.class_type)
					{
					case HTML_PHP:
						r_htm = i->second;
						break;
					case JAVASCRIPT_PHP:
						r_js = i->second;
						break;
					case VBS_PHP:
						r_vbs = i->second;
						break;
					case PHP:
						r_php = i->second;
						break;
					}
				}
				r_htm.SLOC_lines[PHY] = r_htm.exec_lines[PHY] + r_htm.data_lines[PHY];
				r_htm.SLOC_lines[LOG] = r_htm.exec_lines[LOG] + r_htm.data_lines[LOG];
				r_htm.total_lines = r_htm.SLOC_lines[PHY] +	r_htm.blank_lines + r_htm.comment_lines;

				r_js.SLOC_lines[PHY] = r_js.exec_lines[PHY] + r_js.data_lines[PHY];
				r_js.SLOC_lines[LOG] = r_js.exec_lines[LOG] + r_js.data_lines[LOG];
				r_js.total_lines = r_js.SLOC_lines[PHY] +	r_js.blank_lines + r_js.comment_lines;

				r_vbs.SLOC_lines[PHY] = r_vbs.exec_lines[PHY] + r_vbs.data_lines[PHY];
				r_vbs.SLOC_lines[LOG] = r_vbs.exec_lines[LOG] + r_vbs.data_lines[LOG];
				r_vbs.total_lines = r_vbs.SLOC_lines[PHY] +	r_vbs.blank_lines + r_vbs.comment_lines;

				r_php.SLOC_lines[PHY] = r_php.directive_lines[PHY] + r_php.exec_lines[PHY] + r_php.data_lines[PHY];
				r_php.SLOC_lines[LOG] = r_php.directive_lines[LOG] + r_php.exec_lines[LOG] + r_php.data_lines[LOG];
				r_php.total_lines = r_php.SLOC_lines[PHY] +	r_php.blank_lines + r_php.comment_lines;

				if (print_ascii || print_legacy)
				{
					(*pout).setf(ios::right);
					(*pout).width(8);		(*pout) << (r_htm.total_lines + r_js.total_lines + r_vbs.total_lines + r_php.total_lines);
					(*pout) << " ";
					(*pout).width(7);		(*pout) << (r_htm.blank_lines + r_js.blank_lines + r_vbs.blank_lines + r_php.blank_lines);
					(*pout) << " |";
					(*pout).width(8);		(*pout) << (r_htm.comment_lines + r_js.comment_lines + r_vbs.comment_lines + r_php.comment_lines);
					(*pout) << " ";
					(*pout).width(8);		(*pout) << (r_htm.e_comm_lines + r_js.e_comm_lines + r_vbs.e_comm_lines + r_php.e_comm_lines);
					(*pout) << " |";
					(*pout).width(8);		(*pout) << r_htm.data_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_htm.exec_lines[LOG];
					(*pout) << " |";
					(*pout).width(8);		(*pout) << r_js.data_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_js.exec_lines[LOG];
					(*pout) << " |";
					(*pout).width(8);		(*pout) << r_vbs.data_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_vbs.exec_lines[LOG];
					(*pout) << " |";
					(*pout).width(8);		(*pout) << r_php.directive_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_php.data_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_php.exec_lines[LOG];
					if (print_legacy)
					{
						(*pout) << " |";
						(*pout).width(8);	(*pout) << (r_htm.SLOC_lines[LOG] + r_js.SLOC_lines[LOG] + r_vbs.SLOC_lines[LOG] + r_php.SLOC_lines[LOG]);
					}
					(*pout) << " |";
					(*pout).width(8);		(*pout) << r_htm.SLOC_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_js.SLOC_lines[LOG];
					(*pout) << " ";
					(*pout).width(8);		(*pout) << r_vbs.SLOC_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_php.SLOC_lines[LOG];
					if (!print_legacy)
					{
						(*pout) << " |";
						(*pout).width(8);	(*pout) << (r_htm.SLOC_lines[LOG] + r_js.SLOC_lines[LOG] + r_vbs.SLOC_lines[LOG] + r_php.SLOC_lines[LOG]);
						(*pout) << " |";
						(*pout).width(9);	(*pout) << (r_htm.SLOC_lines[PHY] + r_js.SLOC_lines[PHY] + r_vbs.SLOC_lines[PHY] + r_php.SLOC_lines[PHY]);
					}
					(*pout) << " | CODE  ";
					(*pout) << its->second.file_name << endl;
					(*pout).unsetf(ios::right);
				}
				if (print_csv)
				{
					(*pout_csv) << (r_htm.total_lines + r_js.total_lines + r_vbs.total_lines + r_php.total_lines) << ",";
					(*pout_csv) << (r_htm.blank_lines + r_js.blank_lines + r_vbs.blank_lines + r_php.blank_lines) << ",";
					(*pout_csv) << (r_htm.comment_lines + r_js.comment_lines + r_vbs.comment_lines + r_php.comment_lines) << ",";
					(*pout_csv) << (r_htm.e_comm_lines + r_js.e_comm_lines + r_vbs.e_comm_lines + r_php.e_comm_lines) << ",";
					(*pout_csv) << r_htm.data_lines[LOG] << ",";
					(*pout_csv) << r_htm.exec_lines[LOG] << ",";
					(*pout_csv) << r_js.data_lines[LOG] << ",";
					(*pout_csv) << r_js.exec_lines[LOG] << ",";
					(*pout_csv) << r_vbs.data_lines[LOG] << ",";
					(*pout_csv) << r_vbs.exec_lines[LOG] << ",";
					(*pout_csv) << r_php.directive_lines[LOG] << ",";
					(*pout_csv) << r_php.data_lines[LOG] << ",";
					(*pout_csv) << r_php.exec_lines[LOG] << ",";
					(*pout_csv) << r_htm.SLOC_lines[LOG] << ",";
					(*pout_csv) << r_js.SLOC_lines[LOG] << ",";
					(*pout_csv) << r_vbs.SLOC_lines[LOG] << ",";
					(*pout_csv) << r_php.SLOC_lines[LOG] << ",";
					(*pout_csv) << (r_htm.SLOC_lines[LOG] + r_js.SLOC_lines[LOG] + r_vbs.SLOC_lines[LOG] + r_php.SLOC_lines[LOG]) << ",";
					(*pout_csv) << (r_htm.SLOC_lines[PHY] + r_js.SLOC_lines[PHY] + r_vbs.SLOC_lines[PHY] + r_php.SLOC_lines[PHY]) << ",";
					(*pout_csv) << "CODE," << its->second.file_name << endl;
				}

				webtotal[webType].num_of_file++;

				webtotal[webType].total_line += (r_htm.total_lines + r_js.total_lines + r_vbs.total_lines + r_php.total_lines);
				webtotal[webType].blank_line += (r_htm.blank_lines + r_js.blank_lines + r_vbs.blank_lines + r_php.blank_lines);
				webtotal[webType].whole_comment += (r_htm.comment_lines + r_js.comment_lines + r_vbs.comment_lines + r_php.comment_lines);
				webtotal[webType].embed_comment += (r_htm.e_comm_lines + r_js.e_comm_lines + r_vbs.e_comm_lines + r_php.e_comm_lines);
				
				//0:htm 1:js 2:vbs 3:php
				webtotal[webType].phy_decl[0] += r_htm.data_lines[PHY];
				webtotal[webType].phy_instr[0] += r_htm.exec_lines[PHY];
				webtotal[webType].log_decl[0] += r_htm.data_lines[LOG];
				webtotal[webType].log_instr[0] += r_htm.exec_lines[LOG];

				webtotal[webType].phy_decl[1] += r_js.data_lines[PHY];
				webtotal[webType].phy_instr[1] += r_js.exec_lines[PHY];
				webtotal[webType].log_decl[1] += r_js.data_lines[LOG];
				webtotal[webType].log_instr[1] += r_js.exec_lines[LOG];

				webtotal[webType].phy_decl[2] += r_vbs.data_lines[PHY];
				webtotal[webType].phy_instr[2] += r_vbs.exec_lines[PHY];
				webtotal[webType].log_decl[2] += r_vbs.data_lines[LOG];
				webtotal[webType].log_instr[2] += r_vbs.exec_lines[LOG];

				webtotal[webType].phy_direct[3] += r_php.directive_lines[PHY];
				webtotal[webType].phy_decl[3] += r_php.data_lines[PHY];
				webtotal[webType].phy_instr[3] += r_php.exec_lines[PHY];
				webtotal[webType].log_direct[3] += r_php.directive_lines[LOG];
				webtotal[webType].log_decl[3] += r_php.data_lines[LOG];
				webtotal[webType].log_instr[3] += r_php.exec_lines[LOG];
			}
			else if (webType == WEB_JSP)
			{
				results r_htm;
				results r_js;
				results r_vbs;
				results r_java;
				for (SourceFileList::iterator i = startpos; i!= endpos; i++)
				{
					switch (i->second.class_type)
					{
					case HTML_JSP:
						r_htm = i->second;
						break;
					case JAVASCRIPT_JSP:
						r_js = i->second;
						break;
					case VBS_JSP:
						r_vbs = i->second;
						break;
					case JAVA_JSP:
						r_java = i->second;
						break;
					}
				}
				r_htm.SLOC_lines[PHY] = r_htm.exec_lines[PHY] + r_htm.data_lines[PHY];
				r_htm.SLOC_lines[LOG] = r_htm.exec_lines[LOG] + r_htm.data_lines[LOG];
				r_htm.total_lines = r_htm.SLOC_lines[PHY] +	r_htm.blank_lines + r_htm.comment_lines;

				r_js.SLOC_lines[PHY] = r_js.exec_lines[PHY] + r_js.data_lines[PHY];
				r_js.SLOC_lines[LOG] = r_js.exec_lines[LOG] + r_js.data_lines[LOG];
				r_js.total_lines = r_js.SLOC_lines[PHY] +	r_js.blank_lines + r_js.comment_lines;

				r_vbs.SLOC_lines[PHY] = r_vbs.exec_lines[PHY] + r_vbs.data_lines[PHY];
				r_vbs.SLOC_lines[LOG] = r_vbs.exec_lines[LOG] + r_vbs.data_lines[LOG];
				r_vbs.total_lines = r_vbs.SLOC_lines[PHY] +	r_vbs.blank_lines + r_vbs.comment_lines;

				r_java.SLOC_lines[PHY] = r_java.directive_lines[PHY] + r_java.exec_lines[PHY] + r_java.data_lines[PHY];
				r_java.SLOC_lines[LOG] = r_java.directive_lines[LOG] + r_java.exec_lines[LOG] + r_java.data_lines[LOG];
				r_java.total_lines = r_java.SLOC_lines[PHY] +	r_java.blank_lines + r_java.comment_lines;

				if (print_ascii || print_legacy)
				{
					(*pout).setf(ios::right);
					(*pout).width(8);		(*pout) << (r_htm.total_lines + r_js.total_lines + r_vbs.total_lines + r_java.total_lines);
					(*pout) << " ";
					(*pout).width(7);		(*pout) << (r_htm.blank_lines + r_js.blank_lines + r_vbs.blank_lines + r_java.blank_lines);
					(*pout) << " |";
					(*pout).width(8);		(*pout) << (r_htm.comment_lines + r_js.comment_lines + r_vbs.comment_lines + r_java.comment_lines);
					(*pout) << " ";
					(*pout).width(8);		(*pout) << (r_htm.e_comm_lines + r_js.e_comm_lines + r_vbs.e_comm_lines + r_java.e_comm_lines);
					(*pout) << " |";
					(*pout).width(8);		(*pout) << r_htm.data_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_htm.exec_lines[LOG];
					(*pout) << " |";
					(*pout).width(8);		(*pout) << r_js.data_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_js.exec_lines[LOG];
					(*pout) << " |";
					(*pout).width(8);		(*pout) << r_vbs.data_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_vbs.exec_lines[LOG];
					(*pout) << " |";
					(*pout).width(8);		(*pout) << r_java.directive_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_java.data_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_java.exec_lines[LOG];
					if (print_legacy)
					{
						(*pout) << " |";
						(*pout).width(8);	(*pout) << (r_htm.SLOC_lines[LOG] + r_js.SLOC_lines[LOG] + r_vbs.SLOC_lines[LOG] + r_java.SLOC_lines[LOG]);
					}
					(*pout) << " |";
					(*pout).width(8);		(*pout) << r_htm.SLOC_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_js.SLOC_lines[LOG];
					(*pout) << " ";
					(*pout).width(8);		(*pout) << r_vbs.SLOC_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_java.SLOC_lines[LOG];
					if (!print_legacy)
					{
						(*pout) << " |";
						(*pout).width(8);	(*pout) << (r_htm.SLOC_lines[LOG] + r_js.SLOC_lines[LOG] + r_vbs.SLOC_lines[LOG] + r_java.SLOC_lines[LOG]);
						(*pout) << " |";
						(*pout).width(9);	(*pout) << (r_htm.SLOC_lines[PHY] + r_js.SLOC_lines[PHY] + r_vbs.SLOC_lines[PHY] + r_java.SLOC_lines[PHY]);
					}
					(*pout) << " | CODE  ";
					(*pout) << its->second.file_name << endl;
					(*pout).unsetf(ios::right);
				}
				if (print_csv)
				{
					(*pout_csv) << (r_htm.total_lines + r_js.total_lines + r_vbs.total_lines + r_java.total_lines) << ",";
					(*pout_csv) << (r_htm.blank_lines + r_js.blank_lines + r_vbs.blank_lines + r_java.blank_lines) << ",";
					(*pout_csv) << (r_htm.comment_lines + r_js.comment_lines + r_vbs.comment_lines + r_java.comment_lines) << ",";
					(*pout_csv) << (r_htm.e_comm_lines + r_js.e_comm_lines + r_vbs.e_comm_lines + r_java.e_comm_lines) << ",";
					(*pout_csv) << r_htm.data_lines[LOG] << ",";
					(*pout_csv) << r_htm.exec_lines[LOG] << ",";
					(*pout_csv) << r_js.data_lines[LOG] << ",";
					(*pout_csv) << r_js.exec_lines[LOG] << ",";
					(*pout_csv) << r_vbs.data_lines[LOG] << ",";
					(*pout_csv) << r_vbs.exec_lines[LOG] << ",";
					(*pout_csv) << r_java.directive_lines[LOG] << ",";
					(*pout_csv) << r_java.data_lines[LOG] << ",";
					(*pout_csv) << r_java.exec_lines[LOG] << ",";
					(*pout_csv) << r_htm.SLOC_lines[LOG] << ",";
					(*pout_csv) << r_js.SLOC_lines[LOG] << ",";
					(*pout_csv) << r_vbs.SLOC_lines[LOG] << ",";
					(*pout_csv) << r_java.SLOC_lines[LOG] << ",";
					(*pout_csv) << (r_htm.SLOC_lines[LOG] + r_js.SLOC_lines[LOG] + r_vbs.SLOC_lines[LOG] + r_java.SLOC_lines[LOG]) << ",";
					(*pout_csv) << (r_htm.SLOC_lines[PHY] + r_js.SLOC_lines[PHY] + r_vbs.SLOC_lines[PHY] + r_java.SLOC_lines[PHY]) << ",";
					(*pout_csv) << "CODE," << its->second.file_name << endl;
				}

				webtotal[webType].num_of_file++;

				webtotal[webType].total_line += (r_htm.total_lines + r_js.total_lines + r_vbs.total_lines + r_java.total_lines);
				webtotal[webType].blank_line += (r_htm.blank_lines + r_js.blank_lines + r_vbs.blank_lines + r_java.blank_lines);
				webtotal[webType].whole_comment += (r_htm.comment_lines + r_js.comment_lines + r_vbs.comment_lines + r_java.comment_lines);
				webtotal[webType].embed_comment += (r_htm.e_comm_lines + r_js.e_comm_lines + r_vbs.e_comm_lines + r_java.e_comm_lines);
				
				//0:htm 1:js 2:vbs 3:java
				webtotal[webType].phy_decl[0] += r_htm.data_lines[PHY];
				webtotal[webType].phy_instr[0] += r_htm.exec_lines[PHY];
				webtotal[webType].log_decl[0] += r_htm.data_lines[LOG];
				webtotal[webType].log_instr[0] += r_htm.exec_lines[LOG];

				webtotal[webType].phy_decl[1] += r_js.data_lines[PHY];
				webtotal[webType].phy_instr[1] += r_js.exec_lines[PHY];
				webtotal[webType].log_decl[1] += r_js.data_lines[LOG];
				webtotal[webType].log_instr[1] += r_js.exec_lines[LOG];

				webtotal[webType].phy_decl[2] += r_vbs.data_lines[PHY];
				webtotal[webType].phy_instr[2] += r_vbs.exec_lines[PHY];
				webtotal[webType].log_decl[2] += r_vbs.data_lines[LOG];
				webtotal[webType].log_instr[2] += r_vbs.exec_lines[LOG];

				webtotal[webType].phy_direct[3] += r_java.directive_lines[PHY];
				webtotal[webType].phy_decl[3] += r_java.data_lines[PHY];
				webtotal[webType].phy_instr[3] += r_java.exec_lines[PHY];
				webtotal[webType].log_direct[3] += r_java.directive_lines[LOG];
				webtotal[webType].log_decl[3] += r_java.data_lines[LOG];
				webtotal[webType].log_instr[3] += r_java.exec_lines[LOG];
			}
			else if (webType == WEB_ASP)
			{
				results r_htm;
				results r_jsc;
				results r_vbsc;
				results r_jss;
				results r_vbss;
				results r_css;
				for (SourceFileList::iterator i = startpos; i!= endpos; i++)
				{
					switch (i->second.class_type)
					{
					case HTML_ASP:
						r_htm = i->second;
						break;
					case JAVASCRIPT_ASP_C:
						r_jsc = i->second;
						break;
					case VBS_ASP_C:
						r_vbsc = i->second;
						break;
					case JAVASCRIPT_ASP_S:
						r_jss = i->second;
						break;
					case VBS_ASP_S:
						r_vbss = i->second;
						break;
					case CSHARP_ASP_S:
						r_css = i->second;
						break;
					}
				}
				r_htm.SLOC_lines[PHY] = r_htm.exec_lines[PHY] + r_htm.data_lines[PHY];
				r_htm.SLOC_lines[LOG] = r_htm.exec_lines[LOG] + r_htm.data_lines[LOG];
				r_htm.total_lines = r_htm.SLOC_lines[PHY] +	r_htm.blank_lines + r_htm.comment_lines;

				r_jsc.SLOC_lines[PHY] = r_jsc.exec_lines[PHY] + r_jsc.data_lines[PHY];
				r_jsc.SLOC_lines[LOG] = r_jsc.exec_lines[LOG] + r_jsc.data_lines[LOG];
				r_jsc.total_lines = r_jsc.SLOC_lines[PHY] +	r_jsc.blank_lines + r_jsc.comment_lines;

				r_vbsc.SLOC_lines[PHY] = r_vbsc.exec_lines[PHY] + r_vbsc.data_lines[PHY];
				r_vbsc.SLOC_lines[LOG] = r_vbsc.exec_lines[LOG] + r_vbsc.data_lines[LOG];
				r_vbsc.total_lines = r_vbsc.SLOC_lines[PHY] +	r_vbsc.blank_lines + r_vbsc.comment_lines;

				r_jss.SLOC_lines[PHY] = r_jss.directive_lines[PHY] + r_jss.exec_lines[PHY] + r_jss.data_lines[PHY];
				r_jss.SLOC_lines[LOG] = r_jss.directive_lines[LOG] + r_jss.exec_lines[LOG] + r_jss.data_lines[LOG];
				r_jss.total_lines = r_jss.SLOC_lines[PHY] +	r_jss.blank_lines + r_jss.comment_lines;

				r_vbss.SLOC_lines[PHY] = r_vbss.exec_lines[PHY] + r_vbss.data_lines[PHY];
				r_vbss.SLOC_lines[LOG] = r_vbss.exec_lines[LOG] + r_vbss.data_lines[LOG];
				r_vbss.total_lines = r_vbss.SLOC_lines[PHY] +	r_vbss.blank_lines + r_vbss.comment_lines;

				r_css.SLOC_lines[PHY] = r_css.exec_lines[PHY] + r_css.data_lines[PHY];
				r_css.SLOC_lines[LOG] = r_css.exec_lines[LOG] + r_css.data_lines[LOG];
				r_css.total_lines = r_css.SLOC_lines[PHY] +	r_css.blank_lines + r_css.comment_lines;

				if (print_ascii || print_legacy)
				{
					(*pout).setf(ios::right);
					(*pout).width(8);		(*pout) << (r_htm.total_lines + r_jsc.total_lines + r_vbsc.total_lines + r_jss.total_lines + r_vbss.total_lines + r_css.total_lines);
					(*pout) << " ";
					(*pout).width(7);		(*pout) << (r_htm.blank_lines + r_jsc.blank_lines + r_vbsc.blank_lines + r_jss.blank_lines + r_vbss.blank_lines + r_css.blank_lines);
					(*pout) << " |";
					(*pout).width(8);		(*pout) << (r_htm.comment_lines + r_jsc.comment_lines + r_vbsc.comment_lines + r_jss.comment_lines + r_vbss.comment_lines + r_css.comment_lines);
					(*pout) << " ";
					(*pout).width(8);		(*pout) << (r_htm.e_comm_lines + r_jsc.e_comm_lines + r_vbsc.e_comm_lines + r_jss.e_comm_lines + r_vbss.e_comm_lines + r_css.e_comm_lines);
					(*pout) << " |";
					(*pout).width(8);		(*pout) << r_htm.data_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_htm.exec_lines[LOG];
					(*pout) << " |";
					(*pout).width(8);		(*pout) << r_jsc.data_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_jsc.exec_lines[LOG];
					(*pout) << " |";
					(*pout).width(8);		(*pout) << r_vbsc.data_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_vbsc.exec_lines[LOG];
					(*pout) << " |";
					(*pout).width(8);		(*pout) << r_jss.data_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_jss.exec_lines[LOG];
					(*pout) << " |";
					(*pout).width(8);		(*pout) << r_vbss.data_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_vbss.exec_lines[LOG];
					(*pout) << " |";
					(*pout).width(8);		(*pout) << r_css.data_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_css.exec_lines[LOG];
					if (print_legacy)
					{
						(*pout) << " |";
						(*pout).width(8);	(*pout) << (r_htm.SLOC_lines[LOG] + r_jsc.SLOC_lines[LOG] + r_vbsc.SLOC_lines[LOG] + r_jss.SLOC_lines[LOG] + r_vbss.SLOC_lines[LOG] + r_css.SLOC_lines[LOG]);
					}
					(*pout) << " |";
					(*pout).width(8);		(*pout) << r_htm.SLOC_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_jsc.SLOC_lines[LOG];
					(*pout) << " ";
					(*pout).width(8);		(*pout) << r_vbsc.SLOC_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_jss.SLOC_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_vbss.SLOC_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_css.SLOC_lines[LOG];
					if (!print_legacy)
					{
						(*pout) << " |";
						(*pout).width(8);	(*pout) << (r_htm.SLOC_lines[LOG] + r_jsc.SLOC_lines[LOG] + r_vbsc.SLOC_lines[LOG] + r_jss.SLOC_lines[LOG] + r_vbss.SLOC_lines[LOG] + r_css.SLOC_lines[LOG]);
						(*pout) << " |";
						(*pout).width(9);	(*pout) << (r_htm.SLOC_lines[PHY] + r_jsc.SLOC_lines[PHY] + r_vbsc.SLOC_lines[PHY] + r_jss.SLOC_lines[PHY] + r_vbss.SLOC_lines[PHY] + r_css.SLOC_lines[PHY]);
					}
					(*pout) << " | CODE  ";
					(*pout) << its->second.file_name<<endl;
					(*pout).unsetf(ios::right);
				}
				if (print_csv)
				{
					(*pout_csv) << (r_htm.total_lines + r_jsc.total_lines + r_vbsc.total_lines + r_jss.total_lines + r_vbss.total_lines + r_css.total_lines) << ",";
					(*pout_csv) << (r_htm.blank_lines + r_jsc.blank_lines + r_vbsc.blank_lines + r_jss.blank_lines + r_vbss.blank_lines + r_css.blank_lines) << ",";
					(*pout_csv) << (r_htm.comment_lines + r_jsc.comment_lines + r_vbsc.comment_lines + r_jss.comment_lines + r_vbss.comment_lines + r_css.comment_lines) << ",";
					(*pout_csv) << (r_htm.e_comm_lines + r_jsc.e_comm_lines + r_vbsc.e_comm_lines + r_jss.e_comm_lines + r_vbss.e_comm_lines + r_css.e_comm_lines) << ",";
					(*pout_csv) << r_htm.data_lines[LOG] << ",";
					(*pout_csv) << r_htm.exec_lines[LOG] << ",";
					(*pout_csv) << r_jsc.data_lines[LOG] << ",";
					(*pout_csv) << r_jsc.exec_lines[LOG] << ",";
					(*pout_csv) << r_vbsc.data_lines[LOG] << ",";
					(*pout_csv) << r_vbsc.exec_lines[LOG] << ",";
					(*pout_csv) << r_jss.data_lines[LOG] << ",";
					(*pout_csv) << r_jss.exec_lines[LOG] << ",";
					(*pout_csv) << r_vbss.data_lines[LOG] << ",";
					(*pout_csv) << r_vbss.exec_lines[LOG] << ",";
					(*pout_csv) << r_css.data_lines[LOG] << ",";
					(*pout_csv) << r_css.exec_lines[LOG] << ",";
					(*pout_csv) << r_htm.SLOC_lines[LOG] << ",";
					(*pout_csv) << r_jsc.SLOC_lines[LOG] << ",";
					(*pout_csv) << r_vbsc.SLOC_lines[LOG] << ",";
					(*pout_csv) << r_jss.SLOC_lines[LOG] << ",";
					(*pout_csv) << r_vbss.SLOC_lines[LOG] << ",";
					(*pout_csv) << r_css.SLOC_lines[LOG] << ",";
					(*pout_csv) << (r_htm.SLOC_lines[LOG] + r_jsc.SLOC_lines[LOG] + r_vbsc.SLOC_lines[LOG] + r_jss.SLOC_lines[LOG] + r_vbss.SLOC_lines[LOG] + r_css.SLOC_lines[LOG]) << ",";
					(*pout_csv) << (r_htm.SLOC_lines[PHY] + r_jsc.SLOC_lines[PHY] + r_vbsc.SLOC_lines[PHY] + r_jss.SLOC_lines[PHY] + r_vbss.SLOC_lines[PHY] + r_css.SLOC_lines[PHY]) << ",";
					(*pout_csv) << "CODE," << its->second.file_name << endl;
				}

				webtotal[webType].num_of_file++;

				webtotal[webType].total_line += (r_htm.total_lines + r_jsc.total_lines + r_vbsc.total_lines + r_jss.total_lines + r_vbss.total_lines + r_css.total_lines);
				webtotal[webType].blank_line += (r_htm.blank_lines + r_jsc.blank_lines + r_vbsc.blank_lines + r_jss.blank_lines + r_vbss.blank_lines + r_css.blank_lines);
				webtotal[webType].whole_comment += (r_htm.comment_lines + r_jsc.comment_lines + r_vbsc.comment_lines + r_jss.comment_lines + r_vbss.comment_lines + r_css.comment_lines);
				webtotal[webType].embed_comment += (r_htm.e_comm_lines + r_jsc.e_comm_lines + r_vbsc.e_comm_lines + r_jss.e_comm_lines + r_vbss.e_comm_lines + r_css.e_comm_lines);
				
				//0:htm 1:jsc 2:vbsc 3:jss 4:vbss 5:csharps
				webtotal[webType].phy_decl[0] += r_htm.data_lines[PHY];
				webtotal[webType].phy_instr[0] += r_htm.exec_lines[PHY];
				webtotal[webType].log_decl[0] += r_htm.data_lines[LOG];
				webtotal[webType].log_instr[0] += r_htm.exec_lines[LOG];

				webtotal[webType].phy_decl[1] += r_jsc.data_lines[PHY];
				webtotal[webType].phy_instr[1] += r_jsc.exec_lines[PHY];
				webtotal[webType].log_decl[1] += r_jsc.data_lines[LOG];
				webtotal[webType].log_instr[1] += r_jsc.exec_lines[LOG];

				webtotal[webType].phy_decl[2] += r_vbsc.data_lines[PHY];
				webtotal[webType].phy_instr[2] += r_vbsc.exec_lines[PHY];
				webtotal[webType].log_decl[2] += r_vbsc.data_lines[LOG];
				webtotal[webType].log_instr[2] += r_vbsc.exec_lines[LOG];

				webtotal[webType].phy_decl[3] += r_jss.data_lines[PHY];
				webtotal[webType].phy_instr[3] += r_jss.exec_lines[PHY];
				webtotal[webType].log_decl[3] += r_jss.data_lines[LOG];
				webtotal[webType].log_instr[3] += r_jss.exec_lines[LOG];

				webtotal[webType].phy_decl[4] += r_vbss.data_lines[PHY];
				webtotal[webType].phy_instr[4] += r_vbss.exec_lines[PHY];
				webtotal[webType].log_decl[4] += r_vbss.data_lines[LOG];
				webtotal[webType].log_instr[4] += r_vbss.exec_lines[LOG];

				webtotal[webType].phy_decl[5] += r_css.data_lines[PHY];
				webtotal[webType].phy_instr[5] += r_css.exec_lines[PHY];
				webtotal[webType].log_decl[5] += r_css.data_lines[LOG];
				webtotal[webType].log_instr[5] += r_css.exec_lines[LOG];
			}
			else if (webType == WEB_XML)
			{
				results r_xml;
				results r_js;
				results r_vbs;
				results r_cs;
				for (SourceFileList::iterator i = startpos; i!= endpos; i++)
				{
					switch (i->second.class_type)
					{
					case XML:
						r_xml = i->second;
						break;
					case JAVASCRIPT_XML:
						r_js = i->second;
						break;
					case VBS_XML:
						r_vbs = i->second;
						break;
					case CSHARP_XML:
						r_cs = i->second;
						break;
					}
				}
				r_xml.SLOC_lines[PHY] = r_xml.exec_lines[PHY] + r_xml.data_lines[PHY];
				r_xml.SLOC_lines[LOG] = r_xml.exec_lines[LOG] + r_xml.data_lines[LOG];
				r_xml.total_lines = r_xml.SLOC_lines[PHY] +	r_xml.blank_lines + r_xml.comment_lines;

				r_js.SLOC_lines[PHY] = r_js.exec_lines[PHY] + r_js.data_lines[PHY];
				r_js.SLOC_lines[LOG] = r_js.exec_lines[LOG] + r_js.data_lines[LOG];
				r_js.total_lines = r_js.SLOC_lines[PHY] +	r_js.blank_lines + r_js.comment_lines;

				r_vbs.SLOC_lines[PHY] = r_vbs.exec_lines[PHY] + r_vbs.data_lines[PHY];
				r_vbs.SLOC_lines[LOG] = r_vbs.exec_lines[LOG] + r_vbs.data_lines[LOG];
				r_vbs.total_lines = r_vbs.SLOC_lines[PHY] +	r_vbs.blank_lines + r_vbs.comment_lines;

				r_cs.SLOC_lines[PHY] = r_cs.exec_lines[PHY] + r_cs.data_lines[PHY];
				r_cs.SLOC_lines[LOG] = r_cs.exec_lines[LOG] + r_cs.data_lines[LOG];
				r_cs.total_lines = r_cs.SLOC_lines[PHY] +	r_cs.blank_lines + r_cs.comment_lines;

				if (print_ascii || print_legacy)
				{
					(*pout).setf(ios::right);
					(*pout).width(8);		(*pout) << (r_xml.total_lines + r_js.total_lines + r_vbs.total_lines + r_cs.total_lines);
					(*pout) << " ";
					(*pout).width(7);		(*pout) << (r_xml.blank_lines + r_js.blank_lines + r_vbs.blank_lines + r_cs.blank_lines);
					(*pout) << " |";
					(*pout).width(8);		(*pout) << (r_xml.comment_lines + r_js.comment_lines + r_vbs.comment_lines + r_cs.comment_lines);
					(*pout) << " ";
					(*pout).width(8);		(*pout) << (r_xml.e_comm_lines + r_js.e_comm_lines + r_vbs.e_comm_lines + r_cs.e_comm_lines);
					(*pout) << " |";
					(*pout).width(8);		(*pout) << r_xml.data_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_xml.exec_lines[LOG];
					(*pout) << " |";
					(*pout).width(8);		(*pout) << r_js.data_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_js.exec_lines[LOG];
					(*pout) << " |";
					(*pout).width(8);		(*pout) << r_vbs.data_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_vbs.exec_lines[LOG];
					(*pout) << " |";
					(*pout).width(8);		(*pout) << r_cs.data_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_cs.exec_lines[LOG];
					if (print_legacy)
					{
						(*pout) << " |";
						(*pout).width(8);	(*pout) << (r_xml.SLOC_lines[LOG] + r_js.SLOC_lines[LOG] + r_vbs.SLOC_lines[LOG] + r_cs.SLOC_lines[LOG]);
					}
					(*pout) << " |";
					(*pout).width(8);		(*pout) << r_xml.SLOC_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_js.SLOC_lines[LOG];
					(*pout) << " ";
					(*pout).width(8);		(*pout) << r_vbs.SLOC_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_cs.SLOC_lines[LOG];
					if (!print_legacy)
					{
						(*pout) << " |";
						(*pout).width(8);	(*pout) << (r_xml.SLOC_lines[LOG] + r_js.SLOC_lines[LOG] + r_vbs.SLOC_lines[LOG] + r_cs.SLOC_lines[LOG]);
						(*pout) << " |";
						(*pout).width(9);	(*pout) << (r_xml.SLOC_lines[PHY] + r_js.SLOC_lines[PHY] + r_vbs.SLOC_lines[PHY] + r_cs.SLOC_lines[PHY]);
					}
					(*pout) << " | CODE  ";
					(*pout) << its->second.file_name<<endl;
					(*pout).unsetf(ios::right);
				}
				if (print_csv)
				{
					(*pout_csv) << (r_xml.total_lines + r_js.total_lines + r_vbs.total_lines + r_cs.total_lines) << ",";
					(*pout_csv) << (r_xml.blank_lines + r_js.blank_lines + r_vbs.blank_lines + r_cs.blank_lines) << ",";
					(*pout_csv) << (r_xml.comment_lines + r_js.comment_lines + r_vbs.comment_lines + r_cs.comment_lines) << ",";
					(*pout_csv) << (r_xml.e_comm_lines + r_js.e_comm_lines + r_vbs.e_comm_lines + r_cs.e_comm_lines) << ",";
					(*pout_csv) << r_xml.data_lines[LOG] << ",";
					(*pout_csv) << r_xml.exec_lines[LOG] << ",";
					(*pout_csv) << r_js.data_lines[LOG] << ",";
					(*pout_csv) << r_js.exec_lines[LOG] << ",";
					(*pout_csv) << r_vbs.data_lines[LOG] << ",";
					(*pout_csv) << r_vbs.exec_lines[LOG] << ",";
					(*pout_csv) << r_cs.data_lines[LOG] << ",";
					(*pout_csv) << r_cs.exec_lines[LOG] << ",";
					(*pout_csv) << r_xml.SLOC_lines[LOG] << ",";
					(*pout_csv) << r_js.SLOC_lines[LOG] << ",";
					(*pout_csv) << r_vbs.SLOC_lines[LOG] << ",";
					(*pout_csv) << r_cs.SLOC_lines[LOG] << ",";
					(*pout_csv) << (r_xml.SLOC_lines[LOG] + r_js.SLOC_lines[LOG] + r_vbs.SLOC_lines[LOG] + r_cs.SLOC_lines[LOG]) << ",";
					(*pout_csv) << (r_xml.SLOC_lines[PHY] + r_js.SLOC_lines[PHY] + r_vbs.SLOC_lines[PHY] + r_cs.SLOC_lines[PHY]) << ",";
					(*pout_csv) << "CODE," << its->second.file_name << endl;
				}

				webtotal[webType].num_of_file++;

				webtotal[webType].total_line += (r_xml.total_lines + r_js.total_lines + r_vbs.total_lines + r_cs.total_lines);
				webtotal[webType].blank_line += (r_xml.blank_lines + r_js.blank_lines + r_vbs.blank_lines + r_cs.blank_lines);
				webtotal[webType].whole_comment += (r_xml.comment_lines + r_js.comment_lines + r_vbs.comment_lines + r_cs.comment_lines);
				webtotal[webType].embed_comment += (r_xml.e_comm_lines + r_js.e_comm_lines + r_vbs.e_comm_lines + r_cs.e_comm_lines);

				//0:xml 1:js 2:vbs 3:csharp
				webtotal[webType].phy_decl[0] += r_xml.data_lines[PHY];
				webtotal[webType].phy_instr[0] += r_xml.exec_lines[PHY];
				webtotal[webType].log_decl[0] += r_xml.data_lines[LOG];
				webtotal[webType].log_instr[0] += r_xml.exec_lines[LOG];

				webtotal[webType].phy_decl[1] += r_js.data_lines[PHY];
				webtotal[webType].phy_instr[1] += r_js.exec_lines[PHY];
				webtotal[webType].log_decl[1] += r_js.data_lines[LOG];
				webtotal[webType].log_instr[1] += r_js.exec_lines[LOG];

				webtotal[webType].phy_decl[2] += r_vbs.data_lines[PHY];
				webtotal[webType].phy_instr[2] += r_vbs.exec_lines[PHY];
				webtotal[webType].log_decl[2] += r_vbs.data_lines[LOG];
				webtotal[webType].log_instr[2] += r_vbs.exec_lines[LOG];

				webtotal[webType].phy_decl[3] += r_cs.data_lines[PHY];
				webtotal[webType].phy_instr[3] += r_cs.exec_lines[PHY];
				webtotal[webType].log_decl[3] += r_cs.data_lines[LOG];
				webtotal[webType].log_instr[3] += r_cs.exec_lines[LOG];
			}
			else if (webType == WEB_CFM)
			{
				results r_htm;
				results r_js;
				results r_vbs;
				results r_sql;
				results r_cfm;
				results r_cfs;
				for (SourceFileList::iterator i = startpos; i!= endpos; i++)
				{
					switch (i->second.class_type)
					{
					case HTML_CFM:
						r_htm = i->second;
						break;
					case JAVASCRIPT_CFM:
						r_js = i->second;
						break;
					case VBS_CFM:
						r_vbs = i->second;
						break;
					case SQL_CFM:
						r_sql = i->second;
						break;
					case COLDFUSION:
						r_cfm = i->second;
						break;
					case CFSCRIPT:
						r_cfs = i->second;
						break;
					}
				}
				r_htm.SLOC_lines[PHY] = r_htm.exec_lines[PHY] + r_htm.data_lines[PHY];
				r_htm.SLOC_lines[LOG] = r_htm.exec_lines[LOG] + r_htm.data_lines[LOG];
				r_htm.total_lines = r_htm.SLOC_lines[PHY] +	r_htm.blank_lines + r_htm.comment_lines;

				r_js.SLOC_lines[PHY] = r_js.exec_lines[PHY] + r_js.data_lines[PHY];
				r_js.SLOC_lines[LOG] = r_js.exec_lines[LOG] + r_js.data_lines[LOG];
				r_js.total_lines = r_js.SLOC_lines[PHY] +	r_js.blank_lines + r_js.comment_lines;

				r_vbs.SLOC_lines[PHY] = r_vbs.exec_lines[PHY] + r_vbs.data_lines[PHY];
				r_vbs.SLOC_lines[LOG] = r_vbs.exec_lines[LOG] + r_vbs.data_lines[LOG];
				r_vbs.total_lines = r_vbs.SLOC_lines[PHY] +	r_vbs.blank_lines + r_vbs.comment_lines;

				r_sql.SLOC_lines[PHY] = r_sql.exec_lines[PHY] + r_sql.data_lines[PHY];
				r_sql.SLOC_lines[LOG] = r_sql.exec_lines[LOG] + r_sql.data_lines[LOG];
				r_sql.total_lines = r_sql.SLOC_lines[PHY] +	r_sql.blank_lines + r_sql.comment_lines;

				r_cfm.SLOC_lines[PHY] = r_cfm.exec_lines[PHY] + r_cfm.data_lines[PHY];
				r_cfm.SLOC_lines[LOG] = r_cfm.exec_lines[LOG] + r_cfm.data_lines[LOG];
				r_cfm.total_lines = r_cfm.SLOC_lines[PHY] +	r_cfm.blank_lines + r_cfm.comment_lines;

				r_cfs.SLOC_lines[PHY] = r_cfs.exec_lines[PHY] + r_cfs.data_lines[PHY];
				r_cfs.SLOC_lines[LOG] = r_cfs.exec_lines[LOG] + r_cfs.data_lines[LOG];
				r_cfs.total_lines = r_cfs.SLOC_lines[PHY] +	r_cfs.blank_lines + r_cfs.comment_lines;

				if (print_ascii || print_legacy)
				{
					(*pout).setf(ios::right);
					(*pout).width(8);		(*pout) << (r_htm.total_lines + r_js.total_lines + r_vbs.total_lines + r_sql.total_lines + r_cfm.total_lines + r_cfs.total_lines);
					(*pout) << " ";
					(*pout).width(7);		(*pout) << (r_htm.blank_lines + r_js.blank_lines + r_vbs.blank_lines + r_sql.blank_lines + r_cfm.blank_lines + r_cfs.blank_lines);
					(*pout) << " |";
					(*pout).width(8);		(*pout) << (r_htm.comment_lines + r_js.comment_lines + r_vbs.comment_lines + r_sql.comment_lines + r_cfm.comment_lines + r_cfs.comment_lines);
					(*pout) << " ";
					(*pout).width(8);		(*pout) << (r_htm.e_comm_lines + r_js.e_comm_lines + r_vbs.e_comm_lines + r_sql.e_comm_lines + r_cfm.e_comm_lines + r_cfs.e_comm_lines);
					(*pout) << " |";
					(*pout).width(8);		(*pout) << r_htm.data_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_htm.exec_lines[LOG];
					(*pout) << " |";
					(*pout).width(8);		(*pout) << r_js.data_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_js.exec_lines[LOG];
					(*pout) << " |";
					(*pout).width(8);		(*pout) << r_vbs.data_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_vbs.exec_lines[LOG];
					(*pout) << " |";
					(*pout).width(8);		(*pout) << r_sql.data_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_sql.exec_lines[LOG];
					(*pout) << " |";
					(*pout).width(8);		(*pout) << r_cfm.data_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_cfm.exec_lines[LOG];
					(*pout) << " |";
					(*pout).width(8);		(*pout) << r_cfs.data_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_cfs.exec_lines[LOG];
					if (print_legacy)
					{
						(*pout) << " |";
						(*pout).width(8);	(*pout) << (r_htm.SLOC_lines[LOG] + r_js.SLOC_lines[LOG] + r_vbs.SLOC_lines[LOG] + r_sql.SLOC_lines[LOG] + r_cfm.SLOC_lines[LOG] + r_cfs.SLOC_lines[LOG]);
					}
					(*pout) << " |";
					(*pout).width(8);		(*pout) << r_htm.SLOC_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_js.SLOC_lines[LOG];
					(*pout) << " ";
					(*pout).width(8);		(*pout) << r_vbs.SLOC_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_sql.SLOC_lines[LOG];
					(*pout) << " ";
					(*pout).width(10);		(*pout) << r_cfm.SLOC_lines[LOG];
					(*pout) << " ";
					(*pout).width(8);		(*pout) << r_cfs.SLOC_lines[LOG];
					if (!print_legacy)
					{
						(*pout) << " |";
						(*pout).width(8);	(*pout) << (r_htm.SLOC_lines[LOG] + r_js.SLOC_lines[LOG] + r_vbs.SLOC_lines[LOG] + r_sql.SLOC_lines[LOG] + r_cfm.SLOC_lines[LOG] + r_cfs.SLOC_lines[LOG]);
						(*pout) << " |";
						(*pout).width(9);	(*pout) << (r_htm.SLOC_lines[PHY] + r_js.SLOC_lines[PHY] + r_vbs.SLOC_lines[PHY] + r_sql.SLOC_lines[PHY] + r_cfm.SLOC_lines[PHY] + r_cfs.SLOC_lines[PHY]);
					}
					(*pout) << " | CODE  ";
					(*pout) << its->second.file_name<<endl;
					(*pout).unsetf(ios::right);
				}
				if (print_csv)
				{
					(*pout_csv) << (r_htm.total_lines + r_js.total_lines + r_vbs.total_lines + r_sql.total_lines + r_cfm.total_lines + r_cfs.total_lines) << ",";
					(*pout_csv) << (r_htm.blank_lines + r_js.blank_lines + r_vbs.blank_lines + r_sql.blank_lines + r_cfm.blank_lines + r_cfs.blank_lines) << ",";
					(*pout_csv) << (r_htm.comment_lines + r_js.comment_lines + r_vbs.comment_lines + r_sql.comment_lines + r_cfm.comment_lines + r_cfs.comment_lines) << ",";
					(*pout_csv) << (r_htm.e_comm_lines + r_js.e_comm_lines + r_vbs.e_comm_lines + r_sql.e_comm_lines + r_cfm.e_comm_lines + r_cfs.e_comm_lines) << ",";
					(*pout_csv) << r_htm.data_lines[LOG] << ",";
					(*pout_csv) << r_htm.exec_lines[LOG] << ",";
					(*pout_csv) << r_js.data_lines[LOG] << ",";
					(*pout_csv) << r_js.exec_lines[LOG] << ",";
					(*pout_csv) << r_vbs.data_lines[LOG] << ",";
					(*pout_csv) << r_vbs.exec_lines[LOG] << ",";
					(*pout_csv) << r_sql.data_lines[LOG] << ",";
					(*pout_csv) << r_sql.exec_lines[LOG] << ",";
					(*pout_csv) << r_cfm.data_lines[LOG] << ",";
					(*pout_csv) << r_cfm.exec_lines[LOG] << ",";
					(*pout_csv) << r_cfs.data_lines[LOG] << ",";
					(*pout_csv) << r_cfs.exec_lines[LOG] << ",";
					(*pout_csv) << r_htm.SLOC_lines[LOG] << ",";
					(*pout_csv) << r_js.SLOC_lines[LOG] << ",";
					(*pout_csv) << r_vbs.SLOC_lines[LOG] << ",";
					(*pout_csv) << r_sql.SLOC_lines[LOG] << ",";
					(*pout_csv) << r_cfm.SLOC_lines[LOG] << ",";
					(*pout_csv) << r_cfs.SLOC_lines[LOG] << ",";
					(*pout_csv) << (r_htm.SLOC_lines[LOG] + r_js.SLOC_lines[LOG] + r_vbs.SLOC_lines[LOG] + r_sql.SLOC_lines[LOG] + r_cfm.SLOC_lines[LOG] + r_cfs.SLOC_lines[LOG]) << ",";
					(*pout_csv) << (r_htm.SLOC_lines[PHY] + r_js.SLOC_lines[PHY] + r_vbs.SLOC_lines[PHY] + r_sql.SLOC_lines[PHY] + r_cfm.SLOC_lines[PHY] + r_cfs.SLOC_lines[PHY]) << ",";
					(*pout_csv) << "CODE," << its->second.file_name << endl;
				}

				webtotal[webType].num_of_file++;

				webtotal[webType].total_line += (r_htm.total_lines + r_js.total_lines + r_vbs.total_lines + r_sql.total_lines + r_cfm.total_lines + r_cfs.total_lines);
				webtotal[webType].blank_line += (r_htm.blank_lines + r_js.blank_lines + r_vbs.blank_lines + r_sql.blank_lines + r_cfm.blank_lines + r_cfs.blank_lines);
				webtotal[webType].whole_comment += (r_htm.comment_lines + r_js.comment_lines + r_vbs.comment_lines + r_sql.comment_lines + r_cfm.comment_lines + r_cfs.comment_lines);
				webtotal[webType].embed_comment += (r_htm.e_comm_lines + r_js.e_comm_lines + r_vbs.e_comm_lines + r_sql.e_comm_lines + r_cfm.e_comm_lines + r_cfs.e_comm_lines);

				//0:htm 1:js 2:vbs 3:sql 5:cfm 6:cfs
				webtotal[webType].phy_decl[0] += r_htm.data_lines[PHY];
				webtotal[webType].phy_instr[0] += r_htm.exec_lines[PHY];
				webtotal[webType].log_decl[0] += r_htm.data_lines[LOG];
				webtotal[webType].log_instr[0] += r_htm.exec_lines[LOG];

				webtotal[webType].phy_decl[1] += r_js.data_lines[PHY];
				webtotal[webType].phy_instr[1] += r_js.exec_lines[PHY];
				webtotal[webType].log_decl[1] += r_js.data_lines[LOG];
				webtotal[webType].log_instr[1] += r_js.exec_lines[LOG];

				webtotal[webType].phy_decl[2] += r_vbs.data_lines[PHY];
				webtotal[webType].phy_instr[2] += r_vbs.exec_lines[PHY];
				webtotal[webType].log_decl[2] += r_vbs.data_lines[LOG];
				webtotal[webType].log_instr[2] += r_vbs.exec_lines[LOG];

				webtotal[webType].phy_decl[3] += r_sql.data_lines[PHY];
				webtotal[webType].phy_instr[3] += r_sql.exec_lines[PHY];
				webtotal[webType].log_decl[3] += r_sql.data_lines[LOG];
				webtotal[webType].log_instr[3] += r_sql.exec_lines[LOG];

				webtotal[webType].phy_decl[4] += r_cfm.data_lines[PHY];
				webtotal[webType].phy_instr[4] += r_cfm.exec_lines[PHY];
				webtotal[webType].log_decl[4] += r_cfm.data_lines[LOG];
				webtotal[webType].log_instr[4] += r_cfm.exec_lines[LOG];

				webtotal[webType].phy_decl[5] += r_cfs.data_lines[PHY];
				webtotal[webType].phy_instr[5] += r_cfs.exec_lines[PHY];
				webtotal[webType].log_decl[5] += r_cfs.data_lines[LOG];
				webtotal[webType].log_instr[5] += r_cfs.exec_lines[LOG];
			}
			else
			{
				webType = WEB_HTM;
				results r_htm;
				results r_js;
				results r_vbs;
				results r_cs;
				for (SourceFileList::iterator i = startpos; i!= endpos; i++)
				{
					switch (i->second.class_type)
					{
					case HTML:
						r_htm = i->second;
						break;
					case JAVASCRIPT_HTML:
						r_js = i->second;
						break;
					case VBS_HTML:
						r_vbs = i->second;
						break;
					case CSHARP_HTML:
						r_cs = i->second;
						break;
					}
				}
				r_htm.SLOC_lines[PHY] = r_htm.exec_lines[PHY] + r_htm.data_lines[PHY];
				r_htm.SLOC_lines[LOG] = r_htm.exec_lines[LOG] + r_htm.data_lines[LOG];
				r_htm.total_lines = r_htm.SLOC_lines[PHY] +	r_htm.blank_lines + r_htm.comment_lines;

				r_js.SLOC_lines[PHY] = r_js.exec_lines[PHY] + r_js.data_lines[PHY];
				r_js.SLOC_lines[LOG] = r_js.exec_lines[LOG] + r_js.data_lines[LOG];
				r_js.total_lines = r_js.SLOC_lines[PHY] +	r_js.blank_lines + r_js.comment_lines;

				r_vbs.SLOC_lines[PHY] = r_vbs.exec_lines[PHY] + r_vbs.data_lines[PHY];
				r_vbs.SLOC_lines[LOG] = r_vbs.exec_lines[LOG] + r_vbs.data_lines[LOG];
				r_vbs.total_lines = r_vbs.SLOC_lines[PHY] +	r_vbs.blank_lines + r_vbs.comment_lines;

				r_cs.SLOC_lines[PHY] = r_cs.exec_lines[PHY] + r_cs.data_lines[PHY];
				r_cs.SLOC_lines[LOG] = r_cs.exec_lines[LOG] + r_cs.data_lines[LOG];
				r_cs.total_lines = r_cs.SLOC_lines[PHY] +	r_cs.blank_lines + r_cs.comment_lines;

				if (print_ascii || print_legacy)
				{
					(*pout).setf(ios::right);
					(*pout).width(8);		(*pout) << (r_htm.total_lines + r_js.total_lines + r_vbs.total_lines + r_cs.total_lines);
					(*pout) << " ";
					(*pout).width(7);		(*pout) << (r_htm.blank_lines + r_js.blank_lines + r_vbs.blank_lines + r_cs.blank_lines);
					(*pout) << " |";
					(*pout).width(8);		(*pout) << (r_htm.comment_lines + r_js.comment_lines + r_vbs.comment_lines + r_cs.comment_lines);
					(*pout) << " ";
					(*pout).width(8);		(*pout) << (r_htm.e_comm_lines + r_js.e_comm_lines + r_vbs.e_comm_lines + r_cs.e_comm_lines);
					(*pout) << " |";
					(*pout).width(8);		(*pout) << r_htm.data_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_htm.exec_lines[LOG];
					(*pout) << " |";
					(*pout).width(8);		(*pout) << r_js.data_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_js.exec_lines[LOG];
					(*pout) << " |";
					(*pout).width(8);		(*pout) << r_vbs.data_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_vbs.exec_lines[LOG];
					(*pout) << " |";
					(*pout).width(8);		(*pout) << r_cs.data_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_cs.exec_lines[LOG];
					if (print_legacy)
					{
						(*pout) << " |";
						(*pout).width(8);	(*pout) << (r_htm.SLOC_lines[LOG] + r_js.SLOC_lines[LOG] + r_vbs.SLOC_lines[LOG] + r_cs.SLOC_lines[LOG]);
					}
					(*pout) << " |";
					(*pout).width(8);		(*pout) << r_htm.SLOC_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_js.SLOC_lines[LOG];
					(*pout) << " ";
					(*pout).width(8);		(*pout) << r_vbs.SLOC_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_cs.SLOC_lines[LOG];
					if (!print_legacy)
					{
						(*pout) << " |";
						(*pout).width(8);	(*pout) << (r_htm.SLOC_lines[LOG] + r_js.SLOC_lines[LOG] + r_vbs.SLOC_lines[LOG] + r_cs.SLOC_lines[LOG]);
						(*pout) << " |";
						(*pout).width(9);	(*pout) << (r_htm.SLOC_lines[PHY] + r_js.SLOC_lines[PHY] + r_vbs.SLOC_lines[PHY] + r_cs.SLOC_lines[PHY]);
					}
					(*pout) << " | CODE  ";
					(*pout) << its->second.file_name<<endl;
					(*pout).unsetf(ios::right);
				}
				if (print_csv)
				{
					(*pout_csv) << (r_htm.total_lines + r_js.total_lines + r_vbs.total_lines + r_cs.total_lines) << ",";
					(*pout_csv) << (r_htm.blank_lines + r_js.blank_lines + r_vbs.blank_lines + r_cs.blank_lines) << ",";
					(*pout_csv) << (r_htm.comment_lines + r_js.comment_lines + r_vbs.comment_lines + r_cs.comment_lines) << ",";
					(*pout_csv) << (r_htm.e_comm_lines + r_js.e_comm_lines + r_vbs.e_comm_lines + r_cs.e_comm_lines) << ",";
					(*pout_csv) << r_htm.data_lines[LOG] << ",";
					(*pout_csv) << r_htm.exec_lines[LOG] << ",";
					(*pout_csv) << r_js.data_lines[LOG] << ",";
					(*pout_csv) << r_js.exec_lines[LOG] << ",";
					(*pout_csv) << r_vbs.data_lines[LOG] << ",";
					(*pout_csv) << r_vbs.exec_lines[LOG] << ",";
					(*pout_csv) << r_cs.data_lines[LOG] << ",";
					(*pout_csv) << r_cs.exec_lines[LOG] << ",";
					(*pout_csv) << r_htm.SLOC_lines[LOG] << ",";
					(*pout_csv) << r_js.SLOC_lines[LOG] << ",";
					(*pout_csv) << r_vbs.SLOC_lines[LOG] << ",";
					(*pout_csv) << r_cs.SLOC_lines[LOG] << ",";
					(*pout_csv) << (r_htm.SLOC_lines[LOG] + r_js.SLOC_lines[LOG] + r_vbs.SLOC_lines[LOG] + r_cs.SLOC_lines[LOG]) << ",";
					(*pout_csv) << (r_htm.SLOC_lines[PHY] + r_js.SLOC_lines[PHY] + r_vbs.SLOC_lines[PHY] + r_cs.SLOC_lines[PHY]) << ",";
					(*pout_csv) << "CODE," << its->second.file_name << endl;
				}

				webtotal[webType].num_of_file++;

				webtotal[webType].total_line += (r_htm.total_lines + r_js.total_lines + r_vbs.total_lines + r_cs.total_lines);
				webtotal[webType].blank_line += (r_htm.blank_lines + r_js.blank_lines + r_vbs.blank_lines + r_cs.blank_lines);
				webtotal[webType].whole_comment += (r_htm.comment_lines + r_js.comment_lines + r_vbs.comment_lines + r_cs.comment_lines);
				webtotal[webType].embed_comment += (r_htm.e_comm_lines + r_js.e_comm_lines + r_vbs.e_comm_lines + r_cs.e_comm_lines);
				
				//0:htm 1:js 2:vbs 3:csharp
				webtotal[webType].phy_decl[0] += r_htm.data_lines[PHY];
				webtotal[webType].phy_instr[0] += r_htm.exec_lines[PHY];
				webtotal[webType].log_decl[0] += r_htm.data_lines[LOG];
				webtotal[webType].log_instr[0] += r_htm.exec_lines[LOG];

				webtotal[webType].phy_decl[1] += r_js.data_lines[PHY];
				webtotal[webType].phy_instr[1] += r_js.exec_lines[PHY];
				webtotal[webType].log_decl[1] += r_js.data_lines[LOG];
				webtotal[webType].log_instr[1] += r_js.exec_lines[LOG];

				webtotal[webType].phy_decl[2] += r_vbs.data_lines[PHY];
				webtotal[webType].phy_instr[2] += r_vbs.exec_lines[PHY];
				webtotal[webType].log_decl[2] += r_vbs.data_lines[LOG];
				webtotal[webType].log_instr[2] += r_vbs.exec_lines[LOG];

				webtotal[webType].phy_decl[3] += r_cs.data_lines[PHY];
				webtotal[webType].phy_instr[3] += r_cs.exec_lines[PHY];
				webtotal[webType].log_decl[3] += r_cs.data_lines[LOG];
				webtotal[webType].log_instr[3] += r_cs.exec_lines[LOG];
			}

			// skip the other web language partial file
			its = --endpos;
		}
		else // languages other than WEB
		{
			class_type = its->second.class_type;

			// do not print temp files that are created to represent embedded code
			if (its->second.file_name.find(EMBEDDED_FILE_PREFIX) != string::npos) 
				continue;

			if (print_ascii || print_legacy)
			{
				pout = CounterForEachLanguage[class_type]->GetOutputStream(outDir + outputFileNamePrePend, cmdLine);
				if (pout == NULL)
				{
					string err = "Error: Unable to create file (";
					err += outputFileNamePrePend + CounterForEachLanguage[class_type]->language_name + OUTPUT_FILE_NAME;
					err += "). Operation aborted.";
					cout << endl << err << endl;
					CUtil::AddError(err);
					return 0;
				}
			}
			if (print_csv)
			{
				pout_csv = CounterForEachLanguage[class_type]->GetOutputStream(outDir + outputFileNamePrePend, cmdLine, true);
				if (pout_csv == NULL)
				{
					string err = "Error: Unable to create file (";
					err += outputFileNamePrePend + CounterForEachLanguage[class_type]->language_name + OUTPUT_FILE_NAME_CSV;
					err += "). Operation aborted.";
					cout << endl << err << endl;
					CUtil::AddError(err);
					return 0;
				}
			}

			if (total.count(class_type) == 0)
				total.insert(TotalValueMap::value_type(class_type, TotalValue()));

			if (its->second.e_flag)
			{
				if (print_ascii || print_legacy)
				{
					(*pout).setf(ios::left);
					(*pout) << " Error: ";
					(*pout).width(65);
					(*pout) << its->second.error_code;
					(*pout) << its->second.file_name << endl << endl;
					(*pout).unsetf(ios::left);
				}
				if (print_csv)
				{
					(*pout_csv) << "Error: ";
					(*pout_csv) << its->second.error_code << ",,,,,,,,,";
					(*pout_csv) << its->second.file_name << endl << endl;
				}
				continue;
			}
			else
			{
				its->second.SLOC_lines[PHY] = its->second.directive_lines[PHY] + its->second.exec_lines[PHY] + its->second.data_lines[PHY];
				its->second.SLOC_lines[LOG] = its->second.directive_lines[LOG] + its->second.exec_lines[LOG] + its->second.data_lines[LOG];
				its->second.total_lines = its->second.SLOC_lines[PHY] +	its->second.blank_lines + its->second.comment_lines;
			}

			total[class_type].num_of_file++;

			if (print_ascii || print_legacy)
			{
				(*pout).setf(ios::right);
				(*pout).width(8);		(*pout) << its->second.total_lines;
				(*pout) << " ";
				(*pout).width(7);		(*pout) << its->second.blank_lines;
				(*pout) << " |";
				(*pout).width(8);		(*pout) << its->second.comment_lines;
				(*pout) << " ";
				(*pout).width(8);		(*pout) << its->second.e_comm_lines;
				(*pout) << " |";
				(*pout).width(8);		(*pout) << its->second.directive_lines[LOG];
				(*pout) << " ";
				(*pout).width(7);		(*pout) << its->second.data_lines[LOG];
				(*pout) << " ";
				(*pout).width(7);		(*pout) << its->second.exec_lines[LOG];
				(*pout) << " |";
				(*pout).width(8);	(*pout) << its->second.SLOC_lines[LOG];
				if (!print_legacy)
				{
					(*pout) << " ";
					(*pout).width(8);	(*pout) << its->second.SLOC_lines[PHY];
				}
				(*pout) << (class_type != UNKNOWN && class_type != DATAFILE ? " | CODE" : " | DATA");
				(*pout) << "  " << its->second.file_name;
				(*pout) << endl;
				(*pout).unsetf(ios::right);
			}
			if (print_csv)
			{
				(*pout_csv) << its->second.total_lines << ",";
				(*pout_csv) << its->second.blank_lines << ",";
				(*pout_csv) << its->second.comment_lines << ",";
				(*pout_csv) << its->second.e_comm_lines << ",";
				(*pout_csv) << its->second.directive_lines[LOG] << ",";
				(*pout_csv) << its->second.data_lines[LOG] << ",";
				(*pout_csv) << its->second.exec_lines[LOG] << ",";
				(*pout_csv) << its->second.SLOC_lines[LOG] << ",";
				(*pout_csv) << its->second.SLOC_lines[PHY] << ",";
				(*pout_csv) << (class_type != UNKNOWN && class_type != DATAFILE ? "CODE" : "DATA") << ",";
				(*pout_csv) << its->second.file_name << endl;
			}

			// total count for physical lines
			total[class_type].total_line += its->second.total_lines;
			total[class_type].blank_line += its->second.blank_lines;
			total[class_type].whole_comment += its->second.comment_lines;
			total[class_type].embed_comment += its->second.e_comm_lines;
			total[class_type].phy_direct += its->second.directive_lines[PHY];
			total[class_type].phy_decl += its->second.data_lines[PHY];
			total[class_type].phy_instr += its->second.exec_lines[PHY];
			total[class_type].log_direct += its->second.directive_lines[LOG];
			total[class_type].log_decl += its->second.data_lines[LOG];
			total[class_type].log_instr += its->second.exec_lines[LOG];
		}
	}

	// display summary for WEB languages
	for (WebTotalValueMap::iterator itto = webtotal.begin(); itto != webtotal.end(); itto++)
	{
		webCounter = (CWebCounter*)CounterForEachLanguage[WEB];
		if (itto->first == WEB_PHP)
		{
			if (print_ascii || print_legacy)
			{
				pout = webCounter->GetOutputStream(WEB_PHP, outDir + outputFileNamePrePend, cmdLine);

				(*pout) << endl;
				CUtil::PrintFileHeaderLine(*pout, "RESULTS SUMMARY");
				(*pout) << endl;
				(*pout) << "                                    |       HTML      |     JS-Clnt     |    VBS-Clnt     |           PHP           |" << endl;
				if (print_legacy)
				{
					(*pout) << "   Total   Blank |      Comments    |    Word  Exec.  |   Data   Exec.  |   Data   Exec.  | Compiler  Data   Exec.  |                    SLOC                    | File  SLOC" << endl;
					(*pout) << "   Lines   Lines |   Whole Embedded |     LOC  Instr. |   Decl.  Instr. |   Decl.  Instr. | Direct.   Decl.  Instr. |   Total      HTML JS-Clnt VBS-Clnt     PHP | Type  Definition" << endl;
					(*pout) << "-----------------+------------------+-----------------+-----------------+-----------------+-------------------------+---------+----------------------------------+------------------" << endl;
				}
				else
				{
					(*pout) << "   Total   Blank |      Comments    |    Word  Exec.  |   Data   Exec.  |   Data   Exec.  | Compiler  Data   Exec.  |                    SLOC                    | File  SLOC" << endl;
					(*pout) << "   Lines   Lines |   Whole Embedded |     LOC  Instr. |   Decl.  Instr. |   Decl.  Instr. | Direct.   Decl.  Instr. |    HTML JS-Clnt VBS-Clnt     PHP     Total | Type  Definition" << endl;
					(*pout) << "-----------------+------------------+-----------------+-----------------+-----------------+-------------------------+----------------------------------+---------+------------------" << endl;
				}

				(*pout).setf(ios::right);
				(*pout).width(8);		(*pout) << itto->second.total_line;
				(*pout) << " ";
				(*pout).width(7);		(*pout) << itto->second.blank_line;
				(*pout) << " |";
				(*pout).width(8);		(*pout) << itto->second.whole_comment;
				(*pout) << " ";
				(*pout).width(8);		(*pout) << itto->second.embed_comment;
				(*pout) << " |";
				(*pout).width(8);		(*pout) << itto->second.phy_decl[0];
				(*pout) << " ";
				(*pout).width(7);		(*pout) << itto->second.phy_instr[0];
				(*pout) << " |";
				(*pout).width(8);		(*pout) << itto->second.phy_decl[1];
				(*pout) << " ";
				(*pout).width(7);		(*pout) << itto->second.phy_instr[1];
				(*pout) << " |";
				(*pout).width(8);		(*pout) << itto->second.phy_decl[2];
				(*pout) << " ";
				(*pout).width(7);		(*pout) << itto->second.phy_instr[2];
				(*pout) << " |";
				(*pout).width(8);		(*pout) << itto->second.phy_direct[3];
				(*pout) << " ";
				(*pout).width(7);		(*pout) << itto->second.phy_decl[3];
				(*pout) << " ";
				(*pout).width(7);		(*pout) << itto->second.phy_instr[3];
				if (print_legacy)
				{
					(*pout) << " |";
					(*pout).width(8);	(*pout) << (itto->second.phy_decl[0] + itto->second.phy_instr[0] +
						itto->second.phy_decl[1] + itto->second.phy_instr[1] +
						itto->second.phy_decl[2] + itto->second.phy_instr[2] +
						itto->second.phy_direct[3] + itto->second.phy_decl[3] + itto->second.phy_instr[3]);
				}
				(*pout) << " |";
				(*pout).width(8);		(*pout) << (itto->second.phy_decl[0] + itto->second.phy_instr[0]);
				(*pout) << " ";
				(*pout).width(7);		(*pout) << (itto->second.phy_decl[1] + itto->second.phy_instr[1]);
				(*pout) << " ";
				(*pout).width(8);		(*pout) << (itto->second.phy_decl[2] + itto->second.phy_instr[2]);
				(*pout) << " ";
				(*pout).width(7);		(*pout) << (itto->second.phy_direct[3] + itto->second.phy_decl[3] + itto->second.phy_instr[3]);
				if (!print_legacy)
				{
					(*pout) << " |";
					(*pout).width(8);	(*pout) << (itto->second.phy_decl[0] + itto->second.phy_instr[0] +
						itto->second.phy_decl[1] + itto->second.phy_instr[1] +
						itto->second.phy_decl[2] + itto->second.phy_instr[2] +
						itto->second.phy_direct[3] + itto->second.phy_decl[3] + itto->second.phy_instr[3]);
				}
				(*pout) << " | CODE  Physical"<<endl;

				(*pout).setf(ios::right);
				(*pout).width(8);		(*pout) << itto->second.total_line;
				(*pout) << " ";
				(*pout).width(7);		(*pout) << itto->second.blank_line;
				(*pout) << " |";
				(*pout).width(8);		(*pout) << itto->second.whole_comment;
				(*pout) << " ";
				(*pout).width(8);		(*pout) << itto->second.embed_comment;
				(*pout) << " |";
				(*pout).width(8);		(*pout) << itto->second.log_decl[0];
				(*pout) << " ";
				(*pout).width(7);		(*pout) << itto->second.log_instr[0];
				(*pout) << " |";
				(*pout).width(8);		(*pout) << itto->second.log_decl[1];
				(*pout) << " ";
				(*pout).width(7);		(*pout) << itto->second.log_instr[1];
				(*pout) << " |";
				(*pout).width(8);		(*pout) << itto->second.log_decl[2];
				(*pout) << " ";
				(*pout).width(7);		(*pout) << itto->second.log_instr[2];
				(*pout) << " |";
				(*pout).width(8);		(*pout) << itto->second.log_direct[3];
				(*pout) << " ";
				(*pout).width(7);		(*pout) << itto->second.log_decl[3];
				(*pout) << " ";
				(*pout).width(7);		(*pout) << itto->second.log_instr[3];
				if (print_legacy)
				{
					(*pout) << " |";
					(*pout).width(8);	(*pout) << (itto->second.log_decl[0] + itto->second.log_instr[0] +
						itto->second.log_decl[1] + itto->second.log_instr[1] +
						itto->second.log_decl[2] + itto->second.log_instr[2] +
						itto->second.log_direct[3] + itto->second.log_decl[3] + itto->second.log_instr[3]);
				}
				(*pout) << " |";
				(*pout).width(8);		(*pout) << (itto->second.log_decl[0] + itto->second.log_instr[0]);
				(*pout) << " ";
				(*pout).width(7);		(*pout) << (itto->second.log_decl[1] + itto->second.log_instr[1]);
				(*pout) << " ";
				(*pout).width(8);		(*pout) << (itto->second.log_decl[2] + itto->second.log_instr[2]);
				(*pout) << " ";
				(*pout).width(7);		(*pout) << (itto->second.log_direct[3] + itto->second.log_decl[3] + itto->second.log_instr[3]);
				if (!print_legacy)
				{
					(*pout) << " |";
					(*pout).width(8);	(*pout) << (itto->second.log_decl[0] + itto->second.log_instr[0] +
						itto->second.log_decl[1] + itto->second.log_instr[1] +
						itto->second.log_decl[2] + itto->second.log_instr[2] +
						itto->second.log_direct[3] + itto->second.log_decl[3] + itto->second.log_instr[3]);
				}
				(*pout) << " | CODE  Logical" << endl;
			}
			if (print_csv)
			{
				pout_csv = webCounter->GetOutputStream(WEB_PHP, outDir + outputFileNamePrePend, cmdLine, true);

				(*pout_csv) << endl;
				CUtil::PrintFileHeaderLine(*pout_csv, "RESULTS SUMMARY");
				(*pout_csv) << endl;
				(*pout_csv) << ",,,,HTML,,JS-Clnt,,VBS-Clnt,,PHP" << endl;
				(*pout_csv) << "Total,Blank,Comments,,Word,Exec.,Data,Exec.,Data,Exec.,Compiler,Data,Exec.,SLOC,,,,,File,SLOC" << endl;
				(*pout_csv) << "Lines,Lines,Whole,Embedded,LOC,Instr.,Decl.,Instr.,Decl.,Instr.,Direct.,Decl.,Instr.,HTML,JS-Clnt,VBS-Clnt,PHP,Total,Type,Definition" << endl;

				(*pout_csv) << itto->second.total_line << ",";
				(*pout_csv) << itto->second.blank_line << ",";
				(*pout_csv) << itto->second.whole_comment << ",";
				(*pout_csv) << itto->second.embed_comment << ",";
				(*pout_csv) << itto->second.phy_decl[0] << ",";
				(*pout_csv) << itto->second.phy_instr[0] << ",";
				(*pout_csv) << itto->second.phy_decl[1] << ",";
				(*pout_csv) << itto->second.phy_instr[1] << ",";
				(*pout_csv) << itto->second.phy_decl[2] << ",";
				(*pout_csv) << itto->second.phy_instr[2] << ",";
				(*pout_csv) << itto->second.phy_direct[3] << ",";
				(*pout_csv) << itto->second.phy_decl[3] << ",";
				(*pout_csv) << itto->second.phy_instr[3] << ",";
				(*pout_csv) << (itto->second.phy_decl[0] + itto->second.phy_instr[0]) << ",";
				(*pout_csv) << (itto->second.phy_decl[1] + itto->second.phy_instr[1]) << ",";
				(*pout_csv) << (itto->second.phy_decl[2] + itto->second.phy_instr[2]) << ",";
				(*pout_csv) << (itto->second.phy_direct[3] + itto->second.phy_decl[3] + itto->second.phy_instr[3]) << ",";
				(*pout_csv) << (itto->second.phy_decl[0] + itto->second.phy_instr[0] +
					itto->second.phy_decl[1] + itto->second.phy_instr[1] +
					itto->second.phy_decl[2] + itto->second.phy_instr[2] +
					itto->second.phy_direct[3] + itto->second.phy_decl[3] + itto->second.phy_instr[3]) << ",";
				(*pout_csv) << "CODE,Physical" << endl;

				(*pout_csv) << itto->second.total_line << ",";
				(*pout_csv) << itto->second.blank_line << ",";
				(*pout_csv) << itto->second.whole_comment << ",";
				(*pout_csv) << itto->second.embed_comment << ",";
				(*pout_csv) << itto->second.log_decl[0] << ",";
				(*pout_csv) << itto->second.log_instr[0] << ",";
				(*pout_csv) << itto->second.log_decl[1] << ",";
				(*pout_csv) << itto->second.log_instr[1] << ",";
				(*pout_csv) << itto->second.log_decl[2] << ",";
				(*pout_csv) << itto->second.log_instr[2] << ",";
				(*pout_csv) << itto->second.log_direct[3] << ",";
				(*pout_csv) << itto->second.log_decl[3] << ",";
				(*pout_csv) << itto->second.log_instr[3] << ",";
				(*pout_csv) << (itto->second.log_decl[0] + itto->second.log_instr[0]) << ",";
				(*pout_csv) << (itto->second.log_decl[1] + itto->second.log_instr[1]) << ",";
				(*pout_csv) << (itto->second.log_decl[2] + itto->second.log_instr[2]) << ",";
				(*pout_csv) << (itto->second.log_direct[3] + itto->second.log_decl[3] + itto->second.log_instr[3]) << ",";
				(*pout_csv) << (itto->second.log_decl[0] + itto->second.log_instr[0] +
					itto->second.log_decl[1] + itto->second.log_instr[1] +
					itto->second.log_decl[2] + itto->second.log_instr[2] +
					itto->second.log_direct[3] + itto->second.log_decl[3] + itto->second.log_instr[3]) << ",";
				(*pout_csv) << "CODE,Logical" << endl;
			}
		}
		else if (itto->first == WEB_JSP)
		{
			if (print_ascii || print_legacy)
			{
				pout = webCounter->GetOutputStream(WEB_JSP, outDir + outputFileNamePrePend, cmdLine);

				(*pout) << endl;
				CUtil::PrintFileHeaderLine(*pout, "RESULTS SUMMARY");
				(*pout) << endl;
				(*pout) << "                                    |       HTML      |     JS-Clnt     |    VBS-Clnt     |          Java           |" << endl;
				if (print_legacy)
				{
					(*pout) << "   Total   Blank |      Comments    |    Word  Exec.  |   Data   Exec.  |   Data   Exec.  | Compiler  Data   Exec.  |                    SLOC                    | File  SLOC" << endl;
					(*pout) << "   Lines   Lines |   Whole Embedded |     LOC  Instr. |   Decl.  Instr. |   Decl.  Instr. | Direct.   Decl.  Instr. |   Total      HTML JS-Clnt VBS-Clnt    Java | Type  Definition" << endl;
					(*pout) << "-----------------+------------------+-----------------+-----------------+-----------------+-------------------------+---------+----------------------------------+------------------" << endl;
				}
				else
				{
					(*pout) << "   Total   Blank |      Comments    |    Word  Exec.  |   Data   Exec.  |   Data   Exec.  | Compiler  Data   Exec.  |                    SLOC                    | File  SLOC" << endl;
					(*pout) << "   Lines   Lines |   Whole Embedded |     LOC  Instr. |   Decl.  Instr. |   Decl.  Instr. | Direct.   Decl.  Instr. |    HTML JS-Clnt VBS-Clnt    Java     Total | Type  Definition" << endl;
					(*pout) << "-----------------+------------------+-----------------+-----------------+-----------------+-------------------------+----------------------------------+---------+------------------" << endl;
				}

				(*pout).setf(ios::right);
				(*pout).width(8);		(*pout) << itto->second.total_line;
				(*pout) << " ";
				(*pout).width(7);		(*pout) << itto->second.blank_line;
				(*pout) << " |";
				(*pout).width(8);		(*pout) << itto->second.whole_comment;
				(*pout) << " ";
				(*pout).width(8);		(*pout) << itto->second.embed_comment;
				(*pout) << " |";
				(*pout).width(8);		(*pout) << itto->second.phy_decl[0];
				(*pout) << " ";
				(*pout).width(7);		(*pout) << itto->second.phy_instr[0];
				(*pout) << " |";
				(*pout).width(8);		(*pout) << itto->second.phy_decl[1];
				(*pout) << " ";
				(*pout).width(7);		(*pout) << itto->second.phy_instr[1];
				(*pout) << " |";
				(*pout).width(8);		(*pout) << itto->second.phy_decl[2];
				(*pout) << " ";
				(*pout).width(7);		(*pout) << itto->second.phy_instr[2];
				(*pout) << " |";
				(*pout).width(8);		(*pout) << itto->second.phy_direct[3];
				(*pout) << " ";
				(*pout).width(7);		(*pout) << itto->second.phy_decl[3];
				(*pout) << " ";
				(*pout).width(7);		(*pout) << itto->second.phy_instr[3];
				if (print_legacy)
				{
					(*pout) << " |";
					(*pout).width(8);	(*pout) << (itto->second.phy_decl[0] + itto->second.phy_instr[0] +
						itto->second.phy_decl[1] + itto->second.phy_instr[1] +
						itto->second.phy_decl[2] + itto->second.phy_instr[2] +
						itto->second.phy_direct[3] + itto->second.phy_decl[3] + itto->second.phy_instr[3]);
				}
				(*pout) << " |";
				(*pout).width(8);		(*pout) << (itto->second.phy_decl[0] + itto->second.phy_instr[0]);
				(*pout) << " ";
				(*pout).width(7);		(*pout) << (itto->second.phy_decl[1] + itto->second.phy_instr[1]);
				(*pout) << " ";
				(*pout).width(8);		(*pout) << (itto->second.phy_decl[2] + itto->second.phy_instr[2]);
				(*pout) << " ";
				(*pout).width(7);		(*pout) << (itto->second.phy_direct[3] + itto->second.phy_decl[3] + itto->second.phy_instr[3]);
				if (!print_legacy)
				{
					(*pout) << " |";
					(*pout).width(8);	(*pout) << (itto->second.phy_decl[0] + itto->second.phy_instr[0] +
						itto->second.phy_decl[1] + itto->second.phy_instr[1] +
						itto->second.phy_decl[2] + itto->second.phy_instr[2] +
						itto->second.phy_direct[3] + itto->second.phy_decl[3] + itto->second.phy_instr[3]);
				}
				(*pout) << " | CODE  Physical"<<endl;

				(*pout).setf(ios::right);
				(*pout).width(8);		(*pout) << itto->second.total_line;
				(*pout) << " ";
				(*pout).width(7);		(*pout) << itto->second.blank_line;
				(*pout) << " |";
				(*pout).width(8);		(*pout) << itto->second.whole_comment;
				(*pout) << " ";
				(*pout).width(8);		(*pout) << itto->second.embed_comment;
				(*pout) << " |";
				(*pout).width(8);		(*pout) << itto->second.log_decl[0];
				(*pout) << " ";
				(*pout).width(7);		(*pout) << itto->second.log_instr[0];
				(*pout) << " |";
				(*pout).width(8);		(*pout) << itto->second.log_decl[1];
				(*pout) << " ";
				(*pout).width(7);		(*pout) << itto->second.log_instr[1];
				(*pout) << " |";
				(*pout).width(8);		(*pout) << itto->second.log_decl[2];
				(*pout) << " ";
				(*pout).width(7);		(*pout) << itto->second.log_instr[2];
				(*pout) << " |";
				(*pout).width(8);		(*pout) << itto->second.log_direct[3];
				(*pout) << " ";
				(*pout).width(7);		(*pout) << itto->second.log_decl[3];
				(*pout) << " ";
				(*pout).width(7);		(*pout) << itto->second.log_instr[3];
				if (print_legacy)
				{
					(*pout) << " |";
					(*pout).width(8);	(*pout) << (itto->second.log_decl[0] + itto->second.log_instr[0] +
						itto->second.log_decl[1] + itto->second.log_instr[1] +
						itto->second.log_decl[2] + itto->second.log_instr[2] +
						itto->second.log_direct[3] + itto->second.log_decl[3] + itto->second.log_instr[3]);
				}
				(*pout) << " |";
				(*pout).width(8);		(*pout) << (itto->second.log_decl[0] + itto->second.log_instr[0]);
				(*pout) << " ";
				(*pout).width(7);		(*pout) << (itto->second.log_decl[1] + itto->second.log_instr[1]);
				(*pout) << " ";
				(*pout).width(8);		(*pout) << (itto->second.log_decl[2] + itto->second.log_instr[2]);
				(*pout) << " ";
				(*pout).width(7);		(*pout) << (itto->second.log_direct[3] + itto->second.log_decl[3] + itto->second.log_instr[3]);
				if (!print_legacy)
				{
					(*pout) << " |";
					(*pout).width(8);	(*pout) << (itto->second.log_decl[0] + itto->second.log_instr[0] +
						itto->second.log_decl[1] + itto->second.log_instr[1] +
						itto->second.log_decl[2] + itto->second.log_instr[2] +
						itto->second.log_direct[3] + itto->second.log_decl[3] + itto->second.log_instr[3]);
				}
				(*pout) << " | CODE  Logical" << endl;
			}
			if (print_csv)
			{
				pout_csv = webCounter->GetOutputStream(WEB_JSP, outDir + outputFileNamePrePend, cmdLine, true);

				(*pout_csv) << endl;
				CUtil::PrintFileHeaderLine(*pout_csv, "RESULTS SUMMARY");
				(*pout_csv) << endl;
				(*pout_csv) << ",,,,HTML,,JS-Clnt,,VBS-Clnt,,Java" << endl;
				(*pout_csv) << "Total,Blank,Comments,,Word,Exec.,Data,Exec.,Data,Exec.,Compiler,Data,Exec.,SLOC,,,,,File,SLOC" << endl;
				(*pout_csv) << "Lines,Lines,Whole,Embedded,LOC,Instr.,Decl.,Instr.,Decl.,Instr.,Direct.,Decl.,Instr.,HTML,JS-Clnt,VBS-Clnt,Java,Total,Type,Definition" << endl;

				(*pout_csv) << itto->second.total_line << ",";
				(*pout_csv) << itto->second.blank_line << ",";
				(*pout_csv) << itto->second.whole_comment << ",";
				(*pout_csv) << itto->second.embed_comment << ",";
				(*pout_csv) << itto->second.phy_decl[0] << ",";
				(*pout_csv) << itto->second.phy_instr[0] << ",";
				(*pout_csv) << itto->second.phy_decl[1] << ",";
				(*pout_csv) << itto->second.phy_instr[1] << ",";
				(*pout_csv) << itto->second.phy_decl[2] << ",";
				(*pout_csv) << itto->second.phy_instr[2] << ",";
				(*pout_csv) << itto->second.phy_direct[3] << ",";
				(*pout_csv) << itto->second.phy_decl[3] << ",";
				(*pout_csv) << itto->second.phy_instr[3] << ",";
				(*pout_csv) << (itto->second.phy_decl[0] + itto->second.phy_instr[0]) << ",";
				(*pout_csv) << (itto->second.phy_decl[1] + itto->second.phy_instr[1]) << ",";
				(*pout_csv) << (itto->second.phy_decl[2] + itto->second.phy_instr[2]) << ",";
				(*pout_csv) << (itto->second.phy_direct[3] + itto->second.phy_decl[3] + itto->second.phy_instr[3]) << ",";
				(*pout_csv) << (itto->second.phy_decl[0] + itto->second.phy_instr[0] +
					itto->second.phy_decl[1] + itto->second.phy_instr[1] +
					itto->second.phy_decl[2] + itto->second.phy_instr[2] +
					itto->second.phy_direct[3] + itto->second.phy_decl[3] + itto->second.phy_instr[3]) << ",";
				(*pout_csv) << "CODE,Physical" << endl;

				(*pout_csv) << itto->second.total_line << ",";
				(*pout_csv) << itto->second.blank_line << ",";
				(*pout_csv) << itto->second.whole_comment << ",";
				(*pout_csv) << itto->second.embed_comment << ",";
				(*pout_csv) << itto->second.log_decl[0] << ",";
				(*pout_csv) << itto->second.log_instr[0] << ",";
				(*pout_csv) << itto->second.log_decl[1] << ",";
				(*pout_csv) << itto->second.log_instr[1] << ",";
				(*pout_csv) << itto->second.log_decl[2] << ",";
				(*pout_csv) << itto->second.log_instr[2] << ",";
				(*pout_csv) << itto->second.log_direct[3] << ",";
				(*pout_csv) << itto->second.log_decl[3] << ",";
				(*pout_csv) << itto->second.log_instr[3] << ",";
				(*pout_csv) << (itto->second.log_decl[0] + itto->second.log_instr[0]) << ",";
				(*pout_csv) << (itto->second.log_decl[1] + itto->second.log_instr[1]) << ",";
				(*pout_csv) << (itto->second.log_decl[2] + itto->second.log_instr[2]) << ",";
				(*pout_csv) << (itto->second.log_direct[3] + itto->second.log_decl[3] + itto->second.log_instr[3]) << ",";
				(*pout_csv) << (itto->second.log_decl[0] + itto->second.log_instr[0] +
					itto->second.log_decl[1] + itto->second.log_instr[1] +
					itto->second.log_decl[2] + itto->second.log_instr[2] +
					itto->second.log_direct[3] + itto->second.log_decl[3] + itto->second.log_instr[3]) << ",";
				(*pout_csv) << "CODE,Logical" << endl;
			}
		}
		else if (itto->first == WEB_ASP)
		{
			if (print_ascii || print_legacy)
			{
				pout = webCounter->GetOutputStream(WEB_ASP, outDir + outputFileNamePrePend, cmdLine);

				(*pout) << endl;
				CUtil::PrintFileHeaderLine(*pout, "RESULTS SUMMARY");
				(*pout) << endl;
				(*pout) << "                                    |       HTML      |     JS-Clnt     |    VBS-Clnt     |      JS-Svr     |     VBS-Svr     |      C#-Svr     |" << endl;
				if (print_legacy)
				{
					(*pout) << "   Total   Blank |      Comments    |    Word  Exec.  |   Data   Exec.  |   Data   Exec.  |   Data   Exec.  |   Data   Exec.  |   Data   Exec.  |                            SLOC                            | File  SLOC" << endl;
					(*pout) << "   Lines   Lines |   Whole Embedded |     LOC  Instr. |   Decl.  Instr. |   Decl.  Instr. |   Decl.  Instr. |   Decl.  Instr. |   Decl.  Instr. |   Total      HTML JS-Clnt VBS-Clnt  JS-Svr VBS-Svr  C#-Svr | Type  Definition" << endl;
					(*pout) << "-----------------+------------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+---------+--------------------------------------------------+------------------" << endl;
				}
				else
				{
					(*pout) << "   Total   Blank |      Comments    |    Word  Exec.  |   Data   Exec.  |   Data   Exec.  |   Data   Exec.  |   Data   Exec.  |   Data   Exec.  |                            SLOC                            | File  SLOC" << endl;
					(*pout) << "   Lines   Lines |   Whole Embedded |     LOC  Instr. |   Decl.  Instr. |   Decl.  Instr. |   Decl.  Instr. |   Decl.  Instr. |   Decl.  Instr. |    HTML JS-Clnt VBS-Clnt  JS-Svr VBS-Svr  C#-Svr     Total | Type  Definition" << endl;
					(*pout) << "-----------------+------------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+--------------------------------------------------+---------+------------------" << endl;
				}

				(*pout).setf(ios::right);
				(*pout).width(8);		(*pout) << itto->second.total_line;
				(*pout) << " ";
				(*pout).width(7);		(*pout) << itto->second.blank_line;
				(*pout) << " |";
				(*pout).width(8);		(*pout) << itto->second.whole_comment;
				(*pout) << " ";
				(*pout).width(8);		(*pout) << itto->second.embed_comment;
				(*pout) << " |";
				(*pout).width(8);		(*pout) << itto->second.phy_decl[0];
				(*pout) << " ";
				(*pout).width(7);		(*pout) << itto->second.phy_instr[0];
				(*pout) << " |";
				(*pout).width(8);		(*pout) << itto->second.phy_decl[1];
				(*pout) << " ";
				(*pout).width(7);		(*pout) << itto->second.phy_instr[1];
				(*pout) << " |";
				(*pout).width(8);		(*pout) << itto->second.phy_decl[2];
				(*pout) << " ";
				(*pout).width(7);		(*pout) << itto->second.phy_instr[2];
				(*pout) << " |";
				(*pout).width(8);		(*pout) << itto->second.phy_decl[3];
				(*pout) << " ";
				(*pout).width(7);		(*pout) << itto->second.phy_instr[3];
				(*pout) << " |";
				(*pout).width(8);		(*pout) << itto->second.phy_decl[4];
				(*pout) << " ";
				(*pout).width(7);		(*pout) << itto->second.phy_instr[4];
				(*pout) << " |";
				(*pout).width(8);		(*pout) << itto->second.phy_decl[5];
				(*pout) << " ";
				(*pout).width(7);		(*pout) << itto->second.phy_instr[5];
				if (print_legacy)
				{
					(*pout) << " |";
					(*pout).width(8);	(*pout) << (itto->second.phy_decl[0] + itto->second.phy_instr[0] +
						itto->second.phy_decl[1] + itto->second.phy_instr[1] +
						itto->second.phy_decl[2] + itto->second.phy_instr[2] +
						itto->second.phy_decl[3] + itto->second.phy_instr[3] +
						itto->second.phy_decl[4] + itto->second.phy_instr[4] +
						itto->second.phy_decl[5] + itto->second.phy_instr[5]);
				}
				(*pout) << " |";
				(*pout).width(8);		(*pout) << (itto->second.phy_decl[0] + itto->second.phy_instr[0]);
				(*pout) << " ";
				(*pout).width(7);		(*pout) << (itto->second.phy_decl[1] + itto->second.phy_instr[1]);
				(*pout) << " ";
				(*pout).width(8);		(*pout) << (itto->second.phy_decl[2] + itto->second.phy_instr[2]);
				(*pout) << " ";
				(*pout).width(7);		(*pout) << (itto->second.phy_decl[3] + itto->second.phy_instr[3]);
				(*pout) << " ";
				(*pout).width(7);		(*pout) << (itto->second.phy_decl[4] + itto->second.phy_instr[4]);
				(*pout) << " ";
				(*pout).width(7);		(*pout) << (itto->second.phy_decl[5] + itto->second.phy_instr[5]);
				if (!print_legacy)
				{
					(*pout) << " |";
					(*pout).width(8);	(*pout) << (itto->second.phy_decl[0] + itto->second.phy_instr[0] +
						itto->second.phy_decl[1] + itto->second.phy_instr[1] +
						itto->second.phy_decl[2] + itto->second.phy_instr[2] +
						itto->second.phy_decl[3] + itto->second.phy_instr[3] +
						itto->second.phy_decl[4] + itto->second.phy_instr[4] +
						itto->second.phy_decl[5] + itto->second.phy_instr[5]);
				}
				(*pout) << " | CODE  Physical"<<endl;

				(*pout).setf(ios::right);
				(*pout).width(8);		(*pout) << itto->second.total_line;
				(*pout) << " ";
				(*pout).width(7);		(*pout) << itto->second.blank_line;
				(*pout) << " |";
				(*pout).width(8);		(*pout) << itto->second.whole_comment;
				(*pout) << " ";
				(*pout).width(8);		(*pout) << itto->second.embed_comment;
				(*pout) << " |";
				(*pout).width(8);		(*pout) << itto->second.log_decl[0];
				(*pout) << " ";
				(*pout).width(7);		(*pout) << itto->second.log_instr[0];
				(*pout) << " |";
				(*pout).width(8);		(*pout) << itto->second.log_decl[1];
				(*pout) << " ";
				(*pout).width(7);		(*pout) << itto->second.log_instr[1];
				(*pout) << " |";
				(*pout).width(8);		(*pout) << itto->second.log_decl[2];
				(*pout) << " ";
				(*pout).width(7);		(*pout) << itto->second.log_instr[2];
				(*pout) << " |";
				(*pout).width(8);		(*pout) << itto->second.log_decl[3];
				(*pout) << " ";
				(*pout).width(7);		(*pout) << itto->second.log_instr[3];
				(*pout) << " |";
				(*pout).width(8);		(*pout) << itto->second.log_decl[4];
				(*pout) << " ";
				(*pout).width(7);		(*pout) << itto->second.log_instr[4];
				(*pout) << " |";
				(*pout).width(8);		(*pout) << itto->second.log_decl[5];
				(*pout) << " ";
				(*pout).width(7);		(*pout) << itto->second.log_instr[5];
				if (print_legacy)
				{
					(*pout) << " |";
					(*pout).width(8);	(*pout) << (itto->second.log_decl[0] + itto->second.log_instr[0] +
						itto->second.log_decl[1] + itto->second.log_instr[1] +
						itto->second.log_decl[2] + itto->second.log_instr[2] +
						itto->second.log_decl[3] + itto->second.log_instr[3] +
						itto->second.log_decl[4] + itto->second.log_instr[4] +
						itto->second.log_decl[5] + itto->second.log_instr[5]);
				}
				(*pout) << " |";
				(*pout).width(8);		(*pout) << (itto->second.log_decl[0] + itto->second.log_instr[0]);
				(*pout) << " ";
				(*pout).width(7);		(*pout) << (itto->second.log_decl[1] + itto->second.log_instr[1]);
				(*pout) << " ";
				(*pout).width(8);		(*pout) << (itto->second.log_decl[2] + itto->second.log_instr[2]);
				(*pout) << " ";
				(*pout).width(7);		(*pout) << (itto->second.log_decl[3] + itto->second.log_instr[3]);
				(*pout) << " ";
				(*pout).width(7);		(*pout) << (itto->second.log_decl[4] + itto->second.log_instr[4]);
				(*pout) << " ";
				(*pout).width(7);		(*pout) << (itto->second.log_decl[5] + itto->second.log_instr[5]);
				if (!print_legacy)
				{
					(*pout) << " |";
					(*pout).width(8);	(*pout) << (itto->second.log_decl[0] + itto->second.log_instr[0] +
						itto->second.log_decl[1] + itto->second.log_instr[1] +
						itto->second.log_decl[2] + itto->second.log_instr[2] +
						itto->second.log_decl[3] + itto->second.log_instr[3] +
						itto->second.log_decl[4] + itto->second.log_instr[4] +
						itto->second.log_decl[5] + itto->second.log_instr[5]);
				}
				(*pout) << " | CODE  Logical" << endl;
			}
			if (print_csv)
			{
				pout_csv = webCounter->GetOutputStream(WEB_ASP, outDir + outputFileNamePrePend, cmdLine, true);

				(*pout_csv) << endl;
				CUtil::PrintFileHeaderLine(*pout_csv, "RESULTS SUMMARY");
				(*pout_csv) << endl;
				(*pout_csv) << ",,,,HTML,,JS-Clnt,,VBS-Clnt,,JS-Svr,,VBS-Svr,,C#-Svr" << endl;
				(*pout_csv) << "Total,Blank,Comments,,Word,Exec.,Data,Exec.,Data,Exec.,Data,Exec.,Data,Exec.,Data,Exec.,SLOC,,,,,,,File,SLOC" << endl;
				(*pout_csv) << "Lines,Lines,Whole,Embedded,LOC,Instr.,Decl.,Instr.,Decl.,Instr.,Decl.,Instr.,Decl.,Instr.,Decl.,Instr.,HTML,JS-Clnt,VBS-Clnt,JS-Svr,VBS-Svr,C#-Svr,Total,Type,Definition" << endl;

				(*pout_csv) << itto->second.total_line << ",";
				(*pout_csv) << itto->second.blank_line << ",";
				(*pout_csv) << itto->second.whole_comment << ",";
				(*pout_csv) << itto->second.embed_comment << ",";
				(*pout_csv) << itto->second.phy_decl[0] << ",";
				(*pout_csv) << itto->second.phy_instr[0] << ",";
				(*pout_csv) << itto->second.phy_decl[1] << ",";
				(*pout_csv) << itto->second.phy_instr[1] << ",";
				(*pout_csv) << itto->second.phy_decl[2] << ",";
				(*pout_csv) << itto->second.phy_instr[2] << ",";
				(*pout_csv) << itto->second.phy_decl[3] << ",";
				(*pout_csv) << itto->second.phy_instr[3] << ",";
				(*pout_csv) << itto->second.phy_decl[4] << ",";
				(*pout_csv) << itto->second.phy_instr[4] << ",";
				(*pout_csv) << itto->second.phy_decl[5] << ",";
				(*pout_csv) << itto->second.phy_instr[5] << ",";
				(*pout_csv) << (itto->second.phy_decl[0] + itto->second.phy_instr[0]) << ",";
				(*pout_csv) << (itto->second.phy_decl[1] + itto->second.phy_instr[1]) << ",";
				(*pout_csv) << (itto->second.phy_decl[2] + itto->second.phy_instr[2]) << ",";
				(*pout_csv) << (itto->second.phy_decl[3] + itto->second.phy_instr[3]) << ",";
				(*pout_csv) << (itto->second.phy_decl[4] + itto->second.phy_instr[4]) << ",";
				(*pout_csv) << (itto->second.phy_decl[5] + itto->second.phy_instr[5]) << ",";
				(*pout_csv) << (itto->second.phy_decl[0] + itto->second.phy_instr[0] +
					itto->second.phy_decl[1] + itto->second.phy_instr[1] +
					itto->second.phy_decl[2] + itto->second.phy_instr[2] +
					itto->second.phy_decl[3] + itto->second.phy_instr[3] +
					itto->second.phy_decl[4] + itto->second.phy_instr[4] +
					itto->second.phy_decl[5] + itto->second.phy_instr[5]) << ",";
				(*pout_csv) << "CODE,Physical" << endl;

				(*pout_csv) << itto->second.total_line << ",";
				(*pout_csv) << itto->second.blank_line << ",";
				(*pout_csv) << itto->second.whole_comment << ",";
				(*pout_csv) << itto->second.embed_comment << ",";
				(*pout_csv) << itto->second.log_decl[0] << ",";
				(*pout_csv) << itto->second.log_instr[0] << ",";
				(*pout_csv) << itto->second.log_decl[1] << ",";
				(*pout_csv) << itto->second.log_instr[1] << ",";
				(*pout_csv) << itto->second.log_decl[2] << ",";
				(*pout_csv) << itto->second.log_instr[2] << ",";
				(*pout_csv) << itto->second.log_decl[3] << ",";
				(*pout_csv) << itto->second.log_instr[3] << ",";
				(*pout_csv) << itto->second.log_decl[4] << ",";
				(*pout_csv) << itto->second.log_instr[4] << ",";
				(*pout_csv) << itto->second.log_decl[5] << ",";
				(*pout_csv) << itto->second.log_instr[5] << ",";
				(*pout_csv) << (itto->second.log_decl[0] + itto->second.log_instr[0]) << ",";
				(*pout_csv) << (itto->second.log_decl[1] + itto->second.log_instr[1]) << ",";
				(*pout_csv) << (itto->second.log_decl[2] + itto->second.log_instr[2]) << ",";
				(*pout_csv) << (itto->second.log_decl[3] + itto->second.log_instr[3]) << ",";
				(*pout_csv) << (itto->second.log_decl[4] + itto->second.log_instr[4]) << ",";
				(*pout_csv) << (itto->second.log_decl[5] + itto->second.log_instr[5]) << ",";
				(*pout_csv) << (itto->second.log_decl[0] + itto->second.log_instr[0] +
					itto->second.log_decl[1] + itto->second.log_instr[1] +
					itto->second.log_decl[2] + itto->second.log_instr[2] +
					itto->second.log_decl[3] + itto->second.log_instr[3] +
					itto->second.log_decl[4] + itto->second.log_instr[4] +
					itto->second.log_decl[5] + itto->second.log_instr[5]) << ",";
				(*pout_csv) << "CODE,Logical" << endl;
			}
		}
		else if (itto->first == WEB_XML)
		{
			if (print_ascii || print_legacy)
			{
				pout = webCounter->GetOutputStream(WEB_XML, outDir + outputFileNamePrePend, cmdLine);

				(*pout) << endl;
				CUtil::PrintFileHeaderLine(*pout, "RESULTS SUMMARY");
				(*pout) << endl;
				(*pout) << "                                    |        XML      |     JS-Clnt     |    VBS-Clnt     |     C#-Clnt     |" << endl;
				if (print_legacy)
				{
					(*pout) << "   Total   Blank |      Comments    |    Word  Exec.  |   Data   Exec.  |   Data   Exec.  |   Data   Exec.  |                    SLOC                    | File  SLOC" << endl;
					(*pout) << "   Lines   Lines |   Whole Embedded |     LOC  Instr. |   Decl.  Instr. |   Decl.  Instr. |   Decl.  Instr. |   Total       XML JS-Clnt VBS-Clnt C#-Clnt | Type  Definition" << endl;
					(*pout) << "-----------------+------------------+-----------------+-----------------+-----------------+-----------------+---------+----------------------------------+------------------" << endl;
				}
				else
				{
					(*pout) << "   Total   Blank |      Comments    |    Word  Exec.  |   Data   Exec.  |   Data   Exec.  |   Data   Exec.  |                    SLOC                    | File  SLOC" << endl;
					(*pout) << "   Lines   Lines |   Whole Embedded |     LOC  Instr. |   Decl.  Instr. |   Decl.  Instr. |   Decl.  Instr. |     XML JS-Clnt VBS-Clnt C#-Clnt     Total | Type  Definition" << endl;
					(*pout) << "-----------------+------------------+-----------------+-----------------+-----------------+----------------------------------------------------+---------+------------------" << endl;
				}

				(*pout).setf(ios::right);
				(*pout).width(8);		(*pout) << itto->second.total_line;
				(*pout) << " ";
				(*pout).width(7);		(*pout) << itto->second.blank_line;
				(*pout) << " |";
				(*pout).width(8);		(*pout) << itto->second.whole_comment;
				(*pout) << " ";
				(*pout).width(8);		(*pout) << itto->second.embed_comment;
				(*pout) << " |";
				(*pout).width(8);		(*pout) << itto->second.phy_decl[0];
				(*pout) << " ";
				(*pout).width(7);		(*pout) << itto->second.phy_instr[0];
				(*pout) << " |";
				(*pout).width(8);		(*pout) << itto->second.phy_decl[1];
				(*pout) << " ";
				(*pout).width(7);		(*pout) << itto->second.phy_instr[1];
				(*pout) << " |";
				(*pout).width(8);		(*pout) << itto->second.phy_decl[2];
				(*pout) << " ";
				(*pout).width(7);		(*pout) << itto->second.phy_instr[2];
				(*pout) << " |";
				(*pout).width(8);		(*pout) << itto->second.phy_decl[3];
				(*pout) << " ";
				(*pout).width(7);		(*pout) << itto->second.phy_instr[3];
				if (print_legacy)
				{
					(*pout) << " |";
					(*pout).width(8);	(*pout) << (itto->second.phy_decl[0] + itto->second.phy_instr[0] +
						itto->second.phy_decl[1] + itto->second.phy_instr[1] +
						itto->second.phy_decl[2] + itto->second.phy_instr[2] +
						itto->second.phy_decl[3] + itto->second.phy_instr[3]);
				}
				(*pout) << " |";
				(*pout).width(8);		(*pout) << (itto->second.phy_decl[0] + itto->second.phy_instr[0]);
				(*pout) << " ";
				(*pout).width(7);		(*pout) << (itto->second.phy_decl[1] + itto->second.phy_instr[1]);
				(*pout) << " ";
				(*pout).width(8);		(*pout) << (itto->second.phy_decl[2] + itto->second.phy_instr[2]);
				(*pout) << " ";
				(*pout).width(7);		(*pout) << (itto->second.phy_decl[3] + itto->second.phy_instr[3]);
				if (!print_legacy)
				{
					(*pout) << " |";
					(*pout).width(8);	(*pout) << (itto->second.phy_decl[0] + itto->second.phy_instr[0] +
						itto->second.phy_decl[1] + itto->second.phy_instr[1] +
						itto->second.phy_decl[2] + itto->second.phy_instr[2] +
						itto->second.phy_decl[3] + itto->second.phy_instr[3]);
				}
				(*pout) << " | CODE  Physical" << endl;

				(*pout).setf(ios::right);
				(*pout).width(8);		(*pout) << itto->second.total_line;
				(*pout) << " ";
				(*pout).width(7);		(*pout) << itto->second.blank_line;
				(*pout) << " |";
				(*pout).width(8);		(*pout) << itto->second.whole_comment;
				(*pout) << " ";
				(*pout).width(8);		(*pout) << itto->second.embed_comment;
				(*pout) << " |";
				(*pout).width(8);		(*pout) << itto->second.log_decl[0];
				(*pout) << " ";
				(*pout).width(7);		(*pout) << itto->second.log_instr[0];
				(*pout) << " |";
				(*pout).width(8);		(*pout) << itto->second.log_decl[1];
				(*pout) << " ";
				(*pout).width(7);		(*pout) << itto->second.log_instr[1];
				(*pout) << " |";
				(*pout).width(8);		(*pout) << itto->second.log_decl[2];
				(*pout) << " ";
				(*pout).width(7);		(*pout) << itto->second.log_instr[2];
				(*pout) << " |";
				(*pout).width(8);		(*pout) << itto->second.log_decl[3];
				(*pout) << " ";
				(*pout).width(7);		(*pout) << itto->second.log_instr[3];
				if (print_legacy)
				{
					(*pout) << " |";
					(*pout).width(8);	(*pout) << (itto->second.log_decl[0] + itto->second.log_instr[0] +
						itto->second.log_decl[1] + itto->second.log_instr[1] +
						itto->second.log_decl[2] + itto->second.log_instr[2] +
						itto->second.log_decl[3] + itto->second.log_instr[3]);
				}
				(*pout) << " |";
				(*pout).width(8);		(*pout) << (itto->second.log_decl[0] + itto->second.log_instr[0]);
				(*pout) << " ";
				(*pout).width(7);		(*pout) << (itto->second.log_decl[1] + itto->second.log_instr[1]);
				(*pout) << " ";
				(*pout).width(8);		(*pout) << (itto->second.log_decl[2] + itto->second.log_instr[2]);
				(*pout) << " ";
				(*pout).width(7);		(*pout) << (itto->second.log_decl[3] + itto->second.log_instr[3]);
				if (!print_legacy)
				{
					(*pout) << " |";
					(*pout).width(8);	(*pout) << (itto->second.log_decl[0] + itto->second.log_instr[0] +
						itto->second.log_decl[1] + itto->second.log_instr[1] +
						itto->second.log_decl[2] + itto->second.log_instr[2] +
						itto->second.log_decl[3] + itto->second.log_instr[3]);
				}
				(*pout) << " | CODE  Logical" << endl;
			}
			if (print_csv)
			{
				pout_csv = webCounter->GetOutputStream(WEB_XML, outDir + outputFileNamePrePend, cmdLine, true);

				(*pout_csv) << endl;
				CUtil::PrintFileHeaderLine(*pout_csv, "RESULTS SUMMARY");
				(*pout_csv) << endl;
				(*pout_csv) << ",,,,XML,,JS-Clnt,,VBS-Clnt,,C#-Clnt" << endl;
				(*pout_csv) << "Total,Blank,Comments,,Word,Exec.,Data,Exec.,Data,Exec.,Data,Exec.,SLOC,,,,,File,SLOC" << endl;
				(*pout_csv) << "Lines,Lines,Whole,Embedded,LOC,Instr.,Decl.,Instr.,Decl.,Instr.,Decl.,Instr.,XML,JS-Clnt,VBS-Clnt,C#-Clnt,Total,Type,Definition" << endl;

				(*pout_csv) << itto->second.total_line << ",";
				(*pout_csv) << itto->second.blank_line << ",";
				(*pout_csv) << itto->second.whole_comment << ",";
				(*pout_csv) << itto->second.embed_comment << ",";
				(*pout_csv) << itto->second.phy_decl[0] << ",";
				(*pout_csv) << itto->second.phy_instr[0] << ",";
				(*pout_csv) << itto->second.phy_decl[1] << ",";
				(*pout_csv) << itto->second.phy_instr[1] << ",";
				(*pout_csv) << itto->second.phy_decl[2] << ",";
				(*pout_csv) << itto->second.phy_instr[2] << ",";
				(*pout_csv) << itto->second.phy_decl[3] << ",";
				(*pout_csv) << itto->second.phy_instr[3] << ",";
				(*pout_csv) << (itto->second.phy_decl[0] + itto->second.phy_instr[0]) << ",";
				(*pout_csv) << (itto->second.phy_decl[1] + itto->second.phy_instr[1]) << ",";
				(*pout_csv) << (itto->second.phy_decl[2] + itto->second.phy_instr[2]) << ",";
				(*pout_csv) << (itto->second.phy_decl[3] + itto->second.phy_instr[3]) << ",";
				(*pout_csv) << (itto->second.phy_decl[0] + itto->second.phy_instr[0] +
					itto->second.phy_decl[1] + itto->second.phy_instr[1] +
					itto->second.phy_decl[2] + itto->second.phy_instr[2] +
					itto->second.phy_decl[3] + itto->second.phy_instr[3]) << ",";
				(*pout_csv) << "CODE,Physical" << endl;

				(*pout_csv) << itto->second.total_line << ",";
				(*pout_csv) << itto->second.blank_line << ",";
				(*pout_csv) << itto->second.whole_comment << ",";
				(*pout_csv) << itto->second.embed_comment << ",";
				(*pout_csv) << itto->second.log_decl[0] << ",";
				(*pout_csv) << itto->second.log_instr[0] << ",";
				(*pout_csv) << itto->second.log_decl[1] << ",";
				(*pout_csv) << itto->second.log_instr[1] << ",";
				(*pout_csv) << itto->second.log_decl[2] << ",";
				(*pout_csv) << itto->second.log_instr[2] << ",";
				(*pout_csv) << itto->second.log_decl[3] << ",";
				(*pout_csv) << itto->second.log_instr[3] << ",";
				(*pout_csv) << (itto->second.log_decl[0] + itto->second.log_instr[0]) << ",";
				(*pout_csv) << (itto->second.log_decl[1] + itto->second.log_instr[1]) << ",";
				(*pout_csv) << (itto->second.log_decl[2] + itto->second.log_instr[2]) << ",";
				(*pout_csv) << (itto->second.log_decl[3] + itto->second.log_instr[3]) << ",";
				(*pout_csv) << (itto->second.log_decl[0] + itto->second.log_instr[0] +
					itto->second.log_decl[1] + itto->second.log_instr[1] +
					itto->second.log_decl[2] + itto->second.log_instr[2] +
					itto->second.log_decl[3] + itto->second.log_instr[3]) << ",";
				(*pout_csv) << "CODE,Logical" << endl;
			}
		}
		else if (itto->first == WEB_CFM)
		{
			if (print_ascii || print_legacy)
			{
				pout = webCounter->GetOutputStream(WEB_CFM, outDir + outputFileNamePrePend, cmdLine);

				(*pout) << endl;
				CUtil::PrintFileHeaderLine(*pout, "RESULTS SUMMARY");
				(*pout) << endl;
				(*pout) << "                                    |       HTML      |     JS-Clnt     |    VBS-Clnt     |       SQL       |    ColdFusion   |     CFScript    |" << endl;
				if (print_legacy)
				{
					(*pout) << "   Total   Blank |      Comments    |    Word  Exec.  |   Data   Exec.  |   Data   Exec.  |   Data   Exec.  |   Data   Exec.  |   Data   Exec.  |                              SLOC                              | File  SLOC" << endl;
					(*pout) << "   Lines   Lines |   Whole Embedded |     LOC  Instr. |   Decl.  Instr. |   Decl.  Instr. |   Decl.  Instr. |   Decl.  Instr. |   Decl.  Instr. |   Total      HTML JS-Clnt VBS-Clnt     SQL ColdFusion CFScript | Type  Definition" << endl;
					(*pout) << "-----------------+------------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+---------+------------------------------------------------------+------------------" << endl;
				}
				else
				{
					(*pout) << "   Total   Blank |      Comments    |    Word  Exec.  |   Data   Exec.  |   Data   Exec.  |   Data   Exec.  |   Data   Exec.  |   Data   Exec.  |                              SLOC                              | File  SLOC" << endl;
					(*pout) << "   Lines   Lines |   Whole Embedded |     LOC  Instr. |   Decl.  Instr. |   Decl.  Instr. |   Decl.  Instr. |   Decl.  Instr. |   Decl.  Instr. |    HTML JS-Clnt VBS-Clnt     SQL ColdFusion CFScript     Total | Type  Definition" << endl;
					(*pout) << "-----------------+------------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+------------------------------------------------------+---------+------------------" << endl;
				}

				(*pout).setf(ios::right);
				(*pout).width(8);		(*pout) << itto->second.total_line;
				(*pout) << " ";
				(*pout).width(7);		(*pout) << itto->second.blank_line;
				(*pout) << " |";
				(*pout).width(8);		(*pout) << itto->second.whole_comment;
				(*pout) << " ";
				(*pout).width(8);		(*pout) << itto->second.embed_comment;
				(*pout) << " |";
				(*pout).width(8);		(*pout) << itto->second.phy_decl[0];
				(*pout) << " ";
				(*pout).width(7);		(*pout) << itto->second.phy_instr[0];
				(*pout) << " |";
				(*pout).width(8);		(*pout) << itto->second.phy_decl[1];
				(*pout) << " ";
				(*pout).width(7);		(*pout) << itto->second.phy_instr[1];
				(*pout) << " |";
				(*pout).width(8);		(*pout) << itto->second.phy_decl[2];
				(*pout) << " ";
				(*pout).width(7);		(*pout) << itto->second.phy_instr[2];
				(*pout) << " |";
				(*pout).width(8);		(*pout) << itto->second.phy_decl[3];
				(*pout) << " ";
				(*pout).width(7);		(*pout) << itto->second.phy_instr[3];
				(*pout) << " |";
				(*pout).width(8);		(*pout) << itto->second.phy_decl[4];
				(*pout) << " ";
				(*pout).width(7);		(*pout) << itto->second.phy_instr[4];
				(*pout) << " |";
				(*pout).width(8);		(*pout) << itto->second.phy_decl[5];
				(*pout) << " ";
				(*pout).width(7);		(*pout) << itto->second.phy_instr[5];
				if (print_legacy)
				{
					(*pout) << " |";
					(*pout).width(8);	(*pout) << (itto->second.phy_decl[0] + itto->second.phy_instr[0] +
						itto->second.phy_decl[1] + itto->second.phy_instr[1] +
						itto->second.phy_decl[2] + itto->second.phy_instr[2] +
						itto->second.phy_decl[3] + itto->second.phy_instr[3] +
						itto->second.phy_decl[4] + itto->second.phy_instr[4] +
						itto->second.phy_decl[5] + itto->second.phy_instr[5]);
				}
				(*pout) << " |";
				(*pout).width(8);		(*pout) << (itto->second.phy_decl[0] + itto->second.phy_instr[0]);
				(*pout) << " ";
				(*pout).width(7);		(*pout) << (itto->second.phy_decl[1] + itto->second.phy_instr[1]);
				(*pout) << " ";
				(*pout).width(8);		(*pout) << (itto->second.phy_decl[2] + itto->second.phy_instr[2]);
				(*pout) << " ";
				(*pout).width(7);		(*pout) << (itto->second.phy_decl[3] + itto->second.phy_instr[3]);
				(*pout) << " ";
				(*pout).width(10);		(*pout) << (itto->second.phy_decl[4] + itto->second.phy_instr[4]);
				(*pout) << " ";
				(*pout).width(8);		(*pout) << (itto->second.phy_decl[5] + itto->second.phy_instr[5]);
				if (!print_legacy)
				{
					(*pout) << " |";
					(*pout).width(8);	(*pout) << (itto->second.phy_decl[0] + itto->second.phy_instr[0] +
						itto->second.phy_decl[1] + itto->second.phy_instr[1] +
						itto->second.phy_decl[2] + itto->second.phy_instr[2] +
						itto->second.phy_decl[3] + itto->second.phy_instr[3] +
						itto->second.phy_decl[4] + itto->second.phy_instr[4] +
						itto->second.phy_decl[5] + itto->second.phy_instr[5]);
				}
				(*pout) << " | CODE  Physical"<<endl;

				(*pout).setf(ios::right);
				(*pout).width(8);		(*pout) << itto->second.total_line;
				(*pout) << " ";
				(*pout).width(7);		(*pout) << itto->second.blank_line;
				(*pout) << " |";
				(*pout).width(8);		(*pout) << itto->second.whole_comment;
				(*pout) << " ";
				(*pout).width(8);		(*pout) << itto->second.embed_comment;
				(*pout) << " |";
				(*pout).width(8);		(*pout) << itto->second.log_decl[0];
				(*pout) << " ";
				(*pout).width(7);		(*pout) << itto->second.log_instr[0];
				(*pout) << " |";
				(*pout).width(8);		(*pout) << itto->second.log_decl[1];
				(*pout) << " ";
				(*pout).width(7);		(*pout) << itto->second.log_instr[1];
				(*pout) << " |";
				(*pout).width(8);		(*pout) << itto->second.log_decl[2];
				(*pout) << " ";
				(*pout).width(7);		(*pout) << itto->second.log_instr[2];
				(*pout) << " |";
				(*pout).width(8);		(*pout) << itto->second.log_decl[3];
				(*pout) << " ";
				(*pout).width(7);		(*pout) << itto->second.log_instr[3];
				(*pout) << " |";
				(*pout).width(8);		(*pout) << itto->second.log_decl[4];
				(*pout) << " ";
				(*pout).width(7);		(*pout) << itto->second.log_instr[4];
				(*pout) << " |";
				(*pout).width(8);		(*pout) << itto->second.log_decl[5];
				(*pout) << " ";
				(*pout).width(7);		(*pout) << itto->second.log_instr[5];
				if (print_legacy)
				{
					(*pout) << " |";
					(*pout).width(8);	(*pout) << (itto->second.log_decl[0] + itto->second.log_instr[0] +
						itto->second.log_decl[1] + itto->second.log_instr[1] +
						itto->second.log_decl[2] + itto->second.log_instr[2] +
						itto->second.log_decl[3] + itto->second.log_instr[3] +
						itto->second.log_decl[4] + itto->second.log_instr[4] +
						itto->second.log_decl[5] + itto->second.log_instr[5]);
				}
				(*pout) << " |";
				(*pout).width(8);		(*pout) << (itto->second.log_decl[0] + itto->second.log_instr[0]);
				(*pout) << " ";
				(*pout).width(7);		(*pout) << (itto->second.log_decl[1] + itto->second.log_instr[1]);
				(*pout) << " ";
				(*pout).width(8);		(*pout) << (itto->second.log_decl[2] + itto->second.log_instr[2]);
				(*pout) << " ";
				(*pout).width(7);		(*pout) << (itto->second.log_decl[3] + itto->second.log_instr[3]);
				(*pout) << " ";
				(*pout).width(10);		(*pout) << (itto->second.log_decl[4] + itto->second.log_instr[4]);
				(*pout) << " ";
				(*pout).width(8);		(*pout) << (itto->second.log_decl[5] + itto->second.log_instr[5]);
				if (!print_legacy)
				{
					(*pout) << " |";
					(*pout).width(8);	(*pout) << (itto->second.log_decl[0] + itto->second.log_instr[0] +
						itto->second.log_decl[1] + itto->second.log_instr[1] +
						itto->second.log_decl[2] + itto->second.log_instr[2] +
						itto->second.log_decl[3] + itto->second.log_instr[3] +
						itto->second.log_decl[4] + itto->second.log_instr[4] +
						itto->second.log_decl[5] + itto->second.log_instr[5]);
				}
				(*pout) << " | CODE  Logical" << endl;
			}
			if (print_csv)
			{
				pout_csv = webCounter->GetOutputStream(WEB_CFM, outDir + outputFileNamePrePend, cmdLine, true);

				(*pout_csv) << endl;
				CUtil::PrintFileHeaderLine(*pout_csv, "RESULTS SUMMARY");
				(*pout_csv) << endl;
				(*pout_csv) << ",,,,HTML,,JS-Clnt,,VBS-Clnt,,SQL,,ColdFusion,,CFScript" << endl;
				(*pout_csv) << "Total,Blank,Comments,,Word,Exec.,Data,Exec.,Data,Exec.,Data,Exec.,Data,Exec.,Data,Exec.,SLOC,,,,,,,File,SLOC" << endl;
				(*pout_csv) << "Lines,Lines,Whole,Embedded,LOC,Instr.,Decl.,Instr.,Decl.,Instr.,Decl.,Instr.,Decl.,Instr.,Decl.,Instr.,HTML,JS-Clnt,VBS-Clnt,SQL,ColdFusion,CFScript,Total,Type,Definition" << endl;

				(*pout_csv) << itto->second.total_line << ",";
				(*pout_csv) << itto->second.blank_line << ",";
				(*pout_csv) << itto->second.whole_comment << ",";
				(*pout_csv) << itto->second.embed_comment << ",";
				(*pout_csv) << itto->second.phy_decl[0] << ",";
				(*pout_csv) << itto->second.phy_instr[0] << ",";
				(*pout_csv) << itto->second.phy_decl[1] << ",";
				(*pout_csv) << itto->second.phy_instr[1] << ",";
				(*pout_csv) << itto->second.phy_decl[2] << ",";
				(*pout_csv) << itto->second.phy_instr[2] << ",";
				(*pout_csv) << itto->second.phy_decl[3] << ",";
				(*pout_csv) << itto->second.phy_instr[3] << ",";
				(*pout_csv) << itto->second.phy_decl[4] << ",";
				(*pout_csv) << itto->second.phy_instr[4] << ",";
				(*pout_csv) << itto->second.phy_decl[5] << ",";
				(*pout_csv) << itto->second.phy_instr[5] << ",";
				(*pout_csv) << (itto->second.phy_decl[0] + itto->second.phy_instr[0]) << ",";
				(*pout_csv) << (itto->second.phy_decl[1] + itto->second.phy_instr[1]) << ",";
				(*pout_csv) << (itto->second.phy_decl[2] + itto->second.phy_instr[2]) << ",";
				(*pout_csv) << (itto->second.phy_decl[3] + itto->second.phy_instr[3]) << ",";
				(*pout_csv) << (itto->second.phy_decl[4] + itto->second.phy_instr[4]) << ",";
				(*pout_csv) << (itto->second.phy_decl[5] + itto->second.phy_instr[5]) << ",";
				(*pout_csv) << (itto->second.phy_decl[0] + itto->second.phy_instr[0] +
					itto->second.phy_decl[1] + itto->second.phy_instr[1] +
					itto->second.phy_decl[2] + itto->second.phy_instr[2] +
					itto->second.phy_decl[3] + itto->second.phy_instr[3] +
					itto->second.phy_decl[4] + itto->second.phy_instr[4] +
					itto->second.phy_decl[5] + itto->second.phy_instr[5]) << ",";
				(*pout_csv) << "CODE,Physical" << endl;

				(*pout_csv) << itto->second.total_line << ",";
				(*pout_csv) << itto->second.blank_line << ",";
				(*pout_csv) << itto->second.whole_comment << ",";
				(*pout_csv) << itto->second.embed_comment << ",";
				(*pout_csv) << itto->second.log_decl[0] << ",";
				(*pout_csv) << itto->second.log_instr[0] << ",";
				(*pout_csv) << itto->second.log_decl[1] << ",";
				(*pout_csv) << itto->second.log_instr[1] << ",";
				(*pout_csv) << itto->second.log_decl[2] << ",";
				(*pout_csv) << itto->second.log_instr[2] << ",";
				(*pout_csv) << itto->second.log_decl[3] << ",";
				(*pout_csv) << itto->second.log_instr[3] << ",";
				(*pout_csv) << itto->second.log_decl[4] << ",";
				(*pout_csv) << itto->second.log_instr[4] << ",";
				(*pout_csv) << itto->second.log_decl[5] << ",";
				(*pout_csv) << itto->second.log_instr[5] << ",";
				(*pout_csv) << (itto->second.log_decl[0] + itto->second.log_instr[0]) << ",";
				(*pout_csv) << (itto->second.log_decl[1] + itto->second.log_instr[1]) << ",";
				(*pout_csv) << (itto->second.log_decl[2] + itto->second.log_instr[2]) << ",";
				(*pout_csv) << (itto->second.log_decl[3] + itto->second.log_instr[3]) << ",";
				(*pout_csv) << (itto->second.log_decl[4] + itto->second.log_instr[4]) << ",";
				(*pout_csv) << (itto->second.log_decl[5] + itto->second.log_instr[5]) << ",";
				(*pout_csv) << (itto->second.log_decl[0] + itto->second.log_instr[0] +
					itto->second.log_decl[1] + itto->second.log_instr[1] +
					itto->second.log_decl[2] + itto->second.log_instr[2] +
					itto->second.log_decl[3] + itto->second.log_instr[3] +
					itto->second.log_decl[4] + itto->second.log_instr[4] +
					itto->second.log_decl[5] + itto->second.log_instr[5]) << ",";
				(*pout_csv) << "CODE,Logical" << endl;
			}
		}
		else if (itto->first == WEB_HTM)
		{
			if (print_ascii || print_legacy)
			{
				pout = webCounter->GetOutputStream(WEB_HTM, outDir + outputFileNamePrePend, cmdLine);

				(*pout) << endl;
				CUtil::PrintFileHeaderLine(*pout, "RESULTS SUMMARY");
				(*pout) << endl;
				(*pout) << "                                    |       HTML      |     JS-Clnt     |    VBS-Clnt     |     C#-Clnt     |" << endl;
				if (print_legacy)
				{
					(*pout) << "   Total   Blank |      Comments    |    Word  Exec.  |   Data   Exec.  |   Data   Exec.  |   Data   Exec.  |                    SLOC                    | File  SLOC" << endl;
					(*pout) << "   Lines   Lines |   Whole Embedded |     LOC  Instr. |   Decl.  Instr. |   Decl.  Instr. |   Decl.  Instr. |   Total      HTML JS-Clnt VBS-Clnt C#-Clnt | Type  Definition" << endl;
					(*pout) << "-----------------+------------------+-----------------+-----------------+-----------------+-----------------+---------+----------------------------------+------------------" << endl;
				}
				else
				{
					(*pout) << "   Total   Blank |      Comments    |    Word  Exec.  |   Data   Exec.  |   Data   Exec.  |   Data   Exec.  |                    SLOC                    | File  SLOC" << endl;
					(*pout) << "   Lines   Lines |   Whole Embedded |     LOC  Instr. |   Decl.  Instr. |   Decl.  Instr. |   Decl.  Instr. |    HTML JS-Clnt VBS-Clnt C#-Clnt     Total | Type  Definition" << endl;
					(*pout) << "-----------------+------------------+-----------------+-----------------+-----------------+----------------------------------------------------+---------+------------------" << endl;
				}

				(*pout).setf(ios::right);
				(*pout).width(8);		(*pout) << itto->second.total_line;
				(*pout) << " ";
				(*pout).width(7);		(*pout) << itto->second.blank_line;
				(*pout) << " |";
				(*pout).width(8);		(*pout) << itto->second.whole_comment;
				(*pout) << " ";
				(*pout).width(8);		(*pout) << itto->second.embed_comment;
				(*pout) << " |";
				(*pout).width(8);		(*pout) << itto->second.phy_decl[0];
				(*pout) << " ";
				(*pout).width(7);		(*pout) << itto->second.phy_instr[0];
				(*pout) << " |";
				(*pout).width(8);		(*pout) << itto->second.phy_decl[1];
				(*pout) << " ";
				(*pout).width(7);		(*pout) << itto->second.phy_instr[1];
				(*pout) << " |";
				(*pout).width(8);		(*pout) << itto->second.phy_decl[2];
				(*pout) << " ";
				(*pout).width(7);		(*pout) << itto->second.phy_instr[2];
				(*pout) << " |";
				(*pout).width(8);		(*pout) << itto->second.phy_decl[3];
				(*pout) << " ";
				(*pout).width(7);		(*pout) << itto->second.phy_instr[3];
				if (print_legacy)
				{
					(*pout) << " |";
					(*pout).width(8);	(*pout) << (itto->second.phy_decl[0] + itto->second.phy_instr[0] +
						itto->second.phy_decl[1] + itto->second.phy_instr[1] +
						itto->second.phy_decl[2] + itto->second.phy_instr[2] +
						itto->second.phy_decl[3] + itto->second.phy_instr[3]);
				}
				(*pout) << " |";
				(*pout).width(8);		(*pout) << (itto->second.phy_decl[0] + itto->second.phy_instr[0]);
				(*pout) << " ";
				(*pout).width(7);		(*pout) << (itto->second.phy_decl[1] + itto->second.phy_instr[1]);
				(*pout) << " ";
				(*pout).width(8);		(*pout) << (itto->second.phy_decl[2] + itto->second.phy_instr[2]);
				(*pout) << " ";
				(*pout).width(7);		(*pout) << (itto->second.phy_decl[3] + itto->second.phy_instr[3]);
				if (!print_legacy)
				{
					(*pout) << " |";
					(*pout).width(8);	(*pout) << (itto->second.phy_decl[0] + itto->second.phy_instr[0] +
						itto->second.phy_decl[1] + itto->second.phy_instr[1] +
						itto->second.phy_decl[2] + itto->second.phy_instr[2] +
						itto->second.phy_decl[3] + itto->second.phy_instr[3]);
				}
				(*pout) << " | CODE  Physical" << endl;

				(*pout).setf(ios::right);
				(*pout).width(8);		(*pout) << itto->second.total_line;
				(*pout) << " ";
				(*pout).width(7);		(*pout) << itto->second.blank_line;
				(*pout) << " |";
				(*pout).width(8);		(*pout) << itto->second.whole_comment;
				(*pout) << " ";
				(*pout).width(8);		(*pout) << itto->second.embed_comment;
				(*pout) << " |";
				(*pout).width(8);		(*pout) << itto->second.log_decl[0];
				(*pout) << " ";
				(*pout).width(7);		(*pout) << itto->second.log_instr[0];
				(*pout) << " |";
				(*pout).width(8);		(*pout) << itto->second.log_decl[1];
				(*pout) << " ";
				(*pout).width(7);		(*pout) << itto->second.log_instr[1];
				(*pout) << " |";
				(*pout).width(8);		(*pout) << itto->second.log_decl[2];
				(*pout) << " ";
				(*pout).width(7);		(*pout) << itto->second.log_instr[2];
				(*pout) << " |";
				(*pout).width(8);		(*pout) << itto->second.log_decl[3];
				(*pout) << " ";
				(*pout).width(7);		(*pout) << itto->second.log_instr[3];
				if (print_legacy)
				{
					(*pout) << " |";
					(*pout).width(8);	(*pout) << (itto->second.log_decl[0] + itto->second.log_instr[0] +
						itto->second.log_decl[1] + itto->second.log_instr[1] +
						itto->second.log_decl[2] + itto->second.log_instr[2] +
						itto->second.log_decl[3] + itto->second.log_instr[3]);
				}
				(*pout) << " |";
				(*pout).width(8);		(*pout) << (itto->second.log_decl[0] + itto->second.log_instr[0]);
				(*pout) << " ";
				(*pout).width(7);		(*pout) << (itto->second.log_decl[1] + itto->second.log_instr[1]);
				(*pout) << " ";
				(*pout).width(8);		(*pout) << (itto->second.log_decl[2] + itto->second.log_instr[2]);
				(*pout) << " ";
				(*pout).width(7);		(*pout) << (itto->second.log_decl[3] + itto->second.log_instr[3]);
				if (!print_legacy)
				{
					(*pout) << " |";
					(*pout).width(8);	(*pout) << (itto->second.log_decl[0] + itto->second.log_instr[0] +
						itto->second.log_decl[1] + itto->second.log_instr[1] +
						itto->second.log_decl[2] + itto->second.log_instr[2] +
						itto->second.log_decl[3] + itto->second.log_instr[3]);
				}
				(*pout) << " | CODE  Logical" << endl;
			}
			if (print_csv)
			{
				pout_csv = webCounter->GetOutputStream(WEB_HTM, outDir + outputFileNamePrePend, cmdLine, true);

				(*pout_csv) << endl;
				CUtil::PrintFileHeaderLine(*pout_csv, "RESULTS SUMMARY");
				(*pout_csv) << endl;
				(*pout_csv) << ",,,,HTML,,JS-Clnt,,VBS-Clnt,,C#-Clnt" << endl;
				(*pout_csv) << "Total,Blank,Comments,,Word,Exec.,Data,Exec.,Data,Exec.,Data,Exec.,SLOC,,,,,File,SLOC" << endl;
				(*pout_csv) << "Lines,Lines,Whole,Embedded,LOC,Instr.,Decl.,Instr.,Decl.,Instr.,Decl.,Instr.,HTML,JS-Clnt,VBS-Clnt,C#-Clnt,Total,Type,Definition" << endl;

				(*pout_csv) << itto->second.total_line << ",";
				(*pout_csv) << itto->second.blank_line << ",";
				(*pout_csv) << itto->second.whole_comment << ",";
				(*pout_csv) << itto->second.embed_comment << ",";
				(*pout_csv) << itto->second.phy_decl[0] << ",";
				(*pout_csv) << itto->second.phy_instr[0] << ",";
				(*pout_csv) << itto->second.phy_decl[1] << ",";
				(*pout_csv) << itto->second.phy_instr[1] << ",";
				(*pout_csv) << itto->second.phy_decl[2] << ",";
				(*pout_csv) << itto->second.phy_instr[2] << ",";
				(*pout_csv) << itto->second.phy_decl[3] << ",";
				(*pout_csv) << itto->second.phy_instr[3] << ",";
				(*pout_csv) << (itto->second.phy_decl[0] + itto->second.phy_instr[0]) << ",";
				(*pout_csv) << (itto->second.phy_decl[1] + itto->second.phy_instr[1]) << ",";
				(*pout_csv) << (itto->second.phy_decl[2] + itto->second.phy_instr[2]) << ",";
				(*pout_csv) << (itto->second.phy_decl[3] + itto->second.phy_instr[3]) << ",";
				(*pout_csv) << (itto->second.phy_decl[0] + itto->second.phy_instr[0] +
					itto->second.phy_decl[1] + itto->second.phy_instr[1] +
					itto->second.phy_decl[2] + itto->second.phy_instr[2] +
					itto->second.phy_decl[3] + itto->second.phy_instr[3]) << ",";
				(*pout_csv) << "CODE,Physical" << endl;

				(*pout_csv) << itto->second.total_line << ",";
				(*pout_csv) << itto->second.blank_line << ",";
				(*pout_csv) << itto->second.whole_comment << ",";
				(*pout_csv) << itto->second.embed_comment << ",";
				(*pout_csv) << itto->second.log_decl[0] << ",";
				(*pout_csv) << itto->second.log_instr[0] << ",";
				(*pout_csv) << itto->second.log_decl[1] << ",";
				(*pout_csv) << itto->second.log_instr[1] << ",";
				(*pout_csv) << itto->second.log_decl[2] << ",";
				(*pout_csv) << itto->second.log_instr[2] << ",";
				(*pout_csv) << itto->second.log_decl[3] << ",";
				(*pout_csv) << itto->second.log_instr[3] << ",";
				(*pout_csv) << (itto->second.log_decl[0] + itto->second.log_instr[0]) << ",";
				(*pout_csv) << (itto->second.log_decl[1] + itto->second.log_instr[1]) << ",";
				(*pout_csv) << (itto->second.log_decl[2] + itto->second.log_instr[2]) << ",";
				(*pout_csv) << (itto->second.log_decl[3] + itto->second.log_instr[3]) << ",";
				(*pout_csv) << (itto->second.log_decl[0] + itto->second.log_instr[0] +
					itto->second.log_decl[1] + itto->second.log_instr[1] +
					itto->second.log_decl[2] + itto->second.log_instr[2] +
					itto->second.log_decl[3] + itto->second.log_instr[3]) << ",";
				(*pout_csv) << "CODE,Logical" << endl;
			}
		}

		// display statistics
		if (print_ascii || print_legacy)
		{
			(*pout) << endl << "Number of files successfully accessed........................ ";
			(*pout).width(5);		(*pout) << itto->second.num_of_file;
			(*pout) << " out of ";

			if (filesToPrint != NULL)
			{
				if (excludeFiles)
				{
					if (useListA)
					{
						if (itto->first == WEB_PHP)
							(*pout) << webCounter->total_php_filesA - webCounter->total_php_dupFilesA << endl;
						else if (itto->first == WEB_ASP)
							(*pout) << webCounter->total_asp_filesA - webCounter->total_asp_dupFilesA << endl;
						else if (itto->first == WEB_JSP)
							(*pout) << webCounter->total_jsp_filesA - webCounter->total_jsp_dupFilesA << endl;
						else if (itto->first == WEB_XML)
							(*pout) << webCounter->total_xml_filesA - webCounter->total_xml_dupFilesA << endl;
						else if (itto->first == WEB_CFM)
							(*pout) << webCounter->total_cfm_filesA - webCounter->total_cfm_dupFilesA << endl;
						else
							(*pout) << webCounter->total_htm_filesA - webCounter->total_htm_dupFilesA << endl;
					}
					else
					{
						if (itto->first == WEB_PHP)
							(*pout) << webCounter->total_php_filesB - webCounter->total_php_dupFilesB << endl;
						else if (itto->first == WEB_ASP)
							(*pout) << webCounter->total_asp_filesB - webCounter->total_asp_dupFilesB << endl;
						else if (itto->first == WEB_JSP)
							(*pout) << webCounter->total_jsp_filesB - webCounter->total_jsp_dupFilesB << endl;
						else if (itto->first == WEB_XML)
							(*pout) << webCounter->total_xml_filesB - webCounter->total_xml_dupFilesB << endl;
						else if (itto->first == WEB_CFM)
							(*pout) << webCounter->total_cfm_filesB - webCounter->total_cfm_dupFilesB << endl;
						else
							(*pout) << webCounter->total_htm_filesB - webCounter->total_htm_dupFilesB << endl;
					}
				}
				else
				{
					if (useListA)
					{
						if (itto->first == WEB_PHP)
							(*pout) << webCounter->total_php_dupFilesA << endl;
						else if (itto->first == WEB_ASP)
							(*pout) << webCounter->total_asp_dupFilesA << endl;
						else if (itto->first == WEB_JSP)
							(*pout) << webCounter->total_jsp_dupFilesA << endl;
						else if (itto->first == WEB_XML)
							(*pout) << webCounter->total_xml_dupFilesA << endl;
						else if (itto->first == WEB_CFM)
							(*pout) << webCounter->total_cfm_dupFilesA << endl;
						else
							(*pout) << webCounter->total_htm_dupFilesA << endl;
					}
					else
					{
						if (itto->first == WEB_PHP)
							(*pout) << webCounter->total_php_dupFilesB << endl;
						else if (itto->first == WEB_ASP)
							(*pout) << webCounter->total_asp_dupFilesB << endl;
						else if (itto->first == WEB_JSP)
							(*pout) << webCounter->total_jsp_dupFilesB << endl;
						else if (itto->first == WEB_XML)
							(*pout) << webCounter->total_xml_dupFilesB << endl;
						else if (itto->first == WEB_CFM)
							(*pout) << webCounter->total_cfm_dupFilesB << endl;
						else
							(*pout) << webCounter->total_htm_dupFilesB << endl;
					}
				}
			}
			else if (useListA)
			{
				if (itto->first == WEB_PHP)
					(*pout) << webCounter->total_php_filesA << endl;
				else if (itto->first == WEB_ASP)
					(*pout) << webCounter->total_asp_filesA << endl;
				else if (itto->first == WEB_JSP)
					(*pout) << webCounter->total_jsp_filesA << endl;
				else if (itto->first == WEB_XML)
					(*pout) << webCounter->total_xml_filesA << endl;
				else if (itto->first == WEB_CFM)
					(*pout) << webCounter->total_cfm_filesA << endl;
				else
					(*pout) << webCounter->total_htm_filesA << endl;
			}
			else
			{
				if (itto->first == WEB_PHP)
					(*pout) << webCounter->total_php_filesB << endl;
				else if (itto->first == WEB_ASP)
					(*pout) << webCounter->total_asp_filesB << endl;
				else if (itto->first == WEB_JSP)
					(*pout) << webCounter->total_jsp_filesB << endl;
				else if (itto->first == WEB_XML)
					(*pout) << webCounter->total_xml_filesB << endl;
				else if (itto->first == WEB_CFM)
					(*pout) << webCounter->total_cfm_filesB << endl;
				else
					(*pout) << webCounter->total_htm_filesB << endl;
			}

			(*pout) << endl << "Ratio of Physical to Logical SLOC............................ ";
		}
		if (print_csv)
		{
			(*pout_csv) << endl << "Number of files successfully accessed,";
			(*pout_csv) << itto->second.num_of_file;
			(*pout_csv) << ",out of,";

			if (filesToPrint != NULL)
			{
				if (excludeFiles)
				{
					if (useListA)
					{
						if (itto->first == WEB_PHP)
							(*pout_csv) << webCounter->total_php_filesA - webCounter->total_php_dupFilesA << endl;
						else if (itto->first == WEB_ASP)
							(*pout_csv) << webCounter->total_asp_filesA - webCounter->total_asp_dupFilesA << endl;
						else if (itto->first == WEB_JSP)
							(*pout_csv) << webCounter->total_jsp_filesA - webCounter->total_jsp_dupFilesA << endl;
						else if (itto->first == WEB_XML)
							(*pout_csv) << webCounter->total_xml_filesA - webCounter->total_xml_dupFilesA << endl;
						else if (itto->first == WEB_CFM)
							(*pout_csv) << webCounter->total_cfm_filesA - webCounter->total_cfm_dupFilesA << endl;
						else
							(*pout_csv) << webCounter->total_htm_filesA - webCounter->total_htm_dupFilesA << endl;
					}
					else
					{
						if (itto->first == WEB_PHP)
							(*pout_csv) << webCounter->total_php_filesB - webCounter->total_php_dupFilesB << endl;
						else if (itto->first == WEB_ASP)
							(*pout_csv) << webCounter->total_asp_filesB - webCounter->total_asp_dupFilesB << endl;
						else if (itto->first == WEB_JSP)
							(*pout_csv) << webCounter->total_jsp_filesB - webCounter->total_jsp_dupFilesB << endl;
						else if (itto->first == WEB_XML)
							(*pout_csv) << webCounter->total_xml_filesB - webCounter->total_xml_dupFilesB << endl;
						else if (itto->first == WEB_CFM)
							(*pout_csv) << webCounter->total_cfm_filesB - webCounter->total_cfm_dupFilesB << endl;
						else
							(*pout_csv) << webCounter->total_htm_filesB - webCounter->total_htm_dupFilesB << endl;
					}
				}
				else
				{
					if (useListA)
					{
						if (itto->first == WEB_PHP)
							(*pout_csv) << webCounter->total_php_dupFilesA << endl;
						else if (itto->first == WEB_ASP)
							(*pout_csv) << webCounter->total_asp_dupFilesA << endl;
						else if (itto->first == WEB_JSP)
							(*pout_csv) << webCounter->total_jsp_dupFilesA << endl;
						else if (itto->first == WEB_XML)
							(*pout_csv) << webCounter->total_xml_dupFilesA << endl;
						else if (itto->first == WEB_CFM)
							(*pout_csv) << webCounter->total_cfm_dupFilesA << endl;
						else
							(*pout_csv) << webCounter->total_htm_dupFilesA << endl;
					}
					else
					{
						if (itto->first == WEB_PHP)
							(*pout_csv) << webCounter->total_php_dupFilesB << endl;
						else if (itto->first == WEB_ASP)
							(*pout_csv) << webCounter->total_asp_dupFilesB << endl;
						else if (itto->first == WEB_JSP)
							(*pout_csv) << webCounter->total_jsp_dupFilesB << endl;
						else if (itto->first == WEB_XML)
							(*pout_csv) << webCounter->total_xml_dupFilesB << endl;
						else if (itto->first == WEB_CFM)
							(*pout_csv) << webCounter->total_cfm_dupFilesB << endl;
						else
							(*pout_csv) << webCounter->total_htm_dupFilesB << endl;
					}
				}
			}
			else if (useListA)
			{
				if (itto->first == WEB_PHP)
					(*pout_csv) << webCounter->total_php_filesA << endl;
				else if (itto->first == WEB_ASP)
					(*pout_csv) << webCounter->total_asp_filesA << endl;
				else if (itto->first == WEB_JSP)
					(*pout_csv) << webCounter->total_jsp_filesA << endl;
				else if (itto->first == WEB_XML)
					(*pout_csv) << webCounter->total_xml_filesA << endl;
				else if (itto->first == WEB_CFM)
					(*pout_csv) << webCounter->total_cfm_filesA << endl;
				else
					(*pout_csv) << webCounter->total_htm_filesA << endl;
			}
			else
			{
				if (itto->first == WEB_PHP)
					(*pout_csv) << webCounter->total_php_filesB << endl;
				else if (itto->first == WEB_ASP)
					(*pout_csv) << webCounter->total_asp_filesB << endl;
				else if (itto->first == WEB_JSP)
					(*pout_csv) << webCounter->total_jsp_filesB << endl;
				else if (itto->first == WEB_XML)
					(*pout_csv) << webCounter->total_xml_filesB << endl;
				else if (itto->first == WEB_CFM)
					(*pout_csv) << webCounter->total_cfm_filesB << endl;
				else
					(*pout_csv) << webCounter->total_htm_filesB << endl;
			}

			(*pout_csv) << endl << "Ratio of Physical to Logical SLOC,";
		}

		unsigned int tlsloc = itto->second.log_decl[0] + itto->second.log_instr[0] +
			itto->second.log_decl[1] + itto->second.log_instr[1] +
			itto->second.log_decl[2] + itto->second.log_instr[2] +
			itto->second.log_decl[3] + itto->second.log_instr[3] +
			itto->second.log_decl[4] + itto->second.log_instr[4] +
			itto->second.log_decl[5] + itto->second.log_instr[5];
		if (tlsloc > 0)
		{
			unsigned int tpsloc = itto->second.phy_decl[0] + itto->second.phy_instr[0] +
				itto->second.phy_decl[1] + itto->second.phy_instr[1] +
				itto->second.phy_decl[2] + itto->second.phy_instr[2] +
				itto->second.phy_decl[3] + itto->second.phy_instr[3] +
				itto->second.phy_decl[4] + itto->second.phy_instr[4] +
				itto->second.phy_decl[5] + itto->second.phy_instr[5];
			float tslocrat = (float)tpsloc / (float)tlsloc;

			if (print_ascii || print_legacy)
			{
				(*pout).setf(ios::fixed,ios::floatfield);
				(*pout).width(8);
				(*pout).precision(2);
				(*pout) << tslocrat << endl;
				(*pout).unsetf(ios::floatfield);
			}
			if (print_csv)
			{
				(*pout_csv).setf(ios::fixed,ios::floatfield);
				(*pout_csv).width(8);
				(*pout_csv).precision(2);
				(*pout_csv) << tslocrat << endl;
				(*pout_csv).unsetf(ios::floatfield);
			}
		}
		else
		{
			if (print_ascii || print_legacy)
				(*pout) << "    NA" << endl;
			if (print_csv)
				(*pout_csv) << "NA" << endl;
		}
	}

	// display summary for other languages, other than WEB
	for (TotalValueMap::iterator itto = total.begin(); itto != total.end(); itto++)
	{
		if (print_ascii || print_legacy)
		{
			pout = CounterForEachLanguage[itto->first]->GetOutputStream(outDir + outputFileNamePrePend, cmdLine);

			(*pout) << endl;
			CUtil::PrintFileHeaderLine(*pout, "RESULTS SUMMARY");
			(*pout) << endl;
			if (print_legacy)
			{
				(*pout) << "   Total   Blank |      Comments    | Compiler  Data   Exec.  |  Number  |         | File  SLOC" << endl;
				(*pout) << "   Lines   Lines |   Whole Embedded | Direct.   Decl.  Instr. | of Files |   SLOC  | Type  Definition" << endl;
				(*pout) << "-----------------+------------------+-------------------------+----------+---------+------------------" << endl;
			}
			else
			{
				(*pout) << "   Total   Blank |      Comments    | Compiler  Data   Exec.  |         | File  SLOC" << endl;
				(*pout) << "   Lines   Lines |   Whole Embedded | Direct.   Decl.  Instr. |   SLOC  | Type  Definition" << endl;
				(*pout) << "-----------------+------------------+-------------------------+---------+------------------" << endl;
			}

			(*pout).setf(ios::right);
			(*pout).width(8);		(*pout) << itto->second.total_line;
			(*pout) << " ";
			(*pout).width(7);		(*pout) << itto->second.blank_line;
			(*pout) << " |";
			(*pout).width(8);		(*pout) << itto->second.whole_comment;
			(*pout) << " ";
			(*pout).width(8);		(*pout) << itto->second.embed_comment;
			(*pout) << " |";
			(*pout).width(8);		(*pout) << itto->second.phy_direct;
			(*pout) << " ";
			(*pout).width(7);		(*pout) << itto->second.phy_decl;
			(*pout) << " ";
			(*pout).width(7);		(*pout) << itto->second.phy_instr;
			if (print_legacy)
			{
				(*pout) << " |";
				(*pout).width(8);		(*pout) << itto->second.num_of_file;
			}
			(*pout) << " |";
			(*pout).width(8);		(*pout) << itto->second.phy_direct + itto->second.phy_decl + itto->second.phy_instr;
			(*pout) << " | CODE  Physical" << endl;

			(*pout).setf(ios::right);
			(*pout).width(8);		(*pout) << itto->second.total_line;
			(*pout) << " ";
			(*pout).width(7);		(*pout) << itto->second.blank_line;
			(*pout) << " |";
			(*pout).width(8);		(*pout) << itto->second.whole_comment;
			(*pout) << " ";
			(*pout).width(8);		(*pout) << itto->second.embed_comment;
			(*pout) << " |";

			(*pout).width(8);		(*pout) << itto->second.log_direct;
			(*pout) << " ";
			(*pout).width(7);		(*pout) << itto->second.log_decl;
			(*pout) << " ";
			(*pout).width(7);		(*pout) << itto->second.log_instr;
			if (print_legacy)
			{
				(*pout) << " |";
				(*pout).width(8);		(*pout) << itto->second.num_of_file;
			}
			(*pout) << " |";
			(*pout).width(8);		(*pout) << itto->second.log_direct + itto->second.log_decl + itto->second.log_instr;
			(*pout) << " | CODE  Logical" << endl;

			// display statistics
			(*pout) << endl << "Number of files successfully accessed........................ ";
			(*pout).width(5);		(*pout) << itto->second.num_of_file;
			(*pout) << " out of ";
			if (filesToPrint != NULL)
			{
				if (excludeFiles)
				{
					if (useListA)
						(*pout) << CounterForEachLanguage[itto->first]->total_filesA - CounterForEachLanguage[itto->first]->total_dupFilesA << endl;
					else
						(*pout) << CounterForEachLanguage[itto->first]->total_filesB - CounterForEachLanguage[itto->first]->total_dupFilesB << endl;
				}
				else
				{
					if (useListA)
						(*pout) << CounterForEachLanguage[itto->first]->total_dupFilesA << endl;
					else
						(*pout) << CounterForEachLanguage[itto->first]->total_dupFilesB << endl;
				}
			}
			else if (useListA)
				(*pout) << CounterForEachLanguage[itto->first]->total_filesA << endl;
			else
				(*pout) << CounterForEachLanguage[itto->first]->total_filesB << endl;

			(*pout) << endl << "Ratio of Physical to Logical SLOC............................ ";
		}
		if (print_csv)
		{
			pout_csv = CounterForEachLanguage[itto->first]->GetOutputStream(outDir + outputFileNamePrePend, cmdLine, true);

			(*pout_csv) << endl;
			CUtil::PrintFileHeaderLine(*pout_csv, "RESULTS SUMMARY");
			(*pout_csv) << endl;
			(*pout_csv) << "Total,Blank,Comments,,Compiler,Data,Exec.,,File,SLOC" << endl;
			(*pout_csv) << "Lines,Lines,Whole,Embedded,Direct.,Decl.,Instr.,SLOC,Type,Definition" << endl;

			(*pout_csv) << itto->second.total_line << ",";
			(*pout_csv) << itto->second.blank_line << ",";
			(*pout_csv) << itto->second.whole_comment << ",";
			(*pout_csv) << itto->second.embed_comment << ",";
			(*pout_csv) << itto->second.phy_direct << ",";
			(*pout_csv) << itto->second.phy_decl << ",";
			(*pout_csv) << itto->second.phy_instr << ",";
			(*pout_csv) << itto->second.phy_direct + itto->second.phy_decl + itto->second.phy_instr << ",";
			(*pout_csv) << "CODE,Physical" << endl;

			(*pout_csv) << itto->second.total_line << ",";
			(*pout_csv) << itto->second.blank_line << ",";
			(*pout_csv) << itto->second.whole_comment << ",";
			(*pout_csv) << itto->second.embed_comment << ",";

			(*pout_csv) << itto->second.log_direct << ",";
			(*pout_csv) << itto->second.log_decl << ",";
			(*pout_csv) << itto->second.log_instr << ",";
			(*pout_csv) << itto->second.log_direct + itto->second.log_decl + itto->second.log_instr << ",";
			(*pout_csv) << "CODE,Logical" << endl;

			// display statistics
			(*pout_csv) << endl << "Number of files successfully accessed,";
			(*pout_csv) << itto->second.num_of_file;
			(*pout_csv) << ",out of,";

			if (filesToPrint != NULL)
			{
				if (excludeFiles)
				{
					if (useListA)
						(*pout_csv) << CounterForEachLanguage[itto->first]->total_filesA - CounterForEachLanguage[itto->first]->total_dupFilesA << endl;
					else
						(*pout_csv) << CounterForEachLanguage[itto->first]->total_filesB - CounterForEachLanguage[itto->first]->total_dupFilesB << endl;
				}
				else
				{
					if (useListA)
						(*pout_csv) << CounterForEachLanguage[itto->first]->total_dupFilesA << endl;
					else
						(*pout_csv) << CounterForEachLanguage[itto->first]->total_dupFilesB << endl;
				}
			}
			else if (useListA)
				(*pout_csv) << CounterForEachLanguage[itto->first]->total_filesA << endl;
			else
				(*pout_csv) << CounterForEachLanguage[itto->first]->total_filesB << endl;

			(*pout_csv) << endl << "Ratio of Physical to Logical SLOC,";
		}
		
		unsigned int tlsloc = itto->second.log_direct + itto->second.log_decl + itto->second.log_instr;
		if (tlsloc > 0)
		{
			unsigned int tpsloc = itto->second.phy_direct + itto->second.phy_decl + itto->second.phy_instr;
			float tslocrat = (float)tpsloc / (float)tlsloc;

			if (print_ascii || print_legacy)
			{
				(*pout).setf(ios::fixed,ios::floatfield);
				(*pout).width(8);
				(*pout).precision(2);
				(*pout) << tslocrat << endl;
				(*pout).unsetf(ios::floatfield);
			}
			if (print_csv)
			{
				(*pout_csv).setf(ios::fixed,ios::floatfield);
				(*pout_csv).width(8);
				(*pout_csv).precision(2);
				(*pout_csv) << tslocrat << endl;
				(*pout_csv).unsetf(ios::floatfield);
			}
		}
		else
		{
			if (print_ascii || print_legacy)
				(*pout) << "    NA" << endl;
			if (print_csv)
				(*pout_csv) << "NA" << endl;
		}
	}

	if (print_cmplx)
	{
		string dots = "........................";
		UIntPairVector::iterator idirc;
		UIntPairVector::iterator idatc;
		UIntPairVector::iterator iexec;
		StringVector::iterator idir;
		StringVector::iterator idat;
		StringVector::iterator iexe;

		// display keywords counts
		unsigned int ty;
		for (map<int, CCodeCounter*>::iterator iter = ++CounterForEachLanguage.begin(); iter != CounterForEachLanguage.end(); iter++)
		{
			if (iter->second->directive.size() == 0 && iter->second->data_name_list.size() == 0 && iter->second->exec_name_list.size()  == 0)
				continue;
			else if (total.count(iter->second->classtype) == 0)
			{
				if (iter->second->isPrintKeyword && (excludeFiles ||
					(useListA && iter->second->total_dupFilesA > 0) || (!useListA && iter->second->total_dupFilesB > 0)))
				{
					ty = iter->second->classtype;
					if (ty == PHP || ty == HTML_PHP || ty == JAVASCRIPT_PHP || ty == VBS_PHP)
					{
						if (print_ascii || print_legacy)
							pout = ((CWebCounter*)CounterForEachLanguage[WEB])->GetOutputStream(WEB_PHP, outDir + outputFileNamePrePend, cmdLine);
						if (print_csv)
							pout_csv = ((CWebCounter*)CounterForEachLanguage[WEB])->GetOutputStream(WEB_PHP, outDir + outputFileNamePrePend, cmdLine, true);
					}
					else if (ty == JAVA_JSP || ty == HTML_JSP || ty == JAVASCRIPT_JSP || ty == VBS_JSP)
					{
						if (print_ascii || print_legacy)
							pout = ((CWebCounter*)CounterForEachLanguage[WEB])->GetOutputStream(WEB_JSP, outDir + outputFileNamePrePend, cmdLine);
						if (print_csv)
							pout_csv = ((CWebCounter*)CounterForEachLanguage[WEB])->GetOutputStream(WEB_JSP, outDir + outputFileNamePrePend, cmdLine, true);
					}
					else if (ty == HTML_ASP || ty == JAVASCRIPT_ASP_C || ty == VBS_ASP_C || ty == JAVASCRIPT_ASP_S || ty == VBS_ASP_S || ty == CSHARP_ASP_S)
					{
						if (print_ascii || print_legacy)
							pout = ((CWebCounter*)CounterForEachLanguage[WEB])->GetOutputStream(WEB_ASP, outDir + outputFileNamePrePend, cmdLine);
						if (print_csv)
							pout_csv = ((CWebCounter*)CounterForEachLanguage[WEB])->GetOutputStream(WEB_ASP, outDir + outputFileNamePrePend, cmdLine, true);
					}
					else if (ty == HTML || ty == JAVASCRIPT_HTML || ty == VBS_HTML || ty == CSHARP_HTML)
					{
						if (print_ascii || print_legacy)
							pout = ((CWebCounter*)CounterForEachLanguage[WEB])->GetOutputStream(WEB_HTM, outDir + outputFileNamePrePend, cmdLine);
						if (print_csv)
							pout_csv = ((CWebCounter*)CounterForEachLanguage[WEB])->GetOutputStream(WEB_HTM, outDir + outputFileNamePrePend, cmdLine, true);
					}
					else if (ty == XML || ty == JAVASCRIPT_XML || ty == VBS_XML || ty == CSHARP_XML)
					{
						if (print_ascii || print_legacy)
							pout = ((CWebCounter*)CounterForEachLanguage[WEB])->GetOutputStream(WEB_XML, outDir + outputFileNamePrePend, cmdLine);
						if (print_csv)
							pout_csv = ((CWebCounter*)CounterForEachLanguage[WEB])->GetOutputStream(WEB_XML, outDir + outputFileNamePrePend, cmdLine, true);
					}
					else if (ty == COLDFUSION || ty == CFSCRIPT || ty == HTML_CFM || ty == JAVASCRIPT_CFM || ty == VBS_CFM || ty == SQL_CFM)
					{
						if (print_ascii || print_legacy)
							pout = ((CWebCounter*)CounterForEachLanguage[WEB])->GetOutputStream(WEB_CFM, outDir + outputFileNamePrePend, cmdLine);
						if (print_csv)
							pout_csv = ((CWebCounter*)CounterForEachLanguage[WEB])->GetOutputStream(WEB_CFM, outDir + outputFileNamePrePend, cmdLine, true);
					}
					else
						continue;
				}
				else
					continue;
			}
			else
			{
				if (print_ascii || print_legacy)
					pout = CounterForEachLanguage[iter->second->classtype]->GetOutputStream(outDir + outputFileNamePrePend, cmdLine);
				if (print_csv)
					pout_csv = CounterForEachLanguage[iter->second->classtype]->GetOutputStream(outDir + outputFileNamePrePend, cmdLine, true);
			}

			if (print_ascii || print_legacy)
			{
				(*pout) << endl;
				CUtil::PrintFileHeaderLine(*pout, "TOTAL OCCURRENCES OF " + iter->second->language_name + " KEYWORDS");
				(*pout) << "--------------------------------------------------------------------------------------------------------------" << endl;
				(*pout) << "    Compiler Directives                  Data Keywords                        Executable Keywords" << endl;
				(*pout).setf(ios::right);
			}
			if (print_csv)
			{
				(*pout_csv) << endl;
				CUtil::PrintFileHeaderLine(*pout_csv, "TOTAL OCCURRENCES OF " + iter->second->language_name + " KEYWORDS");
				(*pout_csv) << "Compiler Directives,,Data Keywords,,Executable Keywords" << endl;
			}

			idirc = iter->second->directive_count.begin();
			idatc = iter->second->data_name_count.begin();
			iexec = iter->second->exec_name_count.begin();
			idir = iter->second->directive.begin();
			idat = iter->second->data_name_list.begin();
			iexe = iter->second->exec_name_list.begin();

			while ( (idir != iter->second->directive.end()) || (idat != iter->second->data_name_list.end()) ||
				(iexe != iter->second->exec_name_list.end()) )
			{
				if (idir != iter->second->directive.end())
				{
					if (print_ascii || print_legacy)
					{
						(*pout) << ' ' << *idir << dots.substr(idir->length());
						(*pout).width(7);
						if (filesToPrint != NULL && !excludeFiles)
							(*pout) << (*idirc).second;
						else
							(*pout) << (*idirc).first;
					}
					if (print_csv)
					{
						(*pout_csv) << *idir << ",";
						if (filesToPrint != NULL && !excludeFiles)
							(*pout_csv) << (*idirc).second << ",";
						else
							(*pout_csv) << (*idirc).first << ",";
					}
					idir++;
					idirc++;
				}
				else
				{
					if (print_ascii || print_legacy)
						(*pout) << "                                ";
					if (print_csv)
						(*pout_csv) << ",,";
				}
				if (print_ascii || print_legacy)
					(*pout) << "     ";

				if (idat != iter->second->data_name_list.end())
				{
					if (print_ascii || print_legacy)
					{
						(*pout) << ' ' << *idat << dots.substr(idat->length());
						(*pout).width(7);
						if (filesToPrint != NULL && !excludeFiles)
							(*pout) << (*idatc).second;
						else
							(*pout) << (*idatc).first;
					}
					if (print_csv)
					{
						(*pout_csv) << *idat << ",";
						if (filesToPrint != NULL && !excludeFiles)
							(*pout_csv) << (*idatc).second << ",";
						else
							(*pout_csv) << (*idatc).first << ",";
					}
					idat++;
					idatc++;
				}
				else
				{
					if (print_ascii || print_legacy)
						(*pout) << "                                ";
					if (print_csv)
						(*pout_csv) << ",,";
				}
				if (print_ascii || print_legacy)
					(*pout) << "     ";

				if (iexe != iter->second->exec_name_list.end())
				{
					if (print_ascii || print_legacy)
					{
						(*pout) << ' ' << *iexe << dots.substr(iexe->length());
						(*pout).width(7);
						if (filesToPrint != NULL && !excludeFiles)
							(*pout) << (*iexec).second;
						else
							(*pout) << (*iexec).first;
					}
					if (print_csv)
					{
						(*pout_csv) << *iexe << ",";
						if (filesToPrint != NULL && !excludeFiles)
							(*pout_csv) << (*iexec).second;
						else
							(*pout_csv) << (*iexec).first;
					}
					iexe++;
					iexec++;
				}
				else
				{
					if (print_ascii || print_legacy)
						(*pout) << "                                ";
				}
				if (print_ascii || print_legacy)
					(*pout) << endl;
				if (print_csv)
					(*pout_csv) << endl;
			}
		}
	}

	// close all files
	for (map<int,CCodeCounter*>::iterator iter=CounterForEachLanguage.begin(); iter!=CounterForEachLanguage.end(); iter++)
		iter->second->CloseOutputStream();

	// print out language count summary
	if (!PrintCountSummary(total, webtotal, useListA, outputFileNamePrePend))
		return 0;

	return 1;
}

/*!
* Retrieves the total languages output file stream.
* Opens a new stream if it has not been opened already.
*
* \param outputFileNamePrePend name to prepend to the output file
* \param csvOutput CSV file stream? (otherwise ASCII text file)
*
* \return output file stream
*/
ofstream* MainObject::GetTotalOutputStream(const string &outputFileNamePrePend, bool csvOutput)
{
	if (csvOutput)
	{
		if (!output_file_csv.is_open())
		{
			string fname = outputFileNamePrePend + "TOTAL" + OUTPUT_FILE_NAME_CSV;
			output_file_csv.open(fname.c_str(), ofstream::out);

			if (!output_file_csv.is_open()) return NULL;

			CUtil::PrintFileHeader(output_file_csv, "SLOC COUNT RESULTS FOR ALL SOURCE FILES", cmdLine);
		}
		return &output_file_csv;
	}
	else
	{
		if (!output_file.is_open())
		{
			string fname = outputFileNamePrePend + "TOTAL" + OUTPUT_FILE_NAME;
			output_file.open(fname.c_str(), ofstream::out);

			if (!output_file.is_open()) return NULL;

			CUtil::PrintFileHeader(output_file, "SLOC COUNT RESULTS FOR ALL SOURCE FILES", cmdLine);
		}
		return &output_file;
	}
}

/*!
* Closes the total languages output file stream.
*/
void MainObject::CloseTotalOutputStream()
{
	if (output_file.is_open())
		output_file.close();
	if (output_file_csv.is_open())
		output_file_csv.close();
}

/*!
* Prints the total counting results.
*
* \param useListA use file list A? (otherwise use list B)
* \param outputFileNamePrePend name to prepend to the output file
* \param filesToPrint list of files to include or exclude
* \param excludeFiles exclude files? (if true excludes files in filesToPrint; if false includes only files in filesToPrint)
*
* \return method status
*/
int MainObject::PrintTotalCountResults(bool useListA, const string &outputFileNamePrePend, StringVector *filesToPrint, bool excludeFiles)
{
	ofstream* pout;
	ofstream* pout_csv;
	TotalValueMap total;
	WebTotalValueMap webtotal;
	TotalValue allLang;
	AllWebTotalValue allWebLang;
	unsigned int totalNonDupFileA = 0, totalNonDupWebFileA = 0, totalFileA = 0, totalWebFileA = 0;
	unsigned int totalNonDupFileB = 0, totalNonDupWebFileB = 0, totalFileB  = 0, totalWebFileB = 0;
	bool printHeader = false;
	unsigned int tlsloc = 0, tpsloc = 0;
	float tslocrat = 0.0f;
	unsigned int class_type;
	StringVector::iterator sit;
	CWebCounter *webCounter;
	WebType webType;

	// skip if all files are excluded
	if (filesToPrint != NULL && filesToPrint->size() < 1 && !excludeFiles)
		return 0;

	// display each non-web count
	SourceFileList::iterator its;
	SourceFileList* mySourceFile = (useListA) ? &SourceFileA : &SourceFileB;
	for (its = mySourceFile->begin(); its != mySourceFile->end(); its++)
	{
		if (filesToPrint != NULL && filesToPrint->size() > 0)
		{
			// restrict based on those files in the filesToPrint list
			sit = filesToPrint->begin();
			while (sit != filesToPrint->end() && its->second.file_name.compare((*sit)) != 0)
				sit++;

			if (excludeFiles)
			{
				// skip the file if in the filesToPrint list
				if (sit != filesToPrint->end())
					continue;
			}
			else
			{
				// skip the file if NOT in the filesToPrint list
				if (sit == filesToPrint->end())
					continue;
			}
		}

		// languages other than WEB
		if (its->second.class_type != WEB)
		{
			class_type = its->second.class_type;

			// do not print temp files that are created to represent embedded code
			if (its->second.file_name.find(EMBEDDED_FILE_PREFIX) != string::npos) 
				continue;

			if (total.count(class_type) == 0)
				total.insert(TotalValueMap::value_type(class_type, TotalValue()));

			// get the stream for non-web language, skip if already printed
			if (!printHeader)
			{
				if (print_ascii || print_legacy)
				{
					pout = GetTotalOutputStream(outDir + outputFileNamePrePend);
					if (pout == NULL)
					{
						string err = "Error: Unable to create file (";
						err += outputFileNamePrePend + "TOTAL" + OUTPUT_FILE_NAME;
						err += "). Operation aborted.";
						cout << endl << err << endl;
						CUtil::AddError(err);
						return 0;
					}
					// if there exists non-web language, print the header
					CUtil::PrintFileHeaderLine(*pout, "RESULTS FOR ALL NON-WEB LANGUAGE FILES");
					(*pout) << endl;
					if (print_legacy)
					{
						(*pout) << "   Total   Blank |      Comments    | Compiler  Data   Exec.  | Logical | File  Module" << endl;
						(*pout) << "   Lines   Lines |   Whole Embedded | Direct.   Decl.  Instr. |   SLOC  | Type  Name" << endl;
						(*pout) << "-----------------+------------------+-------------------------+---------+---------------------------" << endl;
					}
					else
					{
						(*pout) << "   Total   Blank |      Comments    | Compiler  Data   Exec.  | Logical Physical | File  Module" << endl;
						(*pout) << "   Lines   Lines |   Whole Embedded | Direct.   Decl.  Instr. |   SLOC    SLOC   | Type  Name" << endl;
						(*pout) << "-----------------+------------------+-------------------------+------------------+---------------------------" << endl;
					}
				}
				if (print_csv)
				{
					pout_csv = GetTotalOutputStream(outDir + outputFileNamePrePend, true);
					if (pout_csv == NULL)
					{
						string err = "Error: Unable to create file (";
						err += outputFileNamePrePend + "TOTAL" + OUTPUT_FILE_NAME_CSV;
						err += "). Operation aborted.";
						cout << endl << err << endl;
						CUtil::AddError(err);
						return 0;
					}
					// if there exists non-web language, print the header
					(*pout_csv) << endl << "          RESULTS FOR ALL NON-WEB LANGUAGE FILES" << endl;
					(*pout_csv) << "Total,Blank,Comments,,Compiler,Data,Exec.,Logical,Physical,File,Module" << endl;
					(*pout_csv) << "Lines,Lines,Whole,Embedded,Direct.,Decl.,Instr.,SLOC,SLOC,Type,Name" << endl;
				}
				printHeader = true;
			}

			if (its->second.e_flag)
			{
				if (print_ascii || print_legacy)
				{
					(*pout).setf(ios::left);
					(*pout) << " Error: ";
					(*pout).width(65);
					(*pout) << its->second.error_code;
					(*pout) << its->second.file_name << endl << endl;
					(*pout).unsetf(ios::left);
				}
				if (print_csv)
				{
					(*pout_csv) << "Error: ";
					(*pout_csv) << its->second.error_code << ",,,,,,,,,";
					(*pout_csv) << its->second.file_name << endl << endl;
				}
				continue;
			}
			else
			{
				its->second.SLOC_lines[PHY] = its->second.directive_lines[PHY] + its->second.exec_lines[PHY] + its->second.data_lines[PHY];
				its->second.SLOC_lines[LOG] = its->second.directive_lines[LOG] + its->second.exec_lines[LOG] + its->second.data_lines[LOG];
				its->second.total_lines = its->second.SLOC_lines[PHY] +	its->second.blank_lines + its->second.comment_lines;
			}

			total[class_type].num_of_file++;

			if (print_ascii || print_legacy)
			{
				(*pout).setf(ios::right);
				(*pout).width(8);		(*pout) << its->second.total_lines;
				(*pout) << " ";
				(*pout).width(7);		(*pout) << its->second.blank_lines;
				(*pout) << " |";
				(*pout).width(8);		(*pout) << its->second.comment_lines;
				(*pout) << " ";
				(*pout).width(8);		(*pout) << its->second.e_comm_lines;
				(*pout) << " |";
				(*pout).width(8);		(*pout) << its->second.directive_lines[LOG];
				(*pout) << " ";
				(*pout).width(7);		(*pout) << its->second.data_lines[LOG];
				(*pout) << " ";
				(*pout).width(7);		(*pout) << its->second.exec_lines[LOG];
				(*pout) << " |";
				if (print_legacy)
				{
					(*pout).width(8);	(*pout) << its->second.SLOC_lines[LOG];
				}
				else
				{
					(*pout).width(8);	(*pout) << its->second.SLOC_lines[LOG];
					(*pout) << " ";
					(*pout).width(8);	(*pout) << its->second.SLOC_lines[PHY];
				}
				(*pout) << (class_type != UNKNOWN && class_type != DATAFILE ? " | CODE" : " | DATA");
				(*pout) << " " << its->second.file_name;
				(*pout) << endl;
				(*pout).unsetf(ios::right);
			}
			if (print_csv)
			{
				(*pout_csv) << its->second.total_lines << ",";
				(*pout_csv) << its->second.blank_lines << ",";
				(*pout_csv) << its->second.comment_lines << ",";
				(*pout_csv) << its->second.e_comm_lines << ",";
				(*pout_csv) << its->second.directive_lines[LOG] << ",";
				(*pout_csv) << its->second.data_lines[LOG] << ",";
				(*pout_csv) << its->second.exec_lines[LOG] << ",";
				(*pout_csv) << its->second.SLOC_lines[LOG] << ",";
				(*pout_csv) << its->second.SLOC_lines[PHY] << ",";
				(*pout_csv) << (class_type != UNKNOWN && class_type != DATAFILE ? "CODE" : "DATA") << ",";
				(*pout_csv) << its->second.file_name << endl;
			}

			// total count for physical lines of this class type
			total[class_type].total_line += its->second.total_lines;
			total[class_type].blank_line += its->second.blank_lines;
			total[class_type].whole_comment += its->second.comment_lines;
			total[class_type].embed_comment += its->second.e_comm_lines;
			total[class_type].phy_direct += its->second.directive_lines[PHY];
			total[class_type].phy_decl += its->second.data_lines[PHY];
			total[class_type].phy_instr += its->second.exec_lines[PHY];
			total[class_type].log_direct += its->second.directive_lines[LOG];
			total[class_type].log_decl += its->second.data_lines[LOG];
			total[class_type].log_instr += its->second.exec_lines[LOG];

			// total count for physical lines of ALL languages
			allLang.total_line += its->second.total_lines;
			allLang.blank_line += its->second.blank_lines;
			allLang.whole_comment += its->second.comment_lines;
			allLang.embed_comment += its->second.e_comm_lines;
			allLang.phy_direct += its->second.directive_lines[PHY];
			allLang.phy_decl += its->second.data_lines[PHY];
			allLang.phy_instr += its->second.exec_lines[PHY];
			allLang.log_direct += its->second.directive_lines[LOG];
			allLang.log_decl += its->second.data_lines[LOG];
			allLang.log_instr += its->second.exec_lines[LOG];
			allLang.num_of_file++;
		}
	}

	// display summary for other languages, other than WEB
	for (TotalValueMap::iterator itto = total.begin(); itto != total.end(); itto++)
	{
		if (filesToPrint != NULL)
		{
			if (excludeFiles)
			{
				if (useListA)
					totalNonDupFileA += CounterForEachLanguage[itto->first]->total_filesA - CounterForEachLanguage[itto->first]->total_dupFilesA;
				else
					totalNonDupFileB += CounterForEachLanguage[itto->first]->total_filesB - CounterForEachLanguage[itto->first]->total_dupFilesB;
			}
			else
			{
				if (useListA)
					totalNonDupFileA += CounterForEachLanguage[itto->first]->total_dupFilesA;
				else
					totalNonDupFileB += CounterForEachLanguage[itto->first]->total_dupFilesB;
			}
		}
		else if (useListA)
			totalFileA += CounterForEachLanguage[itto->first]->total_filesA;
		else
			totalFileB += CounterForEachLanguage[itto->first]->total_filesB;

		tlsloc += itto->second.log_direct + itto->second.log_decl + itto->second.log_instr;
		tpsloc += itto->second.phy_direct + itto->second.phy_decl + itto->second.phy_instr;
	}

	// print other languages count summary
	if (total.size() > 0)
	{
		if (print_ascii || print_legacy)
		{
			(*pout) << endl;
			CUtil::PrintFileHeaderLine(*pout, "RESULTS SUMMARY FOR NON-WEB LANGUAGES");
			(*pout) << endl;
			if (print_legacy)
			{
				(*pout) << "   Total   Blank |      Comments    | Compiler  Data   Exec.  |  Number  |         | File  SLOC" << endl;
				(*pout) << "   Lines   Lines |   Whole Embedded | Direct.   Decl.  Instr. | of Files |   SLOC  | Type  Definition" << endl;
				(*pout) << "-----------------+------------------+-------------------------+----------+---------+------------------" << endl;
			}
			else
			{
				(*pout) << "   Total   Blank |      Comments    | Compiler  Data   Exec.  |         | File  SLOC" << endl;
				(*pout) << "   Lines   Lines |   Whole Embedded | Direct.   Decl.  Instr. |   SLOC  | Type  Definition" << endl;
				(*pout) << "-----------------+------------------+-------------------------+---------+------------------" << endl;
			}

			(*pout).setf(ios::right);
			(*pout).width(8);		(*pout) << allLang.total_line;
			(*pout) << " ";
			(*pout).width(7);		(*pout) << allLang.blank_line;
			(*pout) << " |";
			(*pout).width(8);		(*pout) << allLang.whole_comment;
			(*pout) << " ";
			(*pout).width(8);		(*pout) << allLang.embed_comment;
			(*pout) << " |";
			(*pout).width(8);		(*pout) << allLang.phy_direct;
			(*pout) << " ";
			(*pout).width(7);		(*pout) << allLang.phy_decl;
			(*pout) << " ";
			(*pout).width(7);		(*pout) << allLang.phy_instr;
			if (print_legacy)
			{
				(*pout) << " |";
				(*pout).width(8);		(*pout) << allLang.num_of_file;
			}
			(*pout) << " |";
			(*pout).width(8);		(*pout) << allLang.phy_direct + allLang.phy_decl + allLang.phy_instr;
			(*pout) << " | CODE  Physical" << endl;

			(*pout).setf(ios::right);
			(*pout).width(8);		(*pout) << allLang.total_line;
			(*pout) << " ";
			(*pout).width(7);		(*pout) << allLang.blank_line;
			(*pout) << " |";
			(*pout).width(8);		(*pout) << allLang.whole_comment;
			(*pout) << " ";
			(*pout).width(8);		(*pout) << allLang.embed_comment;
			(*pout) << " |";

			(*pout).width(8);		(*pout) << allLang.log_direct;
			(*pout) << " ";
			(*pout).width(7);		(*pout) << allLang.log_decl;
			(*pout) << " ";
			(*pout).width(7);		(*pout) << allLang.log_instr;
			if (print_legacy)
			{
				(*pout) << " |";
				(*pout).width(8);		(*pout) << allLang.num_of_file;
			}
			(*pout) << " |";
			(*pout).width(8);		(*pout) << allLang.log_direct + allLang.log_decl + allLang.log_instr;
			(*pout) << " | CODE  Logical" << endl;

			// display statistics
			(*pout) << endl << "Number of files successfully accessed........................ ";
			(*pout).width(5);		(*pout) << allLang.num_of_file;
			(*pout) << " out of ";
			if (filesToPrint != NULL)
			{
				if (useListA)
					(*pout) << totalNonDupFileA << endl;
				else
					(*pout) << totalNonDupFileB << endl;
			}
			else if (useListA)
				(*pout) << totalFileA << endl;
			else
				(*pout) << totalFileB << endl;

			(*pout) << endl << "Ratio of Physical to Logical SLOC............................ ";

			if (tlsloc > 0)
			{
				tslocrat = (float)tpsloc / (float)tlsloc;
				(*pout).setf(ios::fixed,ios::floatfield);
				(*pout).width(8);
				(*pout).precision(2);
				(*pout) << tslocrat << endl;
				(*pout).unsetf(ios::floatfield);
			}
			else
				(*pout) << "    NA" << endl;
		}
		if (print_csv)
		{
			(*pout_csv) << endl;
			CUtil::PrintFileHeaderLine(*pout_csv, "RESULTS SUMMARY FOR NON-WEB LANGUAGES");
			(*pout_csv) << "Total,Blank,Comments,,Compiler,Data,Exec.,,File,SLOC" << endl;
			(*pout_csv) << "Lines,Lines,Whole,Embedded,Direct.,Decl.,Instr.,SLOC,Type,Definition" << endl;

			(*pout_csv) << allLang.total_line << ",";
			(*pout_csv) << allLang.blank_line << ",";
			(*pout_csv) << allLang.whole_comment << ",";
			(*pout_csv) << allLang.embed_comment << ",";
			(*pout_csv) << allLang.phy_direct << ",";
			(*pout_csv) << allLang.phy_decl << ",";
			(*pout_csv) << allLang.phy_instr << ",";
			(*pout_csv) << allLang.phy_direct + allLang.phy_decl + allLang.phy_instr << ",";
			(*pout_csv) << "CODE,Physical" << endl;

			(*pout_csv) << allLang.total_line << ",";
			(*pout_csv) << allLang.blank_line << ",";
			(*pout_csv) << allLang.whole_comment << ",";
			(*pout_csv) << allLang.embed_comment << ",";

			(*pout_csv) << allLang.log_direct << ",";
			(*pout_csv) << allLang.log_decl << ",";
			(*pout_csv) << allLang.log_instr << ",";
			(*pout_csv) << allLang.log_direct + allLang.log_decl + allLang.log_instr << ",";
			(*pout_csv) << "CODE,Logical" << endl;

			// display statistics
			(*pout_csv) << endl << "Number of files successfully accessed,";
			(*pout_csv) << allLang.num_of_file;
			(*pout_csv) << ",out of,";

			if (filesToPrint != NULL)
			{
				if (useListA)
					(*pout_csv) << totalNonDupFileA << endl;
				else
					(*pout_csv) << totalNonDupFileB << endl;
			}
			else if (useListA)
				(*pout_csv) << totalFileA << endl;
			else
				(*pout_csv) << totalFileB << endl;

			(*pout_csv) << endl << "Ratio of Physical to Logical SLOC,";

			if (tlsloc > 0)
			{
				tslocrat = (float)tpsloc / (float)tlsloc;
				(*pout_csv).setf(ios::fixed,ios::floatfield);
				(*pout_csv).width(8);
				(*pout_csv).precision(2);
				(*pout_csv) << tslocrat << endl;
				(*pout_csv).unsetf(ios::floatfield);
			}
			else
				(*pout_csv) << "NA" << endl;
		}
	}

	// display web language count
	printHeader = false;
	for (its = mySourceFile->begin(); its != mySourceFile->end(); its++)
	{
		if (filesToPrint != NULL && filesToPrint->size() > 0)
		{
			// restrict based on those files in the filesToPrint list
			sit = filesToPrint->begin();
			while (sit != filesToPrint->end() && its->second.file_name.compare((*sit)) != 0)
				sit++;

			if (excludeFiles)
			{
				// skip the file if in the filesToPrint list
				if (sit != filesToPrint->end())
					continue;
			}
			else
			{
				// skip the file if NOT in the filesToPrint list
				if (sit == filesToPrint->end())
					continue;
			}
		}

		if (its->second.class_type == WEB)
		{
			SourceFileList::iterator startpos = its;
			SourceFileList::iterator endpos = ++startpos;
			for (; endpos!= mySourceFile->end(); endpos++)
			{
				if (endpos->second.file_name.find(EMBEDDED_FILE_PREFIX) == string::npos)
					break;
			}
			webType = ((CWebCounter*)CounterForEachLanguage[WEB])->GetWebType(its->second.file_name);

			// get the stream for web languages
			if (!printHeader)
			{
				if (print_ascii || print_legacy)
				{
					pout = GetTotalOutputStream(outDir + outputFileNamePrePend);
					if (pout == NULL)
					{
						string err = "Error: Unable to create file (";
						err += outputFileNamePrePend + "TOTAL" + OUTPUT_FILE_NAME;
						err += "). Operation aborted.";
						cout << endl << err << endl;
						CUtil::AddError(err);
						return 0;
					}
					// if there exists web language, append the header to the file
					(*pout) << endl;
					CUtil::PrintFileHeaderLine(*pout, "RESULTS FOR ALL WEB LANGUAGE FILES");
					(*pout) << endl;
					(*pout) << "                                    |       HTML      |        XML      |     JS-Clnt     |    VBS-Clnt     |     C#-Clnt     |      JS-Svr     |     VBS-Svr     |      C#-Svr     |           PHP           |          Java           |       SQL       |    ColdFusion   |     CFScript    |" << endl;
					if (print_legacy)
					{
						(*pout) << "   Total   Blank |      Comments    |    Word  Exec.  |    Word  Exec.  |   Data   Exec.  |   Data   Exec.  |   Data   Exec.  |   Data   Exec.  |   Data   Exec.  |   Data   Exec.  | Compiler  Data   Exec.  | Compiler  Data   Exec.  |   Data   Exec.  |   Data   Exec.  |   Data   Exec.  |                                                          Logical SLOC                                                  | File  Module" << endl;
						(*pout) << "   Lines   Lines |   Whole Embedded |     LOC  Instr. |     LOC  Instr. |   Decl.  Instr. |   Decl.  Instr. |   Decl.  Instr. |   Decl.  Instr. |   Decl.  Instr. |   Decl.  Instr. | Direct.   Decl.  Instr. | Direct.   Decl.  Instr. |   Decl.  Instr. |   Decl.  Instr. |   Decl.  Instr. |   Total      HTML     XML JS-Clnt VBS-Clnt C#-Clnt  JS-Svr VBS-Svr  C#-Svr     PHP    Java     SQL ColdFusion CFScript | Type  Name" << endl;
						(*pout) << "-----------------+------------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-------------------------+-------------------------+-----------------+-----------------+-----------------+---------+--------------------------------------------------------------------------------------------------------------+---------------------------" << endl;
					}
					else
					{
						(*pout) << "   Total   Blank |      Comments    |    Word  Exec.  |    Word  Exec.  |   Data   Exec.  |   Data   Exec.  |   Data   Exec.  |   Data   Exec.  |   Data   Exec.  |   Data   Exec.  | Compiler  Data   Exec.  | Compiler  Data   Exec.  |   Data   Exec.  |   Data   Exec.  |   Data   Exec.  |                                                          Logical SLOC                                                  | Physical | File  Module" << endl;
						(*pout) << "   Lines   Lines |   Whole Embedded |     LOC  Instr. |     LOC  Instr. |   Decl.  Instr. |   Decl.  Instr. |   Decl.  Instr. |   Decl.  Instr. |   Decl.  Instr. |   Decl.  Instr. | Direct.   Decl.  Instr. | Direct.   Decl.  Instr. |   Decl.  Instr. |   Decl.  Instr. |   Decl.  Instr. |    HTML     XML JS-Clnt VBS-Clnt C#-Clnt  JS-Svr VBS-Svr  C#-Svr     PHP    Java     SQL ColdFusion CFScript     Total |   SLOC   | Type  Name" << endl;
						(*pout) << "-----------------+------------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-------------------------+-------------------------+-----------------+-----------------+-----------------+--------------------------------------------------------------------------------------------------------------+---------+----------+---------------------------" << endl;
					}
				}
				if (print_csv)
				{
					pout_csv = GetTotalOutputStream(outDir + outputFileNamePrePend, true);
					if (pout_csv == NULL)
					{
						string err = "Error: Unable to create file (";
						err += outputFileNamePrePend + "Total" + OUTPUT_FILE_NAME_CSV;
						err += "). Operation aborted.";
						cout << endl << err << endl;
						CUtil::AddError(err);
						return 0;
					}
					// if there exists web lang, append the header to the file
					(*pout_csv) << endl;
					CUtil::PrintFileHeaderLine(*pout_csv, "RESULTS FOR ALL WEB LANGUAGE FILES");
					(*pout_csv) << endl;
					(*pout_csv) << ",,,,HTML,,XML,,JS-Clnt,,VBS-Clnt,,C#-Clnt,,JS-Svr,,VBS-Svr,,C#-Svr,,PHP,,,Java,,,SQL,,ColdFusion,,CFScript" << endl;
					(*pout_csv) << "Total,Blank,Comments,,Word,Exec.,Word,Exec.,Data,Exec.,Data,Exec.,Data,Exec.,Data,Exec.,Data,Exec.,Data,Exec.,Compiler,Data,Exec.,Compiler,Data,Exec.,Data,Exec.,Data,Exec.,Data,Exec.,Logical SLOC,,,,,,,,,,,,,,Physical,File,Module" << endl;
					(*pout_csv) << "Lines,Lines,Whole,Embedded,LOC,Instr.,LOC,Instr.,Decl.,Instr.,Decl.,Instr.,Decl.,Instr.,Decl.,Instr.,Decl.,Instr.,Decl.,Instr.,Direct.,Decl.,Instr.,Direct.,Decl.,Instr.,Decl.,Instr.,Decl.,Instr.,Decl.,Instr.,HTML,XML,JS-Clnt,VBS-Clnt,C#-Clnt,JS-Svr,VBS-Svr,C#-Svr,PHP,Java,SQL,ColdFusion,CFScript,Total,SLOC,Type,Name" << endl;
				}
				printHeader = true;
			}

			if (webType == WEB_PHP)
			{
				results r_htm;
				results r_js;
				results r_vbs;
				results r_php;
				for (SourceFileList::iterator i = startpos; i!= endpos; i++)
				{
					switch (i->second.class_type)
					{
					case HTML_PHP:
						r_htm = i->second;
						break;
					case JAVASCRIPT_PHP:
						r_js = i->second;
						break;
					case VBS_PHP:
						r_vbs = i->second;
						break;
					case PHP:
						r_php = i->second;
						break;
					}
				}
				r_htm.SLOC_lines[PHY] = r_htm.exec_lines[PHY] + r_htm.data_lines[PHY];
				r_htm.SLOC_lines[LOG] = r_htm.exec_lines[LOG] + r_htm.data_lines[LOG];
				r_htm.total_lines = r_htm.SLOC_lines[PHY] +	r_htm.blank_lines + r_htm.comment_lines;

				r_js.SLOC_lines[PHY] = r_js.exec_lines[PHY] + r_js.data_lines[PHY];
				r_js.SLOC_lines[LOG] = r_js.exec_lines[LOG] + r_js.data_lines[LOG];
				r_js.total_lines = r_js.SLOC_lines[PHY] +	r_js.blank_lines + r_js.comment_lines;

				r_vbs.SLOC_lines[PHY] = r_vbs.exec_lines[PHY] + r_vbs.data_lines[PHY];
				r_vbs.SLOC_lines[LOG] = r_vbs.exec_lines[LOG] + r_vbs.data_lines[LOG];
				r_vbs.total_lines = r_vbs.SLOC_lines[PHY] +	r_vbs.blank_lines + r_vbs.comment_lines;

				r_php.SLOC_lines[PHY] = r_php.directive_lines[PHY] + r_php.exec_lines[PHY] + r_php.data_lines[PHY];
				r_php.SLOC_lines[LOG] = r_php.directive_lines[LOG] + r_php.exec_lines[LOG] + r_php.data_lines[LOG];
				r_php.total_lines = r_php.SLOC_lines[PHY] +	r_php.blank_lines + r_php.comment_lines;

				if (print_ascii || print_legacy)
				{
					(*pout).setf(ios::right);
					(*pout).width(8);		(*pout) << (r_htm.total_lines + r_js.total_lines + r_vbs.total_lines + r_php.total_lines);
					(*pout) << " ";
					(*pout).width(7);		(*pout) << (r_htm.blank_lines + r_js.blank_lines + r_vbs.blank_lines + r_php.blank_lines);
					(*pout) << " |";
					(*pout).width(8);		(*pout) << (r_htm.comment_lines + r_js.comment_lines + r_vbs.comment_lines + r_php.comment_lines);
					(*pout) << " ";
					(*pout).width(8);		(*pout) << (r_htm.e_comm_lines + r_js.e_comm_lines + r_vbs.e_comm_lines + r_php.e_comm_lines);
					(*pout) << " |";
					(*pout).width(8);		(*pout) << r_htm.data_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_htm.exec_lines[LOG];
					(*pout) << " |";
					(*pout).width(8);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " |";
					(*pout).width(8);		(*pout) << r_js.data_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_js.exec_lines[LOG];
					(*pout) << " |";
					(*pout).width(8);		(*pout) << r_vbs.data_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_vbs.exec_lines[LOG];
					(*pout) << " |";
					(*pout).width(8);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " |";					
					(*pout).width(8);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " |";
					(*pout).width(8);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " |";
					(*pout).width(8);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " |";
					(*pout).width(8);		(*pout) << r_php.directive_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_php.data_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_php.exec_lines[LOG];
					(*pout) << " |";
					(*pout).width(8);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " |";
					(*pout).width(8);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " |";
					(*pout).width(8);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " |";
					(*pout).width(8);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					if (print_legacy)
					{
						(*pout) << " |";
						(*pout).width(8);	(*pout) << (r_htm.SLOC_lines[LOG] + r_js.SLOC_lines[LOG] + r_vbs.SLOC_lines[LOG] + r_php.SLOC_lines[LOG]);
					}
					(*pout) << " |";
					(*pout).width(8);		(*pout) << r_htm.SLOC_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_js.SLOC_lines[LOG];
					(*pout) << " ";
					(*pout).width(8);		(*pout) << r_vbs.SLOC_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_php.SLOC_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(10);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(8);		(*pout) << "0";
					if (!print_legacy)
					{
						(*pout) << " |";
						(*pout).width(8);	(*pout) << (r_htm.SLOC_lines[LOG] + r_js.SLOC_lines[LOG] + r_vbs.SLOC_lines[LOG] + r_php.SLOC_lines[LOG]);
						(*pout) << " |";
						(*pout).width(9);	(*pout) << (r_htm.SLOC_lines[PHY] + r_js.SLOC_lines[PHY] + r_vbs.SLOC_lines[PHY] + r_php.SLOC_lines[PHY]);
					}
					(*pout) << " | CODE  ";
					(*pout) << its->second.file_name << endl;
					(*pout).unsetf(ios::right);
				}
				if (print_csv)
				{
					(*pout_csv) << (r_htm.total_lines + r_js.total_lines + r_vbs.total_lines + r_php.total_lines) << ",";
					(*pout_csv) << (r_htm.blank_lines + r_js.blank_lines + r_vbs.blank_lines + r_php.blank_lines) << ",";
					(*pout_csv) << (r_htm.comment_lines + r_js.comment_lines + r_vbs.comment_lines + r_php.comment_lines) << ",";
					(*pout_csv) << (r_htm.e_comm_lines + r_js.e_comm_lines + r_vbs.e_comm_lines + r_php.e_comm_lines) << ",";
					(*pout_csv) << r_htm.data_lines[LOG] << ",";
					(*pout_csv) << r_htm.exec_lines[LOG] << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << r_js.data_lines[LOG] << ",";
					(*pout_csv) << r_js.exec_lines[LOG] << ",";
					(*pout_csv) << r_vbs.data_lines[LOG] << ",";
					(*pout_csv) << r_vbs.exec_lines[LOG] << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";					
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << r_php.directive_lines[LOG] << ",";
					(*pout_csv) << r_php.data_lines[LOG] << ",";
					(*pout_csv) << r_php.exec_lines[LOG] << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << r_htm.SLOC_lines[LOG] << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << r_js.SLOC_lines[LOG] << ",";
					(*pout_csv) << r_vbs.SLOC_lines[LOG] << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << r_php.SLOC_lines[LOG] << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << (r_htm.SLOC_lines[LOG] + r_js.SLOC_lines[LOG] + r_vbs.SLOC_lines[LOG] + r_php.SLOC_lines[LOG]) << ",";
					(*pout_csv) << (r_htm.SLOC_lines[PHY] + r_js.SLOC_lines[PHY] + r_vbs.SLOC_lines[PHY] + r_php.SLOC_lines[PHY]) << ",";
					(*pout_csv) << "CODE," << its->second.file_name << endl;
				}

				webtotal[webType].num_of_file++;

				webtotal[webType].total_line += (r_htm.total_lines + r_js.total_lines + r_vbs.total_lines + r_php.total_lines);
				webtotal[webType].blank_line += (r_htm.blank_lines + r_js.blank_lines + r_vbs.blank_lines + r_php.blank_lines);
				webtotal[webType].whole_comment += (r_htm.comment_lines + r_js.comment_lines + r_vbs.comment_lines + r_php.comment_lines);
				webtotal[webType].embed_comment += (r_htm.e_comm_lines + r_js.e_comm_lines + r_vbs.e_comm_lines + r_php.e_comm_lines);

				//0:htm 1:js 2:vbs 3:php
				webtotal[webType].phy_decl[0] += r_htm.data_lines[PHY];
				webtotal[webType].phy_instr[0] += r_htm.exec_lines[PHY];
				webtotal[webType].log_decl[0] += r_htm.data_lines[LOG];
				webtotal[webType].log_instr[0] += r_htm.exec_lines[LOG];

				webtotal[webType].phy_decl[1] += r_js.data_lines[PHY];
				webtotal[webType].phy_instr[1] += r_js.exec_lines[PHY];
				webtotal[webType].log_decl[1] += r_js.data_lines[LOG];
				webtotal[webType].log_instr[1] += r_js.exec_lines[LOG];

				webtotal[webType].phy_decl[2] += r_vbs.data_lines[PHY];
				webtotal[webType].phy_instr[2] += r_vbs.exec_lines[PHY];
				webtotal[webType].log_decl[2] += r_vbs.data_lines[LOG];
				webtotal[webType].log_instr[2] += r_vbs.exec_lines[LOG];

				webtotal[webType].phy_direct[3] += r_php.directive_lines[PHY];
				webtotal[webType].phy_decl[3] += r_php.data_lines[PHY];
				webtotal[webType].phy_instr[3] += r_php.exec_lines[PHY];
				webtotal[webType].log_direct[3] += r_php.directive_lines[LOG];
				webtotal[webType].log_decl[3] += r_php.data_lines[LOG];
				webtotal[webType].log_instr[3] += r_php.exec_lines[LOG];

				allWebLang.num_of_file++;

				allWebLang.total_line += (r_htm.total_lines + r_js.total_lines + r_vbs.total_lines + r_php.total_lines);
				allWebLang.blank_line += (r_htm.blank_lines + r_js.blank_lines + r_vbs.blank_lines + r_php.blank_lines);
				allWebLang.whole_comment += (r_htm.comment_lines + r_js.comment_lines + r_vbs.comment_lines + r_php.comment_lines);
				allWebLang.embed_comment += (r_htm.e_comm_lines + r_js.e_comm_lines + r_vbs.e_comm_lines + r_php.e_comm_lines);

				allWebLang.phy_decl[0] += r_htm.data_lines[PHY];
				allWebLang.phy_instr[0] += r_htm.exec_lines[PHY];
				allWebLang.log_decl[0] += r_htm.data_lines[LOG];
				allWebLang.log_instr[0] += r_htm.exec_lines[LOG];

				allWebLang.phy_decl[2] += r_js.data_lines[PHY];
				allWebLang.phy_instr[2] += r_js.exec_lines[PHY];
				allWebLang.log_decl[2] += r_js.data_lines[LOG];
				allWebLang.log_instr[2] += r_js.exec_lines[LOG];

				allWebLang.phy_decl[3] += r_vbs.data_lines[PHY];
				allWebLang.phy_instr[3] += r_vbs.exec_lines[PHY];
				allWebLang.log_decl[3] += r_vbs.data_lines[LOG];
				allWebLang.log_instr[3] += r_vbs.exec_lines[LOG];

				allWebLang.phy_direct[8] += r_php.directive_lines[PHY];
				allWebLang.phy_decl[8] += r_php.data_lines[PHY];
				allWebLang.phy_instr[8] += r_php.exec_lines[PHY];
				allWebLang.log_direct[8] += r_php.directive_lines[LOG];
				allWebLang.log_decl[8] += r_php.data_lines[LOG];
				allWebLang.log_instr[8] += r_php.exec_lines[LOG];
			}
			else if (webType == WEB_JSP)
			{
				results r_htm;
				results r_js;
				results r_vbs;
				results r_java;
				for (SourceFileList::iterator i = startpos; i!= endpos; i++)
				{
					switch (i->second.class_type)
					{
					case HTML_JSP:
						r_htm = i->second;
						break;
					case JAVASCRIPT_JSP:
						r_js = i->second;
						break;
					case VBS_JSP:
						r_vbs = i->second;
						break;
					case JAVA_JSP:
						r_java = i->second;
						break;
					}
				}
				r_htm.SLOC_lines[PHY] = r_htm.exec_lines[PHY] + r_htm.data_lines[PHY];
				r_htm.SLOC_lines[LOG] = r_htm.exec_lines[LOG] + r_htm.data_lines[LOG];
				r_htm.total_lines = r_htm.SLOC_lines[PHY] +	r_htm.blank_lines + r_htm.comment_lines;

				r_js.SLOC_lines[PHY] = r_js.exec_lines[PHY] + r_js.data_lines[PHY];
				r_js.SLOC_lines[LOG] = r_js.exec_lines[LOG] + r_js.data_lines[LOG];
				r_js.total_lines = r_js.SLOC_lines[PHY] +	r_js.blank_lines + r_js.comment_lines;

				r_vbs.SLOC_lines[PHY] = r_vbs.exec_lines[PHY] + r_vbs.data_lines[PHY];
				r_vbs.SLOC_lines[LOG] = r_vbs.exec_lines[LOG] + r_vbs.data_lines[LOG];
				r_vbs.total_lines = r_vbs.SLOC_lines[PHY] +	r_vbs.blank_lines + r_vbs.comment_lines;

				r_java.SLOC_lines[PHY] = r_java.directive_lines[PHY] + r_java.exec_lines[PHY] + r_java.data_lines[PHY];
				r_java.SLOC_lines[LOG] = r_java.directive_lines[LOG] + r_java.exec_lines[LOG] + r_java.data_lines[LOG];
				r_java.total_lines = r_java.SLOC_lines[PHY] +	r_java.blank_lines + r_java.comment_lines;

				if (print_ascii || print_legacy)
				{
					(*pout).setf(ios::right);
					(*pout).width(8);		(*pout) << (r_htm.total_lines + r_js.total_lines + r_vbs.total_lines + r_java.total_lines);
					(*pout) << " ";
					(*pout).width(7);		(*pout) << (r_htm.blank_lines + r_js.blank_lines + r_vbs.blank_lines + r_java.blank_lines);
					(*pout) << " |";
					(*pout).width(8);		(*pout) << (r_htm.comment_lines + r_js.comment_lines + r_vbs.comment_lines + r_java.comment_lines);
					(*pout) << " ";
					(*pout).width(8);		(*pout) << (r_htm.e_comm_lines + r_js.e_comm_lines + r_vbs.e_comm_lines + r_java.e_comm_lines);
					(*pout) << " |";
					(*pout).width(8);		(*pout) << r_htm.data_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_htm.exec_lines[LOG];
					(*pout) << " |";
					(*pout).width(8);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " |";
					(*pout).width(8);		(*pout) << r_js.data_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_js.exec_lines[LOG];
					(*pout) << " |";
					(*pout).width(8);		(*pout) << r_vbs.data_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_vbs.exec_lines[LOG];
					(*pout) << " |";
					(*pout).width(8);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " |";
					(*pout).width(8);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " |";
					(*pout).width(8);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " |";
					(*pout).width(8);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " |";
					(*pout).width(8);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " |";
					(*pout).width(8);		(*pout) << r_java.directive_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_java.data_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_java.exec_lines[LOG];
					(*pout) << " |";
					(*pout).width(8);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " |";
					(*pout).width(8);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " |";
					(*pout).width(8);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					if (print_legacy)
					{
						(*pout) << " |";
						(*pout).width(8);	(*pout) << (r_htm.SLOC_lines[LOG] + r_js.SLOC_lines[LOG] + r_vbs.SLOC_lines[LOG] + r_java.SLOC_lines[LOG]);
					}
					(*pout) << " |";
					(*pout).width(8);		(*pout) << r_htm.SLOC_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_js.SLOC_lines[LOG];
					(*pout) << " ";
					(*pout).width(8);		(*pout) << r_vbs.SLOC_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_java.SLOC_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(10);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(8);		(*pout) << "0";
					if (!print_legacy)
					{
						(*pout) << " |";
						(*pout).width(8);	(*pout) << (r_htm.SLOC_lines[LOG] + r_js.SLOC_lines[LOG] + r_vbs.SLOC_lines[LOG] + r_java.SLOC_lines[LOG]);
						(*pout) << " |";
						(*pout).width(9);	(*pout) << (r_htm.SLOC_lines[PHY] + r_js.SLOC_lines[PHY] + r_vbs.SLOC_lines[PHY] + r_java.SLOC_lines[PHY]);
					}
					(*pout) << " | CODE  ";
					(*pout) << its->second.file_name << endl;
					(*pout).unsetf(ios::right);				
				}
				if (print_csv)
				{
					(*pout_csv) << (r_htm.total_lines + r_js.total_lines + r_vbs.total_lines + r_java.total_lines) << ",";
					(*pout_csv) << (r_htm.blank_lines + r_js.blank_lines + r_vbs.blank_lines + r_java.blank_lines) << ",";
					(*pout_csv) << (r_htm.comment_lines + r_js.comment_lines + r_vbs.comment_lines + r_java.comment_lines) << ",";
					(*pout_csv) << (r_htm.e_comm_lines + r_js.e_comm_lines + r_vbs.e_comm_lines + r_java.e_comm_lines) << ",";
					(*pout_csv) << r_htm.data_lines[LOG] << ",";
					(*pout_csv) << r_htm.exec_lines[LOG] << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << r_js.data_lines[LOG] << ",";
					(*pout_csv) << r_js.exec_lines[LOG] << ",";
					(*pout_csv) << r_vbs.data_lines[LOG] << ",";
					(*pout_csv) << r_vbs.exec_lines[LOG] << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << r_java.directive_lines[LOG] << ",";
					(*pout_csv) << r_java.data_lines[LOG] << ",";
					(*pout_csv) << r_java.exec_lines[LOG] << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << r_htm.SLOC_lines[LOG] << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << r_js.SLOC_lines[LOG] << ",";
					(*pout_csv) << r_vbs.SLOC_lines[LOG] << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << r_java.SLOC_lines[LOG] << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << (r_htm.SLOC_lines[LOG] + r_js.SLOC_lines[LOG] + r_vbs.SLOC_lines[LOG] + r_java.SLOC_lines[LOG]) << ",";
					(*pout_csv) << (r_htm.SLOC_lines[PHY] + r_js.SLOC_lines[PHY] + r_vbs.SLOC_lines[PHY] + r_java.SLOC_lines[PHY]) << ",";
					(*pout_csv) << "CODE," << its->second.file_name << endl;
				}

				webtotal[webType].num_of_file++;

				webtotal[webType].total_line += (r_htm.total_lines + r_js.total_lines + r_vbs.total_lines + r_java.total_lines);
				webtotal[webType].blank_line += (r_htm.blank_lines + r_js.blank_lines + r_vbs.blank_lines + r_java.blank_lines);
				webtotal[webType].whole_comment += (r_htm.comment_lines + r_js.comment_lines + r_vbs.comment_lines + r_java.comment_lines);
				webtotal[webType].embed_comment += (r_htm.e_comm_lines + r_js.e_comm_lines + r_vbs.e_comm_lines + r_java.e_comm_lines);

				//0:htm 1:js 2:vbs 3:java
				webtotal[webType].phy_decl[0] += r_htm.data_lines[PHY];
				webtotal[webType].phy_instr[0] += r_htm.exec_lines[PHY];
				webtotal[webType].log_decl[0] += r_htm.data_lines[LOG];
				webtotal[webType].log_instr[0] += r_htm.exec_lines[LOG];

				webtotal[webType].phy_decl[1] += r_js.data_lines[PHY];
				webtotal[webType].phy_instr[1] += r_js.exec_lines[PHY];
				webtotal[webType].log_decl[1] += r_js.data_lines[LOG];
				webtotal[webType].log_instr[1] += r_js.exec_lines[LOG];

				webtotal[webType].phy_decl[2] += r_vbs.data_lines[PHY];
				webtotal[webType].phy_instr[2] += r_vbs.exec_lines[PHY];
				webtotal[webType].log_decl[2] += r_vbs.data_lines[LOG];
				webtotal[webType].log_instr[2] += r_vbs.exec_lines[LOG];

				webtotal[webType].phy_direct[3] += r_java.directive_lines[PHY];
				webtotal[webType].phy_decl[3] += r_java.data_lines[PHY];
				webtotal[webType].phy_instr[3] += r_java.exec_lines[PHY];
				webtotal[webType].log_direct[3] += r_java.directive_lines[LOG];
				webtotal[webType].log_decl[3] += r_java.data_lines[LOG];
				webtotal[webType].log_instr[3] += r_java.exec_lines[LOG];

				allWebLang.num_of_file++;

				allWebLang.total_line += (r_htm.total_lines + r_js.total_lines + r_vbs.total_lines + r_java.total_lines);
				allWebLang.blank_line += (r_htm.blank_lines + r_js.blank_lines + r_vbs.blank_lines + r_java.blank_lines);
				allWebLang.whole_comment += (r_htm.comment_lines + r_js.comment_lines + r_vbs.comment_lines + r_java.comment_lines);
				allWebLang.embed_comment += (r_htm.e_comm_lines + r_js.e_comm_lines + r_vbs.e_comm_lines + r_java.e_comm_lines);

				allWebLang.phy_decl[0] += r_htm.data_lines[PHY];
				allWebLang.phy_instr[0] += r_htm.exec_lines[PHY];
				allWebLang.log_decl[0] += r_htm.data_lines[LOG];
				allWebLang.log_instr[0] += r_htm.exec_lines[LOG];

				allWebLang.phy_decl[2] += r_js.data_lines[PHY];
				allWebLang.phy_instr[2] += r_js.exec_lines[PHY];
				allWebLang.log_decl[2] += r_js.data_lines[LOG];
				allWebLang.log_instr[2] += r_js.exec_lines[LOG];

				allWebLang.phy_decl[3] += r_vbs.data_lines[PHY];
				allWebLang.phy_instr[3] += r_vbs.exec_lines[PHY];
				allWebLang.log_decl[3] += r_vbs.data_lines[LOG];
				allWebLang.log_instr[3] += r_vbs.exec_lines[LOG];

				allWebLang.phy_direct[9] += r_java.directive_lines[PHY];
				allWebLang.phy_decl[9] += r_java.data_lines[PHY];
				allWebLang.phy_instr[9] += r_java.exec_lines[PHY];
				allWebLang.log_direct[9] += r_java.directive_lines[LOG];
				allWebLang.log_decl[9] += r_java.data_lines[LOG];
				allWebLang.log_instr[9] += r_java.exec_lines[LOG];
			}
			else if (webType == WEB_ASP)
			{
				results r_htm;
				results r_jsc;
				results r_vbsc;
				results r_jss;
				results r_vbss;
				results r_css;
				for (SourceFileList::iterator i = startpos; i!= endpos; i++)
				{
					switch (i->second.class_type)
					{
					case HTML_ASP:
						r_htm = i->second;
						break;
					case JAVASCRIPT_ASP_C:
						r_jsc = i->second;
						break;
					case VBS_ASP_C:
						r_vbsc = i->second;
						break;
					case JAVASCRIPT_ASP_S:
						r_jss = i->second;
						break;
					case VBS_ASP_S:
						r_vbss = i->second;
						break;
					case CSHARP_ASP_S:
						r_css = i->second;
						break;
					}
				}
				r_htm.SLOC_lines[PHY] = r_htm.exec_lines[PHY] + r_htm.data_lines[PHY];
				r_htm.SLOC_lines[LOG] = r_htm.exec_lines[LOG] + r_htm.data_lines[LOG];
				r_htm.total_lines = r_htm.SLOC_lines[PHY] +	r_htm.blank_lines + r_htm.comment_lines;

				r_jsc.SLOC_lines[PHY] = r_jsc.exec_lines[PHY] + r_jsc.data_lines[PHY];
				r_jsc.SLOC_lines[LOG] = r_jsc.exec_lines[LOG] + r_jsc.data_lines[LOG];
				r_jsc.total_lines = r_jsc.SLOC_lines[PHY] +	r_jsc.blank_lines + r_jsc.comment_lines;

				r_vbsc.SLOC_lines[PHY] = r_vbsc.exec_lines[PHY] + r_vbsc.data_lines[PHY];
				r_vbsc.SLOC_lines[LOG] = r_vbsc.exec_lines[LOG] + r_vbsc.data_lines[LOG];
				r_vbsc.total_lines = r_vbsc.SLOC_lines[PHY] +	r_vbsc.blank_lines + r_vbsc.comment_lines;

				r_jss.SLOC_lines[PHY] = r_jss.directive_lines[PHY] + r_jss.exec_lines[PHY] + r_jss.data_lines[PHY];
				r_jss.SLOC_lines[LOG] = r_jss.directive_lines[LOG] + r_jss.exec_lines[LOG] + r_jss.data_lines[LOG];
				r_jss.total_lines = r_jss.SLOC_lines[PHY] +	r_jss.blank_lines + r_jss.comment_lines;

				r_vbss.SLOC_lines[PHY] = r_vbss.exec_lines[PHY] + r_vbss.data_lines[PHY];
				r_vbss.SLOC_lines[LOG] = r_vbss.exec_lines[LOG] + r_vbss.data_lines[LOG];
				r_vbss.total_lines = r_vbss.SLOC_lines[PHY] +	r_vbss.blank_lines + r_vbss.comment_lines;

				r_css.SLOC_lines[PHY] = r_css.exec_lines[PHY] + r_css.data_lines[PHY];
				r_css.SLOC_lines[LOG] = r_css.exec_lines[LOG] + r_css.data_lines[LOG];
				r_css.total_lines = r_css.SLOC_lines[PHY] +	r_css.blank_lines + r_css.comment_lines;

				if (print_ascii || print_legacy)
				{										
					(*pout).setf(ios::right);
					(*pout).width(8);		(*pout) << (r_htm.total_lines + r_jsc.total_lines + r_vbsc.total_lines + r_jss.total_lines + r_vbss.total_lines + r_css.total_lines);
					(*pout) << " ";
					(*pout).width(7);		(*pout) << (r_htm.blank_lines + r_jsc.blank_lines + r_vbsc.blank_lines + r_jss.blank_lines + r_vbss.blank_lines + r_css.blank_lines);
					(*pout) << " |";
					(*pout).width(8);		(*pout) << (r_htm.comment_lines + r_jsc.comment_lines + r_vbsc.comment_lines + r_jss.comment_lines + r_vbss.comment_lines + r_css.comment_lines);
					(*pout) << " ";
					(*pout).width(8);		(*pout) << (r_htm.e_comm_lines + r_jsc.e_comm_lines + r_vbsc.e_comm_lines + r_jss.e_comm_lines + r_vbss.e_comm_lines + r_css.e_comm_lines);
					(*pout) << " |";
					(*pout).width(8);		(*pout) << r_htm.data_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_htm.exec_lines[LOG];
					(*pout) << " |";
					(*pout).width(8);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " |";
					(*pout).width(8);		(*pout) << r_jsc.data_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_jsc.exec_lines[LOG];
					(*pout) << " |";
					(*pout).width(8);		(*pout) << r_vbsc.data_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_vbsc.exec_lines[LOG];
					(*pout) << " |";
					(*pout).width(8);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " |";					
					(*pout).width(8);		(*pout) << r_jss.data_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_jss.exec_lines[LOG];
					(*pout) << " |";
					(*pout).width(8);		(*pout) << r_vbss.data_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_vbss.exec_lines[LOG];
					(*pout) << " |";
					(*pout).width(8);		(*pout) << r_css.data_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_css.exec_lines[LOG];
					(*pout) << " |";
					(*pout).width(8);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " |";
					(*pout).width(8);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " |";
					(*pout).width(8);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " |";
					(*pout).width(8);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " |";
					(*pout).width(8);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					if (print_legacy)
					{
						(*pout) << " |";
						(*pout).width(8);	(*pout) << (r_htm.SLOC_lines[LOG] + r_jsc.SLOC_lines[LOG] + r_vbsc.SLOC_lines[LOG] + r_jss.SLOC_lines[LOG] + r_vbss.SLOC_lines[LOG] + r_css.SLOC_lines[LOG]);
					}
					(*pout) << " |";
					(*pout).width(8);		(*pout) << r_htm.SLOC_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_jsc.SLOC_lines[LOG];
					(*pout) << " ";
					(*pout).width(8);		(*pout) << r_vbsc.SLOC_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_jss.SLOC_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_vbss.SLOC_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_css.SLOC_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(10);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(8);		(*pout) << "0";
					if (!print_legacy)
					{
						(*pout) << " |";
						(*pout).width(8);	(*pout) << (r_htm.SLOC_lines[LOG] + r_jsc.SLOC_lines[LOG] + r_vbsc.SLOC_lines[LOG] + r_jss.SLOC_lines[LOG] + r_vbss.SLOC_lines[LOG] + r_css.SLOC_lines[LOG]);
						(*pout) << " |";
						(*pout).width(9);	(*pout) << (r_htm.SLOC_lines[PHY] + r_jsc.SLOC_lines[PHY] + r_vbsc.SLOC_lines[PHY] + r_jss.SLOC_lines[PHY] + r_vbss.SLOC_lines[PHY] + r_css.SLOC_lines[PHY]);
					}
					(*pout) << " | CODE  ";
					(*pout) << its->second.file_name << endl;
					(*pout).unsetf(ios::right);
				}
				if (print_csv)
				{
					(*pout_csv) << (r_htm.total_lines + r_jsc.total_lines + r_vbsc.total_lines + r_jss.total_lines + r_vbss.total_lines + r_css.total_lines) << ",";
					(*pout_csv) << (r_htm.blank_lines + r_jsc.blank_lines + r_vbsc.blank_lines + r_jss.blank_lines + r_vbss.blank_lines + r_css.blank_lines) << ",";
					(*pout_csv) << (r_htm.comment_lines + r_jsc.comment_lines + r_vbsc.comment_lines + r_jss.comment_lines + r_vbss.comment_lines + r_css.comment_lines) << ",";
					(*pout_csv) << (r_htm.e_comm_lines + r_jsc.e_comm_lines + r_vbsc.e_comm_lines + r_jss.e_comm_lines + r_vbss.e_comm_lines + r_css.e_comm_lines) << ",";
					(*pout_csv) << r_htm.data_lines[LOG] << ",";
					(*pout_csv) << r_htm.exec_lines[LOG] << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << r_jsc.data_lines[LOG] << ",";
					(*pout_csv) << r_jsc.exec_lines[LOG] << ",";
					(*pout_csv) << r_vbsc.data_lines[LOG] << ",";
					(*pout_csv) << r_vbsc.exec_lines[LOG] << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";					
					(*pout_csv) << r_jss.data_lines[LOG] << ",";
					(*pout_csv) << r_jss.exec_lines[LOG] << ",";
					(*pout_csv) << r_vbss.data_lines[LOG] << ",";
					(*pout_csv) << r_vbss.exec_lines[LOG] << ",";
					(*pout_csv) << r_css.data_lines[LOG] << ",";
					(*pout_csv) << r_css.exec_lines[LOG] << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";					
					(*pout_csv) << r_htm.SLOC_lines[LOG] << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << r_jsc.SLOC_lines[LOG] << ",";
					(*pout_csv) << r_vbsc.SLOC_lines[LOG] << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << r_jss.SLOC_lines[LOG] << ",";
					(*pout_csv) << r_vbss.SLOC_lines[LOG] << ",";
					(*pout_csv) << r_css.SLOC_lines[LOG] << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << (r_htm.SLOC_lines[LOG] + r_jsc.SLOC_lines[LOG] + r_vbsc.SLOC_lines[LOG] + r_jss.SLOC_lines[LOG] + r_vbss.SLOC_lines[LOG] + r_css.SLOC_lines[LOG]) << ",";
					(*pout_csv) << (r_htm.SLOC_lines[PHY] + r_jsc.SLOC_lines[PHY] + r_vbsc.SLOC_lines[PHY] + r_jss.SLOC_lines[PHY] + r_vbss.SLOC_lines[PHY] + r_css.SLOC_lines[PHY]) << ",";
					(*pout_csv) << "CODE," << its->second.file_name << endl;
				}

				webtotal[webType].num_of_file++;

				webtotal[webType].total_line += (r_htm.total_lines + r_jsc.total_lines + r_vbsc.total_lines + r_jss.total_lines + r_vbss.total_lines + r_css.total_lines);
				webtotal[webType].blank_line += (r_htm.blank_lines + r_jsc.blank_lines + r_vbsc.blank_lines + r_jss.blank_lines + r_vbss.blank_lines + r_css.blank_lines);
				webtotal[webType].whole_comment += (r_htm.comment_lines + r_jsc.comment_lines + r_vbsc.comment_lines + r_jss.comment_lines + r_vbss.comment_lines + r_css.comment_lines);
				webtotal[webType].embed_comment += (r_htm.e_comm_lines + r_jsc.e_comm_lines + r_vbsc.e_comm_lines + r_jss.e_comm_lines + r_vbss.e_comm_lines + r_css.e_comm_lines);

				//0:htm 1:jsc 2:vbsc 3:jss 4:vbss 5:csharps
				webtotal[webType].phy_decl[0] += r_htm.data_lines[PHY];
				webtotal[webType].phy_instr[0] += r_htm.exec_lines[PHY];
				webtotal[webType].log_decl[0] += r_htm.data_lines[LOG];
				webtotal[webType].log_instr[0] += r_htm.exec_lines[LOG];

				webtotal[webType].phy_decl[1] += r_jsc.data_lines[PHY];
				webtotal[webType].phy_instr[1] += r_jsc.exec_lines[PHY];
				webtotal[webType].log_decl[1] += r_jsc.data_lines[LOG];
				webtotal[webType].log_instr[1] += r_jsc.exec_lines[LOG];

				webtotal[webType].phy_decl[2] += r_vbsc.data_lines[PHY];
				webtotal[webType].phy_instr[2] += r_vbsc.exec_lines[PHY];
				webtotal[webType].log_decl[2] += r_vbsc.data_lines[LOG];
				webtotal[webType].log_instr[2] += r_vbsc.exec_lines[LOG];

				webtotal[webType].phy_decl[3] += r_jss.data_lines[PHY];
				webtotal[webType].phy_instr[3] += r_jss.exec_lines[PHY];
				webtotal[webType].log_decl[3] += r_jss.data_lines[LOG];
				webtotal[webType].log_instr[3] += r_jss.exec_lines[LOG];

				webtotal[webType].phy_decl[4] += r_vbss.data_lines[PHY];
				webtotal[webType].phy_instr[4] += r_vbss.exec_lines[PHY];
				webtotal[webType].log_decl[4] += r_vbss.data_lines[LOG];
				webtotal[webType].log_instr[4] += r_vbss.exec_lines[LOG];

				webtotal[webType].phy_decl[5] += r_css.data_lines[PHY];
				webtotal[webType].phy_instr[5] += r_css.exec_lines[PHY];
				webtotal[webType].log_decl[5] += r_css.data_lines[LOG];
				webtotal[webType].log_instr[5] += r_css.exec_lines[LOG];

				allWebLang.num_of_file++;

				allWebLang.total_line += (r_htm.total_lines + r_jsc.total_lines + r_vbsc.total_lines + r_jss.total_lines + r_vbss.total_lines + r_css.total_lines);
				allWebLang.blank_line += (r_htm.blank_lines + r_jsc.blank_lines + r_vbsc.blank_lines + r_jss.blank_lines + r_vbss.blank_lines + r_css.blank_lines);
				allWebLang.whole_comment += (r_htm.comment_lines + r_jsc.comment_lines + r_vbsc.comment_lines + r_jss.comment_lines + r_vbss.comment_lines + r_css.comment_lines);
				allWebLang.embed_comment += (r_htm.e_comm_lines + r_jsc.e_comm_lines + r_vbsc.e_comm_lines + r_jss.e_comm_lines + r_vbss.e_comm_lines + r_css.e_comm_lines);

				allWebLang.phy_decl[0] += r_htm.data_lines[PHY];
				allWebLang.phy_instr[0] += r_htm.exec_lines[PHY];
				allWebLang.log_decl[0] += r_htm.data_lines[LOG];
				allWebLang.log_instr[0] += r_htm.exec_lines[LOG];

				allWebLang.phy_decl[2] += r_jsc.data_lines[PHY];
				allWebLang.phy_instr[2] += r_jsc.exec_lines[PHY];
				allWebLang.log_decl[2] += r_jsc.data_lines[LOG];
				allWebLang.log_instr[2] += r_jsc.exec_lines[LOG];

				allWebLang.phy_decl[3] += r_vbsc.data_lines[PHY];
				allWebLang.phy_instr[3] += r_vbsc.exec_lines[PHY];
				allWebLang.log_decl[3] += r_vbsc.data_lines[LOG];
				allWebLang.log_instr[3] += r_vbsc.exec_lines[LOG];

				allWebLang.phy_decl[5] += r_jss.data_lines[PHY];
				allWebLang.phy_instr[5] += r_jss.exec_lines[PHY];
				allWebLang.log_decl[5] += r_jss.data_lines[LOG];
				allWebLang.log_instr[5] += r_jss.exec_lines[LOG];

				allWebLang.phy_decl[6] += r_vbss.data_lines[PHY];
				allWebLang.phy_instr[6] += r_vbss.exec_lines[PHY];
				allWebLang.log_decl[6] += r_vbss.data_lines[LOG];
				allWebLang.log_instr[6] += r_vbss.exec_lines[LOG];

				allWebLang.phy_decl[7] += r_css.data_lines[PHY];
				allWebLang.phy_instr[7] += r_css.exec_lines[PHY];
				allWebLang.log_decl[7] += r_css.data_lines[LOG];
				allWebLang.log_instr[7] += r_css.exec_lines[LOG];
			}
			else if (webType == WEB_XML)
			{
				results r_xml;
				results r_js;
				results r_vbs;
				results r_cs;
				for (SourceFileList::iterator i = startpos; i!= endpos; i++)
				{
					switch (i->second.class_type)
					{
					case XML:
						r_xml = i->second;
						break;
					case JAVASCRIPT_XML:
						r_js = i->second;
						break;
					case VBS_XML:
						r_vbs = i->second;
						break;
					case CSHARP_XML:
						r_cs = i->second;
						break;
					}
				}
				r_xml.SLOC_lines[PHY] = r_xml.exec_lines[PHY] + r_xml.data_lines[PHY];
				r_xml.SLOC_lines[LOG] = r_xml.exec_lines[LOG] + r_xml.data_lines[LOG];
				r_xml.total_lines = r_xml.SLOC_lines[PHY] +	r_xml.blank_lines + r_xml.comment_lines;

				r_js.SLOC_lines[PHY] = r_js.exec_lines[PHY] + r_js.data_lines[PHY];
				r_js.SLOC_lines[LOG] = r_js.exec_lines[LOG] + r_js.data_lines[LOG];
				r_js.total_lines = r_js.SLOC_lines[PHY] +	r_js.blank_lines + r_js.comment_lines;

				r_vbs.SLOC_lines[PHY] = r_vbs.exec_lines[PHY] + r_vbs.data_lines[PHY];
				r_vbs.SLOC_lines[LOG] = r_vbs.exec_lines[LOG] + r_vbs.data_lines[LOG];
				r_vbs.total_lines = r_vbs.SLOC_lines[PHY] +	r_vbs.blank_lines + r_vbs.comment_lines;

				r_cs.SLOC_lines[PHY] = r_cs.exec_lines[PHY] + r_cs.data_lines[PHY];
				r_cs.SLOC_lines[LOG] = r_cs.exec_lines[LOG] + r_cs.data_lines[LOG];
				r_cs.total_lines = r_cs.SLOC_lines[PHY] +	r_cs.blank_lines + r_cs.comment_lines;

				if (print_ascii || print_legacy)
				{		
					(*pout).setf(ios::right);
					(*pout).width(8);		(*pout) << (r_xml.total_lines + r_js.total_lines + r_vbs.total_lines + r_cs.total_lines);
					(*pout) << " ";
					(*pout).width(7);		(*pout) << (r_xml.blank_lines + r_js.blank_lines + r_vbs.blank_lines + r_cs.blank_lines);
					(*pout) << " |";
					(*pout).width(8);		(*pout) << (r_xml.comment_lines + r_js.comment_lines + r_vbs.comment_lines + r_cs.comment_lines);
					(*pout) << " ";
					(*pout).width(8);		(*pout) << (r_xml.e_comm_lines + r_js.e_comm_lines + r_vbs.e_comm_lines + r_cs.e_comm_lines);
					(*pout) << " |";
					(*pout).width(8);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " |";
					(*pout).width(8);		(*pout) << r_xml.data_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_xml.exec_lines[LOG];
					(*pout) << " |";
					(*pout).width(8);		(*pout) << r_js.data_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_js.exec_lines[LOG];
					(*pout) << " |";
					(*pout).width(8);		(*pout) << r_vbs.data_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_vbs.exec_lines[LOG];
					(*pout) << " |";
					(*pout).width(8);		(*pout) << r_cs.data_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_cs.exec_lines[LOG];
					(*pout) << " |";
					(*pout).width(8);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " |";
					(*pout).width(8);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " |";
					(*pout).width(8);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " |";
					(*pout).width(8);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " |";
					(*pout).width(8);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " |";
					(*pout).width(8);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " |";
					(*pout).width(8);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " |";
					(*pout).width(8);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					if (print_legacy)
					{
						(*pout) << " |";
						(*pout).width(8);	(*pout) << (r_xml.SLOC_lines[LOG] + r_js.SLOC_lines[LOG] + r_vbs.SLOC_lines[LOG] + r_cs.SLOC_lines[LOG]);
					}
					(*pout) << " |";
					(*pout).width(8);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_xml.SLOC_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_js.SLOC_lines[LOG];
					(*pout) << " ";
					(*pout).width(8);		(*pout) << r_vbs.SLOC_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_cs.SLOC_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(10);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(8);		(*pout) << "0";
					if (!print_legacy)
					{
						(*pout) << " |";
						(*pout).width(8);	(*pout) << (r_xml.SLOC_lines[LOG] + r_js.SLOC_lines[LOG] + r_vbs.SLOC_lines[LOG] + r_cs.SLOC_lines[LOG]);
						(*pout) << " |";
						(*pout).width(9);	(*pout) << (r_xml.SLOC_lines[PHY] + r_js.SLOC_lines[PHY] + r_vbs.SLOC_lines[PHY] + r_cs.SLOC_lines[PHY]);
					}
					(*pout) << " | CODE  ";
					(*pout) << its->second.file_name << endl;
					(*pout).unsetf(ios::right);
				}
				if (print_csv)
				{
					(*pout_csv) << (r_xml.total_lines + r_js.total_lines + r_vbs.total_lines + r_cs.total_lines) << ",";
					(*pout_csv) << (r_xml.blank_lines + r_js.blank_lines + r_vbs.blank_lines + r_cs.blank_lines) << ",";
					(*pout_csv) << (r_xml.comment_lines + r_js.comment_lines + r_vbs.comment_lines + r_cs.comment_lines) << ",";
					(*pout_csv) << (r_xml.e_comm_lines + r_js.e_comm_lines + r_vbs.e_comm_lines + r_cs.e_comm_lines) << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << r_xml.data_lines[LOG] << ",";
					(*pout_csv) << r_xml.exec_lines[LOG] << ",";
					(*pout_csv) << r_js.data_lines[LOG] << ",";
					(*pout_csv) << r_js.exec_lines[LOG] << ",";
					(*pout_csv) << r_vbs.data_lines[LOG] << ",";
					(*pout_csv) << r_vbs.exec_lines[LOG] << ",";
					(*pout_csv) << r_cs.data_lines[LOG] << ",";
					(*pout_csv) << r_cs.exec_lines[LOG] << ",";					
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";					
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";					
					(*pout_csv) << "0" << ",";
					(*pout_csv) << r_xml.SLOC_lines[LOG] << ",";
					(*pout_csv) << r_js.SLOC_lines[LOG] << ",";
					(*pout_csv) << r_vbs.SLOC_lines[LOG] << ",";
					(*pout_csv) << r_cs.SLOC_lines[LOG] << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";	
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << (r_xml.SLOC_lines[LOG] + r_js.SLOC_lines[LOG] + r_vbs.SLOC_lines[LOG] + r_cs.SLOC_lines[LOG]) << ",";
					(*pout_csv) << (r_xml.SLOC_lines[PHY] + r_js.SLOC_lines[PHY] + r_vbs.SLOC_lines[PHY] + r_cs.SLOC_lines[PHY]) << ",";
					(*pout_csv) << "CODE," << its->second.file_name << endl;
				}

				webtotal[webType].num_of_file++;

				webtotal[webType].total_line += (r_xml.total_lines + r_js.total_lines + r_vbs.total_lines + r_cs.total_lines);
				webtotal[webType].blank_line += (r_xml.blank_lines + r_js.blank_lines + r_vbs.blank_lines + r_cs.blank_lines);
				webtotal[webType].whole_comment += (r_xml.comment_lines + r_js.comment_lines + r_vbs.comment_lines + r_cs.comment_lines);
				webtotal[webType].embed_comment += (r_xml.e_comm_lines + r_js.e_comm_lines + r_vbs.e_comm_lines + r_cs.e_comm_lines);

				//0:xml 1:js 2:vbs 3:csharp
				webtotal[webType].phy_decl[0] += r_xml.data_lines[PHY];
				webtotal[webType].phy_instr[0] += r_xml.exec_lines[PHY];
				webtotal[webType].log_decl[0] += r_xml.data_lines[LOG];
				webtotal[webType].log_instr[0] += r_xml.exec_lines[LOG];

				webtotal[webType].phy_decl[1] += r_js.data_lines[PHY];
				webtotal[webType].phy_instr[1] += r_js.exec_lines[PHY];
				webtotal[webType].log_decl[1] += r_js.data_lines[LOG];
				webtotal[webType].log_instr[1] += r_js.exec_lines[LOG];

				webtotal[webType].phy_decl[2] += r_vbs.data_lines[PHY];
				webtotal[webType].phy_instr[2] += r_vbs.exec_lines[PHY];
				webtotal[webType].log_decl[2] += r_vbs.data_lines[LOG];
				webtotal[webType].log_instr[2] += r_vbs.exec_lines[LOG];

				webtotal[webType].phy_decl[3] += r_cs.data_lines[PHY];
				webtotal[webType].phy_instr[3] += r_cs.exec_lines[PHY];
				webtotal[webType].log_decl[3] += r_cs.data_lines[LOG];
				webtotal[webType].log_instr[3] += r_cs.exec_lines[LOG];

				allWebLang.num_of_file++;

				allWebLang.total_line += (r_xml.total_lines + r_js.total_lines + r_vbs.total_lines + r_cs.total_lines);
				allWebLang.blank_line += (r_xml.blank_lines + r_js.blank_lines + r_vbs.blank_lines + r_cs.blank_lines);
				allWebLang.whole_comment += (r_xml.comment_lines + r_js.comment_lines + r_vbs.comment_lines + r_cs.comment_lines);
				allWebLang.embed_comment += (r_xml.e_comm_lines + r_js.e_comm_lines + r_vbs.e_comm_lines + r_cs.e_comm_lines);

				allWebLang.phy_decl[1] += r_xml.data_lines[PHY];
				allWebLang.phy_instr[1] += r_xml.exec_lines[PHY];
				allWebLang.log_decl[1] += r_xml.data_lines[LOG];
				allWebLang.log_instr[1] += r_xml.exec_lines[LOG];

				allWebLang.phy_decl[2] += r_js.data_lines[PHY];
				allWebLang.phy_instr[2] += r_js.exec_lines[PHY];
				allWebLang.log_decl[2] += r_js.data_lines[LOG];
				allWebLang.log_instr[2] += r_js.exec_lines[LOG];

				allWebLang.phy_decl[3] += r_vbs.data_lines[PHY];
				allWebLang.phy_instr[3] += r_vbs.exec_lines[PHY];
				allWebLang.log_decl[3] += r_vbs.data_lines[LOG];
				allWebLang.log_instr[3] += r_vbs.exec_lines[LOG];

				allWebLang.phy_decl[4] += r_cs.data_lines[PHY];
				allWebLang.phy_instr[4] += r_cs.exec_lines[PHY];
				allWebLang.log_decl[4] += r_cs.data_lines[LOG];
				allWebLang.log_instr[4] += r_cs.exec_lines[LOG];
			}
			else if (webType == WEB_CFM)
			{
				results r_htm;
				results r_js;
				results r_vbs;
				results r_sql;
				results r_cfm;
				results r_cfs;
				for (SourceFileList::iterator i = startpos; i!= endpos; i++)
				{
					switch (i->second.class_type)
					{
					case HTML_CFM:
						r_htm = i->second;
						break;
					case JAVASCRIPT_CFM:
						r_js = i->second;
						break;
					case VBS_CFM:
						r_vbs = i->second;
						break;
					case SQL_CFM:
						r_sql = i->second;
						break;
					case COLDFUSION:
						r_cfm = i->second;
						break;
					case CFSCRIPT:
						r_cfs = i->second;
						break;
					}
				}
				r_htm.SLOC_lines[PHY] = r_htm.exec_lines[PHY] + r_htm.data_lines[PHY];
				r_htm.SLOC_lines[LOG] = r_htm.exec_lines[LOG] + r_htm.data_lines[LOG];
				r_htm.total_lines = r_htm.SLOC_lines[PHY] +	r_htm.blank_lines + r_htm.comment_lines;

				r_js.SLOC_lines[PHY] = r_js.exec_lines[PHY] + r_js.data_lines[PHY];
				r_js.SLOC_lines[LOG] = r_js.exec_lines[LOG] + r_js.data_lines[LOG];
				r_js.total_lines = r_js.SLOC_lines[PHY] +	r_js.blank_lines + r_js.comment_lines;

				r_vbs.SLOC_lines[PHY] = r_vbs.exec_lines[PHY] + r_vbs.data_lines[PHY];
				r_vbs.SLOC_lines[LOG] = r_vbs.exec_lines[LOG] + r_vbs.data_lines[LOG];
				r_vbs.total_lines = r_vbs.SLOC_lines[PHY] +	r_vbs.blank_lines + r_vbs.comment_lines;

				r_sql.SLOC_lines[PHY] = r_sql.exec_lines[PHY] + r_sql.data_lines[PHY];
				r_sql.SLOC_lines[LOG] = r_sql.exec_lines[LOG] + r_sql.data_lines[LOG];
				r_sql.total_lines = r_sql.SLOC_lines[PHY] +	r_sql.blank_lines + r_sql.comment_lines;

				r_cfm.SLOC_lines[PHY] = r_cfm.exec_lines[PHY] + r_cfm.data_lines[PHY];
				r_cfm.SLOC_lines[LOG] = r_cfm.exec_lines[LOG] + r_cfm.data_lines[LOG];
				r_cfm.total_lines = r_cfm.SLOC_lines[PHY] +	r_cfm.blank_lines + r_cfm.comment_lines;

				r_cfs.SLOC_lines[PHY] = r_cfs.exec_lines[PHY] + r_cfs.data_lines[PHY];
				r_cfs.SLOC_lines[LOG] = r_cfs.exec_lines[LOG] + r_cfs.data_lines[LOG];
				r_cfs.total_lines = r_cfs.SLOC_lines[PHY] +	r_cfs.blank_lines + r_cfs.comment_lines;

				if (print_ascii || print_legacy)
				{
					(*pout).setf(ios::right);
					(*pout).width(8);		(*pout) << (r_htm.total_lines + r_js.total_lines + r_vbs.total_lines + r_sql.total_lines + r_cfm.total_lines + r_cfs.total_lines);
					(*pout) << " ";
					(*pout).width(7);		(*pout) << (r_htm.blank_lines + r_js.blank_lines + r_vbs.blank_lines + r_sql.blank_lines + r_cfm.blank_lines + r_cfs.blank_lines);
					(*pout) << " |";
					(*pout).width(8);		(*pout) << (r_htm.comment_lines + r_js.comment_lines + r_vbs.comment_lines + r_sql.comment_lines + r_cfm.comment_lines + r_cfs.comment_lines);
					(*pout) << " ";
					(*pout).width(8);		(*pout) << (r_htm.e_comm_lines + r_js.e_comm_lines + r_vbs.e_comm_lines + r_sql.e_comm_lines + r_cfm.e_comm_lines + r_cfs.e_comm_lines);
					(*pout) << " |";
					(*pout).width(8);		(*pout) << r_htm.data_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_htm.exec_lines[LOG];
					(*pout) << " |";
					(*pout).width(8);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " |";
					(*pout).width(8);		(*pout) << r_js.data_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_js.exec_lines[LOG];
					(*pout) << " |";
					(*pout).width(8);		(*pout) << r_vbs.data_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_vbs.exec_lines[LOG];
					(*pout) << " |";
					(*pout).width(8);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " |";
					(*pout).width(8);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " |";					
					(*pout).width(8);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " |";
					(*pout).width(8);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " |";
					(*pout).width(8);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " |";
					(*pout).width(8);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " |";
					(*pout).width(8);		(*pout) << r_sql.data_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_sql.exec_lines[LOG];
					(*pout) << " |";
					(*pout).width(8);		(*pout) << r_cfm.data_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_cfm.exec_lines[LOG];
					(*pout) << " |";
					(*pout).width(8);		(*pout) << r_cfs.data_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_cfs.exec_lines[LOG];
					if (print_legacy)
					{
						(*pout) << " |";					
						(*pout).width(8);	(*pout) << (r_htm.SLOC_lines[LOG] + r_js.SLOC_lines[LOG] + r_vbs.SLOC_lines[LOG] + r_sql.SLOC_lines[LOG] + r_cfm.SLOC_lines[LOG] + r_cfs.SLOC_lines[LOG]);
					}
					(*pout) << " |";
					(*pout).width(8);		(*pout) << r_htm.SLOC_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_js.SLOC_lines[LOG];
					(*pout) << " ";
					(*pout).width(8);		(*pout) << r_vbs.SLOC_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_sql.SLOC_lines[LOG];
					(*pout) << " ";
					(*pout).width(10);		(*pout) << r_cfm.SLOC_lines[LOG];
					(*pout) << " ";
					(*pout).width(8);		(*pout) << r_cfs.SLOC_lines[LOG];
					if (!print_legacy)
					{
						(*pout) << " |";					
						(*pout).width(8);	(*pout) << (r_htm.SLOC_lines[LOG] + r_js.SLOC_lines[LOG] + r_vbs.SLOC_lines[LOG] + r_sql.SLOC_lines[LOG] + r_cfm.SLOC_lines[LOG] + r_cfs.SLOC_lines[LOG]);
						(*pout) << " |";
						(*pout).width(9);	(*pout) << (r_htm.SLOC_lines[PHY] + r_js.SLOC_lines[PHY] + r_vbs.SLOC_lines[PHY] + r_sql.SLOC_lines[PHY] + r_cfm.SLOC_lines[PHY] + r_cfs.SLOC_lines[PHY]);
					}
					(*pout) << " | CODE  ";
					(*pout) << its->second.file_name << endl;
					(*pout).unsetf(ios::right);
				}
				if (print_csv)
				{
					(*pout_csv) << (r_htm.total_lines + r_js.total_lines + r_vbs.total_lines + r_sql.total_lines + r_cfm.total_lines + r_cfs.total_lines) << ",";
					(*pout_csv) << (r_htm.blank_lines + r_js.blank_lines + r_vbs.blank_lines + r_sql.blank_lines + r_cfm.blank_lines + r_cfs.blank_lines) << ",";
					(*pout_csv) << (r_htm.comment_lines + r_js.comment_lines + r_vbs.comment_lines + r_sql.comment_lines + r_cfm.comment_lines + r_cfs.comment_lines) << ",";
					(*pout_csv) << (r_htm.e_comm_lines + r_js.e_comm_lines + r_vbs.e_comm_lines + r_sql.e_comm_lines + r_cfm.e_comm_lines + r_cfs.e_comm_lines) << ",";
					(*pout_csv) << r_htm.data_lines[LOG] << ",";
					(*pout_csv) << r_htm.exec_lines[LOG] << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << r_js.data_lines[LOG] << ",";
					(*pout_csv) << r_js.exec_lines[LOG] << ",";
					(*pout_csv) << r_vbs.data_lines[LOG] << ",";
					(*pout_csv) << r_vbs.exec_lines[LOG] << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";					
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";					
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << r_sql.data_lines[LOG] << ",";
					(*pout_csv) << r_sql.exec_lines[LOG] << ",";
					(*pout_csv) << r_cfm.data_lines[LOG] << ",";
					(*pout_csv) << r_cfm.exec_lines[LOG] << ",";
					(*pout_csv) << r_cfs.data_lines[LOG] << ",";
					(*pout_csv) << r_cfs.exec_lines[LOG] << ",";					
					(*pout_csv) << r_htm.SLOC_lines[LOG] << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << r_js.SLOC_lines[LOG] << ",";
					(*pout_csv) << r_vbs.SLOC_lines[LOG] << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";					
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << r_sql.SLOC_lines[LOG] << ",";
					(*pout_csv) << r_cfm.SLOC_lines[LOG] << ",";
					(*pout_csv) << r_cfs.SLOC_lines[LOG] << ",";
					(*pout_csv) << (r_htm.SLOC_lines[LOG] + r_js.SLOC_lines[LOG] + r_vbs.SLOC_lines[LOG] + r_sql.SLOC_lines[LOG] + r_cfm.SLOC_lines[LOG] + r_cfs.SLOC_lines[LOG]) << ",";
					(*pout_csv) << (r_htm.SLOC_lines[PHY] + r_js.SLOC_lines[PHY] + r_vbs.SLOC_lines[PHY] + r_sql.SLOC_lines[PHY] + r_cfm.SLOC_lines[PHY] + r_cfs.SLOC_lines[PHY]) << ",";
					(*pout_csv) << "CODE," << its->second.file_name << endl;
				}

				webtotal[webType].num_of_file++;

				webtotal[webType].total_line += (r_htm.total_lines + r_js.total_lines + r_vbs.total_lines + r_sql.total_lines + r_cfm.total_lines + r_cfs.total_lines);
				webtotal[webType].blank_line += (r_htm.blank_lines + r_js.blank_lines + r_vbs.blank_lines + r_sql.blank_lines + r_cfm.blank_lines + r_cfs.blank_lines);
				webtotal[webType].whole_comment += (r_htm.comment_lines + r_js.comment_lines + r_vbs.comment_lines + r_sql.comment_lines + r_cfm.comment_lines + r_cfs.comment_lines);
				webtotal[webType].embed_comment += (r_htm.e_comm_lines + r_js.e_comm_lines + r_vbs.e_comm_lines + r_sql.e_comm_lines + r_cfm.e_comm_lines + r_cfs.e_comm_lines);

				//0:htm 1:js 2:vbs 3:sql 5:cfm 6:cfs
				webtotal[webType].phy_decl[0] += r_htm.data_lines[PHY];
				webtotal[webType].phy_instr[0] += r_htm.exec_lines[PHY];
				webtotal[webType].log_decl[0] += r_htm.data_lines[LOG];
				webtotal[webType].log_instr[0] += r_htm.exec_lines[LOG];

				webtotal[webType].phy_decl[1] += r_js.data_lines[PHY];
				webtotal[webType].phy_instr[1] += r_js.exec_lines[PHY];
				webtotal[webType].log_decl[1] += r_js.data_lines[LOG];
				webtotal[webType].log_instr[1] += r_js.exec_lines[LOG];

				webtotal[webType].phy_decl[2] += r_vbs.data_lines[PHY];
				webtotal[webType].phy_instr[2] += r_vbs.exec_lines[PHY];
				webtotal[webType].log_decl[2] += r_vbs.data_lines[LOG];
				webtotal[webType].log_instr[2] += r_vbs.exec_lines[LOG];

				webtotal[webType].phy_decl[3] += r_sql.data_lines[PHY];
				webtotal[webType].phy_instr[3] += r_sql.exec_lines[PHY];
				webtotal[webType].log_decl[3] += r_sql.data_lines[LOG];
				webtotal[webType].log_instr[3] += r_sql.exec_lines[LOG];

				webtotal[webType].phy_decl[4] += r_cfm.data_lines[PHY];
				webtotal[webType].phy_instr[4] += r_cfm.exec_lines[PHY];
				webtotal[webType].log_decl[4] += r_cfm.data_lines[LOG];
				webtotal[webType].log_instr[4] += r_cfm.exec_lines[LOG];

				webtotal[webType].phy_decl[5] += r_cfs.data_lines[PHY];
				webtotal[webType].phy_instr[5] += r_cfs.exec_lines[PHY];
				webtotal[webType].log_decl[5] += r_cfs.data_lines[LOG];
				webtotal[webType].log_instr[5] += r_cfs.exec_lines[LOG];

				allWebLang.num_of_file++;

				allWebLang.total_line += (r_htm.total_lines + r_js.total_lines + r_vbs.total_lines + r_sql.total_lines + r_cfm.total_lines + r_cfs.total_lines);
				allWebLang.blank_line += (r_htm.blank_lines + r_js.blank_lines + r_vbs.blank_lines + r_sql.blank_lines + r_cfm.blank_lines + r_cfs.blank_lines);
				allWebLang.whole_comment += (r_htm.comment_lines + r_js.comment_lines + r_vbs.comment_lines + r_sql.comment_lines + r_cfm.comment_lines + r_cfs.comment_lines);
				allWebLang.embed_comment += (r_htm.e_comm_lines + r_js.e_comm_lines + r_vbs.e_comm_lines + r_sql.e_comm_lines + r_cfm.e_comm_lines + r_cfs.e_comm_lines);

				allWebLang.phy_decl[0] += r_htm.data_lines[PHY];
				allWebLang.phy_instr[0] += r_htm.exec_lines[PHY];
				allWebLang.log_decl[0] += r_htm.data_lines[LOG];
				allWebLang.log_instr[0] += r_htm.exec_lines[LOG];

				allWebLang.phy_decl[2] += r_js.data_lines[PHY];
				allWebLang.phy_instr[2] += r_js.exec_lines[PHY];
				allWebLang.log_decl[2] += r_js.data_lines[LOG];
				allWebLang.log_instr[2] += r_js.exec_lines[LOG];

				allWebLang.phy_decl[3] += r_vbs.data_lines[PHY];
				allWebLang.phy_instr[3] += r_vbs.exec_lines[PHY];
				allWebLang.log_decl[3] += r_vbs.data_lines[LOG];
				allWebLang.log_instr[3] += r_vbs.exec_lines[LOG];

				allWebLang.phy_decl[10] += r_sql.data_lines[PHY];
				allWebLang.phy_instr[10] += r_sql.exec_lines[PHY];
				allWebLang.log_decl[10] += r_sql.data_lines[LOG];
				allWebLang.log_instr[10] += r_sql.exec_lines[LOG];

				allWebLang.phy_decl[11] += r_cfm.data_lines[PHY];
				allWebLang.phy_instr[11] += r_cfm.exec_lines[PHY];
				allWebLang.log_decl[11] += r_cfm.data_lines[LOG];
				allWebLang.log_instr[11] += r_cfm.exec_lines[LOG];

				allWebLang.phy_decl[12] += r_cfs.data_lines[PHY];
				allWebLang.phy_instr[12] += r_cfs.exec_lines[PHY];
				allWebLang.log_decl[12] += r_cfs.data_lines[LOG];
				allWebLang.log_instr[12] += r_cfs.exec_lines[LOG];
			}
			else
			{
				webType = WEB_HTM;
				results r_htm;
				results r_js;
				results r_vbs;
				results r_cs;
				for (SourceFileList::iterator i = startpos; i!= endpos; i++)
				{
					switch (i->second.class_type)
					{
					case HTML:
						r_htm = i->second;
						break;
					case JAVASCRIPT_HTML:
						r_js = i->second;
						break;
					case VBS_HTML:
						r_vbs = i->second;
						break;
					case CSHARP_HTML:
						r_cs = i->second;
						break;
					}
				}
				r_htm.SLOC_lines[PHY] = r_htm.exec_lines[PHY] + r_htm.data_lines[PHY];
				r_htm.SLOC_lines[LOG] = r_htm.exec_lines[LOG] + r_htm.data_lines[LOG];
				r_htm.total_lines = r_htm.SLOC_lines[PHY] +	r_htm.blank_lines + r_htm.comment_lines;

				r_js.SLOC_lines[PHY] = r_js.exec_lines[PHY] + r_js.data_lines[PHY];
				r_js.SLOC_lines[LOG] = r_js.exec_lines[LOG] + r_js.data_lines[LOG];
				r_js.total_lines = r_js.SLOC_lines[PHY] +	r_js.blank_lines + r_js.comment_lines;

				r_vbs.SLOC_lines[PHY] = r_vbs.exec_lines[PHY] + r_vbs.data_lines[PHY];
				r_vbs.SLOC_lines[LOG] = r_vbs.exec_lines[LOG] + r_vbs.data_lines[LOG];
				r_vbs.total_lines = r_vbs.SLOC_lines[PHY] +	r_vbs.blank_lines + r_vbs.comment_lines;

				r_cs.SLOC_lines[PHY] = r_cs.exec_lines[PHY] + r_cs.data_lines[PHY];
				r_cs.SLOC_lines[LOG] = r_cs.exec_lines[LOG] + r_cs.data_lines[LOG];
				r_cs.total_lines = r_cs.SLOC_lines[PHY] +	r_cs.blank_lines + r_cs.comment_lines;

				if (print_ascii || print_legacy)
				{		
					(*pout).setf(ios::right);
					(*pout).width(8);		(*pout) << (r_htm.total_lines + r_js.total_lines + r_vbs.total_lines + r_cs.total_lines);
					(*pout) << " ";
					(*pout).width(7);		(*pout) << (r_htm.blank_lines + r_js.blank_lines + r_vbs.blank_lines + r_cs.blank_lines);
					(*pout) << " |";
					(*pout).width(8);		(*pout) << (r_htm.comment_lines + r_js.comment_lines + r_vbs.comment_lines + r_cs.comment_lines);
					(*pout) << " ";
					(*pout).width(8);		(*pout) << (r_htm.e_comm_lines + r_js.e_comm_lines + r_vbs.e_comm_lines + r_cs.e_comm_lines);
					(*pout) << " |";
					(*pout).width(8);		(*pout) << r_htm.data_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_htm.exec_lines[LOG];
					(*pout) << " |";
					(*pout).width(8);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " |";
					(*pout).width(8);		(*pout) << r_js.data_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_js.exec_lines[LOG];
					(*pout) << " |";
					(*pout).width(8);		(*pout) << r_vbs.data_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_vbs.exec_lines[LOG];
					(*pout) << " |";
					(*pout).width(8);		(*pout) << r_cs.data_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_cs.exec_lines[LOG];
					(*pout) << " |";
					(*pout).width(8);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " |";
					(*pout).width(8);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " |";
					(*pout).width(8);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " |";
					(*pout).width(8);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " |";
					(*pout).width(8);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " |";
					(*pout).width(8);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " |";
					(*pout).width(8);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " |";
					(*pout).width(8);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					if (print_legacy)
					{
						(*pout) << " |";					
						(*pout).width(8);	(*pout) << (r_htm.SLOC_lines[LOG] + r_js.SLOC_lines[LOG] + r_vbs.SLOC_lines[LOG] + r_cs.SLOC_lines[LOG]);
					}
					(*pout) << " |";
					(*pout).width(8);		(*pout) << r_htm.SLOC_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_js.SLOC_lines[LOG];
					(*pout) << " ";
					(*pout).width(8);		(*pout) << r_vbs.SLOC_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << r_cs.SLOC_lines[LOG];
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(7);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(10);		(*pout) << "0";
					(*pout) << " ";
					(*pout).width(8);		(*pout) << "0";
					if (!print_legacy)
					{
						(*pout) << " |";					
						(*pout).width(8);	(*pout) << (r_htm.SLOC_lines[LOG] + r_js.SLOC_lines[LOG] + r_vbs.SLOC_lines[LOG] + r_cs.SLOC_lines[LOG]);
						(*pout) << " |";
						(*pout).width(9);	(*pout) << (r_htm.SLOC_lines[PHY] + r_js.SLOC_lines[PHY] + r_vbs.SLOC_lines[PHY] + r_cs.SLOC_lines[PHY]);
					}
					(*pout) << " | CODE  ";
					(*pout) << its->second.file_name << endl;
					(*pout).unsetf(ios::right);
				}
				if (print_csv)
				{
					(*pout_csv) << (r_htm.total_lines + r_js.total_lines + r_vbs.total_lines + r_cs.total_lines) << ",";
					(*pout_csv) << (r_htm.blank_lines + r_js.blank_lines + r_vbs.blank_lines + r_cs.blank_lines) << ",";
					(*pout_csv) << (r_htm.comment_lines + r_js.comment_lines + r_vbs.comment_lines + r_cs.comment_lines) << ",";
					(*pout_csv) << (r_htm.e_comm_lines + r_js.e_comm_lines + r_vbs.e_comm_lines + r_cs.e_comm_lines) << ",";
					(*pout_csv) << r_htm.data_lines[LOG] << ",";
					(*pout_csv) << r_htm.exec_lines[LOG] << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << r_js.data_lines[LOG] << ",";
					(*pout_csv) << r_js.exec_lines[LOG] << ",";
					(*pout_csv) << r_vbs.data_lines[LOG] << ",";
					(*pout_csv) << r_vbs.exec_lines[LOG] << ",";
					(*pout_csv) << r_cs.data_lines[LOG] << ",";
					(*pout_csv) << r_cs.exec_lines[LOG] << ",";					
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";					
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";					
					(*pout_csv) << r_htm.SLOC_lines[LOG] << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << r_js.SLOC_lines[LOG] << ",";
					(*pout_csv) << r_vbs.SLOC_lines[LOG] << ",";
					(*pout_csv) << r_cs.SLOC_lines[LOG] << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";	
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << "0" << ",";
					(*pout_csv) << (r_htm.SLOC_lines[LOG] + r_js.SLOC_lines[LOG] + r_vbs.SLOC_lines[LOG] + r_cs.SLOC_lines[LOG]) << ",";
					(*pout_csv) << (r_htm.SLOC_lines[PHY] + r_js.SLOC_lines[PHY] + r_vbs.SLOC_lines[PHY] + r_cs.SLOC_lines[PHY]) << ",";
					(*pout_csv) << "CODE," << its->second.file_name << endl;
				}

				webtotal[webType].num_of_file++;

				webtotal[webType].total_line += (r_htm.total_lines + r_js.total_lines + r_vbs.total_lines + r_cs.total_lines);
				webtotal[webType].blank_line += (r_htm.blank_lines + r_js.blank_lines + r_vbs.blank_lines + r_cs.blank_lines);
				webtotal[webType].whole_comment += (r_htm.comment_lines + r_js.comment_lines + r_vbs.comment_lines + r_cs.comment_lines);
				webtotal[webType].embed_comment += (r_htm.e_comm_lines + r_js.e_comm_lines + r_vbs.e_comm_lines + r_cs.e_comm_lines);

				//0:htm 1:js 2:vbs 3:csharp
				webtotal[webType].phy_decl[0] += r_htm.data_lines[PHY];
				webtotal[webType].phy_instr[0] += r_htm.exec_lines[PHY];
				webtotal[webType].log_decl[0] += r_htm.data_lines[LOG];
				webtotal[webType].log_instr[0] += r_htm.exec_lines[LOG];

				webtotal[webType].phy_decl[1] += r_js.data_lines[PHY];
				webtotal[webType].phy_instr[1] += r_js.exec_lines[PHY];
				webtotal[webType].log_decl[1] += r_js.data_lines[LOG];
				webtotal[webType].log_instr[1] += r_js.exec_lines[LOG];

				webtotal[webType].phy_decl[2] += r_vbs.data_lines[PHY];
				webtotal[webType].phy_instr[2] += r_vbs.exec_lines[PHY];
				webtotal[webType].log_decl[2] += r_vbs.data_lines[LOG];
				webtotal[webType].log_instr[2] += r_vbs.exec_lines[LOG];

				webtotal[webType].phy_decl[3] += r_cs.data_lines[PHY];
				webtotal[webType].phy_instr[3] += r_cs.exec_lines[PHY];
				webtotal[webType].log_decl[3] += r_cs.data_lines[LOG];
				webtotal[webType].log_instr[3] += r_cs.exec_lines[LOG];

				allWebLang.num_of_file++;

				allWebLang.total_line += (r_htm.total_lines + r_js.total_lines + r_vbs.total_lines + r_cs.total_lines);
				allWebLang.blank_line += (r_htm.blank_lines + r_js.blank_lines + r_vbs.blank_lines + r_cs.blank_lines);
				allWebLang.whole_comment += (r_htm.comment_lines + r_js.comment_lines + r_vbs.comment_lines + r_cs.comment_lines);
				allWebLang.embed_comment += (r_htm.e_comm_lines + r_js.e_comm_lines + r_vbs.e_comm_lines + r_cs.e_comm_lines);

				allWebLang.phy_decl[0] += r_htm.data_lines[PHY];
				allWebLang.phy_instr[0] += r_htm.exec_lines[PHY];
				allWebLang.log_decl[0] += r_htm.data_lines[LOG];
				allWebLang.log_instr[0] += r_htm.exec_lines[LOG];

				allWebLang.phy_decl[2] += r_js.data_lines[PHY];
				allWebLang.phy_instr[2] += r_js.exec_lines[PHY];
				allWebLang.log_decl[2] += r_js.data_lines[LOG];
				allWebLang.log_instr[2] += r_js.exec_lines[LOG];

				allWebLang.phy_decl[3] += r_vbs.data_lines[PHY];
				allWebLang.phy_instr[3] += r_vbs.exec_lines[PHY];
				allWebLang.log_decl[3] += r_vbs.data_lines[LOG];
				allWebLang.log_instr[3] += r_vbs.exec_lines[LOG];

				allWebLang.phy_decl[4] += r_cs.data_lines[PHY];
				allWebLang.phy_instr[4] += r_cs.exec_lines[PHY];
				allWebLang.log_decl[4] += r_cs.data_lines[LOG];
				allWebLang.log_instr[4] += r_cs.exec_lines[LOG];
			}

			// skip the other web language partial file
			its = --endpos;
		}
	}

	// display summary for WEB languages
	totalNonDupFileA = 0; totalFileA = 0;
	totalNonDupFileB = 0; totalFileB = 0;
	tslocrat = 0.0f; tpsloc = 0; tlsloc = 0;
	for (WebTotalValueMap::iterator itto = webtotal.begin(); itto != webtotal.end(); itto++)
	{
		webCounter = (CWebCounter*)CounterForEachLanguage[WEB];
		if (filesToPrint != NULL)
		{
			if (excludeFiles)
			{
				if (useListA)
				{
					if (itto->first == WEB_PHP)
						totalNonDupFileA += webCounter->total_php_filesA - webCounter->total_php_dupFilesA;
					else if (itto->first == WEB_ASP)
						totalNonDupFileA += webCounter->total_asp_filesA - webCounter->total_asp_dupFilesA;
					else if (itto->first == WEB_JSP)
						totalNonDupFileA += webCounter->total_jsp_filesA - webCounter->total_jsp_dupFilesA;
					else if (itto->first == WEB_XML)
						totalNonDupFileA += webCounter->total_xml_filesA - webCounter->total_xml_dupFilesA;
					else if (itto->first == WEB_CFM)
						totalNonDupFileA += webCounter->total_cfm_filesA - webCounter->total_cfm_dupFilesA;
					else
						totalNonDupFileA += webCounter->total_htm_filesA - webCounter->total_htm_dupFilesA;
				}
				else
				{
					if (itto->first == WEB_PHP)
						totalNonDupFileB += webCounter->total_php_filesB - webCounter->total_php_dupFilesB;
					else if (itto->first == WEB_ASP)
						totalNonDupFileB += webCounter->total_asp_filesB - webCounter->total_asp_dupFilesB;
					else if (itto->first == WEB_JSP)
						totalNonDupFileB += webCounter->total_jsp_filesB - webCounter->total_jsp_dupFilesB;
					else if (itto->first == WEB_XML)
						totalNonDupFileA += webCounter->total_xml_filesB - webCounter->total_xml_dupFilesB;
					else if (itto->first == WEB_CFM)
						totalNonDupFileB += webCounter->total_cfm_filesB - webCounter->total_cfm_dupFilesB;
					else
						totalNonDupFileB += webCounter->total_htm_filesB - webCounter->total_htm_dupFilesB;
				}
			}
			else
			{
				if (useListA)
				{
					if (itto->first == WEB_PHP)
						totalNonDupFileA += webCounter->total_php_dupFilesA;
					else if (itto->first == WEB_ASP)
						totalNonDupFileA += webCounter->total_asp_dupFilesA;
					else if (itto->first == WEB_JSP)
						totalNonDupFileA += webCounter->total_jsp_dupFilesA;
					else if (itto->first == WEB_XML)
						totalNonDupFileA += webCounter->total_xml_dupFilesA;
					else if (itto->first == WEB_CFM)
						totalNonDupFileA += webCounter->total_cfm_dupFilesA;
					else
						totalNonDupFileA += webCounter->total_htm_dupFilesA;
				}
				else
				{
					if (itto->first == WEB_PHP)
						totalNonDupFileB += webCounter->total_php_dupFilesB;
					else if (itto->first == WEB_ASP)
						totalNonDupFileB += webCounter->total_asp_dupFilesB;
					else if (itto->first == WEB_JSP)
						totalNonDupFileB += webCounter->total_jsp_dupFilesB;
					else if (itto->first == WEB_XML)
						totalNonDupFileA += webCounter->total_xml_dupFilesB;
					else if (itto->first == WEB_CFM)
						totalNonDupFileB += webCounter->total_cfm_dupFilesB;
					else
						totalNonDupFileB += webCounter->total_htm_dupFilesB;
				}
			}
		}
		else if (useListA)
		{
			if (itto->first == WEB_PHP)
				totalFileA += webCounter->total_php_filesA;
			else if (itto->first == WEB_ASP)
				totalFileA += webCounter->total_asp_filesA;
			else if (itto->first == WEB_JSP)
				totalFileA += webCounter->total_jsp_filesA;
			else if (itto->first == WEB_XML)
				totalFileA += webCounter->total_xml_filesA;
			else if (itto->first == WEB_CFM)
				totalFileA += webCounter->total_cfm_filesA;
			else
				totalFileA += webCounter->total_htm_filesA;
		}
		else
		{
			if (itto->first == WEB_PHP)
				totalFileB += webCounter->total_php_filesB;
			else if (itto->first == WEB_ASP)
				totalFileB += webCounter->total_asp_filesB;
			else if (itto->first == WEB_JSP)
				totalFileB += webCounter->total_jsp_filesB;
			else if (itto->first == WEB_XML)
				totalFileA += webCounter->total_xml_filesB;
			else if (itto->first == WEB_CFM)
				totalFileB += webCounter->total_cfm_filesB;
			else
				totalFileB += webCounter->total_htm_filesB;
		}

		tlsloc += itto->second.log_decl[0] + itto->second.log_instr[0] +
			itto->second.log_decl[1] + itto->second.log_instr[1] +
			itto->second.log_decl[2] + itto->second.log_instr[2] +
			itto->second.log_decl[3] + itto->second.log_instr[3] +
			itto->second.log_decl[4] + itto->second.log_instr[4] +
			itto->second.log_decl[5] + itto->second.log_instr[5];

		tpsloc += itto->second.phy_decl[0] + itto->second.phy_instr[0] +
			itto->second.phy_decl[1] + itto->second.phy_instr[1] +
			itto->second.phy_decl[2] + itto->second.phy_instr[2] +
			itto->second.phy_decl[3] + itto->second.phy_instr[3] +
			itto->second.phy_decl[4] + itto->second.phy_instr[4] +
			itto->second.phy_decl[5] + itto->second.phy_instr[5];
	}

	if (webtotal.size() > 0) 
	{
		if (print_ascii || print_legacy)
		{
			(*pout) << endl;
			CUtil::PrintFileHeaderLine(*pout, "RESULTS SUMMARY FOR WEB LANGUAGES");
			(*pout) << endl;
			(*pout) << "                                    |       HTML      |        XML      |     JS-Clnt     |    VBS-Clnt     |     C#-Clnt     |      JS-Svr     |     VBS-Svr     |      C#-Svr     |           PHP           |          Java           |       SQL       |    ColdFusion   |     CFScript    |" << endl;
			if (print_legacy)
			{
				(*pout) << "   Total   Blank |      Comments    |    Word  Exec.  |    Word  Exec.  |   Data   Exec.  |   Data   Exec.  |   Data   Exec.  |   Data   Exec.  |   Data   Exec.  |   Data   Exec.  | Compiler  Data   Exec.  | Compiler  Data   Exec.  |   Data   Exec.  |   Data   Exec.  |   Data   Exec.  |                                                              SLOC                                                      | File  SLOC" << endl;
				(*pout) << "   Lines   Lines |   Whole Embedded |     LOC  Instr. |     LOC  Instr. |   Decl.  Instr. |   Decl.  Instr. |   Decl.  Instr. |   Decl.  Instr. |   Decl.  Instr. |   Decl.  Instr. | Direct.   Decl.  Instr. | Direct.   Decl.  Instr. |   Decl.  Instr. |   Decl.  Instr. |   Decl.  Instr. |   Total      HTML     XML JS-Clnt VBS-Clnt C#-Clnt  JS-Svr VBS-Svr  C#-Svr     PHP    Java     SQL ColdFusion CFScript | Type  Definition" << endl;
				(*pout) << "-----------------+------------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-------------------------+-------------------------+-----------------+-----------------+-----------------+---------+--------------------------------------------------------------------------------------------------------------+------------------" << endl;
			}
			else
			{
				(*pout) << "   Total   Blank |      Comments    |    Word  Exec.  |    Word  Exec.  |   Data   Exec.  |   Data   Exec.  |   Data   Exec.  |   Data   Exec.  |   Data   Exec.  |   Data   Exec.  | Compiler  Data   Exec.  | Compiler  Data   Exec.  |   Data   Exec.  |   Data   Exec.  |   Data   Exec.  |                                                              SLOC                                                      | File  SLOC" << endl;
				(*pout) << "   Lines   Lines |   Whole Embedded |     LOC  Instr. |     LOC  Instr. |   Decl.  Instr. |   Decl.  Instr. |   Decl.  Instr. |   Decl.  Instr. |   Decl.  Instr. |   Decl.  Instr. | Direct.   Decl.  Instr. | Direct.   Decl.  Instr. |   Decl.  Instr. |   Decl.  Instr. |   Decl.  Instr. |    HTML     XML JS-Clnt VBS-Clnt C#-Clnt  JS-Svr VBS-Svr  C#-Svr     PHP    Java     SQL ColdFusion CFScript     Total | Type  Definition" << endl;
				(*pout) << "-----------------+------------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-----------------+-------------------------+-------------------------+-----------------+-----------------+-----------------+--------------------------------------------------------------------------------------------------------------+---------+------------------" << endl;
			}

			(*pout).setf(ios::right);
			(*pout).width(8);		(*pout) << allWebLang.total_line;
			(*pout) << " ";
			(*pout).width(7);		(*pout) << allWebLang.blank_line;
			(*pout) << " |";
			(*pout).width(8);		(*pout) << allWebLang.whole_comment;
			(*pout) << " ";
			(*pout).width(8);		(*pout) << allWebLang.embed_comment;
			(*pout) << " |";	// 0 - HTML
			(*pout).width(8);		(*pout) << allWebLang.phy_decl[0];
			(*pout) << " ";
			(*pout).width(7);		(*pout) << allWebLang.phy_instr[0];
			(*pout) << " |";	// 1 - XML
			(*pout).width(8);		(*pout) << allWebLang.phy_decl[1];
			(*pout) << " ";
			(*pout).width(7);		(*pout) << allWebLang.phy_instr[1];
			(*pout) << " |";	// 2 - JSclnt
			(*pout).width(8);		(*pout) << allWebLang.phy_decl[2];
			(*pout) << " ";
			(*pout).width(7);		(*pout) << allWebLang.phy_instr[2];
			(*pout) << " |";	// 3 - VBSclnt
			(*pout).width(8);		(*pout) << allWebLang.phy_decl[3];
			(*pout) << " ";
			(*pout).width(7);		(*pout) << allWebLang.phy_instr[3];
			(*pout) << " |";	// 4 - C#clnt
			(*pout).width(8);		(*pout) << allWebLang.phy_decl[4];
			(*pout) << " ";
			(*pout).width(7);		(*pout) << allWebLang.phy_instr[4];
			(*pout) << " |";	// 5 - JSsrv
			(*pout).width(8);		(*pout) << allWebLang.phy_decl[5];
			(*pout) << " ";
			(*pout).width(7);		(*pout) << allWebLang.phy_instr[5];
			(*pout) << " |";	// 6 - VBSsrv
			(*pout).width(8);		(*pout) << allWebLang.phy_decl[6];
			(*pout) << " ";
			(*pout).width(7);		(*pout) << allWebLang.phy_instr[6];
			(*pout) << " |";	// 7 - C#srv
			(*pout).width(8);		(*pout) << allWebLang.phy_decl[7];
			(*pout) << " ";
			(*pout).width(7);		(*pout) << allWebLang.phy_instr[7];
			(*pout) << " |";	// 8 - PHP
			(*pout).width(8);		(*pout) << allWebLang.phy_direct[8];
			(*pout) << " ";
			(*pout).width(7);		(*pout) << allWebLang.phy_decl[8];
			(*pout) << " ";
			(*pout).width(7);		(*pout) << allWebLang.phy_instr[8];
			(*pout) << " |";	// 9 - Java
			(*pout).width(8);		(*pout) << allWebLang.phy_direct[9];
			(*pout) << " ";
			(*pout).width(7);		(*pout) << allWebLang.phy_decl[9];
			(*pout) << " ";
			(*pout).width(7);		(*pout) << allWebLang.phy_instr[9];
			(*pout) << " |";	//10 - SQL
			(*pout).width(8);		(*pout) << allWebLang.phy_decl[10];
			(*pout) << " ";
			(*pout).width(7);		(*pout) << allWebLang.phy_instr[10];
			(*pout) << " |";	//11 - CF
			(*pout).width(8);		(*pout) << allWebLang.phy_decl[11];
			(*pout) << " ";
			(*pout).width(7);		(*pout) << allWebLang.phy_instr[11];
			(*pout) << " |";	//12 - CFS
			(*pout).width(8);		(*pout) << allWebLang.phy_decl[12];
			(*pout) << " ";
			(*pout).width(7);		(*pout) << allWebLang.phy_instr[12];
			if (print_legacy)
			{
				(*pout) << " |";
				(*pout).width(8);		(*pout) << (allWebLang.phy_decl[0] + allWebLang.phy_instr[0] +
					allWebLang.phy_decl[1] + allWebLang.phy_instr[1] +
					allWebLang.phy_decl[2] + allWebLang.phy_instr[2] +
					allWebLang.phy_decl[3] + allWebLang.phy_instr[3] +
					allWebLang.phy_decl[4] + allWebLang.phy_instr[4] + 
					allWebLang.phy_decl[5] + allWebLang.phy_instr[5] +
					allWebLang.phy_decl[6] + allWebLang.phy_instr[6] +
					allWebLang.phy_decl[7] + allWebLang.phy_instr[7] +
					allWebLang.phy_direct[8] + allWebLang.phy_decl[8] + allWebLang.phy_instr[8] +
					allWebLang.phy_direct[9] + allWebLang.phy_decl[9] + allWebLang.phy_instr[9] +
					allWebLang.phy_decl[10] + allWebLang.phy_instr[10] +
					allWebLang.phy_decl[11] + allWebLang.phy_instr[11] +
					allWebLang.phy_decl[12] + allWebLang.phy_instr[12]);
			}
			(*pout) << " |";
			(*pout).width(8);		(*pout) << (allWebLang.phy_decl[0] + allWebLang.phy_instr[0]);		// HTML
			(*pout) << " ";
			(*pout).width(7);		(*pout) << (allWebLang.phy_decl[1] + allWebLang.phy_instr[1]);		// XML
			(*pout) << " ";
			(*pout).width(7);		(*pout) << (allWebLang.phy_decl[2] + allWebLang.phy_instr[2]);		// JSclnt
			(*pout) << " ";
			(*pout).width(8);		(*pout) << (allWebLang.phy_decl[3] + allWebLang.phy_instr[3]);		// VBSclnt
			(*pout) << " ";
			(*pout).width(7);		(*pout) << (allWebLang.phy_decl[4] + allWebLang.phy_instr[4]);		// C#clnt
			(*pout) << " ";
			(*pout).width(7);		(*pout) << (allWebLang.phy_decl[5] + allWebLang.phy_instr[5]);		// JSsrv
			(*pout) << " ";
			(*pout).width(7);		(*pout) << (allWebLang.phy_decl[6] + allWebLang.phy_instr[6]);		// VBSsrv
			(*pout) << " ";
			(*pout).width(7);		(*pout) << (allWebLang.phy_decl[7] + allWebLang.phy_instr[7]);		// C#srv
			(*pout) << " ";
			(*pout).width(7);		(*pout) << (allWebLang.phy_direct[8] + allWebLang.phy_decl[8] + allWebLang.phy_instr[8]);	// PHP
			(*pout) << " ";
			(*pout).width(7);		(*pout) << (allWebLang.phy_direct[9] + allWebLang.phy_decl[9] + allWebLang.phy_instr[9]);	// Java
			(*pout) << " ";
			(*pout).width(7);		(*pout) << (allWebLang.phy_decl[10] + allWebLang.phy_instr[10]);		// SQL
			(*pout) << " ";
			(*pout).width(10);		(*pout) << (allWebLang.phy_decl[11] + allWebLang.phy_instr[11]);	// CF
			(*pout) << " ";
			(*pout).width(8);		(*pout) << (allWebLang.phy_decl[12] + allWebLang.phy_instr[12]);	// CFS
			if (!print_legacy)
			{
				(*pout) << " |";
				(*pout).width(8);		(*pout) << (allWebLang.phy_decl[0] + allWebLang.phy_instr[0] +
					allWebLang.phy_decl[1] + allWebLang.phy_instr[1] +
					allWebLang.phy_decl[2] + allWebLang.phy_instr[2] +
					allWebLang.phy_decl[3] + allWebLang.phy_instr[3] +
					allWebLang.phy_decl[4] + allWebLang.phy_instr[4] + 
					allWebLang.phy_decl[5] + allWebLang.phy_instr[5] +
					allWebLang.phy_decl[6] + allWebLang.phy_instr[6] +
					allWebLang.phy_decl[7] + allWebLang.phy_instr[7] +
					allWebLang.phy_direct[8] + allWebLang.phy_decl[8] + allWebLang.phy_instr[8] +
					allWebLang.phy_direct[9] + allWebLang.phy_decl[9] + allWebLang.phy_instr[9] +
					allWebLang.phy_decl[10] + allWebLang.phy_instr[10] +
					allWebLang.phy_decl[11] + allWebLang.phy_instr[11] +
					allWebLang.phy_decl[12] + allWebLang.phy_instr[12]);
			}
			(*pout) << " | CODE  Physical" << endl;

			(*pout).setf(ios::right);
			(*pout).width(8);		(*pout) << allWebLang.total_line;
			(*pout) << " ";
			(*pout).width(7);		(*pout) << allWebLang.blank_line;
			(*pout) << " |";
			(*pout).width(8);		(*pout) << allWebLang.whole_comment;
			(*pout) << " ";
			(*pout).width(8);		(*pout) << allWebLang.embed_comment;
			(*pout) << " |";	// 0 - HTML
			(*pout).width(8);		(*pout) << allWebLang.log_decl[0];
			(*pout) << " ";
			(*pout).width(7);		(*pout) << allWebLang.log_instr[0];
			(*pout) << " |";	// 1 - XML
			(*pout).width(8);		(*pout) << allWebLang.log_decl[1];
			(*pout) << " ";
			(*pout).width(7);		(*pout) << allWebLang.log_instr[1];
			(*pout) << " |";	// 2 - JSclnt
			(*pout).width(8);		(*pout) << allWebLang.log_decl[2];
			(*pout) << " ";
			(*pout).width(7);		(*pout) << allWebLang.log_instr[2];
			(*pout) << " |";	// 3 - VBSclnt
			(*pout).width(8);		(*pout) << allWebLang.log_decl[3];
			(*pout) << " ";
			(*pout).width(7);		(*pout) << allWebLang.log_instr[3];
			(*pout) << " |";	// 4 - C#clnt
			(*pout).width(8);		(*pout) << allWebLang.log_decl[4];
			(*pout) << " ";
			(*pout).width(7);		(*pout) << allWebLang.log_instr[4];
			(*pout) << " |";	// 5 - JSsrv
			(*pout).width(8);		(*pout) << allWebLang.log_decl[5];
			(*pout) << " ";
			(*pout).width(7);		(*pout) << allWebLang.log_instr[5];
			(*pout) << " |";	// 6 - VBSsrv
			(*pout).width(8);		(*pout) << allWebLang.log_decl[6];
			(*pout) << " ";
			(*pout).width(7);		(*pout) << allWebLang.log_instr[6];
			(*pout) << " |";	// 7 - C#srv
			(*pout).width(8);		(*pout) << allWebLang.log_decl[7];
			(*pout) << " ";
			(*pout).width(7);		(*pout) << allWebLang.log_instr[7];
			(*pout) << " |";	// 8 - PHP
			(*pout).width(8);		(*pout) << allWebLang.log_direct[8];
			(*pout) << " ";
			(*pout).width(7);		(*pout) << allWebLang.log_decl[8];
			(*pout) << " ";
			(*pout).width(7);		(*pout) << allWebLang.log_instr[8];
			(*pout) << " |";	// 9 - Java
			(*pout).width(8);		(*pout) << allWebLang.log_direct[9];
			(*pout) << " ";
			(*pout).width(7);		(*pout) << allWebLang.log_decl[9];
			(*pout) << " ";
			(*pout).width(7);		(*pout) << allWebLang.log_instr[9];
			(*pout) << " |";	//10 - SQL
			(*pout).width(8);		(*pout) << allWebLang.log_decl[10];
			(*pout) << " ";
			(*pout).width(7);		(*pout) << allWebLang.log_instr[10];
			(*pout) << " |";	//11 - CF
			(*pout).width(8);		(*pout) << allWebLang.log_decl[11];
			(*pout) << " ";
			(*pout).width(7);		(*pout) << allWebLang.log_instr[11];
			(*pout) << " |";	//12 - CFS
			(*pout).width(8);		(*pout) << allWebLang.log_decl[12];
			(*pout) << " ";
			(*pout).width(7);		(*pout) << allWebLang.log_instr[12];
			if (print_legacy)
			{
				(*pout) << " |";
				(*pout).width(7);		(*pout) << (allWebLang.log_decl[0] + allWebLang.log_instr[0] +
					allWebLang.log_decl[1] + allWebLang.log_instr[1] +
					allWebLang.log_decl[2] + allWebLang.log_instr[2] +
					allWebLang.log_decl[3] + allWebLang.log_instr[3] +
					allWebLang.log_decl[4] + allWebLang.log_instr[4] + 
					allWebLang.log_decl[5] + allWebLang.log_instr[5] +
					allWebLang.log_decl[6] + allWebLang.log_instr[6] +
					allWebLang.log_decl[7] + allWebLang.log_instr[7] +
					allWebLang.log_direct[8] + allWebLang.log_decl[8] + allWebLang.log_instr[8] +
					allWebLang.log_direct[9] + allWebLang.log_decl[9] + allWebLang.log_instr[9] +
					allWebLang.log_decl[10] + allWebLang.log_instr[10] +
					allWebLang.log_decl[11] + allWebLang.log_instr[11] +
					allWebLang.log_decl[12] + allWebLang.log_instr[12]);
			}
			(*pout) << " |";
			(*pout).width(8);		(*pout) << (allWebLang.log_decl[0] + allWebLang.log_instr[0]);		// HTML
			(*pout) << " ";
			(*pout).width(7);		(*pout) << (allWebLang.log_decl[1] + allWebLang.log_instr[1]);		// XML
			(*pout) << " ";
			(*pout).width(7);		(*pout) << (allWebLang.log_decl[2] + allWebLang.log_instr[2]);		// JSclnt
			(*pout) << " ";
			(*pout).width(8);		(*pout) << (allWebLang.log_decl[3] + allWebLang.log_instr[3]);		// VBSclnt
			(*pout) << " ";
			(*pout).width(7);		(*pout) << (allWebLang.log_decl[4] + allWebLang.log_instr[4]);		// C#clnt
			(*pout) << " ";
			(*pout).width(7);		(*pout) << (allWebLang.log_decl[5] + allWebLang.log_instr[5]);		// JSsvr
			(*pout) << " ";
			(*pout).width(7);		(*pout) << (allWebLang.log_decl[6] + allWebLang.log_instr[6]);		// VBSsrv
			(*pout) << " ";
			(*pout).width(7);		(*pout) << (allWebLang.log_decl[7] + allWebLang.log_instr[7]);		// C#srv
			(*pout) << " ";
			(*pout).width(7);		(*pout) << (allWebLang.log_direct[8] + allWebLang.log_decl[8] + allWebLang.log_instr[8]);	// PHP
			(*pout) << " ";
			(*pout).width(7);		(*pout) << (allWebLang.log_direct[9] + allWebLang.log_decl[9] + allWebLang.log_instr[9]);	// Java
			(*pout) << " ";
			(*pout).width(7);		(*pout) << (allWebLang.log_decl[10] + allWebLang.log_instr[10]);		// SQL
			(*pout) << " ";
			(*pout).width(10);		(*pout) << (allWebLang.log_decl[11] + allWebLang.log_instr[11]);	// CF
			(*pout) << " ";
			(*pout).width(8);		(*pout) << (allWebLang.log_decl[12] + allWebLang.log_instr[12]);	// CFS
			if (!print_legacy)
			{
				(*pout) << " |";
				(*pout).width(8);		(*pout) << (allWebLang.log_decl[0] + allWebLang.log_instr[0] +
					allWebLang.log_decl[1] + allWebLang.log_instr[1] +
					allWebLang.log_decl[2] + allWebLang.log_instr[2] +
					allWebLang.log_decl[3] + allWebLang.log_instr[3] +
					allWebLang.log_decl[4] + allWebLang.log_instr[4] + 
					allWebLang.log_decl[5] + allWebLang.log_instr[5] +
					allWebLang.log_decl[6] + allWebLang.log_instr[6] +
					allWebLang.log_decl[7] + allWebLang.log_instr[7] +
					allWebLang.log_direct[8] + allWebLang.log_decl[8] + allWebLang.log_instr[8] +
					allWebLang.log_direct[9] + allWebLang.log_decl[9] + allWebLang.log_instr[9] +
					allWebLang.log_decl[10] + allWebLang.log_instr[10] +
					allWebLang.log_decl[11] + allWebLang.log_instr[11] +
					allWebLang.log_decl[12] + allWebLang.log_instr[12]);
			}
			(*pout) << " | CODE  Logical" << endl;

			// display statistics
			(*pout) << endl << "Number of files successfully accessed........................ ";
			(*pout).width(5);		(*pout) << allWebLang.num_of_file;
			(*pout) << " out of ";
			if (filesToPrint != NULL)
			{
				if (useListA)
					(*pout) << totalNonDupFileA << endl;
				else
					(*pout) << totalNonDupFileB << endl;
			}
			else if (useListA)
				(*pout) << totalFileA << endl;
			else
				(*pout) << totalFileB << endl;

			(*pout) << endl << "Ratio of Physical to Logical SLOC............................ ";

			if (tlsloc > 0)
			{
				tslocrat = (float)tpsloc / (float)tlsloc;
				(*pout).setf(ios::fixed,ios::floatfield);
				(*pout).width(8);
				(*pout).precision(2);
				(*pout) << tslocrat << endl;
				(*pout).unsetf(ios::floatfield);
			}
			else
				(*pout) << "    NA" << endl;
		}
		if (print_csv)
		{
			(*pout_csv) << endl;
			CUtil::PrintFileHeaderLine(*pout_csv, "RESULTS SUMMARY FOR WEB LANGUAGES");
			(*pout_csv) << ",,,,HTML,,XML,,JS-Clnt,,VBS-Clnt,,C#-Clnt,,JS-Svr,,VBS-Svr,,C#-Svr,,PHP,,,Java,,,SQL,,ColdFusion,,CFScript" << endl;
			(*pout_csv) << "Total,Blank,Comments,,Word,Exec.,Word,Exec.,Data,Exec.,Data,Exec.,Data,Exec.,Data,Exec.,Data,Exec.,Data,Exec.,Compiler,Data,Exec.,Compiler,Data,Exec.,Data,Exec.,Data,Exec.,Data,Exec.,SLOC,,,,,,,,,,,,,File,SLOC" << endl;
			(*pout_csv) << "Lines,Lines,Whole,Embedded,LOC,Instr.,LOC,Instr.,Decl.,Instr.,Decl.,Instr.,Decl.,Instr.,Decl.,Instr.,Decl.,Instr.,Decl.,Instr.,Direct.,Decl.,Instr.,Direct.,Decl.,Instr.,Decl.,Instr.,Decl.,Instr.,Decl.,Instr.,HTML,XML,JS-Clnt,VBS-Clnt,C#-Clnt,JS-Svr,VBS-Svr,C#-Svr,PHP,Java,SQL,ColdFusion,CFScript,Total,Type,Definition" << endl;

			(*pout_csv) << allWebLang.total_line << ",";
			(*pout_csv) << allWebLang.blank_line << ",";
			(*pout_csv) << allWebLang.whole_comment << ",";
			(*pout_csv) << allWebLang.embed_comment << ",";
			(*pout_csv) << allWebLang.phy_decl[0] << ",";
			(*pout_csv) << allWebLang.phy_instr[0] << ",";
			(*pout_csv) << allWebLang.phy_decl[1] << ",";
			(*pout_csv) << allWebLang.phy_instr[1] << ",";
			(*pout_csv) << allWebLang.phy_decl[2] << ",";
			(*pout_csv) << allWebLang.phy_instr[2] << ",";
			(*pout_csv) << allWebLang.phy_decl[3] << ",";
			(*pout_csv) << allWebLang.phy_instr[3] << ",";
			(*pout_csv) << allWebLang.phy_decl[4] << ",";
			(*pout_csv) << allWebLang.phy_instr[4] << ",";
			(*pout_csv) << allWebLang.phy_decl[5] << ",";
			(*pout_csv) << allWebLang.phy_instr[5] << ",";
			(*pout_csv) << allWebLang.phy_decl[6] << ",";
			(*pout_csv) << allWebLang.phy_instr[6] << ",";
			(*pout_csv) << allWebLang.phy_decl[7] << ",";
			(*pout_csv) << allWebLang.phy_instr[7] << ",";
			(*pout_csv) << allWebLang.phy_direct[8] << ",";
			(*pout_csv) << allWebLang.phy_decl[8] << ",";
			(*pout_csv) << allWebLang.phy_instr[8] << ",";
			(*pout_csv) << allWebLang.phy_direct[9] << ",";
			(*pout_csv) << allWebLang.phy_decl[9] << ",";
			(*pout_csv) << allWebLang.phy_instr[9] << ",";
			(*pout_csv) << allWebLang.phy_decl[10] << ",";
			(*pout_csv) << allWebLang.phy_instr[10] << ",";
			(*pout_csv) << allWebLang.phy_decl[11] << ",";
			(*pout_csv) << allWebLang.phy_instr[11] << ",";
			(*pout_csv) << allWebLang.phy_decl[12] << ",";
			(*pout_csv) << allWebLang.phy_instr[12] << ",";
			(*pout_csv) << (allWebLang.phy_decl[0] + allWebLang.phy_instr[0]) << ",";
			(*pout_csv) << (allWebLang.phy_decl[1] + allWebLang.phy_instr[1]) << ",";
			(*pout_csv) << (allWebLang.phy_decl[2] + allWebLang.phy_instr[2]) << ",";
			(*pout_csv) << (allWebLang.phy_decl[3] + allWebLang.phy_instr[3]) << ",";
			(*pout_csv) << (allWebLang.phy_decl[4] + allWebLang.phy_instr[4]) << ",";
			(*pout_csv) << (allWebLang.phy_decl[5] + allWebLang.phy_instr[5]) << ",";
			(*pout_csv) << (allWebLang.phy_decl[6] + allWebLang.phy_instr[6]) << ",";
			(*pout_csv) << (allWebLang.phy_decl[7] + allWebLang.phy_instr[7]) << ",";
			(*pout_csv) << (allWebLang.phy_direct[8] + allWebLang.phy_decl[8] + allWebLang.phy_instr[8]) << ",";
			(*pout_csv) << (allWebLang.phy_direct[9] + allWebLang.phy_decl[9] + allWebLang.phy_instr[9]) << ",";
			(*pout_csv) << (allWebLang.phy_decl[10] + allWebLang.phy_instr[10]) << ",";
			(*pout_csv) << (allWebLang.phy_decl[11] + allWebLang.phy_instr[11]) << ",";
			(*pout_csv) << (allWebLang.phy_decl[12] + allWebLang.phy_instr[12]) << ",";
			(*pout_csv) << (allWebLang.phy_decl[0] + allWebLang.phy_instr[0] +
				allWebLang.phy_decl[1] + allWebLang.phy_instr[1] +
				allWebLang.phy_decl[2] + allWebLang.phy_instr[2] +
				allWebLang.phy_decl[3] + allWebLang.phy_instr[3] +
				allWebLang.phy_decl[4] + allWebLang.phy_instr[4] + 
				allWebLang.phy_decl[5] + allWebLang.phy_instr[5] +
				allWebLang.phy_decl[6] + allWebLang.phy_instr[6] +
				allWebLang.phy_decl[7] + allWebLang.phy_instr[7] +
				allWebLang.phy_direct[8] + allWebLang.phy_decl[8] + allWebLang.phy_instr[8] +
				allWebLang.phy_direct[9] + allWebLang.phy_decl[9] + allWebLang.phy_instr[9] +
				allWebLang.phy_decl[10] + allWebLang.phy_instr[10] +
				allWebLang.phy_decl[11] + allWebLang.phy_instr[11] +
				allWebLang.phy_decl[12] + allWebLang.phy_instr[12]) << ",";
			(*pout_csv) << "CODE,Physical" << endl;

			(*pout_csv) << allWebLang.total_line << ",";
			(*pout_csv) << allWebLang.blank_line << ",";
			(*pout_csv) << allWebLang.whole_comment << ",";
			(*pout_csv) << allWebLang.embed_comment << ",";
			(*pout_csv) << allWebLang.log_decl[0] << ",";
			(*pout_csv) << allWebLang.log_instr[0] << ",";
			(*pout_csv) << allWebLang.log_decl[1] << ",";
			(*pout_csv) << allWebLang.log_instr[1] << ",";
			(*pout_csv) << allWebLang.log_decl[2] << ",";
			(*pout_csv) << allWebLang.log_instr[2] << ",";
			(*pout_csv) << allWebLang.log_decl[3] << ",";
			(*pout_csv) << allWebLang.log_instr[3] << ",";
			(*pout_csv) << allWebLang.log_decl[4] << ",";
			(*pout_csv) << allWebLang.log_instr[4] << ",";
			(*pout_csv) << allWebLang.log_decl[5] << ",";
			(*pout_csv) << allWebLang.log_instr[5] << ",";
			(*pout_csv) << allWebLang.log_decl[6] << ",";
			(*pout_csv) << allWebLang.log_instr[6] << ",";
			(*pout_csv) << allWebLang.log_decl[7] << ",";
			(*pout_csv) << allWebLang.log_instr[7] << ",";
			(*pout_csv) << allWebLang.log_direct[8] << ",";
			(*pout_csv) << allWebLang.log_decl[8] << ",";
			(*pout_csv) << allWebLang.log_instr[8] << ",";
			(*pout_csv) << allWebLang.log_direct[9] << ",";
			(*pout_csv) << allWebLang.log_decl[9] << ",";
			(*pout_csv) << allWebLang.log_instr[9] << ",";
			(*pout_csv) << allWebLang.log_decl[10] << ",";
			(*pout_csv) << allWebLang.log_instr[10] << ",";
			(*pout_csv) << allWebLang.log_decl[11] << ",";
			(*pout_csv) << allWebLang.log_instr[11] << ",";
			(*pout_csv) << allWebLang.log_decl[12] << ",";
			(*pout_csv) << allWebLang.log_instr[12] << ",";
			(*pout_csv) << (allWebLang.log_decl[0] + allWebLang.log_instr[0]) << ",";
			(*pout_csv) << (allWebLang.log_decl[1] + allWebLang.log_instr[1]) << ",";
			(*pout_csv) << (allWebLang.log_decl[2] + allWebLang.log_instr[2]) << ",";
			(*pout_csv) << (allWebLang.log_decl[3] + allWebLang.log_instr[3]) << ",";
			(*pout_csv) << (allWebLang.log_decl[4] + allWebLang.log_instr[4]) << ",";
			(*pout_csv) << (allWebLang.log_decl[5] + allWebLang.log_instr[5]) << ",";
			(*pout_csv) << (allWebLang.log_decl[6] + allWebLang.log_instr[6]) << ",";
			(*pout_csv) << (allWebLang.log_decl[7] + allWebLang.log_instr[7]) << ",";
			(*pout_csv) << (allWebLang.log_direct[8] + allWebLang.log_decl[8] + allWebLang.log_instr[8]) << ",";
			(*pout_csv) << (allWebLang.log_direct[9] + allWebLang.log_decl[9] + allWebLang.log_instr[9]) << ",";
			(*pout_csv) << (allWebLang.log_decl[10] + allWebLang.log_instr[10]) << ",";
			(*pout_csv) << (allWebLang.log_decl[11] + allWebLang.log_instr[11]) << ",";
			(*pout_csv) << (allWebLang.log_decl[12] + allWebLang.log_instr[12]) << ",";
			(*pout_csv) << (allWebLang.log_decl[0] + allWebLang.log_instr[0] +
				allWebLang.log_decl[1] + allWebLang.log_instr[1] +
				allWebLang.log_decl[2] + allWebLang.log_instr[2] +
				allWebLang.log_decl[3] + allWebLang.log_instr[3] +
				allWebLang.log_decl[4] + allWebLang.log_instr[4] + 
				allWebLang.log_decl[5] + allWebLang.log_instr[5] +
				allWebLang.log_decl[6] + allWebLang.log_instr[6] +
				allWebLang.log_decl[7] + allWebLang.log_instr[7] +
				allWebLang.log_direct[8] + allWebLang.log_decl[8] + allWebLang.log_instr[8] +
				allWebLang.log_direct[9] + allWebLang.log_decl[9] + allWebLang.log_instr[9] +
				allWebLang.log_decl[10] + allWebLang.log_instr[10] +
				allWebLang.log_decl[11] + allWebLang.log_instr[11] +
				allWebLang.log_decl[12] + allWebLang.log_instr[12]) << ",";
			(*pout_csv) << "CODE,Logical" << endl;

			// display statistics
			(*pout_csv) << endl << "Number of files successfully accessed,";
			(*pout_csv) << allWebLang.num_of_file;
			(*pout_csv) << ",out of,";

			if (filesToPrint != NULL)
			{
				if (useListA)
					(*pout_csv) << totalNonDupFileA << endl;
				else
					(*pout_csv) << totalNonDupFileB << endl;
			}
			else if (useListA)
				(*pout_csv) << totalFileA << endl;
			else
				(*pout_csv) << totalFileB << endl;

			(*pout_csv) << endl << "Ratio of Physical to Logical SLOC,";

			if (tlsloc > 0)
			{
				tslocrat = (float)tpsloc / (float)tlsloc;
				(*pout_csv).setf(ios::fixed,ios::floatfield);
				(*pout_csv).width(8);
				(*pout_csv).precision(2);
				(*pout_csv) << tslocrat << endl;
				(*pout_csv).unsetf(ios::floatfield);
			}
			else
				(*pout_csv) << "NA" << endl;
		}
	}

	if (print_cmplx)
	{
		string dots = "........................";
		UIntPairVector::iterator idirc;
		UIntPairVector::iterator idatc;
		UIntPairVector::iterator iexec;
		StringVector::iterator idir;
		StringVector::iterator idat;
		StringVector::iterator iexe;

		// display keyword counts
		unsigned int ty;
		for (map<int, CCodeCounter*>::iterator iter = ++CounterForEachLanguage.begin(); iter != CounterForEachLanguage.end(); iter++)
		{
			if (iter->second->directive.size() == 0 && iter->second->data_name_list.size() == 0 && iter->second->exec_name_list.size()  == 0)
				continue;
			else if (total.count(iter->second->classtype) == 0)
			{
				if (iter->second->isPrintKeyword && (excludeFiles ||
					(useListA && iter->second->total_dupFilesA > 0) || (!useListA && iter->second->total_dupFilesB > 0)))
				{
					ty = iter->second->classtype;
					if (ty == PHP || ty == HTML_PHP || ty == JAVASCRIPT_PHP || ty == VBS_PHP ||
						ty == JAVA_JSP || ty == HTML_JSP || ty == JAVASCRIPT_JSP || ty == VBS_JSP ||
						ty == HTML_ASP || ty == JAVASCRIPT_ASP_C || ty == VBS_ASP_C || ty == JAVASCRIPT_ASP_S || ty == VBS_ASP_S || ty == CSHARP_ASP_S ||
						ty == COLDFUSION || ty == CFSCRIPT || ty == HTML_CFM || ty == JAVASCRIPT_CFM || ty == VBS_CFM || ty == SQL_CFM ||
						ty == XML || ty == JAVASCRIPT_XML || ty == VBS_XML || ty == CSHARP_XML ||
						ty == HTML || ty == JAVASCRIPT_HTML || ty == VBS_HTML || ty == CSHARP_HTML)
					{
						if (print_ascii || print_legacy)
							pout = this->GetTotalOutputStream(outDir + outputFileNamePrePend);
						if (print_csv)
							pout_csv = this->GetTotalOutputStream(outDir + outputFileNamePrePend, true);
					}
					else
						continue;
				}
				else
					continue;
			}
			else
			{
				if (print_ascii || print_legacy)
					pout = this->GetTotalOutputStream(outDir + outputFileNamePrePend);
				if (print_csv)
					pout_csv = this->GetTotalOutputStream(outDir + outputFileNamePrePend, true);
			}

			if (print_ascii || print_legacy)
			{
				(*pout) << endl;
				CUtil::PrintFileHeaderLine(*pout, "TOTAL OCCURRENCES OF " + iter->second->language_name + " KEYWORDS");
				(*pout) << "--------------------------------------------------------------------------------------------------------------" << endl;
				(*pout) << "    Compiler Directives                  Data Keywords                        Executable Keywords" << endl;
				(*pout).setf(ios::right);
			}
			if (print_csv)
			{
				(*pout_csv) << endl;
				CUtil::PrintFileHeaderLine(*pout_csv, "TOTAL OCCURRENCES OF " + iter->second->language_name + " KEYWORDS");
				(*pout_csv) << "Compiler Directives,,Data Keywords,,Executable Keywords" << endl;
			}

			idirc = iter->second->directive_count.begin();
			idatc = iter->second->data_name_count.begin();
			iexec = iter->second->exec_name_count.begin();
			idir = iter->second->directive.begin();
			idat = iter->second->data_name_list.begin();
			iexe = iter->second->exec_name_list.begin();

			while ( (idir != iter->second->directive.end()) || (idat != iter->second->data_name_list.end()) ||
				(iexe != iter->second->exec_name_list.end()) )
			{
				if (idir != iter->second->directive.end())
				{
					if (print_ascii || print_legacy)
					{
						(*pout) << ' ' << *idir << dots.substr(idir->length());
						(*pout).width(7);
						if (filesToPrint != NULL && !excludeFiles)
							(*pout) << (*idirc).second;
						else
							(*pout) << (*idirc).first;
					}
					if (print_csv)
					{
						(*pout_csv) << *idir << ",";
						if (filesToPrint != NULL && !excludeFiles)
							(*pout_csv) << (*idirc).second << ",";
						else
							(*pout_csv) << (*idirc).first << ",";
					}
					idir++;
					idirc++;
				}
				else
				{
					if (print_ascii || print_legacy)
						(*pout) << "                                ";
					if (print_csv)
						(*pout_csv) << ",,";
				}
				if (print_ascii || print_legacy)
					(*pout) << "     ";

				if (idat != iter->second->data_name_list.end())
				{
					if (print_ascii || print_legacy)
					{
						(*pout) << ' ' << *idat << dots.substr(idat->length());
						(*pout).width(7);
						if (filesToPrint != NULL && !excludeFiles)
							(*pout) << (*idatc).second;
						else
							(*pout) << (*idatc).first;
					}
					if (print_csv)
					{
						(*pout_csv) << *idat << ",";
						if (filesToPrint != NULL && !excludeFiles)
							(*pout_csv) << (*idatc).second << ",";
						else
							(*pout_csv) << (*idatc).first << ",";
					}
					idat++;
					idatc++;
				}
				else
				{
					if (print_ascii || print_legacy)
						(*pout) << "                                ";
					if (print_csv)
						(*pout_csv) << ",,";
				}
				if (print_ascii || print_legacy)
					(*pout) << "     ";

				if (iexe != iter->second->exec_name_list.end())
				{
					if (print_ascii || print_legacy)
					{
						(*pout) << ' ' << *iexe << dots.substr(iexe->length());
						(*pout).width(7);
						if (filesToPrint != NULL && !excludeFiles)
							(*pout) << (*iexec).second;
						else
							(*pout) << (*iexec).first;
					}
					if (print_csv)
					{
						(*pout_csv) << *iexe << ",";
						if (filesToPrint != NULL && !excludeFiles)
							(*pout_csv) << (*iexec).second;
						else
							(*pout_csv) << (*iexec).first;
					}
					iexe++;
					iexec++;
				}
				else
				{
					if (print_ascii || print_legacy)
						(*pout) << "                                ";
				}
				if (print_ascii || print_legacy)
					(*pout) << endl;
				if (print_csv)
					(*pout_csv) << endl;
			}
		}
	}

	// close all files
	for (map<int, CCodeCounter*>::iterator iter=CounterForEachLanguage.begin(); iter!=CounterForEachLanguage.end(); iter++)
		iter->second->CloseOutputStream();

	CloseTotalOutputStream();

	// print out language count summary
	if (!PrintCountSummary(total, webtotal, useListA, outputFileNamePrePend))
		return 0;

	return 1;
}

/*!
* Retrieves the output summary file stream.
* Opens a new stream if it has not been opened already.
*
* \param outputFileNamePrePend name to prepend to the output file
* \param csvOutput CSV file stream? (otherwise ASCII text file)
*
* \return output summary file stream
*/
ofstream* MainObject::GetOutputSummaryStream(const string &outputFileNamePrePend, bool csvOutput)
{
	if (csvOutput)
	{
		if (!output_summary_csv.is_open())
		{
			string fname = outputFileNamePrePend + OUTPUT_FILE_SUM_CSV;
			output_summary_csv.open(fname.c_str(), ofstream::out);

			if (!output_summary_csv.is_open()) return NULL;

			CUtil::PrintFileHeader(output_summary_csv, "LANGUAGE COUNT SUMMARY", cmdLine);
		}
		return &output_summary_csv;
	}
	else
	{
		if (!output_summary.is_open())
		{
			string fname = outputFileNamePrePend + OUTPUT_FILE_SUM;
			output_summary.open(fname.c_str(), ofstream::out);

			if (!output_summary.is_open()) return NULL;

			CUtil::PrintFileHeader(output_summary, "LANGUAGE COUNT SUMMARY", cmdLine);
		}
		return &output_summary;
	}
}

/*!
* Closes the output summary file stream.
*/
void MainObject::CloseOutputSummaryStream()
{
	if (output_summary.is_open())
		output_summary.close();
	if (output_summary_csv.is_open())
		output_summary_csv.close();
}

/*!
* Prints the language counting summary for a set of files.
*
* \param total map of count totals
* \param webtotal map of web language count totals
* \param useListA use file list A? (otherwise use list B)
* \param outputFileNamePrePend name to prepend to the output file
*
* \return method status
*/
int MainObject::PrintCountSummary(TotalValueMap &total, WebTotalValueMap &webtotal,
	bool useListA, const string &outputFileNamePrePend)
{
	ofstream *pout;
	ofstream *pout_csv;
	unsigned int class_type;
	WebType webType;
	size_t i;
	unsigned int fCnt, pCnt, lCnt, rCnt, fTot, pTot, lTot;

	if (print_ascii || print_legacy)
	{
		pout = GetOutputSummaryStream(outDir + outputFileNamePrePend);
		if (pout == NULL)
		{
			string err = "Error: Failed to open language count summary output file (";
			err += outputFileNamePrePend + OUTPUT_FILE_SUM;
			err += "). Operation aborted.";
			cout << err << endl;
			CUtil::AddError(err);
			return 0;
		}

		(*pout) << "Language                      |   Number   |  Physical  |   Logical" << endl;
		(*pout) << "Name                          |  of Files  |    SLOC    |    SLOC" << endl;
		(*pout) << "------------------------------+------------+------------+-------------" << endl;

		rCnt = fTot = pTot = lTot = 0;
		for (map<int, CCodeCounter*>::iterator itso = ++CounterForEachLanguage.begin(); itso != CounterForEachLanguage.end(); itso++)
		{
			class_type = itso->second->classtype;

			if (itso->second->file_extension.size() > 0)
			{
				for (i = 0; i < itso->second->file_extension.size(); i++)
				{
					if (itso->second->file_extension[i].find(".*") == 0)
					{
						class_type = WEB;
						break;
					}
				}
				if (class_type == WEB)
					continue;

				fCnt = total[class_type].num_of_file;
				if (fCnt > 0)
				{
					pCnt = total[class_type].phy_direct + total[class_type].phy_decl + total[class_type].phy_instr;
					lCnt = total[class_type].log_direct + total[class_type].log_decl + total[class_type].log_instr;
					fTot += fCnt;
					pTot += pCnt;
					lTot += lCnt;

					(*pout).setf(ofstream::left);
					(*pout).width(30);
					(*pout) << itso->second->language_name;
					(*pout).unsetf(ofstream::left);
					(*pout) << "|";
					(*pout).setf(ofstream::right);
					(*pout).width(10);
					(*pout) << fCnt;
					(*pout) << "  |";
					(*pout).width(10);
					(*pout) << pCnt;
					(*pout) << "  |";
					(*pout).width(10);
					(*pout) << lCnt << endl;
					(*pout).unsetf(ofstream::right);

					rCnt++;
				}
			}
		}
		for (WebTotalValueMap::iterator itsw = webtotal.begin(); itsw != webtotal.end(); itsw++)
		{
			webType = itsw->first;
			fCnt = webtotal[webType].num_of_file;
			if (fCnt > 0)
			{
				pCnt = 0;
				lCnt = 0;
				for (i = 0; i < 6; i++)
				{
					pCnt += webtotal[webType].phy_decl[i] + webtotal[webType].phy_instr[i];
					lCnt += webtotal[webType].log_decl[i] + webtotal[webType].log_instr[i];
				}
				fTot += fCnt;
				pTot += pCnt;
				lTot += lCnt;

				(*pout).setf(ofstream::left);
				(*pout).width(30);
				(*pout) << CWebCounter::GetWebLangName(webType);
				(*pout).unsetf(ofstream::left);
				(*pout) << "|";
				(*pout).setf(ofstream::right);
				(*pout).width(10);
				(*pout) << fCnt;
				(*pout) << "  |";
				(*pout).width(10);
				(*pout) << pCnt;
				(*pout) << "  |";
				(*pout).width(10);
				(*pout) << lCnt << endl;
				(*pout).unsetf(ofstream::right);

				rCnt++;
			}
		}

		if (rCnt > 0)
		{
			(*pout) << "------------------------------+------------+------------+-------------" << endl;
			(*pout).setf(ofstream::left);
			(*pout).width(30);
			(*pout) << "Total";
			(*pout).unsetf(ofstream::left);
			(*pout) << "|";
			(*pout).setf(ofstream::right);
			(*pout).width(10);
			(*pout) << fTot;
			(*pout) << "  |";
			(*pout).width(10);
			(*pout) << pTot;
			(*pout) << "  |";
			(*pout).width(10);
			(*pout) << lTot << endl;
			(*pout).unsetf(ofstream::right);
		}
	}
	if (print_csv)
	{
		pout_csv = GetOutputSummaryStream(outDir + outputFileNamePrePend, true);
		if (pout_csv == NULL)
		{
			string err = "Error: Failed to open language count summary output file (";
			err += outputFileNamePrePend + OUTPUT_FILE_SUM_CSV;
			err += "). Operation aborted.";
			cout << err << endl;
			CUtil::AddError(err);
			return 0;
		}

		(*pout_csv) << "Language,Number,Physical,Logical" << endl;
		(*pout_csv) << "Name,of Files,SLOC,SLOC" << endl;

		rCnt = fTot = pTot = lTot = 0;
		for (map<int, CCodeCounter*>::iterator itso = ++CounterForEachLanguage.begin(); itso != CounterForEachLanguage.end(); itso++)
		{
			class_type = itso->second->classtype;

			if (itso->second->file_extension.size() > 0)
			{
				for (i = 0; i < itso->second->file_extension.size(); i++)
				{
					if (itso->second->file_extension[i].find(".*") == 0)
					{
						class_type = WEB;
						break;
					}
				}
				if (class_type == WEB)
					continue;

				fCnt = total[class_type].num_of_file;
				if (fCnt > 0)
				{
					pCnt = total[class_type].phy_direct + total[class_type].phy_decl + total[class_type].phy_instr;
					lCnt = total[class_type].log_direct + total[class_type].log_decl + total[class_type].log_instr;
					fTot += fCnt;
					pTot += pCnt;
					lTot += lCnt;

					(*pout_csv) << itso->second->language_name << "," << fCnt << "," << pCnt << "," << lCnt << endl;

					rCnt++;
				}
			}
		}
		for (WebTotalValueMap::iterator itsw = webtotal.begin(); itsw != webtotal.end(); itsw++)
		{
			webType = itsw->first;
			fCnt = webtotal[webType].num_of_file;
			if (fCnt > 0)
			{
				pCnt = 0;
				lCnt = 0;
				for (i = 0; i < 6; i++)
				{
					pCnt += webtotal[webType].phy_decl[i] + webtotal[webType].phy_instr[i];
					lCnt += webtotal[webType].log_decl[i] + webtotal[webType].log_instr[i];
				}
				fTot += fCnt;
				pTot += pCnt;
				lTot += lCnt;

				(*pout_csv) << CWebCounter::GetWebLangName(webType) << "," << fCnt << "," << pCnt << "," << lCnt << endl;

				rCnt++;
			}
		}

		if (rCnt > 0)
			(*pout_csv) << endl << "Total," << fTot << "," << pTot << "," << lTot << endl;
	}
	CloseOutputSummaryStream();

	return 1;
}

/*!
* Prints the complexity results.
*
* \param useListA use file list A? (otherwise use list B)
* \param outputFileNamePrePend name to prepend to the output file
* \param printDuplicates print duplicate files? (otherwise print unique files)
*
* \return method status
*/
int MainObject::PrintComplexityResults(bool useListA, const string &outputFileNamePrePend, bool printDuplicates) 
{
	if (useListA)
	{
		if (printDuplicates && duplicateFilesInA2.size() < 1)
			return 1;
	}
	else
	{
		if (printDuplicates && duplicateFilesInB2.size() < 1)
			return 1;
	}

	size_t i;
	string dots = "......................";
	string COL_SP = "                           ";
	string SP_BW_COL = "    ";
	string nestedLoops = "";
	SourceFileList* mySourceFile = (useListA) ? &SourceFileA : &SourceFileB;
	size_t loopCol = 0;

	StringVector::iterator imath;		// math
	StringVector::iterator itrig;		// trig
	StringVector::iterator ilog;		// logarithmic
	StringVector::iterator icalc;		// calculation
	StringVector::iterator icond;		// conditionals
	StringVector::iterator ilogic;		// logical
	StringVector::iterator ipreproc;	// preprocessor
	StringVector::iterator iassign;		// assign
	StringVector::iterator ipointer;	// pointers
	UIntPairVector::iterator imathc;
	UIntPairVector::iterator itrigc;
	UIntPairVector::iterator ilogc;
	UIntPairVector::iterator icalcc;
	UIntPairVector::iterator icondc;
	UIntPairVector::iterator ilogicc;
	UIntPairVector::iterator ipreprocc;
	UIntPairVector::iterator iassignc;
	UIntPairVector::iterator ipointerc;
	results cmplxTotal;

	cmplxTotal.cmplx_math_lines = 0;
	cmplxTotal.cmplx_trig_lines = 0;
	cmplxTotal.cmplx_logarithm_lines = 0;
	cmplxTotal.cmplx_calc_lines = 0;
	cmplxTotal.cmplx_cond_lines = 0;
	cmplxTotal.cmplx_logic_lines = 0;
	cmplxTotal.cmplx_preproc_lines = 0;
	cmplxTotal.cmplx_assign_lines = 0;
	cmplxTotal.cmplx_pointer_lines = 0;

	// check for counts
	for (SourceFileList::iterator itt2 = mySourceFile->begin(); itt2 != mySourceFile->end(); itt2++)
	{
		if ((!printDuplicates && !itt2->second.duplicate) || (printDuplicates && itt2->second.duplicate))
		{
			if (itt2->second.cmplx_nestloop_count.size() > loopCol)
				loopCol = itt2->second.cmplx_nestloop_count.size();
		}
	}

	// open file and print headers
	ofstream cplxOutputFile, cplxOutputFileCSV;
	if (print_ascii || print_legacy)
	{
		string cplxOutputFileName = outDir + outputFileNamePrePend;
		cplxOutputFileName.append(OUTPUT_FILE_CPLX);
		cplxOutputFile.open(cplxOutputFileName.c_str(), ofstream::out);
		if (!cplxOutputFile.is_open())
		{
			string err = "Error: Unable to create file (";
			err += cplxOutputFileName;
			err += "). Operation aborted";
			cout << endl << err << endl;
			CUtil::AddError(err);
			return 0;
		}

		CUtil::PrintFileHeader(cplxOutputFile, "COMPLEXITY COUNT RESULTS", cmdLine);

		if (print_legacy)
		{
			cplxOutputFile << "#| S | Cond  |Logical| Trig  |  Log  |Preproc| Math  |Assign |  Ptr  | Nesting levels              | Filename" << endl;
			cplxOutputFile << "-------------------------------------------------------------------------------------------------------------------------------------" << endl;
		}
		else
		{
			cplxOutputFile << " Math    Trig  Logarithm  Calculation     Cond.   Logical   Preproc.  Assignment   Pointer   ";
			for (i = 1; i <= loopCol; i++)
			{
				cplxOutputFile << "L" << i << "-Loops  ";
				if (i < 10)
					cplxOutputFile << " ";
			}
			cplxOutputFile << "|   File Name" << endl;
			cplxOutputFile << " --------------------------------------------------------------------------------------------";
			for (i = 1; i <= loopCol; i++)
				cplxOutputFile << "-----------";
			cplxOutputFile << "+-----------------------------------" << endl;
		}
	}
	if (print_csv)
	{
		string cplxOutputFileNameCSV = outDir + outputFileNamePrePend;
		cplxOutputFileNameCSV.append(OUTPUT_FILE_CPLX_CSV);
		cplxOutputFileCSV.open(cplxOutputFileNameCSV.c_str(), ofstream::out);
		if (!cplxOutputFileCSV.is_open())
		{
			string err = "Error: Unable to create file (";
			err += cplxOutputFileNameCSV;
			err += "). Operation aborted";
			cout << endl << err << endl;
			CUtil::AddError(err);
			return 0;
		}

		CUtil::PrintFileHeader(cplxOutputFileCSV, "COMPLEXITY COUNT RESULTS", cmdLine);

		cplxOutputFileCSV << "Math,Trigonometric,Logarithmic,Calculations,Conditionals,Logical,Preprocessor,Assignment,Pointer";
		for (i = 1; i <= loopCol; i++)
			cplxOutputFileCSV << ",L" << i << "-Loops";
		cplxOutputFileCSV << ",File Name" << endl;
	}

	// print counts for each file
	for (SourceFileList::iterator itt2 = mySourceFile->begin(); itt2 != mySourceFile->end(); itt2++)
	{
		if (itt2->second.file_name.find(EMBEDDED_FILE_PREFIX) != string::npos) continue;

		if ((!printDuplicates && !itt2->second.duplicate) || (printDuplicates && itt2->second.duplicate))
		{
			// do not print temporary files, but sum all of their counts
			SourceFileList::iterator it = itt2;
			for (it++; it != mySourceFile->end(); it++)
			{
				if (it->second.file_name.find(EMBEDDED_FILE_PREFIX) == string::npos) break;
				itt2->second.cmplx_math_lines += it->second.cmplx_math_lines;
				itt2->second.cmplx_trig_lines += it->second.cmplx_trig_lines;
				itt2->second.cmplx_logarithm_lines += it->second.cmplx_logarithm_lines;
				itt2->second.cmplx_calc_lines += it->second.cmplx_calc_lines;
				itt2->second.cmplx_cond_lines += it->second.cmplx_cond_lines;
				itt2->second.cmplx_logic_lines += it->second.cmplx_logic_lines;
				itt2->second.cmplx_preproc_lines += it->second.cmplx_preproc_lines;
				itt2->second.cmplx_assign_lines += it->second.cmplx_assign_lines;
				itt2->second.cmplx_pointer_lines += it->second.cmplx_pointer_lines;

				for (i = 0; i < it->second.cmplx_nestloop_count.size(); i++)
				{
					if (itt2->second.cmplx_nestloop_count.size() < i + 1)
						itt2->second.cmplx_nestloop_count.push_back(it->second.cmplx_nestloop_count[i]);
					else
						itt2->second.cmplx_nestloop_count[i] += it->second.cmplx_nestloop_count[i];
				}
			}

			if (print_legacy)
			{
				if (useListA)
					cplxOutputFile << "A ";
				else
					cplxOutputFile << "B ";
				if (printDuplicates)
					cplxOutputFile << " X ";
				else if (SourceFileB.size() > 0 && !itt2->second.matched)
				{
					if (useListA)
						cplxOutputFile << " D ";
					else
						cplxOutputFile << " N ";
				}
				else
					cplxOutputFile << " C ";
				cplxOutputFile.width(8);	cplxOutputFile << itt2->second.cmplx_cond_lines;
				cplxOutputFile.width(8);	cplxOutputFile << itt2->second.cmplx_logic_lines;
				cplxOutputFile.width(8);	cplxOutputFile << itt2->second.cmplx_trig_lines;
				cplxOutputFile.width(8);	cplxOutputFile << itt2->second.cmplx_logarithm_lines;
				cplxOutputFile.width(8);	cplxOutputFile << itt2->second.cmplx_preproc_lines;
				cplxOutputFile.width(8);	cplxOutputFile << itt2->second.cmplx_math_lines + itt2->second.cmplx_calc_lines;
				cplxOutputFile.width(8);	cplxOutputFile << itt2->second.cmplx_assign_lines;
				cplxOutputFile.width(8);	cplxOutputFile << itt2->second.cmplx_pointer_lines;

				nestedLoops = "";
				if (itt2->second.cmplx_nestloop_count.size() > 0)
				{
					std::stringstream ss;
					ss << itt2->second.cmplx_nestloop_count[0];
					for (size_t i = 1; i < itt2->second.cmplx_nestloop_count.size(); i++)
						ss << "," << itt2->second.cmplx_nestloop_count[i];
					nestedLoops = ss.str();
				}
				cplxOutputFile << "  ";
				cplxOutputFile.width(28);		cplxOutputFile.setf(ios::left);
				cplxOutputFile << nestedLoops;	cplxOutputFile.unsetf(ios::left);
				cplxOutputFile << "  ";
				cplxOutputFile << itt2->second.file_name << endl;
			}
			else if (print_ascii)
			{
				cplxOutputFile.width(5);	cplxOutputFile << itt2->second.cmplx_math_lines;
				cplxOutputFile.width(8);	cplxOutputFile << itt2->second.cmplx_trig_lines;
				cplxOutputFile.width(11);	cplxOutputFile << itt2->second.cmplx_logarithm_lines;
				cplxOutputFile.width(11);	cplxOutputFile << itt2->second.cmplx_calc_lines;
				cplxOutputFile.width(11);	cplxOutputFile << itt2->second.cmplx_cond_lines;
				cplxOutputFile.width(11);	cplxOutputFile << itt2->second.cmplx_logic_lines;
				cplxOutputFile.width(11);	cplxOutputFile << itt2->second.cmplx_preproc_lines;
				cplxOutputFile.width(11);	cplxOutputFile << itt2->second.cmplx_assign_lines;
				cplxOutputFile.width(11);	cplxOutputFile << itt2->second.cmplx_pointer_lines;
				for (i = 0; i < itt2->second.cmplx_nestloop_count.size(); i++)
				{
					cplxOutputFile.width(11);
					cplxOutputFile << itt2->second.cmplx_nestloop_count[i];
				}
				for (i = itt2->second.cmplx_nestloop_count.size(); i < loopCol; i++)
					cplxOutputFile << "          0";
				cplxOutputFile << "   |   " << itt2->second.file_name << endl;
			}
			if (print_csv)
			{
				cplxOutputFileCSV << itt2->second.cmplx_math_lines << ",";
				cplxOutputFileCSV << itt2->second.cmplx_trig_lines << ",";
				cplxOutputFileCSV << itt2->second.cmplx_logarithm_lines << ",";
				cplxOutputFileCSV << itt2->second.cmplx_calc_lines << ",";
				cplxOutputFileCSV << itt2->second.cmplx_cond_lines << ",";
				cplxOutputFileCSV << itt2->second.cmplx_logic_lines << ",";
				cplxOutputFileCSV << itt2->second.cmplx_preproc_lines << ",";
				cplxOutputFileCSV << itt2->second.cmplx_assign_lines << ",";
				cplxOutputFileCSV << itt2->second.cmplx_pointer_lines << ",";
				for (i = 0; i < itt2->second.cmplx_nestloop_count.size(); i++)
					cplxOutputFileCSV << itt2->second.cmplx_nestloop_count[i] << ",";
				for (i = itt2->second.cmplx_nestloop_count.size(); i < loopCol; i++)
					cplxOutputFileCSV << "0,";
				cplxOutputFileCSV << itt2->second.file_name << endl;
			}

			cmplxTotal.cmplx_math_lines += itt2->second.cmplx_math_lines;
			cmplxTotal.cmplx_trig_lines += itt2->second.cmplx_trig_lines;
			cmplxTotal.cmplx_logarithm_lines += itt2->second.cmplx_logarithm_lines;
			cmplxTotal.cmplx_calc_lines += itt2->second.cmplx_calc_lines;
			cmplxTotal.cmplx_cond_lines += itt2->second.cmplx_cond_lines;
			cmplxTotal.cmplx_logic_lines += itt2->second.cmplx_logic_lines;
			cmplxTotal.cmplx_preproc_lines += itt2->second.cmplx_preproc_lines;
			cmplxTotal.cmplx_assign_lines += itt2->second.cmplx_assign_lines;
			cmplxTotal.cmplx_pointer_lines += itt2->second.cmplx_pointer_lines;

			itt2 = --it;
		}
	}

	if (print_legacy)
	{
		cplxOutputFile << endl << "Note: # represents the baseline; S represents N=New, D=Deleted, C=Common, X=Duplicate" << endl;
	}
	else if (print_ascii)
	{
		cplxOutputFile << endl << endl << " -----------------------------------------------< totals >-----------------------------------------------------------------------";
		for (i = 1; i <= loopCol; i++)
			cplxOutputFile << "-----------";
		cplxOutputFile << endl << endl;

		cplxOutputFile.width(5);	cplxOutputFile << cmplxTotal.cmplx_math_lines;
		cplxOutputFile.width(8);	cplxOutputFile << cmplxTotal.cmplx_trig_lines;
		cplxOutputFile.width(11);	cplxOutputFile << cmplxTotal.cmplx_logarithm_lines;
		cplxOutputFile.width(11);	cplxOutputFile << cmplxTotal.cmplx_calc_lines;
		cplxOutputFile.width(11);	cplxOutputFile << cmplxTotal.cmplx_cond_lines;
		cplxOutputFile.width(11);	cplxOutputFile << cmplxTotal.cmplx_logic_lines;
		cplxOutputFile.width(11);	cplxOutputFile << cmplxTotal.cmplx_preproc_lines;
		cplxOutputFile.width(11);	cplxOutputFile << cmplxTotal.cmplx_assign_lines;
		cplxOutputFile.width(11);	cplxOutputFile << cmplxTotal.cmplx_pointer_lines << endl << endl;
	}
	if (print_csv)
	{
		cplxOutputFileCSV << endl << "Totals" << endl;

		cplxOutputFileCSV << cmplxTotal.cmplx_math_lines << ",";
		cplxOutputFileCSV << cmplxTotal.cmplx_trig_lines << ",";
		cplxOutputFileCSV << cmplxTotal.cmplx_logarithm_lines << ",";
		cplxOutputFileCSV << cmplxTotal.cmplx_calc_lines << ",";
		cplxOutputFileCSV << cmplxTotal.cmplx_cond_lines << ",";
		cplxOutputFileCSV << cmplxTotal.cmplx_logic_lines << ",";
		cplxOutputFileCSV << cmplxTotal.cmplx_preproc_lines << ",";
		cplxOutputFileCSV << cmplxTotal.cmplx_assign_lines << ",";
		cplxOutputFileCSV << cmplxTotal.cmplx_pointer_lines << endl;
	}

	for (map<int, CCodeCounter*>::iterator iter = ++CounterForEachLanguage.begin(); iter != CounterForEachLanguage.end(); iter++)
	{
		// only print for languages found in files
		if (printDuplicates)
		{
			if (iter->second->counted_dupFiles < 1)
				continue;
		}
		else
		{
			if (iter->second->counted_files < 1)
				continue;
		}

		imath = iter->second->math_func_list.begin();
		itrig = iter->second->trig_func_list.begin();
		ilog = iter->second->log_func_list.begin();
		icalc = iter->second->cmplx_calc_list.begin();
		icond = iter->second->cmplx_cond_list.begin();
		ilogic = iter->second->cmplx_logic_list.begin();
		ipreproc = iter->second->cmplx_preproc_list.begin();
		iassign = iter->second->cmplx_assign_list.begin();
		ipointer = iter->second->cmplx_pointer_list.begin();

		imathc = iter->second->math_func_count.begin();
		itrigc = iter->second->trig_func_count.begin();
		ilogc = iter->second->log_func_count.begin();
		icalcc = iter->second->cmplx_calc_count.begin();
		icondc = iter->second->cmplx_cond_count.begin();
		ilogicc = iter->second->cmplx_logic_count.begin();
		ipreprocc = iter->second->cmplx_preproc_count.begin();
		iassignc = iter->second->cmplx_assign_count.begin();
		ipointerc = iter->second->cmplx_pointer_count.begin();

		if ( (imathc != iter->second->math_func_count.end()) ||
			 (itrigc != iter->second->trig_func_count.end()) ||
			 (ilogc  != iter->second->log_func_count.end()) ||
			 (icalcc != iter->second->cmplx_calc_count.end()) ||
			 (icondc != iter->second->cmplx_cond_count.end()) ||
			 (ilogicc != iter->second->cmplx_logic_count.end()) ||
			 (ipreprocc != iter->second->cmplx_preproc_count.end()) ||
			 (iassignc != iter->second->cmplx_assign_count.end()) ||
			 (ipointerc != iter->second->cmplx_pointer_count.end()) )
		{
			if (print_ascii)
			{
				cplxOutputFile << endl;
				CUtil::PrintFileHeaderLine(cplxOutputFile, "TOTAL OCCURRENCES OF " + iter->second->language_name + " COMPLEXITY COUNTS");
				cplxOutputFile << "-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------" << endl;
				cplxOutputFile << "    Math Functions                 Trigonometric                  Logarithmic                    Calculations                   Conditionals                   Logical                        Preprocessor                   Assignment                     Pointer" << endl;
				cplxOutputFile.setf(ios::right);
			}
			if (print_csv)
			{
				cplxOutputFileCSV << endl;
				CUtil::PrintFileHeaderLine(cplxOutputFileCSV, "TOTAL OCCURRENCES OF " + iter->second->language_name + " COMPLEXITY COUNTS");
				cplxOutputFileCSV << "Math Functions,,Trigonometric,,Logarithmic,,Calculations,,Conditionals,,Logical,,Preprocessor,,Assignment,,Pointer" << endl;
			}
		}

		while (	(imathc != iter->second->math_func_count.end()) ||
				(itrigc != iter->second->trig_func_count.end()) ||
				(ilogc  != iter->second->log_func_count.end()) ||
				(icalcc != iter->second->cmplx_calc_count.end()) ||
				(icondc != iter->second->cmplx_cond_count.end()) ||
				(ilogicc != iter->second->cmplx_logic_count.end()) ||
				(ipreprocc != iter->second->cmplx_preproc_count.end()) ||
				(iassignc != iter->second->cmplx_assign_count.end()) ||
				(ipointerc != iter->second->cmplx_pointer_count.end()) )
		{
			if (imath != iter->second->math_func_list.end())  // imath
			{
				if (print_ascii)
				{
					cplxOutputFile << ' ' << *imath << dots.substr(imath->length());
					cplxOutputFile.width(4);
					if (printDuplicates)
						cplxOutputFile << (*imathc).second;
					else
						cplxOutputFile << (*imathc).first;
				}
				if (print_csv)
				{
					cplxOutputFileCSV << *imath << ",";
					if (printDuplicates)
						cplxOutputFileCSV << (*imathc).second;
					else
						cplxOutputFileCSV << (*imathc).first;
				}
				imath++;
				imathc++;
			}
			else
			{
				if (print_ascii)
					cplxOutputFile << COL_SP;
				if (print_csv)
					cplxOutputFileCSV << ",";
			}
			if (print_ascii)
				cplxOutputFile << SP_BW_COL;

			if (itrig != iter->second->trig_func_list.end())  // itrig
			{
				if (print_ascii)
				{
					cplxOutputFile << ' ' << *itrig << dots.substr(itrig->length());
					cplxOutputFile.width(4);
					if (printDuplicates)
						cplxOutputFile << (*itrigc).second;
					else
						cplxOutputFile << (*itrigc).first;
				}
				if (print_csv)
				{
					cplxOutputFileCSV << "," << *itrig << ",";
					if (printDuplicates)
						cplxOutputFileCSV << (*itrigc).second;
					else
						cplxOutputFileCSV << (*itrigc).first;
				}
				itrig++;
				itrigc++;
			}
			else
			{
				if (print_ascii)
					cplxOutputFile << COL_SP;
				if (print_csv)
					cplxOutputFileCSV << ",,";
			}
			if (print_ascii)
				cplxOutputFile << SP_BW_COL;

			if (ilog != iter->second->log_func_list.end())   // ilog
			{
				if (print_ascii)
				{
					cplxOutputFile << ' ' << *ilog << dots.substr(ilog->length());
					cplxOutputFile.width(4);
					if (printDuplicates)
						cplxOutputFile << (*ilogc).second;
					else
						cplxOutputFile << (*ilogc).first;
				}
				if (print_csv)
				{
					cplxOutputFileCSV << "," << *ilog << ",";
					if (printDuplicates)
						cplxOutputFileCSV << (*ilogc).second;
					else
						cplxOutputFileCSV << (*ilogc).first;
				}
				ilog++;
				ilogc++;
			}
			else
			{
				if (print_ascii)
					cplxOutputFile << COL_SP;
				if (print_csv)
					cplxOutputFileCSV << ",,";
			}
			if (print_ascii)
				cplxOutputFile << SP_BW_COL;

			if (icalc != iter->second->cmplx_calc_list.end())   // icalc
			{
				if (print_ascii)
				{
					cplxOutputFile << ' ' << *icalc << dots.substr(icalc->length());
					cplxOutputFile.width(4);
					if (printDuplicates)
						cplxOutputFile << (*icalcc).second;
					else
						cplxOutputFile << (*icalcc).first;
				}
				if (print_csv)
				{
					cplxOutputFileCSV << "," << *icalc << ",";
					if (printDuplicates)
						cplxOutputFileCSV << (*icalcc).second;
					else
						cplxOutputFileCSV << (*icalcc).first;
				}
				icalc++;
				icalcc++;
			}
			else
			{
				if (print_ascii)
					cplxOutputFile << COL_SP;
				if (print_csv)
					cplxOutputFileCSV << ",,";
			}
			if (print_ascii)
				cplxOutputFile << SP_BW_COL;

			if (icond != iter->second->cmplx_cond_list.end())   // icond
			{
				if (print_ascii)
				{
					cplxOutputFile << ' ' << *icond << dots.substr(icond->length());
					cplxOutputFile.width(4);
					if (printDuplicates)
						cplxOutputFile << (*icondc).second;
					else
						cplxOutputFile << (*icondc).first;
				}
				if (print_csv)
				{
					cplxOutputFileCSV << "," << *icond << ",";
					if (printDuplicates)
						cplxOutputFileCSV << (*icondc).second;
					else
						cplxOutputFileCSV << (*icondc).first;
				}
				icond++;
				icondc++;
			}
			else
			{
				if (print_ascii)
					cplxOutputFile << COL_SP;
				if (print_csv)
					cplxOutputFileCSV << ",,";
			}
			if (print_ascii)
				cplxOutputFile << SP_BW_COL;

			if (ilogic != iter->second->cmplx_logic_list.end())   // ilogic
			{
				if (print_ascii)
				{
					cplxOutputFile << ' ' << *ilogic << dots.substr(ilogic->length());
					cplxOutputFile.width(4);
					if (printDuplicates)
						cplxOutputFile << (*ilogicc).second;
					else
						cplxOutputFile << (*ilogicc).first;
				}
				if (print_csv)
				{
					cplxOutputFileCSV << "," << *ilogic << ",";
					if (printDuplicates)
						cplxOutputFileCSV << (*ilogicc).second;
					else
						cplxOutputFileCSV << (*ilogicc).first;
				}
				ilogic++;
				ilogicc++;
			}
			else
			{
				if (print_ascii)
					cplxOutputFile << COL_SP;
				if (print_csv)
					cplxOutputFileCSV << ",,";
			}
			if (print_ascii)
				cplxOutputFile << SP_BW_COL;

			if (ipreproc != iter->second->cmplx_preproc_list.end())   // ipreproc
			{
				if (print_ascii)
				{
					cplxOutputFile << ' ' << *ipreproc << dots.substr(ipreproc->length());
					cplxOutputFile.width(4);
					if (printDuplicates)
						cplxOutputFile << (*ipreprocc).second;
					else
						cplxOutputFile << (*ipreprocc).first;
				}
				if (print_csv)
				{
					cplxOutputFileCSV << "," << *ipreproc << ",";
					if (printDuplicates)
						cplxOutputFileCSV << (*ipreprocc).second;
					else
						cplxOutputFileCSV << (*ipreprocc).first;
				}
				ipreproc++;
				ipreprocc++;
			}
			else
			{
				if (print_ascii)
					cplxOutputFile << COL_SP;
				if (print_csv)
					cplxOutputFileCSV << ",,";
			}
			if (print_ascii)
				cplxOutputFile << SP_BW_COL;

			if (iassign != iter->second->cmplx_assign_list.end())   // ipreproc
			{
				if (print_ascii)
				{
					cplxOutputFile << ' ' << *iassign << dots.substr(iassign->length());
					cplxOutputFile.width(4);
					if (printDuplicates)
						cplxOutputFile << (*iassignc).second;
					else
						cplxOutputFile << (*iassignc).first;
				}
				if (print_csv)
				{
					cplxOutputFileCSV << "," << *iassign << ",";
					if (printDuplicates)
						cplxOutputFileCSV << (*iassignc).second;
					else
						cplxOutputFileCSV << (*iassignc).first;
				}
				iassign++;
				iassignc++;
			}
			else
			{
				if (print_ascii)
					cplxOutputFile << COL_SP;
				if (print_csv)
					cplxOutputFileCSV << ",,";
			}
			if (print_ascii)
				cplxOutputFile << SP_BW_COL;

			if (ipointer != iter->second->cmplx_pointer_list.end())   // RST Pointers
			{
				if (print_ascii)
				{
					cplxOutputFile << ' ' << *ipointer << dots.substr(ipointer->length());
					cplxOutputFile.width(4);
					if (printDuplicates)
						cplxOutputFile << (*ipointerc).second;
					else
						cplxOutputFile << (*ipointerc).first;
				}
				if (print_csv)
				{
					cplxOutputFileCSV << "," << *ipointer << ",";
					if (printDuplicates)
						cplxOutputFileCSV << (*ipointerc).second;
					else
						cplxOutputFileCSV << (*ipointerc).first;
				}
				ipointer++;
				ipointerc++;
			}
			else
			{
				if (print_ascii)
					cplxOutputFile << COL_SP;
			}
			if (print_ascii)
				cplxOutputFile << endl;
			if (print_csv)
				cplxOutputFileCSV << endl;
		}
	}
	if (print_ascii || print_legacy)
		cplxOutputFile.close();
	if (print_csv)
		cplxOutputFileCSV.close();

	// print cyclomatic complexity if requested
	if (print_cyclomatic_cmplx)
		PrintCyclomaticComplexity(useListA, outputFileNamePrePend, printDuplicates);

	return 1;
}

/*!
* Prints the cyclomatic complexity results.
*
* \param useListA use file list A? (otherwise use list B)
* \param outputFileNamePrePend name to prepend to the output file
* \param printDuplicates print duplicate files? (otherwise print unique files)
*
* \return method status
*/
int MainObject::PrintCyclomaticComplexity(bool useListA, const string &outputFileNamePrePend, bool printDuplicates) 
{
	if (useListA)
	{
		if (printDuplicates && duplicateFilesInA2.size() < 1)
			return 1;
	}
	else
	{
		if (printDuplicates && duplicateFilesInB2.size() < 1)
			return 1;
	}

	SourceFileList* mySourceFile = (useListA) ? &SourceFileA : &SourceFileB;
	bool found = false;

	// check for counts
	for (SourceFileList::iterator itt2 = mySourceFile->begin(); itt2 != mySourceFile->end(); itt2++)
	{
		if ((!printDuplicates && !itt2->second.duplicate) || (printDuplicates && itt2->second.duplicate))
		{
			if (itt2->second.cmplx_cycfunct_count.size() > 0)
			{
				found = true;
				break;
			}
		}
	}
	if (!found)
		return 1;

	// open file and print headers
	ofstream cycCplxOutputFile, cycCplxOutputFileCSV;
	if (print_ascii || print_legacy)
	{
		string cycCplxOutputFileName = outDir + outputFileNamePrePend;
		cycCplxOutputFileName.append(OUTPUT_FILE_CYC_CPLX);
		cycCplxOutputFile.open(cycCplxOutputFileName.c_str(), ofstream::out);
		if (!cycCplxOutputFile.is_open())
		{
			string err = "Error: Unable to create file (";
			err += cycCplxOutputFileName;
			err += "). Operation aborted";
			cout << endl << err << endl;
			CUtil::AddError(err);
			return 0;
		}

		CUtil::PrintFileHeader(cycCplxOutputFile, "CYCLOMATIC COMPLEXITY RESULTS", cmdLine);

		cycCplxOutputFile << "Function                                          Cyclomatic   Risk        |   File" << endl;
		cycCplxOutputFile << "Name                                              Complexity               |   Name" << endl;
		cycCplxOutputFile << "---------------------------------------------------------------------------+-----------------------" << endl;
	}
	if (print_csv)
	{
		string cycCplxOutputFileNameCSV = outDir + outputFileNamePrePend;
		cycCplxOutputFileNameCSV.append(OUTPUT_FILE_CYC_CPLX_CSV);
		cycCplxOutputFileCSV.open(cycCplxOutputFileNameCSV.c_str(), ofstream::out);
		if (!cycCplxOutputFileCSV.is_open())
		{
			string err = "Error: Unable to create file (";
			err += cycCplxOutputFileNameCSV;
			err += "). Operation aborted";
			cout << endl << err << endl;
			CUtil::AddError(err);
			return 0;
		}

		CUtil::PrintFileHeader(cycCplxOutputFileCSV, "CYCLOMATIC COMPLEXITY RESULTS", cmdLine);
		cycCplxOutputFileCSV << "Function Name,Cyclomatic Complexity,Risk,File Name" << endl;
	}

	// print cyclomatic complexity for each file
	for (SourceFileList::iterator itt2 = mySourceFile->begin(); itt2 != mySourceFile->end(); itt2++)
	{
		if (itt2->second.file_name.find(EMBEDDED_FILE_PREFIX) != string::npos) continue;

		if ((!printDuplicates && !itt2->second.duplicate) || (printDuplicates && itt2->second.duplicate))
		{
			if (print_ascii || print_legacy)
			{
				srcLineVector::iterator it;
				for (it = itt2->second.cmplx_cycfunct_count.begin(); it != itt2->second.cmplx_cycfunct_count.end(); it++)
				{
					cycCplxOutputFile.setf(ofstream::left);
					cycCplxOutputFile.width(50);
					cycCplxOutputFile << (*it).first;
					cycCplxOutputFile.setf(ofstream::right);
					cycCplxOutputFile.width(10);
					cycCplxOutputFile << (*it).second;
					cycCplxOutputFile.unsetf(ofstream::right);
					cycCplxOutputFile << "   ";
					cycCplxOutputFile.setf(ofstream::left);
					cycCplxOutputFile.width(9);
					if ((*it).second <= 10)
						cycCplxOutputFile << "Low";
					else if ((*it).second <= 20)
						cycCplxOutputFile << "Medium";
					else if ((*it).second <= 50)
						cycCplxOutputFile << "High";
					else
						cycCplxOutputFile << "Very High";
					cycCplxOutputFile.unsetf(ofstream::right);
					cycCplxOutputFile << "   |   " << itt2->second.file_name << endl;
				}
			}
			if (print_csv)
			{
				srcLineVector::iterator it;
				for (it = itt2->second.cmplx_cycfunct_count.begin(); it != itt2->second.cmplx_cycfunct_count.end(); it++)
				{
					cycCplxOutputFileCSV << (*it).first << "," << (*it).second << ",";
					if ((*it).second <= 10)
						cycCplxOutputFileCSV << "Low,";
					else if ((*it).second <= 20)
						cycCplxOutputFileCSV << "Medium,";
					else if ((*it).second <= 50)
						cycCplxOutputFileCSV << "High,";
					else
						cycCplxOutputFileCSV << "Very High,";
					cycCplxOutputFileCSV << itt2->second.file_name << endl;
				}
			}
		}
	}
	if (print_ascii || print_legacy)
		cycCplxOutputFile.close();
	if (print_csv)
		cycCplxOutputFileCSV.close();

	return 1;
}

/*!
* Prints the duplicate summary output file.
* Shows which files were duplicates, regardless of file name/path.
*
* \param useListA use file list A? (otherwise use list B)
* \param outputFileNamePrePend name to prepend to the output file
*/
void MainObject::PrintDuplicateSummary(bool useListA, const string &outputFileNamePrePend)
{
	if (useListA)
	{
		if (duplicateFilesInA2.size() < 1)
			return;
	}
	else
	{
		if (duplicateFilesInB2.size() < 1)
			return;
	}

	if (print_ascii || print_legacy)
	{
		ofstream dupFile;
		string dupFileName = outDir + outputFileNamePrePend;
		dupFileName.append(DUP_PAIRS_OUTFILE);
		dupFile.open(dupFileName.c_str(), ofstream::out);
		if (!dupFile.is_open())
		{
			string err = "Error: Failed to open duplicate file pair summary output file (";
			err += dupFileName;
			err += ")";
			cout << err << endl;
			CUtil::AddError(err);
			return;
		}

		CUtil::PrintFileHeader(dupFile, "DUPLICATE FILE PAIRS", cmdLine);
		dupFile.setf(ofstream::left);
		dupFile.width(45);
		dupFile << "Original";
		dupFile.unsetf(ofstream::left);
		dupFile.width(5);
		dupFile << "  |  ";
		dupFile.width(3);
		dupFile.setf(ofstream::left);
		dupFile.width(45);
		dupFile << "Duplicate";
		dupFile << endl;
		if (useListA)
			PrintDuplicateList(duplicateFilesInA1, duplicateFilesInA2, dupFile);
		else
			PrintDuplicateList(duplicateFilesInB1, duplicateFilesInB2, dupFile);
		dupFile.close();
	}
	if (print_csv)
	{
		ofstream dupFileCSV;
		string dupFileNameCSV = outDir + outputFileNamePrePend;
		dupFileNameCSV.append(DUP_PAIRS_OUTFILE_CSV);
		dupFileCSV.open(dupFileNameCSV.c_str(), ofstream::out);
		if (!dupFileCSV.is_open())
		{
			string err = "Error: Failed to open duplicate file pair summary output file (";
			err += dupFileNameCSV;
			err += ")";
			cout << err << endl;
			CUtil::AddError(err);
			return;
		}

		CUtil::PrintFileHeader(dupFileCSV, "DUPLICATE FILE PAIRS", cmdLine);
		dupFileCSV << "Original,Duplicate" << endl;
		if (useListA)
			PrintDuplicateList(duplicateFilesInA1, duplicateFilesInA2, dupFileCSV, true);
		else
			PrintDuplicateList(duplicateFilesInB1, duplicateFilesInB2, dupFileCSV, true);
		dupFileCSV.close();
	}
}

/*!
* Prints the duplicate file list.
*
* \param myList1 original files list
* \param myList2 duplicate files list
* \param outfile output file stream
* \param csvFormat print CSV file format
*/
void MainObject::PrintDuplicateList(StringVector &myList1, StringVector &myList2, ofstream &outfile, bool csvFormat)
{
	if (myList1.size() > 0)
	{
		if (csvFormat)
		{
			StringVector::iterator myI2 = myList2.begin();
			for (StringVector::iterator myI1 = myList1.begin(); myI1 != myList1.end(); myI1++, myI2++)
				outfile << (*myI1) << "," << (*myI2) << endl;
		}
		else
		{
			for (int y = 0; y < 90; y++)
				outfile << "-";
			outfile << endl;
			StringVector::iterator myI2 = myList2.begin();
			for (StringVector::iterator myI1 = myList1.begin(); myI1 != myList1.end(); myI1++, myI2++)
			{
				outfile.setf(ofstream::left);
				outfile.width(45);
				outfile << (*myI1);
				outfile.unsetf(ofstream::left);
				outfile.width(5);
				outfile << "  |  ";
				outfile.setf(ofstream::left);
				outfile.width(45);
				outfile << (*myI2) << endl;
			}
		}
	}
}

/*!
* Finds duplicate files in a baseline.
*
* \param fileList file list
* \param dupList1 first (source) duplicate files list
* \param dupList2 duplicate files list
* \param checkMatch check for matching files (applies only when differencing)
*/
void MainObject::FindDuplicateFiles(SourceFileList &fileList, StringVector &dupList1, StringVector &dupList2, bool checkMatch)
{
	for (SourceFileList::iterator i = fileList.begin(); i != fileList.end(); i++)
	{
		if (!(*i).second.duplicate && !(*i).second.firstDuplicate)
		{
			if ((*i).second.file_name.find(EMBEDDED_FILE_PREFIX) == string::npos)
				FindDuplicateFor(fileList, i, dupList1, dupList2, checkMatch);
		}
	}

	// update duplicate embedded files
	for (SourceFileList::iterator i = fileList.begin(); i != fileList.end(); i++)
	{
		if ((*i).second.class_type == WEB && ((*i).second.duplicate || (*i).second.firstDuplicate))
		{
			SourceFileList::iterator j = i;
			for (j++; j != fileList.end(); j++)
			{
				if (j->second.file_name.find(EMBEDDED_FILE_PREFIX) != string::npos)
				{
					if ((*i).second.duplicate)
						j->second.duplicate = true;
					else
						j->second.firstDuplicate = true;
				}
				else
					break;
			}
		}
	}	
}

/*!
* Searches for duplicates of a given source file.
*
* \param compareList list of source files
* \param sfi source file list iterator
* \param dupList1 first (source) duplicate files list
* \param dupList2 duplicate files list
* \param checkMatch check for matching files (applies only when differencing)
*/
bool MainObject::FindDuplicateFor(SourceFileList &compareList, SourceFileList::iterator &sfi,
								  StringVector &dupList1, StringVector &dupList2, bool checkMatch)
{
	vector<pair<SourceFileElement*, SourceFileElement*> > matchedFiles;

	SourceFileElement* nullElement = NULL;

	size_t dupCnt = 0;
	bool foundDup = false, recDup = true, filesMatched;
	int filenameMatched;
	SourceFileList::iterator i = sfi;
	SourceFileList::iterator j = sfi;
	size_t sizeF1, sizeF2;
	double pctcheck, changed_lines, total_lines, pct_change;
	bool found;
	srcLineVector emptyFile;
	
	if (j == compareList.end())
		return false;

	for (j++; j != compareList.end(); j++)
	{
		if ((*j).second.duplicate || (*j).second.firstDuplicate ||
			(*j).second.file_name.find(EMBEDDED_FILE_PREFIX) != string::npos)
		{
			// already been matched or embedded file
			continue;
		}
		filenameMatched = CUtil::ExtractFilename((*i).second.file_name).compare(CUtil::ExtractFilename((*j).second.file_name));
		if ((*i).first.size() != (*j).first.size() &&
			filenameMatched != 0)
		{
			// two files have different number of lines and different filename
			continue;
		}

		// if files have same name, do a diff and mark as duplicates if logical SLOC change % is below threshold
		filesMatched = false;
		if (filenameMatched == 0 && ((*i).second.file_type != DATA || ((*i).first.size() < 1 && (*j).first.size() < 1)))
		{
			// match empty files with same name
			if ((*i).first.size() < 1 && (*j).first.size() < 1)
				filesMatched = true;
			else
			{
				// each source file elements results object has a mySLOCLines object with the SLOC to be diffed
				changed_lines = total_lines = pct_change = 0.0;
				sizeF1 = 0;
				sizeF2 = 0;

				// for web languages, diff each of the embedded files
				if ((*i).second.class_type == WEB)
				{
					// find all matches for i embedded files in j
					SourceFileList::iterator i1 = i;
					SourceFileList::iterator j1 = j;
					for (i1++; i1 != compareList.end(); i1++)
					{
						if (i1->second.file_name.find(EMBEDDED_FILE_PREFIX) == string::npos)
							break;

						found = false;
						j1 = j;
						for (j1++; j1 != compareList.end(); j1++)
						{
							if (j1->second.file_name.find(EMBEDDED_FILE_PREFIX) == string::npos)
								break;
							if (CUtil::ExtractFilename(i1->second.file_name).compare(CUtil::ExtractFilename(j1->second.file_name)) == 0)
							{
								found = true;
								matchedFiles.push_back(make_pair(&(*i1), &(*j1)));
								sizeF1 += i1->second.mySLOCLines.size();
								sizeF2 += j1->second.mySLOCLines.size();
							}
						}
						if (!found)
						{
							sizeF1 += i1->second.mySLOCLines.size();
							matchedFiles.push_back(make_pair(&(*i1), nullElement));
						}
					}

					// find all unmatched j embedded files
					j1 = j;
					for (j1++; j1 != compareList.end(); j1++)
					{
						if (j1->second.file_name.find(EMBEDDED_FILE_PREFIX) == string::npos)
							break;

						found = false;
						i1 = i;
						for (i1++; i1 != compareList.end(); i1++)
						{
							if (i1->second.file_name.find(EMBEDDED_FILE_PREFIX) == string::npos)
								break;
							if (CUtil::ExtractFilename(i1->second.file_name).compare(CUtil::ExtractFilename(j1->second.file_name)) == 0) 
							{
								found = true;
								break;
							}
						}
						if (!found)
						{
							sizeF2 += j1->second.mySLOCLines.size();
							matchedFiles.push_back(make_pair(nullElement, &(*j1)));
						}
					}
					
					if (sizeF1 > sizeF2)
						pctcheck = 100 * (double)(sizeF1 - sizeF2) / sizeF1;
					else
						pctcheck = 100 * (double)(sizeF2 - sizeF1) / sizeF2;

					// perform comparison only if the change percent (pctcheck) is not greater than threshold
					if (pctcheck <= duplicate_threshold)
					{
						vector<pair<SourceFileElement*, SourceFileElement*> >::iterator ii = matchedFiles.begin();
						while (ii != matchedFiles.end())
						{
							if (ii->first == nullElement)
							{								
								// don't need to compare the empty file to compute the information
								changed_lines += ii->second->second.mySLOCLines.size(); // all lines deleted
							} 
							else if (ii->second == nullElement)
							{
								// don't need to compare the empty file to compute the information
								changed_lines += ii->first->second.mySLOCLines.size();
								total_lines += ii->first->second.mySLOCLines.size();								
							} 
							else
								CompareForDuplicate(ii->first->second.mySLOCLines, ii->second->second.mySLOCLines, changed_lines, total_lines);

							ii++;
						}
					}
					else
						continue;
				}
				else
				{
					// only compare if the chance of duplicates is high
					sizeF1 = (*i).second.mySLOCLines.size();
					sizeF2 = (*j).second.mySLOCLines.size();
					if (sizeF1 > sizeF2)
						pctcheck = 100 * (double)(sizeF1 - sizeF2) / sizeF1;
					else
						pctcheck = 100 * (double)(sizeF2 - sizeF1) / sizeF2;

					// perform comparison only if the change percent (pctcheck) is not greater than threshold
					if (pctcheck <= duplicate_threshold)
						CompareForDuplicate((*i).second.mySLOCLines, (*j).second.mySLOCLines, changed_lines, total_lines); 
					else
						continue;
				}

				if (changed_lines > 0.0)
					pct_change = (changed_lines / total_lines) * 100.0;
				if (pct_change <= duplicate_threshold)
					filesMatched = true;
			}
		}
		else
		{
			// if filenames are different, do a line by line comparison for identical duplicate
			if ((*i).first.size() < 1 || (*j).first.size() < 1 || (*i).first.size() != (*j).first.size())
			{
				// don't match empty file with different names
				continue;
			}

			// note: two files have the same number of lines
			vector<lineElement>::iterator baseLine = (*i).first.begin();
			vector<lineElement>::iterator compareLine = (*j).first.begin();
			while (baseLine != (*i).first.end() && compareLine != (*j).first.end())
			{
				if ((*baseLine).line.compare((*compareLine).line) != 0)
					break;
				baseLine++;
				compareLine++;
			}
			if (baseLine == (*i).first.end() && compareLine == (*j).first.end())
				filesMatched = true;
		}
		if (filesMatched)
		{
			// check whether a comparison match exists
			recDup = true;
			if (checkMatch)
			{
				if ((*i).second.matched)
					checkMatch = false;
				else if ((*j).second.matched)
				{
					// change previously set first duplicate (if necessary)
					if (foundDup)
					{
						(*i).second.firstDuplicate = false;
						for (size_t n = dupList1.size() - dupCnt; n < dupList1.size(); n++)
							dupList1[n] = (*j).second.file_name;
					}

					// switch first duplicate for one with a match
					recDup = false;
					checkMatch = false;
					(*j).second.firstDuplicate = true;
					(*i).second.duplicate = true;
					dupList1.push_back((*j).second.file_name);
					dupList2.push_back((*i).second.file_name);
					dupCnt++;
					i = j;
				}
			}

			if (recDup)
			{
				// add pair to duplicate list
				(*i).second.firstDuplicate = true;
				(*j).second.duplicate = true;
				dupList1.push_back((*i).second.file_name);
				dupList2.push_back((*j).second.file_name);
				dupCnt++;
			}
			foundDup = true;
		}
	}
	return foundDup;
}

/*!
* Compares two files and adds to the changed/total lines for duplicate processing.
*
* \param firstFile first file to compare
* \param secondFile second file to compare
* \param changedLines accumulated number of changed lines
* \param totalLines accumulated total number of lines
*/
void MainObject::CompareForDuplicate(srcLineVector &firstFile, srcLineVector &secondFile,
									 double &changedLines, double &totalLines)
{
	CmpMngr myDiffManager;
	srcLineVector ff = firstFile;
	srcLineVector sf = secondFile;

	myDiffManager.Compare(&ff, &sf, 60);
	changedLines += myDiffManager.nAddedLines + myDiffManager.nDeletedLines + myDiffManager.nChangedLines;
	totalLines += myDiffManager.nDeletedLines + myDiffManager.nChangedLines + myDiffManager.nNochangedLines;
}
