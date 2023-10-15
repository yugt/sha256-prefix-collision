#include <iostream>
#include <cassert>
#include <sstream>
#include <string>
#include <vector>
#include <array>
#include <unordered_map>

// for multithread (>=32)
#include <atomic>
#include <thread>
#include <mutex>
#include <condition_variable>

#include <chrono> // performance measure

#include "sha256.h"


using std::string, std::vector, std::array,
    std::thread, std::unordered_map;

using namespace std::chrono;


const int p62[6] = {
    1,
    62,
    3844,
    238328,
    14776336,
    916132832
};

enum { L = 62, T = 32 };

const char c[L] = 
{
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
    'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
    'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
    'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
};

void lbub(int index, array<int, 10>& range)
{
    for(int i=0; i<range.size(); i+=2)
    {
        range[ i ] = (index % 2)==0 ?  0 : L/2;
        range[i+1] = (index % 2)==0 ?  L/2 : L;
        index /= 2;
    }
}


class check
{
    std::condition_variable cv;
    std::atomic<int> counter;
    vector<thread> tasks;
    unordered_map<string, string> table;
    array<vector<std::pair<string, string>>, T> local;
    std::mutex m;
    char prefix;

    bool valid(char input)
    {
        for(int i=0;i<L;i++){
            if (input == c[i]) return true;
        }
        return false;
    }

    void child1(int index)
    {
        array<int, 10> range;
        lbub(index, range);
        int prod = 1;
        for(int i=2; i<range.size(); i+=2) prod *= range[i+1]-range[i];
        auto& task = local.at(index);
        task.reserve(prod);
        int i[5] = { 0,0,0,0,0 };
        for(i[0]=range[0]; i[0]<range[1]; i[0]++){
        for(i[1]=range[2]; i[1]<range[3]; i[1]++){
        for(i[2]=range[4]; i[2]<range[5]; i[2]++){
        for(i[3]=range[6]; i[3]<range[7]; i[3]++){
        for(i[4]=range[8]; i[4]<range[9]; i[4]++){
            string text({ prefix, c[i[0]], c[i[1]], c[i[2]], c[i[3]], c[i[4]] });
            task.emplace_back(sha256(text).substr(0,16), text.substr(1,5));
        }}}}
        m.lock(); table.insert(task.begin(), task.end()); m.unlock();
        task.clear();
        }
        task.shrink_to_fit();
        counter++;
        if(counter == local.size()) cv.notify_one();
    }

    void child2(int index, char p)
    {
        array<int, 10> range;
        lbub(index, range);
        int i[5] = { 0,0,0,0,0 };
        for(i[0]=range[0]; i[0]<range[1]; i[0]++){
        for(i[1]=range[2]; i[1]<range[3]; i[1]++){
        for(i[2]=range[4]; i[2]<range[5]; i[2]++){
        for(i[3]=range[6]; i[3]<range[7]; i[3]++){
        for(i[4]=range[8]; i[4]<range[9]; i[4]++){
            string text({ p, c[i[0]], c[i[1]], c[i[2]], c[i[3]], c[i[4]] });
            string hash = sha256(text).substr(0,16);
            if(table.contains(hash))
                std::printf("%s,%c%s,%s\n",
                    hash.c_str(), prefix, table[hash].c_str(), text.c_str());
        }}}}}
        counter++;
        if(counter == local.size()) cv.notify_one();
    }

    auto parent(char p)
    {
        auto start = high_resolution_clock::now();
        counter = 0;
        table.reserve(p62[5]);
        tasks.clear(); tasks.reserve(local.size());
        for(auto i=0; i<local.size(); i++)
            p == '\0' ?
            tasks.emplace_back([this, i]{child1(i);}) :
            tasks.emplace_back([this, i, p]{child2(i,p);});
        assert(tasks.size() == local.size());
        for(auto& t:tasks) t.join();
        std::unique_lock<std::mutex> lck(m);
        cv.wait(lck, [this] { return counter == tasks.size(); } );
        assert(table.size() == p62[5]);
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start);
        return duration.count();
    }

public:
    check(string input)
    {
        assert(input.length()==1 ?
            valid(input.c_str()[0]) :
            valid(input.c_str()[0]) &&
            valid(input.c_str()[1]) );
        prefix = input.c_str()[0];
        std::cerr << prefix << '\t' << parent('\0') << std::endl;
        if(input.length()==2)
        { // generate + single
            std::cerr << input.c_str()[1] << '\t' <<
            parent(input.c_str()[1]) << std::endl; //compare single prefix
        }
        else
        {
            int begin = 0;
			for(;begin < L;begin++) { if(c[begin]==input.c_str()[0]) break; }
			for(int i=begin+1; i<L; i++)
                std::cerr << c[i] << '\t' << parent(c[i]) << std::endl;
        }
    }

};

int main(int argc, char* argv[])
{
    assert(argc==2);
    string input(argv[1]);
    assert(input.length() <= 2);
    check _(input);
    return 0;
}
