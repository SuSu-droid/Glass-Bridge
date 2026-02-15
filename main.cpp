#include<iostream>
#include<raylib.h>
#include<vector>
#include <chrono>
using namespace std;

int iN() {
	if (IsKeyDown(KEY_A)) {
		return 1;
	}
	else if (IsKeyDown(KEY_D)) {
		return 2;
	}
	else if (IsKeyDown(KEY_W)) {
		return 3;
	}
	else if (IsKeyDown(KEY_S)) {
		return 4;
	}
	else if (IsKeyPressed(KEY_X)) {
		exit(0);
	}
	else {
		return 0;
	}
}

int main() {
	SetTargetFPS(60);
	InitWindow(1000, 500, "Glass bridge");
	int countOfPlates = 8;
	while (!WindowShouldClose()) {
		Rectangle rec1{ 200, 125, 100, 20};
		Rectangle rec2{ 200, 150, 100, 20};
		Rectangle rec3{ 200, 175, 100, 20};
		Color col1{ 0, 0, 0, 0 };
		Color col2{ 0, 0, 0, 0 };
		Color col3{ 0, 0, 0, 0 };
		Vector2 mouse = GetMousePosition();
		if (CheckCollisionPointRec(mouse, rec1)) {
			col1 = { 0, 0, 0, 75 };
		}
		if (CheckCollisionPointRec(mouse, rec2)) {
			col2 = { 0, 0, 0, 75 };
		}
		if (CheckCollisionPointRec(mouse, rec3)) {
			col3 = { 0, 0, 0, 75 };
		}
		if (CheckCollisionPointRec(mouse, rec1) and IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			countOfPlates = 8;
			break;
		}
		if (CheckCollisionPointRec(mouse, rec2) and IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			countOfPlates = 12;
			break;
		}
		if (CheckCollisionPointRec(mouse, rec3) and IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
			countOfPlates = 16;
			break;
		}
		BeginDrawing();
		ClearBackground(RAYWHITE);
		DrawText("CHOSE DIFFICULT LEVEL (1-3):", 150, 75, 40, BLACK);
		DrawRectangleRec(rec1, col1);
		DrawRectangleRec(rec2, col2);
		DrawRectangleRec(rec3, col3);
		DrawText("LEVEL 1", 200, 125, 20, BLACK);
		DrawText("LEVEL 2", 200, 150, 20, BLACK);
		DrawText("LEVEL 3", 200, 175, 20, BLACK);
		EndDrawing();
	}
	vector<vector<int>> pls(countOfPlates, vector<int>(2, 0));
	for (int i = 0; i < countOfPlates; i++) {
		pls[i][rand() % 2] = 1;
	}
	double x = 15;
	double y = 240;
	double z = 20;
	int ij = 0;
	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(RAYWHITE);
		Rectangle start{ 0, 100, 50, 300 };
		Rectangle finish{ 925, 100, 75, 300 };
		DrawRectangleRec(start, RED);
		DrawLine(50, 190, 950, 190, RED);
		DrawLine(50, 240, 950, 240, RED);
		DrawLine(50, 260, 950, 260, RED);
		DrawLine(50, 310, 950, 310, RED);
		DrawRectangleRec(finish, RED);
		int px = 113;
		int pxa = 0;
		int s = 0;
		if (countOfPlates == 8) {
			pxa = 100;
			s = 50;
		}
		if (countOfPlates == 12) {
			pxa = 70;
			s = 30;
		}
		if (countOfPlates == 16) {
			pxa = 50;
			s = 25;
		}
		vector<vector<Rectangle>> plates(countOfPlates, vector<Rectangle>(2));
		for (int i = 0; i < countOfPlates; i++) {
			plates[i][0] = { (float)px, 190, (float)s, 50 };
			plates[i][1] = { (float)px, 260, (float)s, 50 };
			px += pxa;
		}
		int dir = iN();
		if (dir == 1 and x > 0) {
			x -= 1;
		}
		else if (dir == 2 and x < 980) {
			x += 1;
		}
		else if (dir == 3 and y > 0) {
			y -= 1;
		}
		else if (dir == 4 and y < 480) {
			y += 1;
		}
		if (IsKeyPressed(KEY_SPACE) and ij == 0) {
			ij = 1;
		}
		if (ij == 1) {
			z += 0.25;
			if (z == 30) {
				ij = 2;
			}
		}
		if (ij == 2) {
			z -= 0.25;
			if (z == 20) {
				ij = 0;
			}
		}
		Rectangle player{ x, y, z, z };
		bool flag = false;
		if (ij == 0 and (!CheckCollisionRecs(player, start) and !CheckCollisionRecs(player, finish))) {
			flag = true;
		}
		DrawRectangleRec(player, { 0, 0, 0, 255 });
		for (int i = 0; i < countOfPlates; i++) {
			DrawRectangleRec(plates[i][0], {0, 0, 255, 125});
			DrawRectangleRec(plates[i][1], {0, 0, 255, 125});
			if (CheckCollisionRecs(player, plates[i][0]) and flag) {
				if (pls[i][0] == 0) {
					flag = false;
				}
			}
			else if (CheckCollisionRecs(player, plates[i][1]) and flag) {
				if (pls[i][1] == 0) {
					flag = false;
				}
			}
		}
		if (flag) {
			exit(0);
		}
		EndDrawing();
	}
	return 0;
}