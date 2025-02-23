#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H
#include <string>

class TaskManager {
public:
    static void task1(const std::string& filename);
    static void task2(const std::string& filename);
    static void fillBinaryFile(const std::string& filename);

    struct Toy {
        char name[50];
        double price;
        int ageMin;
        int ageMax;
    };
    static void fillToyFile(const std::string& filename);
    static void task3(const std::string& filename);

    // Задание 4
    static void fillTextFileWithSingleNumbers(const std::string& filename);
    static void task4(const std::string& filename);

    // Задание 5
    static void fillTextFileWithMultipleNumbers(const std::string& filename);
    static void task5(const std::string& filename);

    // Задание 6
    static void task6(const std::string& inputFilename, const std::string& outputFilename);

    // безопасный инпут
    static int safeinputnumber(const std::string& prompt);
};

#endif // TASK_MANAGER_H
