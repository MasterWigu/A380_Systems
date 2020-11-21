#Fuel system IDs tables
This file has the tables of the ids of the various components of the fuel system


## Tanks (both physical and plane)
| Phys ID | Plane ID | Location                    |
| ---     | ---      | ---                         |
| 0       | 0        | Left Outer                  |
| 1       | 1        | Left feed 1                 |
| 2       | 2        | Left Mid                    |
| 3       | 3        | Left Inr                    |
| 4       | 4        | Left feed 2                 |
| 5       | 5        | Right feed 3                |
| 6       | 6        | Right Inr                   |
| 7       | 7        | Right Mid                   |
| 8       | 8        | Right Feed 4                |
| 9       | 9        | Right Outer                 |
| 10      | 10       | Trim                        |
| -       | 11       | Left feed 1 collector cell  |
| -       | 12       | Left feed 2 collector cell  |
| -       | 13       | Right feed 3 collector cell |
| -       | 14       | Right feed 4 collector cell |

## Buses (physical system)
| ID   | Location                  |
| ---  | ---                       |
| 0    | Fwd Gallery               |
| 1    | Aft Gallery               |
| 2    | Eng 1 feed                |
| 3    | Eng 2 feed                |
| 4    | Eng 3 feed                |
| 5    | Eng 4 feed                |
| 6    | Fwd feed junction         |
| 7    | Trim feed                 |

## Pumps (both physical and plane)
| ID    | Pump location             | Bus  |
| ---   | ---                       | ---  |
| 0     | Feed 1 main pump          | 2    |
| 1     | Feed 1 stby pump          | 2    |
| 2     | Feed 2 main pump          | 3    |
| 3     | Feed 2 stby pump          | 3    |
| 4     | Feed 3 main pump          | 4    |
| 5     | Feed 3 stby pump          | 4    |
| 6     | Feed 4 main pump          | 5    |
| 7     | Feed 4 stby pump          | 5    |
| 8     | Left outer pump           | 0    |
| 9     | Left mid fwd pump         | 0    |
| 10    | Left mid aft pump         | 1    |
| 11    | Left inr fwd pump         | 0    |
| 12    | Left inr atf pump         | 1    |
| 13    | Right inr fwd pump        | 0    |
| 14    | Right inr aft pump        | 1    |
| 15    | Irght mid fwd pump        | 0    |
| 16    | Right mid aft pump        | 1    |
| 17    | Right outer pump          | 0    |
| 18    | Left trim pump            | 7    |
| 19    | Right trim pump           | 7    |
| 20    | APU pump                  | 0    |

## Valves
(T = Tank valve; B = Bus Valve; E = Emergency valve; C = Consumer (LP Valve))

(If the location has "<->" instead of "->", it means the valve is capable of gravity feeding)
  
| Phys ID | Plane ID | Type         | Location (src)      | Location (des)       | Gravity Feeding?    |
| ---     | ---      | ---          | ---                 | ---                  | ---                 |
| T0      | 0        | Tank Valve   | Fwd Gallery         | Left Outer tank      | Yes                 |
| T1      | 1        | Tank Valve   | Aft Gallery         | Left Outer tank      | Yes                 |
| T2      | 2        | Tank Valve   | Fwd Gallery         | Left Feed 1 tank     | No                  |
| T3      | 3        | Tank Valve   | Aft Gallery         | Left Feed 1 tank     | No                  |
| T4      | 4        | Tank Valve   | Fwd Gallery         | Left Mid tank        | No                  |
| T5      | 5        | Tank Valve   | Aft Gallery         | Left Mid tank        | No                  |
| T6      | 6        | Tank Valve   | Fwd Gallery         | Left Inr tank        | No                  |
| T7      | 7        | Tank Valve   | Aft Gallery         | Left Inr tank        | No                  |
| T8      | 8        | Tank Valve   | Fwd Gallery         | Left Feed 2 tank     | No                  |
| T9      | 9        | Tank Valve   | Aft Gallery         | Left Feed 2 tank     | No                  |
| T10     | 10       | Tank Valve   | Fwd Gallery         | Right Feed 3 tank    | No                  |
| T11     | 11       | Tank Valve   | Aft Gallery         | Right Feed 3 tank    | No                  |
| T12     | 12       | Tank Valve   | Fwd Gallery         | Right Inr Tank       | No                  |
| T13     | 13       | Tank Valve   | Aft Gallery         | Right Inr Tank       | No                  |
| T14     | 14       | Tank Valve   | Fwd Gallery         | Right Mid Tank       | No                  |
| T15     | 15       | Tank Valve   | Aft Gallery         | Right Mid Tank       | No                  |
| T16     | 16       | Tank Valve   | Fwd Gallery         | Right Feed 4 tank    | No                  |
| T17     | 17       | Tank Valve   | Aft Gallery         | Right Feed 4 tank    | No                  |
| T18     | 18       | Tank Valve   | Fwd Gallery         | Right Outer tank     | Yes                 |
| T19     | 19       | Tank Valve   | Aft Gallery         | Right Outer tank     | Yes                 |
| T20     | 20       | Tank Valve   | Trim Bus            | Trim tank left       | Yes                 |
| T21     | 21       | Tank Valve   | Trim Bus            | Trim tank right      | Yes                 |
| E0      | 28       | Emerg. Valve | Left Outer tank     | Left Feed 1 tank     | -                   |
| E1      | 29       | Emerg. Valve | Right Outer tank    | Right Feed 4 tank    | -                   |
| B0      | 30       | Bus Valve    | Eng 1 feed          | Fwd feed junction    | -                   |
| B1      | 31       | Bus Valve    | Eng 2 feed          | Fwd feed junction    | -                   |
| B2      | 32       | Bus Valve    | Eng 3 feed          | Fwd feed junction    | -                   |
| B3      | 33       | Bus Valve    | Eng 4 feed          | Fwd feed junction    | -                   |
| B4      | 34       | Bus Valve    | Fwd feed junction   | Fwd Gallery          | -                   |
| B5      | 35       | Bus Valve    | Fwd Gallery (left)  | Aft Gallery (left)   | -                   |
| B6      | 36       | Bus Valve    | Fwd Gallery (right) | Aft Gallery (right)  | -                   |
| B7      | 37       | Bus Valve    | Fwd Gallery         | Trim bus             | -                   |
| B8      | 38       | Bus Valve    | Aft Gallery         | Trim bus             | -                   |
| C0      | 40       | Consumer     | Eng 1 feed          | Engine 1             | -                   |
| C1      | 41       | Consumer     | Eng 2 feed          | Engine 2             | -                   |
| C2      | 42       | Consumer     | Eng 3 feed          | Engine 3             | -                   |
| C3      | 43       | Consumer     | Eng 4 feed          | Engine 4             | -                   |
| C4      | 44       | Consumer     | Fwd Gallery         | APU                  | -                   |
| C5      | 45       | Consumer     | Aft Gallery         | Left Jettison        | -                   |
| C6      | 46       | Consumer     | Aft Gallery         | Right Jettison       | -                   |


## Abnormal Cases
| ID  | FCOM ID | Name                                                       |
| --- | ---     | ---                                                        |
| 0   | 1       | All transfers on Fwd gallery only                          |
| 1   | 2       | All transfers on Aft gallery only                          |
| 2   | 3       | Transfer to the outer tanks on the aft gallery only        |
| 3   | 4       | Gallery functionality swap (for inner tanks)               |
| 4   | 4       | Gallery functionality swap (for mid tanks)                 |
| 5   | 5       | Gravity transfer from the outer tanks                      |
| 6   | 6       | Trim tank transfer                                         |
| 7   | -       | General failure (multiple incompatible cases (i.e. 0 & 1)  |


## Transfers / Templates

(the feeds for engines dont need templates because they are selected in the cockpit with the crossfeed valves)

| ID   | From                    | To                   |
| ---  | ---                     | ---                  |
| 0    | Inner tanks             | Feed tanks 1 & 4     |
| 1    | Inner tanks             | Feed tanks 2 & 3     |
| 2    | Inner tanks             | All feed tanks       |
| 3    | Inner tanks             | Outer tanks          |
| 4    | Mid tanks               | Feed tanks 1 & 4     |
| 5    | Mid tanks               | Feed tanks 2 & 3     |
| 6    | Mid tanks               | All feed tanks       |
| 7    | Mid tanks               | Outer tanks          |
| 8    | Trim tanks              | Inner tanks          |
| 9    | Trim tanks              | Mid tanks            |
| 10   | Trim tanks              | All feed tanks       |
| 11   | Outer tanks             | Inner tanks          |
| 12   | Outer tanks             | Mid tanks            |
| 13   | Outer tanks             | All feed tanks       |
| 14   | ALL TANKS               | Jettison             |



