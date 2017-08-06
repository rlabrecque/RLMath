#include "pch.h"
#include "CEngine.h"

SDL_Window* g_Window = nullptr;

bool CEngine::Init() {
	SDL_Log( "Initializing CEngine\n" );

	SDL_SetMainReady();
	if ( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER ) != 0 ) {
		SDL_LogError( SDL_LOG_CATEGORY_APPLICATION, "Unable to initialize SDL: %s", SDL_GetError() );
		return false;
	}

	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
	SDL_GL_SetAttribute( SDL_GL_DEPTH_SIZE, 24 );
	SDL_GL_SetAttribute( SDL_GL_STENCIL_SIZE, 8 );
#ifdef __EMSCRIPTEN__
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 2 );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 2 );
#else
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MAJOR_VERSION, 4 );
	SDL_GL_SetAttribute( SDL_GL_CONTEXT_MINOR_VERSION, 3 );
#endif // __EMSCRIPTEN__

	g_Window = SDL_CreateWindow( "RLMath Test Application", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WindowWidth, WindowHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE );
	if ( !g_Window ) {
		SDL_LogError( SDL_LOG_CATEGORY_APPLICATION, "SDL_CreateWindow failed: %s", SDL_GetError() );
		return false;
	}
	
	if ( !m_pInputManager.Init() ) {
		SDL_LogError( SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize CInputManager\n" );
		return false;
	}

	if ( !m_pRenderer.Init() ) {
		SDL_LogError( SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize CRenderer\n" );
		return false;
	}

	if ( !m_pUserInterface.Init() ) {
		SDL_LogError( SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize CUserInterface\n" );
		return false;
	}

	if ( !m_pSceneManager.Init() ) {
		SDL_LogError( SDL_LOG_CATEGORY_APPLICATION, "Failed to initialize CSceneManager\n" );
		return false;
	}

	SDL_Log( "Successfully initialized.\n" );
	return true;
}

void CEngine::Shutdown() {
	m_pSceneManager.Shutdown();
	m_pUserInterface.Shutdown();
	m_pRenderer.Shutdown();
	m_pInputManager.Shutdown();

	SDL_DestroyWindow( g_Window );
	SDL_Quit();
}

bool CEngine::OnUpdate() {
	m_pInputManager.BeginFrame();

	SDL_Event e;
	while ( SDL_PollEvent( &e ) ) {
		if ( e.type == SDL_QUIT ) {
#ifdef __EMSCRIPTEN__
			emscripten_cancel_main_loop();
#endif // __EMSCRIPTEN__
			return false;
		}

		m_pUserInterface.ProcessEvent( e );
		m_pInputManager.ProcessEvent( e );
	}

	m_pSceneManager.GetCurrentScene()->OnUpdate( m_pInputManager );
	m_pUserInterface.RunFrame( m_pSceneManager );
	m_pRenderer.RunFrame( m_pSceneManager, m_pUserInterface );

	/*if ( fps.get_ticks() < 1000 / FRAMES_PER_SECOND ) {
	SDL_Delay( (1000 / FRAMES_PER_SECOND) - fps.get_ticks() );
	}*/

	return true;
}
