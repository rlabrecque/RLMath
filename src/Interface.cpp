#include "Interface.h"

#define IMGUI_DISABLE_TEST_WINDOWS
#include "imgui.h"
#include "examples\sdl_opengl3_example\imgui_impl_sdl_gl3.h"
#undef IMGUI_DISABLE_TEST_WINDOWS

Vec4 g_ClearColor = Vec4( 0.75f, 0.75f, 0.75f, 1.0f );
Vec4 g_DrawColor = Vec4( 1.0f, 1.0f, 1.0f, 1.0f );

void Interface_Init() {
	ImGui_ImplSdlGL3_Init( g_Window );
}

void Interface_Shutdown() {
	ImGui_ImplSdlGL3_Shutdown();
}

void Interface_ProcessEvent( SDL_Event* event ) {
	ImGui_ImplSdlGL3_ProcessEvent( event );
}

void Interface_RunFrame() {
	ImGui_ImplSdlGL3_NewFrame( g_Window );

	ImGui::SetNextWindowPos( Vec2( WindowWidth - 320, 0 ), ImGuiSetCond_Always );
	ImGui::SetNextWindowSize( Vec2( 320, (float)WindowHeight), ImGuiSetCond_Always );
	if ( !ImGui::Begin( "Right Panel", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings ) ) {
		ImGui::End();
		return;
	}
	ImGui::Text( "Frametime: %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate );
	ImGui::Separator();
	ImGui::ColorEdit3( "Clear Color", g_ClearColor.data );
	ImGui::ColorEdit3( "Draw Color", g_DrawColor.data );
	ImGui::Separator();

	if(ImGui::CollapsingHeader( "Geometry Playground", ImGuiTreeNodeFlags_DefaultOpen)) {
		if ( ImGui::Button( "Clear Geometry" ) ) {
			ClearGeometry();
		}

		ImGui::RadioButton( "Point", (int*)&mode, k_EGeometryInsertMode_Point ); ImGui::SameLine();
		ImGui::RadioButton( "Ray", (int*)&mode, k_EGeometryInsertMode_Ray ); ImGui::SameLine();
		ImGui::RadioButton( "Plane", (int*)&mode, k_EGeometryInsertMode_Plane ); ImGui::SameLine();
		ImGui::RadioButton( "Rect", (int*)&mode, k_EGeometryInsertMode_Rect ); ImGui::SameLine();
		ImGui::RadioButton( "Circle", (int*)&mode, k_EGeometryInsertMode_Circle );
	}

	if ( ImGui::Button( "Draw that recursive trangle" )) {
		bDrawSierpinski = !bDrawSierpinski;
	}

	ImGui::End();
}

void Interface_Draw() {
	ImGui::Render();
}
