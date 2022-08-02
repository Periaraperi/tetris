#pragma once

#include <vector>
#include "vector3.h"
#include <iostream>

enum class Tetromino_Type {
    L, L_MIRRORED,
    S,Z,
    T,
    SQUARE,
    BAR
};

static std::vector<Vector3<int>> colors = { {91,137,48}, {105,25,25}, {92,55,120}};

class Tetromino {
public:
    Tetromino();
    Tetromino(Tetromino_Type shape_type);
    ~Tetromino();

    void move(const Vector3<int>& vec, std::vector<std::vector<int>>& grid);
    void rotate(const std::vector<std::vector<int>>& grid);
    bool go_down(const std::vector<std::vector<int>>& grid);
    bool is_valid_position(int x, int y, const std::vector<std::vector<int>>& grid);
    void offset(int x, int y);

    std::vector<Vector3<int>> get_positions() {return m_positions;}
    Tetromino_Type get_type() {return m_type;}
    int get_color_id() {return m_color_id;}
private:
    Tetromino_Type m_type;
    int m_color_id;
    bool m_rotated; // need only for bar, s and z
    std::vector<Vector3<int>> m_positions;
    void init_piece(Tetromino_Type shape_type);
};
