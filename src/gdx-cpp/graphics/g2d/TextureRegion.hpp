
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

#ifndef GDX_CPP_GRAPHICS_G2D_TEXTUREREGION_HPP_
#define GDX_CPP_GRAPHICS_G2D_TEXTUREREGION_HPP_

#include "gdx-cpp/graphics/Texture.hpp"
#include "gdx-cpp/utils/MatrixBase.hpp"

namespace gdx {

class TextureRegion {
public:
    typedef ref_ptr_maker<TextureRegion>::shared_ptr_def ptr;

    static ptr newFromTexture(Texture::ptr texture);
    static ptr newFromRegion(TextureRegion& region);
    
    TextureRegion ();
    TextureRegion (Texture::ptr _texture);
    TextureRegion (Texture::ptr _texture, int x, int y, int width, int height);
    TextureRegion (Texture::ptr _texture, float u, float v, float u2, float v2);
    TextureRegion (TextureRegion& region);
    TextureRegion (TextureRegion& region, int x, int y, int width, int height);
    virtual void setRegion (Texture::ptr texture);
    virtual void setRegion (int x,int y,int width,int height);
    virtual void setRegion (float u,float v,float u2,float v2);
    virtual void setRegion (const TextureRegion& region);
    virtual void setRegion (const TextureRegion& region, int x, int y, int width, int height);
    Texture::ptr getTexture () const;
    void setTexture (Texture::ptr texture);
    float getU () const;
    void setU (float u);
    float getV () const;
    void setV (float v);
    float getU2 () const;
    void setU2 (float u2);
    float getV2 () const;
    void setV2 (float v2);
    int getRegionX () const;
    void setRegionX (int x);
    int getRegionY () const;
    void setRegionY (int y);
    int getRegionWidth () const;
    void setRegionWidth (int width);
    int getRegionHeight () const;
    void setRegionHeight (int height);
    void flip (bool x,bool y);
    void scroll (float xAmount,float yAmount);
    MatrixBase< TextureRegion::ptr > split (int tileWidth, int tileHeight);
    MatrixBase< TextureRegion::ptr > split (Texture::ptr texture, int tileWidth, int tileHeight);

    float u, v;
    float u2, v2;
    
    
    virtual ~TextureRegion();

protected:
    Texture::ptr texture;

private:

};

} // namespace gdx

#endif // GDX_CPP_GRAPHICS_G2D_TEXTUREREGION_HPP_
