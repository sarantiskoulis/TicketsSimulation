#include <iostream>
#include <random>
#include <nlohmann/json.hpp>
#include <fstream>
#include <thread>
#include <vector>
#include "settings.h"

using json = nlohmann::json;

using namespace std;
std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<> dis(-setpSize, setpSize);
std::uniform_real_distribution<> c2dis(p2_lower_limit, p2_upper_limit);
std::uniform_real_distribution<> c3dis(p3_lower_limit, p3_upper_limit);
std::uniform_real_distribution<> c4dis(p4_lower_limit, p4_upper_limit);
std::uniform_real_distribution<> c5dis(p5_lower_limit, p5_upper_limit);


long int p5(double v) {
    double p = (3.870185 * v) - 9.690052;
    int p_int = static_cast<int>(p);
    return p_int;
}

double pnl(int v ,double c2, double c3, double c4, double c5) {
    double profit = (c2 *(11.965685 * p5(v))) + (c3 * (3.878246 * p5(v))) + (c4 * (0.9003124 * p5(v)) )+ (c5 * p5(v));
    double _pnl = profit - v;
    return _pnl;
}


void Update(double &c, double x, double lb, double hb) {
    if (c + x > hb) {
        c -= x;
    }
    if (c - x > lb) {
        c += x;
    }
}


void Runs(int start, int end, int runs , vector<double> &HighestRound) {

    int v = 10;
    double c2 = c2dis(gen);
    double c3 = c3dis(gen);
    double c4 = c4dis(gen);
    double c5 = c5dis(gen);

    double high_pnl = 0;
    double high_c2 = 0.0;
    double high_c3 = 0.0;
    double high_c4 = 0.0;
    double high_c5 = 0.0;

    for (int k = start; k < end; ++k) {
        for (int i = 0; i < runs; ++i) {
            double pnl_score = pnl(v ,c2,c3,c4,c5);
            if (pnl_score > high_pnl) {
                high_pnl = pnl_score;
                high_c2 = c2;
                high_c3 = c3;
                high_c4 = c4;
                high_c5 = c5;

            }
            double randNum5 =dis(gen);
            double randNum4 =dis(gen);
            double randNum3 =dis(gen);
            double randNum2 =dis(gen);
            Update(c2, randNum2, 0.022, 0.045);
            Update(c3, randNum3, 0.05, 0.09);
            Update(c4, randNum4, 0.11, 0.19);
            Update(c5, randNum5, 0.30, 0.5);
        }
        if (high_pnl > HighestRound[0]) {
            HighestRound[0] = high_pnl;
            HighestRound[1] = high_c2;
            HighestRound[2] = high_c3;
            HighestRound[3] = high_c4;
            HighestRound[4] = high_c5;
        }

        c2 = c2dis(gen);
        c3 = c3dis(gen);
        c4 = c4dis(gen);
        c5 = c5dis(gen);
    }
}


int main() {
    json log;
    int num_threads = 20;
    std::vector<std::thread> threads;
    const int elements_per_thread = num_elements / num_threads;
    std::vector<std::vector<double>> answersVector(num_threads, std::vector<double>(5, 0));

    for (int i = 0; i < num_threads; ++i) {
        int start = i * elements_per_thread;
        int end = (i == num_threads - 1) ? num_elements : start + elements_per_thread;
        threads.emplace_back(Runs,
                             start, end,
                             runs,
                             std::ref(answersVector[i])

        );
    }
    for (auto &thread: threads) {
        thread.join();
    }
    for (auto ans: answersVector) {
        cout << "pnl: " << ans[0];
        cout << " c2 " << ans[1];
        cout << " c3 " << ans[2];
        cout << " c4 " << ans[3];
        cout << " c5 " << ans[4];
        cout << endl;
    }



//    cout << high_pnl<< " " << high_c2<< " "<< high_c3 << " " << high_c4 << " " << high_c5 << endl;
//    std::ofstream outJson("C:\\Users\\sarantis\\CLionProjects\\TicketsSimulation\\logs.json");
//    std::string jsonString = log.dump();
//    outJson << jsonString;



}
