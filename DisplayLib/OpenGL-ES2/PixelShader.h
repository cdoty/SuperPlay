#pragma once

static const char gsc_szPixelShader[]	=
"\
precision mediump float; \
\
uniform	sampler2D		pTexture; \
varying	mediump vec2	vecTexCoord; \
\
void main(void) \
{ \
	vec4	color	= texture2D(pTexture, vecTexCoord); \
\
	if (0.0 == color.a) \
	{ \
		discard; \
	} \
\
	gl_FragColor	= color; \
} \
";
