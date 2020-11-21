# Fuel System

This system is responsible for managing the flows of fuel, controlling valves and pumps. It consists of a physical system and the plane system.

## Physical system
The physical system is the simulation of the real "hardware" in the plane, in this case it is the tanks, fuel pumps, valves and pipes.

### Logic of the physical system
This system doesn't do any management, it is only responsible to respond to the commands issued by the plane system, more specifically, opening and closing valves and turning pumps on and off.

For the calculation of flows of fuel, the system follows a series of steps:
1. See what pipes (buses) are interconnected by open bus valves
    1. It assigns a unique id to each bus
    2. If a bus is connected to another bus, it rewrites the id of that bus to be equal to the id of the first bus
    3. In the end, buses with the same id will be treated as one bus (since they are connected)
2. (for each bus) Poll all the pumps to see how much fuel can be pumped, and if that is 0, poll all the valves for gravity fed fuel
3. (for each bus) Distribute all the available fuel between all consumers (LP Valves) and valves.
4. (for each bus) Order all the pumps (or gravity valves) to really subtract the used fuel from the tanks (this must be done after distribution because there may be an excess of fuel, and we dont need all pumps to pump the maximum amount they reported in 2.)
5. Check if all consumers (Engines & APU) received the amount of fuel they needed and save that info because it will be needed by the engines & APU systems.


## Plane system
The plane system is the simulation of the logic inside the plane's computers, in this system, mainly the FQDC and FQMS.

### Logic of the plane system
There are two main computers in this system, each with specific tasks.

#### FQDC
This computer is responsible to read the levels of the tanks from the physical system. Since we are not simulating the individual sensors, this computer acts only as a placeholder for the simulation of failures (we can introduce deviations in the measured levels that will be sensed by the FQMS)

#### FQMS
This computer is the brain of the fuel system. It decides what transfers are needed and how to do them.

Its logic has several steps:
1. It will start by updating its internal timers
    1. these timers are used to trigger some transfers, as stated on the FCOM, they are:
        1. Time above and bellow FL245
        2. Time above and bellow FL255
        3. Times since the destination is at less than 30 and 80 minutes
2. It will calculate the target CG in flight
3. Read the tank levels, both directly from the physical system and via the FQDC
4. Detect if there are failures (from the last cycle) that trigger any of the abnormal modes
    1. These modes are stated in the FCOM, here we treat mode 3 as two different modes, for fwd and aft galleries
    2. We also add a new mode that represents the case in which there are so many failures that we now have conflicting abnormal modes
5. It will select the transfers that need to be done.
    1. Depending on active abnormal modes, there will be different transfers available and with different priorities.
    2. It will parse the triggering conditions for all transfers and select those that need to be active
6. It will then parse the active transfers and translate that information to valves and pumps that need to be on or off.
    1. This step is done using templates. There is one template for each possible transfer.
        1. The template will return a state for all pumps and valves according to the active abnormal cases.
        2. Some transfers cannot occur in certain abnormal scenarios
        3. Some transfers cannot be triggered manually (via cockpit buttons)
        4. Only a restrict group of transfers can be used in the case of a general fault (the new abnormal mode)
7. The outputs from all active transfers' templates are combined in one state to be transmitted to the physical system
8. After that new state is applied, we check if there is any fail (valve or pump not responding to the state) and store it for analysis in the next cycle.
9. The frontend is updated with the new statuses (for the other systems to read)
