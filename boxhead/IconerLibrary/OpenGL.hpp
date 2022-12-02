#pragma once
#include "BasicBlobs.hpp"

namespace ogl
{
	class Pipeline;
	class Shader;
	class VertexStream;
	class Buffer;
	class Uniform;
	class Attribute;

	using Vertex2D = blob::Vertex2D;
	using Vertex = blob::Vertex;

	enum class PRIMITIVE_TYPES : GLenum
	{
		POINTS = GL_POINTS							// 0x0000
		, LINES = GL_LINES
		, LINE_STRIP = GL_LINE_STRIP				// 0x0003
		, TRIANGLES = GL_TRIANGLES					// 0x0004
		, TRIANGLE_STRIP = GL_TRIANGLE_STRIP		// 0x0005
		, TRIANGLE_FAN = GL_TRIANGLE_FAN			// 0x0006
		, QUADS = GL_QUADS							// 0x0007
		, QUAD_STRIP = GL_QUAD_STRIP				// 0x0008
		, POLYGON = GL_POLYGON						// 0x0009
		, POLYGON_STIPPLE = GL_POLYGON_STIPPLE_BIT	// 0x00000010
	};

	using CallbackRenderer = void (*)(void);
	using CallbackViewport = void (*)(int width, int height);
	using CallbackKeyboard = void (*)(unsigned char key, int mouse_x, int mouse_y);
	using CallbackSpecialKeyboard = void (*)(int key, int mouse_x, int mouse_y);
	using CallbackMouse = void (*)(int btn, int state, int screen_x, int screen_y);
	using CallbackMouseMove = void (*)(int mouse_x, int mouse_y);
	using CallbackTimer = void (*)(int delta_time_ms);

	static int gl_width{}, gl_height{};
	static Colour background_color = { 0.0f, 0.0f, 0.0f, 1.0f };
	static CallbackTimer gl_local_timer = nullptr;
	static CallbackRenderer gl_local_renderer = nullptr;

	inline void TurnOnOption(const GLenum& option)
	{
		glEnable(option);
	}

	inline void TurnOffOption(const GLenum& option)
	{
		glDisable(option);
	}

	inline void SetBlendMethod(const GLenum& source, const GLenum& dest)
	{
		glBlendFunc(source, dest);
	}

	inline void SetRenderer(CallbackRenderer&& renderer)
	{
		gl_local_renderer = std::forward<CallbackRenderer>(renderer);
	}

	inline void SetRenderer(const CallbackRenderer& renderer)
	{
		gl_local_renderer = renderer;
	}

	inline void SetViewportUpdater(CallbackViewport&& callback)
	{
		glutReshapeFunc(std::forward<CallbackViewport>(callback));
	}

	inline void SetViewportUpdater(const CallbackViewport& callback)
	{
		glutReshapeFunc(callback);
	}

	inline void SetKeyboardMethod(CallbackKeyboard&& callback)
	{
		glutKeyboardFunc(std::forward<CallbackKeyboard>(callback));
	}

	inline void SetKeyboardMethod(const CallbackKeyboard& callback)
	{
		glutKeyboardFunc(callback);
	}

	inline void SetSpecialKeyboardMethod(CallbackSpecialKeyboard&& callback)
	{
		glutSpecialFunc(std::forward<CallbackSpecialKeyboard>(callback));
	}

	inline void SetSpecialKeyboardMethod(const CallbackSpecialKeyboard& callback)
	{
		glutSpecialFunc(callback);
	}

	inline void SetMouseMethod(CallbackMouse&& callback)
	{
		glutMouseFunc(std::forward<CallbackMouse>(callback));
	}

	inline void SetMouseMethod(const CallbackMouse& callback)
	{
		glutMouseFunc(callback);
	}

	inline void SetMouseMoverMethod(CallbackMouseMove&& callback)
	{
		glutMotionFunc(std::forward<CallbackMouseMove>(callback));
	}

	inline void SetMouseMoverMethod(const CallbackMouseMove& callback)
	{
		glutMotionFunc(callback);
	}

	inline void SetTimer(CallbackTimer&& callback, const int& next_ms_time, const int& passed_value = 0)
	{
		gl_local_timer = std::forward<CallbackTimer>(callback);

		glutTimerFunc(next_ms_time, gl_local_timer, passed_value);
	}

	inline void SetTimer(const CallbackTimer& callback, const int& next_ms_time, const int& passed_value = 0)
	{
		gl_local_timer = callback;

		glutTimerFunc(next_ms_time, callback, passed_value);
	}

	inline void SetTimer(const int& next_ms_time, const int& passed_value = 0)
	{
		glutTimerFunc(next_ms_time, gl_local_timer, passed_value);
	}

	inline constexpr bool IsLeftMouseButton(const int& btn) noexcept
	{
		return (GLUT_LEFT_BUTTON == btn);
	}

	inline constexpr bool IsRightMouseButton(const int& btn) noexcept
	{
		return (GLUT_RIGHT_BUTTON == btn);
	}

	inline constexpr bool IsMiddleMouseButton(const int& btn) noexcept
	{
		return (GLUT_MIDDLE_BUTTON == btn);
	}

	inline constexpr bool IsMouseClicked(const int& state) noexcept
	{
		return (GLUT_DOWN == state);
	}

	inline constexpr bool IsMouseReleased(const int& state) noexcept
	{
		return (GLUT_UP == state);
	}

	inline void Refresh()
	{
		glutPostRedisplay();
	}

	inline void Render(const PRIMITIVE_TYPES& primitives, const GLsizei& count, const GLint& first = 0)
	{
		glDrawArrays(static_cast<GLenum>(primitives), first, count);
	}

	inline void RenderIndexed(const PRIMITIVE_TYPES& primitives, const GLsizei& count, GLvoid const* indices = nullptr, const GLenum& type = GL_UNSIGNED_INT)
	{
		glDrawElements(static_cast<GLenum>(primitives), count, type, indices);
	}

	inline void PrimitivesBegin(const GLenum& primitives)
	{
		glBegin(primitives);
	}

	inline void PrimitivesBegin(const PRIMITIVE_TYPES& primitives)
	{
		glBegin(static_cast<GLenum>(primitives));
	}

	inline void PrimitivesEnd()
	{
		glEnd();
		glFlush();
	}

	inline void DrawVertex(float x, float y)
	{
		glVertex2f(x, y);
	}

	inline void DrawVertex(float x, float y, float z)
	{
		glVertex3f(x, y, z);
	}

	inline void DrawVertex(const Point& coords)
	{
		glVertex2f(coords.x, coords.y);
	}

	inline void DrawVertex(const Quad& coords)
	{
		glVertex3f(coords.x, coords.y, coords.z);
	}

	inline void DrawVertex(const Vertex2D& coords)
	{
		glVertex2f(coords.x, coords.y);
	}

	inline void DrawVertex(const Vertex& coords)
	{
		glVertex3f(coords.x, coords.y, coords.z);
	}

	inline void DrawColoredVertex(const Vertex2D& coords)
	{
		glColor4f(coords.r, coords.g, coords.b, coords.a);
		glVertex2f(coords.x, coords.y);
	}

	inline void DrawColoredVertex(const Vertex& coords)
	{
		glColor4f(coords.r, coords.g, coords.b, coords.a);
		glVertex3f(coords.x, coords.y, coords.z);
	}

	inline void DrawSetColor(float r, float g, float b)
	{
		glColor3f(r, g, b);
	}

	inline void DrawSetColor(float r, float g, float b, float a)
	{
		glColor4f(r, g, b, a);
	}

	inline void DrawSetColor(const Vertex2D& vertex)
	{
		const auto r = vertex.r;
		const auto g = vertex.g;
		const auto b = vertex.b;
		const auto a = vertex.a;
		DrawSetColor(r, g, b, a);
	}

	inline void DrawSetColor(const Vertex& vertex)
	{
		const auto r = vertex.r;
		const auto g = vertex.g;
		const auto b = vertex.b;
		const auto a = vertex.a;
		DrawSetColor(r, g, b, a);
	}

	inline void DrawSetColor(const Colour& color)
	{
		DrawSetColor(color.r, color.g, color.b, color.a);
	}

	inline void DrawSetColor(Colour&& color)
	{
		DrawSetColor(std::forward<float>(color.r), std::forward<float>(color.g), std::forward<float>(color.b), std::forward<float>(color.a));
	}

	inline void DrawClearColor(float r, float g, float b, float a)
	{
		glClearColor(r, g, b, a);
	}

	inline void DrawClearColor(const Colour& color)
	{
		DrawClearColor(color.r, color.g, color.b, color.a);
	}

	inline void DrawClearColor(Colour&& color)
	{
		DrawClearColor(std::forward<float>(color.r), std::forward<float>(color.g), std::forward<float>(color.b), std::forward<float>(color.a));
	}

	inline void DrawScreen()
	{
		glutSwapBuffers();
	}

	inline void ClearMasks(const GLbitfield& mask)
	{
		glClear(mask);
	}

	inline void ResetProgram()
	{
		glUseProgram(0);
	}

	inline void DefaultRenderer()
	{
		glLoadIdentity();
		ClearMasks(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		DrawClearColor(background_color);

		gl_local_renderer();

		DrawScreen();
	}

	inline void Awake(int argc, char** argv)
	{
		glutInit(&argc, argv);

		glewExperimental = (GL_TRUE);
	}

	inline void Ready(std::string_view title
		, const int view_width, const int view_height
		, const int viewport_x, const int viewport_y)
	{
		glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
		glutInitWindowSize(view_width, view_height);
		glutInitWindowPosition(viewport_x, viewport_y);
		
		ogl::gl_width = view_width;
		ogl::gl_height = view_height;

		glutCreateWindow(title.data());

		if (glewInit() != GLEW_OK)
		{
			throw std::runtime_error("Unable to initialize GLEW");
		}
		else
		{
			std::cout << "GLEW Initialized\n";
		}
	}

	inline void Start()
	{
		TurnOnOption(GL_BLEND);
		glutDisplayFunc(DefaultRenderer);

		glutMainLoop();
	}

	inline float GetAspectRatio() noexcept
	{
		return static_cast<float>(gl_width) / static_cast<float>(gl_height);
	}
	
	inline constexpr glm::vec3 right = { 1.0f, 0.0f, 0.0f };
	inline constexpr glm::vec3 up = { 0.0f, 1.0f, 0.0f };
	inline constexpr glm::vec3 forward = { 0.0f, 0.0f, 1.0f };
	inline constexpr glm::mat4 identity = glm::mat4{ 1.0f };

	inline glm::mat4 Scale(const glm::mat4& matrix, const float& xs, const float& ys, const float& zs)
	{
		return glm::scale(matrix, { xs, ys, zs });
	}

	inline glm::mat4 Rotate(const glm::mat4& matrix, const float& xr, const float& yr, const float& zr)
	{
		auto result = glm::rotate(matrix, xr, ogl::right);
		result = glm::rotate(result, yr, ogl::up);

		return glm::rotate(result, zr, ogl::forward);
	}

	inline glm::mat4 Rotate(const glm::mat4& matrix, const float (&rotations)[3])
	{
		return Rotate(matrix, rotations[0], rotations[1], rotations[2]);
	}

	inline glm::mat4 Translate(const glm::mat4& matrix, const float& x, const float& y, const float& z)
	{
		return glm::translate(matrix, { x, y, z });
	}

	inline glm::mat4 Translate(const glm::mat4& matrix, const glm::vec3& position)
	{
		return glm::translate(matrix, position);
	}
}
