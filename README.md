# muon electron scattering study using Geant4

- Muons of uniform energy distribution are shot at an Al plate of 1 cm x 1 cm lateral dimensions and 0.5 cm thickness
- If an electron scatters off, the exit positions of the muon and the electron produced in the scattering are recorded along with their energies 
- The code plots.C shows how to read the output file from the simulation and plot various graphs using ROOT
- The mac file mu_e.mac contains the commands to be executed by Geant4 to run the simulation.
- To run the simulation, you must first complile the code. Download this code or clone this repository. Let us call this folder as ```src```. Inside the src folder you should find the B1 folder.  Next, create a build folder named ```build``` outside the ```src``` folder and open cmake-gui from that folder. Set the source folder location to ```B1``` and build folder to ```build``` and finally click compile and generate.
- From the build folder, run:
```make -j4 ```
```./exampleB1``` (with visualisation) or
```./exampleB1 mu_e.mac``` (without visualisation)
-On running the last command, the output file ```mu_e.root``` will be created in the build folder. This file contains the data from the simulation.

- Articles to read:
    - https://lss.fnal.gov/archive/other/Part.Kinmatics-(ChaptersI-VI,X).pdf
    - https://web.physics.utah.edu/~jui/5110/hw/kin_rel.pdf