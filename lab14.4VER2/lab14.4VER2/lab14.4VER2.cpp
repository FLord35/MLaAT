//14.4
//Казино в день своего юбилея решило сделать подарок клиентам.Составляется список клиентов
//в порядке их прихода.Каждый клиент имеет общий баланс игры, выраженный положительным
//или отрицательным целым числом.Казино устраивает общий фуршет, затраты на который
//устанавливаются следующим образом.По списку клиентов формируется соответствующий список
//балансов.Значения двух соседних элементов списка заменяются разностью предыдущего и
//последующего элементов до тех пор, пока не останется единственное число, определяющее
//величину затрат на фуршет.Найти такую последовательность операций, чтобы оставшееся число
//было максимальным.Определить этот максимум.

//Баранов Антон Сергеевич ПС-23, Visual Studio 2022

//Источники:
//https://neerc.ifmo.ru/wiki/index.php?title=%D0%97%D0%B0%D0%B4%D0%B0%D1%87%D0%B0_%D0%BE_%D1%80%D0%B0%D1%81%D1%81%D1%82%D0%B0%D0%BD%D0%BE%D0%B2%D0%BA%D0%B5_%D0%B7%D0%BD%D0%B0%D0%BA%D0%BE%D0%B2_%D0%B2_%D0%B2%D1%8B%D1%80%D0%B0%D0%B6%D0%B5%D0%BD%D0%B8%D0%B8
//https://fvn2009.narod.ru/Olympiads/Rules_Olympiads/Rules22.htm

#include <iostream>
#include <fstream>
#include <vector>
#include <ctime>

const std::string INPUT_FILE_NAME = "input15.txt";
const std::string OUTPUT_FILE_NAME = "output.txt";

int main()
{
    std::ifstream inputFile;

    inputFile.open(INPUT_FILE_NAME);
    if (inputFile.fail())
    {
        std::cout << "File opening error" << std::endl;
        return 0;
    }

    int numbersQuantity;

    inputFile >> numbersQuantity;

    std::vector<int> vectorOfNumbers;
    std::vector<bool> vectorOfOperations; //true = +, false = - ;
    std::vector<int> vectorOfActionNumbers;

    int temp;

    //Да, очень некрасиво выходит. Не хочу исправлять
    inputFile >> temp;
    vectorOfNumbers.push_back(temp);
    inputFile >> temp;
    vectorOfNumbers.push_back(temp);
    vectorOfOperations.push_back(false);

    for (int i = 2; i < numbersQuantity; i++) //Перед положительными числами расставляем плюсы, перед отрицательными - минусы
    {
        inputFile >> temp;
        vectorOfNumbers.push_back(temp);
        if (temp < 0)
        {
            vectorOfOperations.push_back(false);
        }
        else
        {
            vectorOfOperations.push_back(true);
        }
    }

    int actionCounter = 0;

    for (int i = 0; i < vectorOfOperations.size(); i++) //Ищем '+' в выражении, выставляем им первые действия
    {
        if (vectorOfOperations[i]) //Встретили знак '+'
        {
            vectorOfActionNumbers.push_back(i + 1 - actionCounter);
            actionCounter++;
        }
    }

    for (int i = 0; i < vectorOfOperations.size() - actionCounter; i++) //Оставшиеся действия - это первые по списку операции
    {
        vectorOfActionNumbers.push_back(1);
    }

    long long maxSum = vectorOfNumbers[0];

    for (int i = 0; i < vectorOfOperations.size(); i++) //Здесь вычисляем максимальное оставшееся число
    {
        if (vectorOfOperations[i])
        {
            maxSum = maxSum + vectorOfNumbers[i + 1];
        }
        else
        {
            maxSum = maxSum - vectorOfNumbers[i + 1];
        }
    }

    std::ofstream outputFile;

    outputFile.open(OUTPUT_FILE_NAME);
    if (outputFile.fail())
    {
        std::cout << "File opening error" << std::endl;
        return 0;
    }

    outputFile << maxSum << std::endl;

    for (int i = 0; i < vectorOfActionNumbers.size(); i++)
    {
        outputFile << vectorOfActionNumbers[i] << " ";
    }

    std::cout << "runtime = " << clock() / 1000.0 << std::endl;
}
