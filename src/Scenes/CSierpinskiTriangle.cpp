#include "CSierpinskiTriangle.h"

#include "CRenderer.h"
#define IMGUI_DISABLE_TEST_WINDOWS
#include "imgui.h"
#undef IMGUI_DISABLE_TEST_WINDOWS

void DrawSierpinskiTriangle( CRenderer& renderer, Vec2 A, Vec2 B, Vec2 C, int i ) {
	if ( i == 6 ) { return; }
	++i;

	renderer.SetDrawColor( Vec4( 0, 0, 0, 1 ) );
	renderer.DrawTriangle( A, (A + B) / 2, (A + C) / 2 );
	renderer.DrawTriangle( B, (B + A) / 2, (B + C) / 2 );
	renderer.DrawTriangle( C, (C + A) / 2, (C + B) / 2 );

	renderer.SetDrawColor( Vec4( 1, 1, 1, 1 ) );
	renderer.DrawTriangle( (A + B) / 2, (A + C) / 2, (B + C) / 2 );

	DrawSierpinskiTriangle( renderer, A, (A + B) / 2, (A + C) / 2, i );
	DrawSierpinskiTriangle( renderer, B, (B + A) / 2, (B + C) / 2, i );
	DrawSierpinskiTriangle( renderer, C, (C + A) / 2, (C + B) / 2, i );
}

const char * CSierpinskiTriangle::GetName() const {
	return "Sierpinski Triangle";
}

void CSierpinskiTriangle::OnInit() {

}

void CSierpinskiTriangle::OnEnable() {

}

void CSierpinskiTriangle::OnDisable() {

}

void CSierpinskiTriangle::OnUpdate() {

}

void CSierpinskiTriangle::OnInterface() {

}

void CSierpinskiTriangle::OnRender( CRenderer& renderer ) const {
	DrawSierpinskiTriangle( renderer, Vec2( 400, 100 ), Vec2( 700, 500 ), Vec2( 100, 500 ), 0 );
}
