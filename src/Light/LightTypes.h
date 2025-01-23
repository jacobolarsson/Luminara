#pragma once

enum class LightType
{
	POINT,
	DIR,
	SPOT
};

struct PointLightData
{
	vec3 color;
	float constAtt;
	float linAtt;
	float quadAtt;
};

struct DirLightData
{
	vec3 color;
	vec3 direction;
};

struct SpotLightData
{
	vec3 color;
	vec3 direction;
	float attenuation;
};

union LightData
{
	PointLightData pointData;
	DirLightData dirData;
	SpotLightData spotData;
};