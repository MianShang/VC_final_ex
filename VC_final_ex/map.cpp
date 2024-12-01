#include "map.h"

void Map_Area::Setmap()
{
    // �� �ʱ�ȭ
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            map_area[i][j] = item;
        }
    }

    // �� �׵θ� ����
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

    // ��� �� ����
    for (int i = 2; i < width - 2; i += 2)
    {
        for (int j = 2; j < height - 2; j += 2)
        {
            map_area[i][j] = wall;

            // �����¿� �� �����ϰ� �� �������� �� ���� ����
            int direction = rand() % 4;
            switch (direction)
            {
            case 0: if (j > 2) map_area[i][j - 1] = wall; break;  // ��
            case 1: if (j < height - 3) map_area[i][j + 1] = wall; break;  // ��
            case 2: if (i > 2) map_area[i - 1][j] = wall; break;  // ��
            case 3: if (i < width - 3) map_area[i + 1][j] = wall; break;  // ��
            }
        }
    }

    // �߰� ��� ���� (�����ϰ� �� ���� ���� ����)
    for (int k = 0; k < 10; k++)
    {
        int i = 2 + rand() % (width - 4);
        int j = 2 + rand() % (height - 4);
        map_area[i][j] = item;
    }

    // �÷��̾� ���� ��ġ ����
    map_area[1][1] = start;

    // ���� ���� ���� ��ġ ����
    int enemy_count = 4; // ���� ����
    while (enemy_count > 0)
    {
        int i = 1 + rand() % (width - 2);  // �� �׵θ��� ������ ���� ��ǥ
        int j = 1 + rand() % (height - 2);

        // �� ���������� �� ����
        if (map_area[i][j] == item || map_area[i][j] == space)
        {
            map_area[i][j] = enemy;
            enemy_count--;
        }
    }

    // ������ �� ���� ���
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
    
    wsprintf(bufi, L"������ ���� ���� : %d", g_item);
    SetBkMode(hdc, TRANSPARENT); // �޹�� ����
    SetTextColor(hdc, RGB(255, 255, 255)); // ���ڻ� ����
    TextOut(hdc, 1100, 300, bufi, lstrlenW(bufi));
    wsprintf(bufi, L"�� ������ : %d", f_item);
    TextOut(hdc, 1100, 250, bufi, lstrlenW(bufi));

    ///�� �׸��� �ڵ�
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
        MessageBox(hWnd, L"��������", L"��� �������� �Ծ����ϴ�", MB_OK);
        SendMessage(hWnd, WM_COMMAND, 2, NULL);
    }

}


void Map_Area::resetGame(std::unique_ptr<OBject>& object)
{   
    object->enemyplaces.clear();

    object->playerPlace = { 130,130,160,160 };

    // �� ���� �ʱ�ȭ
    Setmap();


    // ��ü �ʱ�ȭ
    object->setAreaCopy(map_area);

    // ������ ���� �ʱ�ȭ
    g_item = 0;

    // ȭ�� ����
    InvalidateRect(NULL, NULL, TRUE);
}

