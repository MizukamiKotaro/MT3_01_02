#include <Novice.h>
#include"MyMatrix4x4.h"
#include"MatrixScreenPrintf.h"
#include"MyVector3.h"
#include"VectorScreenPrintf.h"
#include"calc.h"
#include"Grid.h"
#include"Sphere.h"
#include<imgui.h>
#include"MyImGui.h"

const char kWindowTitle[] = "学籍番号";

static const int kRowHeight = 20;
static const int kColumnWidth = 60;

const int kWindowWidth = 1280;
const int kWindowHeight = 720;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR lpCmdLine, _In_ int nShowCmd) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	float speed = 0.01f;

	MyVector3 cameraTranslate{ 0.0f,1.9f,-6.49f };
	MyVector3 cameraRotate{ 0.26f,0.0f,0.0f };

	Sphere sphere = {
		{},
		1.0f
	};

	MyVector3 sphereRotate{};

	MyMatrix4x4 originMatrix = MyMatrix4x4::MakeAffinMatrix({ 1.0f,1.0f,1.0f }, { 0.0f,0.0f,0.0f }, { 0.0f,0.0f,0.0f });
	
	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		if (keys[DIK_R]) {
			cameraTranslate = { 0.0f,1.9f,-6.49f };
			cameraRotate = { 0.26f,0.0f,0.0f };
			sphere = { {},1.0f };
			sphereRotate = {};
		}

		ImGui::Begin("Window");
		MyImGui::SliderVector3("CameraTranslate", cameraTranslate,-10.0f,10.0f);
		MyImGui::SliderVector3("CameraRotate", cameraRotate, -3.141592f, 3.141592f);
		MyImGui::SliderVector3("SphereCenter", sphere.center_, -10.0f, 10.0f);
		MyImGui::SliderVector3("SphereRotate", sphereRotate, -3.141592f, 3.141592f);
		ImGui::SliderFloat("SphereRadius", &sphere.radius_, 0.0f, 2.0f);
		ImGui::End();
		

		MyMatrix4x4 worldMatrix = MyMatrix4x4::MakeAffinMatrix({ 1.0f,1.0f,1.0f }, sphereRotate, sphere.center_);
		MyMatrix4x4 cameraMatrix = MyMatrix4x4::MakeAffinMatrix({ 1.0f,1.0f,1.0f }, cameraRotate, cameraTranslate);
		MyMatrix4x4 viewMatrix = MyMatrix4x4::Inverse(cameraMatrix);
		MyMatrix4x4 projectionMatrix = MyMatrix4x4::MakePerspectiveFovMatrix(0.45f, float(kWindowWidth) / float(kWindowHeight), 0.1f, 100.0f);
		MyMatrix4x4 worldViewProjectionMatrix = MyMatrix4x4::Multiply(worldMatrix, MyMatrix4x4::Multiply(viewMatrix, projectionMatrix));
		MyMatrix4x4 viewportMatrix = MyMatrix4x4::MakeViewportMatrix(0.0f, 0.0f, float(kWindowWidth), float(kWindowHeight), 0.0f, 1.0f);

		MyMatrix4x4 originViewProjectionMatrix = MyMatrix4x4::Multiply(originMatrix, MyMatrix4x4::Multiply(viewMatrix, projectionMatrix));

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		
		Novice::ScreenPrintf(0, 0, "R : reset");
		//VectorScreenPrintf(0, 0, cross, "Cross");
		Grid::DrawGrid(originViewProjectionMatrix, viewportMatrix);
		Sphere::DrawSphere(sphere, worldViewProjectionMatrix, viewportMatrix, 0x000000FF);
		////cameraRotateを使っているけど向きのrotateを用意した方がいいかも
		//if (Calc::Dot(MyMatrix4x4::Multiply(cameraDirection ,MyMatrix4x4::MakeRotateXYZMatrix(cameraRotate)), Calc::Cross((screenVertices[1] - screenVertices[0]), (screenVertices[2] - screenVertices[1]))) <= 0) {
		//	Novice::DrawTriangle(int(screenVertices[0].x), int(screenVertices[0].y), int(screenVertices[1].x), int(screenVertices[1].y),
		//		int(screenVertices[2].x), int(screenVertices[2].y), RED, kFillModeSolid);
		//}

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
