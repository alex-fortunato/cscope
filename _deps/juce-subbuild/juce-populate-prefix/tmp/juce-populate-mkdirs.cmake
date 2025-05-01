# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "/Users/alexanderfortunato/Development/JUCE/cscope/libs/juce")
  file(MAKE_DIRECTORY "/Users/alexanderfortunato/Development/JUCE/cscope/libs/juce")
endif()
file(MAKE_DIRECTORY
  "/Users/alexanderfortunato/Development/JUCE/cscope/_deps/juce-build"
  "/Users/alexanderfortunato/Development/JUCE/cscope/_deps/juce-subbuild/juce-populate-prefix"
  "/Users/alexanderfortunato/Development/JUCE/cscope/_deps/juce-subbuild/juce-populate-prefix/tmp"
  "/Users/alexanderfortunato/Development/JUCE/cscope/_deps/juce-subbuild/juce-populate-prefix/src/juce-populate-stamp"
  "/Users/alexanderfortunato/Development/JUCE/cscope/_deps/juce-subbuild/juce-populate-prefix/src"
  "/Users/alexanderfortunato/Development/JUCE/cscope/_deps/juce-subbuild/juce-populate-prefix/src/juce-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/alexanderfortunato/Development/JUCE/cscope/_deps/juce-subbuild/juce-populate-prefix/src/juce-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/alexanderfortunato/Development/JUCE/cscope/_deps/juce-subbuild/juce-populate-prefix/src/juce-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
