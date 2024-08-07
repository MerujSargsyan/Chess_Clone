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

const int board[8][8];

void draw_board() {
    bool white = false;
    for(int x = w_padding; x < board_dim; x+=sq_dim) {
        white = !white;
        for(int y = h_padding; y < board_dim; y+=sq_dim) {
            DrawRectangle(x, y, sq_dim, sq_dim, col(white));
            white = !white;
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

void init() {
    InitWindow(window_width, window_height, "Chess Clone");
    printf("%d\n", board_dim);
}

void update() {
    while(!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(WHITE);
        // TODO: implement update based draw system
        draw();
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
