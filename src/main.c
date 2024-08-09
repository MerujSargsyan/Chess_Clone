#include <raylib.h>
#include <stdio.h>

#define min(A,B) ((A) < (B)? A: B)
#define col(C) (C)? WHITE: BLACK

const int window_width = 800;
const int window_height = 800;

const int sq_dim = 75;

const int w_padding = (window_width - sq_dim*8)/2;
const int h_padding = (window_height - sq_dim*8)/2;

const int board_dim = min(window_width - w_padding, window_height - h_padding);

typedef struct Square {
    Color col;
    Color main_col;
    int piece;
    Rectangle rect;
} Square;

Square board[8][8];
Square* current; //most recently clicked

void init_board() {
    bool white = false;
    for(int x = 0; x < 8; x++) {
        white = !white;
        for(int y = 0; y < 8; y++) {
            board[x][y] = (Square) {
                col(white),
                col(white),
                0, //TODO: use enum
                (Rectangle) {x*sq_dim+w_padding , y*sq_dim+h_padding, sq_dim, sq_dim}
            };
            white = !white;
        }
    }
}

void draw_board() {
    for(int x = 0; x < 8; x++) {
        for(int y = 0; y < 8; y++) {
            Square sq = board[x][y];
            DrawRectangleRec(sq.rect, sq.col);
        }
    }

    DrawLine(w_padding, h_padding, board_dim, h_padding, BLACK);
    DrawLine(w_padding, h_padding, w_padding, board_dim, BLACK);
    DrawLine(w_padding, board_dim, board_dim, board_dim, BLACK);
    DrawLine(board_dim, h_padding, board_dim, board_dim, BLACK);
}

void draw() {
    draw_board();
}

void check_input(Vector2 pos) {
    if(pos.x >= w_padding && pos.x < board_dim && pos.y >= h_padding && pos.y < board_dim)
    {
        int x = (pos.x- w_padding)/sq_dim;
        int y = (pos.y- h_padding)/sq_dim;
        if(current) current->col = current->main_col;
        current = &board[x][y];
    }
    if(current) current->col = BLUE;
}

void init() {
    InitWindow(window_width, window_height, "Chess Clone");
    init_board();
}

void update() {
    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);
        // TODO: implement update based draw system
        draw();
        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)) check_input(GetMousePosition());
        EndDrawing();
    }
}

void end() {
    CloseWindow();
}

int main() {
    init();
    update();
    end();
    return 0;
}
