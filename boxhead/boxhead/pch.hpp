#pragma once
#include "stdafx.hpp"

#ifndef __PCH__
#define __PCH__

#include <OpenGL.hpp>
#include <Pipeline.hpp>
#include <Uniform.hpp>

class Framework;
class WindowManager;
class Timer;
class Transform;
class Model;
namespace camera
{
	class Camera;
}
class Scene;
class GameObject;
class Entity;
class ModelView;
class Collider;
class BoxCollider;
class OrientedBoxCollider;
class MainScene;
class GameScene;
class WorldManager;
class Player;
class Zombie;

#include "WindowManager.hpp"
#include "Timer.hpp"
#include "Constants.hpp"
#include "Transform.hpp"
#include "Camera.hpp"
#include "Scene.hpp"
#include "Collider.hpp"
#include "GameObject.hpp"
#include "Entity.hpp"
#include "ModelView.hpp"

float RandomizeColour();

#endif
