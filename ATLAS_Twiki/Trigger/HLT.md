**HLT is the ATLAS software system able to select online the good events to store**

Two basic principles:
- regional reconstruction
- early-rejection

# Core HLT framework
## Online and Offline process
![[Screenshot 2025-09-16 at 17.13.56.png]]
![[Screenshot 2025-09-16 at 17.14.14.png]]

## Control flow and data flow
- Data flow: set to true when input data handlers are available
- Control flow: set to true when previous execution is completed

## Event-View processing

Before this part, please make sure you understand ROI(Region of Interest)

## Streaming and Special operations
main stream: majority of events saved into this stream
PEB(partial event building): subset of detector data
TLA(Trigger Level Analysis): some collection reconstructed by HLT

Chains: a standard part + TLA step + PEB step

# A menu of chains
## The menu file
![[Screenshot 2025-09-17 at 17.04.10.png]]
# The trigger chain
chain: selection criteria both for L1 and HLT
each chain in the menu file is represented by ChainProp
![[Screenshot 2025-09-17 at 17.10.29.png]]

## Chains are grouped by Signatures
![[Screenshot 2025-09-17 at 17.15.12.png]]

## Chain name
**name format: HLT + HLTpart + L1seed: each HLT sub-string maps maps a behaviour, sub-strings are grouped by [signature](https://acode-browser1.usatlas.bnl.gov/lxr/source/athena/Trigger/TriggerCommon/TriggerMenuMT/python/HLT/Menu/SignatureDicts.py)** 
one-leg: HLT_mu20
combined-leg: HLT_2mu10_mu12 or HLT_mu26_j20
substrings can also define algorithms 
HLT_mu10_ivarmedium_mu10_10**invmAB**70_L12MU8F
**tag&Probe**?

## Example of a combined chain
![[Screenshot 2025-09-17 at 19.43.05.png]]
![[Screenshot 2025-09-17 at 19.43.54.png]]
2 chainParts:
- g25_medium: medium configured in the gamma code, cut at 25GeV
- tau25_dikaonmass_tracktwoMVA: cut at 25GeV
- 50invmAB: custom combination of legs

## The chain dictionary

all info about a china are stored in a dictionary
![[Screenshot 2025-09-17 at 19.51.21.png]]


# The Chain as a list of Steps
Step1 is the first and seeded by L1
- Menu-sequences: algorithms
- ComboHypo: providing the step decision
- Filter algo will decide if execute next step

don't understand? **Trigger decisions objects**

![[Screenshot 2025-09-17 at 19.57.24.png]]

## Decisions objects