//13.5
//Заданы четыре слова, в каждом из которых нет повторяющихся букв. Требуется составить
//минимальный по количеству клеток прямоугольный кроссворд, в котором два первых слова
//расположены горизонтально, и первое выше второго, а два последних вертикально, и третье левее
//четвертого.Каждое горизонтальное слово должно пересекаться с обоими вертикальными словами.

//Баранов Антон Сергеевич ПС-23, Visual Studio 2022

//Источники:

#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

const std::string INPUT_FILE_NAME = "input.txt";
const std::string OUTPUT_FILE_NAME = "output.txt";

struct Words
{
    std::string horizontalFirst;
    std::string horizontalSecond;
    std::string verticalFirst;
    std::string verticalSecond;
};

int main()
{
    std::ifstream inputFile;

    inputFile.open(INPUT_FILE_NAME);
    if (inputFile.fail())
    {
        std::cout << "File opening error" << std::endl;
        return 0;
    }

    Words words;

    inputFile >> words.horizontalFirst;
    inputFile >> words.horizontalSecond;
    inputFile >> words.verticalFirst;
    inputFile >> words.verticalSecond;

    for (int i = 3; i <= std::min(words.verticalFirst.length(), words.verticalSecond.length()); i++) //Проходим по вертикальному расстоянию между первыми двумя словами
    {
        for (int j = 3; j <= (words.horizontalFirst.length() + words.horizontalSecond.length() - 3); j++) //Проходим по сдвигу первых двух слов относительно друг друга
        {
            
        }
    }

    std::ofstream outputFile;

    outputFile.open(OUTPUT_FILE_NAME);
    if (outputFile.fail())
    {
        std::cout << "File opening error" << std::endl;
        return 0;
    }

    std::cout << "runtime = " << clock() / 1000.0 << std::endl;
}
