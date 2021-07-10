#pragma once

static const char* g_VertexSource =
	"#version 330 core\n"
	"out vec2 uv;\n"
	"void main() {\n"
	"	uv.x = gl_VertexID == 1 ? 2 : 0;\n"
	"	uv.y = gl_VertexID == 2 ? 2 : 0;\n"
	"	gl_Position = vec4(uv * 2 - 1, 1, 1);\n"
	"	uv.y = 1 - uv.y;\n"
	"}";

static const char* g_FragmentSource =
	"#version 330 core\n"
	"in vec2 uv;\n"
	"layout (location = 0) out vec4 color;\n"
	"uniform sampler2D sourceTex;\n"
	"void main() {\n"
	"	color = vec4(texture(sourceTex, uv).rgb, 1);\n"
	"}";
