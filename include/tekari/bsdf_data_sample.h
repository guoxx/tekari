#pragma once

#include <tekari/data_sample.h>
#include <tekari/powitacq.h>

TEKARI_NAMESPACE_BEGIN

class BSDFDataSample : public DataSample
{
public:

    BSDFDataSample(const string& file_path);
    virtual void init() override;
    virtual void set_incident_angle(const Vector2f& incident_angle) override;
    virtual void set_intensity_index(size_t displayed_wavelength) override;

private:
    void compute_samples();

    powitacq::BRDF m_brdf;
    size_t m_n_theta;
    size_t m_n_phi;
};

TEKARI_NAMESPACE_END