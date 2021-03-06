
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

#ifndef GDX_CPP_GRAPHICS_G2D_EMPTYNINEPATCH_HPP_
#define GDX_CPP_GRAPHICS_G2D_EMPTYNINEPATCH_HPP_

#include "NinePatch.hpp"
#include <vector>

namespace gdx {

class EmptyNinePatch : public NinePatch {
public:
    typedef ref_ptr_maker<EmptyNinePatch>::shared_ptr_def ptr;
    
    EmptyNinePatch& getInstance ();
    int getRegionWidth ();
    int getRegionHeight ();
    TextureRegion::ptr getRegion ();
    void draw (const SpriteBatch& batch,float x,float y,float width,float height);
    ~EmptyNinePatch();

protected:


private:
  
  static std::vector<TextureRegion::ptr> emptyPatches;
  static EmptyNinePatch * instance;
  static TextureRegion::ptr region;

  EmptyNinePatch();
  
};

} // namespace gdx

#endif // GDX_CPP_GRAPHICS_G2D_EMPTYNINEPATCH_HPP_
