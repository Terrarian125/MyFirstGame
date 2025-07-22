#include "framework.h"
#include "MyFirstGame.h"
#include "Direct3D.h"
#include "Quad.h"
#include "resource.h"
#include "Camera.h"
#include "Texture.h"
#include "Dice.h"    // Diceを追加
#include <DirectXMath.h>

constexpr auto MAX_LOADSTRING = 100;

using namespace DirectX;

const wchar_t* WIN_CLASS_NAME = L"SAMPLE GAME WINDOW";
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;

HWND hWnd;
HINSTANCE hInst;
WCHAR szTitle[MAX_LOADSTRING];
wchar_t szWindowClass[] = L"MyWindowClass";

ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);

// ここでDiceポインタをグローバルに持つ
Dice* g_dice = nullptr;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HRESULT hr = Direct3D::Initialize(WINDOW_WIDTH, WINDOW_HEIGHT, hWnd);
    if (FAILED(hr))
    {
        MessageBox(nullptr, L"Direct3Dの初期化に失敗しました", L"エラー", MB_OK);
        return hr;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MYFIRSTGAME));

    MSG msg = {};

    Camera::Initialize();

    // Diceの初期化（ここで生成・初期化）
    g_dice = new Dice();
    hr = g_dice->Initialize();
    if (FAILED(hr))
    {
        MessageBox(nullptr, L"Diceの初期化に失敗しました", L"エラー", MB_OK);
        return hr;
    }

    while (true)
    {
        if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
        {
            if (msg.message == WM_QUIT) break;

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else
        {
            Camera::Update();
            Direct3D::BeginDraw();

            // 回転行列
            static float angle = 0.0f;
            angle += 0.084f;
            if (angle > 360.0f) angle -= 360.0f;
            XMMATRIX rot = XMMatrixRotationY(XMConvertToRadians(angle));

            g_dice->Draw(rot);

            Direct3D::EndDraw();
        }
    }

    // 終了時に解放
    if (g_dice)
    {
        delete g_dice;
        g_dice = nullptr;
    }

    Direct3D::Release();

    return (int)msg.wParam;
}

ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex = {};
    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MYFIRSTGAME));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance;

    RECT winRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
    AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, FALSE);
    int winW = winRect.right - winRect.left;
    int winH = winRect.bottom - winRect.top;

    hWnd = CreateWindowW(
        szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, winW, winH,
        nullptr, nullptr, hInstance, nullptr
    );

    if (!hWnd) return FALSE;

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    return TRUE;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
}
