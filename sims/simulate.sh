#################################
# Code for simulating scenarios #
#################################
## Common parameters
## N_anc=10K, N1, N2=1M
region=5000000
N0=1000000
Nanc=10000 
history=1
theta=0.08 # 4*1e6*2*1e-8
rho=0.04 # 4*1e6*1*1e-8
sample=2000
n1=1000
n2=1000

## Scenario 1: Te=8KYA, Ts=2,4,6,8 KYA m=0.001,0.0001,0.00001
# Ts=2Kya Te=8KYA, 8KYA=320gens=0.00008 in 4N0 generations 2KYA=0.00002
macs $sample $region -t $theta -r $rho -T -I 2 $n1 $n2 40 -eM 0.00002 0 -ej 0.00002001 2 1 -en 0.00002002 2 0 -en 0.00008 1 0.01 > sim.ts2k.te8k.out 

# Ts=4Kya Te=8KYA, 8KYA=320gens=0.00008 in 4N0 generations 4KYA=0.00004
macs $sample $region -t $theta -r $rho -T -I 2 $n1 $n2 40 -eM 0.00004 0 -ej 0.00004001 2 1 -eN 0.00004002 2 0 -en 0.00008 1 0.01 > sim.ts4k.t28k.out

# Ts=6Kya Te=8KYA, 8KYA=320gens=0.00008 in 4N0 generations 6KYA=0.00006
macs $sample $region -t $theta -r $rho -T -I 2 $n1 $n2 40 -eM 0.00006 0 -ej 0.00006001 2 1 -eN 0.00006002 2 0 -en 0.00008 1 0.01 > sim.ts6k.te8k.out

