PROJ_NAME = simdim
RCK = raco

DIST_DIR = dist
SRC_DIR  = src
OBJ_DIR  = $(SRC_DIR)/compiled

SRC_FILES = $(PROJ_NAME)
EXEC = $(SRC_DIR)/$(PROJ_NAME)

SRC = $(patsubst %,$(SRC_DIR)/%.rkt,$(SRC_FILES))
OBJ = $(patsubst %,$(OBJ_DIR)/%.zo,$(SRC_FILES))
DIST = $(DIST_DIR)/bin/$(PROJ_NAME)

.PHONY: all clean

all: $(DIST)

clean:
	rm $(EXEC) || true

$(DIST): $(EXEC)
	$(RCK) distribute $(DIST_DIR) $(EXEC)

$(EXEC): $(OBJ)
	$(RCK) exe $(EXEC).rkt

$(OBJ): $(SRC)
	$(RCK) make $(SRC)
