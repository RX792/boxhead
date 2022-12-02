#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <type_traits>
#include <concepts>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <syncstream>
#include <filesystem>
#include <chrono>
#include <ratio>
#include <random>
#include <numbers>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>
#include <array>
#include <tuple>
#include <span>
#include <algorithm>

#define NOMINMAX
#include <GL/glew.h>
#include <GL/wglew.h>
#include <GL/glut.h>
#include <GL/wglew.h>

#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>

#include <glm/glm.hpp>
#include <glm/fwd.hpp>
#include <glm/ext.hpp>

using Path = std::filesystem::path;
