
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

#include "ETC1TextureData.hpp"

#include "gdx-cpp/utils/GdxRuntimeException.hpp"
#include "ETC1.hpp"
#include "gdx-cpp/Application.hpp"
#include "gdx-cpp/Gdx.hpp"
#include "MipMapGenerator.hpp"

using namespace gdx;
TextureData::TextureDataType& ETC1TextureData::getType () {
    return TextureDataType::Compressed;
}

Pixmap::ptr ETC1TextureData::getPixmap () {
    throw GdxRuntimeException("This TextureData implementation does not return a Pixmap");
}

bool ETC1TextureData::disposePixmap () {
    throw GdxRuntimeException("This TextureData implementation does not return a Pixmap");
}

void ETC1TextureData::uploadCompressedData () {
    ETC1::ETC1Data::ptr data = ETC1::ETC1Data::ptr(new ETC1Data(file));

    width = data->width;
    height = data->height;

    if (app->getType() == Application::Desktop || graphics->isGL20Available() == false) {
        Pixmap::ptr pixmap = ETC1.decodeImage(data, Pixmap::Format::RGB565);
        gl->glTexImage2D(GL10::GL_TEXTURE_2D, 0, pixmap->getGLInternalFormat(), pixmap->getWidth(), pixmap->getHeight(), 0,
                            pixmap->getGLFormat(), pixmap->getGLType(), pixmap->getPixels());
        if (useMipMaps) MipMapGenerator::generateMipMap(pixmap, pixmap->getWidth(), pixmap->getHeight(), false);
        pixmap->dispose();
        useMipMaps = false;
    } else {
        gl->glCompressedTexImage2D(GL10::GL_TEXTURE_2D, 0, ETC1::ETC1_RGB8_OES, width, height, 0,
                                      data->compressedData.capacity() - data->dataOffset, data->compressedData);
        if (useMipMaps()) gl20->glGenerateMipmap(GL20::GL_TEXTURE_2D);
    }
    data->dispose();
}

int ETC1TextureData::getWidth () {
    return width;
}

int ETC1TextureData::getHeight () {
    return height;
}

const Pixmap::Format& ETC1TextureData::getFormat () {
    return Pixmap::Format::RGB565;
}

bool ETC1TextureData::useMipMaps () {
    return useMipMaps;
}

bool ETC1TextureData::isManaged () {
    return true;
}

