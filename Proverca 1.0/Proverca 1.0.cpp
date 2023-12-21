#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
#include <stdio.h>
#include <string>
#include <windows.h>

using namespace std;

int main()
{
    vector <string> m1 = { "C", "+", "+" };
    vector <string> m2 = { "C", "+", "+" };
    string file_name = "parasha.txt";
    const char* file_name_const = file_name.c_str();
    for (int i = 0; i < m1.size();i++) {

        FILE* pipe = popen(file_name_const, "w+");
        if (!pipe) {
            cerr << "Неправильно введена ссылка на файл" << endl;
            break;
        }
        // Ждем, пока чужая программа будет готова принимать ввод
        while (1) {
            char c;
            fscanf(pipe, "%c", &c);
            if (c == '@') {
                break;
            }
        }

        //Вводит нужное значение
        const char* vvod = (m1[i]+"\n").c_str();
        fprintf(pipe, (m1[i] + "\n").c_str());

        //
        const long long bufferSize = 5000000;
        char buffer[bufferSize];

        // Считываем символы до первого символа "@"
        while (fgets(buffer, bufferSize, pipe) != nullptr) {
            if (strstr(buffer, "@") != nullptr) {
                break;
            }
        }

        // Считываем символы между "@" и сохраняем их в строку
        string result = "";
        while (fgets(buffer, bufferSize, pipe) != nullptr) {
            if (strstr(buffer, "@") != nullptr) {
                break;
            }
            result += buffer;
        }

        // Убираем завершающий символ новой строки
        result.erase(result.length() - 1);

        std::cout << "Считанная строка: " << result << std::endl;

        pclose(pipe);


    }
}
