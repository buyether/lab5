#include "TaskManager.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <stdexcept>
#include <algorithm> // Для max_element и min_element
#include <limits>    // Для numeric_limits

using namespace std;

// задание 1: Разность между max и min элементами
// задание 1: Разность между max и min элементами
void TaskManager::task1(const string& filename) {
    ifstream inFile(filename, ios::binary); // открываем файл в бинарном режиме
    if (!inFile) { // если файл не открылся, выбрасываем исключение
        throw runtime_error("Ошибка при открытии файла для чтения.");
    }

    vector<int> numbers; // создаём вектор для хранения чисел из файла
    int value;
    while (inFile.read(reinterpret_cast<char*>(&value), sizeof(value))) {
        // читаем данные из файла блоками по размеру int и добавляем их в вектор
        numbers.push_back(value);
    }

    if (numbers.empty()) { // если вектор пустой, значит файл был пустым
        throw runtime_error("Файл пуст.");
    }

    cout << "Прочитанные данные из файла: ";
    for (int num : numbers) { // выводим все числа, которые были прочитаны из файла
        cout << num << " ";
    }
    cout << endl;

    int maxElement = *max_element(numbers.begin(), numbers.end()); // находим максимальный элемент в векторе
    int minElement = *min_element(numbers.begin(), numbers.end()); // находим минимальный элемент в векторе
    cout << "Максимальный элемент: " << maxElement
        << ", минимальный: " << minElement
        << ", разница между ними: " << maxElement - minElement << endl;
    // выводим максимальный, минимальный элементы и их разницу

    inFile.close(); // закрываем файл после чтения
}



// задание 2: Копирование элементов в матрицу n x n
void TaskManager::task2(const string& filename) {
    int n;
    cout << "Введите размер матрицы (n): ";
    cin >> n;

    if (cin.fail() || n <= 0) {
        throw invalid_argument("Некорректный ввод. Размер матрицы должен быть положительным числом.");
    }
    else if (n > 20) {
        throw invalid_argument("Слишком большое число. Максимальный размер матрицы — 20.");
    }

    ifstream inFile(filename, ios::binary); // открываем файл в бинарном режиме
    if (!inFile) {
        throw runtime_error("Ошибка при открытии файла для чтения.");
    }

    vector<int> numbers;

    int value;
    while (inFile.read(reinterpret_cast<char*>(&value), sizeof(value))) {
        numbers.push_back(value); // читаем числа из файла и добавляем их в вектор
    }

    inFile.close(); // закрываем файл после чтения

    cout << "Прочитанные данные из файла: ";
    for (int num : numbers) {
        cout << num << " "; // выводим все числа, считанные из файла
    }
    cout << endl;

    vector<vector<int>> matrix(n, vector<int>(n, 0)); // создаём квадратную матрицу n x n, заполненную нулями
    size_t elementsToCopy = min(static_cast<size_t>(n * n), numbers.size()); // определяем, сколько элементов можно скопировать в матрицу

    for (size_t i = 0; i < elementsToCopy; ++i) {
        matrix[i / n][i % n] = numbers[i]; // заполняем матрицу элементами из вектора
        // i / n - номер строки, i % n - номер столбца
    }

    cout << "Исходная матрица:" << endl;
    for (const auto& row : matrix) {
        for (int elem : row) {
            cout << elem << " "; // выводим элементы матрицы построчно
        }
        cout << endl;
    }

    // найти максимальный элемент только в матрице
    int maxElement = INT_MIN; // начинаем с минимального значения int
    for (const auto& row : matrix) {
        for (int elem : row) {
            if (elem > maxElement) { // обновляем максимальный элемент, если нашли больший
                maxElement = elem;
            }
        }
    }

    cout << "Максимальный элемент в матрице: " << maxElement << endl;

    // заменить все вхождения максимального элемента на 0
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (matrix[i][j] == maxElement) { // если элемент равен максимальному, заменяем его на 0
                matrix[i][j] = 0;
            }
        }
    }

    cout << "Матрица после обработки:" << endl;
    for (const auto& row : matrix) {
        for (int elem : row) {
            cout << elem << " "; // выводим обработанную матрицу построчно
        }
        cout << endl;
    }
}

// задание 3
void TaskManager::task3(const string& filename) {
    ifstream inFile(filename, ios::binary);
    if (!inFile) {
        throw runtime_error("Ошибка при открытии файла для чтения.");
    }

    vector<Toy> toys;
    Toy toy;

    while (inFile.read(reinterpret_cast<char*>(&toy), sizeof(toy))) {
        toys.push_back(toy);
    }

    if (toys.empty()) {
        throw runtime_error("Файл пуст.");
    }

    cout << "Все игрушки в файле:" << endl;
    for (const auto& t : toys) {
        cout << "Название: " << t.name
            << ", Цена: " << t.price
            << ", Возраст: " << t.ageMin << "-" << t.ageMax << endl;
    }


    // поиск максимальной цены
    Toy maxPriceToy;
    double maxPrice = -1;
    for (const auto& t : toys) {
        if (t.price > maxPrice) {
            maxPrice = t.price;
            maxPriceToy = t;
        }
    }

    cout << "Максимальная цена: " << maxPrice << " у игрушки " << maxPriceToy.name << endl;

    double k;
    cout << "Введите значение k (разница в цене): ";
    cin >> k;

    if (cin.fail() || k < 0) {
        throw invalid_argument("Некорректный ввод. Значение k должно быть неотрицательным.");
    }


    // вывод игрушек, соответствующих условию
    cout << "Игрушки с ценой не более чем на " << k << " рублей меньше максимальной цены:" << endl;
    for (const auto& t : toys) {
        if (maxPrice - t.price <= k) {
            cout << t.name << " (Цена: " << t.price << ", Возраст: "
                << t.ageMin << "-" << t.ageMax << ")" << endl;
        }
    }

    inFile.close();
}

void TaskManager::task4(const string& filename) {
    ifstream inFile(filename); // открываем файл в текстовом режиме
    if (!inFile) {
        throw runtime_error("Ошибка при открытии файла для чтения."); // если файл не открылся, выбрасываем исключение
    }

    vector<int> numbers; // создаём вектор для хранения чисел из файла
    int value;
    while (inFile >> value) { // считываем числа из файла до конца
        numbers.push_back(value); // добавляем каждое число в вектор
    }

    if (numbers.empty()) { // проверяем, что файл не пуст
        throw runtime_error("Файл пуст.");
    }

    int maxElement = *max_element(numbers.begin(), numbers.end()); // находим максимальный элемент в векторе
    int count = count_if(numbers.begin(), numbers.end(), [maxElement](int x) { return x == maxElement; });
    // считаем, сколько раз максимальный элемент встречается в векторе с помощью лямбда-функции

    cout << "Максимальный элемент: " << maxElement << endl;
    cout << "Количество вхождений максимального элемента: " << count << endl;

    inFile.close(); // закрываем файл после работы
}

void TaskManager::task5(const string& filename) {
    ifstream inFile(filename); // открываем файл в текстовом режиме
    if (!inFile) {
        throw runtime_error("Ошибка при открытии файла для чтения."); // если файл не открылся, выбрасываем исключение
    }

    int evenCount = 0; // счётчик чётных чисел
    int value;

    while (inFile >> value) { // считываем числа из файла до конца
        if (value % 2 == 0) { // проверяем, является ли число чётным
            ++evenCount; // увеличиваем счётчик, если число чётное
        }
    }

    cout << "Количество чётных элементов: " << evenCount << endl;

    inFile.close(); // закрываем файл после работы
}


void TaskManager::task6(const string& inputFilename, const string& outputFilename) {
    // проверяем существование входного файла
    ifstream inFile(inputFilename);
    if (!inFile) {
        // если файл не существует, создаём его с тестовой фразой
        ofstream testFile(inputFilename);
        if (!testFile) {
            throw runtime_error("Не удалось создать входной файл.");
        }
        testFile << "This is a test string for verification.\n";
        testFile << "Just a random piece of text.\n";
        testFile << "Patterns are everywhere if you look closely.\n";
        testFile << "Test cases are important for debugging\n";
        testFile.close();
        cout << "Файл \"" << inputFilename << "\" не найден. Создан новый файл с тестовыми данными." << endl;
    }
    else {
        inFile.close(); // закрываем файл, если он существует
    }

    // запрашиваем комбинацию символов для поиска
    string pattern;
    cout << "Введите комбинацию символов для поиска: ";
    getline(cin, pattern);

    if (pattern.empty()) {
        throw invalid_argument("Комбинация символов не может быть пустой.");
    }

    // открываем файлы для чтения и записи
    inFile.open(inputFilename);
    ofstream outFile(outputFilename);

    if (!inFile || !outFile) {
        throw runtime_error("Ошибка при открытии файлов.");
    }

    string line;
    bool found = false; // флаг для проверки наличия совпадений

    while (getline(inFile, line)) {
        // поиск подстроки в строке
        if (line.find(pattern) != string::npos) { // проверяем наличие подстроки
            outFile << line << endl;
            found = true;
        }
    }

    if (found) {
        cout << "Строки с комбинацией \"" << pattern
            << "\" успешно записаны в файл \"" << outputFilename << "\"." << endl;
    }
    else {
        cout << "Комбинация \"" << pattern
            << "\" не найдена в файле \""
            << inputFilename << "\"." << endl;
    }

    inFile.close();
    outFile.close();

    cout << "Задание выполнено." << endl;
}

// * - *            РАБОТА С ФАЙЛАМИ            * - * \\

void TaskManager::fillBinaryFile(const string& filename) {
    int numElements = safeinputnumber("\nВведите количество данных для генерации: ");

    if (cin.fail() || numElements > 20) {
        throw invalid_argument("Слишком большое число");
    }

    if (numElements > 0) {
        ofstream outFile(filename, ios::binary);
        if (!outFile) {
            throw runtime_error("Ошибка при открытии файла для записи.");
        }

        srand(static_cast<unsigned>(time(0)));

        cout << "Сгенерированные данные для записи в файл: ";

        for (int i = 0; i < numElements; ++i) {
            int value = rand() % 101; // Случайное число от 0 до 100
            cout << value << " "; // выводим сгенерированное значение
            outFile.write(reinterpret_cast<const char*>(&value), sizeof(value));
        }

        cout << endl;

        outFile.close();

        cout << "Файл с данными успешно заполнен." << endl;
    }

}

void TaskManager::fillTextFileWithMultipleNumbers(const string& filename) {
    int numLines = safeinputnumber("Введите количество строк для генерации: ");
    int numbersPerLine = safeinputnumber(" Введите количество чисел в строке: ");

    if (numLines > 0 && numbersPerLine > 0) {
        ofstream outFile(filename);
        if (!outFile) {
            throw runtime_error("Ошибка при открытии файла для записи.");
        }

        srand(static_cast<unsigned>(time(0)));
        for (int i = 0; i < numLines; ++i) {
            for (int j = 0; j < numbersPerLine; ++j) {
                outFile << rand() % 101 << " "; // случайные числа от 0 до 100
            }
            outFile << endl;
        }

        outFile.close();
    }
}

void TaskManager::fillToyFile(const string& filename) {
    int numToys = safeinputnumber("\nВведите количество игрушек для генерации: ");

    if (numToys > 20) {
        throw invalid_argument("Слишком много данных. Максимум — 20 игрушек.");
    }

    if (numToys > 0) {
        ofstream outFile(filename, ios::binary);
        if (!outFile) {
            throw runtime_error("Ошибка при открытии файла для записи.");
        }

        srand(static_cast<unsigned>(time(0)));

        for (int i = 0; i < numToys; ++i) {
            Toy toy;
            snprintf(toy.name, sizeof(toy.name), "Toy_%d", i + 1); // генерация имени игрушки
            toy.price = rand() % 1000 + 100; // цена от 100 до 1099 рублей
            toy.ageMin = rand() % 12 + 1; // минимальный возраст от 1 до 12 лет
            toy.ageMax = toy.ageMin + rand() % (18 - toy.ageMin); // максимальный возраст

            outFile.write(reinterpret_cast<const char*>(&toy), sizeof(toy));
        }

        outFile.close();
        cout << "Файл с игрушками успешно заполнен." << endl;

        // Считываем и выводим данные из файла
        ifstream inFile(filename, ios::binary);
        if (!inFile) {
            throw runtime_error("Ошибка при открытии файла для чтения.");
        }

        cout << "Сгенерированные данные:" << endl;
        Toy toy;
        while (inFile.read(reinterpret_cast<char*>(&toy), sizeof(toy))) {
            cout << "Название: " << toy.name
                << ", Цена: " << toy.price
                << ", Возраст: " << toy.ageMin << "-" << toy.ageMax << endl;
        }

        inFile.close();
    }
}


void TaskManager::fillTextFileWithSingleNumbers(const string& filename) {
    int numElements = safeinputnumber("\nВведите количество чисел для генерации: ");

    if (cin.fail() || numElements > 500) {
        throw invalid_argument("Слишком большое число");
    }

    if (numElements > 0) {
        ofstream outFile(filename);
        if (!outFile) {
            throw runtime_error("Ошибка при открытии файла для записи.");
        }

        srand(static_cast<unsigned>(time(0)));
        for (int i = 0; i < numElements; ++i) {
            outFile << rand() % 101 << endl; // случайные числа от 0 до 100
        }

        outFile.close();

        cout << "Файл успешно заполнен." << endl;
    }
}


// * - *              ДОПОЛНИТЕЛЬНО             * - * \\

// вспомогательный метод для безопасного ввода числа
int TaskManager::safeinputnumber(const string& prompt) {
    int number;

    while (true) {
        cout << prompt;
        cin >> number;

        if (cin.fail()) { // проверяем наличие ошибок ввода
            cin.clear(); // сбрасываем флаг ошибки
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Очищаем буфер ввода
            cout << "Ошибка: введено некорректное значение. Попробуйте снова." << endl;
        }
        else if (number < 0) { // дополнительная проверка на положительное число
            cout << "Ошибка: число должно быть положительным. Попробуйте снова." << endl;
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // очищаем буфер на случай лишних символов
            return number; // корректный ввод
        }
    }
}
