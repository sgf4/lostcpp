
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
    string(REGEX REPLACE "\\.| |-|\/" "_" fname_c ${fname})
    # Read hex data from file
    file(READ ${fpath} filedata HEX)

    string(LENGTH "${filedata}" filedata_length)
    math(EXPR filedata_length "${filedata_length}/2")

    # Convert hex data for C compatibility
    string(REGEX REPLACE "([0-9a-f][0-9a-f])" "0x\\1," filedata ${filedata})
    # Append data to output file
    file(APPEND ${output} "unsigned char ${fname_c}_data[] {${filedata} 0x00}; template<> Embed embed<\"${fname}\"> { ${fname_c}_data, sizeof(${fname_c}_data)};\n")
endforeach()