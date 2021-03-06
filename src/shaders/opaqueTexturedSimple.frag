#version 450
#extension GL_ARB_separate_shader_objects : enable
#extension GL_ARB_shading_language_420pack : enable

//In:
layout (location = 0) in vec2 vUV;
layout (location = 1) in vec3 vNormal;
layout (location = 2) in vec3 vPosition;
layout (location = 3) in vec4 mlightviewVertexPos;

layout (set = 1, binding = 0) uniform sampler2D uTexture;
layout (set = 2, binding = 1) uniform sampler2D shadowTexture;

layout(push_constant) uniform PushConsts {
	mat4x4 modelMatrix;
	mat4x4 normalMatrix;
} pu;

//Out:
layout (location = 0) out vec4 color;

float normpdf(in float x, in float sigma)
{
	return 0.39894*exp(-0.5*x*x/(sigma*sigma))/sigma;
}

const int kernelSize = 1;
const float bias = 0.0023;

void main() {
	vec3 lightFragmentPosition = mlightviewVertexPos.xyz;
	lightFragmentPosition.xy = lightFragmentPosition.xy * 0.5 + 0.5;
	float shadowFactor = 0.0;

	vec2 inc = 1.0 / textureSize(shadowTexture, 0);

	for(int row = -kernelSize; row <= kernelSize; ++row)
	{
		for(int col = -kernelSize; col <= kernelSize; ++col)
		{
			float rowColShadowEffectWeight = 1.0f; // normpdf(row,1.0) * normpdf(col,1.0);

			vec2 uvOffset = vec2(row, col) * inc;
			vec2 uv = lightFragmentPosition.xy + uvOffset;
			float textDepth = texture(shadowTexture, uv).r;
			shadowFactor += lightFragmentPosition.z + bias < textDepth ? 1.0 * rowColShadowEffectWeight : 0.0;        
		}    
	}//*/
	const float usedShadowPixels = kernelSize * 2 + 1;
	shadowFactor = 1.0-(shadowFactor / usedShadowPixels);
	
	/*float shade = 1.0;
	shade = intensity <= 0.8 ? 0.8 : shade;
	shade = intensity <= 0.15 ? 0.5 : shade;
	shade = intensity <= -0.3 ? 0.1 : shade;//*/
	
	const float ambientLight = 0.75;

	//todo move this into the pushconstants
	vec3 lightDirectionIn = normalize(vec3(0.5,1,-.5));
	//vec3 R = reflect(lightDirectionIn, vNormal);
	float intensity = max(dot(normalize(vNormal), lightDirectionIn), 0.0);

	shadowFactor = shadowFactor*(1.0-ambientLight) + ambientLight; 
	intensity = intensity*(1.0-ambientLight) + ambientLight;
	intensity = (intensity + shadowFactor)/2.0;
	float colorMult = intensity;
	color = vec4(texture(uTexture, vUV).rgb * colorMult, 1.0);
}
