##############################################
# Code to make plots from parsed macs output #
# i.e. output of rareDemo.                   #
##############################################

require(lattice)

options <- commandArgs(trailingOnly = TRUE)
if (length(options) > 0) {
    infile <- options[1]
} else {
    infile <- "sim.m5.ts2k.te8k.stat"
}

data <- read.table(infile, header=TRUE, skip=2)

trellis.device()
plot(data$DAC1, data$DAC2, pch=19, xlab="DAC in population 1", ylab="DAC in population 2",
     main="Derived allele counts")
