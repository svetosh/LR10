#include <iostream>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

const std::string INFO = "Комманды для использования:\n"
                          "exit - закончить работу программы\n"
    "show - вывод на экран текщуго каталога\n"
    "what - вывод на экран содержимое каталога\n"
    "create - создание папки\n"
    "size - вывод на экран размер файла\n"
    "copy - копироваание файла\n"
    "deleteF - удаление файла\n"
    "deleteD - удаление католога с файлами\n"
    "up - перемещение по каталогам вверх\n"
    "down - перемещение по каталогам вниз\n"
    "renameF - переименовать файл\n"
    "renameD - переименовать каталог\n"
    "move - переместить файл\n";

int main(int argc, char* argv[])
{
    setlocale(LC_ALL, "ru");
    std::string comand, fileName, directoryName;
    fs::path cur_path, copy_to_path, new_path;
    std::cout << INFO;
    std::getline(std::cin, comand);
    while (comand != "exit")
    {
        if (comand == "show")
        {
            std::cout << fs::current_path() << std::endl;
        }
        else if (comand == "what")
        {
            for (auto& p : fs::directory_iterator(fs::current_path()))
            {
                cur_path = p.path();
                std::cout << cur_path.filename() << std::endl;
            }
        }
        else if (comand == "create")
        {
            std::string newDirectory;
            std::cout << "Введите название папки: " << std::endl;
            std::getline(std::cin, newDirectory);
            cur_path = fs::current_path();
            cur_path /= newDirectory;
            if (!(fs::exists(cur_path))) fs::create_directory(newDirectory);
        }
        else if (comand == "size")
        {
            std::cout << "Введите название файл, размер которого васм инетересует: " << std::endl;
            std::getline(std::cin, fileName);
            cur_path = fs::current_path() / fileName;
            if (fs::exists(cur_path)) std::cout << fs::file_size(cur_path) << std::endl;
        }
        else if (comand == "copy")
        {
            std::string copy;
            std::cout << "Введите файл, который будем копировать: " << std::endl;
            std::getline(std::cin, fileName);
            cur_path = fs::current_path() / fileName;
            copy_to_path = fs::current_path();
            std::cout << "Введите название нового файла: " << std::endl;
            std::getline(std::cin, copy);
            copy_to_path /= copy;
            fs::copy_file(cur_path, copy_to_path);
        }
        else if (comand == "deleteF")
        {
            std::cout << "Введите файл, который удалим: " << std::endl;
            std::getline(std::cin, fileName);
            cur_path = fs::current_path() / fileName;
            fs::remove(cur_path);
        }
        else if (comand == "deleteD")
        {
            std::string deletD;
            std::cout << "Введите каталога, который удалим: " << std::endl;
            std::getline(std::cin, deletD);
            cur_path = fs::current_path() / deletD;
            fs::remove_all(cur_path);
        }
        else if (comand == "up")
        {
            std::string up;
            std::getline(std::cin, up);
            cur_path = fs::current_path() / up;
            fs::create_directory(up);
            fs::current_path(cur_path);
            std::cout << fs::current_path() << std::endl;
        }
        else if (comand == "down")
        {
            cur_path = fs::current_path().remove_filename();
            fs::current_path(cur_path);
            std::cout << fs::current_path() << std::endl;
        }
        else if (comand == "renameF")
        {
            std::string renameFile;
            std::cout << "Введите название файл, который будем переименовывать: " << std::endl;
            std::getline(std::cin, fileName);
            std::cout << "Введите название: " << std::endl;
            std::getline(std::cin, renameFile);
            cur_path = fs::current_path() / fileName;
            new_path = fs::current_path() / renameFile;
            fs::rename(cur_path, new_path);
        }
        else if (comand == "renameD")
        {
            std::string renameDirectory;
            std::cout << "Введите название каталога, который будем переименовывать: " << std::endl;
            std::getline(std::cin, directoryName);
            std::cout << "Введите название: " << std::endl;
            std::getline(std::cin, renameDirectory);
            cur_path = fs::current_path() / directoryName;
            new_path = fs::current_path() / renameDirectory;
            fs::rename(cur_path, new_path);
        }
        else if (comand == "move")
        {
            cur_path = fs::current_path();
            std::cout << "Введите название файла, который будем перемещать: " << std::endl;
            std::getline(std::cin, fileName);
            std::cout << "Куда? " << std::endl;
            std::getline(std::cin, directoryName);
            cur_path /= fileName;
            new_path = fs::current_path();
            new_path /= directoryName;
            new_path /= fileName;
            fs::rename(cur_path, new_path);
        }
        std::cout << "Вы ввели некорректную комманду, будьте аккуратней и повторите попытку: " << std::endl;
        std::getline(std::cin, comand);
    }
    return 1;
}
