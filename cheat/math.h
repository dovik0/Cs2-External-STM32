#pragma once
#ifndef _VECTOR_ESP_
#define _VECTOR_ESP_
#include <numbers>
#include <cmath>
#include "overlay.h"

struct view_matrix_t {
	float* operator[ ](int index) {
		return matrix[index];
	}

	float matrix[4][4];
};

struct Vec4 {
	float x, y, z, w;
	bool IsNull() const noexcept {
		return x == 0.f && y == 0.f && z == 0.f && w == 0.f;
	}
};

class Vec2
{
public:
	float x, y;

	Vec2() {};

	Vec2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	bool IsNull() const noexcept {
		return x == 0.f && y == 0.f;
	}

	Vec2 operator+(const Vec2& Input)
	{
		return Vec2{ x + Input.x, y + Input.y };
	}

	Vec2 operator-(const Vec2& Input)
	{
		return Vec2{ x - Input.x, y - Input.y };
	}

	Vec2 operator*(const Vec2& Input)
	{
		return Vec2{ x * Input.x, y * Input.y };
	}

	Vec2 operator/(const float& Input)
	{
		return Vec2{ x / Input, y / Input };
	}

	Vec2 operator*(const float& Input)
	{
		return Vec2{ x * Input, y * Input };
	}

	bool IsValid()
	{
		return x && y;
	}

	float Length()
	{
		return std::sqrt((x * x) + (y * y));
	}

	float Distance(Vec2 To)
	{
		return std::sqrt(std::pow(To.x - x, 2.f) + std::pow(To.y - y, 2.f));
	}

	Vec2 Normalize()
	{
		if (y <= -180.f) y += 360.f;
		else if (y > 180.f) y -= 360.f;

		if (x > 90.f) x -= 180.f;
		else if (x <= -90.f) x += 180.f;

		return { x,y };
	}
};

struct Vec3
{
	constexpr Vec3(
		const float x = 0.f,
		const float y = 0.f,
		const float z = 0.f) noexcept :
		x(x), y(y), z(z) {
	}

	constexpr bool IsNull() const noexcept {
		return x == 0.f && y == 0.f && z == 0.f;
	}
	constexpr const Vec3& operator-(const Vec3& other) const noexcept
	{
		return Vec3{ x - other.x, y - other.y, z - other.z };
	}

	constexpr const Vec3& operator+(const Vec3& other) const noexcept
	{
		return Vec3{ x + other.x, y + other.y, z + other.z };
	}

	constexpr const Vec3& operator/(const float factor) const noexcept
	{
		return Vec3{ x / factor, y / factor, z / factor };
	}

	constexpr const Vec3& operator*(const float factor) const noexcept
	{
		return Vec3{ x * factor, y * factor, z * factor };
	}

	constexpr const bool operator>(const Vec3& other) const noexcept {
		return x > other.x && y > other.y && z > other.z;
	}

	constexpr const bool operator>=(const Vec3& other) const noexcept {
		return x >= other.x && y >= other.y && z >= other.z;
	}

	constexpr const bool operator<(const Vec3& other) const noexcept {
		return x < other.x && y < other.y && z < other.z;
	}

	constexpr const bool operator<=(const Vec3& other) const noexcept {
		return x <= other.x && y <= other.y && z <= other.z;
	}

	float length() const {
		return std::sqrt(x * x + y * y + z * z);
	}

	float length2d() const {
		return std::sqrt(x * x + y * y);
	}

	constexpr const bool IsZero() const noexcept
	{
		return x == 0.f && y == 0.f && z == 0.f;
	}

	float calcDist(const Vec3& point) const {
		float dx = point.x - x;
		float dy = point.y - y;
		float dz = point.z - z;

		return std::sqrt(dx * dx + dy * dy + dz * dz);
	}
	float x, y, z;
};

inline float distance(Vec3 p1, Vec3 p2)
{
	return sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2) + pow(p1.z - p2.z, 2)) / 10.0f;
}

struct espvec
{
	Vec3 head_t;
	Vec3 screenPos, screenHead;
};

inline bool W2S(const Vec3& pos, Vec3& out, view_matrix_t matrix) {
	if (&pos == nullptr) {
		return false;
	}

	if (pos.x == 0 || pos.y == 0 || pos.z == 0)
		return false;
	out.x = matrix[0][0] * pos.x + matrix[0][1] * pos.y + matrix[0][2] * pos.z + matrix[0][3];
	out.y = matrix[1][0] * pos.x + matrix[1][1] * pos.y + matrix[1][2] * pos.z + matrix[1][3];

	float w = matrix[3][0] * pos.x + matrix[3][1] * pos.y + matrix[3][2] * pos.z + matrix[3][3];

	if (w < 0.01f)
		return false;

	float inv_w = 1.0f / w;
	out.x *= inv_w;
	out.y *= inv_w;

	float x = overlay::G_Width * 0.5f;
	float y = overlay::G_Height * 0.5f;

	x += 0.5f * out.x * overlay::G_Width + 0.5f;
	y -= 0.5f * out.y * overlay::G_Height + 0.5f;

	out.x = x;
	out.y = y;

	return true;
}
#endif