#include "CRenderer.h"
#include "CUserInterface.h"
#include "CSceneManager.h"

#include "Tests.h"

SDL_Window* g_Window = nullptr;
Vec2 g_MousePosition = Vec2( 0, 0 );
bool g_bMouseMovedThisFrame = false;
bool g_MouseButton[3] = { false, false, false };
bool g_MouseButtonDownThisFrame[3] = { false, false, false };
bool g_MouseButtonUpThisFrame[3] = { false, false, false };

const unsigned char* g_KeyboardState;

static CRenderer g_Renderer;
static CUserInterface g_UserInterface;
static CSceneManager g_SceneManager;

static bool bQuitRequested = false;

int Init() {
	SDL_SetMainReady();
	if ( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER ) != 0 ) {
		SDL_LogError( SDL_LOG_CATEGORY_APPLICATION, "Unable to initialize SDL: %s", SDL_GetError() );
		return false;
	}

	SDL_Rect desktopRect;
	if ( SDL_GetDisplayBounds( 0, &desktopRect ) != 0 ) {
		SDL_LogError( SDL_LOG_CATEGORY_APPLICATION, "SDL_GetDisplayBounds failed: %s", SDL_GetError() );
		return false;
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
		return false;
	}

	if ( !g_Renderer.Init() ||
		!g_UserInterface.Init() ||
		!g_SceneManager.Init() ) {
		return false;
	}

	return true;
}

void RunFrame() {
	g_bMouseMovedThisFrame = false;
	g_MouseButtonDownThisFrame[0] = false;
	g_MouseButtonDownThisFrame[1] = false;
	g_MouseButtonDownThisFrame[2] = false;
	g_MouseButtonUpThisFrame[0] = false;
	g_MouseButtonUpThisFrame[1] = false;
	g_MouseButtonUpThisFrame[2] = false;

	SDL_Event event;
	while ( SDL_PollEvent( &event ) ) {
		g_UserInterface.ProcessEvent( &event );
		switch ( event.type ) {
		case SDL_QUIT:
			bQuitRequested = true;
			break;
		case SDL_MOUSEBUTTONDOWN:
			if ( event.button.button == SDL_BUTTON_LEFT ) {
				g_MouseButtonDownThisFrame[0] = true;
				g_MouseButton[0] = true;
			}
			break;
		case SDL_MOUSEBUTTONUP:
			if ( event.button.button == SDL_BUTTON_LEFT ) {
				g_MouseButton[0] = false;
				g_MouseButtonUpThisFrame[0] = true;
			}
			break;
		case SDL_MOUSEMOTION:
			g_bMouseMovedThisFrame = true;
			break;
		}
	}

	int x, y;
	SDL_GetMouseState( &x, &y );
	g_MousePosition.x = (float)x;
	g_MousePosition.y = (float)y;

	g_KeyboardState = SDL_GetKeyboardState( NULL );
	
	g_SceneManager.GetCurrentScene()->OnUpdate();
}

int main( int argc, char* argv[] ) {
	if ( !Init() ) {
		return -1;
	}

	RunTests();

	while ( !bQuitRequested ) {
		RunFrame();
		g_UserInterface.RunFrame( g_SceneManager );
		g_Renderer.RunFrame( g_SceneManager, g_UserInterface );

		/*if ( fps.get_ticks() < 1000 / FRAMES_PER_SECOND ) {
			SDL_Delay( (1000 / FRAMES_PER_SECOND) - fps.get_ticks() );
		}*/
	}

	g_SceneManager.Shutdown();
	g_UserInterface.Shutdown();
	g_Renderer.Shutdown();
	SDL_DestroyWindow( g_Window );
	SDL_Quit();

	return 0;
}
