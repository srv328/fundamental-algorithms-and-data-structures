#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>

struct Passenger {
    struct Flight_Number {
        std::string sym;
        int num;
    };
    Flight_Number flight_number;
    std::string fio;
    std::string fio_commander;
    struct Date {
        int number;
        int month;
        int year;
    };
    Date date;
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
        person->flight_number.sym = s.substr(0, 2);
        person->flight_number.num = stoi(s.substr(2, 4));
        fin >> fa; fin >> im; fin >> ot;
        person->fio = fa + ' ' + im + ' ' + ot;
        fin >> s;
        person->date = parseDate(s);
        fin >> fa; fin >> im; fin >> ot;
        person->fio_commander = fa + ' ' + im + ' ' + ot;
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
        fout << char('A' + rand() % ('Z' - 'A')) << char('A' + rand() % ('Z' - 'A')) << std::to_string(rand() % 9000 + 1000) + ' '\
            + surnames[rand() % 126] + ' ' + names[rand() % 65] + ' ' + patronymic[rand() % 36] + ' ' + date\
            + '.' + mon + '.' + std::to_string(rand() % 92 + 1930) + ' ' + surnames[rand() % 126] + ' ' + names[rand() % 65] + ' ' + patronymic[rand() % 36] + '\n';
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

const int k = 256, NMAX = 10000;
int badchar[k];

struct bohr_vrtx {
    int next_vrtx[k], pat_num, suff_link, auto_move[k], par, suff_flink;
    bool flag;
    char symb;
};
std::vector<bohr_vrtx> bohr;
std::vector<std::string> pattern;

bohr_vrtx make_bohr_vrtx(int p, char c) {
    bohr_vrtx v;
    memset(v.next_vrtx, 255, sizeof(v.next_vrtx));
    memset(v.auto_move, 255, sizeof(v.auto_move));
    v.flag = false;
    v.suff_link = -1;
    v.par = p;
    v.symb = c;
    v.suff_flink = -1;
    return v;
}
void bohr_ini() {
    bohr.push_back(make_bohr_vrtx(0, '$'));
}
void add_string_to_bohr(const std::string& s) {
    int num = 0;
    for (int i = 0; i < s.length(); i++) {
        char ch = s[i];
        if (bohr[num].next_vrtx[ch] == -1) {
            bohr.push_back(make_bohr_vrtx(num, ch));
            bohr[num].next_vrtx[ch] = bohr.size() - 1;
        }
        num = bohr[num].next_vrtx[ch];
    }
    bohr[num].flag = true;
    pattern.push_back(s);
    bohr[num].pat_num = pattern.size() - 1;
}
bool is_string_in_bohr(const std::string& s) {
    int num = 0;
    for (int i = 0; i < s.length(); i++) {
        char ch = s[i];
        if (bohr[num].next_vrtx[ch] == -1) {
            return false;
        }
        num = bohr[num].next_vrtx[ch];
    }
    return true;
}
int get_auto_move(int v, char ch);
int get_suff_link(int v) {
    if (bohr[v].suff_link == -1)
        if (v == 0 || bohr[v].par == 0)
            bohr[v].suff_link = 0;
        else
            bohr[v].suff_link = get_auto_move(get_suff_link(bohr[v].par), bohr[v].symb);
    return bohr[v].suff_link;
}
int get_auto_move(int v, char ch) {
    if (bohr[v].auto_move[ch] == -1)
        if (bohr[v].next_vrtx[ch] != -1)
            bohr[v].auto_move[ch] = bohr[v].next_vrtx[ch];
        else
            if (v == 0)
                bohr[v].auto_move[ch] = 0;
            else
                bohr[v].auto_move[ch] = get_auto_move(get_suff_link(v), ch);
    return bohr[v].auto_move[ch];
}
int get_suff_flink(int v) {
    if (bohr[v].suff_flink == -1) {
        int u = get_suff_link(v);
        if (u == 0)
            bohr[v].suff_flink = 0;
        else
            bohr[v].suff_flink = (bohr[u].flag) ? u : get_suff_flink(u);
    }
    return bohr[v].suff_flink;
}
int check(int v, int i) {
    int count = 0;
    for (int u = v;u != 0;u = get_suff_flink(u)) {
        if (bohr[u].flag) count++;
    }
    return count;
}
int find_all_pos(std::string s) {
    int u = 0;
    int count = 0;
    for (int i = 0;i < s.length();i++) {
        u = get_auto_move(u, s[i]);
        count += check(u, i + 1);
    }
    return count;
}

void badCharHeuristic(std::string str, int size, int badchar[k])
{
    for (int i = 0; i < k; i++) { badchar[i] = -1; }
    for (int i = 0; i < size; i++) { badchar[(int)str[i]] = i; }
}

int searchBM(std::string txt)
{
    int count = 0;
    for (int i = 0; i < pattern.size(); i++) {
        int m = pattern[i].size();
        int n = txt.size();
        badCharHeuristic(pattern[i], m, badchar);
        int s = 0;
        while (s <= (n - m))
        {
            int j = m - 1;
            while (j >= 0 && pattern[i][j] == txt[s + j]) { j--; }
            if (j < 0) { count++; s += (s + m < n) ? m - badchar[txt[s + m]] : 1; }
            else s += std::max(1, j - badchar[txt[s + j]]);
        }
    }
    return count;
}

void Aho(std::vector<Passenger*> data, int min) {
    std::vector<Passenger*>res;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < data.size(); i++) { if ((find_all_pos(data[i]->fio) >= min) || (find_all_pos(data[i]->fio_commander) >= min)) { res.push_back(data[i]); } }
    long long microseconds = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start).count();
    writeData(res, "AHO_CORASIK.txt", microseconds);
}

void BM(std::vector<Passenger*>data, int min) {
    std::vector<Passenger*>res1;
    auto start1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < pattern.size(); i++) {
        int m = pattern[i].size();
        badCharHeuristic(pattern[i], m, badchar);
    }
    for (int i = 0; i < data.size(); i++) { if ((searchBM(data[i]->fio) >= min) || (searchBM(data[i]->fio_commander)) >= min) { res1.push_back(data[i]); } }
    long long microseconds1 = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - start1).count();
    writeData(res1, "BOYER_MURRR.txt", microseconds1);
}

int main() {
    int n = 10000;
    generateFile(n, "input.txt");
    std::vector<Passenger*>data = readData("input.txt");
    bohr_ini();
    add_string_to_bohr("she");
    add_string_to_bohr("he");
    add_string_to_bohr("his");
    add_string_to_bohr("her");
    add_string_to_bohr("i");
    add_string_to_bohr("is");
    add_string_to_bohr("ovich");
    add_string_to_bohr("vich");
    add_string_to_bohr("ch");
    int min = 4;
    Aho(data,min);
    BM(data, min);
}
