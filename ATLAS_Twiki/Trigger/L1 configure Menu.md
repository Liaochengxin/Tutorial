Refer: [How to configure the L1 trigger menu](https://indico.cern.ch/event/1489545/contributions/6278488/attachments/3010890/5308544/TriggerTutorialFeb2025_L1Menu.pdf)

This part will cover the configure menu of L1 hardware, it's not hard, but contain a lot of short name

# Hardware
## L1 Menu.json
For some examples, please download relevant file [here](https://atlas-triggertool.web.cern.ch/db/run3/smk/3393/) 
![[Screenshot 2025-09-15 at 19.14.34.png]]
**eFEX, jFEX, gFEX: electron/photo, Jet, global feature extractor, these parameter will help calculate shower variables**
**L1Topo: Level-1 Topological Trigger, basically used for **
**MUCTPI: Muon Central Trigger Processor Interface, can set the threshold for muon, and other topo algorithms**
**CTP: Central Trigger Processor: combine all threshold into L1 complex triggers**

### structure of L1 Menu file
![[Screenshot 2025-09-15 at 19.26.30.png]]
- item: triggers
- threshold: object selection
- topo algorithm: topo selection
![[Screenshot 2025-09-15 at 19.34.03.png]]
### item
name for item please ref [Trigger_naming_Run3](https://twiki.cern.ch/twiki/bin/view/Atlas/TriggerNamingRun3)
ctpid: CTP index, range from 0..512 since CTP have 512 bit
definition: actually is item composition, as you can see here is 1 e & 2 tau & 4 jet 
bunch group: still don't understand? but always contain BGRP0
partition: used to differentiate trigger hardware, but now is deprecated
CTP monitor: monitor low frequency and high frequency 

## thresholds
basically cover the major hardware parameter
![[Screenshot 2025-09-16 at 09.10.01.png]]
detail about thresholds and the working point can be used in thresholds definition
![[Screenshot 2025-09-16 at 09.35.09.png]]

## Topo Algorithm
![[Screenshot 2025-09-16 at 09.46.01.png]]
- sorting algorithms:  arrange and truncate input collections with possible selections on the objects applied
	- klass: class of algorithm
	- input: TOBs is trigger of objects
	- output: name for output set  
	- fixedParameters: hardware parameter
	- variableParameters: physics parameter control
![[Screenshot 2025-09-16 at 09.52.04.png]]

- Decision Alg: make combinations of objects of from the reduced collections and apply topology-criteria on the combinations => 1 output bit per selection (multiple selections can be defined)
	- klass: same for sorting alg
	- input: combination of reduced collection
	- output: after selection set
	- fixed parameter: same for sorting alg 
	- Variable parameter
![[Screenshot 2025-09-16 at 09.53.20.png]]

- Multiplicity alg: just counting object that passed the selection
![[Screenshot 2025-09-16 at 09.57.03.png]]

## Boards
Boards part is about the definition for Board
Boards can connect the Central Trigger Processor and subsystem![[Screenshot 2025-09-16 at 12.02.51.png]]
each key stands for a real board
now, only 5 boards currently in use:
- Topo1(multiplicity counting)
- Topo2, Topo3(topological algorithm)
- MuCTPi(muon data)
- CTPIN9(CTPIN 7/8 already decommissioned) 
Decommissioned boards:
- legacyTopo0,1
- legacyTopoMerger
- CTPIN7, CTPIN8
![[Screenshot 2025-09-16 at 12.14.41.png]]

## CTP
content in L1 menu.json only have 
- CTP input connectors
- CTP monitoring information

configuration for CTP
- L1 items(built from trigger signals and bunch groups)
- Bunchgroup set(separate .json file or database key)
- L1 Prescale set(separate .json file or database key)

# L1 menu configuration software