#include "algorithm.h"

#include "sudokuDefs.h"

#include <iostream>
#include <algorithm>

// A set of all subsets for a given superset
SetSetInt powerSet(SetInt superset)
{
  // Generate a power set of the set of digits 1 - 9
  SetSetInt powerSet;
  
  //int numberOfSubsets = 1 << 9; // 2 ^ 9
  int numberOfSubsets = 1 << superset.size(); // 2 ^ n
  
  // Start at 1 to exclude empty set
  // Exclude size > 4
  // Do not include the 'numberOfSubsets' as an index
  for (int subsetIndex = 1; subsetIndex < numberOfSubsets; ++subsetIndex)
  {
    SetInt subset;
    int i = 0;
    for (SetInt::iterator iter = superset.begin();
	 iter != superset.end();
	 ++iter, ++i)
    {
      // Include this digit if the corresponding bit of subsetIndex is set
      int bitSet = (1 << i) & subsetIndex;
      if (bitSet) subset.insert(*iter);
    }
    // Only add the required subsets
    if (subset.size() <= 4)
      powerSet.insert(subset);
    else
      { /* discard */ }
  }
  return powerSet;
}

void combineSets(SetSetInt *sets, SetInt *outputSet)
{
  std::for_each(sets->begin(), sets->end(),
		[outputSet](SetInt set)
		{std::set_union(set.begin(),
				set.end(),
				outputSet->begin(),
				outputSet->end(),
				std::inserter(*outputSet,
					      outputSet->begin()));}
		);
}

void print_set(SetInt &set)
{
  std::for_each(set.begin(), set.end(),
		[](int i){ std::cout << i << " "; });
  std::cout << std::endl;
}

void print_set(SetSetInt &set)
{
  std::for_each(set.begin(), set.end(),
		[](SetInt ints){ print_set(ints); });
}
