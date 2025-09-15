**Reference: [data Process Chain](https://indico.cern.ch/event/472469/contributions/1982677/attachments/1220934/1785823/intro_slides.pdf) [General Analysis](https://twiki.cern.ch/twiki/bin/viewauth/AtlasProtected/DataMCForAnalysis)**
**For latest one: please ref this indico [ATLAS induction day](https://indico.cern.ch/event/1369653/)**
overview for Chain
![[Screenshot 2025-09-12 at 19.18.33.png]]

# Trigger
More details: [Trigger slides](https://indico.cern.ch/event/403126/contributions/956172/attachments/1153704/1657569/SoftwareTutorialTrigger-2015-09-14.pdf) [Run2-Trigger paper](https://iopscience.iop.org/article/10.1088/1748-0221/15/10/P10004/pdf)
Level 1: hardware inside ATLAS
High Level Trigger: online trigger
Trigger Process
FE: front-end
ROD: Read-out Driver
![[Screenshot 2025-09-13 at 10.31.28.png]]
[main trigger page](https://twiki.cern.ch/twiki/bin/viewauth/Atlas/AtlasTrigger)
[trigger menu](https://twiki.cern.ch/twiki/bin/view/Atlas/TriggerPhysicsMenu)

# Data Process
![[Screenshot 2025-09-13 at 11.13.44.png]]
## Point 1
Raw data -> Streams(for different goal)
Express Steam is for quick Data Quality and prompt calibration

DCA: Distance of closest approach 
Phi: angle between Closest approach point and Beam
![[Screenshot 2025-09-13 at 11.01.51.png]]

## Tier-0
- Bulk reconstruction uses the majority of the Tier0 resources
- Processes the RAW data using updated calibrations determined in the Prompt Calibration
- Produces many outputs used for a variety of purposes, the most important being the AOD

## data quality and luminosity
- Fast Reconstruction job run to monitoring Data quality and Detector
	- if the detectors are functioning properly
	- if the performance of the physics object (e.g. muon) reconstruction is acceptable
	- Distinguish tolerable from intolerable data quality “defects”
- [GRL](https://twiki.cern.ch/twiki/bin/view/AtlasProtected/GoodRunListsForAnalysisRun2)
- Bad data flag in Lumi block scalar![[Screenshot 2025-09-13 at 11.27.27.png]]
- The luminosity used in your analysis has to account for this missing data

Lumi in analysis should passed
- GRL
- trigger prescales applied
- Level-I trigger live time(fraction of delivered by LHC and recored by ATLAS)

USE lumi-calc tool 

## Tier-1
Reprocess with update condition DB and fix some bug, job will run in the Grid

## Data format
![[Screenshot 2025-09-13 at 19.37.16.png]]
 -  Datasets are collections of files, form fundamental unit of ATLAS data and MC
 - Each processing step changes the data type, and adds the AMI tag used • Changes with Run 2 
	 - the merge m-tag has mostly disappeared for reprocessed data and MC
	 - the p-tag will in general refer to the Derivation Framework version - DAOD

[find data](https://ami.in2p3.fr/?subapp=document) ami is ATLAS metadata interface
[Getting data]()

# MC Production
[Tutorial for MC](https://indico.cern.ch/event/440423/)
### why we need MC
- test performance of Detector
- Calc eff of reco
- modeling interest background process
- modeling interest process
- For ML(Classifier)
- Sys analysis

### Step for MC
- event generation
- detector simulation
- Digitisation

pile-up simulation should be inject with low momentum event

# ATLAS analysis and xAOD
## analysis model
![[Screenshot 2025-09-13 at 21.08.21.png]]

## component of analysis
![[Screenshot 2025-09-13 at 21.13.21.png]]

## Derivation
### data reduction
- skimmer: remove event
- thinner: remove object
- slimmer: remove variable
### argumentation
- add new object container
- new variable

