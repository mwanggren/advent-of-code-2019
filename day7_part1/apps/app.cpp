#include <Computer.hpp>

#include "IORigged.hpp"

#include <iostream>
#include <memory>
#include <cstdlib>

// NOTE: There is some seriously ugly code here that should be cleaned up!
//       I got a AddressSanitizer: heap-buffer-overflow error when using 
//       vector of inputs in rigged IO system, must investigate!

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cout << "Please provide input file as only parameter!" << std::endl;
        return EXIT_FAILURE;
    }
    std::string lInputFile = argv[1];

    int lMaxThrust = 0;
    for (int lAmpAPhase=0; lAmpAPhase < 5; lAmpAPhase++)
    {
        for (int lAmpBPhase=0; lAmpBPhase < 5; lAmpBPhase++)
        {
            for (int lAmpCPhase=0; lAmpCPhase < 5; lAmpCPhase++)
            {
                for (int lAmpDPhase=0; lAmpDPhase < 5; lAmpDPhase++)
                {
                    for (int lAmpEPhase=0; lAmpEPhase < 5; lAmpEPhase++)
                    {
                        int lCurrentThrust = 0;
                        int lPhaseSettings[5] = {lAmpAPhase, lAmpBPhase, lAmpCPhase, lAmpDPhase, lAmpEPhase};
                        bool lUniquePhases = true;
                        for (int ix = 0; ix < 5; ix++)
                            for (int iy = 0; iy < 5; iy++)
                                if ((ix != iy) && (lPhaseSettings[ix] == lPhaseSettings[iy]))
                                    lUniquePhases = false;
                        if (!lUniquePhases)
                            continue;
                        for(int ix = 0; ix < 5; ix++)
                        {
                            IORigged lRiggedIOSystem;
//                            lRiggedIOSystem.addInput(lPhaseSettings[ix]);
//                            lRiggedIOSystem.addInput(lCurrentThrust);
                            lRiggedIOSystem.setFirstInput(lPhaseSettings[ix]);
                            lRiggedIOSystem.setSecondInput(lCurrentThrust);
                            Computer lComputer (&lRiggedIOSystem);
                            if (!(lComputer.loadProgramFromFile(lInputFile)))
                                std::cout << "failed to load program from file" << std::endl;
                            if (!(lComputer.runUntilHalt()))
                                std::cout << "failed to run program until completion" << std::endl; 
                            lCurrentThrust = lRiggedIOSystem.readLastOutput();
                        }
                        if (lCurrentThrust > lMaxThrust) 
                        {
                            std::cout << "New highest " << lCurrentThrust << " was " << lMaxThrust << " seq: " << 
                            lPhaseSettings[0] << "," << lPhaseSettings[1] << "," << lPhaseSettings[2] << "," << lPhaseSettings[3] << "," << lPhaseSettings[4] << std::endl;
                            lMaxThrust = lCurrentThrust;
                        }
                    }
                }
            }
        }
    }
    std::cout << "Max thrust signal is " << lMaxThrust << std::endl;
}
