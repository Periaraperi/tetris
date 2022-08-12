#include "tetromino.h"

Tetromino::Tetromino(){}

Tetromino::Tetromino(Tetromino_Type shape_type) 
{
    m_type = shape_type;
    m_rotated = false;
    init_piece(shape_type);
}

Tetromino::~Tetromino() {}

void Tetromino::init_piece(Tetromino_Type shape_type)
{
    switch (shape_type){
        case Tetromino_Type::L: {
            m_positions.push_back({0, 0,0});
            m_positions.push_back({0,-1,0});
            m_positions.push_back({0, 1,0});
            m_positions.push_back({1, 1,0});
            m_color_id = 0;
            break;
        }
        case Tetromino_Type::L_MIRRORED: {
            m_positions.push_back({ 0, 0,0});
            m_positions.push_back({ 0,-1,0});
            m_positions.push_back({ 0, 1,0});
            m_positions.push_back({-1, 1,0});
            m_color_id = 1;
            break;
        }
        case Tetromino_Type::S: {
            m_positions.push_back({ 0, 0,0});
            m_positions.push_back({ 1, 0,0});
            m_positions.push_back({ 0, 1,0});
            m_positions.push_back({-1, 1,0});
            m_color_id = 0;
            break;
        }
        case Tetromino_Type::Z: {
            m_positions.push_back({ 0, 0,0});
            m_positions.push_back({ 0, 1,0});
            m_positions.push_back({-1, 0,0});
            m_positions.push_back({ 1, 1,0});
            m_color_id = 1;
            break;
        }
        case Tetromino_Type::T: {
            m_positions.push_back({ 0, 0,0});
            m_positions.push_back({ 0,-1,0});
            m_positions.push_back({ 1, 0,0});
            m_positions.push_back({-1, 0,0});
            m_color_id = 2;
            break;
        }
        case Tetromino_Type::SQUARE: {
            m_positions.push_back({0,0,0});
            m_positions.push_back({1,0,0});
            m_positions.push_back({0,1,0});
            m_positions.push_back({1,1,0});
            m_color_id = 2;
            break;
        }
        case Tetromino_Type::BAR: {
            m_positions.push_back({ 0,0,0});
            m_positions.push_back({-1,0,0});
            m_positions.push_back({ 1,0,0});
            m_positions.push_back({ 2,0,0});
            m_color_id = 2;
            break;
        }
    }
}

void Tetromino::offset(int x, int y)
{
    for(auto& p:m_positions) {
        p.x += x;
        p.y += y;
    }
}

void Tetromino::move(const Vector3<int>& vec, std::vector<std::vector<int>>& grid)
{
    std::vector<Vector3<int>> temp = m_positions;
    for(auto& p:temp) {
        p.x += vec.x;
        p.y += vec.y;
        if(!is_valid_position(p.x,p.y,grid))
            return;
    }
    m_positions = temp;
}

void Tetromino::rotate(const std::vector<std::vector<int>>& grid)
{
    if(m_type==Tetromino_Type::SQUARE) return; // does not rotate

    std::vector<Vector3<int>> temp = m_positions;
    
    // pivot point is always on first index in positions
    int x = temp[0].x;
    int y = temp[0].y;
    
    // rotate by 90 deg
    // and check if rotated coordinate is valid
    for(auto& p:temp) {
        // translate to origin 
        p.x -= x;
        p.y -= y;
        // rotate around pivot (m_positions[0])
        std::swap(p.x,p.y);
        if((m_type==Tetromino_Type::BAR || m_type==Tetromino_Type::S || m_type==Tetromino_Type::Z) && m_rotated) 
            p.y *= (-1);
        else 
            p.x *= (-1);
        // translate back
        p.x += x;
        p.y += y;

        // these types are special
        if((m_type==Tetromino_Type::BAR || m_type==Tetromino_Type::S || m_type==Tetromino_Type::Z)) {
            if(!m_rotated)
                ++p.x;
            else 
                --p.x;
        }

        // check if coordinate is valid
        if(!is_valid_position(p.x,p.y,grid))
            return;
    }

    m_positions = temp;
    if((m_type==Tetromino_Type::BAR || m_type==Tetromino_Type::S || m_type==Tetromino_Type::Z)) {
        bool k = !m_rotated;
        m_rotated = k;
    }
    
}

bool Tetromino::go_down(const std::vector<std::vector<int>>& grid)
{
    std::vector<Vector3<int>> temp = m_positions;
    for(auto& p:temp) {
        ++p.y;
        if(!is_valid_position(p.x,p.y,grid))
            return false;
    }
    m_positions = temp;
    return true;
}

bool Tetromino::is_valid_position(int x, int y, const std::vector<std::vector<int>>& grid)
{
    if(!(x>=0 && x<10 && y<20)) return false;
    if(y<0) return true;
    if(grid[y][x]!=0) return false;
    return true;
}
