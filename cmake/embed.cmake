
message("Embedding files...")

find_package(Python3 REQUIRED)

set(EMBED_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/tools/embed.py")
file(GLOB_RECURSE EMBED_FILES res/*)

execute_process(
    COMMAND ${Python3_EXECUTABLE} ${EMBED_SCRIPT} ${EMBED_FILES}
)
