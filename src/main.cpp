#include "pch.h"
#include "Tests.h"
#include "CEngine.h"

int main( int argc, char* argv[] ) {
	RunTests();

	CEngine engine;

	if ( !engine.Init() ) {
		return -1;
	}

#ifdef __EMSCRIPTEN__
	static CEngine* pEngine = &engine;
	emscripten_set_main_loop( [] { pEngine->OnUpdate(); }, 0, true );
#else
	while ( engine.OnUpdate() ) {}
#endif

	engine.Shutdown();

	return 0;
}
