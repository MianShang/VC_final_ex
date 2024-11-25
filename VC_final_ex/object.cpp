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
		MessageBox(hWnd, L"적에게 당했습니다", L"게임종료", MB_OK);
	}

}

void OBject::setEnemy(HWND hWnd) 
{
	std::pair<int, int> nextMove = bfs((enemyPlace.left - 100) / 30, (enemyPlace.top - 100) / 30);

	int newX = nextMove.first;
	int newY = nextMove.second;


	// 새 위치로 적을 이동시킵니다.
	enemyPlace.left = 100 + newX * 30;
	enemyPlace.right = enemyPlace.left + 30;
	enemyPlace.top = 100 + newY * 30;
	enemyPlace.bottom = enemyPlace.top + 30;



	if (IntersectRect(&out, &playerPlace, &enemyPlace))
	{
		KillTimer(hWnd, 1);
		MessageBox(hWnd, L"적에게 당했습니다", L"게임종료", MB_OK);
	}
}

std::pair<int,int> OBject::bfs(int start_x, int start_y ) 
{
	// 큐를 사용하여 BFS를 구현 각 원소는 (x, y) 좌표
	std::queue<std::pair<int, int>> q;

	// 방문한 노드를 추적하기 위한 벡터 초기값 false
	std::vector<std::vector<bool>> visited(30, std::vector<bool>(25, false));

	// 각 노드의 부모 노드를 저장하는 벡터 경로 역추적에 사용
	std::vector<std::vector<std::pair<int, int>>> parent(30, std::vector<std::pair<int, int>>(25));

	// 시작 위치를 큐에 넣고 방문했다고 표시
	q.push({ start_x, start_y });
	visited[start_x][start_y] = true;

	// 상, 하, 좌, 우 이동 배열
	int dx[] = { 1, 0, -1, 0 };
	int dy[] = { 0, 1, 0, -1 };

	// 플레이어의 현재 위치를 계산
	int player_x = (playerPlace.left - 100) / 30;
	int player_y = (playerPlace.top - 100) / 30;

	// BFS 메인 루프
	while (!q.empty()) {
		// 큐에서 현재 위치를 가져옴
		int x = q.front().first;
		int y = q.front().second;
		q.pop();

		// 플레이어를 찾았는지 확인
		if (x == player_x && y == player_y) {
			// 플레이어를 경로를 역추적
			while (x != start_x || y != start_y) {
				// 현재 위치의 부모 노드
				int px = parent[x][y].first;
				int py = parent[x][y].second;
				// 시작 위치 바로 다음 위치 반환
				if (px == start_x && py == start_y) {
					return { x, y };  // 다음 이동할 위치 반환
				}
				// 계속해서 역추적
				x = px;
				y = py;
			}
		}

		// 현재 위치에서 상, 하, 좌, 우로 이동
		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];

			// 새 위치가 유효 확인
			// 1. 맵 범위 내
			// 2. 방문 여부(방문 안한곳)
			// 3. 벽이 아닌지 (area[nx][ny] != 1)
			if (nx >= 0 && nx < 30 && ny >= 0 && ny < 25 && !visited[nx][ny] && area[nx][ny] != 1) {
				// 새 위치를 큐에 추가
				q.push({ nx, ny });
				// 새 위치를 방문 표시
				visited[nx][ny] = true;
				// 새 위치의 부모를 현재 위치 설정
				parent[nx][ny] = { x, y };
			}
		}
	}

	// 플레이어에게 도달 경로 확인 불가 현재 위치 반환
	return { start_x, start_y };

}