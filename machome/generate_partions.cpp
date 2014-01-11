/*
 * =====================================================================================
 *
 *       Filename:  generate_partitons.cpp
 *
 *    Description:  generate all partitons of a given number
 *
 *        Version:  1.0
 *        Created:  11/01/2014 09:30:01
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Rong Xiao (rxiao), akelux@gmail.com
 *   Organization:  VRTalents
 *
 * =====================================================================================
 */
#include <vector>
#include <utility>
#include <iostream>
#include <ostream>
#include <algorithm>

using namespace std;

template<class T> ostream& operator<<(ostream& os, const vector<T>& v) {
    os << '(';
    for (const T& t : v) {
        os << ' ' << t;
    }
    os  << ' ' << ')';
    return os;
}
/*
 * Algorithm:
 *      1. if number of partitons not change, each partitons is generate from partitons of n-1 with same number:
 *          add 1 to a component and keep the non decremental ordering, e.g 1 -> 2. (1,1) -> (1,2), (1,2) -> (1,3), (2,2)
 *      2. 
 */
vector<vector<size_t>> generatePartions(const size_t n) {
    vector<pair<vector<size_t>, vector<size_t>>> draft;  // working draft: [(1,2,3), (0,1,2) 
    for (size_t  i = 1; i<=n; ++i) {
                cout << "i: " << i << endl;
        vector<pair<vector<size_t>, vector<size_t>>> t;  // inner working draft
        t.push_back(pair<vector<size_t>, vector<size_t>>(vector<size_t>(i, 1), vector<size_t>(1,i-1)));
        for (auto it = draft.begin(); it!=draft.end(); ++it) {
            vector<size_t>& partiton = it->first;
            cout << "partiton: " << partiton << endl;
            vector<size_t>& jumps = it->second;
            cout << "jumps: " << jumps << endl;
            const size_t m = jumps.size();
            size_t j = 0;
            for ( ; j<m-1; ++j) {
                cout << "j: " << j << endl;
                size_t l = jumps[j]; 
                vector<size_t> t_partiton(partiton);
                t_partiton[l]++;
                vector<size_t> t_jumps(jumps);
                if (t_partiton[l] == t_partiton[l+1]) { // check if keep l, delete l
                    t_jumps.erase(t_jumps.begin()+j);
                }
                cout << "t_partiton: " << t_partiton << endl;
                cout << "t_jumps: " << t_jumps << endl;
                if (l>0) {
                    if  (j == 0 || t_jumps[j-1] != l-1) {
                        vector<size_t> tt_jumps (t_jumps.size()+1);
                        const auto it0 = t_jumps.begin(); 
                        auto it1= std::copy(it0,  it0+j, tt_jumps.begin());
                        *it1 = l-1;
                        ++it1;
                        std::copy(it0+j,  t_jumps.end(), it1);
                        t.push_back(pair<vector<size_t>, vector<size_t>>(t_partiton, std::move(tt_jumps)));
                    } else {
                        t.push_back(pair<vector<size_t>, vector<size_t>>(t_partiton, t_jumps));
                    }
                }
                t.push_back(pair<vector<size_t>, vector<size_t>>(std::move(t_partiton), std::move(t_jumps)));
            }
            ++partiton.back();  // reuse space for last case
            size_t l = jumps.back();
            if (l<partiton.size() && partiton[l] == partiton[l+1]) {
                jumps.pop_back();
            }
            if (l>0) {
                if  (j == 0 || jumps[j-1] != l-1) {
                    vector<size_t> tt_jumps (jumps.size()+1);
                    const auto it0 = jumps.begin(); 
                    auto it1= std::copy(it0,  it0+j, tt_jumps.begin());
                    *it1 = l-1;
                    ++it1;
                    std::copy(it0+j,  jumps.end(), it1);
                    t.push_back(pair<vector<size_t>, vector<size_t>>(partiton, std::move(tt_jumps)));
                } else {
                    t.push_back(pair<vector<size_t>, vector<size_t>>(partiton, jumps));
                }
            }
            t.push_back(pair<vector<size_t>, vector<size_t>>(std::move(partiton), std::move(jumps)));
        }
        std::swap(t, draft);
    }
    const size_t m = draft.size();
    vector<vector<size_t>> res(m);
    for (size_t i = 0; i!=m; ++i) {
        std::swap(res[i], draft[i].first);
    }
    return std::move(res);
}

int main() {
    // cout << generatePartions(0) << endl;
    // cout << generatePartions(1) << endl;
    // cout << generatePartions(2) << endl;
    cout << generatePartions(3) << endl;
    // cout << generatePartions(4) << endl;
    // cout << generatePartions(5) << endl;
}

