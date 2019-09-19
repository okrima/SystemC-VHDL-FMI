// /////////////////////////////////////////////////////////////////////////
// C++ code automatically generated by hif2sc
// Part of HIFSuite - Version 2017.05.1-antlia
// Site: www.hifsuite.com - Contact: hifsuite@edalab.it
//
// HIFSuite copyright: EDALab s.r.l. - Networked Embedded Systems
// Site: www.edalab.it - Contact: info@edalab.it
// /////////////////////////////////////////////////////////////////////////


#ifndef ACCELEROMETER_HH
#define ACCELEROMETER_HH

#include <stdint.h>

class accelerometer
{

public:

    bool analog_clock_old;
    double avx_old;
    double avy_old;
    double avz_old;
    struct accelerometer_iostruct{
        double accelerometer_V_reduced_0_dot_ddt;
        double accelerometer_V_avx_ddt;
        double accelerometer_V_avy_ddt;
        double accelerometer_V_avz_ddt;
        double accelerometer_V_reduced_1_dot_ddt;
        double accelerometer_V_reduced_1_ddt;
        double accelerometer_V_reduced_0_ddt;
        double avz;
        double avy;
        double avx;
        double Cap7;
        double Cap5;
        double Cap2;
        double Cap1;
        bool analog_clock;

        accelerometer_iostruct():
            accelerometer_V_reduced_0_dot_ddt(0.0),
            accelerometer_V_avx_ddt(0.0),
            accelerometer_V_avy_ddt(0.0),
            accelerometer_V_avz_ddt(0.0),
            accelerometer_V_reduced_1_dot_ddt(0.0),
            accelerometer_V_reduced_1_ddt(0.0),
            accelerometer_V_reduced_0_ddt(0.0),
            avz(0.0),
            avy(0.0),
            avx(0.0),
            Cap7(0.0),
            Cap5(0.0),
            Cap2(0.0),
            Cap1(0.0),
            analog_clock(false)
        {}

        accelerometer_iostruct( const double accelerometer_V_reduced_0_dot_ddt_0,
             const double accelerometer_V_avx_ddt_0, const double accelerometer_V_avy_ddt_0,
             const double accelerometer_V_avz_ddt_0, const double accelerometer_V_reduced_1_dot_ddt_0,
             const double accelerometer_V_reduced_1_ddt_0, const double accelerometer_V_reduced_0_ddt_0,
             const double avz_0, const double avy_0, const double avx_0, const double
             Cap7_0, const double Cap5_0, const double Cap2_0, const double Cap1_0,
             const bool analog_clock_0 ):
            accelerometer_V_reduced_0_dot_ddt(accelerometer_V_reduced_0_dot_ddt_0
                ),
            accelerometer_V_avx_ddt(accelerometer_V_avx_ddt_0),
            accelerometer_V_avy_ddt(accelerometer_V_avy_ddt_0),
            accelerometer_V_avz_ddt(accelerometer_V_avz_ddt_0),
            accelerometer_V_reduced_1_dot_ddt(accelerometer_V_reduced_1_dot_ddt_0
                ),
            accelerometer_V_reduced_1_ddt(accelerometer_V_reduced_1_ddt_0),
            accelerometer_V_reduced_0_ddt(accelerometer_V_reduced_0_ddt_0),
            avz(avz_0),
            avy(avy_0),
            avx(avx_0),
            Cap7(Cap7_0),
            Cap5(Cap5_0),
            Cap2(Cap2_0),
            Cap1(Cap1_0),
            analog_clock(analog_clock_0)
        {}

        ~accelerometer_iostruct()
        {}

        bool operator == (const accelerometer_iostruct & other) const
        {
            if (accelerometer_V_reduced_0_dot_ddt != other.accelerometer_V_reduced_0_dot_ddt
                ) return false;
            if (accelerometer_V_avx_ddt != other.accelerometer_V_avx_ddt) return
                 false;
            if (accelerometer_V_avy_ddt != other.accelerometer_V_avy_ddt) return
                 false;
            if (accelerometer_V_avz_ddt != other.accelerometer_V_avz_ddt) return
                 false;
            if (accelerometer_V_reduced_1_dot_ddt != other.accelerometer_V_reduced_1_dot_ddt
                ) return false;
            if (accelerometer_V_reduced_1_ddt != other.accelerometer_V_reduced_1_ddt
                ) return false;
            if (accelerometer_V_reduced_0_ddt != other.accelerometer_V_reduced_0_ddt
                ) return false;
            if (avz != other.avz) return false;
            if (avy != other.avy) return false;
            if (avx != other.avx) return false;
            if (Cap7 != other.Cap7) return false;
            if (Cap5 != other.Cap5) return false;
            if (Cap2 != other.Cap2) return false;
            if (Cap1 != other.Cap1) return false;
            if (analog_clock != other.analog_clock) return false;
            return true;
        }
    };
    accelerometer_iostruct hif_a2t_data;
    double accelerometer_V_Cap7;
    double accelerometer_V_Cap5;
    double accelerometer_V_Cap2;
    double accelerometer_V_Cap1;
    double accelerometer_V_avz_dot;
    double accelerometer_V_avy_dot;
    double accelerometer_V_avx_dot;
    double accelerometer_V_reduced_1_dot;
    double accelerometer_V_reduced_0_dot;
    double accelerometer_V_reduced_1;
    double accelerometer_V_avy;
    double accelerometer_V_avz;
    double accelerometer_V_avx;
    double accelerometer_V_reduced_0;
    accelerometer();


    ~accelerometer();


    bool process_in_queue;
    bool flag_analog_clock;

    void process();


    void update_input_queue( bool synch_phase = true );


    void update_event_queue();


    void flag_elaboration();


    void synch_elaboration();


    void simulate( accelerometer_iostruct * io_exchange, int32_t & cycles_number
         );


    void start_of_simulation();


    void initialize();


    void finalize();


private:

    accelerometer( const accelerometer & );
    const accelerometer& operator= ( const accelerometer & );


};


#endif
