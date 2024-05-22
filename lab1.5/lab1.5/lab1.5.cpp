//1.5
//Дачный участок Степана Петровича имеет форму прямоугольника размером a x b.На участке
//имеется n построек, причем основание каждой постройки — прямоугольник со сторонами,
//параллельными сторонам участка.
//Вдохновленный успехами соседей, Степан Петрович хочет посадить на своем участке m видов
//плодовых культур(участок Степана Петровича находится в северной местности, поэтому m = 1
//или m = 2).Для каждого вида растений Степан Петрович хочет выделить отдельную
//прямоугольную грядку со сторонами, параллельными сторонам участка.Само собой, грядки не
//могут занимать территорию, занятую постройками или другими грядками.
//Степан Петрович хочет расположить грядки таким образом, чтобы их суммарная площадь была
//максимальной.Грядки не должны пересекаться, но могут касаться друг друга.
//
//Требуется написать программу, которая по заданным размерам участка и координатам
//построек определяет оптимальное расположение планируемых грядок.
//Ввод.В первой строке входного файла содержатся два целых числа n и m(0 ≤ n ≤ 10; 1 ≤ m ≤
//2).Во второй строке содержатся два целых числа a и b(1 ≤ a, b ≤ 10000).Далее следуют n
//строк, каждая из которых содержит четыре целых числа x i, 1, y i, 1, x i, 2, y i, 2 –координаты двух
//противоположных углов постройки(0  x i, 1 & lt; x i, 2  a, 0  y i, 1 & lt; y i, 2   b).Различные постройки не могут
//пересекаться, но могут касаться друг друга.
//Вывод.В первой строке выводится общая площадь грядок.Каждая из следующих m строк
//содержит координаты двух противоположных углов предполагаемой грядки.Координаты должны
//быть целыми(всегда можно добиться максимальной суммарной площади грядок, располагая их в
//прямоугольниках с целыми координатами).В случае, если в вашем решении Степану Петровичу
//следует расположить менее m грядок, необходимо вывести для грядок, которые не следует сажать,
//строку «0 0 0 0»(см.второй пример).

//Баранов Антон Сергеевич ПС-23, Visual Studio 2022

//Источники:
//https://code.tutsplus.com/collision-detection-using-the-separating-axis-theorem--gamedev-169t
//http://cppstudio.com/post/468/

#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <ctime>

const std::string INPUT_FILE_NAME = "input9.txt";
const std::string OUTPUT_FILE_NAME = "output.txt";

struct Coordinates
{
    int x;
    int y;
};

struct DoubleCoordinates
{
    double x;
    double y;
};

struct BuildingPosition
{
    Coordinates topLeftCorner;
    Coordinates bottomRightCorner;
};

bool IsPointViable(std::vector<BuildingPosition> &positions, int x, int y)
{
    std::vector<BuildingPosition>::iterator buildingCoordinates = positions.begin();
    bool isPointViable = true; //Не находится ли точка внутри уже существующей постройки

    for (buildingCoordinates; buildingCoordinates != positions.end(); ++buildingCoordinates)
    {
        if (buildingCoordinates->topLeftCorner.x < x &&
            buildingCoordinates->bottomRightCorner.x > x &&
            buildingCoordinates->topLeftCorner.y < y &&
            buildingCoordinates->bottomRightCorner.y > y)
        {
            isPointViable = false;
            break;
        }
    }

    return isPointViable;
}

bool IsCollisionPresent(BuildingPosition firstPos, BuildingPosition secondPos)
{
    double firstHalfWidth = static_cast<double>(firstPos.bottomRightCorner.x - firstPos.topLeftCorner.x) / 2;
    double firstHalfHeight = static_cast<double>(firstPos.bottomRightCorner.y - firstPos.topLeftCorner.y) / 2;

    DoubleCoordinates firstCenter = { firstPos.topLeftCorner.x + firstHalfWidth, firstPos.topLeftCorner.y + firstHalfHeight };

    double secondHalfWidth = static_cast<double>(secondPos.bottomRightCorner.x - secondPos.topLeftCorner.x) / 2;
    double secondHalfHeight = static_cast<double>(secondPos.bottomRightCorner.y - secondPos.topLeftCorner.y) / 2;

    DoubleCoordinates secondCenter = { secondPos.topLeftCorner.x + secondHalfWidth, secondPos.topLeftCorner.y + secondHalfHeight };

    double lengthX = abs(firstCenter.x - secondCenter.x);
    double lengthY = abs(firstCenter.y - secondCenter.y);

    double gapX = lengthX - secondHalfWidth - firstHalfWidth;
    double gapY = lengthY - secondHalfHeight - firstHalfHeight;
    if (gapX < 0 && gapY < 0)
        return true;
    else
        return false;
}

int main()
{
    std::ifstream inputFile;

    inputFile.open(INPUT_FILE_NAME);
    if (inputFile.fail())
    {
        std::cout << "File opening error" << std::endl;
        return 0;
    }

    int buildingsQuantity = 0;
    int culturesQuantity = 0;

    int fieldWidth = 0;
    int fieldHeight = 0;

    std::vector<BuildingPosition> vectorOfPositions;
    std::set<int> setOfAllPositionsX;
    std::set<int> setOfAllPositionsY;

    inputFile >> buildingsQuantity >> culturesQuantity;
    inputFile >> fieldWidth >> fieldHeight;

    setOfAllPositionsX.insert(0);
    setOfAllPositionsX.insert(fieldWidth);

    setOfAllPositionsY.insert(0);
    setOfAllPositionsY.insert(fieldHeight);

    BuildingPosition temp;

    for (int i = 0; i < buildingsQuantity; i++) //Идёт запись координат в вектор и set-ы
    {
        inputFile >>
            temp.topLeftCorner.x >>
            temp.topLeftCorner.y >>
            temp.bottomRightCorner.x >>
            temp.bottomRightCorner.y;

        vectorOfPositions.push_back(temp);

        setOfAllPositionsX.insert(temp.topLeftCorner.x);
        setOfAllPositionsX.insert(temp.bottomRightCorner.x);
                           
        setOfAllPositionsY.insert(temp.topLeftCorner.y);
        setOfAllPositionsY.insert(temp.bottomRightCorner.y);
    }

    inputFile.close();

    std::vector<long long> vectorOfNewAreas;
    std::vector<BuildingPosition> vectorOfNewPositions;
    vectorOfNewAreas.push_back(0);
    vectorOfNewPositions.push_back({ {0, 0}, {0, 0} });

    std::set<int>::iterator topLeftX = setOfAllPositionsX.begin();
    std::set<int>::iterator iterXEnd = setOfAllPositionsX.end();

    --iterXEnd; //set сортирует по возрастанию, последнее значение x всегда максимальное, нет смысла его проверять

    for (topLeftX; topLeftX != iterXEnd; ++topLeftX)
    {
        std::set<int>::iterator topLeftY = setOfAllPositionsY.begin();
        std::set<int>::iterator iterYEnd = setOfAllPositionsY.end();

        --iterYEnd; //По аналогии с iterXEnd

        for (topLeftY; topLeftY != iterYEnd; ++topLeftY)
        {

            if (IsPointViable(vectorOfPositions, *topLeftX, *topLeftY)) //Если точка не внутри постройки, подбираем вторую точку
            {
                std::set<int>::iterator bottomRightX = topLeftX;

                ++bottomRightX; //Можно не проверять значения x меньше тех, что имеет левый верхний угол (И равные им тоже)

                for (bottomRightX; bottomRightX != setOfAllPositionsX.end(); ++bottomRightX)
                {
                    std::set<int>::iterator bottomRightY = topLeftY;

                    ++bottomRightY; //По аналогии с bottomRightX

                    for (bottomRightY; bottomRightY != setOfAllPositionsY.end(); ++bottomRightY)
                    {
                        BuildingPosition possibleAreaPosition = { {*topLeftX, *topLeftY}, {*bottomRightX, *bottomRightY} };
                        std::vector<BuildingPosition>::iterator buildingCoordinates = vectorOfPositions.begin();

                        bool isPositionCorrect = true;

                        for (buildingCoordinates; buildingCoordinates != vectorOfPositions.end(); ++buildingCoordinates)
                        {
                            if (IsCollisionPresent(*buildingCoordinates, possibleAreaPosition))
                                isPositionCorrect = false;
                        }

                        if (isPositionCorrect)
                        {
                            long long newArea = static_cast<long long>(*bottomRightX - *topLeftX) * static_cast<long long>(*bottomRightY - *topLeftY);
                            BuildingPosition newAreaPosition = { {*topLeftX, *topLeftY}, {*bottomRightX, *bottomRightY} };

                            vectorOfNewAreas.push_back(newArea);
                            vectorOfNewPositions.push_back(newAreaPosition);
                        }
                    }
                }
            }
        }
    }

    //Результаты
    long long maxSumOfAreas = 0;
    int maxAreaIndexI = 0;
    int maxAreaIndexJ = 0;

    for (int i = 0; i < vectorOfNewAreas.size(); i++)
    {
        for (int j = 0; j < vectorOfNewAreas.size(); j++)
        {
            if (i != j)
            {
                long long newSumOfAreas = vectorOfNewAreas[i] + vectorOfNewAreas[j];

                if (newSumOfAreas >= maxSumOfAreas)
                {
                    if (!IsCollisionPresent(vectorOfNewPositions[i], vectorOfNewPositions[j]))
                    {
                        maxSumOfAreas = newSumOfAreas;
                        maxAreaIndexI = i;
                        maxAreaIndexJ = j;
                    }
                }
            }
        }
    }

    std::vector<BuildingPosition> allNewPositions;
    allNewPositions.push_back(vectorOfNewPositions[maxAreaIndexI]);
    allNewPositions.push_back(vectorOfNewPositions[maxAreaIndexJ]);

    std::ofstream outputFile;

    outputFile.open(OUTPUT_FILE_NAME);
    if (outputFile.fail())
    {
        std::cout << "File opening error" << std::endl;
        return 0;
    }

    outputFile << maxSumOfAreas << std::endl;
    for (auto& it : allNewPositions)
    {
        outputFile <<
            it.topLeftCorner.x << " " <<
            it.topLeftCorner.y << " " <<
            it.bottomRightCorner.x << " " <<
            it.bottomRightCorner.y << std::endl;
    }

    outputFile.close();

    std::cout << "runtime = " << clock() / 1000.0 << std::endl;

    return 0;
}
