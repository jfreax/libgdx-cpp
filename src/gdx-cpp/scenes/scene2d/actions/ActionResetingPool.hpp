
/*
    Copyright 2011 Aevum Software aevum @ aevumlab.com

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.

    @author Victor Vicente de Carvalho victor.carvalho@aevumlab.com
    @author Ozires Bortolon de Faria ozires@aevumlab.com
*/

#ifndef GDX_CPP_SCENES_SCENE2D_ACTIONS_ACTIONRESETINGPOOL_HPP_
#define GDX_CPP_SCENES_SCENE2D_ACTIONS_ACTIONRESETINGPOOL_HPP_

#include "gdx-cpp/utils/Pool.hpp"

namespace gdx {
template <typename T>
class ActionResetingPool : public Pool<T> {
public:
    ActionResetingPool (int initialCapacity, int max)
        : Pool<T>(initialCapacity, max)
    {        
    }
    
    T* obtain () {
        T* elem = Pool<T>::obtain();
        elem->reset();
        return elem;
    }
};

} // namespace gdx

#endif // GDX_CPP_SCENES_SCENE2D_ACTIONS_ACTIONRESETINGPOOL<T EXTENDS ACTION>_HPP_
