/*
 *    Copyright 2011 Aevum Software aevum @ aevumlab.com
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 *
 *    @author Victor Vicente de Carvalho victor.carvalho@aevumlab.com
 *    @author Ozires Bortolon de Faria ozires@aevumlab.com
 */


#ifndef GDX_CPP_UTILS_MATRIXBASE_HPP
#define GDX_CPP_UTILS_MATRIXBASE_HPP

#include "ArrayBase.hpp"
#include <vector>

namespace gdx {

template <class T>
struct ArrayBase
{
public:

    ArrayBase(int _size): size(_size)
    {
      value = new T[size];
    }

    T operator[] (unsigned i) {
        return value[i];
    }

  int size;
private:
  T * value;
};

} //namespace gdx
#endif // GDX_CPP_UTILS_MATRIXBASE_HPP

