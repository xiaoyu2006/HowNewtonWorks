#ifndef NEWTONSPACE
#define NEWTONSPACE

// std::vector
#include <vector>
// sqrt
#include <cmath>
// memset
#include <cstring>

struct Point {
    double x, y;
    Point(double x, double y) {
        this->x = x;
        this->y = y;
    }

    Point() {
        this->x = .0;
        this->y = .0;
    }
};


struct Partical {
    double mass;
    Point pos, d;
    Partical(double mass, Point pos, Point d) {
        this->mass = mass;
        this->pos = pos;
        this->d = d;
    }
};


class NewtonSpace {
public:
    std::vector<Partical> *particals;

    NewtonSpace() {
        this->particals = new std::vector<Partical>;
    }

    ~NewtonSpace() {
        delete this->particals;
    }

    void addPartical(Partical p) {
        this->particals->push_back(p);
    }

    int getLen() {
        return this->particals->size();
    }

    void update(double G, double time) {
        this->updateSpd(G, time);
        this->updatePos(time);
    }

    std::vector<Partical> getParticals() {
        return *this->particals;
    }

private:
    // Main part!
    void updateSpd(double G, double time) {
        int len = this->getLen();

        // distances
        double dist[len][len];
        // forces
        double a[len][len];
        // accelerations
        double d2x[len];
        double d2y[len];

        memset(d2x, .0, sizeof(d2x));
        memset(d2y, .0, sizeof(d2y));

        // distances
        for(int i=0; i<len; i++) {
            for(int j=0; j<len; j++) {
                if(i==j)continue;
                dist[i][j] = sqrt(
                    pow(((*this->particals)[i].pos.x - (*this->particals)[j].pos.x),2.) +
                    pow(((*this->particals)[i].pos.y - (*this->particals)[j].pos.y),2.)
                );
            }
        }

        // forces
        for(int i=0; i<len; i++) {
            for(int j=0; j<len; j++) {
                if(i==j)continue;
                a[i][j] = G*(*this->particals)[i].mass/dist[i][j];
            }
        }

        // accelerations
        for(int i=0; i<len; i++) {
            for(int j=0; j<len; j++) {
                if(i==j)continue;
                d2x[i] += a[i][j]*((*this->particals)[i].pos.x - (*this->particals)[j].pos.x);
                d2y[i] += a[i][j]*((*this->particals)[i].pos.y - (*this->particals)[j].pos.y);
            }
        }

        // apply
        for(int i=0; i<len; i++) {
            (*this->particals)[i].d.x += d2x[i]*time;
            (*this->particals)[i].d.y += d2y[i]*time;
        }
    }

    void updatePos(double time) {
        for(Partical it : *this->particals) {
            it.pos.x += it.d.x*time;
            it.pos.y += it.d.y*time;
        }
    }
};

#endif
