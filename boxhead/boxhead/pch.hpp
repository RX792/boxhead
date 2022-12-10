#pragma once
#include "stdafx.hpp"

#ifndef __PCH__
#define __PCH__

#include <OpenGL.hpp>
#include <Pipeline.hpp>
#include <Uniform.hpp>

#include "Timer.hpp"
#include "Constants.hpp"
#include "Transform.hpp"

class Framework;
class Timer;
class WindowManager;
class Scene;
class MainScene;
class GameScene;
class MapManager;
class Transform;
class GameObject;
class Entity;
class Camera;
class Collider;
class BoxCollider;
class OrientedBoxCollider;
class Player;
class Zombie;

float RandomizeColour();

#endif
