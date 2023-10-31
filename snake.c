//gcc snake.c -o snake -lgdi32
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define bodySize 500

const char g_szClassName[] = "snake";
int width = 610, heigth = 632;
int body[bodySize][2] = {{100, 0}, {50, 0}, {0, 0}};
int bodyCount = 3;
int fruit[2] = {400, 400};
char direction[12] = "foward";
int fruitCheckValue = 0;

void generateFruit(){
    int multiples50[] = {0, 50, 100, 150, 200, 250, 300, 350, 400, 450, 500, 550};
    fruit[0] = multiples50[(rand() % (12 + 1 - 1) + 1) - 1];
    fruit[1] = multiples50[(rand() % (12 + 1 - 1) + 1) - 1];
    printf("fruit x: %d y: %d\n", fruit[0], fruit[1]);
}

int gameOverCheck(int _body[bodySize][2]){
    if (
        (_body[0][0] + 50 >= width - 10 && strcmp(direction, "foward") == 0) || 
        (_body[0][0] - 50 < 0 && strcmp(direction, "backward") == 0) ||
        (_body[0][1] + 50 >= heigth - 32 && strcmp(direction, "downward") == 0) ||
        (_body[0][1] - 50 < 0 && strcmp(direction, "upward") == 0)
    ){
        return 1;
    }
    return 0;
}

int fruitCheck(int _body[bodySize][2]){
    if (
        (_body[0][0] + 50 == fruit[0] && _body[0][1] == fruit[1] && strcmp(direction, "foward") == 0) ||
        (_body[0][0] - 50 == fruit[0] && _body[0][1] == fruit[1] && strcmp(direction, "backward") == 0) ||
        (_body[0][1] + 50 == fruit[1] && _body[0][0] == fruit[0] && strcmp(direction, "downward") == 0) ||
        (_body[0][1] - 50 == fruit[1] && _body[0][0] == fruit[0] && strcmp(direction, "upward") == 0)
    ){
        return 1;
    }
    return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
    HDC hdc;
    PAINTSTRUCT ps;
    RECT retangle;

    switch(msg){
        case WM_CREATE:
            break;
        case WM_COMMAND:
            break;
        case WM_KEYDOWN:
            switch (wParam){
                case 'W':
                    strcpy(direction, "upward");
                    break;
                case 'A':
                    strcpy(direction, "backward");
                    break;
                case 'S':
                    strcpy(direction, "downward");
                    break;
                case 'D':
                    strcpy(direction, "foward");
                    break;
                case 'B':
                    InvalidateRect(hwnd, NULL, TRUE);
                    body[0][0] = 100;
                    body[0][1] = 0;
                    body[1][0] = 50;
                    body[1][1] = 0;
                    body[2][0] = 0;
                    body[2][1] = 0;
                    bodyCount = 3;
                    fruitCheckValue = 0;
                    strcpy(direction, "foward");
                    SetTimer(hwnd, 0, 200, (TIMERPROC) NULL);
                    break;
                default:
                    break;
            }
            InvalidateRect(hwnd, NULL, TRUE);
            break;
        case WM_TIMER: 
            switch (wParam) { 
                case 0:
                    int _body[bodySize][2];
                    memcpy(_body, body, sizeof(body));

                    if (gameOverCheck(_body)){
                        KillTimer(hwnd, 0);
                        MessageBox(NULL, "Game Over", "You Lose" , MB_OK);
                        break;
                    }

                    for(int i = 0; i < bodyCount; i++){
                        if (strcmp(direction, "foward") == 0){
                            if (i == 0){
                                body[i + 1][0] = _body[i][0];
                                body[i + 1][1] = _body[i][1];
                                body[i][0] = _body[i][0] + 50;

                                if (fruitCheck(_body)){
                                    fruitCheckValue = 1;
                                    bodyCount += 1;
                                    generateFruit();
                                }
                            } else {
                                if (i + 1 <= bodyCount - 1 || fruitCheckValue == 1){
                                    body[i + 1][0] = _body[i][0];
                                    body[i + 1][1] = _body[i][1];
                                    if (i + 1 > bodyCount - 1){
                                        fruitCheckValue = 0;
                                    }
                                }
                            }
                        } else if (strcmp(direction, "backward") == 0){
                            if (i == 0){
                                body[i + 1][0] = _body[i][0];
                                body[i + 1][1] = _body[i][1];
                                body[i][0] = _body[i][0] - 50;

                                if (fruitCheck(_body)){
                                    fruitCheckValue = 1;
                                    bodyCount += 1;
                                    generateFruit();
                                }
                            } else {
                                if (i + 1 <= bodyCount - 1){
                                    body[i + 1][0] = _body[i][0];
                                    body[i + 1][1] = _body[i][1];
                                }
                            }
                        } else if (strcmp(direction, "upward") == 0){
                            if (i == 0){
                                body[i + 1][0] = _body[i][0];
                                body[i + 1][1] = _body[i][1];
                                body[i][1] = _body[i][1] - 50;

                                if (fruitCheck(_body)){
                                    fruitCheckValue = 1;
                                    bodyCount += 1;
                                    generateFruit();
                                }
                            } else {
                                if (i + 1 <= bodyCount - 1){
                                    body[i + 1][0] = _body[i][0];
                                    body[i + 1][1] = _body[i][1];
                                }
                            }
                        } else if (strcmp(direction, "downward") == 0){
                            if (i == 0){
                                body[i + 1][0] = _body[i][0];
                                body[i + 1][1] = _body[i][1];
                                body[i][1] = _body[i][1] + 50;

                                if (fruitCheck(_body)){
                                    fruitCheckValue = 1;
                                    bodyCount += 1;
                                    generateFruit();
                                }
                            } else {
                                if (i + 1 <= bodyCount - 1){
                                    body[i + 1][0] = _body[i][0];
                                    body[i + 1][1] = _body[i][1];
                                }
                            }
                        }
                    }
                    InvalidateRect(hwnd, NULL, TRUE);
            }
            break;
        case WM_PAINT:
            hdc = BeginPaint(hwnd, &ps);

            for(int i = 0; i < bodyCount; i++){
                SetRect(&retangle, body[i][0], body[i][1], 50 + body[i][0], 50 + body[i][1]);
                FillRect(hdc, &retangle, CreateSolidBrush(RGB(0, 0, 0)));
            }

            SetRect(&retangle, fruit[0], fruit[1], 50 + fruit[0], 50 + fruit[1]);
            FillRect(hdc, &retangle, CreateSolidBrush(RGB(0, 255, 0)));

            EndPaint(hwnd, &ps);

            break;
        case WM_CLOSE:
            DestroyWindow(hwnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
    WNDCLASSEX wc;
    HWND hwnd;
    HWND hwndButton;
    MSG Msg;

    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style          = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = g_szClassName;
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wc)){
        printf("window registration failed");
        return 0;
    }

    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        g_szClassName,
        "Snake",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_VISIBLE,
        CW_USEDEFAULT, CW_USEDEFAULT, width, heigth,
        NULL, NULL, hInstance, NULL
    );

    if (hwnd == NULL){
        printf("window creation failed");
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    while(GetMessage(&Msg, NULL, 0, 0) > 0){
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }

    return Msg.wParam;
}