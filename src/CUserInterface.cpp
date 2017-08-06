#include "pch.h"
#include "CUserInterface.h"
#include "CSceneManager.h"

#include "imgui.h"
#include "examples\sdl_opengl3_example\imgui_impl_sdl_gl3.h"

bool CUserInterface::Init() {
	SDL_Log( "Initializing CUserInterface\n" );
	return ImGui_Impl_Init( g_Window );
}

void CUserInterface::Shutdown() {
	ImGui_Impl_Shutdown();
}

void CUserInterface::ProcessEvent( SDL_Event& event ) {
	ImGui_Impl_ProcessEvent( &event );
}

void CUserInterface::RunFrame( CSceneManager& sceneManager ) {
	ImGui_Impl_NewFrame( g_Window );

	ImGui::SetNextWindowPos( Vec2( WindowWidth - 320, 0 ), ImGuiSetCond_Always );
	ImGui::SetNextWindowSize( Vec2( 320, (float)WindowHeight), ImGuiSetCond_Always );
	if ( !ImGui::Begin( "Right Panel", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings ) ) {
		ImGui::End();
		return;
	}

	ImGui::Text( "Frametime: %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate );
	ImGui::Separator();

	const unsigned int nScenes = sceneManager.GetNumScenes();
	const unsigned int currentSceneIndex = sceneManager.GetCurrentSceneIndex();
	const auto&& scenes = sceneManager.GetScenes();
	for ( unsigned int i = 0; i < nScenes; ++i ) {
		CBaseScene* scene = scenes[i];

		ImGui::SetNextTreeNodeOpen( i == currentSceneIndex );
		bool bIsOpen = ImGui::CollapsingHeader( scene->GetName() );
		if ( i != currentSceneIndex && bIsOpen ) {
			sceneManager.ChangeScene(i);
		}

		if ( bIsOpen ) {
			scene->OnInterface();
		}
	}

	ImGui::End();
}

void CUserInterface::Render() {
	ImGui::Render();
}
