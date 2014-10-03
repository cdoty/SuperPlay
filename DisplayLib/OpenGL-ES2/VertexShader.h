#pragma once

static const char gsc_szVertexShader[]	=
"\
attribute	highp vec4		vecVertex; \
attribute	mediump vec2	vecUV; \
uniform		mediump mat4	matMatrix; \
varying		mediump vec2	vecTexCoord; \
\
void main(void) \
{ \
	gl_Position	= matMatrix * vecVertex; \
	vecTexCoord	= vecUV; \
} \
";
