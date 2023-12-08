//номер рейса(1 поле - 2 буквы, 2 поле - 4 цифры)
//фио(1 поле - строка, 2 поле - строка, 3 поле - строка)
//дата(1 поле - день(2 цифры), 2 поле - месяц(2 цифры), 3 поле - год(4 цифры))
//шевелев роман - 1 ключ - по возрастанию, 2 ключ - по убыванию
//алгоритмы: простые вставки, быстрая(итеративная реализация(с использованием стека), разбиение хоара, опорный - медиана из трёх)

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>
#include <stack>


struct Flight_Number {
    std::string sym;
    int num;
};

struct FIO {
    std::string surname;
    std::string name;
    std::string patronymic;
};

struct Date {
    int number;
    int month;
    int year;
};

struct Passenger {
    Flight_Number flight_number;
    FIO fio;
    Date date;
};

int compare_flight_number(Flight_Number first, Flight_Number second) {
    if (first.sym > second.sym) return 1;
    if (first.sym < second.sym) return -1;
    if (first.num > second.num) return 1;
    if (first.num < second.num) return -1;
    return 0;
}

int compare_FIO(FIO first, FIO second) {
    if (first.surname > second.surname) return 1;
    if (first.surname < second.surname) return -1;
    if (first.name > second.name) return 1;
    if (first.name < second.name) return -1;
    if (first.patronymic > second.patronymic) return 1;
    if (first.patronymic < second.patronymic) return -1;
    return 0;
}

int compare(Passenger* first, Passenger* second) {
    if (compare_flight_number(first->flight_number, second->flight_number) == 1) return 1;
    if (compare_flight_number(first->flight_number, second->flight_number) == -1) return -1;
    if (compare_FIO(first->fio, second->fio) == 1) return -1;
    if (compare_FIO(first->fio, second->fio) == -1) return 1;
    return 0;
}

Date parseDate(std::string input) {
    Date date;
    int dots_cnt = 0;
    for (int i = 0; input.length(); i++) {
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

Flight_Number parseNumber(std::string input) {
    Flight_Number number;
    number.sym = input.substr(0, 2);
    number.num = stoi(input.substr(2, 4));
    return number;
}

std::vector<Passenger*> readData(std::string path) {
    setlocale(LC_ALL, "Russian");
    std::ifstream fin;
    std::vector<Passenger*>data;
    fin.open(path);
    int n; fin >> n;
    std::string s;
    for (int i = 0; i < n; i++)
    {
        Passenger* person = new Passenger;
        fin >> s;
        person->flight_number = parseNumber(s);
        fin >> person->fio.surname >> person->fio.name >> person->fio.patronymic;
        fin >> s;
        person->date = parseDate(s);
        data.push_back(person);
    }
    fin.close();
    return data;
}

void generateFile(int n, std::string path) {
    std::ofstream fout;
    fout.open(path);
    fout << n << '\n';
    std::string surnames[126] = { "Антонов", "Зиновьев", "Куропаткин", "Матанализов", "Алгоритмов", "Сортировков", "Иванова", "Кулибина", "Литерная", "Блоха", "Бабай", "Базар", "Бибик", "Гадючка", "Дохлик", "Жуйвода", "Непейвода", "Моська", "Голобев", "Дракула", "Кощеев", "Сова", "Слива", "Интралигатор", "Кисель", "Зажерило",
        "Алиферов", "Андреев", "Анненков", "Барбаянов", "Башинский", "Березницкий", "Бессонов", "Бобровский", "Богатьев", "Божок", "Бондаренко", "Бухалихин", "Ван", "Ваяй", "Виноградов", "Виссарионов", "Власов", "Власов", "Гандзюк", "Герус", "Гоголева", "Горбарёв", "Давыдов", "Данишимаев", "Ди", "Егорова", "Еньшин", "Ерёменко",
        "Ермак", "Ерошенко", "Зеленин", "Иванов", "Карпачёв", "Касьяненко", "Киянов", "Козачко", "Колпакова", "Коряушкин", "Косенко", "Косилов", "Костюченко", "Кочетков", "Кропочев", "Кузьмин", "Кутузов", "Лагунова", "Лазарев", "Лебединский", "Литовченко", "Лукин", "Макогон", "Мареев", "Мартын", "Матушкин", "Машкин", "Михайлов", "Моисеев",
        "Мулява", "Мызников", "Налимов", "Нечепуренко", "Олейникова", "Осипенко", "Охлопков", "Павлов", "Пак", "Пасько", "Перепечаев", "Подолинский", "Половников", "Попов", "Проценко", "Пьявка", "Раздобаров", "Распутный", "Селиверстов", "Сивцева", "Спорышев", "Старцев", "Столетний", "Сутугин", "Тарасов", "Тахавов", "Терёхин",
        "Тимофеев","Трегубова", "Туровский", "Тюкова", "Уваров", "Хегай", "Хмелевский", "Храмцова", "Царегородцев", "Цыплаков", "Чечёткин", "Шевелёв", "Шешеня", "Шибанов", "Шмидт", "Якуба" };
    std::string names[65] = { "Агнес", "Адольф", "Адриан", "Борис", "Валентин", "Василий", "Виталий", "Георгий", "Григорий", "Даниил", "Денис", "Дмитрий", "Евгений", "Егор", "Иван", "Игорь", "Константин", "Леонид", "Максим", "Матвей", "Никита", "Николай", "Олег", "Павел", "Пётр", "Роман", "Руслан", "Сергей", "Степан", "Тимур", "Фёдор", "Юрий",
        "Ярослав", "Алиса", "Александра", "Алёна", "Алла", "Анастасия", "Анжелика", "Валентина", "Вероника", "Виктория", "Галина", "Дарья", "Диана", "Елизавета","Жанна", "Инна", "Ирина", "Карина", "Кристина", "Ксения", "Маргарита", "Мария", "Милана", "Наталья", "Ника", "Оксана", "Ольга", "Руслана", "Светлана", "София", "Софья", "Тамара", "Жанна" };
    std::string patronymic[36] = { "Александрович", "Алексеевич", "Анатольевич", "Аркадьевич", "Богданович", "Борисович", "Валерьевич", "Викторович", "Владимирович", "Вольфович", "Геннадиевич", "Григорьевич", "Денисович", "Евгеньевич", "Ефимович", "Игнатьевич", "Иосифович", "Кириллович", "Львович", "Матвеевич", "Николаевич", "Павлович", "Петрович",
        "Робертович", "Романович","Саныч","Северинович","Станиславович","Тарасович","Тимофеевич","Федорович","Филиппович","Эдуардович","Юрьевич","Яковлевич","Ярославович" };
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
        fout << char('A' + rand() % ('Z' - 'A')) << char('A' + rand() % ('Z' - 'A')) << std::to_string(rand() % 9000 + 1000) << ' '\
            << surnames[rand() % 126] << ' ' << names[rand() % 65] << ' ' << patronymic[rand() % 36] << ' ' << date\
            << '.' << mon << '.' << std::to_string(rand() % 82 + 1940) << '\n';
    }
    fout.close();
}

void writeData(std::vector<Passenger*>data, std::string path, long long microseconds) {
    std::ofstream fout;
    fout.open(path);
    fout << microseconds << '\n';
    for (int i = 0; i < data.size(); i++)
    {
        fout << data[i]->flight_number.sym << data[i]->flight_number.num << ' ';
        fout << data[i]->fio.surname << ' ' << data[i]->fio.name << ' ' << data[i]->fio.patronymic << ' ';
        std::string mon;
        if (data[i]->date.month < 10) mon = '0' + std::to_string(data[i]->date.month);
        else mon = std::to_string(data[i]->date.month);
        std::string dat;
        if (data[i]->date.number < 10) dat = '0' + std::to_string(data[i]->date.number);
        else dat = std::to_string(data[i]->date.number);
        fout << dat << '.' << mon << '.' << data[i]->date.year << '\n';
    }
    fout.close();
}

void StraightInsert(std::vector<Passenger*>& data) 
{
    size_t length = data.size();
    for (size_t i = 0; i < length; i++)
    {
        Passenger* temp = data[i];
        size_t j = i;
        while (j > 0 && compare(data[j - 1], temp) == 1)
        {
            data[j] = data[j - 1];
            j--;
        }
        data[j] = temp;
    }
}

std::pair<int,int> partition(std::vector<Passenger*>& data, int start, int end)
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
    return std::pair<int,int>(i,j);
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


int main()
{
    int n = 40000;
    generateFile(n, "input.txt");
    std::vector<Passenger*>data = readData("input.txt");
    auto start = std::chrono::high_resolution_clock::now();
    StraightInsert(data);
    iterativeQuicksort(data);
    std::reverse(data.begin(),data.end());
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count();
    writeData(data, "output.txt", microseconds);
}
