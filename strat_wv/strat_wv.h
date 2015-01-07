
#ifndef __strat_wv__H__
#define __strat_wv__H__

#include <memory>
#include <vector>

struct coordinates;
using namespace std;
using point = struct coordinates;
using fn_db = std::function<double(const double)>;


class mesh{
   private:   
     point** v_field;
     point** v_field_prev;
     double h {1};
     int N;
   
   public:
      mesh();
      void init_mesh(double interval, int _N);
      void set_mesh(double k, double omega, double t, fn_db m);
      void update();
      int size(){return N;};
      double scale(){return N*h;};
      const point& get_point(int i,int j);
      mesh& operator++();
      ~mesh();
};

struct coordinates{
   double x_pos{};
   double z_pos{};
   double u{};
   double w{};
   double omega{};
   double k{};
   double t{};
   fn_db m {};
   point& operator++();
   double integrator();
};

#endif
