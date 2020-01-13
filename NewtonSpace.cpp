#ifndef NEWTONSPACE
#define NEWTONSPACE

// std::vector
#include <vector>
// sqrt
#include <cmath>
// memset
#include <cstring>
// swap
#include <algorithm>

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

    Point operator *(double c) {
        return Point(this->x*c, this->y*c);
    }

    Point operator /(double c) {
        return Point(this->x/c, this->y/c);
    }

    Point operator +(Point p2) {
        return Point(this->x+p2.x, this->y+p2.y);
    }

    Point operator -(Point p2) {
        return Point(this->x-p2.x, this->y-p2.y);
    }
};


struct Partical {
    double mass, r;
    Point pos, d;
    Partical(double mass, double r, Point pos, Point d) {
        this->mass = mass;
        this->r = r;
        this->pos = pos;
        this->d = d;
    }
};


class NewtonSpace {
public:
    std::vector<Partical> particals;

    NewtonSpace() {
    }

    ~NewtonSpace() {
    }

    void addPartical(Partical p) {
        this->particals.push_back(p);
    }

    int getLen() {
        return this->particals.size();
    }

    void update(double G, double time, bool collide=false) {
        this->updateSpd(G, time, collide);
        this->updatePos(time);
    }

    std::vector<Partical> getParticals() {
        return this->particals;
    }

protected:
    // Main part!
    void updateSpd(double G, double time, bool collide) {
        const int len = this->getLen();

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
                    pow(((this->particals)[i].pos.x - (this->particals)[j].pos.x),2.) +
                    pow(((this->particals)[i].pos.y - (this->particals)[j].pos.y),2.)
                );
            }
        }

        // forces
        for(int i=0; i<len; i++) {
            for(int j=0; j<len; j++) {
                if(i==j)continue;
                // cannot div by zero
                a[i][j] = G*(this->particals)[i].mass/pow(((dist[i][j]<.0001)?.0001:dist[i][j]),2);
            }
        }

        // accelerations
        for(int i=0; i<len; i++) {
            for(int j=0; j<len; j++) {
                if(i==j)continue;
                d2x[i] += a[i][j]*((this->particals)[i].pos.x - (this->particals)[j].pos.x);
                d2y[i] += a[i][j]*((this->particals)[i].pos.y - (this->particals)[j].pos.y);
            }
        }

        // apply
        for(int i=0; i<len; i++) {
            (this->particals)[i].d.x -= d2x[i]*time;
            (this->particals)[i].d.y -= d2y[i]*time;
        }

        if(!collide)return;
        // handle collide
        for(int i=0; i<len-1; i++) {
            for(int j=i+1; j<len; j++) {
                if(dist[i][j] < (this->particals)[i].r + (this->particals)[j].r) {
                    Partical newi = (this->particals)[i];
                    Partical newj = (this->particals)[j];

                    newi.d = ((this->particals)[i].d*((this->particals)[i].mass-(this->particals)[j].mass)+(this->particals)[j].d*(2*(this->particals)[j].mass)) / ((this->particals)[i].mass+(this->particals)[j].mass);
                    newj.d = ((this->particals)[j].d*((this->particals)[j].mass-(this->particals)[i].mass)+(this->particals)[i].d*(2*(this->particals)[i].mass)) / ((this->particals)[i].mass+(this->particals)[j].mass);

                    (this->particals)[i] = newi;
                    (this->particals)[j] = newj;

                    // Some stupid hacks
                    while(
                        sqrt(
                            pow(((this->particals)[i].pos.x - (this->particals)[j].pos.x),2.) +
                            pow(((this->particals)[i].pos.y - (this->particals)[j].pos.y),2.)
                        ) < (this->particals)[i].r + (this->particals)[j].r
                    ) {
                        (this->particals)[i].pos.x += (this->particals)[i].d.x*time;
                        (this->particals)[i].pos.y += (this->particals)[i].d.y*time;

                        (this->particals)[j].pos.x += (this->particals)[j].d.x*time;
                        (this->particals)[j].pos.y += (this->particals)[j].d.y*time;}
                }
            }
        }
    }

    void updatePos(double time) {
        const int len = this->getLen();

        for(int i=0; i<len; i++) {
            (this->particals)[i].pos.x += (this->particals)[i].d.x*time;
            (this->particals)[i].pos.y += (this->particals)[i].d.y*time;
        }
    }
};

#endif
