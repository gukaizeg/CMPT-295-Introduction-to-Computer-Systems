#=======================================================================
# Makefile for vector benchmarks
#-----------------------------------------------------------------------

XLEN ?= 64

default: all

src_dir = .


#--------------------------------------------------------------------
# Sources
#--------------------------------------------------------------------

bmarks = \
	SoA \
	Relu \
	ReluEXT \
	Caxpy \
	Imax 

#--------------------------------------------------------------------
# Build rules
#--------------------------------------------------------------------

VECTOR_GCC ?= g++
VECTOR_GCC_OPTS ?= -DPREALLOCATE=1 -ggdb -ffast-math -fno-common -fno-builtin-printf -Wall
VECTOR_LINK ?= $(RISCV_GCC) $(incs)
VECTOR_LINK_OPTS ?= -lm  
VECTOR_SIM ?= 

incs  += -I$(src_dir)/common $(addprefix -I$(src_dir)/, $(bmarks))
objs  :=

define compile_template
$(1).bin: $(wildcard $(src_dir)/$(1)/*) $(wildcard $(src_dir)/common/*)
	$$(VECTOR_GCC) $$(incs) $$(VECTOR_GCC_OPTS) -o $$@ $(wildcard $(src_dir)/$(1)/*.cpp) $(wildcard $(src_dir)/common/*.cpp) $$(VECTOR_LINK_OPTS)
endef

$(foreach bmark,$(bmarks),$(eval $(call compile_template,$(bmark))))

#------------------------------------------------------------
# Build and run benchmarks on riscv simulator

bmarks_vector_bin  = $(addsuffix .bin,  $(bmarks))
bmarks_vector_out  = $(addsuffix .vector.out,  $(bmarks))

$(bmarks_vector_out): %.vector.out: %.bin
	./$< 
	
# 2> $@

run: $(bmarks_riscv_out)

junk += $(bmarks_vector_bin) $(bmarks_vector_hex) $(bmarks_vector_out)

#------------------------------------------------------------
# Default

all: $(bmarks_vector_bin)

#------------------------------------------------------------
# Install


#------------------------------------------------------------
# Clean up
clean:
	rm -rf $(bmarks_vector_out)
	rm -rf $(bmarks_vector_bin)

veryclean:
	rm -rf $(objs) $(junk)

.PHONY: $(bmarks_riscv_out)