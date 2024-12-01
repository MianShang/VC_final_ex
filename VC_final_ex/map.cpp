#include "map.h"

void Map_Area::Setmap()
{
    // 맵 초기화
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            map_area[i][j] = item;
        }
    }

    // 벽 테두리 설정
    for (int i = 0; i < width; i++)
    {
        map_area[i][0] = wall;
        map_area[i][height - 1] = wall;
    }
    for (int i = 0; i < height; i++)
    {
        map_area[0][i] = wall;
        map_area[width - 1][i] = wall;
    }

    // 가운데 벽 설정
    for (int i = 2; i < width - 2; i += 2)
    {
        for (int j = 2; j < height - 2; j += 2)
        {
            map_area[i][j] = wall;

            // 상하좌우 중 랜덤하게 한 방향으로 벽 연장 설정
            int direction = rand() % 4;
            switch (direction)
            {
            case 0: if (j > 2) map_area[i][j - 1] = wall; break;  // 상
            case 1: if (j < height - 3) map_area[i][j + 1] = wall; break;  // 하
            case 2: if (i > 2) map_area[i - 1][j] = wall; break;  // 좌
            case 3: if (i < width - 3) map_area[i + 1][j] = wall; break;  // 우
            }
        }
    }

    // 추가 경로 생성 (랜덤하게 몇 개의 벽을 제거)
    for (int k = 0; k < 10; k++)
    {
        int i = 2 + rand() % (width - 4);
        int j = 2 + rand() % (height - 4);
        map_area[i][j] = item;
    }

    // 플레이어 시작 위치 설정
    map_area[1][1] = start;

    // 적의 랜덤 시작 위치 설정
    int enemy_count = 4; // 적의 개수
    while (enemy_count > 0)
    {
        int i = 1 + rand() % (width - 2);  // 맵 테두리를 제외한 내부 좌표
        int j = 1 + rand() % (height - 2);

        // 빈 공간에서만 적 생성
        if (map_area[i][j] == item || map_area[i][j] == space)
        {
            map_area[i][j] = enemy;
            enemy_count--;
        }
    }

    // 아이템 총 개수 계산
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            if (map_area[i][j] == item)
            {
                f_item++;
            }
        }
    }
}


void Map_Area::Getmap(HDC hdc, HWND hWnd, RECT player)
{
    
    wsprintf(bufi, L"아이템 먹은 갯수 : %d", g_item);
    SetBkMode(hdc, TRANSPARENT); // 뒷배경 투명
    SetTextColor(hdc, RGB(255, 255, 255)); // 글자색 변경
    TextOut(hdc, 1100, 300, bufi, lstrlenW(bufi));
    wsprintf(bufi, L"총 아이템 : %d", f_item);
    TextOut(hdc, 1100, 250, bufi, lstrlenW(bufi));

    ///맵 그리는 코드
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            box.left = 100 + (i * 30);
            box.top = 100 + (j * 30);
            box.right = box.left + 30;
            box.bottom = box.top + 30;

            if (map_area[i][j] == wall)
            {   
                Rectangle(hdc, box.left, box.top, box.right, box.bottom);
            }
            else if (map_area[i][j] == item)
            {
                if (IntersectRect(&a, &player, &box)) {
                    map_area[i][j] = space;
                    g_item++;
                }

                box.left += 10;
                box.top += 10;
                box.right = box.left + 10;
                box.bottom = box.top + 10;
                Ellipse(hdc, box.left, box.top, box.right, box.bottom);
            }

        }
    }

    if (f_item == g_item) 
    {
        KillTimer(hWnd, 1);
        g_item++;
        for (int i = 0; i < width; i++)
        {
            for (int j = 0; j < height; j++)
            {
                if (map_area[i][j] == item)
                {
                     map_area[i][j] = space;
                }
            }
        }
        InvalidateRect(hWnd, NULL, FALSE);
        MessageBox(hWnd, L"게임종료", L"모든 아이템을 먹었습니다", MB_OK);
        SendMessage(hWnd, WM_COMMAND, 2, NULL);
    }

}


void Map_Area::resetGame(std::unique_ptr<OBject>& object)
{   
    object->enemyplaces.clear();

    object->playerPlace = { 130,130,160,160 };

    // 맵 상태 초기화
    Setmap();


    // 객체 초기화
    object->setAreaCopy(map_area);

    // 아이템 상태 초기화
    g_item = 0;

    // 화면 갱신
    InvalidateRect(NULL, NULL, TRUE);
}

