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

enum Pieace {
    PAWN = 1,
    KNIGHT,
    BISHOP,
    ROOK,
    QUEEN,
    KING
};

typedef struct Square {
    Color col;
    Color main_col;
    int piece;
    Vector2 pos;
    Rectangle rect;
} Square;

Square board[8][8];
Square* current; //most recently clicked

void init_board() {
    bool white = false;
    for(int y = 0; y < 8; y++) {
        white = !white;
        for(int x = 0; x < 8; x++) {
            board[y][x] = (Square) {
                col(white),
                col(white),
                0, //TODO: use enum
                (Vector2) {y, x},
                (Rectangle) {x*sq_dim+w_padding , y*sq_dim+h_padding, sq_dim, sq_dim}
            };
            white = !white;
        }
    }

    for(int x = 0; x < 8; x++) {
        board[1][x].piece = PAWN;
    }

    for(int x = 0; x < 8; x++) {
        board[6][x].piece = PAWN;
    }

    board[0][0].piece = ROOK;
    board[0][7].piece = ROOK;
    board[7][0].piece = ROOK;
    board[7][7].piece = ROOK;

    board[0][1].piece = KNIGHT;
    board[0][6].piece = KNIGHT;
    board[7][1].piece = KNIGHT;
    board[7][6].piece = KNIGHT;

    board[0][2].piece = BISHOP;
    board[0][5].piece = BISHOP;
    board[7][2].piece = BISHOP;
    board[7][5].piece = BISHOP;

    board[0][3].piece = QUEEN;
    board[7][3].piece = QUEEN;

    board[0][4].piece = KING;
    board[7][4].piece = KING;
}

void show_moves() {
    int x = current->pos.x;
    int y = current->pos.y;
    printf("y: %d, x:%d\n", y, x);
    if(current->piece == KING) {
        if(y > 0) board[x][y-1].col = RED;
        if(y < 7) board[x][y+1].col = RED;
        if(x > 0) board[x-1][y].col = RED;
        if(x < 7) board[x+1][y].col = RED;
    }
}

void draw_board() {
    for(int y = 0; y < 8; y++) {
        for(int x = 0; x < 8; x++) {
            Square sq = board[y][x];
            DrawRectangleRec(sq.rect, sq.col);
            Vector2 textPos = (Vector2){ sq.rect.x + sq_dim/2, sq.rect.y + sq_dim/2};
            if(sq.piece) DrawTextCodepoint(GetFontDefault(), sq.piece + '0', textPos, 12.0f, col(!sq.col.r));
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
        int x = (pos.x - w_padding)/sq_dim;
        int y = (pos.y - h_padding)/sq_dim;
        if(current) current->col = current->main_col;
        current = &board[y][x];
    }
    if(current) current->col = BLUE;
    show_moves();
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
