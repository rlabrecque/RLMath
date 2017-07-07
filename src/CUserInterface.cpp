#include "CUserInterface.h"
#include "CSceneManager.h"

#define IMGUI_DISABLE_TEST_WINDOWS
#include "imgui.h"
#include "examples\sdl_opengl3_example\imgui_impl_sdl_gl3.h"
#undef IMGUI_DISABLE_TEST_WINDOWS

bool CUserInterface::Init() {
	return ImGui_ImplSdlGL3_Init( g_Window );
}

void CUserInterface::Shutdown() {
	ImGui_ImplSdlGL3_Shutdown();
}

void CUserInterface::ProcessEvent( SDL_Event* event ) {
	ImGui_ImplSdlGL3_ProcessEvent( event );
}

void CUserInterface::RunFrame( CSceneManager& sceneManager ) {
	ImGui_ImplSdlGL3_NewFrame( g_Window );

	ImGui::SetNextWindowPos( Vec2( WindowWidth - 320, 0 ), ImGuiSetCond_Always );
	ImGui::SetNextWindowSize( Vec2( 320, (float)WindowHeight), ImGuiSetCond_Always );
	if ( !ImGui::Begin( "Right Panel", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings ) ) {
		ImGui::End();
		return;
	}

	ImGui::Text( "Frametime: %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate );
	ImGui::Separator();

	for ( unsigned int i = 0; i < sceneManager.GetNumScenes(); ++i ) {
		CBaseScene* scene = sceneManager.GetScenes()[i];

		ImGui::SetNextTreeNodeOpen( i == sceneManager.GetCurrentSceneIndex() );
		bool bIsOpen = ImGui::CollapsingHeader( scene->GetName() );
		if ( i != sceneManager.GetCurrentSceneIndex() && bIsOpen ) {
			sceneManager.ChangeScene(i);
		}

		if ( bIsOpen ) {
			scene->OnInterface();
		}
	}

	ImGui::End();
}

void CUserInterface::Draw() {
	ImGui::Render();
}
