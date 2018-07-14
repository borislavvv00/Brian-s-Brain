#include <SFML/Graphics.hpp>
#include <iostream>
#define GRID_SIZE 90
#define CELL_SIZE 7

using namespace sf;
using namespace std;

RenderWindow window(VideoMode(GRID_SIZE * CELL_SIZE, GRID_SIZE * CELL_SIZE), "Brian's Brain");
RectangleShape grid[GRID_SIZE][GRID_SIZE];
RectangleShape newGrid[GRID_SIZE][GRID_SIZE];
int countOnCells = 0;
bool isGridFull = false;
bool isFigureReady = false;
Vector2i mousePosition;

void FullGrid()
{
	for (int i = 0; i < GRID_SIZE; i++)
	{
		for (int j = 0; j < GRID_SIZE; j++)
		{
			newGrid[i][j].setPosition(Vector2f(CELL_SIZE * i, CELL_SIZE * j));
			newGrid[i][j].setFillColor(Color::Black);
			newGrid[i][j].setSize(Vector2f(CELL_SIZE, CELL_SIZE));
			grid[i][j].setPosition(Vector2f(CELL_SIZE * i, CELL_SIZE * j));
			grid[i][j].setFillColor(Color::Black);
			grid[i][j].setSize(Vector2f(CELL_SIZE, CELL_SIZE));
		}
	}
}

void DrawStartFigure(int i, int j)
{
	if (Mouse::isButtonPressed(Mouse::Left))
	{
		mousePosition = Mouse::getPosition(window);
		//if mouse is over a cell
		if ((mousePosition.x >= grid[i][j].getPosition().x && mousePosition.x <= grid[i][j].getPosition().x + grid[i][j].getSize().x) && (mousePosition.y >= grid[i][j].getPosition().y && mousePosition.y <= grid[i][j].getPosition().y + grid[i][j].getSize().y))
		{
			if (grid[i][j].getFillColor() == Color::Black)
			{
				grid[i][j].setFillColor(Color::White);
			}
			else if (grid[i][j].getFillColor() == Color::White)
			{
				grid[i][j].setFillColor(Color::Blue);
			}
			else if (grid[i][j].getFillColor() == Color::Blue)
			{
				grid[i][j].setFillColor(Color::Black);
			}
			cout << "Cell turn On" << endl;
		}
	}
}

void ChangeCell(int i, int j)
{
	if (grid[i][j].getFillColor() == Color::White)
	{
		newGrid[i][j].setFillColor(Color::Blue);
	}
	else if (grid[i][j].getFillColor() == Color::Blue)
	{
		newGrid[i][j].setFillColor(Color::Black);
	}
	else if (grid[i][j].getFillColor() == Color::Black && countOnCells == 2)
	{
		newGrid[i][j].setFillColor(Color::White);
	}
}

void CheckCell()
{
	for (int i = 0; i < GRID_SIZE; i++)
	{
		for (int j = 0; j < GRID_SIZE; j++)
		{
			if ((i > 0 && i < GRID_SIZE) && (j > 0 && j < GRID_SIZE))
			{
				for (int h = 0 - 1; h <= 1; h++)
				{
					for (int k = 0 - 1; k <= 1; k++)
					{
						if (grid[i + h][j + k].getFillColor() == Color::White)
						{
							countOnCells++;
							if (h == 1)
							{
								ChangeCell(i, j);
							}
						}
						else if (grid[i + h][j + k].getFillColor() != Color::White)
						{
							ChangeCell(i, j);
							if (h == 1)
							{
								ChangeCell(i, j);
							}
						}
					}
				}
				countOnCells = 0;
			}
		}
	}
}

void DrawGrid()
{
	for (int i = 0; i < GRID_SIZE; i++)
	{
		for (int j = 0; j < GRID_SIZE; j++)
		{
			if (isFigureReady == true)
			{
				grid[i][j] = newGrid[i][j];
			}
			else 
			{
				DrawStartFigure(i, j);
			}
			window.draw(grid[i][j]);
		}
	}
}

int main()
{
	while (window.isOpen())
	{
		while (true)
		{
			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)
				{
					window.close();
				}

				if (event.key.code == Keyboard::D)
				{
					isFigureReady = true;
					cout << "Start" << endl;
				}
				else if (event.key.code == Keyboard::F)
				{
					isGridFull = false;
					isFigureReady = false;
					cout << "Again" << endl;
				}
			}

			if (isGridFull == false)
			{
				FullGrid();
			}
			if (isFigureReady == true)
			{
				CheckCell();
			}
			window.clear();
			DrawGrid();
			window.display();
			isGridFull = true;
		}
	}

	return 0;
}