﻿#pragma once
#include"MyVector3.h"
#include"MyMatrix4x4.h"
#include<cstdint>
class Sphere
{
public:
	Sphere(const MyVector3& center, const float& radius);

	static void DrawSphere(const Sphere& sphere, const MyMatrix4x4& viewProjectionMatrix, const MyMatrix4x4& viewportMatrix, uint32_t color);
public:
	MyVector3 center_;
	float radius_;
};
