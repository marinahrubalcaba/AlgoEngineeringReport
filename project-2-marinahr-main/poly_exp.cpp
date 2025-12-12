
///////////////////////////////////////////////////////////////////////////////
// poly_exp.cpp
//
// Definitions for the functions declared in poly_exp.hpp.
//
///////////////////////////////////////////////////////////////////////////////

#include "poly_exp.hpp"
#include <climits> 
#include <cmath> 
#include <cstdint> 

namespace subarray
{
  summed_span max_subarray_exh(const std::vector<int> &input)
  {

    assert(!input.empty());
    int b = 0;
    int e = 1;

    for (int i = 0; i < input.size(); i++)
    {

      for (int j = i + 1; j <= input.size(); j++)
      {
        summed_span CurrentBest(input.begin() + b, input.begin() + e);
        summed_span PossibleBest(input.begin() + i, input.begin() + j);

        if ((PossibleBest.sum()) > (CurrentBest.sum())) 
        {                                               
          b = i;
          e = j;
        }
      }
    }
    return summed_span(input.begin() + b, input.begin() + e);
  }

  summed_span max_subarray_crossing(const std::vector<int> &input, int low, int middle, int high)
  {
    int leftSum = INT_MIN;  
    int rightSum = INT_MIN; 
    int sum = 0;
    int b;
    int e;

    for (int i = middle; i >= low; i--)
    {
      sum += input[i];
      if (sum > leftSum)
      {
        leftSum = sum;
        b = i;
      }
    }

    sum = 0;

    for (int i = middle + 1; i <= high; i++)
    {
      sum += input[i];
      if (sum > rightSum)
      {
        rightSum = sum;
        e = i;
      }
    }

    return summed_span(input.begin() + b, input.begin() + e + 1);
  }

  summed_span max_subarray_recurse(const std::vector<int> &input, int low, int high)
  {
    if (low == high)
    {
      return (summed_span(input.begin() + low, input.begin() + low + 1));
    }
    int middle = (low + high) / 2;

    summed_span entirelyLeft = max_subarray_recurse(input, low, middle);
    summed_span entirelyRight = max_subarray_recurse(input, middle + 1, high);
    summed_span crossing = max_subarray_crossing(input, low, middle, high);

    if (entirelyLeft.sum() >= entirelyRight.sum() && entirelyLeft.sum() >= crossing.sum()) 
    {                                                                                     
      return entirelyLeft;
    }
    else if (entirelyRight.sum() >= entirelyLeft.sum() && entirelyRight.sum() >= crossing.sum())
    {
      return entirelyRight;
    }
    return crossing;
  }

  summed_span max_subarray_dbh(const std::vector<int> &input)
  {
    assert(!input.empty());
    return max_subarray_recurse(input, 0, input.size() - 1);
  }

  std::optional<std::vector<int>>
  subset_sum_exh(const std::vector<int> &input, int target)
  {
    assert(!input.empty());
    assert(input.size() < 64);

    int n = input.size();

    for (uint64_t bits = 0; bits < pow(2, n); bits++)
    {
      std::vector<int> candidate;
      int sum = 0;

      for (int j = 0; j <= n - 1; j++)
      {
        if (((bits >> j) & 1) == 1)
        {
          candidate.push_back(input[j]);
          sum += input[j];
        }
      }
      if (candidate.size() > 0 && sum == target)
      {
        return candidate;
      }
    }

    return std::nullopt;
  }
}
