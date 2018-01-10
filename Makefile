MEASURE=	common/measure
BRANCH?=	$(shell git rev-parse --abbrev-ref HEAD)

all:

$(MEASURE):	$(MEASURE).c
	@make -s -C common

test:		$(MEASURE)
	@[ "$(BRANCH)" = "master" ] \
	    || { (echo "$(BRANCH)" | grep -q reading) && .scripts/submit.py } \
	    || { [ -f "$(BRANCH)/Makefile" ] && (echo "Testing $(BRANCH)" && cd $(BRANCH) && make -s test) }
