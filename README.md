# bin_vis
Binary visualization tool for generating a BMP image through translating the raw binary code of any file of any type wrt. output file size and group size (how many bytes are to be grouped).

1. Use *make* to create the executable *bin_vis*:
```
make
```
2. Usage:
```
./bin_vis <input file.*> <output file.bmp> <groupsize> <width/height>
```
3. For batch generation, move the desired files to the directory *input* and execute *script.py*:
```
python3 script.py <groupsize> <width/height>
```
4. An *output* directory is created after the batch generation with all the BMP files
