#include "Model.hpp"

bool Model::CalcCellValue(bool isLife, size_t nLife){
    if (isLife){
        if (nLife < 2) return false;
        if (nLife < 4) return true;
        return false;
    }else {
        if (nLife == 3) return true;
        return false;
    }
}

void Model::UpdateCell_NonBoundary(int i, int j){
    assert(i != 0 && i != Height - 1 && j != 0 && j != Width - 1);

    size_t nLife = 0;

    for (int di = -1; di <= 1; ++di){
        for (int dj = -1; dj <= 1; ++dj) {
            nLife += Field[i + di][j + dj];
        }
    }
    nLife -= Field[i][j];

    NewField[i][j] = CalcCellValue(Field[i][j], nLife);
}

void Model::UpdateCell_Boundary(int i, int j){
    assert(i == 0 || i == Height - 1 || j == 0 || j == Width - 1);

    NewField[i][j] = false;
}

Model::Model(size_t width, size_t height)
    : Width{width}, Height{height}, Field(height, std::vector<char>(width)){
    Clear();

    NewField = Field;
}

void Model::Update(){
    for (int i = 0; i < Height; ++i){
        UpdateCell_Boundary(i, 0);
        UpdateCell_Boundary(i, Width - 1);
    }
    for (int j = 0; j < Width; ++j){
        UpdateCell_Boundary(0, j);
        UpdateCell_Boundary(Height - 1, j);
    }
    for (int i = 1; i < Height - 1; ++i){
        for (int j = 1; j < Width - 1; ++j){
        UpdateCell_NonBoundary(i, j);        
        }
    }
    
    Clear();
    std::swap(NewField, Field);
}

const Model::FieldT& Model::GetState() const {
    return Field;
}

void Model::SetCell(int i, int j, bool value){
    Field[i][j] = value;
}

void Model::ToggleCell(int i, int j){
    Field[i][j] = !Field[i][j];
}

void Model::Clear(){
    for (size_t i = 0; i < Height; ++i){
        for (size_t j = 0; j < Width; ++j) {
            Field[i][j] = 0;
        }
    }
}