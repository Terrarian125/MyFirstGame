// MyFirstGame.cpp 

#include "framework.h"
#include "MyFirstGame.h"
#include "Direct3D.h"
#include "Quad.h"
#include "resource.h"
#include "Camera.h"
#include "Texture.h"
constexpr auto MAX_LOADSTRING = 100;


const wchar_t* WIN_CLASS_NAME = L"SAMPLE GAME WINDOW";
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
// グローバル変数の宣誓

// グローバル変数:
HINSTANCE hInst;                                // 現在のインターフェイス
WCHAR szTitle[MAX_LOADSTRING];                  // タイトル バーのテキスト
wchar_t szWindowClass[] = L"MyWindowClass";       // メイン ウィンドウ クラス名
//WCHAR szWindowClass[MAX_LOADSTRING];            // メイン ウィンドウ クラス名

// このコード モジュールに含まれる関数の宣言を転送します:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK    SecondWndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
   _In_opt_ HINSTANCE hPrevInstance,
   _In_ LPWSTR    lpCmdLine,
   _In_ int       nCmdShow)
{
   UNREFERENCED_PARAMETER(hPrevInstance);
   UNREFERENCED_PARAMETER(lpCmdLine);

   LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
   //LoadStringW(hInstance, IDC_MYFIRSTGAME, szWindowClass, MAX_LOADSTRING);
   MyRegisterClass(hInstance);

   if (!InitInstance(hInstance, nCmdShow))
   {
       return FALSE;
   }

   // Direct3Dの初期化
   HRESULT hr = S_OK; 
   // hr = Direct3D::Initialize(WINDOW_WIDTH, WINDOW_HEIGHT, hWnd);
   if (FAILED(hr))
   {
       MessageBox(nullptr, L"Direct3Dの初期化に失敗しました", L"エラー", MB_OK);
       return hr;
   }

   HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_MYFIRSTGAME));

   MSG msg = {};

   Quad* q = new Quad();
   hr = q->Initialize();
   if (FAILED(hr))
   {
       return hr;
   }

   // メイン メッセージ ループ:
   while (true)
   {
       if (PeekMessage(&msg, NULL, 0U, 0U, PM_REMOVE))
       {
           TranslateMessage(&msg);
           DispatchMessage(&msg);
       }
       else
       {
           Camera::Update();
           Direct3D::BeginDraw();

           XMMATRIX mat = XMMatrixRotationY(XMConvertToRadians(45));
           q->Draw(mat);
       }
   }

   q->Release();
   SAFE_DELETE(q);
   Direct3D::Release();

   return (int)msg.wParam;
}

// ウィンドウクラス登録
//  WndProc のプロトタイプ宣言
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

//  MyRegisterClass の定義
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex = {};
    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc; // ← WndProc をここで使用
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MYFIRSTGAME));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = nullptr;
    wcex.lpszClassName = szWindowClass; // ← グローバル変数または定数として別で定義
    wcex.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

// インスタンス初期化
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance;//現在のアプリケーションインスタンスのハンドル

    //ウィンドウサイズの計算
    RECT winRect = { 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
    AdjustWindowRect(&winRect, WS_OVERLAPPEDWINDOW, FALSE);
    int winW = winRect.right - winRect.left;     //ウィンドウ幅
    int winH = winRect.bottom - winRect.top;     //ウィンドウ高さ

    HWND g_hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, winW, winH, nullptr, nullptr, hInstance, nullptr);

    return TRUE;
}

// バージョン情報ボックスのメッセージ ハンドラー
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
