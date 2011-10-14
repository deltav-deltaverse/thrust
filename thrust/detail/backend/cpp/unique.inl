/*
 *  Copyright 2008-2011 NVIDIA Corporation
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */

#pragma once

#include <thrust/detail/config.h>
#include <thrust/detail/backend/cpp/unique.h>
#include <thrust/iterator/iterator_traits.h>
#include <thrust/pair.h>
#include <thrust/detail/backend/dereference.h>

namespace thrust
{
namespace detail
{
namespace backend
{
namespace cpp
{


template<typename ForwardIterator,
         typename BinaryPredicate>
  ForwardIterator unique(tag,
                         ForwardIterator first,
                         ForwardIterator last,
                         BinaryPredicate binary_pred)
{
  // unique_copy() permits in-situ operation
  return thrust::detail::backend::cpp::unique_copy(tag(),first, last, first, binary_pred);
} // end unique()


template<typename InputIterator,
         typename OutputIterator,
         typename BinaryPredicate>
  OutputIterator unique_copy(tag,
                             InputIterator first,
                             InputIterator last,
                             OutputIterator output,
                             BinaryPredicate binary_pred)
{
  typedef typename thrust::iterator_traits<InputIterator>::value_type T;

  if(first != last)
  {
    T prev = backend::dereference(first);

    for(++first; first != last; ++first)
    {
      T temp = backend::dereference(first);

      if (!binary_pred(prev, temp))
      {
        backend::dereference(output) = prev;

        ++output;

        prev = temp;
      }
    }

    backend::dereference(output) = prev;
    ++output;
  }

  return output;
} // end unique_copy()


} // end namespace cpp
} // end namespace backend 
} // end namespace detail
} // end namespace thrust
