//! Code counter class methods for the Ruby language.
/*!
* \file CRubyCounter.cpp
*
* This file contains the code counter class methods for the Ruby language.
*/

#include "CRubyCounter.h"

/*!
* Constructs a CRubyCounter object.
*/
CRubyCounter::CRubyCounter()
{
	classtype = RUBY;
	language_name = "Ruby";

	file_extension.push_back(".rb");

	QuoteStart = "\"%/<";
	QuoteEnd = "\"/";
	QuoteEscapeFront = '\\';
	ContinueLine = ".,";

	BlockCommentStart.push_back("=begin");
	BlockCommentEnd.push_back("=end");

	LineCommentStart.push_back("#");
	delimiter = "";

	directive.push_back("RubyAccessHandler");
	directive.push_back("RubyAddPath");
	directive.push_back("RubyAuthenHandler");
	directive.push_back("RubyAuthzHandler");
	directive.push_back("RubyCleanupHandler");
	directive.push_back("RubyFixupHandler");
	directive.push_back("RubyGcPerRequest");
	directive.push_back("RubyHandler"); 
	directive.push_back("RubyInitHandler");
	directive.push_back("RubyKanjiCode");
	directive.push_back("RubyLogHandler");
	directive.push_back("RubyHeaderParserHandler");
	directive.push_back("RubyOutputMode");
	directive.push_back("RubyPassEnv");
	directive.push_back("RubyRequire");
	directive.push_back("RubyRestrictDirectives");
	directive.push_back("RubySetEnv");
	directive.push_back("RubyTimeOut");
	directive.push_back("RubyTransHandler");
	directive.push_back("RubyTypeHandler");

	exec_name_list.push_back("begin");
	exec_name_list.push_back("break");
	exec_name_list.push_back("case");
	exec_name_list.push_back("catch");
	exec_name_list.push_back("collect");
	exec_name_list.push_back("continue");
	exec_name_list.push_back("default");
	exec_name_list.push_back("die");
	exec_name_list.push_back("do");
	exec_name_list.push_back("each");
	exec_name_list.push_back("else");
	exec_name_list.push_back("elsif");
	exec_name_list.push_back("end");
	exec_name_list.push_back("ensure");
	exec_name_list.push_back("exception");
	exec_name_list.push_back("exit");
	exec_name_list.push_back("for");
	exec_name_list.push_back("if");
	exec_name_list.push_back("new");
	exec_name_list.push_back("puts");
	exec_name_list.push_back("print");
	exec_name_list.push_back("rescue");
	exec_name_list.push_back("return");
	exec_name_list.push_back("switch");
	exec_name_list.push_back("throw");
	exec_name_list.push_back("try");
	exec_name_list.push_back("undef");
	exec_name_list.push_back("unless");
	exec_name_list.push_back("until");
	exec_name_list.push_back("when");
	exec_name_list.push_back("while");

	math_func_list.push_back("atan2");
	math_func_list.push_back("cos");
	math_func_list.push_back("exp");
	math_func_list.push_back("frexp");
	math_func_list.push_back("ldexp");
	math_func_list.push_back("rand");
	math_func_list.push_back("sin");
	math_func_list.push_back("sqrt");
	math_func_list.push_back("srand");
	math_func_list.push_back("tan");

	log_func_list.push_back("log");
	log_func_list.push_back("log10");

	cmplx_calc_list.push_back("%");
	cmplx_calc_list.push_back("+");
	cmplx_calc_list.push_back("-");
	cmplx_calc_list.push_back("*");
	cmplx_calc_list.push_back("/");
	cmplx_calc_list.push_back("**");

	cmplx_cond_list.push_back("begin");
	cmplx_cond_list.push_back("case");
	cmplx_cond_list.push_back("else");
	cmplx_cond_list.push_back("elsif");
	cmplx_cond_list.push_back("ensure");
	cmplx_cond_list.push_back("for");
	cmplx_cond_list.push_back("if");
	cmplx_cond_list.push_back("rescue");
	cmplx_cond_list.push_back("unless");
	cmplx_cond_list.push_back("until");
	cmplx_cond_list.push_back("when");
	cmplx_cond_list.push_back("while");
	
	cmplx_logic_list.push_back("&&");
	cmplx_logic_list.push_back("||");
	cmplx_logic_list.push_back("==");
	cmplx_logic_list.push_back("<=>");
	cmplx_logic_list.push_back("!");
	cmplx_logic_list.push_back("and");
	cmplx_logic_list.push_back("not");
	cmplx_logic_list.push_back("or");
	cmplx_logic_list.push_back("~");
	cmplx_logic_list.push_back(">");
	cmplx_logic_list.push_back("<");
	cmplx_logic_list.push_back(">=");
	cmplx_logic_list.push_back("=<");
	cmplx_logic_list.push_back("===");

	cmplx_assign_list.push_back("=");
	cmplx_assign_list.push_back("+=");
	cmplx_assign_list.push_back("-=");
	cmplx_assign_list.push_back("*=");
	cmplx_assign_list.push_back("/=");
	cmplx_assign_list.push_back("%=");
	cmplx_assign_list.push_back("**=");
}

/*!
* Replaces quoted strings inside a string starting at idx_start with '$'.
* Handles special cases for Ruby string literals.
*
* \param strline string to be processed
* \param idx_start index of line character to start search
* \param contd specifies the quote string is continued from the previous line
* \param CurrentQuoteEnd end quote character of the current status
*
* \return method status
*/
int CRubyCounter::ReplaceQuote(string &strline, size_t &idx_start, bool &contd, char &CurrentQuoteEnd) 
{
	//%DStrD  # multiple lines allowed
	//%QDStrD  # multiple lines allowed
	//%qDStrD  # multiple lines allowed
	//<<DDStrDD  # multiple lines allowed

	// RegEx with /
	// RegEx with %rDRegExD
	static string heredoc_deli = "\"\'-ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_$";
	size_t idx;	// = string::npos;
	static string openParentheses = "([{<";
	static string closedParentheses = ")]}>";

	//( [ { < have to be closed with ) ] } >
	// blank is also used as a delimiter for string literal started with %
	size_t i = 0, startpos = 0, endpos = string::npos;
	bool foundQuote = false;
	size_t strlen = strline.length();
	unsigned int paren = 1;

	if (contd)
	{
		string tstrline = CUtil::TrimString(strline, 1);
		if ((tstrline.length() == 0 && delimiter == "\n") ||	// end of string literal with the new line as delimiter, e.g., %<NL>
			delimiter == tstrline)
		{
			// end of here document
			contd = false;
			delimiter = "";
		}
		else
		{
			// replace the whole line
			strline.replace(idx_start, strlen - idx_start, strlen - idx_start, '$');
			if (strline.length() > 0)
				strline[strline.length() - 1] = ContinueLine[0];	// continue the line
			else
				strline = string(1, ContinueLine[0]);
			return 0;
		}
	} 
	else
	{
		while (i < strlen && !contd)
		{
			switch (strline[i])
			{
			case '%':
				if (!foundQuote)
				{
					foundQuote = true;
					startpos = i;
					if (i + 1 < strlen)
					{
						if (strline[i + 1] == 'Q' ||
							strline[i + 1] == 'q' ||
							strline[i + 1] == 'r')
							i++;
					} 
					if (i + 1 == strlen)
					{
						contd = true;	// continued in the next line
						idx_start = i;
						delimiter = "\n";
						strline[i] = ContinueLine[0];
						return 0;
					}
					else
					{
						delimiter = string(1, strline[i + 1]);
						paren = 1;
					}
					i++;
				}					
				break;

			case '<':
				if (!foundQuote)
				{
					if (i + 2 < strlen && strline[i + 1] == '<')
					{
						// here document
						// foundQuote = true;
						// get the last delimiter specifying the end of the 'here document'

						// find the last delimiter, check for the last delimiter word not in a comment
						idx = strline.find_last_of("#");
						if (idx == string::npos)
							idx = strlen;
						idx = idx - 1;
						string tstrline = CUtil::TrimString(strline.substr(i + 2, idx + 1 - i - 2));
						
						strline[idx] = ContinueLine[0]; // indicate that the string will continue in the next line, so one SLOC is counted
						idx_start = idx + 1;

						idx = tstrline.find_last_of("<<"); // another here-doc delimiter?

						// if yes, get the last delimiter
						if (idx != string::npos)
							tstrline = tstrline.substr(idx + 1, tstrline.length());

						tstrline = CUtil::TrimString(tstrline);

						size_t i1 = 0;
						while (heredoc_deli.find(tstrline[i1]) != string::npos && i1 < tstrline.length())
							i1++;

						delimiter = tstrline.substr(0, i1);
						delimiter = CUtil::TrimString(delimiter);

						delimiter = CUtil::EraseString(delimiter, "\"");
						delimiter = CUtil::EraseString(delimiter, "\'");
						delimiter = CUtil::EraseString(delimiter, "-");

						contd = true;
						return 0;
					}
					else
					{
						idx_start = strline.length();
						return 1;
					}
				}
				break;

			case '/':
				if (!foundQuote)
				{
					delimiter = "/"; 
					foundQuote = true; 
					startpos = i;
				}
				else
				{
					strline.replace(startpos, i - startpos + 1, i - startpos + 1, '$');
					delimiter = "";
					foundQuote = false; 
					idx_start = i + 1;
				}
				break;

			default:
				if (foundQuote)
				{
					if (delimiter.length() == 1 && delimiter[0] == strline[i] &&
						openParentheses.find(delimiter) != string::npos)
					{
						paren++;
					}
					
					// check if the char is a closing bracket
					if ((idx = closedParentheses.find(strline[i])) != string::npos)
					{
						if (delimiter.length() > 0 && openParentheses[idx] == delimiter[0] && paren > 0)
							paren--;
						if (paren == 0)
						{
							// here we go, replace string starting from startpos?
							endpos = i;
						}
					}
					else
					{
						if (delimiter.length() > 0 && strline[i] == delimiter[0] && paren == 1)
						{
							// here we go, replace string starting from startpos
							endpos = i;
						}
					}

					if (endpos != string::npos)
					{
						foundQuote = false;
						// now, replace string from startpos to endpos
						strline.replace(startpos, endpos - startpos + 1, endpos - startpos + 1, '$');
						contd = false;
						delimiter = "";
						endpos = string::npos;
						idx_start = i + 1;
					}
				}					
				break;
			}
			i++;
		}
	}
	return CCodeCounter::ReplaceQuote(strline, idx_start, contd, CurrentQuoteEnd);
}

/*!
* Counts directive lines of code.
*
* \param fmap list of processed file lines
* \param result counter results
* \param fmapBak list of original file lines (same as fmap except it contains unmodified quoted strings)
*
* \return method status
*/
int CRubyCounter::CountDirectiveSLOC(filemap* fmap, results* result, filemap* fmapBak)
{
	bool trunc_flag = false;
	size_t strSize;
	unsigned int cnt = 0;
	string exclude = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_$/\\<>.+?!@#$%^&*()-+*";
	string strDirLine = "";

	filemap::iterator itfmBak = fmapBak->begin();
	for (filemap::iterator iter = fmap->begin(); iter!=fmap->end(); iter++, itfmBak++)
	{
		if (CUtil::CheckBlank(iter->line))
			continue;

		cnt = 0;
		CUtil::CountTally(" " + iter->line, directive, cnt, 1, exclude, "", "", &result->directive_count);

		if (cnt != 0)
		{
			strSize = CUtil::TruncateLine(itfmBak->line.length(), 0, result->lsloc_truncate, trunc_flag);
			if (strSize > 0)
			{
				strDirLine = itfmBak->line.substr(0, strSize);
				if (result->addSLOC(strDirLine, trunc_flag))
					result->directive_lines[LOG]++;
				result->directive_lines[PHY] ++;
			}
			iter->line = "";
		}
 	}
	return 1;
}

/*!
* Processes physical and logical lines according to language specific rules.
* NOTE: all the blank lines +
*               whole line comments +
*               lines with compiler directives
*       should have been blanked from filemap by previous processing
*       before reaching this function
*
* \param fmap list of processed file lines
* \param result counter results
* \param fmapBak list of original file lines (same as fmap except it contains unmodified quoted strings)
*
* \return method status
*/
int CRubyCounter::LanguageSpecificProcess(filemap* fmap, results* result, filemap* fmapBak)
{
	char			prev_char			= 0;
	bool			data_continue		= false;
	bool			inArrayDec			= false;
	string			strLSLOC			= "";
	string			strLSLOCBak			= "";
	unsigned int	openBrackets		= 0;

	filemap::iterator fit, fitbak;
	string line, lineBak;
	StringVector loopLevel;

	unsigned int phys_exec_lines = 0;
	unsigned int phys_data_lines = 0;
	unsigned int temp_lines = 0;
	unsigned int cnt = 0;
	string exclude = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_$";
	delimiter = "";

	for (fit = fmap->begin(), fitbak = fmapBak->begin(); fit != fmap->end(); fit++, fitbak++)
	{
		line = fit->line;
		lineBak = fitbak->line;
	
		// do not process blank lines
		// blank line means blank_line/comment_line/directive
		if (!CUtil::CheckBlank(line))
		{
			LSLOC(result, line, lineBak, strLSLOC, strLSLOCBak);

			if (isPrintKeyword)
			{
				cnt = 0;
				CUtil::CountTally(" " + line, exec_name_list, cnt, 1, exclude, "", "", &result->exec_name_count);
			}

			// no data declaration in Ruby
			result->exec_lines[PHY]++;
		}
	}
	return 1;
}

/*!
* Extracts and stores logical lines of code.
* Determines and extract logical SLOC to place in the result variable
* using addSLOC function. Each time the addSLOC function is called,
* a new logical SLOC is added. This function assumes that the directive
* is handled before it is called.
*
* \param result counter results
* \param line processed physical line of code
* \param lineBak original physical line of code
* \param strLSLOC processed logical string
* \param strLSLOCBak original logical string
*/
void CRubyCounter::LSLOC(results* result, string line, string lineBak, string &strLSLOC, string &strLSLOCBak)
{
	static string control_modifiers[] = {"if", "for", "unless", "while", "until"};
	static size_t control_mod_cnt = 4;
	size_t start = 0; // starting index of the working string
	size_t i = 0, strSize = string::npos;
	bool trunc_flag = false;
	unsigned int cnt = 0;

	string tmp = CUtil::TrimString(strLSLOC);
	bool line_skipped = false;

	string tline = CUtil::TrimString(line);

	if (tline == "end" || tline == "else" || tline == "}")
	{
		if (tmp.length() > 0)
			line_skipped = true;
		else
			return;
	}

	size_t idx = string::npos;
	for (i = 0; i < control_mod_cnt; i++)
	{
		idx = CUtil::FindKeyword(line, control_modifiers[i]);
		if (idx != string::npos)
		{
			if (CUtil::FindKeyword(tline, control_modifiers[i]) != 0)
			{
				// only extract if the mod in the middle of line
				strSize = CUtil::TruncateLine(idx + 1 - start, strLSLOC.length(), result->lsloc_truncate, trunc_flag);
				break;
			}
		}
	}

	if (strSize > 0 && strSize != string::npos)	// only if (idx != 0 && idx != string::npos) returns true
	{
		strLSLOC += line.substr(start, strSize - 1);
		strLSLOCBak += lineBak.substr(start, strSize - 1);
	} 
	else if (!line_skipped)
	{
		strLSLOC += line;
		strLSLOCBak += lineBak;
		
		if (tline.length() > 0)
		{
			for (i = 0; i < ContinueLine.length(); i++)
			{
				if (tline.find_last_of(ContinueLine[i]) == tline.length() - 1)
				{
					// continued to the next line
					return;
				}
			}
		}
	}

	if (CUtil::TrimString(strLSLOC).length() == 0)
		return;
	
	if (result->addSLOC(strLSLOCBak, trunc_flag))
		result->exec_lines[LOG]++;

	if (idx != 0 && idx != string::npos)
	{
		// the line has two logical lines
		strLSLOC = line.substr(idx);
		strLSLOCBak = lineBak.substr(idx);

		if (tline.length() == 0)
			return;
		for (i = 0; i < ContinueLine.length(); i++)
		{
			if (tline.find_last_of(ContinueLine[i]) == tline.length() - 1)
			{
				// continued to the next line
				return;
			}
		}
		if (CUtil::TrimString(strLSLOC).length() == 0)
			return;
		if (result->addSLOC(strLSLOCBak, trunc_flag))
			result->exec_lines[LOG]++;
	}
	if (tline.length() == 0)
		return;

	strLSLOC = strLSLOCBak = "";
}
