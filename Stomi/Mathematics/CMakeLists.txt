# Copyright (c) 2010-2014, Delft University of Technology
# Copyright (c) 2010-2014, K. Kumar (me@kartikkumar.com)
# All rights reserved.
# See http://bit.ly/12SHPLR for license details.

# Set source files.
set(MATHEMATICS_SOURCES
  "${SOURCE_ROOT}${MATHEMATICS_DIR}/basicMathematics.cpp"
)

# Set header files.
set(MATHEMATICS_HEADERS
  "${SOURCE_ROOT}${MATHEMATICS_DIR}/basicMathematics.h"
)

# Add static library.
add_library(stomi_mathematics STATIC ${MATHEMATICS_SOURCES} ${MATHEMATICS_HEADERS})
setup_library_target(stomi_mathematics)
