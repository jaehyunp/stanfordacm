//
// Created by elvircrn on 11/13/2017.
//

#include "simplex.h"

// #define DEBUG
// #define VERBOSE

vector<string> spl::GetHeader(size_t n) {
    vector<string> header = {"$b_i$"};
    for (int i = 1; i < n; i++)
        header.push_back("$x_{" + std::to_string(i) + "}$");
    return header;
}

vector<string> spl::GetCols(std::vector<size_t> BASE, size_t bigM) {
    vector<string> cols;
    if (bigM == 1)
        cols.push_back("M");
    for (size_t i = 1; i < BASE.size(); i++)
        cols.push_back("$x_{" + std::to_string(BASE[i]) + "}$");
    cols.push_back("");
    return cols;
}

std::tuple<int, int> spl::dualPivot(vector<vector<RatInt>> &a, size_t m, size_t n) {
    size_t p = 0, q = 0;
    RatInt min = INF;
    for (size_t i = 0; i < m; i++) {
        if (a[i][0] < 0 && a[i][0] < min) {
            min = a[i][0];
            p = i;
        }
    }

    if (min == INF) {
        return {-1, -1};
    }

    auto tmax = INF;

    for (size_t i = 1; i <= n + m; i++) {

        if ((double)a[p][i] < 0) {
            auto ratio = a[m][i] / a[p][i];
            if ((double)ratio < (double)tmax) {
                tmax = ratio;
                q = i;
            }
        }
    }

    if (tmax == INF)
        return {-1, -1};

    return {static_cast<int>(p), static_cast<int>(q)};
}

std::tuple<int, int, std::vector<std::string>>
spl::dantzig(vector<vector<RatInt>> &a, size_t m, size_t n, size_t bigM) {
    RatInt cmax = -1;
    size_t q = 0;

    for (size_t j = 1; j <= n + m; j++) {
        if ((a[bigM][j] > 0) && (a[bigM][j] > cmax)) {
            cmax = a[bigM][j];
            q = j;
        }
    }

    std::vector<std::string> flt(a.size() - 1);

    if (cmax == -1)
        return {-1, -1, flt};

    auto tmax = INF;

    size_t p = 1 + bigM;


    for (size_t i = 1 + bigM; i <= m; i++) {
        if (a[i][q] > 0) {
            std::stringstream ss;
            ss << (a[i][0] / a[i][q]) << " = " << double(a[i][0] / a[i][q]);
            flt[i - 1] = ss.str();
            if (tmax == INF || (a[i][0] / a[i][q]) < tmax) {
                tmax = a[i][0] / a[i][q];
                p = i;
            }
        }
    }

    if (tmax == INF) {
        std::cout << "Solution is unbounded";
    }

    return (tmax != INF) ? std::tuple<int, int, std::vector<std::string>>{(int) p, (int) q, flt}
                         : std::tuple<int, int, std::vector<std::string>>{(int) INF, (int) INF, flt};
};

std::tuple<int, int, std::vector<std::string>>
spl::MaxRise(vector<vector<RatInt>> &a, size_t m, size_t n, size_t bigM) {
    RatInt cmax = -1;
    RatInt ttmax = 0;

    size_t _p = 0, _q = 0;
    std::vector<std::string> flt(a.size() - 1 + bigM);
    for (size_t q = 1; q <= n + m; q++) {
        if (a[bigM][q] > 0) {
            auto tmax = INF;
            size_t p = 0;

            for (size_t i = 1 + bigM; i <= m; i++) {
                if (a[i][q] > 0) {
                    if (tmax == INF || (a[i][0] / a[i][q]) < tmax) {
                        std::stringstream ss;
                        ss << (a[i][0] / a[i][q]) << " = " << double(a[i][0] / a[i][q]);
                        flt[i - 1] += " " + ss.str();
                        tmax = a[i][0] / a[i][q];
                        p = i;
                    }
                }
            }

            tmax *= a[0][q];

            if (ttmax < tmax) {
                _p = p;
                _q = q;
                ttmax = tmax;
                flt[_p - 1] = std::to_string((double) ttmax);
            }
        }
    }


    return (ttmax != 0) ? std::tuple<int, int, std::vector<std::string>>{(int) _p, (int) _q, flt}
                        : std::tuple<int, int, std::vector<std::string>>{(int) INF, (int) INF, flt};
};

tuple<std::vector<RatInt>, RatInt> spl::Simplex(vector<vector<RatInt>> &a, size_t n, spl::PivotRule pivotRule,
                                                size_t bigM) {
    bool optimal = false;
    size_t m = a.size() - 1;

    std::vector<size_t> BASE(m + 1);
    if (bigM == 0)
        for (size_t i = 1; i <= m; i++)
            BASE[i] = n + i;
    else
        BASE = {0, 3, 4, 6};

    std::vector<bool> highRow(a.size());
    std::vector<bool> highCol(a[0].size());
    ltx::DrawTable<RatInt>(GetHeader(m + n + 1), GetCols(BASE, bigM), a, "", highRow, highCol, {});
    std::cout << '\n';


    while (!optimal) {
        std::cout << "\\\\\n";
        int _p, _q;

        std::vector<string> flt;

        switch (pivotRule) {
            case spl::PivotRule::DANTZIG:
                std::tie(_p, _q, flt) = dantzig(a, m, n, bigM);
                break;
            case spl::PivotRule::MAX_RISE:
                std::tie(_p, _q, flt) = MaxRise(a, m, n, bigM);
                break;
            case spl::PivotRule::DUAL_SIMPLEX:
                std::tie(_p, _q) = dualPivot(a, m, n);
                break;
        }

        if (_p == -1 || _p == INF) {
            break;
        }

        auto p = (size_t) _p;
        auto q = (size_t) _q;

        highRow[p] = true;
        highCol[q] = true;


        ltx::DrawTable<RatInt>(GetHeader(m + n + 1), GetCols(BASE, bigM), a, "", highRow, highCol, flt);

        BASE[p + 1 - (int) bigM] = q;
        RatInt pivot = a[p][q];

        for (size_t j = 0; j <= m + n; j++) {
            a[p][j] /= pivot;
        }

        for (int i = 0; i <= m; i++) {
            if (i != p) {
                auto factor = a[i][q];
                for (size_t j = 0; j <= n + m; j++) {
                    a[i][j] -= factor * a[p][j];
                }
            }
        }

        highCol.assign(highCol.size(), false);
        highRow.assign(highRow.size(), false);

        std::cout << '\n';
    }

    ltx::DrawTable<RatInt>(GetHeader(m + n + 1), GetCols(BASE, bigM), a, "", {}, {}, {});

    std::vector<RatInt> x(n + m + 1);

    if (pivotRule != spl::PivotRule::DUAL_SIMPLEX) {
        for (int i = 1; i <= m; i++)
            x[BASE[i]] = a[i][0];
    }
    else {
        for (int i = 0; i < m; i++)
            x[BASE[i]] = a[i][0];
    }

    RatInt Z;
    if (pivotRule != spl::PivotRule::DUAL_SIMPLEX)
        Z = a[0][0];
    else
        Z = -a[m][0];

    return {x, Z};
}

void spl::SolveSimplex(vector<vector<RatInt>> a, size_t n, spl::PivotRule pivotRule, size_t bigM) {
    std::vector<RatInt> x;
    RatInt Z;
    std::tie(x, Z) = Simplex(a, n, pivotRule, bigM);
    ltx::Begin("equation*");
    std::cout << '\n';
    ltx::Begin("aligned");

    std::cout << "(" << x[1];
    for (int i = 2; i < x.size(); i++)
        std::cout << ", " << x[i];
    std::cout << ")^T\n";
    std::cout << "Optimum: " << -Z << '\n';

    ltx::End("aligned");
    std::cout << '\n';
    ltx::End("equation*");
}
