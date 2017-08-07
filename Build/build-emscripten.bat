SET "EMSCRIPTEN_SDK_PATH=D:\Code\ThirdParty\emsdk-1.35.0-portable-64bit"
SET "OUTPUT_DIR=Output\Emscripten"

call "%EMSCRIPTEN_SDK_PATH%\emsdk_env.bat"

mkdir %OUTPUT_DIR% 2>nul
em++ -std=c++1z -O3 --emrun ^
-s USE_SDL=2 -s USE_WEBGL2=1 -s DISABLE_EXCEPTION_CATCHING=0 ^
-I"../src/" -I"../src/RLMath/" -I"../src/ThirdParty/" -I"../src/Scenes/" -I"../src/ThirdParty/imgui/" -I"../src/ThirdParty/lest/" ^
..\src\CEngine.cpp ^
..\src\CInputManager.cpp ^
..\src\Color.cpp ^
..\src\CUserInterface.cpp ^
..\src\main.cpp ^
..\src\CRenderer.cpp ^
..\src\pch.c ^
..\src\RLMath\Matrix.cpp ^
..\src\RLMath\Vectors.cpp ^
..\src\CSceneManager.cpp ^
..\src\Scenes\CGeometryPlayground.cpp ^
..\src\Scenes\CHTree.cpp ^
..\src\Scenes\CSierpinskiTriangle.cpp ^
..\src\Scenes\CHomingMissile.cpp ^
..\src\Scenes\CSpaceFillingCurves.cpp ^
..\src\Tests.cpp ^
..\src\ThirdParty\GL\gl3w.cpp ^
..\src\ThirdParty\imgui\imgui.cpp ^
..\src\ThirdParty\imgui\imgui_draw.cpp ^
-o "%OUTPUT_DIR%\index.html"