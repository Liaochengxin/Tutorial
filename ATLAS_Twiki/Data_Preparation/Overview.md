welcome to ATLAS data preparation
please read [this](https://twiki.cern.ch/twiki/bin/view/Atlas/DataPreparationIntro) first, which can help you have a overview of the Data preparation

![[Screenshot 2025-09-03 at 11.24.02.png]]
## Tier-0
### Prompt reconstruction
Raw data need to be selected at Tier-0 before distribute to gird
### Streams
reconstruction data are organized into different streams, each stream define by trigger selection and prescales([stream](https://twiki.cern.ch/twiki/bin/view/Atlas/Run3StreamingSetup))
Main streams
- Physics streams: for physics analysis
- Calibration streams:
- Express stream: subset of physics stream, for quick quality check
- Delayed stream:
### Calibration loop
last 48 hours calibration loop, result will used to update calibration constants or conditions database

## Beamspot
Beamspot also called luminous region is the spatial region where collisions take place.

Beamspot reconstruction based on unbind maximum-likelihood fit based on PV(without Beamspot), only PV with the highest sum of squares of transverse momenta of contributing tracks is used.
![[Screenshot 2025-09-03 at 14.21.05.png]]
## Conditions
experts use calibration streams to update some calibration constants and alignment info, include:
- ID subsystem alignment constants
- Precise beamspot location determination
- Masking of noisy SCT strips to prevent biases in track reconstruction
- Masking of noisy LAr channels and rejection of noise bursts

**Conditions Coordinators are responsible for creating and maintaining Global Conditions Tags for both data and Monte Carlo simulations.**
example: CONDBR2-BLKPA-2024-02

## Luminosity
Integrated luminosity delivered from LHC and recorded in ATLAS(Warm start)

Absolute Luminosity determination?



