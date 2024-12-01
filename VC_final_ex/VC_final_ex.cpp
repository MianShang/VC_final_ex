// VC_final_ex.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#include "framework.h"
#include "VC_final_ex.h"
#include <time.h>

#define MAX_LOADSTRING 100

// 전역 변수:
HINSTANCE hInst;                                // 현재 인스턴스입니다.
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.
///윈도우 창크기 구하는 RECT변수
RECT wn_Size = {0,0,2000,2000};

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.
    

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_VCFINALEX, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // 애플리케이션 초기화를 수행합니다:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_VCFINALEX));

    MSG msg;

    // 기본 메시지 루프입니다:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_VCFINALEX));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_VCFINALEX);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   함수: InitInstance(HINSTANCE, int)
//
//   용도: 인스턴스 핸들을 저장하고 주 창을 만듭니다.
//
//   주석:
//
//        이 함수를 통해 인스턴스 핸들을 전역 변수에 저장하고
//        주 프로그램 창을 만든 다음 표시합니다.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // 인스턴스 핸들을 전역 변수에 저장합니다.

   HWND hWnd = CreateWindowW(szWindowClass, L"202307063_임지섭_기말과제", WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, 1400, 1000, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  함수: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  용도: 주 창의 메시지를 처리합니다.
//
//  WM_COMMAND  - 애플리케이션 메뉴를 처리합니다.
//  WM_PAINT    - 주 창을 그립니다.
//  WM_DESTROY  - 종료 메시지를 게시하고 반환합니다.
//
//

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {   
        static HDC hdc;
        static HDC memDC;
        static HBITMAP MyBitmap, OldBitmap;

    case WM_TIMER: 
    {
        if (gameStarted && wParam == 1)
        {
            object->setEnemy(hWnd);
            InvalidateRect(hWnd, NULL, FALSE);
        }

        if (2 == wParam) 
        {   
            map_area->SetPlayTime();
            InvalidateRect(hWnd, NULL, FALSE);
        }

    }
    break;
    case WM_CREATE: 
    {   

       

        map_area = std::make_unique<Map_Area>();  ///맵객체
        object = std::make_unique<OBject>(); // 플레이어 객체

        ///시작전 화면 크기 구하기
        GetClientRect(hWnd, &wn_Size);
        
        hdc = GetDC(hWnd);

        ///벽 지정 for문
        map_area->Setmap();
        memDC = CreateCompatibleDC(hdc); /// 백버퍼 핸들 생성
        object->setAreaCopy(map_area->map_area);
        
        // 버튼 생성
        hStartButton = CreateWindow(L"BUTTON", L"게임 시작",WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 1100, 400, 100, 30, hWnd, (HMENU)1, hInst, nullptr);
    }
    break;

    case WM_SIZE: 
    {   
        
       
        ///창크기 변경시 마다 창크기 구하기
        GetClientRect(hWnd,&wn_Size);

        MyBitmap = CreateCompatibleBitmap(hdc, wn_Size.right, wn_Size.bottom); ///back버퍼 도화지 크기 조정
        SelectObject(memDC, MyBitmap); ///도화지 선택
    }
    break;

    case WM_KEYDOWN: 
    {   

        if (wParam == VK_SPACE)
        {   
            ///치트 힘들면 space바로 클리어 확인
            map_area->g_item = map_area->f_item;
        }

        if (gameStarted) 
        {
            object->setPlayer(wParam, hWnd);
            InvalidateRect(hWnd, NULL, FALSE);
        }

            
    }
    break;

    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // 메뉴 선택을 구문 분석합니다:
            switch (wmId)
            {
            case 1:
            { // 버튼 클릭 이벤트
                if (!gameStarted)
                {
                    gameStarted = true; // 게임 시작 플래그 설정
                    SetTimer(hWnd, 1, 270, NULL); // 타이머 시작
                    ShowWindow(hStartButton, SW_HIDE); // 버튼 숨기기
                    SetTimer(hWnd, 2, 1000,NULL);
                }
            }
                break;
            case 2: 
                {   
                    gameStarted = false;
                    map_area->resetGame(object,hdc); // 게임 리셋
                    ShowWindow(hStartButton, SW_SHOW); // 버튼 다시 활성
                }
                break;
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: 여기에 hdc를 사용하는 그리기 코드를 추가합니다...

            ///후위버퍼를 myBrush로 칠하기
            HBRUSH myBrush = CreateSolidBrush(RGB(0, 0, 0));
            FillRect(memDC, &wn_Size, myBrush);
            DeleteObject(myBrush);


            ///맵 그리기를 후위 버퍼에 그리기
            map_area->Getmap(memDC,hWnd,object->playerPlace);

            ///플레이어, 적 Object를 그림
            object->drawPlayer(memDC);
            object->drawEnemy(memDC);
            ///후위 버퍼 내용을 전위 버퍼 hdc에 고속 복사
            BitBlt(hdc, 0,0, wn_Size.right,wn_Size.bottom, memDC, 0, 0, SRCCOPY); 
          
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        DeleteObject(MyBitmap);
        DeleteDC(memDC);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// 정보 대화 상자의 메시지 처리기입니다.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
