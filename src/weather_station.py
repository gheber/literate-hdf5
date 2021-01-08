import h5py, numpy as np, platform as pfm

# Weather stations record temperatures and wind speeds

with h5py.File('hello.hdf5', 'w') as f:
    f.attrs['system'] = pfm.system();
    f.attrs['release'] = pfm.release();
    f.attrs['processor'] = pfm.processor();

    # station ID 15
    temperature = np.random.random(1024)
    dt = 10.0   # Temperature sampled every 10 seconds
    wind = np.random.random(2048)
    dt_wind = 5.0   # Wind sampled every 5 seconds
    f['/15/temperature'] = temperature
    f['/15/temperature'].attrs['dt'] = dt
    f['/15/wind'] = wind
    f['/15/wind'].attrs['dt'] = dt_wind
    # station 20
    # f["/20/..."] = ...

from pathlib import Path
print('File size: {} bytes'.format(Path('hello.hdf5').stat().st_size))
