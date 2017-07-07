#include "Renderer.h"
#include "Interface.h"
#include "tests.h"

SDL_Window* g_Window = nullptr;
std::unordered_map<Vec2, Vec4> points;
std::unordered_map<Ray, Vec4> rays;
EGeometryInsertMode mode = k_EGeometryInsertMode_Point;

bool bPlacingRay = false;
bool bDrawSierpinski = false;
Vec2 RayPosition;
Vec2 MousePosition;

void ClearGeometry() {
	points.clear();
	rays.clear();
}

static bool g_bMouseMovedThisFrame = false;
static bool g_MouseButton[3] = { false, false, false };
static bool g_MouseButtonDownThisFrame[3] = { false, false, false };
static bool g_MouseButtonUpThisFrame[3] = { false, false, false };

int Init() {
	SDL_SetMainReady();
	if ( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER ) != 0 ) {
		SDL_LogError( SDL_LOG_CATEGORY_APPLICATION, "Unable to initialize SDL: %s", SDL_GetError() );
		return 1;
	}

	SDL_Rect desktopRect;
	if ( SDL_GetDisplayBounds( 0, &desktopRect ) != 0 ) {
		SDL_LogError( SDL_LOG_CATEGORY_APPLICATION, "SDL_GetDisplayBounds failed: %s", SDL_GetError() );
		return 1;
	}

	SDL_GL_SetAttribute( SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
	SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 24 );
	SDL_GL_SetAttribute( SDL_GL_STENCIL_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 3 );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3 );

	g_Window = SDL_CreateWindow( "RLMath Test Application", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WindowWidth, WindowHeight, SDL_WINDOW_OPENGL );
	if ( !g_Window ) {
		SDL_LogError( SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateWindow failed: %s", SDL_GetError() );
		return 3;
	}

	Renderer_Init();
	Interface_Init();

	return 0;
}

void RunFrame() {
	static EGeometryInsertMode lastGeometryInsertMode;
	if ( mode != lastGeometryInsertMode ) {
		printf( "Cleared\n" );
		bPlacingRay = false;
		lastGeometryInsertMode = mode;
	}
	int x, y;
	SDL_GetMouseState( &x, &y );
	MousePosition.x = (float)x;
	MousePosition.y = (float)y;

	if ( x > WindowWidth - 320 ) {
		return;
	}

	if ( g_MouseButton[0] ) {
		switch ( mode ) {
		case k_EGeometryInsertMode_Point:
			if ( g_bMouseMovedThisFrame ) {
				points[MousePosition] = g_DrawColor;
			}
			break;
		}
	}

	if ( g_MouseButtonDownThisFrame[0] ) {
		switch ( mode ) {
		case k_EGeometryInsertMode_Ray:
			bPlacingRay = true;
			RayPosition = MousePosition;
			printf( "Created a ray at: %s\n", RayPosition.ToString() );
			break;
		}
	}

	if ( g_MouseButtonUpThisFrame[0] ) {
		switch ( mode ) {
		case k_EGeometryInsertMode_Point:
			break;
		case k_EGeometryInsertMode_Ray:
			printf( "RayPosition: %s\n", RayPosition.ToString() );
			rays[Ray( RayPosition, (RayPosition + ((MousePosition - RayPosition).normalized() * FLT_MAX)) )] = g_DrawColor;
			bPlacingRay = false;
			printf( "RayPosition: %s\n", RayPosition.ToString() );
			printf( "MousePosition: %s\n", MousePosition.ToString() );
			printf( "Pointing the ray to: %s\n", (MousePosition - RayPosition).normalized().ToString() );
			break;
		}
	}
}

int main( int argc, char* argv[] ) {
	{
		int ret = Init();
		if ( ret != 0 ) {
			return ret;
		}
	}

	RunTests();

	bool bQuitRequested = false;
	while ( !bQuitRequested ) {
		g_bMouseMovedThisFrame = false;
		g_MouseButtonDownThisFrame[0] = false;
		g_MouseButtonDownThisFrame[1] = false;
		g_MouseButtonDownThisFrame[2] = false;
		g_MouseButtonUpThisFrame[0] = false;
		g_MouseButtonUpThisFrame[1] = false;
		g_MouseButtonUpThisFrame[2] = false;

		SDL_Event event;
		while ( SDL_PollEvent( &event ) ) {
			Interface_ProcessEvent( &event );
			switch ( event.type ) {
			case SDL_QUIT:
				bQuitRequested = true;
				break;
			case SDL_MOUSEBUTTONDOWN:
				if ( event.button.button == SDL_BUTTON_LEFT) {
					g_MouseButtonDownThisFrame[0] = true;
					g_MouseButton[0] = true;
					SDL_Log( "DOWN at: %d, %d!\n", event.button.x, event.button.y );
				}
				break;
			case SDL_MOUSEBUTTONUP:
				if ( event.button.button == SDL_BUTTON_LEFT ) {
					g_MouseButton[0] = false;
					g_MouseButtonUpThisFrame[0] = true;
					SDL_Log( "UP!\n" );
				}
				break;
			case SDL_MOUSEMOTION:
				g_bMouseMovedThisFrame = true;
				break;
			}
		}

		RunFrame();

		Interface_RunFrame();
		Renderer_RunFrame();

		/*if ( fps.get_ticks() < 1000 / FRAMES_PER_SECOND ) {
			SDL_Delay( (1000 / FRAMES_PER_SECOND) - fps.get_ticks() );
		}*/
	}

	Renderer_Shutdown();
	SDL_DestroyWindow( g_Window );
	SDL_Quit();

	return 0;
}
