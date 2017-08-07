#include "pch.h"
#include "CRenderer.h"
#include "CSceneManager.h"
#include "CUserInterface.h"

#ifdef __EMSCRIPTEN__
#include <GLES3/gl3.h>
#include <GLES3/gl2ext.h>
#else
#include "GL\gl3w.h"
#endif // __EMSCRIPTEN__

static Vec4 s_DrawColor = Vec4( 1.0f, 1.0f, 1.0f, 1.0f );

static SDL_GLContext s_GLContext;
static unsigned int s_ShaderProgram;
static unsigned int s_PointVBO;
static unsigned int s_LineVBO;
static unsigned int s_TriangleVBO;
static unsigned int s_PointVAO;
static unsigned int s_LineVAO;
static unsigned int s_TriangleVAO;

struct VertexObject {
	Vec2 pos;
	Vec4 color;
};

static int Renderer_Init_Shaders() {
	SDL_Log( "Initializing Shaders\n" );

	const char *vertexShaderSource =
		"#version 300 es\n"
		"uniform vec2 viewPortSize;\n"
		""
		"layout(location = 0) in vec2 position;\n"
		"layout(location = 1) in vec4 vertexInputColor;\n"
		""
		"out vec4 vertexColor;\n"
		""
		"void main() {\n"
		"	gl_PointSize = 1.0f;\n"
		"	gl_Position = vec4( (2.0f * (position.x / viewPortSize.x) - 1.0f), -(2.0f * (position.y / viewPortSize.y) - 1.0f), 0.0f, 1.0f );\n"
		"	vertexColor = vertexInputColor;\n"
		"}\n";

	const char *fragmentShaderSource = 
		"#version 300 es\n"
		"precision mediump float;\n"
		""
		"in vec4 vertexColor;\n"
		"out vec4 FragColor;\n"
		""
		"void main() {\n"
		"FragColor = vertexColor;\n"
		"}\n";

	int  success;
	char infoLog[512];

	unsigned int vertexShader = glCreateShader( GL_VERTEX_SHADER );
	glShaderSource( vertexShader, 1, &vertexShaderSource, nullptr );
	glCompileShader( vertexShader );

	glGetShaderiv( vertexShader, GL_COMPILE_STATUS, &success );
	if ( !success ) {
		glGetShaderInfoLog( vertexShader, sizeof( infoLog ), nullptr, infoLog );
		SDL_LogError( SDL_LOG_CATEGORY_APPLICATION, "Shader Vertex Compilation failed: %s\n", infoLog );
		return false;
	}

	unsigned int fragmentShader = glCreateShader( GL_FRAGMENT_SHADER );
	glShaderSource( fragmentShader, 1, &fragmentShaderSource, nullptr );
	glCompileShader( fragmentShader );
	glGetShaderiv( fragmentShader, GL_COMPILE_STATUS, &success );
	if ( !success ) {
		glGetShaderInfoLog( fragmentShader, sizeof( infoLog ), nullptr, infoLog );
		SDL_LogError( SDL_LOG_CATEGORY_APPLICATION, "Shader Fragment Compilation failed: %s\n", infoLog );
		return false;
	}

	s_ShaderProgram = glCreateProgram();
	glAttachShader( s_ShaderProgram, vertexShader );
	glAttachShader( s_ShaderProgram, fragmentShader );
	glLinkProgram( s_ShaderProgram );
	glGetProgramiv( s_ShaderProgram, GL_LINK_STATUS, &success );
	if ( !success ) {
		glGetProgramInfoLog( s_ShaderProgram, sizeof( infoLog ), nullptr, infoLog );
		SDL_LogError( SDL_LOG_CATEGORY_APPLICATION, "Shader Program Compilation failed: %s\n", infoLog );
		return false;
	}

	glDeleteShader( vertexShader );
	glDeleteShader( fragmentShader );

	return true;
}

bool CRenderer::Init() {
	SDL_Log( "Initializing CRenderer\n" );

	// Create GL Context and initialize it
	s_GLContext = SDL_GL_CreateContext( g_Window );

#ifndef __EMSCRIPTEN__
	gl3wInit();
#endif // !__EMSCRIPTEN__

	glDisable( GL_CULL_FACE );
	glDisable( GL_DEPTH_TEST );
	glEnable( GL_SCISSOR_TEST );
	glEnable( GL_BLEND );
	glBlendEquation( GL_FUNC_ADD );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	if ( !Renderer_Init_Shaders() ) {
		return false;
	}

	glGenBuffers( 1, &s_PointVBO );
	glGenVertexArrays( 1, &s_PointVAO );

	glGenBuffers( 1, &s_LineVBO );
	glGenVertexArrays( 1, &s_LineVAO );

	glGenBuffers( 1, &s_TriangleVBO );
	glGenVertexArrays( 1, &s_TriangleVAO );
	
	glUseProgram( s_ShaderProgram );
	const int vertexPositionLocation = glGetUniformLocation( s_ShaderProgram, "viewPortSize" );
	glUniform2f( vertexPositionLocation, (float)WindowWidth, (float)WindowHeight );

	return true;
}

void CRenderer::Shutdown() {
	glDeleteVertexArrays( 1, &s_PointVAO );
	glDeleteBuffers( 1, &s_PointVBO );
	glDeleteVertexArrays( 1, &s_LineVAO );
	glDeleteBuffers( 1, &s_LineVBO );
	glDeleteVertexArrays( 1, &s_TriangleVAO );
	glDeleteBuffers( 1, &s_TriangleVBO );

	SDL_GL_DeleteContext( s_GLContext );
}

void CRenderer::RunFrame( const float dt, CSceneManager& sceneManager, CUserInterface& userInterface) {
	glViewport( 0, 0, WindowWidth, WindowHeight );
	glClearColor( 0.1f, 0.1f, 0.1f, 1 );
	glClear( GL_COLOR_BUFFER_BIT );

	bInDrawing = true;
	sceneManager.GetCurrentScene()->OnRender(*this);
	bInDrawing = false;

	userInterface.Render();

	SDL_GL_SwapWindow( g_Window );
}

void CRenderer::SetDrawColor( const Vec4 color ) {
	SDL_assert( bInDrawing );

	s_DrawColor = color;
}

void CRenderer::SetDrawColor( const Vec3 color ) {
	SetDrawColor( Vec4( color ) );
}

void CRenderer::SetDrawColor( const float r, const float g, const float b ) {
	SetDrawColor( Vec4( r, g, b, 1 ) );
}

void CRenderer::DrawPoint( const Vec2 point ) {
	SDL_assert( bInDrawing );

	static VertexObject points[1];
	points[0] = { point, s_DrawColor };

	glUseProgram( s_ShaderProgram );
	glBindVertexArray( s_PointVAO );

	glBindBuffer( GL_ARRAY_BUFFER, s_PointVBO );
	glBufferData( GL_ARRAY_BUFFER, sizeof( points ) * sizeof( VertexObject ), &points, GL_STATIC_DRAW );

	glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, sizeof( VertexObject ), nullptr );
	glEnableVertexAttribArray( 0 );

	glVertexAttribPointer( 1, 4, GL_FLOAT, GL_FALSE, sizeof( VertexObject ), (void*)(sizeof(Vec2)) );
	glEnableVertexAttribArray( 1 );

	glDrawArrays( GL_POINTS, 0, (sizeof( points ) / sizeof( VertexObject )) );
}

void CRenderer::DrawLine( const Vec2 start, const Vec2 end ) {
	DrawLine( start, end, s_DrawColor, s_DrawColor );
}

void CRenderer::DrawLine( const Vec2 start, const Vec2 end, const Vec4 startColor, const Vec4 endColor ) {
	SDL_assert( bInDrawing );

	static VertexObject points[3];
	points[0] = { start, startColor };
	points[1] = { end, endColor };

	glUseProgram( s_ShaderProgram );
	glBindVertexArray( s_LineVAO );

	glBindBuffer( GL_ARRAY_BUFFER, s_LineVBO );
	glBufferData( GL_ARRAY_BUFFER, sizeof( points ), &points, GL_STATIC_DRAW );

	glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, sizeof( VertexObject ), nullptr );
	glEnableVertexAttribArray( 0 );

	glVertexAttribPointer( 1, 4, GL_FLOAT, GL_FALSE, sizeof( VertexObject ), (void*)(sizeof( Vec2 )) );
	glEnableVertexAttribArray( 1 );

	glDrawArrays( GL_LINES, 0, (sizeof( points ) / sizeof( VertexObject )) );
}

void CRenderer::DrawTriangle( const Vec2 topVertex, const Vec2 bottomRightVertex, const Vec2 bottomLeftVertex ) {
	DrawTriangle( topVertex, bottomRightVertex, bottomLeftVertex, s_DrawColor, s_DrawColor, s_DrawColor );
}

void CRenderer::DrawTriangle( const Vec2 topVertex, const Vec2 bottomRightVertex, const Vec2 bottomLeftVertex, const Vec4 color1, const Vec4 color2, const Vec4 color3 ) {
	SDL_assert( bInDrawing );

	static VertexObject points[3];
	points[0] = { topVertex, color1 };
	points[1] = { bottomRightVertex, color2 };
	points[2] = { bottomLeftVertex, color3 };

	glUseProgram( s_ShaderProgram );
	glBindVertexArray( s_TriangleVAO );

	glBindBuffer( GL_ARRAY_BUFFER, s_TriangleVBO );
	glBufferData( GL_ARRAY_BUFFER, sizeof( points ), &points, GL_STATIC_DRAW );

	glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, sizeof( VertexObject ), nullptr );
	glEnableVertexAttribArray( 0 );

	glVertexAttribPointer( 1, 4, GL_FLOAT, GL_FALSE, sizeof( VertexObject ), (void*)(sizeof( Vec2 )) );
	glEnableVertexAttribArray( 1 );

	glDrawArrays( GL_TRIANGLES, 0, (sizeof( points ) / sizeof( VertexObject )) );
}

void CRenderer::DrawRay( const Ray ray ) {
	DrawLine( ray.origin, ray.origin + ray.direction * 10000 );
}

void CRenderer::DrawAABB( const AABB aabb ) {
	Vec2 mins = aabb.mins();
	Vec2 maxs = aabb.maxs();

	DrawLine( mins, Vec2( mins.x, maxs.y ) );
	DrawLine( mins, Vec2( maxs.x, mins.y ) );
	DrawLine( maxs, Vec2( mins.x, maxs.y ) );
	DrawLine( maxs, Vec2( maxs.x, mins.y ) );
}

void CRenderer::DrawCircle( const Circle circle ) {
	float r2 = circle.radius * circle.radius;
	for ( float cx = circle.radius, sy = 0; sy < cx; ++sy) {
		DrawPoint( Vec2( circle.origin.x + cx, circle.origin.y + sy ) );
		DrawPoint( Vec2( circle.origin.x + cx, circle.origin.y - sy ) );
		DrawPoint( Vec2( circle.origin.x - cx, circle.origin.y + sy ) );
		DrawPoint( Vec2( circle.origin.x - cx, circle.origin.y - sy ) );
		DrawPoint( Vec2( circle.origin.x + sy, circle.origin.y + cx ) );
		DrawPoint( Vec2( circle.origin.x + sy, circle.origin.y - cx ) );
		DrawPoint( Vec2( circle.origin.x - sy, circle.origin.y + cx ) );
		DrawPoint( Vec2( circle.origin.x - sy, circle.origin.y - cx ) );

		if ( RL_abs( (cx * cx) + (sy * sy) - r2 ) > RL_abs( cx * cx + (sy - 1) * (sy - 1) - r2) ) {
			--cx;
		}
	}
}
