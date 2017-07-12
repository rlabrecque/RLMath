#include "CRenderer.h"
#include "CSceneManager.h"
#include "CUserInterface.h"
#include "GL\gl3w.h"

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
	const char *vertexShaderSource = R"glsl(
#version 330 
uniform vec2 viewPortSize;

layout (location = 0) in vec2 position;
layout (location = 1) in vec4 vertexInputColor;

out vec4 vertexColor;

void main() {
	gl_Position = vec4((2 * (position.x / viewPortSize.x) - 1), -(2 * (position.y / viewPortSize.y) - 1), 0.0f, 1.0f);
	vertexColor = vertexInputColor;
}
)glsl";

	const char *fragmentShaderSource = R"glsl(
#version 330 core
in vec4 vertexColor;
out vec4 FragColor;

void main() {
	FragColor = vertexColor;
}
)glsl";

	int  success;
	char infoLog[512];

	unsigned int vertexShader = glCreateShader( GL_VERTEX_SHADER );
	glShaderSource( vertexShader, 1, &vertexShaderSource, nullptr );
	glCompileShader( vertexShader );

	glGetShaderiv( vertexShader, GL_COMPILE_STATUS, &success );
	if ( !success ) {
		glGetShaderInfoLog( vertexShader, 512, nullptr, infoLog );
		SDL_LogError( SDL_LOG_CATEGORY_APPLICATION, "ERROR::SHADER::VERTEX::COMPILATION_FAILED: %s\n", infoLog );
		return false;
	}

	unsigned int fragmentShader = glCreateShader( GL_FRAGMENT_SHADER );
	glShaderSource( fragmentShader, 1, &fragmentShaderSource, nullptr );
	glCompileShader( fragmentShader );
	glGetShaderiv( fragmentShader, GL_COMPILE_STATUS, &success );
	if ( !success ) {
		glGetShaderInfoLog( fragmentShader, 512, nullptr, infoLog );
		SDL_LogError( SDL_LOG_CATEGORY_APPLICATION, "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED: %s\n", infoLog );
		return false;
	}

	s_ShaderProgram = glCreateProgram();
	glAttachShader( s_ShaderProgram, vertexShader );
	glAttachShader( s_ShaderProgram, fragmentShader );
	glLinkProgram( s_ShaderProgram );
	glGetProgramiv( s_ShaderProgram, GL_LINK_STATUS, &success );
	if ( !success ) {
		glGetProgramInfoLog( s_ShaderProgram, 512, nullptr, infoLog );
		SDL_LogError( SDL_LOG_CATEGORY_APPLICATION, "ERROR::SHADER::PROGRAM::COMPILATION_FAILED: %s\n", infoLog );
		return false;
	}

	glDeleteShader( vertexShader );
	glDeleteShader( fragmentShader );

	return true;
}

bool CRenderer::Init() {
	// Create GL Context and initialize it
	s_GLContext = SDL_GL_CreateContext( g_Window );
	gl3wInit();
	glDisable( GL_CULL_FACE );
	glDisable( GL_DEPTH_TEST );
	//glEnable( GL_PROGRAM_POINT_SIZE );
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
	int vertexPositionLocation = glGetUniformLocation( s_ShaderProgram, "viewPortSize" );
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

void CRenderer::RunFrame( CSceneManager& sceneManager, CUserInterface& userInterface) {
	glViewport( 0, 0, WindowWidth, WindowHeight );
	glClearColor( 0.1f, 0.1f, 0.1f, 1 );
	glClear( GL_COLOR_BUFFER_BIT );

	bInDrawing = true;
	sceneManager.GetCurrentScene()->OnRender(*this);
	bInDrawing = false;

	userInterface.Draw();

	SDL_GL_SwapWindow( g_Window );
}

void CRenderer::SetDrawColor( Vec4 color ) {
	SDL_assert( bInDrawing );

	s_DrawColor = color;
}

void CRenderer::DrawPoint( Vec2 point ) {
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

	glDrawArrays( GL_POINTS, 0, countof( points ) );
}

void CRenderer::DrawLine( Vec2 start, Vec2 end ) {
	SDL_assert( bInDrawing );

	static VertexObject points[3];
	points[0] = { start, s_DrawColor };
	points[1] = { end, s_DrawColor };

	glUseProgram( s_ShaderProgram );
	glBindVertexArray( s_LineVAO );

	glBindBuffer( GL_ARRAY_BUFFER, s_LineVBO );
	glBufferData( GL_ARRAY_BUFFER, sizeof( points ), &points, GL_STATIC_DRAW );

	glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, sizeof( VertexObject ), nullptr );
	glEnableVertexAttribArray( 0 );

	glVertexAttribPointer( 1, 4, GL_FLOAT, GL_FALSE, sizeof( VertexObject ), (void*)(sizeof( Vec2 )) );
	glEnableVertexAttribArray( 1 );

	glDrawArrays( GL_LINES, 0, countof( points ) );
}

void CRenderer::DrawTriangle( Vec2 topVertex, Vec2 bottomRightVertex, Vec2 bottomLeftVertex ) {
	SDL_assert( bInDrawing );

	static VertexObject points[3];
	points[0] = { topVertex, s_DrawColor };
	points[1] = { bottomRightVertex, s_DrawColor };
	points[2] = { bottomLeftVertex, s_DrawColor };

	glUseProgram( s_ShaderProgram );
	glBindVertexArray( s_TriangleVAO );

	glBindBuffer( GL_ARRAY_BUFFER, s_TriangleVBO );
	glBufferData( GL_ARRAY_BUFFER, sizeof( points ), &points, GL_STATIC_DRAW );

	glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, sizeof( VertexObject ), nullptr );
	glEnableVertexAttribArray( 0 );

	glVertexAttribPointer( 1, 4, GL_FLOAT, GL_FALSE, sizeof( VertexObject ), (void*)(sizeof( Vec2 )) );
	glEnableVertexAttribArray( 1 );

	glDrawArrays( GL_TRIANGLES, 0, countof(points) );
}

void CRenderer::DrawRay( Ray ray ) {
	DrawLine( ray.position, ray.position + ray.direction * 10000 );
}

void CRenderer::DrawAABB( AABB aabb ) {
	Vec2 mins = aabb.mins();
	Vec2 maxs = aabb.maxs();

	DrawLine( mins, Vec2( mins.x, maxs.y ) );
	DrawLine( mins, Vec2( maxs.x, mins.y ) );
	DrawLine( maxs, Vec2( mins.x, maxs.y ) );
	DrawLine( maxs, Vec2( maxs.x, mins.y ) );
}

void CRenderer::DrawCircle( Circle circle ) {
	float r2 = circle.radius * circle.radius;
	for ( float cx = circle.radius, sy = 0; sy < cx; ++sy) {
		DrawPoint( Vec2( circle.center.x + cx, circle.center.y + sy ) );
		DrawPoint( Vec2( circle.center.x + cx, circle.center.y - sy ) );
		DrawPoint( Vec2( circle.center.x - cx, circle.center.y + sy ) );
		DrawPoint( Vec2( circle.center.x - cx, circle.center.y - sy ) );
		DrawPoint( Vec2( circle.center.x + sy, circle.center.y + cx ) );
		DrawPoint( Vec2( circle.center.x + sy, circle.center.y - cx ) );
		DrawPoint( Vec2( circle.center.x - sy, circle.center.y + cx ) );
		DrawPoint( Vec2( circle.center.x - sy, circle.center.y - cx ) );

		if ( RL_abs( (cx * cx) + (sy * sy) - r2 ) > RL_abs( cx * cx + (sy - 1) * (sy - 1) - r2) ) {
			--cx;
		}
	}
}
