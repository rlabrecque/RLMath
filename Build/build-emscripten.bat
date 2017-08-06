mkdir Output/html 2>nul
em++ -std=c++1z -O3 --emrun ^
-s USE_SDL=2 -s USE_WEBGL2=1 -s DISABLE_EXCEPTION_CATCHING=0 ^
-I"../src/" -I"../src/RLMath/" -I"../src/ThirdParty/" -I"../src/Scenes/" -I"../src/ThirdParty/imgui/" -I"../src/ThirdParty/lest/" ^
..\src\pch.cpp ^
..\src\CEngine.cpp ^
..\src\Scenes\CGeometryPlayground.cpp ^
..\src\Scenes\CHomingMissile.cpp ^
..\src\CInputManager.cpp ^
..\src\CRenderer.cpp ^
..\src\CSceneManager.cpp ^
..\src\Scenes\CSierpinskiTriangle.cpp ^
..\src\CUserInterface.cpp ^
..\src\ThirdParty\GL\gl3w.cpp ^
..\src\ThirdParty\imgui\imgui.cpp ^
..\src\ThirdParty\imgui\imgui_draw.cpp ^
..\src\ThirdParty\imgui\examples\sdl_opengl3_example\imgui_impl_sdl_gl3.cpp ^
..\src\main.cpp ^
..\src\RLMath\Matrix.cpp ^
..\src\Tests.cpp ^
..\src\RLMath\Vectors.cpp ^
-o Output/html/index.html