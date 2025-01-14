#ifndef _NFFFT_BROADBAND_H_
#define _NFFFT_BROADBAND_H_

#include <complex>

#include "nffft/nffft.h"
#include "util/type_define.h"
#include "xtensor-fftw/basic_double.hpp"
#include "xtensor-fftw/helper.hpp"

namespace xfdtd {
class NffftBroadBand : public NFFFT {
 public:
  NffftBroadBand(SpatialIndex distance_x, SpatialIndex distance_y,
                 SpatialIndex distance_z, double theta, double phi,
                 std::filesystem::path output_dir_path);

  void init(std::unique_ptr<GridBox> output_box, std::shared_ptr<EMF> emf,
            size_t total_time_steps, double dt, double dx, double dy,
            double dz) override;

  void update(size_t current_time_step) override;

  void outputData() override;

 private:
  double _theta, _phi;
  double _smaple_rate;
  size_t _number_samples;
  PointVector _farfield_vector;

  EFTA _jx_yn, _jx_yp, _jx_zn, _jx_zp;
  EFTA _jy_xn, _jy_xp, _jy_zn, _jy_zp;
  EFTA _jz_xn, _jz_xp, _jz_yn, _jz_yp;
  EFTA _mx_yn, _mx_yp, _mx_zn, _mx_zp;
  EFTA _my_xn, _my_xp, _my_zn, _my_zp;
  EFTA _mz_xn, _mz_xp, _mz_yn, _mz_yp;

  // axuiliary function
  EFFA _n_x, _n_y, _n_z;
  EFFA _l_x, _l_y, _l_z;

  EFFA _n_theta, _n_phi, _l_theta, _l_phi;

  xt::xarray<double> _frequencies, _wave_number;
  EFFA _e_theta, _e_phi, _h_theta, _h_phi;
  EFTA _power_theta, _power_phi;

  void updateXN(size_t current_time_step);
  void updateXP(size_t current_time_step);
  void updateYN(size_t current_time_step);
  void updateYP(size_t current_time_step);
  void updateZN(size_t current_time_step);
  void updateZP(size_t current_time_step);

  void calculateFarfield();

  void calculateLNXYZ();
  void calculateAuxiliary(EFFA &n_a, EFFA &n_b, EFFA &l_a, EFFA &l_b,
                          const EFTA &j_a, const EFTA &j_b, EFTA &m_a,
                          EFTA &m_b, int x, int y, int z,
                          const xt::xarray<double> &delay, double ds);

  void outputFarFieldParamertes();
};

}  // namespace xfdtd

#endif  // _NFFFT_BROADBAND_H_