//! Compare manager class methods.
/*!
* \file CmpMngr.h
*
* This file contains the compare manager class methods.
* This class implements the GDiff07 algorithm, developed by Harley Green for 
* The University of Southern California Center for Systems and Software Engineering (USC-CSSE), 
* in conjunction with The Aerospace Corporation.
* The GDiff07 algorithm breaks the counting process for finding differences between two revisions of a file
* into several steps. First it counts and removes all unmodified lines during this process lines that are 
* not matched are put into a separate list for each of the two files. 
* These lists are then searched for swapped lines (DISABLED)
* and have those removed. Then the remaining lines are searched again for modified matches. Once the unmodified, swapped 
* and modified lines are removed the only remaining lines will be either added or deleted so no further action is necessary 
* and the algorithm is finished.
* Uses function for finding a similar line provided by J. Kim 10/09/2006 as part of the USC-CSSE Development process.
*/

#include "CmpMngr.h"

using namespace std;

/*!
* Calls routines to get the final count of the differences between two files.
*
* \param baseFileMap list of base files
* \param compFileMap list of comparison files
* \param match_threshold % threshold for matching, if greater then added/deleted instead of modified
*/
void CmpMngr::Compare(srcLineVector* baseFileMap, srcLineVector* compFileMap, double match_threshold)
{
	MATCH_THRESHOLD = match_threshold;
	nNochangedLines = nChangedLines = nAddedLines = nDeletedLines = 0;

	FindUnmodifiedLines(baseFileMap, compFileMap);
	FindModifiedLines(baseFileMap, compFileMap);

	// remaining lines are added or deleted, no further details needed to be searched.
	for (srcLineVector::iterator i = baseFileMap->begin(); i != baseFileMap->end(); i++)
		nDeletedLines += (*i).second;
	for (srcLineVector::iterator i = compFileMap->begin(); i != compFileMap->end(); i++)
		nAddedLines += (*i).second;
}

/*!
* Finds the number of modified lines, anything remaining in lists is either deleted or added.
*
* \param aHm list of base files
* \param bHm list of comparison files
*/
void CmpMngr::FindModifiedLines(srcLineVector* aHm, srcLineVector* bHm)
{
	srcLineVector* listA;
	srcLineVector* listB;
	stringSizeMap mySSList;
	int i, minSize, maxSize, maxSizeListA = 0;
	bool deleted, deletedA;

	if (aHm->size() == 0 || bHm->size() == 0)
		return;

	// pick the shortest list to do the sorting on
	if (aHm->size() > bHm->size())
	{
		listA = bHm;
		listB = aHm;
	}
	else
	{
		listA = aHm;
		listB = bHm;
	}

	// create a map of string size -> [iterators]
	// quickly access the locations of lines that are in valid size range of modified line for the given search line
	for (srcLineVector::iterator myI = listA->begin(); myI != listA->end(); myI++)
	{
		pair<stringSizeMap::iterator, bool> myResult;

		// populate with the number of copies of this string
		stringList myList((*myI).second, (*myI).first);
		myResult = mySSList.insert(make_pair((int)(*myI).first.size(), myList));
		if (!myResult.second)
		{
			// already had a copy of something this size
			(*myResult.first).second.insert((*myResult.first).second.begin(), myList.begin(), myList.end());	//append the list
		}
		if (maxSizeListA < (int)(*myI).first.size())
			maxSizeListA = (int)(*myI).first.size();
	}

	// iterate through the longer list and searches for modified lines in the shorter list
	// find the min and max size range for modified lines and only looks through those specific locations
	// since the map is sorted, lookup using find is log(n) to get the iterator
	
	// once an entry is found of a list of lines that have the same size in valid modified range, checks each to see if it is modified
	for (srcLineVector::iterator myI = listB->begin(); myI != listB->end();)
	{
		// find the valid size range (dictated by the MATCH_TRESHOLD)
		minSize = (int)((*myI).first.length() * (MATCH_THRESHOLD / 100));
		maxSize = MATCH_THRESHOLD != 0 ? (int)((*myI).first.length() / (MATCH_THRESHOLD / 100)) : maxSizeListA;
		if (maxSize > maxSizeListA)
			maxSize = maxSizeListA;

		deleted = false;
		deletedA = false;
		for (i = minSize; i <= maxSize; i++)
		{
			// find the list of strings of this length
			stringSizeMap::iterator mySSI = mySSList.find(i);
			if (mySSI != mySSList.end())
			{
				// found some
				for (stringList::iterator mySLI = (*mySSI).second.begin(); mySLI != (*mySSI).second.end(); )
				{
					if (SimilarLine((*mySLI),(*myI).first))
					{
						string prev = (*mySLI);
						srcLineVector::iterator listAi = listA->find((*mySLI));

						// eliminates the need to call SimilarLine function on every entry if they are the same
						while ((*myI).second > 0 && (mySLI != (*mySSI).second.end() && (*mySLI) == prev))
						{
							(*myI).second--;
							(*listAi).second--;
							stringList::iterator tmpSLI = mySLI++;
							(*mySSI).second.erase(tmpSLI);
							deletedA = true;
							nChangedLines++;
						}
						if ((*myI).second == 0)
						{
							srcLineVector::iterator tmpI = myI++;
							listB->erase(tmpI);
							deleted = true;
						}
						if ((*listAi).second == 0)
							listA->erase(listAi);
						if (deleted || deletedA)
							break;
					}
					else
						mySLI++;
				}
				if (deleted || deletedA)
					break;
			}
		}
		if (!deleted)
			myI++;
	}
}

/*!
* Performs a binary search to find unmodified lines, relies on fact that they are in
* STL hash (srcLineVector) so they are already sorted and the find function is log(n)
*
* \param aHm list of base files
* \param bHm list of comparison files
*/
void CmpMngr::FindUnmodifiedLines(srcLineVector* aHm, srcLineVector* bHm)
{
	srcLineVector* listA;
	srcLineVector* listB;
	if (aHm->size() > bHm->size())
	{
		listA = bHm;
		listB = aHm;
	}
	else
	{
		listA = aHm;
		listB = bHm;
	}	
	for (srcLineVector::iterator myI = listA->begin(); myI != listA->end(); )
	{
		bool deleted = false;
		srcLineVector::iterator result;
		result = listB->find((*myI).first);
		if (result != listB->end())
		{
			while ((*myI).second > 0 && (*result).second > 0)
			{
				(*myI).second--;
				(*result).second--;
				nNochangedLines++;
			}
			if ((*myI).second == 0)
			{
				srcLineVector::iterator tmpI = myI++;
				listA->erase(tmpI);
				deleted = true;
			}
			if ((*result).second == 0)
				listB->erase(result);
		}
		if (!deleted)
			myI++;
	}
}

/*!
* Determines whether two lines are similar.
* Originally written by J. Kim 10/09/2006
* Revised version of the original method
* - order of characters taken into account
* - criteria for determining 'similar lines' :
*   length(LCS) / length(baseLine) * 100 >= MATCH_THRESHOLD &&
*   length(LCS) / length(compLine) * 100 >= MATCH_THRESHOLD
* - above criteria solves two problems encountered in the original function
* <1>	
* similar_lines("ABC", "ABCDEF") = 1
* similar_lines("ABCDEF", "ABC") = 0
* => because of this, if we modify a line from the original file, sometimes
* we get 1 MODIFIED and sometimes get 1 ADDED + 1 DELETED.
* <2>
* "ABCDEF" and "FDBACE" classified as similar lines (order not taken into account)
* => because of this, when we delete a certain line from the original 
* file and insert a new one, instead of getting 1 ADDED and 1 DELETED, we might get 1 MODIFIED.
* (ex)
* DELETE: out = "test sentence";
* INSERT: cout << "censstetetne";
* and get 1 MODIFIED 
* instead of getting 1 ADDED + 1 DELETED
*
* \param baseLine base line
* \param compareLine comparison line
*
* \return whether two lines are similar
*/
bool CmpMngr::SimilarLine(const string &baseLine, const string &compareLine)
{
	int m, n, i, j, k;
	m = n = i = j = k = 0;
	double LCSlen = 0;
	m = (int)baseLine.size();
	n = (int)compareLine.size();
	vector<int> x1, x2;
	x1.resize(m + 1, 0);
	x2.resize(m + 1, 0);

	// compute length of LCS
	// - no need to use CBitMatrix
	for (j = n - 1; j >= 0; j--)
	{
		for (k = 0; k <= m; k++)
		{
			x2[k] = x1[k];
			x1[k] = 0;
		}
		for (i = m - 1; i >= 0; i--)
		{
			if (baseLine[i] == compareLine[j])
			{
				x1[i] = 1 + x2[i+1];
			}
			else
			{
				if (x1[i+1] > x2[i])
				{
					x1[i] = x1[i+1];
				}
				else
				{
					x1[i] = x2[i];
				}
			}
		}
	}
	LCSlen = x1[0];
	if ((LCSlen / (double)m * 100 >= MATCH_THRESHOLD) &&
		(LCSlen / (double)n * 100 >= MATCH_THRESHOLD))
		return true;
	else 
		return false;
}
