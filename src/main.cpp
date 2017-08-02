#include "pch.h"
#include "Tests.h"
#include "CEngine.h"

int main( int argc, char* argv[] ) {
	RunTests();

	CEngine engine;

	if ( !engine.Init() ) {
		return -1;
	}

	engine.BeginUpdateLoop();

	engine.Shutdown();

	return 0;
}
