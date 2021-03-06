#Look for a directory containing STLport.
#
# The following values are defined
# GDXCPP_INCLUDE_DIR - where to find vector, etc.
# GDXCPP_LIBRARIES   - link against these to use STLport
# GDXCPP_FOUND       - True if the STLport is available.

# also defined, but not for general use are
IF(GDXCPP_LIBRARIES AND GDXCPP_INCLUDE_DIR)
# in cache already
SET(GDXCPP_FIND_QUIETLY TRUE)
ENDIF(GDXCPP_LIBRARIES AND GDXCPP_INCLUDE_DIR)

FIND_PATH(GDXCPP_INCLUDE_DIR
gdx-cpp/Gdx.hpp
PATHS
${GDX_SOURCE}/src
${GDX_ROOT}/include
/usr/local/include
/usr/include
/sw/include
/opt/local/include
/opt/csw/include
/opt/include
)

#ok... I don't know, but when on android the macro find_files does not work, even if "if (EXISTS FILENAME)" works correctly
#so I've replicated the behavior of find_files. Cmake is starting to bother me...
SET(GDX_CPP_GDX_MACRO GDX_CPP_GDX_MACRO-NOTFOUND)
SET(paths_to_check
${GDX_SOURCE}/cmake/
${GDX_ROOT}/share/gdx/cmake/
/usr/share/gdx/cmake/
/usr/local/share/gdx/cmake/
/opt/local/share/gdx/cmake/)

foreach(p ${paths_to_check})

get_filename_component(norm_path ${p}/gdx.cmake ABSOLUTE)
if (EXISTS ${norm_path})
  set(GDX_CPP_GDX_MACRO ${norm_path})
  break()
endif()

endforeach()

include(${GDX_CPP_GDX_MACRO})

macro(find_libraries)
    foreach(lib ${ARGV0})
        FIND_LIBRARY(GDXCPP_${lib}
            NAMES
            ${lib}
            PATHS
            /usr/local/lib
            /usr/lib
            /opt/local/lib
            /opt/lib
            /usr/lib/x86_64-linux-gnu
            ${GDX_ROOT}/lib
            )

        if (GDXCPP_${lib})
            LIST(APPEND GDXCPP_LIBRARIES "${GDXCPP_${lib}}")
        else()
            message(FATAL_ERROR "Could not find Libgdx library dependency:" ${lib})
            SET(GDXCPP_LIBRARIES GDXCPP_LIBRARIES-NOTFOUND)
            return(find_libraries)
        endif()
    endforeach()
endmacro()

if (APPLE)
    find_libraries(gdx-cpp)

    if (GdxCpp_USE_BOX2D)
        find_libraries("Box2D;gdx-cpp-box2d-layer")
    endif()
    
    find_libraries("gdx-cpp-backend-ios;gdx-cpp-agg-svg;")
elseif (UNIX)
    if (GdxCpp_USE_BOX2D)
        find_libraries("Box2D;gdx-cpp-box2d-layer")
    endif()
    
    if (ANDROID_NDK)
         set(GDXCPP_LIBRARIES "${GDXCPP_LIBRARIES};dl;log;GLESv1_CM;GLESv2;")
        find_libraries("gdx-cpp-backend-android;gdx-cpp-agg-svg;")
    else(ANDROID_NDK)
        if (GdxCpp_BUILD_GRAPHICS_OPENGL)
            find_libraries("GL")
        else()
            find_libraries("GLESv1_CM;GLESv2")
        endif()

        find_libraries("vorbis;vorbisfile;openal;ogg;SDL;GLU;gdx-cpp-backend-linux;gdx-cpp-agg-svg;")
    endif()

    find_libraries(gdx-cpp)
endif()

if(GDXCPP_INCLUDE_DIR)
    if(GDXCPP_LIBRARIES)
        set(GDXCPP_FOUND TRUE)
    endif(GDXCPP_LIBRARIES)
endif(GDXCPP_INCLUDE_DIR)

if(GDXCPP_FOUND)
    if(NOT GDXCPP_FIND_QUIETLY)
        foreach(LIB ${GDXCP_LIBRARIES})
           message("Found GDX Library: " ${LIB})
        endforeach()
    endif()
else(GDXCPP_FOUND)
    if(NOT GDXCPP_FIND_QUIETLY)
        message(STATUS "Warning: Unable to find GdxCPP!")
    endif()
endif(GDXCPP_FOUND)

MARK_AS_ADVANCED(GDXCPP_LIBRARY)
