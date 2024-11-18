#include "map.h"

void Map_Area::Setmap()
{   

    for (int i = 0; i < width; i ++)
    {
        for (int j = 0; j < height; j ++)
        {
            map_area[i][j] = item;
        }
    }

    ///�� �׵θ� ����
    for (int i = 0; i < width; i++)
    {
        map_area[i][0] = wall;
        map_area[i][height-1] = wall;
    }
    for (int i = 0; i < height; i++)
    {
        map_area[0][i] = wall;
        map_area[width-1][i] = wall;
    }

    // ��� �� ����
    for (int i = 2; i < width - 2; i += 2)
    {
        for (int j = 2; j < height - 2; j += 2)
        {
            map_area[i][j] = wall;

            /// �����¿� �� �����ϰ� �� �������� �� ���� ����
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
        map_area[i][j] = 0;
    }

    ///�÷��̾� ������ġ ����
    map_area[1][1] = start;
    ///�� ������ġ ����
    map_area[28][23] = enemy;

}

void Map_Area::Getmap(HDC hdc) 
{
   /* for (int i = 0; i < width; i++) {
        if (map_area[i][0] == wall)
        {
            Rectangle(hdc, box.left, box.top, box.right, box.bottom);
            Rectangle(hdc, box.left, 750, box.right, 780);
            box.left = i*30 ;
            box.right = box.left + 30;

        }
    }
    box.top = 0;
    box.bottom = box.top + 30;
    for (int i = 0; i < height + 1; i++)
    {
        if (map_area[0][i] == wall)
        {
            Rectangle(hdc, 0, box.top, 30, box.bottom);
            Rectangle(hdc, 900, box.top, 930, box.bottom);
            box.top = i*30;
            box.bottom = box.top + 30;

        }
    }*/

    
    ///�� �׸��� �ڵ�
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {   
            box.left = i * 30;
            box.top = j * 30;
            box.right = box.left + 30;
            box.bottom = box.top + 30;

            if (map_area[i][j] == wall)
            {
                Rectangle(hdc, box.left, box.top, box.right, box.bottom);
            }
            if(map_area[i][j]== item)
            {   
                box.left += 10;
                box.top += 10;
                box.right = box.left + 10;
                box.bottom = box.top + 10;
                Ellipse(hdc, box.left, box.top, box.right, box.bottom);
            }
        }
    }

}