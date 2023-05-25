#include "MyImGui.h"
#include "imgui.h"

void MyImGui::SliderVector3(const char* label, MyVector3& v, const float& min, const float& max) {
	float inputFloat3[3] = { v.x,v.y,v.z };
	ImGui::SliderFloat3(label, inputFloat3, min, max);

	v.x = inputFloat3[0];
	v.y = inputFloat3[1];
	v.z = inputFloat3[2];
}


