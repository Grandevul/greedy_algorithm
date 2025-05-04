#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <algorithm>
#include <random>
#include <stack>
#include <filesystem>
#include <chrono>

using namespace std;
using namespace std::filesystem;

bool cmp_default(pair <int, int> &x, pair <int, int> &y)
{
    if (x.first > y.first) return true;
    else if (x.first == y.first && x.second < y.second) return true;
    return false;
}

bool cmp_density(pair <int, int> &x, pair <int, int> &y)
{
    double a = x.first / x.second;
    double b = y.first / y.second;
    if (a > b) return true;
    else if (a == b && x.second < y.second) return true;
    return false;
}

int f(vector <pair <int, int> > a, int W, bool (*cmp)(pair <int, int>&, pair <int, int>&))
{
    int ans_value = 0;
    int current_w = 0;
    sort(a.begin(), a.end(), cmp);

    for (auto x : a)
    {
        if (x.second + current_w <= W)
        {
            ans_value += x.first;
            current_w += x.second;
        }
    }

    return ans_value;
}

int code(basic_ifstream<char, char_traits<char>> &in, bool (*cmp)(pair <int, int>&, pair <int, int>&))
{
    int W = 0;

    int n, w;
    vector <pair <int, int> > a;

    if (in.is_open())
    {
        in >> n >> w;
        W = w;
//        cout << n << " " << w << endl;

        for (int i = 0; i < n; i++)
        {
            int vi, wi;
            in >> vi >> wi;
            a.push_back(make_pair(vi, wi));
//            cout << vi << " " << wi << endl;
        }

//        cout << endl;
    }
    in.close();

///--------------------------

    int ans_value = f(a, W, cmp);

//    cout << "Answer: " << ans_value << endl;
    return ans_value;
}

int main()
{
//    ifstream in("data/ks_4_0");

    vector <string> data;

    std::string path = "data/"; // ѕуть к папке
    for (auto& entry : directory_iterator(path))
    {
        std::string path_string{entry.path().u8string()};
        cout << path_string.size() << " ";
        //if (path_string.size() > 13) continue;
        data.push_back(path_string);
    }
    cout << endl;

///-----------------------------------------------------------------

    std::ofstream out("table_default.txt", std::ios::app);

    for (int i = 0; i < data.size(); i++)
    {
        cout << data[i] << " -- ";
        ifstream in(data[i]);
        std::chrono::steady_clock::time_point begin0 = std::chrono::steady_clock::now();
        int value = code(in, cmp_default);
        cout << "Answer: " << value << endl;
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        out << data[i] << "   " << value << "       " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin0).count() << endl;
    }

///-----------------------------------------------------------------
    cout << "\n\n density: \n\n";

    std::ofstream out2("table_density.txt", std::ios::app);

    for (int i = 0; i < data.size(); i++)
    {
        cout << data[i] << " -- ";
        ifstream in(data[i]);
        std::chrono::steady_clock::time_point begin0 = std::chrono::steady_clock::now();
        int value = code(in, cmp_density);
        cout << "Answer: " << value << endl;
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        out2 << data[i] << "   " << value << "       " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin0).count() << endl;
    }
}
