#pragma once
#include <cassert>
#include <cstdlib>
#include <vector>

// Модель игрового поля

class Model {
    public:
    using FieldT = std::vector<std::vector<char>>;

    private:

    size_t Height;
    size_t Width;

    FieldT Field; 
 
    FieldT NewField; 

    private:
 
    static bool CalcCellValue (bool isLife, size_t nLife); 

    void UpdateCell_NonBoundary(int i, int j);

    void UpdateCell_Boundary(int i, int j);

    public:

    Model(size_t width, size_t height);

    void Update();

    const FieldT &GetState() const;

    void SetCell(int i, int j, bool value);

    void ToggleCell(int i, int j);

    void Clear();
};