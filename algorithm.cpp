#include "algorithm.h"

#include <algorithm>

// A set of all subsets for a given superset
std::set<std::set<int>> powerSet()
{
  // Generate a power set of the set of digits 1 - 9
  std::set<std::set<int>> powerSet;
  int numberOfSubsets = 1 << 9; // 2 ^ 9
  // Start at zero for empty set, do not include the 'numberOfSubsets' as an index
  for (int subsetIndex = 0; subsetIndex < numberOfSubsets; ++subsetIndex)
  {
    std::set<int> subset;
    for (int supersetIndex = 0; supersetIndex < 9; ++supersetIndex)
    {
      // Include this digit if the corresponding bit of subsetIndex is set
      int bitSet = (1 << supersetIndex) & subsetIndex;
      if (bitSet)
	subset.insert(supersetIndex + 1); // because 1-9
    }
    powerSet.insert(subset);
  }
  return powerSet;
}
