#include <bits/stdc++.h>
using namespace std;

const double EPS = 1e-6;
const double INF = 1e18;

struct Particle {
    int color;
    double px, py, vx, vy;
};

bool equal(double a, double b) {
    return fabs(a - b) < EPS;
}

bool willEverHitDemon(Particle p, double w, double h, double d, double &timeHit) {
    for (int t = 1; t <= 10000; ++t) {
        double x = p.px + p.vx * t;
        double y = p.py + p.vy * t;
        int refX = floor(x / w);
        if ((int)refX % 2 == 1) x = w - fmod(x, w);
        else x = fmod(x, w);

        int refY
         = floor(y / h);
        if ((int)refY
         % 2 == 1) y = h - fmod(y, h);
        else y = fmod(y, h);

        if (equal(x, 0.0) && equal(y, d)) {
            timeHit = t;
            return true;
        }
    }
    return false;
}

bool canBeSorted(vector<Particle> &particles, double w, double h, double d, double T) {
    for (auto &p : particles) {
        double x = p.px + p.vx * T;
        double y = p.py + p.vy * T;

        int rx = floor(x / w);
        if ((int)rx % 2 == 1) x = w - fmod(x, w);
        else x = fmod(x, w);

        int ry = floor(y / h);
        if ((int)ry % 2 == 1) y = h - fmod(y, h);
        else y = fmod(y, h);

        bool inLeft = (x < w);

        if ((p.color == 0 && !inLeft) || (p.color == 1 && inLeft)) {
            return false;
        }
    }
    return true;
}

int main() {
    int w, h, d, r, b;
    cin >> w >> h >> d >> r >> b;

    vector<Particle> particles(r + b);
    for (int i = 0; i < r + b; ++i) {
        int px, py, vx, vy;
        cin >> px >> py >> vx >> vy;
        particles[i] = {i >= r, (double)px, (double)py, (double)vx, (double)vy};
    }

    vector<double> hitTimes;

    for (auto &p : particles) {
        double t;
        if (willEverHitDemon(p, w, h, d, t)) {
            hitTimes.push_back(t);
        }
    }

    hitTimes.push_back(0.0); 
    sort(hitTimes.begin(), hitTimes.end());

    for (double t : hitTimes) {
        if (canBeSorted(particles, w, h, d, t)) {
            cout << fixed << setprecision(6) << t << "\n";
            return 0;
        }
    }

    cout << "impossible\n";
    return 0;
}
