#include <algorithm>
#include <experimental/filesystem>
#include <fstream>
#include <iostream>
#include <vector>
#include <iterator>

namespace fs = std::experimental::filesystem;

fs::path down(fs::path p) 
{
    return p.parent_path();
}

fs::path up(fs::path p, const std::string s) 
{
    return p / s;
}

int main()
{
    setlocale(LC_ALL, "ru");
    fs::path filepath = fs::current_path();
    std::cout << "Текущий каталог: " << filepath << std::endl;

    std::cout << std::endl;

    std::cout << "Содержимое текущего каталога:" << std::endl;
    for (fs::path p : fs::directory_iterator(filepath)) 
    {
        std::cout << p.filename() << std::endl;
    }

    std::cout << std::endl;

    std::string new_folder = "test_folder";
    if (!(fs::exists(up(filepath, new_folder))))
    {
        fs::create_directory(up(filepath, new_folder));
        std::cout << "Успешно создан каталог test_folder" << std::endl;
    }
    else 
    {
        std::cout << "Каталог test_folder уже существует" << std::endl;
    }

    std::cout << std::endl;
    fs::path new_file = up(filepath, "example");
    if (!(fs::exists(new_file))) 
    {
        std::ofstream(new_file) << "test!";
        std::cout << "Успешно создан файл example" << std::endl;
    }
    std::cout << "Размер файла example: " << fs::file_size(new_file) << std::endl;

    fs::path src = up(filepath, "example");
    fs::path dst = up(filepath, "example1");
    if (!(fs::exists(dst))) 
    {
        fs::copy_file(src, dst);
        std::cout << "Успешно скопировали файл example в файл example1" << std::endl;
    }


    src = up(filepath, "example1");
    dst = up(filepath, "example2");
    fs::copy_file(src, dst);
    fs::remove(dst);
    std::cout << "Успешно удалили созданный файл example2" << std::endl;

    fs::path full_folder = up(filepath, "full_folder");
    if (!(fs::exists(full_folder))) {
        fs::create_directory(full_folder);
    }
    fs::remove_all(full_folder);
    std::cout << "Успешно удалили папку вместе с ее содержимым full_folder" << std::endl;

    std::cout << "Демонстрация перехода в родительскую папку" << std::endl;
    fs::path down_path = filepath;
    std::cout << "Текущий путь: " << down_path << std::endl;
    down_path = down(down_path);
    std::cout << "Новый путь: " << down_path << std::endl;

    std::cout << std::endl;

    fs::rename(up(filepath, "example"), up(filepath, "new_example"));
    std::cout << "Успешно переименовали example в new_example" << std::endl;

    new_folder = "move_folder";
    if (!(fs::exists(up(filepath, new_folder)))) {
        fs::create_directory(up(filepath, new_folder));
    }
    fs::rename(up(filepath, "new_example"), up(up(filepath, new_folder), "new_example"));
    std::cout << "Успешно переместили файл new_example из текущего каталога в каталог move_folder" << std::endl;
}