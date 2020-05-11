#include <iostream>
#include <cctype>


struct Point {
    Point() { }
    Point(unsigned int px, unsigned int py) : x(px), y(py) { }

    unsigned int x, y;
};

class Exception { };
class ChessIllegalMove : Exception { };


enum PieceType { FREE = 0, PAWN = 1, ROOK = 2, BISHOP = 3, KNIGHT = 4, QUEEN = 5, KING = 6, INVALID = 7 };
enum PieceSide { BLACK, WHITE, NA };

class Piece {
public:
    Piece() { }
    Piece(const PieceType& pt, const PieceSide& ps) : type(pt), side(ps) { }
    Piece(const Piece& p) : type(p.type), side(p.side) { }

    bool IsInvalid() const { return type == PieceType::INVALID; }

    static char GetPieceDisplay(Piece& p) {
        char piece_display = 0;
        switch(p.type) {
            case PieceType::PAWN:       piece_display = 'p';    break;
            case PieceType::ROOK:       piece_display = 'r';    break;
            case PieceType::BISHOP:     piece_display = 'b';    break;
            case PieceType::KNIGHT:     piece_display = 'n';    break;
            case PieceType::QUEEN:      piece_display = 'q';    break;
            case PieceType::KING:       piece_display = 'k';    break;
            case PieceType::INVALID:    piece_display = '*';    break;
            case PieceType::FREE:       piece_display = '.';    break;
            default:                    piece_display = ' ';
        }

        return p.side == PieceSide::BLACK ? std::toupper(piece_display) : piece_display;
    }

    friend std::ostream& operator<<(std::ostream& os, Piece& p) {
        os << Piece::GetPieceDisplay(p);
        return os;
    }

    PieceType type;
    PieceSide side;
};

Piece INVALID_PIECE(PieceType::INVALID, PieceSide::NA);

class Board {
    public:
        Board() {
            ResetBoard();
        }

        void ResetBoard() {
            PieceSide side;
            PieceType type;
            for(auto x = 0; x < 12; x++) {
                for(auto y = 0; y < 12; y++) {
                    type = PieceType(default_grid[x][y]);

                    if(type == PieceType::INVALID || type == PieceType::FREE) {
                        side = PieceSide::NA;
                    } else if(x <= 4) {
                        side = PieceSide::WHITE;
                    } else {
                        side = PieceSide::BLACK;
                    }
                    
                    grid[x][y] = Piece(type, side);
                }
            }
        }

        void MakeMove(Point& source, Point& destination) {
            Piece source_piece = grid[source.x][source.y];
            Piece destination_piece = grid[destination.x][destination.y];

            if(source_piece.IsInvalid() || destination_piece.IsInvalid() || source_piece.side == destination_piece.side)
                throw ChessIllegalMove();

            
        }

        friend std::ostream& operator<<(std::ostream& os, Board b) {
            for(auto x = 0; x < 12; x++) {
                for(auto y = 0; y < 12; y++){
                    os << b.grid[x][y] << ' ';
                }
                os << '\n';
            }
            return os;
        }

    private:
        Piece grid[12][12];

        int default_grid[12][12] = {
            { 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7 },
            { 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7 },
            { 7, 7, 2, 4, 3, 5, 6, 3, 4, 2, 7, 7 },
            { 7, 7, 1, 1, 1, 1, 1, 1, 1, 1, 7, 7 },
            { 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7 },
            { 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7 },
            { 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7 },
            { 7, 7, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7 },
            { 7, 7, 1, 1, 1, 1, 1, 1, 1, 1, 7, 7 },
            { 7, 7, 2, 4, 3, 5, 6, 3, 4, 2, 7, 7 },
            { 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7 },
            { 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7 }
        };
};

int main(int argc, char** argv) {
    Board chess_board;
    std::cout << chess_board;
    return 0;
}