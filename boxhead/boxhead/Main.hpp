#pragma once
#include <OpenGL.hpp>
#include <Pipeline.hpp>
#include <VertexStream.hpp>
#include <Blobs.hpp>
#include <Utils.hpp>
#include <BlobUtils.hpp>

#include "Framework.hpp"
#include "misc.h"
#include "shader.h"
#include "input.h"
#include "box.h"
#include "zombie.h"
#include "line.h"

GLvoid Render(GLvoid);
GLvoid UpdateView(const int w, const int h);
GLvoid UpdateKeyboard(const unsigned char key, const int x, const int y);
GLvoid UpdateSpecialKeyboard(const int key, const int x, const int y);
GLvoid UpdateMouse(const int button, const int state, const int x, const int y);
GLvoid UpdateMouseMotion(const int x, const int y);
GLvoid UpdateFrames(const int delta_time);

float RandomizeColour();
