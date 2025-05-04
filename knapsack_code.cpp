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

int main()
{
    int W = 0;
    ifstream in("data/ks_4_0");

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

    int ans_value = f(a, W, cmp_default);

    cout << "Answer: " << ans_value << endl;
    return 0;
}
