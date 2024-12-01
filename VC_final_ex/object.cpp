#include "object.h"

int a, b;

void OBject::setAreaCopy(int area[][25])
{
	for (int i = 0; i < 30; i++) 
	{
		for (int j = 0; j < 25; j++) 
		{	
			this->area[i][j] = area[i][j];
			
			if (area[i][j] == 4) {
				enemyPlace.left = 100 + i * 30;
				enemyPlace.top = 100 + j * 30;
				enemyPlace.right = enemyPlace.left + 30;
				enemyPlace.bottom = enemyPlace.top + 30;
				enemyplaces.push_back(enemyPlace);
			}
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
	for (const auto& enemy : enemyplaces) 
	{
		Ellipse(memDC, enemy.left, enemy.top, enemy.right, enemy.bottom);
	}
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

	for (const auto& enemy : enemyplaces) {

		if (IntersectRect(&out, &playerPlace, &enemy))
		{
			KillTimer(hWnd, 1);
			KillTimer(hWnd, 2);
			SendMessage(hWnd, WM_COMMAND, 2, NULL);
			MessageBox(hWnd, L"게임 종료", L"적에게 당했습니다", MB_OK);
			return;
		}
	}

}

void OBject::setEnemy(HWND hWnd)
{
	// 적들의 새 위치를 기록할 집합
	std::set<std::pair<int, int>> occupied_positions;

	// 모든 적의 현재 위치를 기록
	for (const auto& enemy : enemyplaces)
	{
		int x = (enemy.left - 100) / 30;
		int y = (enemy.top - 100) / 30;
		occupied_positions.insert({ x, y });
	}

	// 각 적에 대해 이동 처리
	for (auto& enemy : enemyplaces)
	{
		int currentX = (enemy.left - 100) / 30;
		int currentY = (enemy.top - 100) / 30;

		// 현재 위치를 초기화
		area[currentX][currentY] = 0;

		// BFS로 다음 이동 위치 계산
		nextMove = bfs(currentX, currentY);

		int newX = nextMove.first;
		int newY = nextMove.second;

		// 이동하려는 위치가 다른 적과 충돌하면 다른 방향 탐색
		if (occupied_positions.count({ newX, newY }) > 0)
		{
			bool found_alternative = false;

			// 상하좌우 대체 경로 탐색
			int dx[] = { 1, 0, -1, 0 };
			int dy[] = { 0, 1, 0, -1 };

			for (int i = 0; i < 4; i++)
			{
				int altX = currentX + dx[i];
				int altY = currentY + dy[i];

				// 이동 가능한 위치인지 확인
				if (altX >= 0 && altX < 30 && altY >= 0 && altY < 25 &&
					area[altX][altY] != 1 && occupied_positions.count({ altX, altY }) == 0)
				{
					newX = altX;
					newY = altY;
					found_alternative = true;
					break;
				}
			}

			// 대체 경로를 찾지 못하면 제자리 유지
			if (!found_alternative)
			{
				newX = currentX;
				newY = currentY;
			}
		}

		// 새 위치를 기록
		occupied_positions.insert({ newX, newY });

		// 적의 새 위치로 이동
		enemy.left = 100 + newX * 30;
		enemy.right = enemy.left + 30;
		enemy.top = 100 + newY * 30;
		enemy.bottom = enemy.top + 30;

		// 맵에 새 위치 반영
		area[newX][newY] = 4;
		
	}

	for (const auto& enemy : enemyplaces) {

		if (IntersectRect(&out, &playerPlace, &enemy))
		{
			KillTimer(hWnd, 1);
			KillTimer(hWnd, 2);
			SendMessage(hWnd, WM_COMMAND, 2, NULL);
			MessageBox(hWnd, L"게임 종료", L"적에게 당했습니다", MB_OK);
			return;
		}
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