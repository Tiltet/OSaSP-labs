#include <stdio.h>
#include <stdlib.h> 
#include <stdint.h> 
#include <unistd.h>

#define JULIAN_DAY_START 15020.0        // Начальная дата в модифицированном юлианском дне (1900.01.01)

struct index_s {
    double time_mark; // временная метка
    uint64_t recno; // номер записи
};

// Функция для генерации случайного числа в заданном диапазоне
double random_double(double min, double max) {
    return min + ((double)rand() / RAND_MAX) * (max - min); // генерация случайного числа с плавающей точкой
}

// Функция для создания случайной временной метки
double generate_time_mark(double max_julian_date) {
    double integerDayPart = JULIAN_DAY_START + rand() % ((int)max_julian_date - (int)JULIAN_DAY_START); // генерация целой части дня
    double fractional_day = random_double(0.0, 0.999999); // генерация дробной части дня
    return integerDayPart + fractional_day; // возвращение временной метки
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "\033[31mИспользование с параметрами: %s <amountOfRecords> <filename>\n\033[0m", argv[0]); // вывод сообщения об использовании программы
        return EXIT_FAILURE;
    }

    size_t amountOfRecords = atoi(argv[1]); // получение количества записей из аргументов командной строки
    // выравнивание
    amountOfRecords = ((amountOfRecords + 255) / 256) * 256; // выравнивание количества записей
    char *filename = argv[2]; // получение имени файла из аргументов командной строки

    // Открываем файл для записи
    FILE *file = fopen(filename, "wb"); // открытие файла для записи в двоичном режиме
    if (!file) {
        perror("Error opening file"); // вывод сообщения об ошибке при открытии файла
        return EXIT_FAILURE;
    }

    // Генерируем и записываем индексные записи
    srand(getpid()); // инициализация генератора случайных чисел
    for (size_t i = 0; i < amountOfRecords; i++) {
        struct index_s record = {
                .time_mark = generate_time_mark(60435), // генерация временной метки
                .recno = i + 1 // первичный индекс начинается с 1
        };
        printf("\n%.2ld\t%lf\n", record.recno, record.time_mark); // вывод номера записи и временной метки
        fwrite(&record, sizeof(struct index_s), 1, file); // запись индексной записи в файл
    }

    // Закрываем файл
    fclose(file); // закрытие файла

    printf("Файл с %zu записями был сгенерирован успешно: %s\n", amountOfRecords, filename); // вывод сообщения об успешной генерации файла индекса

    return EXIT_SUCCESS;
}
