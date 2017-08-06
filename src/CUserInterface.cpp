#include "pch.h"
#include "CUserInterface.h"
#include "CInputManager.h"
#include "CSceneManager.h"

#include "SDL_syswm.h"
#include "imgui.h"

#ifdef __EMSCRIPTEN__
#include <GLES3/gl3.h>
#include <GLES3/gl2ext.h>
#else
#include "GL\gl3w.h"
#endif // __EMSCRIPTEN__

// Data
static GLuint       g_FontTexture = 0;
static int          g_ShaderHandle = 0, g_VertHandle = 0, g_FragHandle = 0;
static int          g_AttribLocationTex = 0, g_AttribLocationProjMtx = 0;
static int          g_AttribLocationPosition = 0, g_AttribLocationUV = 0, g_AttribLocationColor = 0;
static unsigned int g_VboHandle = 0, g_VaoHandle = 0, g_ElementsHandle = 0;

void ImGui_Impl_RenderDrawLists( ImDrawData* draw_data ) {
	// Avoid rendering when minimized, scale coordinates for retina displays (screen coordinates != framebuffer coordinates)
	ImGuiIO& io = ImGui::GetIO();
	int fb_width = (int)(io.DisplaySize.x * io.DisplayFramebufferScale.x);
	int fb_height = (int)(io.DisplaySize.y * io.DisplayFramebufferScale.y);
	if ( fb_width == 0 || fb_height == 0 )
		return;
	draw_data->ScaleClipRects( io.DisplayFramebufferScale );

	// Backup GL state
	GLint last_active_texture; glGetIntegerv( GL_ACTIVE_TEXTURE, &last_active_texture );
	glActiveTexture( GL_TEXTURE0 );
	GLint last_program; glGetIntegerv( GL_CURRENT_PROGRAM, &last_program );
	GLint last_texture; glGetIntegerv( GL_TEXTURE_BINDING_2D, &last_texture );
	GLint last_array_buffer; glGetIntegerv( GL_ARRAY_BUFFER_BINDING, &last_array_buffer );
	GLint last_element_array_buffer; glGetIntegerv( GL_ELEMENT_ARRAY_BUFFER_BINDING, &last_element_array_buffer );
	GLint last_vertex_array; glGetIntegerv( GL_VERTEX_ARRAY_BINDING, &last_vertex_array );
	GLint last_blend_src_rgb; glGetIntegerv( GL_BLEND_SRC_RGB, &last_blend_src_rgb );
	GLint last_blend_dst_rgb; glGetIntegerv( GL_BLEND_DST_RGB, &last_blend_dst_rgb );
	GLint last_blend_src_alpha; glGetIntegerv( GL_BLEND_SRC_ALPHA, &last_blend_src_alpha );
	GLint last_blend_dst_alpha; glGetIntegerv( GL_BLEND_DST_ALPHA, &last_blend_dst_alpha );
	GLint last_blend_equation_rgb; glGetIntegerv( GL_BLEND_EQUATION_RGB, &last_blend_equation_rgb );
	GLint last_blend_equation_alpha; glGetIntegerv( GL_BLEND_EQUATION_ALPHA, &last_blend_equation_alpha );
	GLint last_viewport[4]; glGetIntegerv( GL_VIEWPORT, last_viewport );
	GLint last_scissor_box[4]; glGetIntegerv( GL_SCISSOR_BOX, last_scissor_box );
	GLboolean last_enable_blend = glIsEnabled( GL_BLEND );
	GLboolean last_enable_cull_face = glIsEnabled( GL_CULL_FACE );
	GLboolean last_enable_depth_test = glIsEnabled( GL_DEPTH_TEST );
	GLboolean last_enable_scissor_test = glIsEnabled( GL_SCISSOR_TEST );

	// Setup render state: alpha-blending enabled, no face culling, no depth testing, scissor enabled
	glEnable( GL_BLEND );
	glBlendEquation( GL_FUNC_ADD );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	glDisable( GL_CULL_FACE );
	glDisable( GL_DEPTH_TEST );
	glEnable( GL_SCISSOR_TEST );

	// Setup viewport, orthographic projection matrix
	glViewport( 0, 0, (GLsizei)fb_width, (GLsizei)fb_height );
	const float ortho_projection[4][4] =
	{
		{ 2.0f / io.DisplaySize.x, 0.0f,                     0.0f,  0.0f },
		{ 0.0f,                    2.0f / -io.DisplaySize.y, 0.0f,  0.0f },
		{ 0.0f,                    0.0f,                     -1.0f, 0.0f },
		{ -1.0f,                   1.0f,                     0.0f,  1.0f },
	};
	glUseProgram( g_ShaderHandle );
	glUniform1i( g_AttribLocationTex, 0 );
	glUniformMatrix4fv( g_AttribLocationProjMtx, 1, GL_FALSE, &ortho_projection[0][0] );
	glBindVertexArray( g_VaoHandle );

	for ( int n = 0; n < draw_data->CmdListsCount; n++ ) {
		const ImDrawList* cmd_list = draw_data->CmdLists[n];
		const ImDrawIdx* idx_buffer_offset = 0;

		glBindBuffer( GL_ARRAY_BUFFER, g_VboHandle );
		glBufferData( GL_ARRAY_BUFFER, (GLsizeiptr)cmd_list->VtxBuffer.Size * sizeof( ImDrawVert ), (const GLvoid*)cmd_list->VtxBuffer.Data, GL_STREAM_DRAW );

		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, g_ElementsHandle );
		glBufferData( GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)cmd_list->IdxBuffer.Size * sizeof( ImDrawIdx ), (const GLvoid*)cmd_list->IdxBuffer.Data, GL_STREAM_DRAW );

		for ( int cmd_i = 0; cmd_i < cmd_list->CmdBuffer.Size; cmd_i++ ) {
			const ImDrawCmd* pcmd = &cmd_list->CmdBuffer[cmd_i];
			if ( pcmd->UserCallback ) {
				pcmd->UserCallback( cmd_list, pcmd );
			}
			else {
				glBindTexture( GL_TEXTURE_2D, (GLuint)(intptr_t)pcmd->TextureId );
				glScissor( (int)pcmd->ClipRect.x, (int)(fb_height - pcmd->ClipRect.w), (int)(pcmd->ClipRect.z - pcmd->ClipRect.x), (int)(pcmd->ClipRect.w - pcmd->ClipRect.y) );
				glDrawElements( GL_TRIANGLES, (GLsizei)pcmd->ElemCount, sizeof( ImDrawIdx ) == 2 ? GL_UNSIGNED_SHORT : GL_UNSIGNED_INT, idx_buffer_offset );
			}
			idx_buffer_offset += pcmd->ElemCount;
		}
	}

	// Restore modified GL state
	glUseProgram( last_program );
	glBindTexture( GL_TEXTURE_2D, last_texture );
	glActiveTexture( last_active_texture );
	glBindVertexArray( last_vertex_array );
	glBindBuffer( GL_ARRAY_BUFFER, last_array_buffer );
	glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, last_element_array_buffer );
	glBlendEquationSeparate( last_blend_equation_rgb, last_blend_equation_alpha );
	glBlendFuncSeparate( last_blend_src_rgb, last_blend_dst_rgb, last_blend_src_alpha, last_blend_dst_alpha );
	if ( last_enable_blend ) glEnable( GL_BLEND ); else glDisable( GL_BLEND );
	if ( last_enable_cull_face ) glEnable( GL_CULL_FACE ); else glDisable( GL_CULL_FACE );
	if ( last_enable_depth_test ) glEnable( GL_DEPTH_TEST ); else glDisable( GL_DEPTH_TEST );
	if ( last_enable_scissor_test ) glEnable( GL_SCISSOR_TEST ); else glDisable( GL_SCISSOR_TEST );
	glViewport( last_viewport[0], last_viewport[1], (GLsizei)last_viewport[2], (GLsizei)last_viewport[3] );
	glScissor( last_scissor_box[0], last_scissor_box[1], (GLsizei)last_scissor_box[2], (GLsizei)last_scissor_box[3] );
}

void ImGui_Impl_CreateFontsTexture() {
	// Build texture atlas
	ImGuiIO& io = ImGui::GetIO();
	unsigned char* pixels;
	int width, height;
	io.Fonts->GetTexDataAsRGBA32( &pixels, &width, &height );   // Load as RGBA 32-bits for OpenGL3 demo because it is more likely to be compatible with user's existing shader.

																// Upload texture to graphics system
	GLint last_texture;
	glGetIntegerv( GL_TEXTURE_BINDING_2D, &last_texture );
	glGenTextures( 1, &g_FontTexture );
	glBindTexture( GL_TEXTURE_2D, g_FontTexture );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
	glPixelStorei( GL_UNPACK_ROW_LENGTH, 0 );
	glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels );

	// Store our identifier
	io.Fonts->TexID = (void *)(intptr_t)g_FontTexture;

	// Restore state
	glBindTexture( GL_TEXTURE_2D, last_texture );
}

bool ImGui_Impl_CreateDeviceObjects() {
	// Backup GL state
	GLint last_texture, last_array_buffer, last_vertex_array;
	glGetIntegerv( GL_TEXTURE_BINDING_2D, &last_texture );
	glGetIntegerv( GL_ARRAY_BUFFER_BINDING, &last_array_buffer );
	glGetIntegerv( GL_VERTEX_ARRAY_BINDING, &last_vertex_array );

	const GLchar *vertex_shader =
		"#version 300 es\n"
		"uniform mat4 ProjMtx;\n"
		"in vec2 Position;\n"
		"in vec2 UV;\n"
		"in vec4 Color;\n"
		"out vec2 Frag_UV;\n"
		"out vec4 Frag_Color;\n"
		"void main() {\n"
		"	Frag_UV = UV;\n"
		"	Frag_Color = Color;\n"
		"	gl_Position = ProjMtx * vec4(Position.xy, 0, 1);\n"
		"}\n";

	const GLchar* fragment_shader =
		"#version 300 es\n"
		"precision mediump float;\n"
		"uniform sampler2D Texture;\n"
		"in vec2 Frag_UV;\n"
		"in vec4 Frag_Color;\n"
		"out vec4 Out_Color;\n"
		"void main() {\n"
		"	Out_Color = Frag_Color * texture( Texture, Frag_UV.st );\n"
		"}\n";

	g_ShaderHandle = glCreateProgram();
	g_VertHandle = glCreateShader( GL_VERTEX_SHADER );
	g_FragHandle = glCreateShader( GL_FRAGMENT_SHADER );
	glShaderSource( g_VertHandle, 1, &vertex_shader, 0 );
	glShaderSource( g_FragHandle, 1, &fragment_shader, 0 );
	glCompileShader( g_VertHandle );
	glCompileShader( g_FragHandle );
	glAttachShader( g_ShaderHandle, g_VertHandle );
	glAttachShader( g_ShaderHandle, g_FragHandle );
	glLinkProgram( g_ShaderHandle );

	g_AttribLocationTex = glGetUniformLocation( g_ShaderHandle, "Texture" );
	g_AttribLocationProjMtx = glGetUniformLocation( g_ShaderHandle, "ProjMtx" );
	g_AttribLocationPosition = glGetAttribLocation( g_ShaderHandle, "Position" );
	g_AttribLocationUV = glGetAttribLocation( g_ShaderHandle, "UV" );
	g_AttribLocationColor = glGetAttribLocation( g_ShaderHandle, "Color" );

	glGenBuffers( 1, &g_VboHandle );
	glGenBuffers( 1, &g_ElementsHandle );

	glGenVertexArrays( 1, &g_VaoHandle );
	glBindVertexArray( g_VaoHandle );
	glBindBuffer( GL_ARRAY_BUFFER, g_VboHandle );
	glEnableVertexAttribArray( g_AttribLocationPosition );
	glEnableVertexAttribArray( g_AttribLocationUV );
	glEnableVertexAttribArray( g_AttribLocationColor );

#define OFFSETOF(TYPE, ELEMENT) ((size_t)&(((TYPE *)0)->ELEMENT))
	glVertexAttribPointer( g_AttribLocationPosition, 2, GL_FLOAT, GL_FALSE, sizeof( ImDrawVert ), (GLvoid*)OFFSETOF( ImDrawVert, pos ) );
	glVertexAttribPointer( g_AttribLocationUV, 2, GL_FLOAT, GL_FALSE, sizeof( ImDrawVert ), (GLvoid*)OFFSETOF( ImDrawVert, uv ) );
	glVertexAttribPointer( g_AttribLocationColor, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof( ImDrawVert ), (GLvoid*)OFFSETOF( ImDrawVert, col ) );
#undef OFFSETOF

	ImGui_Impl_CreateFontsTexture();

	// Restore modified GL state
	glBindTexture( GL_TEXTURE_2D, last_texture );
	glBindBuffer( GL_ARRAY_BUFFER, last_array_buffer );
	glBindVertexArray( last_vertex_array );

	return true;
}

void ImGui_Impl_InvalidateDeviceObjects() {
	if ( g_VaoHandle ) glDeleteVertexArrays( 1, &g_VaoHandle );
	if ( g_VboHandle ) glDeleteBuffers( 1, &g_VboHandle );
	if ( g_ElementsHandle ) glDeleteBuffers( 1, &g_ElementsHandle );
	g_VaoHandle = g_VboHandle = g_ElementsHandle = 0;

	if ( g_ShaderHandle && g_VertHandle ) glDetachShader( g_ShaderHandle, g_VertHandle );
	if ( g_VertHandle ) glDeleteShader( g_VertHandle );
	g_VertHandle = 0;

	if ( g_ShaderHandle && g_FragHandle ) glDetachShader( g_ShaderHandle, g_FragHandle );
	if ( g_FragHandle ) glDeleteShader( g_FragHandle );
	g_FragHandle = 0;

	if ( g_ShaderHandle ) glDeleteProgram( g_ShaderHandle );
	g_ShaderHandle = 0;

	if ( g_FontTexture ) {
		glDeleteTextures( 1, &g_FontTexture );
		ImGui::GetIO().Fonts->TexID = 0;
		g_FontTexture = 0;
	}
}

static const char* ImGui_Impl_GetClipboardText( void* ) {
	return SDL_GetClipboardText();
}

static void ImGui_Impl_SetClipboardText( void*, const char* text ) {
	SDL_SetClipboardText( text );
}

bool CUserInterface::Init() {
	SDL_Log( "Initializing CUserInterface\n" );

	ImGui_Impl_CreateDeviceObjects();

	ImGuiIO& io = ImGui::GetIO();
	io.KeyMap[ImGuiKey_Tab] = SDLK_TAB;                     // Keyboard mapping. ImGui will use those indices to peek into the io.KeyDown[] array.
	io.KeyMap[ImGuiKey_LeftArrow] = SDL_SCANCODE_LEFT;
	io.KeyMap[ImGuiKey_RightArrow] = SDL_SCANCODE_RIGHT;
	io.KeyMap[ImGuiKey_UpArrow] = SDL_SCANCODE_UP;
	io.KeyMap[ImGuiKey_DownArrow] = SDL_SCANCODE_DOWN;
	io.KeyMap[ImGuiKey_PageUp] = SDL_SCANCODE_PAGEUP;
	io.KeyMap[ImGuiKey_PageDown] = SDL_SCANCODE_PAGEDOWN;
	io.KeyMap[ImGuiKey_Home] = SDL_SCANCODE_HOME;
	io.KeyMap[ImGuiKey_End] = SDL_SCANCODE_END;
	io.KeyMap[ImGuiKey_Delete] = SDLK_DELETE;
	io.KeyMap[ImGuiKey_Backspace] = SDLK_BACKSPACE;
	io.KeyMap[ImGuiKey_Enter] = SDLK_RETURN;
	io.KeyMap[ImGuiKey_Escape] = SDLK_ESCAPE;
	io.KeyMap[ImGuiKey_A] = SDLK_a;
	io.KeyMap[ImGuiKey_C] = SDLK_c;
	io.KeyMap[ImGuiKey_V] = SDLK_v;
	io.KeyMap[ImGuiKey_X] = SDLK_x;
	io.KeyMap[ImGuiKey_Y] = SDLK_y;
	io.KeyMap[ImGuiKey_Z] = SDLK_z;

	io.RenderDrawListsFn = ImGui_Impl_RenderDrawLists;
	io.GetClipboardTextFn = ImGui_Impl_GetClipboardText;
	io.SetClipboardTextFn = ImGui_Impl_SetClipboardText;
	io.ClipboardUserData = nullptr;
	io.IniFilename = nullptr;

#ifdef _WIN32
	SDL_SysWMinfo wmInfo;
	SDL_VERSION( &wmInfo.version );
	SDL_GetWindowWMInfo( g_Window, &wmInfo );
	io.ImeWindowHandle = wmInfo.info.win.window;
#endif

	return true;
}

void CUserInterface::Shutdown() {
	ImGui_Impl_InvalidateDeviceObjects();
	ImGui::Shutdown();
}

bool CUserInterface::ProcessEvent( SDL_Event& e ) {
	ImGuiIO& io = ImGui::GetIO();
	switch ( e.type ) {
	case SDL_TEXTINPUT:
	{
		io.AddInputCharactersUTF8( e.text.text );
		return true;
	}
	case SDL_KEYDOWN:
	case SDL_KEYUP:
	{
		SDL_Keymod modState = SDL_GetModState();
		int key = e.key.keysym.sym & ~SDLK_SCANCODE_MASK;
		io.KeysDown[key] = (e.type == SDL_KEYDOWN);
		io.KeyShift = ((modState & KMOD_SHIFT) != 0);
		io.KeyCtrl = ((modState & KMOD_CTRL) != 0);
		io.KeyAlt = ((modState & KMOD_ALT) != 0);
		io.KeySuper = ((modState & KMOD_GUI) != 0);
		return true;
	}
	}
	
	return false;
}

void CUserInterface::RunFrame( const float dt, CInputManager& inputManager, CSceneManager& sceneManager ) {
	ImGuiIO& io = ImGui::GetIO();

	// Setup display size (every frame to accommodate for window resizing)
	int display_w, display_h;
	SDL_GL_GetDrawableSize( g_Window, &display_w, &display_h );
	io.DisplaySize = ImVec2( (float)WindowWidth, (float)WindowHeight );
	io.DisplayFramebufferScale = ImVec2( WindowWidth > 0 ? ((float)display_w / WindowWidth) : 0, WindowHeight > 0 ? ((float)display_h / WindowHeight) : 0 );

	io.DeltaTime = dt;
	
	// Setup inputs
	if ( SDL_GetWindowFlags( g_Window ) & SDL_WINDOW_MOUSE_FOCUS ) {
		io.MousePos = inputManager.GetMousePosition();
	}
	else {
		ImVec2( -1, -1 );
	}

	io.MouseDown[0] = inputManager.MouseButtonIsDown( EMouseButton::LEFT );
	io.MouseDown[1] = inputManager.MouseButtonIsDown( EMouseButton::RIGHT );
	io.MouseDown[2] = inputManager.MouseButtonIsDown( EMouseButton::MIDDLE );
	io.MouseDown[3] = inputManager.MouseButtonIsDown( EMouseButton::FOUR );
	io.MouseDown[4] = inputManager.MouseButtonIsDown( EMouseButton::FIVE );
	io.MouseWheel = inputManager.GetMouseWheel().y;
	
	ImGui::NewFrame();

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
