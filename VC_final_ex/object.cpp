#include "object.h"

int a, b;

void OBject::setAreaCopy(int area[][25])
{
	for (int i = 0; i < 30; i++) 
	{
		for (int j = 0; j < 25; j++) 
		{
			this->area[i][j] = area[i][j];
		}
	}
}

void OBject::drawPlayer(HDC memDC)
{	
	HBRUSH myBrush = CreateSolidBrush(RGB(255, 255, 0));
	HBRUSH osBrush = (HBRUSH)SelectObject(memDC, myBrush);
	Ellipse(memDC, playerPlace.left, playerPlace.top, playerPlace.right, playerPlace.bottom);
	SelectObject(memDC, osBrush);
	DeleteObject(osBrush);
	DeleteObject(myBrush);
}

void OBject::drawEnemy(HDC memDC)
{	
	HBRUSH myBrush = CreateSolidBrush(RGB(255, 0, 0));
	HBRUSH osBrush = (HBRUSH)SelectObject(memDC, myBrush);
	Ellipse(memDC, enemyPlace.left, enemyPlace.top, enemyPlace.right, enemyPlace.bottom);
	SelectObject(memDC, osBrush);
	DeleteObject(osBrush);
	DeleteObject(myBrush);
}

void OBject::setPlayer(WPARAM wParam,HWND hWnd)
{		
	a = (playerPlace.left -100 ) / 30;
	b = (playerPlace.top - 100) / 30;

	switch (wParam)
	{
	case VK_RIGHT:
	{	
		if (area[a + 1][b] == 1) 
		{
			break;
		}
		playerPlace.left += 30;
		playerPlace.right = playerPlace.left + 30;

	}
	break;
	case VK_UP:
	{	
		if (area[a][b-1] == 1)
		{
			break;
		}
			playerPlace.top -= 30;
			playerPlace.bottom = playerPlace.top + 30;
	}
	break;
	case VK_LEFT:
	{	
		if (area[a-1][b] == 1)
		{
			break;
		}
			playerPlace.left -= 30;
			playerPlace.right = playerPlace.left + 30;
	}
	break;
	case VK_DOWN:
	{	
		if (area[a][b + 1] == 1)
		{
			break;
		}
			playerPlace.top += 30;
			playerPlace.bottom = playerPlace.top + 30;
	}
	break;
	}

	if (IntersectRect(&out, &playerPlace, &enemyPlace))
	{
		KillTimer(hWnd, 1);
		MessageBox(hWnd, L"������ ���߽��ϴ�", L"��������", MB_OK);
	}

}

void OBject::setEnemy(HWND hWnd) 
{
	std::pair<int, int> nextMove = bfs((enemyPlace.left - 100) / 30, (enemyPlace.top - 100) / 30);

	int newX = nextMove.first;
	int newY = nextMove.second;


	// �� ��ġ�� ���� �̵���ŵ�ϴ�.
	enemyPlace.left = 100 + newX * 30;
	enemyPlace.right = enemyPlace.left + 30;
	enemyPlace.top = 100 + newY * 30;
	enemyPlace.bottom = enemyPlace.top + 30;



	if (IntersectRect(&out, &playerPlace, &enemyPlace))
	{
		KillTimer(hWnd, 1);
		MessageBox(hWnd, L"������ ���߽��ϴ�", L"��������", MB_OK);
	}
}

std::pair<int,int> OBject::bfs(int start_x, int start_y ) 
{
	// ť�� ����Ͽ� BFS�� ���� �� ���Ҵ� (x, y) ��ǥ
	std::queue<std::pair<int, int>> q;

	// �湮�� ��带 �����ϱ� ���� ���� �ʱⰪ false
	std::vector<std::vector<bool>> visited(30, std::vector<bool>(25, false));

	// �� ����� �θ� ��带 �����ϴ� ���� ��� �������� ���
	std::vector<std::vector<std::pair<int, int>>> parent(30, std::vector<std::pair<int, int>>(25));

	// ���� ��ġ�� ť�� �ְ� �湮�ߴٰ� ǥ��
	q.push({ start_x, start_y });
	visited[start_x][start_y] = true;

	// ��, ��, ��, �� �̵� �迭
	int dx[] = { 1, 0, -1, 0 };
	int dy[] = { 0, 1, 0, -1 };

	// �÷��̾��� ���� ��ġ�� ���
	int player_x = (playerPlace.left - 100) / 30;
	int player_y = (playerPlace.top - 100) / 30;

	// BFS ���� ����
	while (!q.empty()) {
		// ť���� ���� ��ġ�� ������
		int x = q.front().first;
		int y = q.front().second;
		q.pop();

		// �÷��̾ ã�Ҵ��� Ȯ��
		if (x == player_x && y == player_y) {
			// �÷��̾ ��θ� ������
			while (x != start_x || y != start_y) {
				// ���� ��ġ�� �θ� ���
				int px = parent[x][y].first;
				int py = parent[x][y].second;
				// ���� ��ġ �ٷ� ���� ��ġ ��ȯ
				if (px == start_x && py == start_y) {
					return { x, y };  // ���� �̵��� ��ġ ��ȯ
				}
				// ����ؼ� ������
				x = px;
				y = py;
			}
		}

		// ���� ��ġ���� ��, ��, ��, ��� �̵�
		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];

			// �� ��ġ�� ��ȿ Ȯ��
			// 1. �� ���� ��
			// 2. �湮 ����(�湮 ���Ѱ�)
			// 3. ���� �ƴ��� (area[nx][ny] != 1)
			if (nx >= 0 && nx < 30 && ny >= 0 && ny < 25 && !visited[nx][ny] && area[nx][ny] != 1) {
				// �� ��ġ�� ť�� �߰�
				q.push({ nx, ny });
				// �� ��ġ�� �湮 ǥ��
				visited[nx][ny] = true;
				// �� ��ġ�� �θ� ���� ��ġ ����
				parent[nx][ny] = { x, y };
			}
		}
	}

	// �÷��̾�� ���� ��� Ȯ�� �Ұ� ���� ��ġ ��ȯ
	return { start_x, start_y };

}