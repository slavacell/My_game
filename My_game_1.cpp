#include <iostream>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include <vector>
#include <string>
#include <stdlib.h>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <stdio.h>
#include <direct.h>
#include <random>

using namespace std;

HANDLE std_handle = GetStdHandle(STD_OUTPUT_HANDLE);
HANDLE screen_buffer_handle = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, CONSOLE_TEXTMODE_BUFFER, 0);
CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info{};
COORD screen_buffer_pos{};
int screen_buffer_size = (int)screen_buffer_info.dwSize.X * (int)screen_buffer_info.dwSize.Y;
CHAR_INFO *screen_buffer = new CHAR_INFO[screen_buffer_size];

int super = 1;      //   1
int character = 2;   //     2
int character_c = 14;   //   14
int level = 2;   //   2
int map_= 1;    //   1
int fps_ = 4;      //   3
vector<int> record{0, 0, 0, 0, 0, 0, 0};

vector<int> level_x{0, 45, 20, 15, 10, 10, 8, 8};
vector<int> level_y{0, 23, 10, 7, 5, 5, 4, 4};

vector<vector<int>> pos{{0, -1}, {0, 1}, {1, 0}, {-1, 0}};

vector<int> Enemy_ch{1, 1, 1, 1, 2, 2, 2, 2,   1, 1, 1, 1, 1, 1,   1, 1, 1};
vector<int> Enemy_cl{2, 2, 10, 10, 2, 2, 10, 10,   12, 12, 12, 4, 4, 4,   8, 8, 8};
vector<int> Enemy_go{5000, 4500, 4000, 3500, 3000, 2500, 2500, 1500,   2000, 1000, 300, 1500, 500, 200,   1000, 300, 100};
vector<int> Enemy_attack{8000, 1000000, 6000, 800000, 4000, 700000, 3000, 600000,   1700, 2300, 100000, 1300, 2700, 100000,   150, 500, 1000};
vector<int> Enemy_hp{1, 1, 2, 2, 3, 3, 5, 3,   7, 5, 1, 7, 7, 1,   12, 10, 7};
vector<int> Enemy_v_hp{9, 14, 29, 19, 49, 49, 99, 99,   199, 199, 99, 299, 299, 99,   999, 999, 999};
//vector<int> Enemy_start_at{0, 0, 3000, 0, 2500, 0, 1500, 0};
vector<string> my_map{"ssssssssssssssssssssssssssssssssssssssssssssss",
                      "s                                            s",
                      "s                                            s",
                      "s                                            s",
                      "s                                            s",
                      "s                                            s",
                      "s                                            s",
                      "s                                            s",
                      "s                                            s",
                      "s                                            s",
                      "s                                            s",
                      "s                                            s",
                      "s                                            s",
                      "s                                            s",
                      "s                                            s",
                      "s                                            s",
                      "s                                            s",
                      "s                                            s",
                      "s                                            s",
                      "s                                            s",
                      "s                                            s",
                      "ssssssssssssssssssssssssssssssssssssssssssssss"};


vector<string> map_1{"ssssssssssssssssssssssssssssssssssssssssssssss",
                     "s       s            s              s   s    s",
                     "s           sss      s     ss       s     s  s",
                     "s   ssss                    s    s           s",
                     "s   s              sss           s sss    ss s",
                     "s   s   ss    s      s      s    s           s",
                     "s             s                        s     s",
                     "s s         sss                    ss     ss s",
                     "s                     s s                  s s",
                     "s   s                         ssss         s s",
                     "s   s      s    s       s        s    ss     s",
                     "s        sss                 s   s           s",
                     "s          s      s          s          sss  s",
                     "s  ss   ssss      s          sssss   s       s",
                     "s                 s     s                    s",
                     "ss       ss             ss          sssss    s",
                     "s              sss       sss        s        s",
                     "s     ss         s              s   s        s",
                     "s    ss    ss    s     s ss     s   s    s   s",
                     "s  s          ss              s              s",
                     "s       ss    ss        s     s              s",
                     "ssssssssssssssssssssssssssssssssssssssssssssss"};


vector<string> map_2{"ssssssssssssssssssssssssssssssssssssssssssssss",
                     "s                                            s",
                     "s                                            s",
                     "s                                            s",
                     "s                                            s",
                     "s                                            s",
                     "s                                            s",
                     "s                                            s",
                     "s                                            s",
                     "s                                            s",
                     "s                                            s",
                     "s                                            s",
                     "s                                            s",
                     "s                                            s",
                     "s                                            s",
                     "s                                            s",
                     "s                                            s",
                     "s                                            s",
                     "s                                            s",
                     "s                                            s",
                     "s                                            s",
                     "ssssssssssssssssssssssssssssssssssssssssssssss"};
//  x 3   y 1   x+=7    y+=7

vector<vector<vector<string>>> map_part{/*{{"ssssssssssssss",
                                          "ss           s",
                                          "s            s",
                                          "s            s",
                                          "s            s",
                                          "s            s",
                                          "s            s",
                                          "s            s",
                                          "s            s",
                                          "ssssssssssssss"}},*/
                                        {{"4  s4  ss     ",
                                          "         2    ",
                                          "   1          ",
                                          "4             ",
                                          "              ",
                                          "          5 5 ",
                                          "s        s3   ",
                                          "s        s    ",
                                          "ss 4     s    ",
                                          "s     ss      "},
                                         {" 2     3      ",
                                          "          3   ",
                                          "              ",
                                          "5     4       ",
                                          "              ",
                                          "   ss5 2      ",
                                          "2    s        ",
                                          "     s        ",
                                          "            4 ",
                                          "              "},
                                         {"  5   55   5  ",
                                          "3  53  3  53  ",
                                          "              ",
                                          "   5      5   ",
                                          " 1           s",
                                          "         4    ",
                                          "        s   4 ",
                                          "        s     ",
                                          "        s    s",
                                          "          ssss"},
                                         {"1      s55  4 ",
                                          "       s      ",
                                          "              ",
                                          "       1      ",
                                          "              ",
                                          "              ",
                                          "              ",
                                          "3   s        s",
                                          "             s",
                                          "    5       ss"}},
                                        /*{{"ssssss",
                                          "s    s",
                                          "s    s",
                                          "s    s",
                                          "s    s",
                                          "ssssss"}},
                                        {{"sssss",
                                          "s   s",
                                          "s   s",
                                          "sssss"}},
                                        {{"sss",
                                          "s s",
                                          "sss"}},
                                        {{"ss",
                                          "ss"}}*/
                                        {{"      ",
                                          " oooo ",
                                          " o  s ",
                                          "   3  ",
                                          "4     ",
                                          "      "},
                                         {"4   4 ",
                                          "      ",
                                          " 5s 4 ",
                                          "      ",
                                          " 5s 4 ",
                                          "      "},
                                         {"5 4  5",
                                          "      ",
                                          " 4 4  ",
                                          "      ",
                                          "  4   ",
                                          "5    5"},
                                         {"4   4 ",
                                          "      ",
                                          "  4   ",
                                          "      ",
                                          "4   4 ",
                                          "      "},
                                         {" ss 4 ",
                                          "      ",
                                          "3     ",
                                          "    55",
                                          "    5s",
                                          " ss  s"},
                                         {"sss  s",
                                          "  5   ",
                                          "2     ",
                                          "      ",
                                          "     5",
                                          "     5"},
                                         {"2     ",
                                          "      ",
                                          "      ",
                                          "      ",
                                          "      ",
                                          "55ooss"},
                                         {"55    ",
                                          "52    ",
                                          "      ",
                                          "      ",
                                          "5     ",
                                          "55    "},
                                         {"3   4 ",
                                          "      ",
                                          "      ",
                                          "555 5 ",
                                          "5   5 ",
                                          "5 5 5 "},
                                         {"  s 4 ",
                                          "5     ",
                                          "55    ",
                                          "55 3  ",
                                          "55    ",
                                          "5     "}},
                                        {{" 3   ",
                                          "     ",
                                          "s    ",
                                          "s ss "},
                                         {"s    ",
                                          "s 3  ",
                                          "4    ",
                                          "     "},
                                         {"4  ss",
                                          "     ",
                                          "   4 ",
                                          "ss   "},
                                         {"oo 4 ",
                                          "     ",
                                          "4    ",
                                          "   ss"},
                                         {"  s  ",
                                          "4 s4 ",
                                          "     ",
                                          "oo   "},
                                         {" 5  s",
                                          "555  ",
                                          "   4 ",
                                          "ss   "},
                                         {" o   ",
                                          " o   ",
                                          " s 4 ",
                                          " o   "},
                                         {"s 4  ",
                                          "     ",
                                          "oosoo",
                                          "     "},
                                         {"s    ",
                                          "5    ",
                                          " 4  5",
                                          "   s "},
                                         {"3   s",
                                          "     ",
                                          "   4 ",
                                          "     "}},
                                        {{" o ",
                                          " o ",
                                          " o "},
                                         {"   ",
                                          "555",
                                          "   "},
                                         {"sss",
                                          "   ",
                                          "sss"},
                                         {"sss",
                                          "   ",
                                          "s s"},
                                         {"s s",
                                          "  s",
                                          "s s"},
                                         {"s s",
                                          "   ",
                                          "sss"},
                                         {" ss",
                                          "ss ",
                                          "s  "},
                                         {"5 s",
                                          "  s",
                                          "sss"},
                                         {"   ",
                                          " 4 ",
                                          "   "},
                                         {" 4 ",
                                          "   ",
                                          "ss "},
                                         {"4  ",
                                          "   ",
                                          " ss"},
                                         {" 55",
                                          "4 s",
                                          "   "},
                                         {" ss",
                                          "   ",
                                          "oo5"},
                                         {"   ",
                                          "s  ",
                                          "  s"},
                                         {"555",
                                          "5s5",
                                          "555"},
                                         {"   ",
                                          " s5",
                                          " o "}},
                                        {{"  ",
                                          "  "},
                                         {"ss",
                                          "ss"},
                                         {"55",
                                          "55"},
                                         {"s ",
                                          "  "},
                                         {" s",
                                          "  "},
                                         {"  ",
                                          " s"},
                                         {"  ",
                                          "s "},
                                         {"oo",
                                          "oo"},
                                         {"oo",
                                          "ss"},
                                         {" s",
                                          " s"},
                                         {"s ",
                                          "s "},
                                         {"ss",
                                          "oo"}},
                                        {{"s"},
                                         {" "},
                                         {"s"},
                                         {" "},
                                         {"s"},
                                         {" "},
                                         {"o"},
                                         {" "}}};



void print_int(int X, int Y, int _int, int c, int color, vector<vector<int>> &screen_symbol, vector<vector<int>> &screen_color){
    for (int i = c; i > 0; i--){
        int qw = i;
        screen_symbol[X + c - i][Y] = _int % int(pow(10, qw)) / pow(10, qw - 1) + 48;
        screen_color[X + c - i][Y] = color;
    }
}

void print_texture(int X, int Y, vector<vector<int>> massiv, vector<vector<int>> color_massiv, vector<vector<int>> &screen_symbol, vector<vector<int>> &screen_color){
    for (int i = 0; i < massiv.size(); i++){
        for (int j = 0; j < massiv[0].size(); j++){
            if (massiv[i][j] != 0){
                screen_color[j + X][i + Y] = color_massiv[i][j];
                screen_symbol[j + X][i + Y] = massiv[i][j];
            }
        }
    }
}

void print_massiv(int X, int Y, vector<string> massiv, vector<vector<int>> color_massiv, vector<vector<int>> &screen_symbol, vector<vector<int>> &screen_color){
    for (int i = 0; i < massiv.size(); i++){
        for (int j = 0; j < massiv[0].size(); j++){
            screen_symbol[j + X][i + Y] = massiv[i][j];
            screen_color[j + X][i + Y] = color_massiv[i][j];
        }
    }
}

int menu(){
    system("mode con cols=46 lines=25");
    system("title My_game_1");
    screen_buffer_handle = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, CONSOLE_TEXTMODE_BUFFER, 0);
    if (std_handle == INVALID_HANDLE_VALUE || screen_buffer_handle == INVALID_HANDLE_VALUE){
        printf("CreateConsoleScreenBuffer failed - (%d)\n", GetLastError());
    }
    if (! SetConsoleActiveScreenBuffer(screen_buffer_handle) ){
        printf("SetConsoleActiveScreenBuffer failed - (%d)\n", GetLastError());
    }

    if (! GetConsoleScreenBufferInfo(screen_buffer_handle, &screen_buffer_info) ){
        printf("GetConsoleScreenBufferInfo failed - (%d)\n", GetLastError());
    }
    screen_buffer_size = (int)screen_buffer_info.dwSize.X * (int)screen_buffer_info.dwSize.Y;
    screen_buffer = new CHAR_INFO[screen_buffer_size];
    memset(screen_buffer, 0, screen_buffer_size * sizeof(CHAR_INFO));
    HWND window_header = GetConsoleWindow();
    POINT mouse, mouse1, cursor;
    vector<vector<int>> screen_symbol(46, vector<int>(25, 0)), screen_color(46, vector<int>(25, 15)),
    screen_s(46, vector<int>(25, 0)), screen_c(46, vector<int>(25, 15));
    bool button_down = false, button_up = false, button_ok = true; int number = 0;
    SYSTEMTIME time;
    vector<int> number_pos{1, 6, 12, 16};
    while (true){
        GetLocalTime(&time);
        ///       down
        if (GetKeyState(83) & 0x8000 || GetKeyState(115) & 0x8000 || GetKeyState(155) & 0x8000 || GetKeyState(235) & 0x8000){
            if (!button_down){number += 1; number %= 4;}
            button_down = true;
        } else {button_down = false;}

        ///       up
        if (GetKeyState(87) & 0x8000 || GetKeyState(119) & 0x8000 || GetKeyState(150) & 0x8000 || GetKeyState(230) & 0x8000){
            if (!button_up){number += 3; number %= 4;}
            button_up = true;
        } else {button_up = false;}

        ///       ok
        if (GetKeyState(32) & 0x8000){
            if (!button_ok){
                if (number == 0){break;}
            }
            button_ok = true;
        } else {button_ok = false;}

        ///       esc
        if (GetKeyState(VK_ESCAPE) & 0x8000) {break;}

        screen_symbol[1][number_pos[number]] = 16;

        print_massiv(4, 1, {"back"}, {{15, 15, 15, 15, 15}}, screen_symbol, screen_color);

        for (int i = 0; i < 46; i++){
            for (int j = 0; j < 25; j++){
                screen_buffer[i + 46 * j].Char.AsciiChar = char(screen_symbol[i][j]);
                screen_buffer[i + 46 * j].Attributes = screen_color[i][j];
            }
        }
        screen_symbol = screen_s; screen_color = screen_c;
        WriteConsoleOutput(screen_buffer_handle, screen_buffer, screen_buffer_info.dwSize, screen_buffer_pos, &screen_buffer_info.srWindow);
    }
}

int new_game(){
    system("mode con cols=46 lines=25");
    system("title My_game_1");
    screen_buffer_handle = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, CONSOLE_TEXTMODE_BUFFER, 0);
    if (std_handle == INVALID_HANDLE_VALUE || screen_buffer_handle == INVALID_HANDLE_VALUE){
        printf("CreateConsoleScreenBuffer failed - (%d)\n", GetLastError());
    }
    if (! SetConsoleActiveScreenBuffer(screen_buffer_handle) ){
        printf("SetConsoleActiveScreenBuffer failed - (%d)\n", GetLastError());
    }

    if (! GetConsoleScreenBufferInfo(screen_buffer_handle, &screen_buffer_info) ){
        printf("GetConsoleScreenBufferInfo failed - (%d)\n", GetLastError());
    }
    screen_buffer_size = (int)screen_buffer_info.dwSize.X * (int)screen_buffer_info.dwSize.Y;
    screen_buffer = new CHAR_INFO[screen_buffer_size];
    memset(screen_buffer, 0, screen_buffer_size * sizeof(CHAR_INFO));
    HWND window_header = GetConsoleWindow();
    //POINT mouse, mouse1, cursor;
    vector<string> map_3;

    SYSTEMTIME time, time1;
    GetLocalTime(&time1);

    if (map_ == 1){
        map_3 = map_1;
    }
    else if (map_ == 3){
        map_3 = my_map;
    }
    else {
        map_3 = map_2;
        vector<vector<vector<int>>> part{{{2, 1}, {16, 1}, {30, 1}, {2, 11}, {16, 11}, {30, 11}}, {}, {}, {}, {},
        {{1, 10}, {1, 11}, {44, 10}, {44, 11}, {1, 5}, {1, 6}, {1, 15}, {1, 16}, {44, 5}, {44, 6}, {44, 15}, {44, 16}}};
        for (int i = 0; i < part.size(); i++){
            for (int j = 0; j < part[i].size(); j++){
                vector<string> a = map_part[i][(rand() + time1.wSecond) % map_part[i].size()];
                for (int k = 0; k < a.size(); k++){
                    for (int l = 0; l < a[k].size(); l++){
                        if (int(a[k][l]) - 48 >= 1 && int(a[k][l]) - 48 <= 4){
                            part[int(a[k][l]) - 48].push_back({part[i][j][0] + l, part[i][j][1] + k});
                        }
                        else if (part[i][j][1] + k < 22 && part[i][j][0] + l < 45){
                            map_3[part[i][j][1] + k][part[i][j][0] + l] = a[k][l];
                        }
                    }
                }
            }
        }
        /*for (int i = 1; i < 21; i += 7){
            for (int j = 3; j < 44; j += 7){
                vector<string> a = map_part[(rand() + time1.wSecond) % map_part.size()];
                for (int k = 0; k < 6; k++){
                    for (int l = 0; l < 5; l++){
                        map_3[i + k][j + l] = a[k][l];
                    }
                }
            }
        }*/
    }

    vector<vector<int>> screen_symbol(46, vector<int>(25, 0)), screen_color(46, vector<int>(25, 15)),
    screen_s(46, vector<int>(25, 0)), screen_c(46, vector<int>(25, 15));
    int step = 0, step_max = 350; int bullet = 7500;
    //bool button_down = false, button_up = false, button_ok = true;
    int t;
    int player_x = 1, player_y = 1, player_z = 0, player_hp = 5, player_id = -1;
    int score = 0; int super_score = 0;

    vector<int> bullet_x{};
    vector<int> bullet_y{};
    vector<int> bullet_z{};
    vector<int> bullet_t{};

    vector<int> hp_x{};
    vector<int> hp_y{};
    int hp_spawn = 0;

    int fps = 0, fps_t = time1.wSecond, fps_s = 0;
    int t_fps = 0; SYSTEMTIME fps_t1, fps_t2;
    GetLocalTime(&fps_t2);

    vector<int> enemy_x{};
    vector<int> enemy_y{};
    vector<int> enemy_t{};
    vector<int> enemy_id{};
    vector<int> enemy_at{};
    vector<int> enemy_hp{};
    int enemy_spawn = 1500;

    vector<int> body_x{};
    vector<int> body_y{};
    vector<int> body_t{};   //   1000
    vector<int> body_c{};

    while (true){
        GetLocalTime(&time);
        t = time.wMilliseconds - time1.wMilliseconds + 1000 * (time.wSecond - time1.wSecond) + 60000 * (time.wMinute - time1.wMinute);
        if (fps_ == 3 && t == 0){Sleep(1); t = 1;}
        step += t;
        if (bullet < 7500) {bullet += t;}
        GetLocalTime(&time1);
        ///       down
        if (GetKeyState(83) & 0x8000 || GetKeyState(115) & 0x8000 || GetKeyState(155) & 0x8000 || GetKeyState(235) & 0x8000){
            player_z = 1;
            if (map_3[player_y + 1][player_x] != 's' && map_3[player_y + 1][player_x] != 'o' && step >= step_max){
                step = 0; player_y += 1;
            }
        }

        ///       up
        if (GetKeyState(87) & 0x8000 || GetKeyState(119) & 0x8000 || GetKeyState(150) & 0x8000 || GetKeyState(230) & 0x8000){
            player_z = 0;
            if (map_3[player_y - 1][player_x] != 's' && map_3[player_y - 1][player_x] != 'o' && step >= step_max){
                step = 0; player_y -= 1;
            }
        }

        ///       right
        if (GetKeyState(68) & 0x8000 || GetKeyState(100) & 0x8000 || GetKeyState(130) & 0x8000 || GetKeyState(162) & 0x8000){
            player_z = 2;
            if (map_3[player_y][player_x + 1] != 's' && map_3[player_y][player_x + 1] != 'o' && step >= step_max){
                step = 0; player_x += 1;
            }
        }

        ///        left
        if (GetKeyState(65) & 0x8000 || GetKeyState(97) & 0x8000 || GetKeyState(148) & 0x8000 || GetKeyState(228) & 0x8000){
            player_z = 3;
            if (map_3[player_y][player_x - 1] != 's' && map_3[player_y][player_x - 1] != 'o'&& step >= step_max){
                step = 0; player_x -= 1;
            }
        }

        ///       ok
        if (GetKeyState(32) & 0x8000){
            if (bullet >= 1500 && step >= step_max && map_3[player_y + pos[player_z][1]][player_x + pos[player_z][0]] != 's'){
                bullet -= 1500; bullet_x.push_back(player_x + pos[player_z][0]);
                bullet_y.push_back(player_y + pos[player_z][1]);
                bullet_z.push_back(player_z); bullet_t.push_back(0);
                step = 100;
            }
        }

        ///       super   k
        if ((super <= 2 && super_score >= 7 || super == 3 && super_score >= 7 * 3) && GetKeyState(75) & 0x8000 ||
            GetKeyState(107) & 0x8000 || GetKeyState(139) & 0x8000 || GetKeyState(171) & 0x8000){
            if (super == 1){
                for (int i = 0; i < 4; i++){
                    bullet_x.push_back(player_x + pos[i][0]);
                    bullet_y.push_back(player_y + pos[i][1]);
                    bullet_z.push_back(i); bullet_t.push_back(0);
                }
            }
            if (super == 2){
                if (pos[player_z][0] == 0){
                    bullet_x.push_back(player_x);
                    bullet_y.push_back(player_y + pos[player_z][1]);
                    bullet_z.push_back(player_z); bullet_t.push_back(0);
                    bullet_x.push_back(player_x - 1);
                    bullet_y.push_back(player_y + pos[player_z][1]);
                    bullet_z.push_back(player_z); bullet_t.push_back(0);
                    bullet_x.push_back(player_x + 1);
                    bullet_y.push_back(player_y + pos[player_z][1]);
                    bullet_z.push_back(player_z); bullet_t.push_back(0);
                }
                else {
                    bullet_x.push_back(player_x + pos[player_z][0]);
                    bullet_y.push_back(player_y);
                    bullet_z.push_back(player_z); bullet_t.push_back(0);
                    bullet_x.push_back(player_x + pos[player_z][0]);
                    bullet_y.push_back(player_y - 1);
                    bullet_z.push_back(player_z); bullet_t.push_back(0);
                    bullet_x.push_back(player_x + pos[player_z][0]);
                    bullet_y.push_back(player_y + 1);
                    bullet_z.push_back(player_z); bullet_t.push_back(0);
                }
            }
            if (super == 3){
                bullet_x.push_back(player_x + pos[player_z][0]);
                bullet_y.push_back(player_y + pos[player_z][1]);
                bullet_z.push_back(player_z); bullet_t.push_back(0);
                hp_x.push_back(player_x + pos[player_z][0]);
                hp_y.push_back(player_y + pos[player_z][1]);
            }
            super_score = 0;
        }

        ///       esc
        if (GetKeyState(VK_ESCAPE) & 0x8000) {break;}

        ///       pause
        if (GetKeyState(VK_F1) & 0x8000){
            while (true){
                GetLocalTime(&time1);
                if (GetKeyState(VK_F2) & 0x8000){break;}
            }
        }

        if (fps_t != time1.wSecond){
            fps_t = time1.wSecond;
            if (fps_s >= 9999){fps = 9999;}
            else {fps = fps_s;}
            fps_s = 0;
        }
        else {fps_s += 1;}

        if ((enemy_spawn >= 2000) || (level >= 5 && enemy_spawn >= 1000)){
            int x = (rand() + time1.wMilliseconds) % 45;
            int y = (rand() + time1.wMilliseconds) % 21;
            if (map_3[y][x] != 's' && map_3[y][x] != 'o' && !(x < player_x + 3 && x > player_x - 3 && y < player_y + 3 && y > player_y - 3)){
                bool spawn = true;
                for (int i = 0; i < enemy_x.size(); i++){
                    if (enemy_x[i] == x && enemy_y[i] == y){spawn = false; break;}
                }
                if (spawn){
                    enemy_spawn -= 2000 + 1000 * (level >= 5); int id;
                    if (level == 1){
                        id = (rand() + time1.wMilliseconds) % 2 + (level - 1) * 2;
                    }
                    else if (level == 5 || level == 6 || level == 7){
                        id = (rand() + time1.wMilliseconds) % 3 + level * 3 - 7;
                    }
                    else {
                        id = (rand() + time1.wMilliseconds) % 4 + (level - 2) * 2;
                    }
                    //int id = (rand() + time1.wMilliseconds) % (4 - 2 * (level == 1)) + (level > 1) * (level - 2) * 2;
                    enemy_x.push_back(x);
                    enemy_y.push_back(y);
                    enemy_at.push_back(0);
                    enemy_t.push_back(0);
                    enemy_id.push_back(id);
                    enemy_hp.push_back(Enemy_hp[id]);
                }
            }
        }
        else{enemy_spawn += t;}

        if (hp_spawn >= 30000){
            int x = (rand() + time1.wMilliseconds) % 45;
            int y = (rand() + time1.wMilliseconds) % 21;
            if (map_3[y][x] != 's' && map_3[y][x] != 'o'){
                hp_x.push_back(x);
                hp_y.push_back(y);
                hp_spawn -= 30000;
            }
            else {hp_spawn -= 5000;}
        }
        else {hp_spawn += t;}

        for (int j = 0; j < hp_x.size(); j++){
            if(hp_x[j] == player_x && hp_y[j] == player_y){
                hp_x[j] = hp_x[hp_x.size() - 1]; hp_x.pop_back();
                hp_y[j] = hp_y[hp_y.size() - 1]; hp_y.pop_back();
                player_hp += 1 * (player_hp < 99);
            }
        }


        for (int i = 0; i < bullet_x.size(); i++){
            bool bullet_delete = false;
            if (bullet_x[i] == player_x && bullet_y[i] == player_y){
                player_hp -= 1;
                bullet_delete = true;
            }
            else if (map_3[bullet_y[i]][bullet_x[i]] != 's'){
                for (int j = 0; j < enemy_x.size(); j++){
                    if (bullet_x[i] == enemy_x[j] && bullet_y[i] == enemy_y[j]){
                        bullet_delete = true;
                        if (enemy_hp[j] > 1){
                            enemy_hp[j] -= 1; player_id = j;
                        }
                        else {
                            if ((rand() + time1.wMilliseconds) % 1000 <= Enemy_v_hp[enemy_id[j]] + 50 * (map_ == 2)){
                                hp_x.push_back(enemy_x[j]);
                                hp_y.push_back(enemy_y[j]);
                            }
                            body_x.push_back(enemy_x[j]);
                            body_y.push_back(enemy_y[j]);
                            body_t.push_back(1000);
                            body_c.push_back(Enemy_cl[enemy_id[j]]);
                            score += Enemy_hp[enemy_id[j]]; player_id = -1;
                            enemy_x[j] = enemy_x[enemy_x.size() - 1]; enemy_x.pop_back();
                            enemy_y[j] = enemy_y[enemy_y.size() - 1]; enemy_y.pop_back();
                            enemy_t[j] = enemy_t[enemy_t.size() - 1]; enemy_t.pop_back();
                            enemy_id[j] = enemy_id[enemy_id.size() - 1]; enemy_id.pop_back();
                            enemy_at[j] = enemy_at[enemy_at.size() - 1]; enemy_at.pop_back();
                            enemy_hp[j] = enemy_hp[enemy_hp.size() - 1]; enemy_hp.pop_back();
                        }
                        super_score += 1;
                        break;
                    }
                }
            }
            else {bullet_delete = true;}

            bullet_t[i] += t;
            if (((bullet_z[i] <= 1 && bullet_t[i] >= 130) || (bullet_z[i] >= 2 && bullet_t[i] >= 100)) && !bullet_delete){
                bullet_t[i] = 0;
                if (bullet_x[i] + pos[bullet_z[i]][0] == player_x && bullet_y[i] + pos[bullet_z[i]][1] == player_y){
                    player_hp -= 1;
                    bullet_delete = true;
                }
                else if (map_3[bullet_y[i] + pos[bullet_z[i]][1]][bullet_x[i] + pos[bullet_z[i]][0]] != 's'){
                    for (int j = 0; j < enemy_x.size(); j++){
                        if (bullet_x[i] + pos[bullet_z[i]][0] == enemy_x[j] && bullet_y[i] + pos[bullet_z[i]][1] == enemy_y[j]){
                            bullet_delete = true;
                            if (enemy_hp[j] > 1){
                                enemy_hp[j] -= 1; player_id = j;
                            }
                            else {
                                if ((rand() + time1.wMilliseconds) % 1000 <= Enemy_v_hp[enemy_id[j]] + 50 * (map_ == 2)){
                                    hp_x.push_back(enemy_x[j]);
                                    hp_y.push_back(enemy_y[j]);
                                }
                                //enemy_t[j] = 0; enemy_hp[j] = Enemy_hp[enemy_id[j]];
                                body_x.push_back(enemy_x[j]);
                                body_y.push_back(enemy_y[j]);
                                body_t.push_back(1000);
                                body_c.push_back(Enemy_cl[enemy_id[j]]);
                                score += Enemy_hp[enemy_id[j]]; player_id = -1;
                                enemy_x[j] = enemy_x[enemy_x.size() - 1]; enemy_x.pop_back();
                                enemy_y[j] = enemy_y[enemy_y.size() - 1]; enemy_y.pop_back();
                                enemy_t[j] = enemy_t[enemy_t.size() - 1]; enemy_t.pop_back();
                                enemy_id[j] = enemy_id[enemy_id.size() - 1]; enemy_id.pop_back();
                                enemy_at[j] = enemy_at[enemy_at.size() - 1]; enemy_at.pop_back();
                                enemy_hp[j] = enemy_hp[enemy_hp.size() - 1]; enemy_hp.pop_back();
                            }
                            super_score += 1;
                            break;
                        }
                    }
                    if (!bullet_delete){
                        bullet_y[i] += pos[bullet_z[i]][1];
                        bullet_x[i] += pos[bullet_z[i]][0];
                    }
                }
                else {bullet_delete = true;}
            }
            if (bullet_delete){
                bullet_x[i] = bullet_x[bullet_x.size() - 1]; bullet_x.pop_back();
                bullet_y[i] = bullet_y[bullet_y.size() - 1]; bullet_y.pop_back();
                bullet_z[i] = bullet_z[bullet_z.size() - 1]; bullet_z.pop_back();
                bullet_t[i] = bullet_t[bullet_t.size() - 1]; bullet_t.pop_back();
            }
        }


        for (int i = 0; i < enemy_x.size(); i++){
            int direction = 0;
            if (player_x == enemy_x[i]){
                if (abs(player_y - enemy_y[i]) <= 1 && enemy_at[i] >= 500){
                    player_hp -= 1; enemy_at[i] = 0;
                }
                else if (enemy_at[i] >= Enemy_attack[enemy_id[i]]){
                    direction += (player_y > enemy_y[i]);
                    bullet_x.push_back(enemy_x[i] + pos[direction][0]);
                    bullet_y.push_back(enemy_y[i] + pos[direction][1]);
                    bullet_z.push_back(direction); bullet_t.push_back(0);
                    enemy_at[i] = 0;
                }
            }
            else if (player_y == enemy_y[i]){
                if (abs(player_x - enemy_x[i]) <= 1 && enemy_at[i] >= 500){
                    player_hp -= 1; enemy_at[i] = 0;
                }
                else if (enemy_at[i] >= Enemy_attack[enemy_id[i]]){
                    direction += 2 + (player_x < enemy_x[i]);
                    bullet_x.push_back(enemy_x[i] + pos[direction][0]);
                    bullet_y.push_back(enemy_y[i] + pos[direction][1]);
                    bullet_z.push_back(direction); bullet_t.push_back(0);
                    enemy_at[i] = 0;
                }
            }
            if (enemy_t[i] >= Enemy_go[enemy_id[i]]){
                direction = rand() % 4;
                if (map_3[enemy_y[i] + pos[direction][1]][enemy_x[i] + pos[direction][0]] != 's' &&
                    map_3[enemy_y[i] + pos[direction][1]][enemy_x[i] + pos[direction][0]] != 'o'){
                    bool go_ = true;
                    for (int j = 0; j < bullet_x.size(); j++){
                        if (enemy_x[i] + pos[direction][0] == bullet_x[j] && enemy_y[i] + pos[direction][1] == bullet_y[j]){
                            go_ = false; break;
                        }
                    }
                    for (int j = 0; j < enemy_x.size(); j++){
                        if (enemy_x[i] + pos[direction][0] == enemy_x[j] && enemy_y[i] + pos[direction][1] == enemy_y[j] && i != j){
                            go_ = false; break;
                        }
                    }
                    if (go_){
                        enemy_x[i] += pos[direction][0];
                        enemy_y[i] += pos[direction][1];
                        enemy_t[i] = 0;
                    }

                }
            }
            for (int j = 0; j < hp_x.size(); j++){
                if(hp_x[j] == enemy_x[i] && hp_y[j] == enemy_y[i]){
                    hp_x[j] = hp_x[hp_x.size() - 1]; hp_x.pop_back();
                    hp_y[j] = hp_y[hp_y.size() - 1]; hp_y.pop_back();
                    enemy_hp[i] += 1 * (enemy_hp[i] < 9);
                }
            }
            enemy_at[i] += t;
            enemy_t[i] += t;
        }


        print_massiv(1, 0, {"x:"}, {{15, 15}}, screen_symbol, screen_color);
        print_int(3, 0, player_x, 2, 15, screen_symbol, screen_color);
        print_massiv(6, 0, {"y:"}, {{15, 15}}, screen_symbol, screen_color);
        print_int(8, 0, player_y, 2, 15, screen_symbol, screen_color);
        print_massiv(11, 0, {"z:"}, {{15, 15}}, screen_symbol, screen_color);
        print_texture(13, 0, {{24 + player_z}}, {{10}}, screen_symbol, screen_color);
        print_massiv(11, 0, {"t:"}, {{15, 15}}, screen_symbol, screen_color);
        if (step >= step_max){print_texture(13, 0, {{43}}, {{10}}, screen_symbol, screen_color);}
        else {print_texture(13, 0, {{45}}, {{12}}, screen_symbol, screen_color);}
        print_massiv(15, 0, {"bullet:"}, {{15, 15, 15, 15, 15, 15, 15}}, screen_symbol, screen_color);
        print_int(22, 0, bullet / 1500, 1, 15, screen_symbol, screen_color);
        print_massiv(24, 0, {"hp:"}, {{15, 15, 15, 15, 15, 15, 15}}, screen_symbol, screen_color);
        print_int(27, 0, player_hp, 2, 15, screen_symbol, screen_color);
        print_texture(29, 0, {{3}}, {{12}}, screen_symbol, screen_color);
        print_massiv(31, 0, {"super:"}, {{15, 15, 15, 15, 15, 15, 15}}, screen_symbol, screen_color);
        if (super <= 2 && super_score >= 7 || super == 3 && super_score >= 7 * 3){
            print_texture(37, 0, {{43}}, {{10}}, screen_symbol, screen_color);
        }
        else {print_texture(37, 0, {{45}}, {{12}}, screen_symbol, screen_color);}
        print_massiv(39, 0, {"f:"}, {{15, 15}}, screen_symbol, screen_color);
        print_int(41, 0, fps, 4, 15, screen_symbol, screen_color);

        print_massiv(1, 2, {"z:"}, {{15, 15}}, screen_symbol, screen_color);
        print_texture(3, 2, {{24 + player_z}}, {{10}}, screen_symbol, screen_color);
        print_massiv(5, 2, {"score:"}, {{15, 15, 15, 15, 15, 15}}, screen_symbol, screen_color);
        print_int(11, 2, score, 4, 15, screen_symbol, screen_color);
        if (player_id == -1){print_massiv(16, 2, {"-:--"}, {{15, 15, 15, 15,}}, screen_symbol, screen_color);}
        else{
            print_texture(16, 2, {{Enemy_ch[enemy_id[player_id]]}}, {{Enemy_cl[enemy_id[player_id]]}}, screen_symbol, screen_color);
            print_massiv(17, 2, {":"}, {{15}}, screen_symbol, screen_color);
            print_int(18, 2, enemy_hp[player_id], 2, 15, screen_symbol, screen_color);
        }
        print_texture(20, 2, {{3}}, {{12}}, screen_symbol, screen_color);



        for (int i = 0; i < enemy_x.size(); i++){
            screen_symbol[enemy_x[i]][enemy_y[i] + 3] = Enemy_ch[enemy_id[i]];
            screen_color[enemy_x[i]][enemy_y[i] + 3] = Enemy_cl[enemy_id[i]];
        }
        for (int i = 0; i < hp_x.size(); i++){
            screen_symbol[hp_x[i]][hp_y[i] + 3] = 3;
            screen_color[hp_x[i]][hp_y[i] + 3] = 12;
        }
        for (int i = 0; i < bullet_x.size(); i++){
            screen_symbol[bullet_x[i]][bullet_y[i] + 3] = 43;
            screen_color[bullet_x[i]][bullet_y[i] + 3] = 15;
        }

        if (player_hp <= 0) {
            body_x.push_back(player_x);
            body_y.push_back(player_y);
            body_t.push_back(1000);
            body_c.push_back(character_c);

        }
        for (int i = 0; i < 22; i++){
            for (int j = 0; j < 46; j++){
                if (map_3[i][j] == 's'){
                    screen_symbol[j][i + 3] = 219;
                    screen_color[j][i + 3] = 15;
                }
                else if (map_3[i][j] == 'o'){
                    screen_symbol[j][i + 3] = 219;
                    screen_color[j][i + 3] = 3;
                }
            }
        }
        for (int i = 0; i < bullet_x.size(); i++){
            screen_symbol[bullet_x[i]][bullet_y[i] + 3] = 43;
            screen_color[bullet_x[i]][bullet_y[i] + 3] = 15 + 48 * (map_3[bullet_y[i]][bullet_x[i]] == 'o');
        }
        for (int i = 0; i < 22; i++){
            for (int j = 0; j < 46; j++){
                if (!((map_ == 3 && GetKeyState(VK_SHIFT) & 0x8000) || (j < player_x + level_x[level] && j > player_x - level_x[level] &&
                    i < player_y + level_y[level] && i > player_y - level_y[level]))){
                    screen_symbol[j][i + 3] = 177;
                    screen_color[j][i + 3] = 15;
                }
            }
        }


        for (int i = 0; i < body_x.size(); i++){
            if (body_t[i] > 0){
                screen_symbol[body_x[i]][body_y[i] + 3] = 253;
                screen_color[body_x[i]][body_y[i] + 3] = body_c[i];
                body_t[i] -= t;
            }
            else{
                body_x[i] = body_x[body_x.size() - 1]; body_x.pop_back();
                body_y[i] = body_y[body_y.size() - 1]; body_y.pop_back();
                body_t[i] = body_t[body_t.size() - 1]; body_t.pop_back();
                body_c[i] = body_c[body_c.size() - 1]; body_c.pop_back();
            }
        }

        if (player_hp > 0) {print_texture(player_x, player_y + 3, {{character}}, {{character_c}}, screen_symbol, screen_color);}

        for (int i = 0; i < 46; i++){
            for (int j = 0; j < 25; j++){
                screen_buffer[i + 46 * j].Char.AsciiChar = char(screen_symbol[i][j]);
                screen_buffer[i + 46 * j].Attributes = screen_color[i][j];
            }
        }
        screen_symbol = screen_s; screen_color = screen_c;
        WriteConsoleOutput(screen_buffer_handle, screen_buffer, screen_buffer_info.dwSize, screen_buffer_pos, &screen_buffer_info.srWindow);
        if (player_hp <= 0) {break;}

        GetLocalTime(&fps_t1);
        t_fps = fps_t1.wMilliseconds - fps_t2.wMilliseconds + 1000 * (fps_t1.wSecond - fps_t2.wSecond) + 60000 * (fps_t1.wMinute - fps_t2.wMinute);
        if (fps_ == 1){
            if (t_fps < 10){Sleep(10 - t_fps);}
        }
        else if (fps_ == 2){
            if (t_fps < 5){Sleep(5 - t_fps);}
        }
        else if (fps_ == 3){
            //Sleep(1);
        }
        GetLocalTime(&fps_t2);
    }
    if (score > record[level] && map_ != 3) {record[level] = score;}
    Sleep(750);
}

int workout(){
    system("mode con cols=46 lines=25");
    system("title My_game_1");
    screen_buffer_handle = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, CONSOLE_TEXTMODE_BUFFER, 0);
    if (std_handle == INVALID_HANDLE_VALUE || screen_buffer_handle == INVALID_HANDLE_VALUE){
        printf("CreateConsoleScreenBuffer failed - (%d)\n", GetLastError());
    }
    if (! SetConsoleActiveScreenBuffer(screen_buffer_handle) ){
        printf("SetConsoleActiveScreenBuffer failed - (%d)\n", GetLastError());
    }

    if (! GetConsoleScreenBufferInfo(screen_buffer_handle, &screen_buffer_info) ){
        printf("GetConsoleScreenBufferInfo failed - (%d)\n", GetLastError());
    }
    screen_buffer_size = (int)screen_buffer_info.dwSize.X * (int)screen_buffer_info.dwSize.Y;
    screen_buffer = new CHAR_INFO[screen_buffer_size];
    memset(screen_buffer, 0, screen_buffer_size * sizeof(CHAR_INFO));
    HWND window_header = GetConsoleWindow();
    //POINT mouse, mouse1, cursor;
    vector<vector<int>> screen_symbol(46, vector<int>(25, 0)), screen_color(46, vector<int>(25, 15)),
    screen_s(46, vector<int>(25, 0)), screen_c(46, vector<int>(25, 15));
    int step = 0, step_max = 350; int bullet = 7500;
    //bool button_down = false, button_up = false, button_ok = true;
    int t;
    int player_x = 1, player_y = 1, player_z = 0, player_hp = 5, player_id = -1;
    int score = 0; int super_score = 0;
    SYSTEMTIME time, time1;
    GetLocalTime(&time1);
    vector<int> bullet_x{};
    vector<int> bullet_y{};
    vector<int> bullet_z{};
    vector<int> bullet_t{};

    vector<int> hp_x{};
    vector<int> hp_y{};

    int fps = 0, fps_t = time1.wSecond, fps_s = 0;

    vector<vector<int>> enemy_xy{{5, 4}, {13, 6}, {5, 17}, {18, 6}, {23, 9}, {24, 16}, {30, 12}, {40, 18}, {44, 8}, {28, 4}};
    vector<int> enemy_t{10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000, 10000};
    vector<int> enemy_id{3, 2, 1, 4, 6, 5, 2, 7, 0, 4};
    vector<int> enemy_at{0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    vector<int> enemy_hp{2, 2, 1, 3, 5, 3, 2, 3, 1, 3};
    while (true){
        GetLocalTime(&time);
        t = time.wMilliseconds - time1.wMilliseconds + 1000 * (time.wSecond - time1.wSecond) + 60000 * (time.wMinute - time1.wMinute);
        step += t;
        if (bullet < 7500) {bullet += t;}
        GetLocalTime(&time1);
        ///       down
        if (GetKeyState(83) & 0x8000 || GetKeyState(115) & 0x8000 || GetKeyState(155) & 0x8000 || GetKeyState(235) & 0x8000){
            player_z = 1;
            if (map_1[player_y + 1][player_x] != 's' && step >= step_max){
                step = 0; player_y += 1;
            }
        }

        ///       up
        if (GetKeyState(87) & 0x8000 || GetKeyState(119) & 0x8000 || GetKeyState(150) & 0x8000 || GetKeyState(230) & 0x8000){
            player_z = 0;
            if (map_1[player_y - 1][player_x] != 's' && step >= step_max){
                step = 0; player_y -= 1;
            }
        }

        ///       right
        if (GetKeyState(68) & 0x8000 || GetKeyState(100) & 0x8000 || GetKeyState(130) & 0x8000 || GetKeyState(162) & 0x8000){
            player_z = 2;
            if (map_1[player_y][player_x + 1] != 's' && step >= step_max){
                step = 0; player_x += 1;
            }
        }

        ///        left
        if (GetKeyState(65) & 0x8000 || GetKeyState(97) & 0x8000 || GetKeyState(148) & 0x8000 || GetKeyState(228) & 0x8000){
            player_z = 3;
            if (map_1[player_y][player_x - 1] != 's' && step >= step_max){
                step = 0; player_x -= 1;
            }
        }

        ///       ok
        if (GetKeyState(32) & 0x8000){
            if (bullet >= 1500 && step >= step_max && map_1[player_y + pos[player_z][1]][player_x + pos[player_z][0]] != 's'){
                bullet -= 1500; bullet_x.push_back(player_x + pos[player_z][0]);
                bullet_y.push_back(player_y + pos[player_z][1]);
                bullet_z.push_back(player_z); bullet_t.push_back(0);
                step = 100;
            }
        }

        ///       super   k
        if ((super <= 2 && super_score >= 7 || super == 3 && super_score >= 7 * 3) && GetKeyState(75) & 0x8000 ||
            GetKeyState(107) & 0x8000 || GetKeyState(139) & 0x8000 || GetKeyState(171) & 0x8000){
            if (super == 1){
                for (int i = 0; i < 4; i++){
                    bullet_x.push_back(player_x + pos[i][0]);
                    bullet_y.push_back(player_y + pos[i][1]);
                    bullet_z.push_back(i); bullet_t.push_back(0);
                }
            }
            if (super == 2){
                if (pos[player_z][0] == 0){
                    bullet_x.push_back(player_x);
                    bullet_y.push_back(player_y + pos[player_z][1]);
                    bullet_z.push_back(player_z); bullet_t.push_back(0);
                    bullet_x.push_back(player_x - 1);
                    bullet_y.push_back(player_y + pos[player_z][1]);
                    bullet_z.push_back(player_z); bullet_t.push_back(0);
                    bullet_x.push_back(player_x + 1);
                    bullet_y.push_back(player_y + pos[player_z][1]);
                    bullet_z.push_back(player_z); bullet_t.push_back(0);
                }
                else {
                    bullet_x.push_back(player_x + pos[player_z][0]);
                    bullet_y.push_back(player_y);
                    bullet_z.push_back(player_z); bullet_t.push_back(0);
                    bullet_x.push_back(player_x + pos[player_z][0]);
                    bullet_y.push_back(player_y - 1);
                    bullet_z.push_back(player_z); bullet_t.push_back(0);
                    bullet_x.push_back(player_x + pos[player_z][0]);
                    bullet_y.push_back(player_y + 1);
                    bullet_z.push_back(player_z); bullet_t.push_back(0);
                }
            }
            if (super == 3){
                bullet_x.push_back(player_x + pos[player_z][0]);
                bullet_y.push_back(player_y + pos[player_z][1]);
                bullet_z.push_back(player_z); bullet_t.push_back(0);
                hp_x.push_back(player_x + pos[player_z][0]);
                hp_y.push_back(player_y + pos[player_z][1]);
            }
            super_score = 0;
        }

        ///       esc
        if (GetKeyState(VK_ESCAPE) & 0x8000) {break;}
        if (player_hp <= 0) {break;}


        if (fps_t != time1.wSecond){
            fps_t = time1.wSecond;
            if (fps_s >= 9999){fps = 9999;}
            else {fps = fps_s;}
            fps_s = 0;
        }
        else {fps_s += 1;}

        for (int j = 0; j < hp_x.size(); j++){
            if(hp_x[j] == player_x && hp_y[j] == player_y){
                hp_x[j] = hp_x[hp_x.size() - 1]; hp_x.pop_back();
                hp_y[j] = hp_y[hp_y.size() - 1]; hp_y.pop_back();
                player_hp += 1 * (player_hp < 9);
            }
        }


        for (int i = 0; i < bullet_x.size(); i++){
            bool bullet_delete = false;
            if (bullet_x[i] == player_x && bullet_y[i] == player_y){
                player_hp -= 1;
                bullet_delete = true;
            }
            else if (map_1[bullet_y[i]][bullet_x[i]] != 's'){
                for (int j = 0; j < enemy_xy.size(); j++){
                    if (bullet_x[i] == enemy_xy[j][0] && bullet_y[i] == enemy_xy[j][1]){
                        bullet_delete = true;
                        if (enemy_t[j] >= 10000){
                            enemy_hp[j] -= 1; super_score += 1; player_id = j;
                            if (enemy_hp[j] == 0){
                                enemy_t[j] = 0; enemy_hp[j] = Enemy_hp[enemy_id[j]];
                                score += Enemy_hp[enemy_id[j]]; player_id = -1;
                            }
                        }
                        break;
                    }
                }
            }
            else {bullet_delete = true;}

            bullet_t[i] += t;
            if (((bullet_z[i] <= 1 && bullet_t[i] >= 130) || (bullet_z[i] >= 2 && bullet_t[i] >= 100)) && !bullet_delete){
                //((bullet_z[i] <= 1 && bullet_t[i] >= 150) || (bullet_z[i] >= 2 && bullet_t[i] >= 100)) && !bullet_delete
                //bullet_t[i] >= 100 && !bullet_delete
                bullet_t[i] = 0;
                if (bullet_x[i] + pos[bullet_z[i]][0] == player_x && bullet_y[i] + pos[bullet_z[i]][1] == player_y){
                    player_hp -= 1;
                    bullet_delete = true;
                }
                else if (map_1[bullet_y[i] + pos[bullet_z[i]][1]][bullet_x[i] + pos[bullet_z[i]][0]] != 's'){
                    for (int j = 0; j < enemy_xy.size(); j++){
                        if (bullet_x[i] + pos[bullet_z[i]][0] == enemy_xy[j][0] && bullet_y[i] + pos[bullet_z[i]][1] == enemy_xy[j][1]){
                            bullet_delete = true;
                            if (enemy_t[j] >= 10000){
                                enemy_hp[j] -= 1; super_score += 1; player_id = j;
                                if (enemy_hp[j] == 0){
                                    enemy_t[j] = 0; enemy_hp[j] = Enemy_hp[enemy_id[j]];
                                    score += Enemy_hp[enemy_id[j]]; player_id = -1;
                                }
                            }
                            break;
                        }
                    }
                    if (!bullet_delete){
                        bullet_y[i] += pos[bullet_z[i]][1];
                        bullet_x[i] += pos[bullet_z[i]][0];
                    }
                }
                else {bullet_delete = true;}
            }
            if (bullet_delete){
                bullet_x[i] = bullet_x[bullet_x.size() - 1]; bullet_x.pop_back();
                bullet_y[i] = bullet_y[bullet_y.size() - 1]; bullet_y.pop_back();
                bullet_z[i] = bullet_z[bullet_z.size() - 1]; bullet_z.pop_back();
                bullet_t[i] = bullet_t[bullet_t.size() - 1]; bullet_t.pop_back();
            }
        }


        for (int i = 0; i < enemy_xy.size(); i++){
            if (enemy_t[i] >= 10000){
                int direction = 0;
                if (player_x == enemy_xy[i][0]){
                    if (abs(player_y - enemy_xy[i][1]) <= 1 && enemy_at[i] >= 500){
                        player_hp -= 1; enemy_at[i] = 0;
                    }
                    else if (enemy_at[i] >= Enemy_attack[enemy_id[i]]){
                        direction += (player_y > enemy_xy[i][1]);
                        bullet_x.push_back(enemy_xy[i][0] + pos[direction][0]);
                        bullet_y.push_back(enemy_xy[i][1] + pos[direction][1]);
                        bullet_z.push_back(direction); bullet_t.push_back(0);
                        enemy_at[i] = 0;
                    }

                }
                else if (player_y == enemy_xy[i][1]){
                    if (abs(player_x - enemy_xy[i][0]) <= 1 && enemy_at[i] >= 500){
                        player_hp -= 1; enemy_at[i] = 0;
                    }
                    else if (enemy_at[i] >= Enemy_attack[enemy_id[i]]){
                        direction += 2 + (player_x < enemy_xy[i][0]);
                        bullet_x.push_back(enemy_xy[i][0] + pos[direction][0]);
                        bullet_y.push_back(enemy_xy[i][1] + pos[direction][1]);
                        bullet_z.push_back(direction); bullet_t.push_back(0);
                        enemy_at[i] = 0;
                    }
                }
                for (int j = 0; j < hp_x.size(); j++){
                    if(hp_x[j] == enemy_xy[i][0] && hp_y[j] == enemy_xy[i][1]){
                        hp_x[j] = hp_x[hp_x.size() - 1]; hp_x.pop_back();
                        hp_y[j] = hp_y[hp_y.size() - 1]; hp_y.pop_back();
                        enemy_hp[i] += 1 * (enemy_hp[i] < 9);
                    }
                }
                enemy_at[i] += t;
            }
            else {enemy_t[i] += t;}
        }


        print_massiv(1, 0, {"x:"}, {{15, 15}}, screen_symbol, screen_color);
        print_int(3, 0, player_x, 2, 15, screen_symbol, screen_color);
        print_massiv(6, 0, {"y:"}, {{15, 15}}, screen_symbol, screen_color);
        print_int(8, 0, player_y, 2, 15, screen_symbol, screen_color);
        print_massiv(11, 0, {"z:"}, {{15, 15}}, screen_symbol, screen_color);
        print_texture(13, 0, {{24 + player_z}}, {{10}}, screen_symbol, screen_color);
        print_massiv(11, 0, {"t:"}, {{15, 15}}, screen_symbol, screen_color);
        if (step >= step_max){print_texture(13, 0, {{43}}, {{10}}, screen_symbol, screen_color);}
        else {print_texture(13, 0, {{45}}, {{12}}, screen_symbol, screen_color);}
        print_massiv(15, 0, {"bullet:"}, {{15, 15, 15, 15, 15, 15, 15}}, screen_symbol, screen_color);
        print_int(22, 0, bullet / 1500, 1, 15, screen_symbol, screen_color);
        print_massiv(24, 0, {"hp:"}, {{15, 15, 15, 15, 15, 15, 15}}, screen_symbol, screen_color);
        print_int(27, 0, player_hp, 2, 15, screen_symbol, screen_color);
        print_texture(29, 0, {{3}}, {{12}}, screen_symbol, screen_color);
        print_massiv(31, 0, {"super:"}, {{15, 15, 15, 15, 15, 15, 15}}, screen_symbol, screen_color);
        if (super <= 2 && super_score >= 7 || super == 3 && super_score >= 7 * 3){
            print_texture(37, 0, {{43}}, {{10}}, screen_symbol, screen_color);
        }
        else {print_texture(37, 0, {{45}}, {{12}}, screen_symbol, screen_color);}
        print_massiv(39, 0, {"f:"}, {{15, 15}}, screen_symbol, screen_color);
        print_int(41, 0, fps, 4, 15, screen_symbol, screen_color);

        print_massiv(1, 2, {"z:"}, {{15, 15}}, screen_symbol, screen_color);
        print_texture(3, 2, {{24 + player_z}}, {{10}}, screen_symbol, screen_color);
        print_massiv(5, 2, {"score:"}, {{15, 15, 15, 15, 15, 15}}, screen_symbol, screen_color);
        print_int(11, 2, score, 4, 15, screen_symbol, screen_color);
        if (player_id == -1){print_massiv(16, 2, {"-:--"}, {{15, 15, 15, 15,}}, screen_symbol, screen_color);}
        else{
            print_texture(16, 2, {{Enemy_ch[enemy_id[player_id]]}}, {{Enemy_cl[enemy_id[player_id]]}}, screen_symbol, screen_color);
            print_massiv(17, 2, {":"}, {{15}}, screen_symbol, screen_color);
            print_int(18, 2, enemy_hp[player_id], 2, 15, screen_symbol, screen_color);
        }
        print_texture(20, 2, {{3}}, {{12}}, screen_symbol, screen_color);



        for (int i = 0; i < enemy_xy.size(); i++){
            if (enemy_t[i] >= 10000){
                screen_symbol[enemy_xy[i][0]][enemy_xy[i][1] + 3] = Enemy_ch[enemy_id[i]];
                screen_color[enemy_xy[i][0]][enemy_xy[i][1] + 3] = Enemy_cl[enemy_id[i]];
            }
            else{
                screen_symbol[enemy_xy[i][0]][enemy_xy[i][1] + 3] = 253;
                screen_color[enemy_xy[i][0]][enemy_xy[i][1] + 3] = 10;
            }
        }
        for (int i = 0; i < hp_x.size(); i++){
            screen_symbol[hp_x[i]][hp_y[i] + 3] = 3;
            screen_color[hp_x[i]][hp_y[i] + 3] = 12;
        }
        for (int i = 0; i < bullet_x.size(); i++){
            screen_symbol[bullet_x[i]][bullet_y[i] + 3] = 43;
            screen_color[bullet_x[i]][bullet_y[i] + 3] = 15;
        }

        print_texture(player_x, player_y + 3, {{character}}, {{character_c}}, screen_symbol, screen_color);

        for (int i = 0; i < 22; i++){
            for (int j = 0; j < 46; j++){
                if (j < player_x + level_x[level] && j > player_x - level_x[level] &&
                    i < player_y + level_y[level] && i > player_y - level_y[level]){
                    if (map_1[i][j] == 's'){
                        screen_symbol[j][i + 3] = 219;
                        screen_color[j][i + 3] = 15;
                    }
                }
                else {
                    screen_symbol[j][i + 3] = 177;
                    screen_color[j][i + 3] = 15;
                }
            }
        }

        for (int i = 0; i < 46; i++){
            for (int j = 0; j < 25; j++){
                screen_buffer[i + 46 * j].Char.AsciiChar = char(screen_symbol[i][j]);
                screen_buffer[i + 46 * j].Attributes = screen_color[i][j];
            }
        }
        screen_symbol = screen_s; screen_color = screen_c;
        WriteConsoleOutput(screen_buffer_handle, screen_buffer, screen_buffer_info.dwSize, screen_buffer_pos, &screen_buffer_info.srWindow);
    }
    Sleep(1000);
}

int menu_map(){
    system("mode con cols=46 lines=25");
    system("title My_game_1");
    screen_buffer_handle = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, CONSOLE_TEXTMODE_BUFFER, 0);
    if (std_handle == INVALID_HANDLE_VALUE || screen_buffer_handle == INVALID_HANDLE_VALUE){
        printf("CreateConsoleScreenBuffer failed - (%d)\n", GetLastError());
    }
    if (! SetConsoleActiveScreenBuffer(screen_buffer_handle) ){
        printf("SetConsoleActiveScreenBuffer failed - (%d)\n", GetLastError());
    }

    if (! GetConsoleScreenBufferInfo(screen_buffer_handle, &screen_buffer_info) ){
        printf("GetConsoleScreenBufferInfo failed - (%d)\n", GetLastError());
    }
    screen_buffer_size = (int)screen_buffer_info.dwSize.X * (int)screen_buffer_info.dwSize.Y;
    screen_buffer = new CHAR_INFO[screen_buffer_size];
    memset(screen_buffer, 0, screen_buffer_size * sizeof(CHAR_INFO));
    HWND window_header = GetConsoleWindow();
    POINT mouse, mouse1, cursor;
    vector<vector<int>> screen_symbol(46, vector<int>(25, 0)), screen_color(46, vector<int>(25, 15)),
    screen_s(46, vector<int>(25, 0)), screen_c(46, vector<int>(25, 15));
    bool button_down = false, button_up = false, button_ok = true; int number = 0;
    SYSTEMTIME time;
    //vector<int> number_pos{1, 6, 12, 16};
    while (true){
        GetLocalTime(&time);
        ///       down
        if (GetKeyState(83) & 0x8000 || GetKeyState(115) & 0x8000 || GetKeyState(155) & 0x8000 || GetKeyState(235) & 0x8000){
            if (!button_down){number += 1; number %= 4;}
            button_down = true;
        } else {button_down = false;}

        ///       up
        if (GetKeyState(87) & 0x8000 || GetKeyState(119) & 0x8000 || GetKeyState(150) & 0x8000 || GetKeyState(230) & 0x8000){
            if (!button_up){number += 3; number %= 4;}
            button_up = true;
        } else {button_up = false;}

        ///       ok
        if (GetKeyState(32) & 0x8000){
            if (!button_ok){
                if (number == 0){break;}
                else {map_ = number;}
            }
            button_ok = true;
        } else {button_ok = false;}

        ///       esc
        if (GetKeyState(VK_ESCAPE) & 0x8000) {break;}

        screen_symbol[1][number + 1] = 16;

        print_massiv(4, 1, {"back"}, {{15, 15, 15, 15, 15}}, screen_symbol, screen_color);
        print_massiv(4, 2, {"map 1"}, {{15, 15, 15, 15, 15, 15}}, screen_symbol, screen_color);
        print_massiv(4, 3, {"random map"}, {{15, 15, 15, 15, 15, 15, 15, 15, 15, 15}}, screen_symbol, screen_color);
        print_massiv(4, 4, {"my map"}, {{15, 15, 15, 15, 15, 15, 15}}, screen_symbol, screen_color);
        print_texture(3, map_ + 1, {{178}}, {{10}}, screen_symbol, screen_color);


        for (int i = 0; i < 46; i++){
            for (int j = 0; j < 25; j++){
                screen_buffer[i + 46 * j].Char.AsciiChar = char(screen_symbol[i][j]);
                screen_buffer[i + 46 * j].Attributes = screen_color[i][j];
            }
        }
        screen_symbol = screen_s; screen_color = screen_c;
        WriteConsoleOutput(screen_buffer_handle, screen_buffer, screen_buffer_info.dwSize, screen_buffer_pos, &screen_buffer_info.srWindow);
    }
}

int menu_super(){
    system("mode con cols=46 lines=25");
    system("title My_game_1");
    screen_buffer_handle = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, CONSOLE_TEXTMODE_BUFFER, 0);
    if (std_handle == INVALID_HANDLE_VALUE || screen_buffer_handle == INVALID_HANDLE_VALUE){
        printf("CreateConsoleScreenBuffer failed - (%d)\n", GetLastError());
    }
    if (! SetConsoleActiveScreenBuffer(screen_buffer_handle) ){
        printf("SetConsoleActiveScreenBuffer failed - (%d)\n", GetLastError());
    }

    if (! GetConsoleScreenBufferInfo(screen_buffer_handle, &screen_buffer_info) ){
        printf("GetConsoleScreenBufferInfo failed - (%d)\n", GetLastError());
    }
    screen_buffer_size = (int)screen_buffer_info.dwSize.X * (int)screen_buffer_info.dwSize.Y;
    screen_buffer = new CHAR_INFO[screen_buffer_size];
    memset(screen_buffer, 0, screen_buffer_size * sizeof(CHAR_INFO));
    HWND window_header = GetConsoleWindow();
    POINT mouse, mouse1, cursor;
    vector<vector<int>> screen_symbol(46, vector<int>(25, 0)), screen_color(46, vector<int>(25, 15)),
    screen_s(46, vector<int>(25, 0)), screen_c(46, vector<int>(25, 15));
    bool button_down = false, button_up = false, button_ok = true; int number = 0;
    SYSTEMTIME time;
    vector<vector<vector<int>>> super_1{{{32, 32, 1, 32, 32, 32},{32, 32, 32, 32, 1, 32},{1, 32, character, 32, 32, 32},{32, 32, 32, 32, 32, 1},{32, 32, 1, 32, 32, 32}},
    {{32, 32, 1, 32, 32, 32},{32, 32, 43, 32, 1, 32},{1, 43, character, 43, 32, 1},{32, 32, 43, 32, 32, 32},{32, 32, 1, 32, 32, 32}},
    {{32, 32, 253, 32, 1, 32},{32, 32, 32, 32, 32, 32},{253, 32, character, 32, 43, 1},{32, 32, 32, 32, 32, 32},{32, 32, 253, 32, 32, 32}},
    {{32, 32, 253, 32, 1, 32},{32, 32, 32, 32, 32, 32},{253, 32, character, 32, 32, 253},{32, 32, 32, 32, 32, 32},{32, 32, 253, 32, 32, 32}},
    {{32, 32, 32, 32, 32, 1},{32, 32, 32, 32, 32, 32},{32, 32, character, 32, 32, 253},{32, 32, 32, 32, 32, 32},{32, 32, 32, 32, 32, 32}}};
    vector<vector<vector<int>>> super_1_c{{{15, 15, 10, 15, 15, 15},{15, 15, 15, 15, 10, 15},{10, 15, character_c, 15, 15, 15},{15, 15, 15, 15, 15, 10},{15, 15, 10, 15, 15, 15}},
    {{15, 15, 10, 15, 15, 15},{15, 15, 15, 15, 10, 15},{10, 15, character_c, 15, 15, 10},{15, 15, 15, 15, 15, 15},{15, 15, 10, 15, 15, 15}},
    {{15, 15, 10, 15, 10, 15},{15, 15, 15, 15, 15, 15},{10, 15, character_c, 15, 15, 10},{15, 15, 15, 15, 15, 15},{15, 15, 10, 15, 15, 15}},
    {{15, 15, 10, 15, 10, 15},{15, 15, 15, 15, 15, 15},{10, 15, character_c, 15, 15, 10},{15, 15, 15, 15, 15, 15},{15, 15, 10, 15, 15, 15}},
    {{15, 15, 15, 15, 15, 10},{15, 15, 15, 15, 15, 15},{15, 15, character_c, 15, 15, 10},{15, 15, 15, 15, 15, 15},{15, 15, 15, 15, 15, 15}}};
    vector<vector<vector<int>>> super_2{{{32, 32, 32, 32, 32, 32},{32, character, 32, 32, 1, 1},{32, 32, 32, 1, 32, 1}},
    {{32, 32, 43, 32, 1, 32},{32, character, 43, 32, 32, 1},{32, 32, 43, 1, 32, 1}},
    {{32, 32, 32, 43, 32, 1},{32, character, 32, 43, 1, 32},{32, 32, 32, 253, 32, 1}},
    {{32, 32, 32, 32, 43, 1},{32, character, 32, 32, 253, 32},{32, 32, 32, 253, 1, 32}},
    {{32, 32, 32, 32, 32, 253},{32, character, 32, 32, 253, 32},{32, 32, 32, 32, 1, 32}}};
    vector<vector<vector<int>>> super_2_c{{{15, 15, 15, 15, 15, 15},{15, character_c, 15, 15, 10, 10},{15, 15, 15, 10, 15, 10}},
    {{15, 15, 15, 15, 10, 15},{15, character_c, 15, 15, 15, 10},{15, 15, 15, 10, 15, 10}},
    {{15, 15, 15, 15, 15, 10},{15, character_c, 15, 15, 10, 15},{15, 15, 15, 10, 15, 10}},
    {{15, 15, 15, 15, 15, 10},{15, character_c, 15, 15, 10, 15},{15, 15, 15, 10, 10, 15}},
    {{15, 15, 15, 15, 15, 10},{15, character_c, 15, 15, 10, 15},{15, 15, 15, 15, 10, 15}}};
    vector<vector<vector<int>>> super_3{{{32, character, 32, 32, 1, 1}},{{32, character, 43, 32, 1, 1}},
    {{32, character, 3, 43, 1, 1}},{{32, character, 3, 32, 253, 1}},{{32, character, 3, 32, 253, 1}}};
    vector<vector<vector<int>>> super_3_c{{{15, character_c, 15, 15, 10, 10}},{{15, character_c, 15, 15, 10, 10}},
    {{15, character_c, 12, 15, 10, 10}},{{15, character_c, 12, 15, 10, 10}},{{15, character_c, 12, 15, 10, 10}}};
    vector<int> number_pos{1, 6, 12, 16};
    while (true){
        GetLocalTime(&time);
        ///       down
        if (GetKeyState(83) & 0x8000 || GetKeyState(115) & 0x8000 || GetKeyState(155) & 0x8000 || GetKeyState(235) & 0x8000){
            if (!button_down){number += 1; number %= 4;}
            button_down = true;
        } else {button_down = false;}

        ///       up
        if (GetKeyState(87) & 0x8000 || GetKeyState(119) & 0x8000 || GetKeyState(150) & 0x8000 || GetKeyState(230) & 0x8000){
            if (!button_up){number += 3; number %= 4;}
            button_up = true;
        } else {button_up = false;}

        ///       ok
        if (GetKeyState(32) & 0x8000){
            if (!button_ok){
                if (number == 0){break;}
                else {super = number;}
            }
            button_ok = true;
        } else {button_ok = false;}

        ///       esc
        if (GetKeyState(VK_ESCAPE) & 0x8000) {break;}

        screen_symbol[1][number_pos[number]] = 16;

        print_texture(3, number_pos[super] - 1, {{178}, {178}, {178}}, {{10}, {10}, {10}}, screen_symbol, screen_color);
        //print_texture(10, number_pos[super] - 1, {{178}, {178}, {178}}, {{10}, {10}, {10}}, screen_symbol, screen_color);

        print_massiv(4, 1, {"back and save"}, {{15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15}}, screen_symbol, screen_color);
        print_texture(4, 4, super_1[time.wMilliseconds / 200], super_1_c[time.wMilliseconds / 200], screen_symbol, screen_color);
        print_texture(4, 11, super_2[time.wMilliseconds / 200], super_2_c[time.wMilliseconds / 200], screen_symbol, screen_color);
        print_texture(4, 16, super_3[time.wMilliseconds / 200], super_3_c[time.wMilliseconds / 200], screen_symbol, screen_color);

        for (int i = 0; i < 46; i++){
            for (int j = 0; j < 25; j++){
                screen_buffer[i + 46 * j].Char.AsciiChar = char(screen_symbol[i][j]);
                screen_buffer[i + 46 * j].Attributes = screen_color[i][j];
            }
        }
        screen_symbol = screen_s; screen_color = screen_c;
        WriteConsoleOutput(screen_buffer_handle, screen_buffer, screen_buffer_info.dwSize, screen_buffer_pos, &screen_buffer_info.srWindow);
    }
}

int menu_character(){
    system("mode con cols=46 lines=25");
    system("title My_game_1");
    //setlocale(LC_ALL, "RUS");
    screen_buffer_handle = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, CONSOLE_TEXTMODE_BUFFER, 0);
    if (std_handle == INVALID_HANDLE_VALUE || screen_buffer_handle == INVALID_HANDLE_VALUE){
        printf("CreateConsoleScreenBuffer failed - (%d)\n", GetLastError());
    }
    if (! SetConsoleActiveScreenBuffer(screen_buffer_handle) ){
        printf("SetConsoleActiveScreenBuffer failed - (%d)\n", GetLastError());
    }

    if (! GetConsoleScreenBufferInfo(screen_buffer_handle, &screen_buffer_info) ){
        printf("GetConsoleScreenBufferInfo failed - (%d)\n", GetLastError());
    }
    screen_buffer_size = (int)screen_buffer_info.dwSize.X * (int)screen_buffer_info.dwSize.Y;
    screen_buffer = new CHAR_INFO[screen_buffer_size];
    memset(screen_buffer, 0, screen_buffer_size * sizeof(CHAR_INFO));
    HWND window_header = GetConsoleWindow();
    POINT mouse, mouse1, cursor;
    //SetWindowPos(window_header, HWND_TOP, 0, 0, 1808, 1808, NULL);
    vector<vector<int>> screen_symbol(46, vector<int>(25, 0)), screen_color(46, vector<int>(25, 15)),
    screen_s(46, vector<int>(25, 0)), screen_c(46, vector<int>(25, 15));
    bool button_down = false, button_up = false, button_ok = true; int number = 0;
    while (true){

        ///       down
        if (GetKeyState(83) & 0x8000 || GetKeyState(115) & 0x8000 || GetKeyState(155) & 0x8000 || GetKeyState(235) & 0x8000){
            if (!button_down){number += 1; number %= 31;}
            button_down = true;
        } else {button_down = false;}

        ///       up
        if (GetKeyState(87) & 0x8000 || GetKeyState(119) & 0x8000 || GetKeyState(150) & 0x8000 || GetKeyState(230) & 0x8000){
            if (!button_up){number += 30; number %= 31;}
            button_up = true;
        } else {button_up = false;}

        ///       ok
        if (GetKeyState(32) & 0x8000){
            if (!button_ok){
                if (number == 0) {break;}
                if (number <= 15) {character = 1; character_c = number;}
                else {character = 2; character_c = number - 15;}
            }
            button_ok = true;
        } else {button_ok = false;}

        ///       esc
        if (GetKeyState(VK_ESCAPE) & 0x8000) {break;}

        if (number < 16){screen_symbol[1][number + 1] = 16;}
        else {screen_symbol[9][number - 14] = 16;}
        for (int i = 1; i <= 2; i++){
            for (int j = 1; j <= 15; j++){
                print_texture(4 + 8 * (i - 1), 1 + j, {{i}}, {{j}}, screen_symbol, screen_color);
            }
        }
        print_massiv(4, 1, {"back and save"}, {{15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15}}, screen_symbol, screen_color);

        print_texture(3 + 8 * (character - 1), 1 + character_c, {{178}}, {{10}}, screen_symbol, screen_color);

        for (int i = 0; i < 46; i++){
            for (int j = 0; j < 25; j++){
                screen_buffer[i + 46 * j].Char.AsciiChar = char(screen_symbol[i][j]);
                screen_buffer[i + 46 * j].Attributes = screen_color[i][j];
            }
        }
        screen_symbol = screen_s; screen_color = screen_c;
        WriteConsoleOutput(screen_buffer_handle, screen_buffer, screen_buffer_info.dwSize, screen_buffer_pos, &screen_buffer_info.srWindow);
    }
}

int menu_map_maker(){
    system("mode con cols=46 lines=25");
    system("title My_game_1");
    screen_buffer_handle = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, CONSOLE_TEXTMODE_BUFFER, 0);
    if (std_handle == INVALID_HANDLE_VALUE || screen_buffer_handle == INVALID_HANDLE_VALUE){
        printf("CreateConsoleScreenBuffer failed - (%d)\n", GetLastError());
    }
    if (! SetConsoleActiveScreenBuffer(screen_buffer_handle) ){
        printf("SetConsoleActiveScreenBuffer failed - (%d)\n", GetLastError());
    }

    if (! GetConsoleScreenBufferInfo(screen_buffer_handle, &screen_buffer_info) ){
        printf("GetConsoleScreenBufferInfo failed - (%d)\n", GetLastError());
    }
    screen_buffer_size = (int)screen_buffer_info.dwSize.X * (int)screen_buffer_info.dwSize.Y;
    screen_buffer = new CHAR_INFO[screen_buffer_size];
    memset(screen_buffer, 0, screen_buffer_size * sizeof(CHAR_INFO));
    HWND window_header = GetConsoleWindow();
    //POINT mouse, mouse1, cursor;
    vector<vector<int>> screen_symbol(46, vector<int>(25, 0)), screen_color(46, vector<int>(25, 15)),
    screen_s(46, vector<int>(25, 0)), screen_c(46, vector<int>(25, 15));
    //bool button_down = false, button_up = false, button_ok = true; int number = 0;
    bool go = true;
    SYSTEMTIME time, time1;
    GetLocalTime(&time1);

    if (record[1] < 100 || record[2] < 60 || record[3] < 30 || record[4] < 20 || record[5] < 10 || record[6] < 7){
        print_massiv(4, 0, {"set minimum records:"}, {{15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15}},
                     screen_symbol, screen_color);
        //print_massiv(4, 2, {"back"}, {{15, 15, 15, 15, 15}}, screen_symbol, screen_color);
        print_massiv(4, 3, {"easy:"}, {{15, 15, 15, 15, 15}}, screen_symbol, screen_color);
        print_int(10, 3, 100, 3, 10 + 2 * (record[1] < 100), screen_symbol, screen_color);
        print_massiv(4, 4, {"normal:"}, {{15, 15, 15, 15, 15, 15, 15}}, screen_symbol, screen_color);
        print_int(12, 4, 60, 2, 10 + 2 * (record[2] < 60), screen_symbol, screen_color);
        print_massiv(4, 5, {"hard:"}, {{15, 15, 15, 15, 15}}, screen_symbol, screen_color);
        print_int(10, 5, 30, 2, 10 + 2 * (record[3] < 30), screen_symbol, screen_color);
        print_massiv(4, 6, {"very hard:"}, {{15, 15, 15, 15, 15, 15, 15, 15, 15, 15}}, screen_symbol, screen_color);
        print_int(15, 6, 20, 2, 10 + 2 * (record[4] < 20), screen_symbol, screen_color);
        print_massiv(4, 7, {"hardcore:"}, {{12, 12, 12, 12, 12, 12, 12, 12, 12, 12}}, screen_symbol, screen_color);
        print_int(14, 7, 10, 2, 10 + 2 * (record[5] < 10), screen_symbol, screen_color);
        print_massiv(4, 8, {"ultra hardcore:"}, {{4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4}}, screen_symbol, screen_color);
        print_int(20, 8, 7, 1, 10 + 2 * (record[6] < 7), screen_symbol, screen_color);
        print_massiv(4, 9, {"may I go home?"}, {{8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8}}, screen_symbol, screen_color);
        print_int(20, 9, 0, 1, 10, screen_symbol, screen_color);
        //screen_symbol[1][2] = 16;
        for (int i = 0; i < 46; i++){
            for (int j = 0; j < 25; j++){
                screen_buffer[i + 46 * j].Char.AsciiChar = char(screen_symbol[i][j]);
                screen_buffer[i + 46 * j].Attributes = screen_color[i][j];
            }
        }
        //screen_symbol = screen_s; screen_color = screen_c;
        WriteConsoleOutput(screen_buffer_handle, screen_buffer, screen_buffer_info.dwSize, screen_buffer_pos, &screen_buffer_info.srWindow);
        go = false;
        Sleep(7000);
    }
    int player_x = 1, player_y = 1, step_max = 150, t, step;

    while (go){
        GetLocalTime(&time);
        t = time.wMilliseconds - time1.wMilliseconds + 1000 * (time.wSecond - time1.wSecond) + 60000 * (time.wMinute - time1.wMinute);
        step += t;
        GetLocalTime(&time1);
        ///       down
        if (GetKeyState(83) & 0x8000 || GetKeyState(115) & 0x8000 || GetKeyState(155) & 0x8000 || GetKeyState(235) & 0x8000){
            if (player_y + 1 <= 20 && player_y + 1 >= 1 && step >= step_max){
                step = 0; player_y += 1;
            }
        }

        ///       up
        if (GetKeyState(87) & 0x8000 || GetKeyState(119) & 0x8000 || GetKeyState(150) & 0x8000 || GetKeyState(230) & 0x8000){
            if (player_y - 1 <= 20 && player_y - 1 >= 1 && step >= step_max){
                step = 0; player_y -= 1;
            }
        }

        ///       right
        if (GetKeyState(68) & 0x8000 || GetKeyState(100) & 0x8000 || GetKeyState(130) & 0x8000 || GetKeyState(162) & 0x8000){
            if (player_x + 1 <= 44 && player_x + 1 >= 1 && step >= step_max){
                step = 0; player_x += 1;
            }
        }

        ///        left
        if (GetKeyState(65) & 0x8000 || GetKeyState(97) & 0x8000 || GetKeyState(148) & 0x8000 || GetKeyState(228) & 0x8000){
            if (player_x - 1 <= 44 && player_x - 1 >= 1 && step >= step_max){
                step = 0; player_x -= 1;
            }
        }

        ///       ok
        if (GetKeyState(32) & 0x8000){
            my_map[player_y][player_x] = 's';
        }

        ///       shift
        if (GetKeyState(VK_SHIFT) & 0x8000){
            my_map[player_y][player_x] = ' ';
        }

        ///       esc
        if (GetKeyState(VK_ESCAPE) & 0x8000) {break;}

        for (int i = 0; i < 22; i++){
            for (int j = 0; j < 46; j++){
                if (my_map[i][j] == 's'){
                    screen_symbol[j][i] = 219;
                    screen_color[j][i] = 15;
                }
            }
        }

        print_texture(player_x, player_y, {{character}}, {{character_c}}, screen_symbol, screen_color);

        for (int i = 0; i < 46; i++){
            for (int j = 0; j < 25; j++){
                screen_buffer[i + 46 * j].Char.AsciiChar = char(screen_symbol[i][j]);
                screen_buffer[i + 46 * j].Attributes = screen_color[i][j];
            }
        }
        screen_symbol = screen_s; screen_color = screen_c;
        WriteConsoleOutput(screen_buffer_handle, screen_buffer, screen_buffer_info.dwSize, screen_buffer_pos, &screen_buffer_info.srWindow);
    }
}

int menu_level(){
    system("mode con cols=46 lines=25");
    system("title My_game_1");
    screen_buffer_handle = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, CONSOLE_TEXTMODE_BUFFER, 0);
    if (std_handle == INVALID_HANDLE_VALUE || screen_buffer_handle == INVALID_HANDLE_VALUE){
        printf("CreateConsoleScreenBuffer failed - (%d)\n", GetLastError());
    }
    if (! SetConsoleActiveScreenBuffer(screen_buffer_handle) ){
        printf("SetConsoleActiveScreenBuffer failed - (%d)\n", GetLastError());
    }

    if (! GetConsoleScreenBufferInfo(screen_buffer_handle, &screen_buffer_info) ){
        printf("GetConsoleScreenBufferInfo failed - (%d)\n", GetLastError());
    }
    screen_buffer_size = (int)screen_buffer_info.dwSize.X * (int)screen_buffer_info.dwSize.Y;
    screen_buffer = new CHAR_INFO[screen_buffer_size];
    memset(screen_buffer, 0, screen_buffer_size * sizeof(CHAR_INFO));
    HWND window_header = GetConsoleWindow();
    POINT mouse, mouse1, cursor;
    vector<vector<int>> screen_symbol(46, vector<int>(25, 0)), screen_color(46, vector<int>(25, 15)),
    screen_s(46, vector<int>(25, 0)), screen_c(46, vector<int>(25, 15));
    bool button_down = false, button_up = false, button_ok = true; int number = 0;
    SYSTEMTIME time;
    while (true){
        GetLocalTime(&time);
        ///       down
        if (GetKeyState(83) & 0x8000 || GetKeyState(115) & 0x8000 || GetKeyState(155) & 0x8000 || GetKeyState(235) & 0x8000){
            if (!button_down){number += 1; number %= 8;}
            button_down = true;
        } else {button_down = false;}

        ///       up
        if (GetKeyState(87) & 0x8000 || GetKeyState(119) & 0x8000 || GetKeyState(150) & 0x8000 || GetKeyState(230) & 0x8000){
            if (!button_up){number += 7; number %= 8;}
            button_up = true;
        } else {button_up = false;}

        ///       ok
        if (GetKeyState(32) & 0x8000){
            if (!button_ok){
                if (number == 0){break;}
                else {level = number;}
            }
            button_ok = true;
        } else {button_ok = false;}

        ///       esc
        if (GetKeyState(VK_ESCAPE) & 0x8000) {break;}

        screen_symbol[1][number + 1] = 16;

        print_massiv(4, 1, {"back and save"}, {{15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15}}, screen_symbol, screen_color);
        print_massiv(4, 2, {"easy"}, {{15, 15, 15, 15, 15}}, screen_symbol, screen_color);
        print_massiv(4, 3, {"normal"}, {{15, 15, 15, 15, 15, 15}}, screen_symbol, screen_color);
        print_massiv(4, 4, {"hard"}, {{15, 15, 15, 15, 15}}, screen_symbol, screen_color);
        print_massiv(4, 5, {"very hard"}, {{15, 15, 15, 15, 15, 15, 15, 15, 15}}, screen_symbol, screen_color);
        print_massiv(4, 6, {"hardcore"}, {{12, 12, 12, 12, 12, 12, 12, 12, 12, 12}}, screen_symbol, screen_color);
        print_massiv(4, 7, {"ultra hardcore"}, {{4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4}}, screen_symbol, screen_color);
        print_massiv(4, 8, {"may I go home?"}, {{8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8}}, screen_symbol, screen_color);
        print_texture(3, level + 1, {{178}}, {{10}}, screen_symbol, screen_color);

        for (int i = 0; i < 46; i++){
            for (int j = 0; j < 25; j++){
                screen_buffer[i + 46 * j].Char.AsciiChar = char(screen_symbol[i][j]);
                screen_buffer[i + 46 * j].Attributes = screen_color[i][j];
            }
        }
        screen_symbol = screen_s; screen_color = screen_c;
        WriteConsoleOutput(screen_buffer_handle, screen_buffer, screen_buffer_info.dwSize, screen_buffer_pos, &screen_buffer_info.srWindow);
    }
}

int menu_record(){
    system("mode con cols=46 lines=25");
    system("title My_game_1");
    screen_buffer_handle = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, CONSOLE_TEXTMODE_BUFFER, 0);
    if (std_handle == INVALID_HANDLE_VALUE || screen_buffer_handle == INVALID_HANDLE_VALUE){
        printf("CreateConsoleScreenBuffer failed - (%d)\n", GetLastError());
    }
    if (! SetConsoleActiveScreenBuffer(screen_buffer_handle) ){
        printf("SetConsoleActiveScreenBuffer failed - (%d)\n", GetLastError());
    }

    if (! GetConsoleScreenBufferInfo(screen_buffer_handle, &screen_buffer_info) ){
        printf("GetConsoleScreenBufferInfo failed - (%d)\n", GetLastError());
    }
    screen_buffer_size = (int)screen_buffer_info.dwSize.X * (int)screen_buffer_info.dwSize.Y;
    screen_buffer = new CHAR_INFO[screen_buffer_size];
    memset(screen_buffer, 0, screen_buffer_size * sizeof(CHAR_INFO));
    HWND window_header = GetConsoleWindow();
    POINT mouse, mouse1, cursor;
    vector<vector<int>> screen_symbol(46, vector<int>(25, 0)), screen_color(46, vector<int>(25, 15)),
    screen_s(46, vector<int>(25, 0)), screen_c(46, vector<int>(25, 15));
    bool button_down = false, button_up = false, button_ok = true; int number = 0;
    SYSTEMTIME time;
    //vector<int> number_pos{1, 6, 12, 16};
    while (true){
        GetLocalTime(&time);
        ///       down
        if (GetKeyState(83) & 0x8000 || GetKeyState(115) & 0x8000 || GetKeyState(155) & 0x8000 || GetKeyState(235) & 0x8000){
            if (!button_down){number += 0; number %= 1;}
            button_down = true;
        } else {button_down = false;}

        ///       up
        if (GetKeyState(87) & 0x8000 || GetKeyState(119) & 0x8000 || GetKeyState(150) & 0x8000 || GetKeyState(230) & 0x8000){
            if (!button_up){number += 0; number %= 1;}
            button_up = true;
        } else {button_up = false;}

        ///       ok
        if (GetKeyState(32) & 0x8000){
            if (!button_ok){
                if (number == 0){break;}
            }
            button_ok = true;
        } else {button_ok = false;}

        ///       esc
        if (GetKeyState(VK_ESCAPE) & 0x8000) {break;}

        screen_symbol[1][number + 1] = 16;

        print_massiv(4, 1, {"back"}, {{15, 15, 15, 15, 15}}, screen_symbol, screen_color);
        print_massiv(4, 2, {"easy:"}, {{15, 15, 15, 15, 15}}, screen_symbol, screen_color);
        print_int(10, 2, record[1], 4, 15, screen_symbol, screen_color);
        print_massiv(4, 3, {"normal:"}, {{15, 15, 15, 15, 15, 15, 15}}, screen_symbol, screen_color);
        print_int(12, 3, record[2], 4, 15, screen_symbol, screen_color);
        print_massiv(4, 4, {"hard:"}, {{15, 15, 15, 15, 15}}, screen_symbol, screen_color);
        print_int(10, 4, record[3], 4, 15, screen_symbol, screen_color);
        print_massiv(4, 5, {"very hard:"}, {{15, 15, 15, 15, 15, 15, 15, 15, 15, 15}}, screen_symbol, screen_color);
        print_int(15, 5, record[4], 4, 15, screen_symbol, screen_color);
        print_massiv(4, 6, {"hardcore:"}, {{12, 12, 12, 12, 12, 12, 12, 12, 12, 12}}, screen_symbol, screen_color);
        print_int(14, 6, record[5], 4, 15, screen_symbol, screen_color);
        print_massiv(4, 7, {"ultra hardcore:"}, {{4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4}}, screen_symbol, screen_color);
        print_int(20, 7, record[6], 4, 15, screen_symbol, screen_color);
        print_massiv(4, 8, {"may I go home?"}, {{8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8}}, screen_symbol, screen_color);
        print_int(20, 8, record[7], 4, 15, screen_symbol, screen_color);

        for (int i = 0; i < 46; i++){
            for (int j = 0; j < 25; j++){
                screen_buffer[i + 46 * j].Char.AsciiChar = char(screen_symbol[i][j]);
                screen_buffer[i + 46 * j].Attributes = screen_color[i][j];
            }
        }
        screen_symbol = screen_s; screen_color = screen_c;
        WriteConsoleOutput(screen_buffer_handle, screen_buffer, screen_buffer_info.dwSize, screen_buffer_pos, &screen_buffer_info.srWindow);
    }
}

int menu_fps(){
    system("mode con cols=46 lines=25");
    system("title My_game_1");
    screen_buffer_handle = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, CONSOLE_TEXTMODE_BUFFER, 0);
    if (std_handle == INVALID_HANDLE_VALUE || screen_buffer_handle == INVALID_HANDLE_VALUE){
        printf("CreateConsoleScreenBuffer failed - (%d)\n", GetLastError());
    }
    if (! SetConsoleActiveScreenBuffer(screen_buffer_handle) ){
        printf("SetConsoleActiveScreenBuffer failed - (%d)\n", GetLastError());
    }

    if (! GetConsoleScreenBufferInfo(screen_buffer_handle, &screen_buffer_info) ){
        printf("GetConsoleScreenBufferInfo failed - (%d)\n", GetLastError());
    }
    screen_buffer_size = (int)screen_buffer_info.dwSize.X * (int)screen_buffer_info.dwSize.Y;
    screen_buffer = new CHAR_INFO[screen_buffer_size];
    memset(screen_buffer, 0, screen_buffer_size * sizeof(CHAR_INFO));
    HWND window_header = GetConsoleWindow();
    POINT mouse, mouse1, cursor;
    vector<vector<int>> screen_symbol(46, vector<int>(25, 0)), screen_color(46, vector<int>(25, 15)),
    screen_s(46, vector<int>(25, 0)), screen_c(46, vector<int>(25, 15));
    bool button_down = false, button_up = false, button_ok = true; int number = 0;
    SYSTEMTIME time;
    while (true){
        GetLocalTime(&time);
        ///       down
        if (GetKeyState(83) & 0x8000 || GetKeyState(115) & 0x8000 || GetKeyState(155) & 0x8000 || GetKeyState(235) & 0x8000){
            if (!button_down){number += 1; number %= 5;}
            button_down = true;
        } else {button_down = false;}

        ///       up
        if (GetKeyState(87) & 0x8000 || GetKeyState(119) & 0x8000 || GetKeyState(150) & 0x8000 || GetKeyState(230) & 0x8000){
            if (!button_up){number += 4; number %= 5;}
            button_up = true;
        } else {button_up = false;}

        ///       ok
        if (GetKeyState(32) & 0x8000){
            if (!button_ok){
                if (number == 0){break;}
                else {fps_ = number;}
            }
            button_ok = true;
        } else {button_ok = false;}

        ///       esc
        if (GetKeyState(VK_ESCAPE) & 0x8000) {break;}

        screen_symbol[1][number + 1] = 16;

        print_massiv(4, 1, {"back and save"}, {{15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15}}, screen_symbol, screen_color);
        print_massiv(4, 2, {"100"}, {{15, 15, 15}}, screen_symbol, screen_color);
        print_massiv(4, 3, {"200"}, {{15, 15, 15}}, screen_symbol, screen_color);
        print_massiv(4, 4, {"1000"}, {{15, 15, 15, 15}}, screen_symbol, screen_color);
        print_massiv(4, 5, {"1000000"}, {{15, 15, 15, 15, 15, 15, 15}}, screen_symbol, screen_color);
        print_texture(3, fps_ + 1, {{178}}, {{10}}, screen_symbol, screen_color);

        for (int i = 0; i < 46; i++){
            for (int j = 0; j < 25; j++){
                screen_buffer[i + 46 * j].Char.AsciiChar = char(screen_symbol[i][j]);
                screen_buffer[i + 46 * j].Attributes = screen_color[i][j];
            }
        }
        screen_symbol = screen_s; screen_color = screen_c;
        WriteConsoleOutput(screen_buffer_handle, screen_buffer, screen_buffer_info.dwSize, screen_buffer_pos, &screen_buffer_info.srWindow);
    }
}

int main(){
    system("mode con cols=46 lines=25");
    system("title My_game_1");
    setlocale(LC_ALL, "C");
    screen_buffer_handle = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, CONSOLE_TEXTMODE_BUFFER, 0);
    if (std_handle == INVALID_HANDLE_VALUE || screen_buffer_handle == INVALID_HANDLE_VALUE){
        printf("CreateConsoleScreenBuffer failed - (%d)\n", GetLastError());
    }
    if (! SetConsoleActiveScreenBuffer(screen_buffer_handle) ){
        printf("SetConsoleActiveScreenBuffer failed - (%d)\n", GetLastError());
    }

    if (! GetConsoleScreenBufferInfo(screen_buffer_handle, &screen_buffer_info) ){
        printf("GetConsoleScreenBufferInfo failed - (%d)\n", GetLastError());
    }
    screen_buffer_size = (int)screen_buffer_info.dwSize.X * (int)screen_buffer_info.dwSize.Y;
    screen_buffer = new CHAR_INFO[screen_buffer_size];
    memset(screen_buffer, 0, screen_buffer_size * sizeof(CHAR_INFO));
    HWND window_header = GetConsoleWindow();
    POINT mouse, mouse1, cursor;
    //SetWindowPos(window_header, HWND_TOP, 0, 0, 1808, 1808, NULL);
    ofstream write;
    ifstream read;
    //system("mkdir %USERPROFILE%\\AppData\\Roaming\\My_game_1");
    system("mkdir C:\\Slavacell");
    system("mkdir C:\\Slavacell\\My_game_1");
    read.open("C:\\Slavacell\\My_game_1\\settings.txt");
    read >> super >> character >> character_c >> level >> map_ >> fps_ >> record[1] >> record[2] >> record[3] >>
    record[4] >> record[5] >> record[6] >> record[7];
    read.close();


    write.open("C:\\Slavacell\\My_game_1\\settings.txt");
    write << super << " " << character << " " << character_c << " " << level << " " << map_ << " " << fps_ << " " << record[1] << " "
    << record[2] << " " << record[3] << " " << record[4] << " " << record[5] << " " << record[6] << " " << record[7];
    write.close();


    read.open("C:\\Slavacell\\My_game_1\\my_map.txt");
    string sa;
    for (int i = 1; i <= 20; i++){
        read >> sa;
        for (int j = 1; j <= 44; j++){
            if (sa[j - 1] == 's'){my_map[i][j] = 's';}
            else if (sa[j - 1] == 'p'){my_map[i][j] = ' ';}
        }
    }
    read.close();

    SYSTEMTIME time, time1;
    //GetLocalTime(&time);
    GetLocalTime(&time);
    vector<vector<int>> screen_symbol(46, vector<int>(25, 0)), screen_color(46, vector<int>(25, 15)),
    screen_s(46, vector<int>(25, 0)), screen_c(46, vector<int>(25, 15));
    float t;time1 = time;
    GetLocalTime(&time);
    t = time.wMilliseconds - time1.wMilliseconds + (time.wSecond - time1.wSecond) * 1000 + (time.wMinute - time1.wMinute) * 60000;

    vector<string> main_menu{"start the new game", "workout", "map", "super", "character", "map maker", "level", "record", "fps for game"};
    //GetCursorPos(&mouse); cursor.x = 0; cursor.y = 0;
    //menu();
    bool button_down = false, button_up = false, button_ok = true; int number = 0;
    while (true){

        ///       down
        if (GetKeyState(83) & 0x8000){// || GetKeyState(115) & 0x8000 || GetKeyState(155) & 0x8000 || GetKeyState(235) & 0x8000){
            if (!button_down){number += 1; number %= 9;}
            button_down = true;
        } else {button_down = false;}

        ///       up
        if (GetKeyState(87) & 0x8000 || GetKeyState(119) & 0x8000 || GetKeyState(150) & 0x8000 || GetKeyState(230) & 0x8000){
            if (!button_up){number += 8; number %= 9;}
            button_up = true;
        } else {button_up = false;}

        ///       ok
        if (GetKeyState(32) & 0x8000){
            if (!button_ok){
                if (number == 0) {new_game();}
                if (number == 1) {workout();}
                if (number == 2) {menu_map();}
                if (number == 3) {menu_super();}
                if (number == 4) {menu_character();}
                if (number == 5) {menu_map_maker();}
                if (number == 6) {menu_level();}
                if (number == 7) {menu_record();}
                if (number == 8) {menu_fps();}

                write.open("C:\\Slavacell\\My_game_1\\settings.txt");
                write << super << " " << character << " " << character_c << " " << level << " " << map_<< " " << fps_ << " " << record[1] << " "
                << record[2] << " " << record[3] << " " << record[4] << " " << record[5] << " " << record[6] << " " << record[7];
                write.close();

                write.open("C:\\Slavacell\\My_game_1\\my_map.txt");
                string sa;
                for (int i = 1; i <= 20; i++){
                    for (int j = 1; j <= 44; j++){
                        if (my_map[i][j] == 's'){write << "s";}
                        else if (my_map[i][j] == ' '){write << "p";}
                    }
                    write << endl;
                }
                write.close();
            }
            button_ok = true;
        } else {button_ok = false;}
        screen_symbol[1][number + 1] = 16;
        //screen_symbol[1][7 + 1] = 219;
        for (int i = 0; i < main_menu.size(); i++){
            print_massiv(4, 1 + i, {main_menu[i]}, {{15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15, 15}}, screen_symbol, screen_color);
        }

        for (int i = 0; i < 46; i++){
            for (int j = 0; j < 25; j++){
                screen_buffer[i + 46 * j].Char.AsciiChar = char(screen_symbol[i][j]);
                screen_buffer[i + 46 * j].Attributes = screen_color[i][j];
            }
        }
        screen_symbol = screen_s; screen_color = screen_c;
        WriteConsoleOutput(screen_buffer_handle, screen_buffer, screen_buffer_info.dwSize, screen_buffer_pos, &screen_buffer_info.srWindow);
    }
}
