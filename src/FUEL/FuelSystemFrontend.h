//
// Created by MasterWigu on 17/10/2020.
//

#ifndef A380_SYSTEMS_FUELSYSTEMFRONTEND_H
#define A380_SYSTEMS_FUELSYSTEMFRONTEND_H

#include <cstdlib>

namespace FuelSystem {

    /// @class FuelSystemFrontend is the frontend of the entire fuel system.
    /// It serves as a cache (it stores copies of the values it serves) and as an unified I/O point for the fuel system data
    class FuelSystemFrontend {
    private:
        int* tankLevels;
        int* valvesFailStates;
        int* valvesCommStates;
        int* pmpsFailStates;
        bool* pmpsCommStates;

    public:
        /// Instantiates a new frontend
        FuelSystemFrontend();

        /// Gets tank levels from the FQMS (external use)
        /// @param [out] out - pointer where the levels will be returned. MUST have size for 15 ints allocated (11 tanks + 4 collectors)
        void getTankLevels(int* out);

        /// Sets tank levels from the FQMS into the frontend (internal use) (makes deep copy)
        /// @param [in] levels - pointer for array of levels (size=15, 11 tanks + 4 collector cells)
        void setTankLevels(int* levels);

        /// Gets valves fail states (for the ECAM) from the FQMS (external use)
        /// @param [out] out - pointer where the states will be returned. MUST have size for 47 ints allocated
        void getValvesFailStates(int* out);

        /// Sets valves fail states from the FQMS into the frontend (internal use) (makes deep copy)
        /// @param [in] valvesFailStates - pointer for array of states (size=47)
        void setValvesFailStates(int *valvesFailStates);

        /// Gets valves commanded states (for the ECAM) from the FQMS (external use)
        /// @param [out] out - pointer where the states will be returned. MUST have size for 47 ints allocated
        void getValvesCommStates(int* out);

        /// Sets valves commanded states from the FQMS into the frontend (internal use) (makes deep copy)
        /// @param [in] valvesCommStates - pointer for array of states (size=47)
        void setValvesCommStates(int *valvesCommStates);

        /// Gets pumps fail states (for the ECAM) from the FQMS (external use)
        /// @param [out] out - pointer where the states will be returned. MUST have size for 21 ints allocated
        void getPmpsFailStates(int* out);

        /// Sets pumps fail states from the FQMS into the frontend (internal use) (makes deep copy)
        /// @param [in] pmpsFailStates - pointer for array of states (size=21)
        void setPmpsFailStates(int *pmpsFailStates);

        /// Gets pumps commanded states (for the ECAM) from the FQMS (external use)
        /// @param [out] out - pointer where the states will be returned. MUST have size for 21 ints allocated
        void getPmpsCommStates(bool* out);

        /// Sets pumps commanded states from the FQMS into the frontend (internal use) (makes deep copy)
        /// @param [in] pmpsCommStates - pointer for array of states (size=21)
        void setPmpsCommStates(bool *pmpsCommStates);
    };
}


#endif //A380_SYSTEMS_FUELSYSTEMFRONTEND_H
