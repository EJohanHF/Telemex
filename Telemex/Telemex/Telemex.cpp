// Telemex.cpp : Define el punto de entrada de la aplicación.
//

#include "framework.h"
#include "Telemex.h"
#include <vector>
#include <string>
#include "Empleado.h"
using std::vector;
using std::wstring;
#include <sstream>

#include <commctrl.h>
#pragma comment(lib, "comctl32.lib")

#define MAX_LOADSTRING 100




std::vector<Empleado> empleados = {
    {101, L"Carlos Perez", L"PERC750821HG1", L"2021-05-03"},
    {102, L"Ana Torres", L"TORA860101GJ3", L"2022-01-15"}
};

void LlenarListView(HWND hListView, const std::vector<Empleado>& empleados) {
    ListView_DeleteAllItems(hListView);

    for (size_t i = 0; i < empleados.size(); ++i) {
        const Empleado& emp = empleados[i];

        std::wstringstream ss;
        ss << emp.codigoEmpleado;
        std::wstring codigoStr = ss.str();

        LVITEM item = { 0 };
        item.mask = LVIF_TEXT;
        item.iItem = static_cast<int>(i);
        item.pszText = const_cast<LPWSTR>(codigoStr.c_str());
        ListView_InsertItem(hListView, &item);

        ListView_SetItemText(hListView, static_cast<int>(i), 1, const_cast<LPWSTR>(emp.nombre.c_str()));
        ListView_SetItemText(hListView, static_cast<int>(i), 2, const_cast<LPWSTR>(emp.rfc.c_str()));
        ListView_SetItemText(hListView, static_cast<int>(i), 3, const_cast<LPWSTR>(emp.fechaIngreso.c_str()));
    }
}

// Variables globales:
HINSTANCE hInst;                                // instancia actual
WCHAR szTitle[MAX_LOADSTRING];                  // Texto de la barra de título
WCHAR szWindowClass[MAX_LOADSTRING];            // nombre de clase de la ventana principal

// Declaraciones de funciones adelantadas incluidas en este módulo de código:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// Controles para "Nuevo Empleado"
HWND hLblCodigo, hEditCodigo;
HWND hLblNombre, hEditNombre;
HWND hLblRFC, hEditRFC;
HWND hLblFecha, hEditFecha;
HWND hListView; // Para la lista de empleados
HWND hBtnGuardar;


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // Inicializar cadenas globales
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_TELEMEX, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Realizar la inicialización de la aplicación:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TELEMEX));

    MSG msg;

    // Bucle principal de mensajes:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int)msg.wParam;
}

//
//  FUNCIÓN: MyRegisterClass()
//
//  PROPÓSITO: Registra la clase de ventana.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TELEMEX));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_TELEMEX);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCIÓN: InitInstance(HINSTANCE, int)
//
//   PROPÓSITO: Guarda el identificador de instancia y crea la ventana principal
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    hInst = hInstance; // Almacenar identificador de instancia en una variable global

    // Inicializar controles comunes (necesario para ListView)
    INITCOMMONCONTROLSEX icex = { sizeof(INITCOMMONCONTROLSEX), ICC_LISTVIEW_CLASSES };
    InitCommonControlsEx(&icex);

    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, 0, 800, 400, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    // Crear controles para ingresar nuevo empleado (ocultos inicialmente)
    hLblCodigo = CreateWindowW(L"STATIC", L"Código:", WS_CHILD | WS_VISIBLE,
        20, 20, 80, 20, hWnd, nullptr, hInst, nullptr);
    hEditCodigo = CreateWindowW(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER,
        110, 20, 200, 20, hWnd, nullptr, hInst, nullptr);

    hLblNombre = CreateWindowW(L"STATIC", L"Nombre:", WS_CHILD | WS_VISIBLE,
        20, 60, 80, 20, hWnd, nullptr, hInst, nullptr);
    hEditNombre = CreateWindowW(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER,
        110, 60, 200, 20, hWnd, nullptr, hInst, nullptr);

    hLblRFC = CreateWindowW(L"STATIC", L"RFC:", WS_CHILD | WS_VISIBLE,
        20, 100, 80, 20, hWnd, nullptr, hInst, nullptr);
    hEditRFC = CreateWindowW(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER,
        110, 100, 200, 20, hWnd, nullptr, hInst, nullptr);

    hLblFecha = CreateWindowW(L"STATIC", L"Fecha Ingreso:", WS_CHILD | WS_VISIBLE,
        20, 140, 100, 20, hWnd, nullptr, hInst, nullptr);
    hEditFecha = CreateWindowW(L"EDIT", L"", WS_CHILD | WS_VISIBLE | WS_BORDER,
        130, 140, 180, 20, hWnd, nullptr, hInst, nullptr);

    hBtnGuardar = CreateWindowW(L"BUTTON", L"Guardar",
        WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
        110, 180, 100, 25,
        hWnd, (HMENU)1001, hInst, nullptr);  // 1001 = ID del botón


    // Ocultar los controles de edición inicialmente
    ShowWindow(hLblCodigo, SW_HIDE);
    ShowWindow(hEditCodigo, SW_HIDE);
    ShowWindow(hLblNombre, SW_HIDE);
    ShowWindow(hEditNombre, SW_HIDE);
    ShowWindow(hLblRFC, SW_HIDE);
    ShowWindow(hEditRFC, SW_HIDE);
    ShowWindow(hLblFecha, SW_HIDE);
    ShowWindow(hEditFecha, SW_HIDE);
    ShowWindow(hBtnGuardar, SW_HIDE);

    // Primero crea el ListView (esto debe ir en InitInstance o similar)
    hListView = CreateWindowW(WC_LISTVIEW, L"",
        WS_CHILD | WS_BORDER | LVS_REPORT | LVS_SINGLESEL,
        100, 1, 600, 200, // x, y, width, height
        hWnd, nullptr, hInst, nullptr);

    // Asegúrate de que hListView no sea NULL
    if (!hListView) {
        MessageBoxW(hWnd, L"No se pudo crear el ListView.", L"Error", MB_OK | MB_ICONERROR);
        return FALSE;
    }

    // Crear columnas
    LVCOLUMNW lvc = { 0 };
    lvc.mask = LVCF_TEXT | LVCF_WIDTH | LVCF_SUBITEM;

    // Columna 0 - Código
    lvc.cx = 80;
    lvc.pszText = (LPWSTR)L"Código";
    lvc.iSubItem = 0;
    ListView_InsertColumn(hListView, 0, &lvc);

    // Columna 1 - Nombre
    lvc.cx = 150;
    lvc.pszText = (LPWSTR)L"Nombre";
    lvc.iSubItem = 1;
    ListView_InsertColumn(hListView, 1, &lvc);

    // Columna 2 - RFC
    lvc.cx = 150;
    lvc.pszText = (LPWSTR)L"RFC";
    lvc.iSubItem = 2;
    ListView_InsertColumn(hListView, 2, &lvc);

    // Columna 3 - Fecha Ingreso
    lvc.cx = 120;
    lvc.pszText = (LPWSTR)L"Fecha Ingreso";
    lvc.iSubItem = 3;
    ListView_InsertColumn(hListView, 3, &lvc);


    return TRUE;
}

//
//  FUNCIÓN: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PROPÓSITO: Procesa mensajes de la ventana principal.
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
    {
        int wmId = LOWORD(wParam);
        // Analizar las selecciones de menú:
        switch (wmId)
        {
        case IDM_ABOUT:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
            break;
        case IDM_EXIT:
            DestroyWindow(hWnd);
            break;
        case ID_EMPLEADO_NUEVO:
            // Mostrar campos
            ShowWindow(hLblCodigo, SW_SHOW);
            ShowWindow(hEditCodigo, SW_SHOW);
            ShowWindow(hLblNombre, SW_SHOW);
            ShowWindow(hEditNombre, SW_SHOW);
            ShowWindow(hLblRFC, SW_SHOW);
            ShowWindow(hEditRFC, SW_SHOW);
            ShowWindow(hLblFecha, SW_SHOW);
            ShowWindow(hEditFecha, SW_SHOW);
            ShowWindow(hBtnGuardar, SW_SHOW);

            // Ocultar lista
            ShowWindow(hListView, SW_HIDE);
            break;

        case ID_EMPLEADO_LISTA:
            // Ocultar campos
            ShowWindow(hLblCodigo, SW_HIDE);
            ShowWindow(hEditCodigo, SW_HIDE);
            ShowWindow(hLblNombre, SW_HIDE);
            ShowWindow(hEditNombre, SW_HIDE);
            ShowWindow(hLblRFC, SW_HIDE);
            ShowWindow(hEditRFC, SW_HIDE);
            ShowWindow(hLblFecha, SW_HIDE);
            ShowWindow(hEditFecha, SW_HIDE);

            // Mostrar lista
            ShowWindow(hListView, SW_SHOW);

            extern std::vector<Empleado> empleados;
LlenarListView(hListView, empleados);
            break;
        default:
            return DefWindowProc(hWnd, message, wParam, lParam);
        }
    }
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Controlador de diálogo "Acerca de".
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
