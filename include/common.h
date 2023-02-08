#pragma once

struct vec2
{
	float x = 0.0f;
	float y = 0.0f;
};

struct unit
{
	vec2 position; // position of unit (-10^5...10^5, -10^5...10^5)
	vec2 direction; // normalized view direction
	float fov_deg = 0.0f; // horizontal field-of-view in degrees (0...180)
	float distance = 0.0f; // view distance (0...10^5)
};
