#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stack>

using namespace std;

void clearFile(std::string path) {
    std::ofstream fout;
    fout.open(path);
    fout << "";
    fout.close();
}

struct Passenger {
    int flight_number;
    std::string fio;
    std::string fio_commander;
    struct Date {
        int number;
        int month;
        int year;
    };
    Date date;
    int numberstr;
};

Passenger::Date parseDate(std::string input) {
    Passenger::Date date{};
    int dots_cnt = 0;
    for (int i = 0; i < input.length(); i++) {
        if (input[i] == '.') {
            dots_cnt++;
            continue;
        }
        else {
            if (dots_cnt == 0) {
                date.number = stoi(input.substr(i, 2));
                i++;
            }
            else if (dots_cnt == 1) {
                date.month = stoi(input.substr(i, 2));
                i++;
            }
            else {
                date.year = stoi(input.substr(i, 4));
                break;
            }
        }
    }
    return date;
};

std::vector<Passenger*> readData(std::string path) {
    setlocale(LC_ALL, "Russian");
    std::ifstream fin;
    std::vector<Passenger*>data;
    fin.open(path);
    int n; fin >> n;
    std::string s, fa, im, ot;
    for (int i = 0; i < n; i++)
    {
        Passenger* person = new Passenger;
        fin >> s;
        person->flight_number = stoi(s.substr(0, 4));
        fin >> fa; fin >> im; fin >> ot;
        person->fio = fa + ' ' + im + ' ' + ot;
        fin >> s;
        person->date = parseDate(s);
        fin >> fa; fin >> im; fin >> ot;
        person->fio_commander = fa + ' ' + im + ' ' + ot;
        person->numberstr = i + 2;
        data.push_back(person);
    }
    fin.close();
    return data;
}

void generateFile(int n, std::string path) {
    std::ofstream fout;
    fout.open(path);
    fout << n << '\n';
    std::string surnames[126] = { "Antonov", "Zinovev", "Kuropatkin", "Matanalizov", "Algoritmov", "Sortirovkov", "Ivanova", "Kulibina", "Liternaya", "Bloha", "Babaj", "Bazar", "Bibik", "Gadyuchka", "Dohlik", "Zhujvoda", "Nepejvoda", "Moska", "Golobev", "Drakula", "Kosheev", "Sova", "Sliva", "Intraligator", "Kisel", "Zazherilo",
    "Aliferov", "Andreev", "Annenkov", "Barbayanov", "Bashinskij", "Bereznickij", "Bessonov", "Bobrovskij", "Bogatev", "Bozhok", "Bondarenko", "Buhalihin", "Van", "Vayaj", "Vinogradov", "Vissarionov", "Vlasov", "Vlasov", "Gandzyuk", "Gerus", "Gogoleva", "Gorbaryov", "Davydov", "Danishimaev", "Di", "Egorova", "Enshin", "Eryomenko",
    "Ermak", "Eroshenko", "Zelenin", "Ivanov", "Karpachyov", "Kasyanenko", "Kiyanov", "Kozachko", "Kolpakova", "Koryaushkin", "Kosenko", "Kosilov", "Kostyuchenko", "Kochetkov", "Kropochev", "Kuzmin", "Kutuzov", "Lagunova", "Lazarev", "Lebedinskij", "Litovchenko", "Lukin", "Makogon", "Mareev", "Martyn", "Matushkin", "Mashkin", "Mihajlov", "Moiseev",
    "Mulyava", "Myznikov", "Nalimov", "Nechepurenko", "Olejnikova", "Osipenko", "Ohlopkov", "Pavlov", "Pak", "Pasko", "Perepechaev", "Podolinskij", "Polovnikov", "Popov", "Procenko", "Pyavka", "Razdobarov", "Rasputnyj", "Seliverstov", "Sivceva", "Sporyshev", "Starcev", "Stoletnij", "Sutugin", "Tarasov", "Tahavov", "Teryohin",
    "Timofeev","Tregubova", "Turovskij", "Tyukova", "Uvarov", "Hegaj", "Hmelevskij", "Hramcova", "Caregorodcev", "Cyplakov", "Chechyotkin", "Shevelyov", "Sheshenya", "Shibanov", "Shmidt", "Yakuba" };
    std::string names[65] = { "Agnes", "Adolf", "Adrian", "Boris", "Valentin", "Vasilij", "Vitalij", "Georgij", "Grigorij", "Daniil", "Denis", "Dmitrij", "Evgenij", "Egor", "Ivan", "Igor", "Konstantin", "Leonid", "Maksim", "Matvej", "Nikita", "Nikolaj", "Oleg", "Pavel", "Pyotr", "Roman", "Ruslan", "Sergej", "Stepan", "Timur", "Fyodor", "Yurij",
        "Yaroslav", "Alisa", "Aleksandra", "Alyona", "Alla", "Anastasiya", "Anzhelika", "Valentina", "Veronika", "Viktoriya", "Galina", "Darya", "Diana", "Elizaveta","Zhanna", "Inna", "Irina", "Karina", "Kristina", "Kseniya", "Margarita", "Mariya", "Milana", "Natalya", "Nika", "Oksana", "Olga", "Ruslana", "Svetlana", "Sofiya", "Sofya", "Tamara", "Zhanna" };
    std::string patronymic[36] = { "Aleksandrovich", "Alekseevich", "Anatolevich", "Arkadevich", "Bogdanovich", "Borisovich", "Valerevich", "Viktorovich", "Vladimirovich", "Volfovich", "Gennadievich", "Grigorevich", "Denisovich", "Evgenevich", "Efimovich", "Ignatevich", "Iosifovich", "Kirillovich", "Lvovich", "Matveevich", "Nikolaevich", "Pavlovich", "Petrovich",
        "Robertovich", "Romanovich","Sanych","Severinovich","Stanislavovich","Tarasovich","Timofeevich","Fedorovich","Filippovich","Eduardovich","Yurevich","Yakovlevich","Yaroslavovich" };
    srand((unsigned)time(NULL));
    for (int i = 0; i < n; i++)
    {
        std::string mon, date;
        int month = rand() % 12 + 1;
        if (month < 10) mon = '0' + std::to_string(month);
        else mon = std::to_string(month);
        int dat = rand() % 31 + 1;
        if (dat < 10) date = '0' + std::to_string(dat);
        else date = std::to_string(dat);
        fout << std::to_string(rand() % 9000 + 1000) + ' ' + surnames[rand() % 126] + ' ' + names[rand() % 65] + ' ' + patronymic[rand() % 36] + ' ' + date + '.' + mon + '.' + std::to_string(rand() % 92 + 1930) + ' ' + surnames[rand() % 126] + ' ' + names[rand() % 65] + ' ' + patronymic[rand() % 36] + '\n';
    }
    fout.close();
}

void writeData(int number, int steps, std::string path) {
    std::ofstream fout;
    fout.open(path, std::ofstream::app);
    if (number + steps) {
        fout << "Ключ находится в " << number << " строке." << '\n';
        fout << "Понадобилось " << steps << " шагов." << '\n' << '\n';
    }
    else {
        fout << "Ключ не найден" << '\n' << '\n';
    }
    fout.close();
}

int compare(Passenger* first, Passenger* second) {
    if (first->flight_number > second->flight_number) return 1;
    if (first->flight_number < second->flight_number) return -1;
    if (first->numberstr > second->numberstr) return 1;
    if (first->numberstr < second->numberstr) return -1;
    return 0;
}

std::pair<int, int> partition(std::vector<Passenger*>& data, int start, int end)
{
    Passenger* pivot = new Passenger;
    Passenger* temp = new Passenger;
    int mid = (start + end) / 2;
    if (compare(data[start], data[mid]) == 1) { temp = data[start]; data[start] = data[mid]; data[mid] = temp; }
    if (compare(data[mid], data[end]) == 1) { temp = data[mid]; data[mid] = data[end]; data[end] = temp; }
    if (compare(data[start], data[mid]) == 1) { temp = data[start]; data[start] = data[mid]; data[mid] = temp; }
    pivot = data[mid];
    int i = start;
    int j = end;
    do {
        while (compare(data[i], pivot) == -1) i++;
        while (compare(data[j], pivot) == 1) j--;
        if (i <= j) {
            temp = data[i];
            data[i] = data[j];
            data[j] = temp;
            i++;
            j--;
        }
    } while (i <= j);
    return std::pair<int, int>(i, j);
}

void linear_search(std::vector<Passenger*>& data, int key) {
    int pos = -1;
    for (int i = 0; i < data.size(); i++) {
        if (data[i]->flight_number == key) {
            pos = i;
        }
    }
    if (pos == -1) {
        writeData(0, 0, "output.txt");
    }
    else {
        writeData(data[pos]->numberstr, pos + 1, "output.txt");
    }
}

void iterativeQuicksort(std::vector<Passenger*>& data)
{
    std::stack<std::pair<int, int>> s;
    int start = 0;
    int end = (int)data.size() - 1;
    s.push(std::make_pair(start, end));
    while (!s.empty())
    {
        start = s.top().first, end = s.top().second;
        s.pop();
        std::pair <int, int> pivot = partition(data, start, end);
        if (pivot.second > start) { s.push(std::make_pair(start, pivot.second)); }
        if (end > pivot.first) { s.push(std::make_pair(pivot.first, end)); }
    }
}

void WriteData(std::vector<Passenger*>data, std::string path) {
    std::ofstream fout;
    fout.open(path);
    for (int i = 0; i < data.size(); i++)
    {
        fout << data[i]->numberstr << ' ' << data[i]->flight_number << ' ';
        fout << data[i]->fio << ' ';
        std::string mon;
        if (data[i]->date.month < 10) mon = '0' + std::to_string(data[i]->date.month);
        else mon = std::to_string(data[i]->date.month);
        std::string dat;
        if (data[i]->date.number < 10) dat = '0' + std::to_string(data[i]->date.number);
        else dat = std::to_string(data[i]->date.number);
        fout << dat << '.' << mon << '.' << data[i]->date.year << ' ' << data[i]->fio_commander << '\n';
    }
    fout.close();
}

void interpolationSearch(std::vector<Passenger*> data, int key) {
    int left = 0;
    int right = data.size() - 1;
    int steps = 0;
    int result = 0;
    iterativeQuicksort(data);
    WriteData(data, "sort.txt");
    while (left <= right && key >= data[left]->flight_number && key <= data[right]->flight_number) {
        steps++;
        if (data[right]->flight_number != data[left]->flight_number)
        {
            int pos = left + ((key - data[left]->flight_number) * (right - left)) / (data[right]->flight_number - data[left]->flight_number);
            cout << pos << ' ';
            if (data[pos]->flight_number == key)
            {
                result = pos;
                left = pos + 1;
            }
            else if (data[pos]->flight_number < key)
            {
                left = pos + 1;
            }
            else
            {
                right = pos - 1;
            }
        }
        else
        {
            if (data[right]->flight_number == key)
            {
                writeData(data[right]->numberstr, steps, "output.txt");
                return;
            }
        }
    }
    writeData(data[result]->numberstr, steps, "output.txt");
}

int main() {
    clearFile("output.txt");
    int key = 1127;
    int n = 13;
    generateFile(n, "input.txt");
    std::vector<Passenger*>data = readData("input.txt");
    linear_search(data, key);
    interpolationSearch(data, key);
}