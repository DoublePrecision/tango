
#include <stdlib.h>
#include <mpi.h>

#include "tango.h"

#define NUM_TIMESTEPS 100
#define SECS_PER_TIMESTEP 1

int main(int argc, char* argv[])
{
    double *air_temp;
    double *sw_flux;
    int i, time;

    air_temp = new double[10];
    sw_flux = new double[10];

    MPI_Init(&argc, &argv);
    tango_init("atm", 1, 1, 1, 1, 1, 1, 1, 1);

    time = 0;
    for (i = 0; i < NUM_TIMESTEPS; i++) {

        tango_begin_transfer(time, "ocean");
        tango_put("air_temp", air_temp, 10);
        tango_put("sw_flux", sw_flux, 10);
        tango_end_transfer();

        time += SECS_PER_TIMESTEP;
    }

    MPI_Finalize();
    tango_finalize();

    delete(air_temp);
    delete(sw_flux);
}