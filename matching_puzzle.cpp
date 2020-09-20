#include <bangtal.h>

using namespace bangtal;


typedef struct {
	int x;
	int y;
}central;

int main() {
	setGameOption(GameOption::GAME_OPTION_INVENTORY_BUTTON, false);
	setGameOption(GameOption::GAME_OPTION_MESSAGE_BOX_BUTTON, false);

	central cent1 = { 190, 460 };
	central cent2 = { 490, 460 };
	central cent3 = { 790, 460 };
	central cent4 = { 190, 260 };
	central cent5 = { 490, 260 };
	central cent6 = { 790, 260 };
	central cent7 = { 190, 60 };
	central cent8 = { 490, 60 };
	central cent9 = { 790, 60 };

	auto scene = Scene::create("숫자방", "Images/배경.png");

	auto num1 = Object::create("Images/1.png", scene, cent5.x, cent5.y);
	auto num2 = Object::create("Images/2.png", scene, cent4.x, cent4.y);
	auto num3 = Object::create("Images/3.png", scene, cent8.x, cent8.y);
	auto num4 = Object::create("Images/4.png", scene, cent3.x, cent3.y);
	auto num5 = Object::create("Images/5.png", scene, cent6.x, cent6.y);
	auto num6 = Object::create("Images/6.png", scene, cent1.x, cent1.y);
	auto num7 = Object::create("Images/7.png", scene, cent7.x, cent7.y);
	auto num8 = Object::create("Images/8.png", scene, cent2.x, cent2.y);
	auto num9 = Object::create("Images/스타.png", scene, cent9.x, cent9.y);
	auto rule = Object::create("Images/룰.png", scene);

	rule->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		rule->hide();
		return true;
		});

	central* cent[3][3] = { {&cent1, &cent2, &cent3}, { &cent4, &cent5, &cent6 }, {&cent7, &cent8, &cent9 } };
	ObjectPtr obj[3][3] = { {num6, num8, num4}, {num2, num1, num5}, {num7, num3, num9} };
	int row = 2, col = 2;
	int puzzle[3][3] = { { 6, 8 ,4 },{ 2, 1, 5 },{ 7, 3, 0 } };
	int key;

	int n = 0;

	num9->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (action == MouseAction::MOUSE_DRAG_LEFT && col > 0) {
			puzzle[row][col] = puzzle[row][col - 1];
			puzzle[row][col - 1] = 0;
			obj[row][col]->locate(scene, cent[row][col - 1]->x, cent[row][col - 1]->y);
			obj[row][col - 1]->locate(scene, cent[row][col]->x, cent[row][col]->y);
			obj[row][col] = obj[row][col - 1];
			obj[row][col - 1] = num9;
			col--;
			return true;
		}
		else if (action == MouseAction::MOUSE_DRAG_RIGHT && col < 2) {
			puzzle[row][col] = puzzle[row][col + 1];
			puzzle[row][col + 1] = 0;
			obj[row][col]->locate(scene, cent[row][col + 1]->x, cent[row][col + 1]->y);
			obj[row][col + 1]->locate(scene, cent[row][col]->x, cent[row][col]->y);
			obj[row][col] = obj[row][col + 1];
			obj[row][col + 1] = num9;
			col++;
			return true;
		}
		else if (action == MouseAction::MOUSE_DRAG_UP && row > 0) {
			puzzle[row][col] = puzzle[row - 1][col];
			puzzle[row - 1][col] = 0;
			obj[row][col]->locate(scene, cent[row - 1][col]->x, cent[row - 1][col]->y);
			obj[row - 1][col]->locate(scene, cent[row][col]->x, cent[row][col]->y);
			obj[row][col] = obj[row - 1][col];
			obj[row - 1][col] = num9;
			row--;
			return true;
		}
		else if (action == MouseAction::MOUSE_DRAG_DOWN && row < 2) {
			puzzle[row][col] = puzzle[row + 1][col];
			puzzle[row + 1][col] = 0;
			obj[row][col]->locate(scene, cent[row + 1][col]->x, cent[row + 1][col]->y);
			obj[row + 1][col]->locate(scene, cent[row][col]->x, cent[row][col]->y);
			obj[row][col] = obj[row + 1][col];
			obj[row + 1][col] = num9;
			row++;
			return true;
		}
		else {
			return true;
		}
		});

	for (int r = 0; r < 3; r++)
	{
		for (int c = 0; c < 3; c++)
		{
			if (puzzle[r][c] != r * 3 + c + 1)
			{
				break;
			}
			else if (r == 2 && c == 2) {
				endGame();
			}
		}
	}



	startGame(scene);

	return 0;
}
