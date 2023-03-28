
# Create empty output file

set(output "build/embeds.cpp")
file(WRITE ${output} "#include <Embed.hpp>\n")
# Collect input files
file(GLOB_RECURSE embeds res/*)
# Iterate through input files
foreach(fpath ${embeds})
    # Get short filename
    string(REPLACE ${CMAKE_SOURCE_DIR}/res/ "" fname ${fpath})
    # string(REGEX MATCH "res/+$" fname ${fpath})
    # Replace filename spaces & extension separator for C compatibility
    # string(REGEX REPLACE "\\.| |-" "_" filename ${filename})
    # Read hex data from file
    file(READ ${fpath} filedata HEX)

    string(LENGTH "${filedata}" filedata_length)
    math(EXPR filedata_length "${filedata_length}/2")

    # Convert hex data for C compatibility
    string(REGEX REPLACE "([0-9a-f][0-9a-f])" "0x\\1," filedata ${filedata})
    # Append data to output file
    file(APPEND ${output} "template<> Embed embed<\"${fname}\"> { {${filedata} 0x00}, ${filedata_length}};\n")
endforeach()