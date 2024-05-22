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

const std::string INPUT_FILE_NAME = "input.txt";
const std::string OUTPUT_FILE_NAME = "output.txt";

struct Cell
{
    long long signlessBiggestResult; //Максимумы будут храниться выше главной диагонали, минимумы - ниже
    bool operation; //true = +, false = -
    int delimeter; //Индекс числа, после которого выполняется операция
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

    int numbersQuantity;

    inputFile >> numbersQuantity;

    std::vector<std::vector<Cell>> vectorOfAnswers;

    vectorOfAnswers.resize(numbersQuantity, std::vector<Cell>(numbersQuantity));

    int temp;

    for (int i = 0; i < numbersQuantity; i++)
    {
        inputFile >> temp;
        vectorOfAnswers[i][i].signlessBiggestResult = temp;
    }

    long long maxResult = LLONG_MIN;
    long long minResult = LLONG_MAX;
    long long maxResultContestant1 = LLONG_MIN;
    long long maxResultContestant2 = LLONG_MIN;
    long long minResultContestant1 = LLONG_MAX;
    long long minResultContestant2 = LLONG_MAX;
    long long maxResultFinalist = LLONG_MIN;
    long long minResultFinalist = LLONG_MAX;
    bool maxResultFinalistOperation = false; //true = +, false = -
    bool minResultFinalistOperation = false; //true = +, false = -

    for (int i = numbersQuantity - 2; i > -1 ; i--)
    {
        for (int j = i + 1; j < numbersQuantity; j++)
        {
            maxResult = LLONG_MIN;
            minResult = LLONG_MAX;

            for (int k = i; k < j; k++)
            {
                if (i == 0 && i == k) //После первого числа не может стоять знак +
                {
                    maxResultContestant1 = LLONG_MIN;
                    minResultContestant1 = LLONG_MAX;
                }
                else
                {
                    maxResultContestant1 = vectorOfAnswers[k][i].signlessBiggestResult + vectorOfAnswers[j][k + 1].signlessBiggestResult;
                    minResultContestant1 = vectorOfAnswers[i][k].signlessBiggestResult + vectorOfAnswers[k + 1][j].signlessBiggestResult;
                }
               
                maxResultContestant2 = vectorOfAnswers[k][i].signlessBiggestResult - vectorOfAnswers[k + 1][j].signlessBiggestResult;
                minResultContestant2 = vectorOfAnswers[i][k].signlessBiggestResult - vectorOfAnswers[j][k + 1].signlessBiggestResult;

                if (maxResultContestant1 > maxResultContestant2)
                {
                    maxResultFinalist = maxResultContestant1;
                    maxResultFinalistOperation = true;
                }
                else
                {
                    maxResultFinalist = maxResultContestant2;
                    maxResultFinalistOperation = false;
                }

                if (minResultContestant1 < minResultContestant2)
                {
                    minResultFinalist = minResultContestant1;
                    minResultFinalistOperation = true;
                }
                else
                {
                    minResultFinalist = minResultContestant2;
                    minResultFinalistOperation = false;
                }

                if (maxResult < maxResultFinalist)
                {
                    maxResult = maxResultFinalist;
                    vectorOfAnswers[j][i].delimeter = k;
                    vectorOfAnswers[j][i].operation = maxResultFinalistOperation;
                }

                if (minResult > minResultFinalist)
                {
                    minResult = minResultFinalist;
                    vectorOfAnswers[i][j].delimeter = k;
                    vectorOfAnswers[i][j].operation = minResultFinalistOperation;
                }
            }

            vectorOfAnswers[j][i].signlessBiggestResult = maxResult;
            vectorOfAnswers[i][j].signlessBiggestResult = minResult;
        }
    }

    std::cout << vectorOfAnswers[numbersQuantity - 1][0].signlessBiggestResult << std::endl;

    std::cout << "runtime = " << clock() / 1000.0 << std::endl;
}

