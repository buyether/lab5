#include <iostream>
#include "TaskManager.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "ru_RU");
    while (true) {
        try {
            cout << "\nВыберите задание:" << endl;
            cout << "1. Разность между max и min элементами в файле" << endl;
            cout << "2. Копирование элементов в матрицу n x n" << endl;
            cout << "3. Найти дорогие игрушки" << endl;
            cout << "4. Подсчитать количество вхождений максимального элемента" << endl;
            cout << "5. Подсчитать количество чётных элементов" << endl;
            cout << "6. Переписать строки с заданной комбинацией символов\n" << endl;
            cout << "* - * Генерация файлов * - *\n" << endl;
            cout << "7. Сгенерировать файл с данными для 1 и 2 задания" << endl;
            cout << "8. Сгенерировать файл с игрушками для 3 задания" << endl;
            cout << "9. Сгенерировать файл с целыми числами для 4 задания" << endl;
            cout << "10. Сгенерировать файл с целыми числами для 5 задания" << endl;
            cout << "0. Выход" << endl;

            int choice = TaskManager::safeinputnumber("\nВведите опцию: ");

            // файлы
            string filename12 = "D:/Учеба/Япы/лаба5/data12.bin";
            string filename3 = "D:/Учеба/Япы/лаба5/data3.bin";
            string filename4 = "D:/Учеба/Япы/лаба5/data4.txt";
            string filename5 = "D:/Учеба/Япы/лаба5/data5.txt";
            string filename6 = "D:/Учеба/Япы/лаба5/data6.txt";
            string filename6_output = "D:/Учеба/Япы/лаба5/data6_output.txt";

            // интерфейс выбора
            switch (choice) {
            case 0: {
                return 0;
            }
            case 1: {
                TaskManager::task1(filename12);
                break;
            }
            case 2: {
                TaskManager::task2(filename12);
                break;
            }
            case 3: {
                TaskManager::task3(filename3);
                break;
            }
            case 4: {
                TaskManager::task4(filename4);
                break;
            }
            case 5: {
                TaskManager::task5(filename5);
                break;
            }
            case 6: {
                TaskManager::task6(filename6, filename6_output);
                break;
            }
            case 7: {
                TaskManager::fillBinaryFile(filename12);
                break;

            }
            case 8: {
                TaskManager::fillToyFile(filename3);
                break;
            }
            case 9: {
                TaskManager::fillTextFileWithSingleNumbers(filename4);
                break;
            }
            case 10: {
                TaskManager::fillTextFileWithMultipleNumbers(filename5);
                break;
            }
            default:
                cout << "Ошибка: Неверный номер задания." << endl;
                break;
            }
        }
        catch (const exception& e) {
            cerr << "Ошибка: " << e.what() << endl;
        }
    }
    return 0;
}
