#pragma once
#include "stdafx.hpp"

#ifndef __PCH__
#define __PCH__

#include <OpenGL.hpp>
#include <Pipeline.hpp>
#include <Uniform.hpp>

#include "WindowManager.hpp"
#include "Timer.hpp"
#include "Constants.hpp"
#include "Transform.hpp"
#include "Camera.hpp"
#include "Scene.hpp"
#include "Collider.hpp"
#include "GameObject.hpp"
#include "Entity.hpp"
#include "Model.hpp"
#include "ModelView.hpp"
#include "Map.hpp"

namespace map
{
	class WorldManager;
}

float RandomizeColour();

#endif
