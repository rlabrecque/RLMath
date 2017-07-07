#include "Renderer.h"
#include "Interface.h"
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
		return 5;
	}

	unsigned int fragmentShader = glCreateShader( GL_FRAGMENT_SHADER );
	glShaderSource( fragmentShader, 1, &fragmentShaderSource, nullptr );
	glCompileShader( fragmentShader );
	glGetShaderiv( fragmentShader, GL_COMPILE_STATUS, &success );
	if ( !success ) {
		glGetShaderInfoLog( fragmentShader, 512, nullptr, infoLog );
		SDL_LogError( SDL_LOG_CATEGORY_APPLICATION, "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED: %s\n", infoLog );
		return 6;
	}

	s_ShaderProgram = glCreateProgram();
	glAttachShader( s_ShaderProgram, vertexShader );
	glAttachShader( s_ShaderProgram, fragmentShader );
	glLinkProgram( s_ShaderProgram );
	glGetProgramiv( s_ShaderProgram, GL_LINK_STATUS, &success );
	if ( !success ) {
		glGetProgramInfoLog( s_ShaderProgram, 512, nullptr, infoLog );
		SDL_LogError( SDL_LOG_CATEGORY_APPLICATION, "ERROR::SHADER::PROGRAM::COMPILATION_FAILED: %s\n", infoLog );
		return 7;
	}

	glDeleteShader( vertexShader );
	glDeleteShader( fragmentShader );

	return 0;
}

int Renderer_Init() {
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

	int ret = Renderer_Init_Shaders();
	if ( ret != 0 ) {
		return ret;
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

	return 0;
}

void Renderer_Shutdown() {
	glDeleteVertexArrays( 1, &s_PointVAO );
	glDeleteBuffers( 1, &s_PointVBO );
	glDeleteVertexArrays( 1, &s_LineVAO );
	glDeleteBuffers( 1, &s_LineVBO );
	glDeleteVertexArrays( 1, &s_TriangleVAO );
	glDeleteBuffers( 1, &s_TriangleVBO );

	SDL_GL_DeleteContext( s_GLContext );
	Interface_Shutdown();
}

void DrawSierpinskiTriangle(Vec2 A, Vec2 B, Vec2 C, int i) {
	if ( i == 6 ) { return; }
	++i;

	Renderer_SetDrawColor( Vec4( 0, 0, 0, 1 ) );
	Renderer_DrawTriangle( A, (A + B) / 2, (A + C) / 2 );
	Renderer_DrawTriangle( B, (B + A) / 2, (B + C) / 2 );
	Renderer_DrawTriangle( C, (C + A) / 2, (C + B) / 2 );

	Renderer_SetDrawColor( Vec4( 1, 1, 1, 1 ) );
	Renderer_DrawTriangle( (A + B) / 2, (A + C) / 2, (B + C) / 2 );

	DrawSierpinskiTriangle( A, (A + B) / 2, (A + C) / 2, i );
	DrawSierpinskiTriangle( B, (B + A) / 2, (B + C) / 2, i );
	DrawSierpinskiTriangle( C, (C + A) / 2, (C + B) / 2, i );
}

void Renderer_RunFrame() {

	glViewport( 0, 0, WindowWidth, WindowHeight );
	glClearColor( g_ClearColor.r, g_ClearColor.g, g_ClearColor.b, g_ClearColor.a );
	glClear( GL_COLOR_BUFFER_BIT );

	/*Renderer_SetDrawColor( Vec4( 128, 0, 128, 1 ) );
	Renderer_DrawTriangle( Vec2( 200, 100 ), Vec2( 300, 300 ), Vec2( 100, 300 ) );
	Renderer_DrawTriangle( Vec2( 400, 100 ), Vec2( 500, 300 ), Vec2( 300, 300 ) );

	Renderer_SetDrawColor( Vec4( 0, 0, 0, 1 ) );
	Renderer_DrawLine( Vec2( 100, 500 ), Vec2( 500, 500 ) );*/


	for ( auto&& ray : rays ) {
		Renderer_SetDrawColor( ray.second );
		Renderer_DrawRay( ray.first );
	}

	for ( auto&& point : points ) {
		Renderer_SetDrawColor( point.second );
		Renderer_DrawPoint( point.first );
	}

	if ( bPlacingRay ) {
		Renderer_SetDrawColor( g_DrawColor );
		Vec2 pos = RayPosition;
		Vec2 dir = (RayPosition + ((MousePosition - RayPosition).normalized() * FLT_MAX));
		/*for ( auto&& ray : rays ) {
			const Vec2 s1 = pos - ray.first.position;
			float planarFactor = Vec2::Dot( lineVec3, crossVec1and2);

			if ( RL_abs( planarFactor ) < 0.0001f && crossVec1and2.squaredMagnitude() > 0.0001f ) {
				float s = Vec2::Dot(crossVec3and2, crossVec1and2) / crossVec1and2.squaredMagnitude();
				Renderer_DrawLine( pos, endPos );
				pos = lineVec3 + (ray.first.position * s);
			}
		}*/

		Renderer_DrawLine( pos, dir );
	}

	if ( bDrawSierpinski ) {
		Vec2 A = Vec2( 400, 100 );
		Vec2 B = Vec2( 700, 500 );
		Vec2 C = Vec2( 100, 500 );
		DrawSierpinskiTriangle( A, B, C, 0 );
	}

	Interface_Draw();

	SDL_GL_SwapWindow( g_Window );
}


void Renderer_SetDrawColor( Vec4 color ) {
	s_DrawColor = color;
}

void Renderer_DrawPoint( Vec2 point ) {
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

void Renderer_DrawLine( Vec2 start, Vec2 end ) {
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

void Renderer_DrawTriangle( Vec2 topVertex, Vec2 bottomRightVertex, Vec2 bottomLeftVertex ) {
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

void Renderer_DrawRay( Ray ray ) {
	Renderer_DrawLine( ray.position, ray.direction );
}
